#include "pch.h"
#include "CLevel_MapEditor.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CAssetMgr.h"

#include "CPalette.h"
#include "CTile.h"

#include "CStrawBerry.h"
#include "CWingBerry.h"
#include "CSpring.h"
#include "CZipMover.h"
#include "CPlatform.h"
#include "CBackGround.h"
#include "CPanelUI.h"


extern HINSTANCE hInst;

extern HWND hEdit = nullptr;
extern HWND hEdit_Img = nullptr;
extern HWND hEdit_BG_Tile = nullptr;
extern HWND hEdit_Game_Tile = nullptr;
extern HWND hEdit_BG_OBJ = nullptr;
extern HWND hEdit_Game_OBJ = nullptr;
extern HWND hEdit_Name = nullptr;


CLevel_MapEditor::CLevel_MapEditor()
	: m_GeneratingRoom(false)
	, m_EditBGTile(false)
	, m_EditGameTile(false)
	, m_EditBGObj(false)
	, m_EditGameObj(false)
	, m_EditSpawnPoint(false)
	, m_CurTile(nullptr)
	, m_BGTile(nullptr)
	, m_GameTile(nullptr)
	, m_BGObj(nullptr)
	, m_GameObj(nullptr)
{
	
}

CLevel_MapEditor::~CLevel_MapEditor()
{
	
}


void CLevel_MapEditor::Enter()
{
	// 메뉴 생성
	SetMenu(CEngine::Get()->GetMainHwnd(), m_Menu);
	CEngine::Get()->ChangeWindowResolution();

	// 편집 툴 (새 윈도우)를 띄움 (모달리스 방식)
	ShowWindow(hEdit, SW_SHOW);


	//Load(L"\\map\\.level");

	//Vec2 vRes = CEngine::Get()->GetResolution();

	////CTexture* pTex = CAssetMgr::Get()->FindAsset<CTexture>(L"Level0_bg3");
	////CTexture* pTex = CAssetMgr::Get()->FindAsset<CTexture>(L"Level3_bg2");
	//CTexture* pTex = CAssetMgr::Get()->FindAsset<CTexture>(L"Level1_bg1");

	//CPanelUI* pPanel = new CPanelUI;
	//pPanel->SetTex(pTex);
	////pPanel->SetPos(vRes / 2.f); 
	////pPanel->SetPos(Vec2(vRes.x*4.f/5.f, vRes.y/12.f));
	//pPanel->SetPos(Vec2(vRes.x/2.f, vRes.y/4.f));
	//pPanel->SetMovable(false);
	//pPanel->SetFix(true);


	//Load(L"\\map\\Level_01_Test.level");

	//vector<CObj*>& vec = const_cast<vector<CObj*>&>(GetLayer(LAYER_TYPE::OBJ));

	//vec[vec.size() - 1]->SetRoom(4);

}

void CLevel_MapEditor::Tick_Derived()
{
	// 에디터 화면으로 이동
	if (KEY_TAP(KEY::ESC))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	// 카메라 이동
	if (KEY_PRESSED(KEY::W))
	{
		CCamera::Get()->m_CamPos.y -= 600.f * fDT;
	}
	if (KEY_PRESSED(KEY::S))
	{
		CCamera::Get()->m_CamPos.y += 600.f * fDT;
	}
	if (KEY_PRESSED(KEY::A))
	{
		CCamera::Get()->m_CamPos.x -= 600.f * fDT;
	}
	if (KEY_PRESSED(KEY::D))
	{
		CCamera::Get()->m_CamPos.x += 600.f * fDT;
	}

	// 마우스가 가리키는 실제좌표를 계산
	m_MouseRealPos = CCamera::Get()->GetRealPos(CKeyMgr::Get()->GetMousePos());

	// 새로운 Room을 만든다 (마우스 드래그)
	if (m_GeneratingRoom)
	{
		// 클릭한 좌표
		if (KEY_TAP(KEY::LBtn))
		{
			m_LT = m_MouseRealPos;
		}

		// 클릭 뗀 좌표
		if (KEY_RELEASED(KEY::LBtn))
		{
			m_RB = m_MouseRealPos;

			// 좌표 비교를 통해 LT와 RB를 재계산함
			if (m_LT.x > m_RB.x)
			{
				std::swap(m_LT.x, m_RB.x);
			}
			if (m_LT.y > m_RB.y)
			{
				std::swap(m_LT.y, m_RB.y);
			}

			m_LT = GetTileLT(m_LT);
			m_RB = GetTileRB(m_RB);

			m_Pos = (m_LT + m_RB) / 2.f;
			m_Scale = m_RB - m_LT;
			m_ColRow = m_Scale / TILE_SCALE;

			tRoom room{};
			room.Position = m_Pos;
			room.Scale = m_Scale;

			SetCurRoom(GetRoomCount());
			AddRoom(room);

			// 현재 편집중인 BGTile을 새로 만들어서 등록
			m_BGTile = new CPlatform;
			m_BGTile->SetPos(m_LT);
			m_BGTile->GetComponent<CTileMap>()->SetRowCol((UINT)m_ColRow.y, (UINT)m_ColRow.x);

			Add_Object(m_BGTile, LAYER_TYPE::BACKGROUND);

			// 현재 편집중인 GameTile을 새로 만들어서 등록
			m_GameTile = new CPlatform;
			m_GameTile->SetPos(m_LT);
			CTileMap* pTileMap = m_GameTile->GetComponent<CTileMap>();
			pTileMap->SetRowCol((UINT)m_ColRow.y, (UINT)m_ColRow.x);
			pTileMap->SetCollider(true);

			Add_Object(m_GameTile, LAYER_TYPE::PLATFORM);

			// 룸 생성 종료
			m_GeneratingRoom = false;
		}
	}
	else
	{
		// 마우스 클릭 시 마우스 위치에 따라 편집중인 Room을 옮김
		if (KEY_TAP(KEY::LBtn))
		{
			vector<tRoom>& Rooms = GetRooms();

			// 룸을 순회하면서 어떤 룸을 클릭했는지 체크
			// 아무 룸에도 해당하지 않으면 마지막 룸이 그대로 유지
			for (int i = 0; i < Rooms.size(); ++i)
			{
				const tRoom& room = Rooms[i];

				if (room.Position.x - room.Scale.x / 2.f <= m_MouseRealPos.x
					&& m_MouseRealPos.x <= room.Position.x + room.Scale.x / 2.f
					&& room.Position.y - room.Scale.y / 2.f <= m_MouseRealPos.y
					&& m_MouseRealPos.y <= room.Position.y + room.Scale.y / 2.f)
				{
					MoveRoom(i);

					m_Pos = room.Position;
					m_Scale = room.Scale;
					m_LT = m_Pos - m_Scale / 2.f;
					m_RB = m_Pos + m_Scale / 2.f;
					m_ColRow = (m_RB - m_LT) / TILE_SCALE;
				}
			}

			// 룸에 해당하는 Platform을 현재 편집중인 platform으로 등록
			const vector<CObj*>& vecBackGround = GetLayer(LAYER_TYPE::BACKGROUND);
			const vector<CObj*>& vecPlatform = GetLayer(LAYER_TYPE::PLATFORM);

			for (auto pObj : vecBackGround)
			{
				if (pObj->GetRoom() == GetCurRoom())
				{
					m_BGTile = dynamic_cast<CPlatform*>(pObj);
					if (m_BGTile)
						break;
				}
			}
			
			for (auto pObj : vecPlatform)
			{
				if (pObj->GetRoom() == GetCurRoom())
				{
					m_GameTile = dynamic_cast<CPlatform*>(pObj);
					break;
				}
			}
		}

		// 타일 편집 상태
		if (m_EditBGTile)
		{
			// BG에 해당하는 Platform 타일 편집
			if (KEY_PRESSED(KEY::LBtn))
			{
				CTileMap* pTileMap = m_BGTile->GetComponent<CTileMap>();
				int RowCnt = (int)pTileMap->GetRowCnt();
				int ColCnt = (int)pTileMap->GetColCnt();

				// 마우스 위치가 타일맵의 어떤 타일을 가리키는 지 계산
				int Col = (int)floor((m_MouseRealPos.x - m_LT.x) / TILE_SCALE);
				int Row = (int)floor((m_MouseRealPos.y - m_LT.y) / TILE_SCALE);

				if (0 <= Row && Row < RowCnt
					&& 0 <= Col && Col < ColCnt)
				{
					pTileMap->SetTile(Row, Col, m_CurTile);
				}
			}
			else if (KEY_PRESSED(KEY::RBtn))
			{
				CTileMap* pTileMap = m_BGTile->GetComponent<CTileMap>();
				int RowCnt = (int)pTileMap->GetRowCnt();
				int ColCnt = (int)pTileMap->GetColCnt();

				// 마우스 위치가 타일맵의 어떤 타일을 가리키는 지 계산
				int Col = (int)floor((m_MouseRealPos.x - m_LT.x) / TILE_SCALE);
				int Row = (int)floor((m_MouseRealPos.y - m_LT.y) / TILE_SCALE);

				if (0 <= Row && Row < RowCnt
					&& 0 <= Col && Col < ColCnt)
				{
					pTileMap->SetTile(Row, Col, nullptr);
				}
			}
		}
		else if (m_EditGameTile)
		{
			// Game에 해당하는 Platform 타일 편집
			if (KEY_PRESSED(KEY::LBtn))
			{
				CTileMap* pTileMap = m_GameTile->GetComponent<CTileMap>();
				int RowCnt = (int)pTileMap->GetRowCnt();
				int ColCnt = (int)pTileMap->GetColCnt();

				// 마우스 위치가 타일맵의 어떤 타일을 가리키는 지 계산
				int Col = (int)floor((m_MouseRealPos.x - m_LT.x) / TILE_SCALE);
				int Row = (int)floor((m_MouseRealPos.y - m_LT.y) / TILE_SCALE);

				if (0 <= Row && Row < RowCnt
					&& 0 <= Col && Col < ColCnt)
				{
					pTileMap->SetTile(Row, Col, m_CurTile);
				}
			}
			else if (KEY_PRESSED(KEY::RBtn))
			{
				CTileMap* pTileMap = m_GameTile->GetComponent<CTileMap>();
				int RowCnt = (int)pTileMap->GetRowCnt();
				int ColCnt = (int)pTileMap->GetColCnt();

				// 마우스 위치가 타일맵의 어떤 타일을 가리키는 지 계산
				int Col = (int)floor((m_MouseRealPos.x - m_LT.x) / TILE_SCALE);
				int Row = (int)floor((m_MouseRealPos.y - m_LT.y) / TILE_SCALE);

				if (0 <= Row && Row < RowCnt
					&& 0 <= Col && Col < ColCnt)
				{
					pTileMap->SetTile(Row, Col, nullptr);
				}
			}
		}
		else
		{
			// EditBG나 EditGame 상태가 아니면 m_CurTile을 해제함
			m_CurTile = nullptr;
		}

		// 오브젝트 편집 상태
		if (m_EditBGObj)
		{
			if (m_BGObj)
			{
				Vec2 vScale = m_BGObj->GetScale();
				Vec2 vPos{};

				// 타일 수가 짝수 개일 때
				if ((int)(vScale.x / TILE_SCALE) % 2 == 0)
				{
					vPos.x = GetTileLT(m_MouseRealPos).x;
				}
				// 타일 수가 홀수 개일 때
				else
				{
					vPos.x = GetTileCenter(m_MouseRealPos).x;
				}

				// 타일 수가 짝수 개일 때
				if ((int)(vScale.y / TILE_SCALE) % 2 == 0)
				{
					vPos.y = GetTileLT(m_MouseRealPos).y;
				}
				// 타일 수가 홀수 개일 때
				else
				{
					vPos.y = GetTileCenter(m_MouseRealPos).y;
				}

				// 마우스 움직일 때 보이도록
				m_BGObj->SetPos(vPos);

				if (KEY_RELEASED(KEY::LBtn))
				{
					int RoomNum = 0;
					RoomNum = GetCurRoom();
					
					// 현재 룸이 없을 때는 리턴
					if (RoomNum == -1)
						return;
					
					m_BGObj->SetRoom(RoomNum);

					// 클릭하는 순간 nullptr로 설정하면서 위치 고정시킴
					m_BGObj = nullptr;
				}
			}
				

			
		}
		else if (m_EditGameObj)
		{
			if (m_GameObj)
			{
				Vec2 vScale = m_GameObj->GetScale();
				Vec2 vPos{};

				// 타일 수가 짝수 개일 때
				if ((int)(vScale.x / TILE_SCALE) % 2 == 0)
				{
					vPos.x = GetTileLT(m_MouseRealPos).x;
				}
				// 타일 수가 홀수 개일 때
				else
				{
					vPos.x = GetTileCenter(m_MouseRealPos).x;
				}

				// 타일 수가 짝수 개일 때
				if ((int)(vScale.y / TILE_SCALE) % 2 == 0)
				{
					vPos.y = GetTileLT(m_MouseRealPos).y;
				}
				// 타일 수가 홀수 개일 때
				else
				{
					vPos.y = GetTileCenter(m_MouseRealPos).y;
				}

				// 마우스 움직일 때 보이도록
				m_GameObj->SetPos(vPos);

				if (KEY_TAP(KEY::LBtn))
				{
					CZipMover* pZip = dynamic_cast<CZipMover*>(m_GameObj);
					if (pZip)
					{
						pZip->SetStartPos(vPos);
					}
				}

				if (KEY_RELEASED(KEY::LBtn))
				{
					int RoomNum = 0;
					RoomNum = GetCurRoom();

					// 현재 룸이 없을 때는 리턴
					if (RoomNum == -1)
						return;

					m_GameObj->SetRoom(RoomNum);

					CZipMover* pZip = dynamic_cast<CZipMover*>(m_GameObj);
					if (pZip)
					{
						pZip->SetEndPos(vPos);
						pZip->SetPos(pZip->GetStartPos());
					}

					m_GameObj = nullptr;
				}
			}

			
		}
		

		// 스폰포인트 편집
		if (m_EditSpawnPoint)
		{
			Vec2 vPos = GetTileLT(m_MouseRealPos);
			
			if (KEY_RELEASED(KEY::LBtn))
			{
				EditSpawnPoint(false);

				vector<tRoom>& Rooms = GetRooms();
				Rooms[GetCurRoom()].SpawnPoints.push_back(vPos);
			}
		}
	}
	
	

	
}

void CLevel_MapEditor::Render_Derived()
{
	// 마우스 실제좌표에서 가장 가까운 TILE_SCALE의 배수로 내림 한 X, Y좌표를
	// 다시 렌더 좌표로 변환해서 출력
	Vec2 vLT = RENDER_POS(GetTileLT(m_MouseRealPos));
	Vec2 vRB = RENDER_POS(GetTileRB(m_MouseRealPos));

	{
		SELECT_PEN(BackDC, PEN_TYPE::ORANGE);
		SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);

		// 타일 경계 표시
		Rectangle(BackDC
			, (int)vLT.x, (int)vLT.y, (int)vRB.x, (int)vRB.y);
	}

	if (m_CurTile)
	{
		// 현재 선택된 타일을 표시함 (반투명)
		BLENDFUNCTION blendFunction;
		blendFunction.BlendOp = AC_SRC_OVER;
		blendFunction.BlendFlags = 0;
		blendFunction.SourceConstantAlpha = 128; // 전체 알파 값 (255는 완전 불투명)
		blendFunction.AlphaFormat = AC_SRC_ALPHA;

		Vec2 TileScale = m_CurTile->GetScale();
		Vec2 TileLT = m_CurTile->GetLT();

		AlphaBlend(BackDC
			, (int)vLT.x, (int)vLT.y
			, (int)TileScale.x * 5
			, (int)TileScale.y * 5
			, m_CurTile->GetTex()->GetDC()
			, (int)TileLT.x
			, (int)TileLT.y
			, (int)TileScale.x
			, (int)TileScale.y
			, blendFunction);

	}

	vector<tRoom>& vecRoom = GetRooms();

	for (auto& Room : vecRoom)
	{
		// Room의 경계를 표시
		Vec2 vLT = RENDER_POS(Room.Position - Room.Scale / 2.f);
		Vec2 vRB = RENDER_POS(Room.Position + Room.Scale / 2.f);

		SELECT_PEN(BackDC, PEN_TYPE::BLUE);
		SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);

		Rectangle(BackDC, (int)vLT.x, (int)vLT.y, (int)vRB.x, (int)vRB.y);

		for (auto vPos : Room.SpawnPoints)
		{
			CTexture* pTex = CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Player\\spawnpoint.png")->Stretch(Vec2(TILE_SCALE * 4, TILE_SCALE * 4));

			vPos = RENDER_POS(vPos);

			BLENDFUNCTION blendFunction;
			blendFunction.BlendOp = AC_SRC_OVER;
			blendFunction.BlendFlags = 0;
			blendFunction.SourceConstantAlpha = 255; // 전체 알파 값 (255는 완전 불투명)
			blendFunction.AlphaFormat = AC_SRC_ALPHA;

			int Width = pTex->GetWidth();
			int Height = pTex->GetHeight();

			AlphaBlend(BackDC
				, (int)(vPos.x - Width / 2.f)
				, (int)(vPos.y - Height / 2.f)
				, pTex->GetWidth()
				, pTex->GetHeight()
				, pTex->GetDC()
				, 0, 0
				, pTex->GetWidth()
				, pTex->GetHeight()
				, blendFunction);
		}
	}

	// 스폰포인트 편집
	if (m_EditSpawnPoint)
	{
		// 현재 선택된 타일을 표시함 (반투명)
		BLENDFUNCTION blendFunction;
		blendFunction.BlendOp = AC_SRC_OVER;
		blendFunction.BlendFlags = 0;
		blendFunction.SourceConstantAlpha = 128; // 전체 알파 값 (255는 완전 불투명)
		blendFunction.AlphaFormat = AC_SRC_ALPHA;

		CTexture* pTex = CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Player\\spawnpoint.png")->Stretch(Vec2(TILE_SCALE * 4, TILE_SCALE * 4));

		Vec2 vPos = GetTileCenter(m_MouseRealPos);

		int Width = pTex->GetWidth();
		int Height = pTex->GetHeight();

		AlphaBlend(BackDC
			, (int)(vLT.x-Width/2.f)
			, (int)(vLT.y-Height/2.f)
			, pTex->GetWidth()
			, pTex->GetHeight()
			, pTex->GetDC()
			, 0, 0
			, pTex->GetWidth()
			, pTex->GetHeight()
			, blendFunction);
	}

	
}

Vec2 CLevel_MapEditor::GetTileLT(Vec2 _ClickPos)
{
	float X = floor(_ClickPos.x / TILE_SCALE) * TILE_SCALE;
	float Y = floor(_ClickPos.y / TILE_SCALE) * TILE_SCALE;

	return Vec2(X, Y);
}

Vec2 CLevel_MapEditor::GetTileRB(Vec2 _ClickPos)
{
	float X = floor(_ClickPos.x / TILE_SCALE) * TILE_SCALE + TILE_SCALE;
	float Y = floor(_ClickPos.y / TILE_SCALE) * TILE_SCALE + TILE_SCALE;

	return Vec2(X, Y);
}

Vec2 CLevel_MapEditor::GetTileCenter(Vec2 _ClickPos)
{
	float X = floor(_ClickPos.x / TILE_SCALE) * TILE_SCALE + TILE_SCALE / 2.f;
	float Y = floor(_ClickPos.y / TILE_SCALE) * TILE_SCALE + TILE_SCALE / 2.f;

	return Vec2(X,Y);
}

void CLevel_MapEditor::SaveMap()
{
}

void CLevel_MapEditor::LoadMap()
{
}

// Custom Picture Control
LRESULT CALLBACK CustomPictureProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static CTexture* pTex = nullptr;

	switch (message)
	{
	case WM_CREATE:
	{
	}
	break;
	case STM_SETIMAGE:
		// wParam으로 CTexture*을 받음
		pTex = (CTexture*)wParam;

	break;
	case WM_PAINT:
		if (pTex)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			BLENDFUNCTION blendFunction;
			blendFunction.BlendOp = AC_SRC_OVER;
			blendFunction.BlendFlags = 0;
			blendFunction.SourceConstantAlpha = 255; // 전체 알파 값 (255는 완전 불투명)
			blendFunction.AlphaFormat = AC_SRC_ALPHA;

			int Width = pTex->GetWidth();
			int Height = pTex->GetHeight();

			AlphaBlend(hdc
				, 0, 0
				, Width * 5
				, Height * 5
				, pTex->GetDC()
				, 0, 0
				, Width
				, Height
				, blendFunction);

			EndPaint(hWnd, &ps);
		}
		break;
		
	case WM_LBUTTONDOWN:
	{
		// 클릭 위치 확인
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		// 클릭된 타일의 인덱스 계산
		int Col = (int)floor(x / TILE_SCALE);
		int Row = (int)floor(y / TILE_SCALE);

		// 선택된 타일 처리 (여기서는 메시지 박스 출력)
		wstring TileName = L"Tile_";
		TileName += pTex->GetName() + L"_";
		TileName += std::to_wstring(Row) + L"_";
		TileName += std::to_wstring(Col);

		// MapEditor level의 현재 타일을 설정함
		CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());

		if (pLevel)
		{
			pLevel->SetCurTile(CAssetMgr::Get()->FindAsset<CTile>(TileName));
		}


		return (INT_PTR)TRUE;
	}

	case WM_DESTROY:

		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void RegisterCustomPictureControl(HINSTANCE hInstance)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = CustomPictureProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"CustomPictureControl";

	RegisterClass(&wc);
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK Editor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)	// X 버튼
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		// 새 방 추가하기 버튼
		if (LOWORD(wParam) == IDC_BUTTON2)
		{
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->GenerateRoom();

			return (INT_PTR)TRUE;
		}

		// 배경 이미지 세팅 버튼
		if (LOWORD(wParam) == IDC_BUTTON3)
		{
			ShowWindow(hEdit_Img, SW_SHOW);

			return (INT_PTR)TRUE;
		}


		// 배경 타일 편집 버튼
		if (LOWORD(wParam) == IDC_BUTTON4)
		{
			// BG Edit 상태에 진입
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
			{
				pLevel->EditBGTile(true);
				pLevel->EditGameTile(false);
			}

			ShowWindow(hEdit_BG_Tile, SW_SHOW);

			return (INT_PTR)TRUE;
		}

		// 게임 타일 편집 버튼
		if (LOWORD(wParam) == IDC_BUTTON5)
		{
			// BG Edit 상태에 진입
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
			{
				pLevel->EditBGTile(false);
				pLevel->EditGameTile(true);
			}

			ShowWindow(hEdit_Game_Tile, SW_SHOW);

			return (INT_PTR)TRUE;
		}

		// 배경 오브젝트 배치 버튼
		if (LOWORD(wParam) == IDC_BUTTON6)
		{
			ShowWindow(hEdit_BG_OBJ, SW_SHOW);

			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
			{
				pLevel->EditBGObj(true);
				pLevel->EditGameObj(false);
			}

			return (INT_PTR)TRUE;
		}

		// 게임 오브젝트 배치 버튼
		if (LOWORD(wParam) == IDC_BUTTON7)
		{
			ShowWindow(hEdit_Game_OBJ, SW_SHOW);

			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
			{
				pLevel->EditBGObj(false);
				pLevel->EditGameObj(true);
			}

			return (INT_PTR)TRUE;
		}

		// 스폰포인트 추가 버튼
		if (LOWORD(wParam) == IDC_BUTTON10)
		{
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->EditSpawnPoint(true);

			return (INT_PTR)TRUE;
		}

		// 레벨 이름 설정
		if (LOWORD(wParam) == IDC_BUTTON11)
		{
			ShowWindow(hEdit_Name, SW_SHOW);

			return (INT_PTR)TRUE;
		}

		// 저장 버튼
		if (LOWORD(wParam) == IDC_BUTTON8)
		{
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->SaveWithName(pLevel->GetLevelName());

			return (INT_PTR)TRUE;
		}

		// 불러오기 버튼
		if (LOWORD(wParam) == IDC_BUTTON9)
		{
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
			{
				// 파일 탐색기에서 불러올 파일 선택
				OPENFILENAME OFN{};
				wchar_t szFilePath[255]{};
				wchar_t filter[] = L"맵\0*.level\0모든 파일\0*.*\0";

				OFN.lStructSize = sizeof(OPENFILENAME);
				OFN.hwndOwner = CEngine::Get()->GetMainHwnd();	// 모달 채택할 윈도우를 지정해줌
				OFN.lpstrFilter = filter;
				OFN.lpstrFile = szFilePath;
				OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				OFN.nMaxFile = 255;	// 파일 문자열 최대 길이
				wstring strAnimPath = CPathMgr::Get()->GetContentPath() + L"\\map";
				OFN.lpstrInitialDir = strAnimPath.c_str(); // 창을 켰을 때 디폴트 경로

				if (GetOpenFileName(&OFN)) {

					wstring strExtension = CPathMgr::Get()->GetPathExtension(szFilePath);

					if (wcscmp(strExtension.c_str(), L".level") == 0)
					{
						// 현재 오브젝트를 전부 비움
						pLevel->Exit();

						// 파일을 로드함
						pLevel->Load(CPathMgr::Get()->GetRelativePath(szFilePath));
					}
				}
			}

			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Editor_Img(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hComboBox = nullptr;
	static CTexture* pTex = nullptr;

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// 콤보박스 핸들
		hComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		// 콤보박스 아이템 추가
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level0_bg0"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level0_bg1"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level0_bg2"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level0_bg3"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level1_bg0"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level1_bg1"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level1_bg2"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level3_bg0"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level3_bg1"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level3_bg2"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level3_bg3"));


		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			// 콤보박스
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			// 콤보박스 글 받아옴
			wchar_t selectedText[256]{};
			SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

			// selectedText로 텍스쳐 불러옴
			pTex = CAssetMgr::Get()->FindAsset<CTexture>(selectedText);

		}

		if (LOWORD(wParam) == IDCANCEL)	// X 버튼
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		// 추가 버튼
		if (LOWORD(wParam) == ID_ADD_IMG)
		{
			Vec2 vRes = CEngine::Get()->GetResolution();

			CLevel* pLevel = CLevelMgr::Get()->GetCurLevel();
			CPanelUI* pPanel = new CPanelUI;
			pPanel->SetTex(pTex);
			pPanel->SetPos(vRes / 2.f);
			pPanel->SetMovable(false);
			pPanel->SetFix(true);


			Add_Object(pPanel, LAYER_TYPE::BACKGROUND);

			return (INT_PTR)TRUE;
		}


		break;

	}


	return (INT_PTR)FALSE;
}



// 배경 타일 편집
INT_PTR CALLBACK Editor_Bg_Tile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hPictureControl = NULL;
	static wstring strPalette = L"";

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// 콤보 박스 핸들 가져오기
		HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		// 콤보 박스에 항목 추가
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgBrick"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgBrickRuined"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgCliffside"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgCore"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgDirt"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgLostLevels"));
		//SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgPool"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgReflection"));
		//SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgResortStone"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgSnow"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgSummit"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgTempleA"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgTempleB"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("bgWood"));


		RegisterCustomPictureControl(hInst);

		hPictureControl = CreateWindowEx(
			0,
			L"CustomPictureControl",
			NULL,
			WS_CHILD | WS_VISIBLE,
			30, 100, 240, 600, // 위치와 크기 설정ㅂ
			hDlg,
			NULL,
			hInst,
			NULL
		);

		

		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			// 콤보 박스에서 항목이 선택되었을 때
			HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			// 선택된 항목의 텍스트 가져오기
			wchar_t selectedText[256]{};
			SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);
			
			strPalette = selectedText;

			// selectedText로 텍스쳐를 가져옴
			CTexture* pTex = CAssetMgr::Get()->FindAsset<CTexture>(strPalette);

			if (hPictureControl)
			{
				// 커스텀 picture control에 이미지 세팅 메시지를 보냄 (CTexture 포인터 전달)
				SendMessage(hPictureControl, STM_SETIMAGE, (WPARAM)pTex, NULL);

				// WM_PAINT 메시지를 호출하기 위해 순간적으로 창을 비활성화 함
				InvalidateRect(hDlg, NULL, TRUE);
			}
		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)	// X 버튼
		{
			EndDialog(hDlg, LOWORD(wParam));

			// BG Edit 상태에서 벗어남
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->EditBGTile(false);

			return (INT_PTR)TRUE;
		}

		break;
	}

	return (INT_PTR)FALSE;
	
}

// 게임 타일 편집
INT_PTR CALLBACK Editor_Game_Tile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hPictureControl = NULL;
	static wstring strPalette = L"";

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// 콤보 박스 핸들 가져오기
		HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		// 콤보 박스에 항목 추가
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("cement"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("cliffside"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("cliffsideAlt"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("core"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("deadgrass"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("dirt"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("girder"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("grass"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("lostlevels"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("poolEdges"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("reflection"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("reflectionAlt"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("rock"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("scifi"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("snow"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("starJump"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("stone"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("summit"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("summitNoSnow"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("template"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("templeA"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("templeB"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("tower"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("wood"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("woodStoneEdges"));

		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Spike_Right")); // Tile_Spike_Right_0_0
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Spike_Left"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Spike_Up"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Spike_Down"));

		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Invisible"));

		RegisterCustomPictureControl(hInst);

		hPictureControl = CreateWindowEx(
			0,
			L"CustomPictureControl",
			NULL,
			WS_CHILD | WS_VISIBLE,
			30, 100, 240, 600, // 위치와 크기 설정ㅂ
			hDlg,
			NULL,
			hInst,
			NULL
		);

		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			// 콤보 박스에서 항목이 선택되었을 때
			HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			// 선택된 항목의 텍스트 가져오기
			wchar_t selectedText[256]{};
			SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

			strPalette = selectedText;

			// selectedText로 텍스쳐를 가져옴
			CTexture* pTex = CAssetMgr::Get()->FindAsset<CTexture>(strPalette);

			if (hPictureControl)
			{
				// 커스텀 picture control에 이미지 세팅 메시지를 보냄 (CTexture 포인터 전달)
				SendMessage(hPictureControl, STM_SETIMAGE, (WPARAM)pTex, NULL);

				// WM_PAINT 메시지를 호출하기 위해 순간적으로 창을 비활성화 함
				InvalidateRect(hDlg, NULL, TRUE);
			}
		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)	// X 버튼
		{
			EndDialog(hDlg, LOWORD(wParam));

			// Game Edit 상태에서 벗어남
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->EditGameTile(false);

			return (INT_PTR)TRUE;
		}

		break;	
	}

	return (INT_PTR)FALSE;

}

INT_PTR CALLBACK Editor_Bg_Obj(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// 콤보 박스 핸들 가져오기
		HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		// 콤보 박스에 항목 추가
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\axe.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\fence_a_left.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\fence_a_middle.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\fence_a_right.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\fence_b_middle.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\fence_b_right.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\fence_c_left.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\fence_c_middle.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\fence_c_right.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\house.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("0-prologue\\sign.png"));

		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\bench_concrete.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\bench_concrete_snow.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\big_sign.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\big_sign_b.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\big_sign_c.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\big_sign_d.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\big_sign_e.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\big_sign_f.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\box.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\box_and_bottle.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\brazilian_coffee_building.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\broken_plane.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\camping_medium.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\camping_medium_ruined.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\camping_small.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\car_ruined.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\car_yellow.png"));

		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\checkpoint.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\Collumn_concrete_E.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\Collumn_concrete_E_broken.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\Collumn_concrete_E_less_broken.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\Collumn_concrete_E_very_broken.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\Collumn_concrete_mid.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\Collumn_concrete_mid_broken.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\Collumn_concrete_mid_broken_E.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\collumn_small_broken.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\collumn_small_broken_b.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\collumn_small_E.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\collumn_small_mid.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\cook_pot.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\dashUpTwiceSign.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\flag00.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\hanging_lamp.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\haning_sign.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\house_unfinished.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\hydrant.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\informationKiosk.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\ladder.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\leftArrowSign.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\old_lamp.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\paint_buckets.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\plane.png"));
		

		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\post_broken.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\post_extra_broken.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\posterA.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\posterB.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\posterC.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\posterD.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\posterE.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\poted_plant.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\rags.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\ragsB.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\recliner.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\royal_pizza_building.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\royal_pizza_sign.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\satellite_dish.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\shack_old.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_forard.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_rockslide.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_slippery.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_that_way.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_under_construction.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_you_can_go_down.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_you_can_go_right.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_you_can_go_up.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_you_can_go_park.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_you_can_t_dash.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_you_can_t_go_down.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_you_can_t_go_right.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\sign_you_can_t_go_up.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\skelly.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\statue.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\trafic_lights.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\trafic_lights_ceiling.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\trafic_lights_ceiling_busted.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\weird_vase.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\windowA.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\windowB.png"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("1-forsakencity\\windowC.png"));

		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			// 콤보 박스에서 항목이 선택되었을 때
			HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			// 선택된 항목의 텍스트 가져오기
			wchar_t selectedText[256]{};
			SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
			{
				CBackGround* pObj = pLevel->GetBGObj();
				if (!pObj)
				{
					pObj = new CBackGround();
					Add_Object(pObj, LAYER_TYPE::BACKGROUND);
					pLevel->SetBGObj(pObj);
				}
				
				pObj->SetTexture(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Objects\\decals\\" + wstring(selectedText))->Scale(5.f));
			}
			
		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)	// X 버튼
		{
			EndDialog(hDlg, LOWORD(wParam));

			// Game Edit 상태에서 벗어남
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->EditBGObj(false);

			return (INT_PTR)TRUE;
		}

		break;
	}

	return (INT_PTR)FALSE;

}

#include <commctrl.h>

INT_PTR CALLBACK Editor_Game_Obj(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hRowEdit = nullptr;
	static HWND hColEdit = nullptr;
	static HWND hComboBox = nullptr;
	static HWND hRowSpin = nullptr;
	static HWND hColSpin = nullptr;

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// 핸들 가져오기
		hRowEdit = GetDlgItem(hDlg, IDC_EDIT1);
		hColEdit = GetDlgItem(hDlg, IDC_EDIT2);
		hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
		hRowSpin = GetDlgItem(hDlg, IDC_SPIN1);
		hColSpin = GetDlgItem(hDlg, IDC_SPIN2);

		// 콤보 박스에 항목 추가
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Strawberry"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Strawberry_Wing"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Spring"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("ZipMover"));

		// rowcol 세팅 기본적으로 비활성화
		EnableWindow(hRowEdit, false);
		EnableWindow(hColEdit, false);

		// spin control과 edit control 연결
		SendMessage(hRowSpin, UDM_SETBUDDY, (WPARAM)hRowEdit, 0);
		SendMessage(hColSpin, UDM_SETBUDDY, (WPARAM)hColEdit, 0);


		//return (INT_PTR)TRUE;
		break;
	}

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			// 콤보 박스에서 항목이 선택되었을 때
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			// 선택된 항목의 텍스트 가져오기
			wchar_t selectedText[256]{};
			SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
			{
				EnableWindow(hRowEdit, false);
				EnableWindow(hColEdit, false);

				if (wcscmp(selectedText, L"Strawberry") == 0)
				{
					CObj* pObj = new CStrawBerry;
					pObj->SetScale(Vec2(80.f, 80.f));

					SetWindowText(hRowEdit, std::to_wstring(2).c_str());
					SetWindowText(hColEdit, std::to_wstring(2).c_str());

					pLevel->SetGameObj(pObj);
					Add_Object(pObj, LAYER_TYPE::OBJ);
				}
				else if (wcscmp(selectedText, L"Strawberry_Wing") == 0)
				{
					CObj* pObj = new CWingBerry;
					pObj->SetScale(Vec2(200.f, 120.f));

					SetWindowText(hRowEdit, std::to_wstring(3).c_str());
					SetWindowText(hColEdit, std::to_wstring(5).c_str());

					pLevel->SetGameObj(pObj);
					Add_Object(pObj, LAYER_TYPE::OBJ);
				}
				else if (wcscmp(selectedText, L"Spring") == 0)
				{
					CObj* pObj = new CSpring;
					pObj->SetScale(Vec2(80.f, 80.f));

					SetWindowText(hRowEdit, std::to_wstring(1).c_str());
					SetWindowText(hColEdit, std::to_wstring(2).c_str());

					pLevel->SetGameObj(pObj);
					Add_Object(pObj, LAYER_TYPE::OBJ);
				}
				else if (wcscmp(selectedText, L"ZipMover") == 0)
				{
					EnableWindow(GetDlgItem(hDlg, IDC_EDIT1), true);
					EnableWindow(GetDlgItem(hDlg, IDC_EDIT2), true);

					CObj* pObj = new CZipMover;

					SetWindowText(hRowEdit, std::to_wstring(2).c_str());
					SetWindowText(hColEdit, std::to_wstring(3).c_str());
					
					pLevel->SetGameObj(pObj);
					Add_Object(pObj, LAYER_TYPE::OBJ);
				}
			}
		}

		if (HIWORD(wParam) == EN_CHANGE) {
			if (LOWORD(wParam) == IDC_EDIT1 ) {
				// Edit control에서 값을 받음
				wchar_t szBuff[256]{};
				GetWindowText(hRowEdit, szBuff, 255);
				int newValue = _wtoi(szBuff);

				// Do something with newValue
				CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
				if (pLevel)
				{
					CZipMover* pObj = dynamic_cast<CZipMover*>(pLevel->GetGameObj());
					if (pObj)
					{
						pObj->SetTile(newValue, pObj->GetCol());
					}
				}
			}
			else if (LOWORD(wParam) == IDC_EDIT2) {
				// Edit control에서 값을 받음
				wchar_t szBuff[256]{};
				GetWindowText(hColEdit, szBuff, 255);
				int newValue = _wtoi(szBuff);

				// Do something with newValue
				CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
				if (pLevel)
				{
					CZipMover* pObj = dynamic_cast<CZipMover*>(pLevel->GetGameObj());
					if (pObj)
					{
						pObj->SetTile(pObj->GetRow(), newValue);
					}
				}
			}
		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)	// X 버튼
		{
			EndDialog(hDlg, LOWORD(wParam));

			// Game Edit 상태에서 벗어남
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->EditGameTile(false);

			return (INT_PTR)TRUE;
		}

		break;
	}

	return (INT_PTR)FALSE;

}

INT_PTR CALLBACK Editor_Name(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit = nullptr;

	switch (message)
	{
	case WM_INITDIALOG:
	{
		hEdit = GetDlgItem(hDlg, IDC_EDIT1);
	}
		return (INT_PTR)TRUE;


	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)	// X 버튼
		{
			wchar_t szBuff[256]{};
			GetWindowText(hEdit, szBuff, 255);

			// 이름 세팅
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->SetLevelName(szBuff);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}