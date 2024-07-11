#include "pch.h"
#include "CLevel_MapEditor.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"

#include "CPalette.h"
#include "CTile.h"

#include "CStrawBerry.h"
#include "CPlatform.h"


extern HINSTANCE hInst;

extern HWND hEdit = nullptr;
extern HWND hEdit_Img = nullptr;
extern HWND hEdit_BG_Tile = nullptr;
extern HWND hEdit_Game_Tile = nullptr;
extern HWND hEdit_BG_OBJ = nullptr;
extern HWND hEdit_Game_OBJ = nullptr;

INT_PTR CALLBACK Editor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CLevel_MapEditor::CLevel_MapEditor()
	: m_GeneratingRoom(false)
	, m_EditBG(false)
	, m_EditGame(false)
	, m_CurTile(nullptr)
	, m_BGTile(nullptr)
	, m_GameTile(nullptr)
{
	
}

CLevel_MapEditor::~CLevel_MapEditor()
{
	
}


void CLevel_MapEditor::Enter()
{
	// �޴� ����
	SetMenu(CEngine::Get()->GetMainHwnd(), m_Menu);
	CEngine::Get()->ChangeWindowResolution();

	// ���� �� (�� ������)�� ��� (��޸��� ���)
	ShowWindow(hEdit, SW_SHOW);


	Load(L"\\map\\Level_MapEditor.level");


	// Strawberry
	//CStrawBerry* pStrawberry = new CStrawBerry;
	//pStrawberry->SetPos(Vec2(200.f, 400.f));
	//pStrawberry->SetScale(Vec2(80.f, 80.f));
	//pStrawberry->SetRoom(0);

	//AddObject(pStrawberry, LAYER_TYPE::OBJ);


	

}

void CLevel_MapEditor::Tick_Derived()
{
	// ���콺�� ����Ű�� ������ǥ�� ���
	m_MouseRealPos = CCamera::Get()->GetRealPos(CKeyMgr::Get()->GetMousePos());

	// ���ο� Room�� ����� (���콺 �巡��)
	if (m_GeneratingRoom)
	{
		// Ŭ���� ��ǥ
		if (KEY_TAP(KEY::LBtn))
		{
			m_LT = m_MouseRealPos;
		}

		// Ŭ�� �� ��ǥ
		if (KEY_RELEASED(KEY::LBtn))
		{
			m_RB = m_MouseRealPos;

			// ��ǥ �񱳸� ���� LT�� RB�� ������
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
			room.SpawnPoints.push_back(m_Pos);

			SetCurRoom(GetRoomCount());
			AddRoom(room);

			// ���� �������� BGTile�� ���� ���� ���
			m_BGTile = new CPlatform;
			m_BGTile->SetPos(m_LT);
			m_BGTile->SetRoom(GetCurRoom());
			m_BGTile->GetComponent<CTileMap>()->SetRowCol((UINT)m_ColRow.y, (UINT)m_ColRow.x);

			Add_Object(m_BGTile, LAYER_TYPE::BACKGROUND);

			// ���� �������� GameTile�� ���� ���� ���
			m_GameTile = new CPlatform;
			m_GameTile->SetPos(m_LT);
			m_BGTile->SetRoom(GetCurRoom());
			m_GameTile->GetComponent<CTileMap>()->SetRowCol((UINT)m_ColRow.y, (UINT)m_ColRow.x);

			Add_Object(m_GameTile, LAYER_TYPE::PLATFORM);

			// �� ���� ����
			m_GeneratingRoom = false;
		}
	}
	else
	{
		// ���콺 Ŭ�� �� ���콺 ��ġ�� ���� �������� Room�� �ű�
		if (KEY_TAP(KEY::LBtn))
		{
			vector<tRoom>& Rooms = GetRooms();

			// ���� ��ȸ�ϸ鼭 � ���� Ŭ���ߴ��� üũ
			// �ƹ� �뿡�� �ش����� ������ ������ ���� �״�� ����
			for (int i = 0; i < Rooms.size(); ++i)
			{
				tRoom& room = Rooms[i];

				if (room.Position.x - room.Scale.x / 2.f <= m_MouseRealPos.x
					&& m_MouseRealPos.x <= room.Position.x + room.Scale.x / 2.f
					&& room.Position.y - room.Scale.y / 2.f <= m_MouseRealPos.y
					&& m_MouseRealPos.y <= room.Position.y + room.Scale.y / 2.f)
				{
					SetCurRoom(i);

					m_Pos = room.Position;
					m_Scale = room.Scale;
					m_LT = m_Pos - m_Scale / 2.f;
					m_RB = m_Pos + m_Scale / 2.f;
					m_ColRow = (m_RB - m_LT) / TILE_SCALE;
				}
			}

			// �뿡 �ش��ϴ� Platform�� ���� �������� platform���� ���
			const vector<CObj*>& vecBackGround = GetLayer(LAYER_TYPE::BACKGROUND);
			const vector<CObj*>& vecPlatform = GetLayer(LAYER_TYPE::PLATFORM);

			for (auto pObj : vecBackGround)
			{
				if (pObj->GetRoom() == GetCurRoom())
				{
					m_BGTile = dynamic_cast<CPlatform*>(pObj);
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

		// ���� ����
		if (m_EditBG)
		{
			// BG�� �ش��ϴ� Platform Ÿ�� ����
			if (KEY_PRESSED(KEY::LBtn) && m_BGTile)
			{
				CTileMap* pTileMap = m_BGTile->GetComponent<CTileMap>();
				int RowCnt = (int)pTileMap->GetRowCnt();
				int ColCnt = (int)pTileMap->GetColCnt();

				// ���콺 ��ġ�� Ÿ�ϸ��� � Ÿ���� ����Ű�� �� ���
				int Col = (int)floor((m_MouseRealPos.x - m_LT.x) / TILE_SCALE);
				int Row = (int)floor((m_MouseRealPos.y - m_LT.y) / TILE_SCALE);

				if (0 <= Row && Row < RowCnt
					&& 0 <= Col && Col < ColCnt)
				{
					pTileMap->SetTile(Row, Col, m_CurTile);
				}

			}
		}
		else if (m_EditGame)
		{
			// Game�� �ش��ϴ� Platform Ÿ�� ����
			if (KEY_PRESSED(KEY::LBtn) && m_GameTile)
			{
				CTileMap* pTileMap = m_GameTile->GetComponent<CTileMap>();
				int RowCnt = (int)pTileMap->GetRowCnt();
				int ColCnt = (int)pTileMap->GetColCnt();

				// ���콺 ��ġ�� Ÿ�ϸ��� � Ÿ���� ����Ű�� �� ���
				int Col = (int)floor((m_MouseRealPos.x - m_LT.x) / TILE_SCALE);
				int Row = (int)floor((m_MouseRealPos.y - m_LT.y) / TILE_SCALE);

				if (0 <= Row && Row < RowCnt
					&& 0 <= Col && Col < ColCnt)
				{
					pTileMap->SetTile(Row, Col, m_CurTile);
				}
			}
		}
		else
		{
			// EditBG�� EditGame ���°� �ƴϸ� m_CurTile�� ������
			m_CurTile = nullptr;
		}
	}
	
	

	
}

void CLevel_MapEditor::Render_Derived()
{
	// ���콺 ������ǥ���� ���� ����� TILE_SCALE�� ����� ���� �� X, Y��ǥ��
	// �ٽ� ���� ��ǥ�� ��ȯ�ؼ� ���
	Vec2 vLT = RENDER_POS(GetTileLT(m_MouseRealPos));
	Vec2 vRB = RENDER_POS(GetTileRB(m_MouseRealPos));

	{
		SELECT_PEN(BackDC, PEN_TYPE::ORANGE);
		SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);

		// Ÿ�� ��� ǥ��
		Rectangle(BackDC
			, (int)vLT.x, (int)vLT.y, (int)vRB.x, (int)vRB.y);
	}

	if (m_CurTile)
	{
		// ���� ���õ� Ÿ���� ǥ���� (������)
		BLENDFUNCTION blendFunction;
		blendFunction.BlendOp = AC_SRC_OVER;
		blendFunction.BlendFlags = 0;
		blendFunction.SourceConstantAlpha = 128; // ��ü ���� �� (255�� ���� ������)
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
		// Room�� ��踦 ǥ��
		Vec2 vLT = Room.Position - Room.Scale / 2.f;
		Vec2 vRB = Room.Position + Room.Scale / 2.f;

		SELECT_PEN(BackDC, PEN_TYPE::BLUE);
		SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);

		Rectangle(BackDC, (int)vLT.x, (int)vLT.y, (int)vRB.x, (int)vRB.y);
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
		// wParam���� CTexture*�� ����
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
			blendFunction.SourceConstantAlpha = 255; // ��ü ���� �� (255�� ���� ������)
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
		// Ŭ�� ��ġ Ȯ��
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		// Ŭ���� Ÿ���� �ε��� ���
		int Col = (int)floor(x / TILE_SCALE);
		int Row = (int)floor(y / TILE_SCALE);

		// ���õ� Ÿ�� ó�� (���⼭�� �޽��� �ڽ� ���)
		wstring TileName = L"Tile_";
		TileName += pTex->GetName() + L"_";
		TileName += std::to_wstring(Row) + L"_";
		TileName += std::to_wstring(Col);

		// MapEditor level�� ���� Ÿ���� ������
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK Editor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)	// X ��ư
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		// �� �� �߰��ϱ� ��ư
		if (LOWORD(wParam) == IDC_BUTTON2)
		{
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->GenerateRoom();

			return (INT_PTR)TRUE;
		}

		// ��� �̹��� ���� ��ư
		if (LOWORD(wParam) == IDC_BUTTON3)
		{
			ShowWindow(hEdit_Img, SW_SHOW);

			return (INT_PTR)TRUE;
		}

		// ��� Ÿ�� ���� ��ư
		if (LOWORD(wParam) == IDC_BUTTON4)
		{
			ShowWindow(hEdit_BG_Tile, SW_SHOW);

			return (INT_PTR)TRUE;
		}

		// ���� Ÿ�� ���� ��ư
		if (LOWORD(wParam) == IDC_BUTTON5)
		{
			ShowWindow(hEdit_Game_Tile, SW_SHOW);

			return (INT_PTR)TRUE;
		}

		// ��� ������Ʈ ��ġ ��ư
		if (LOWORD(wParam) == IDC_BUTTON6)
		{
			ShowWindow(hEdit_BG_OBJ, SW_SHOW);

			return (INT_PTR)TRUE;
		}

		// ���� ������Ʈ ��ġ ��ư
		if (LOWORD(wParam) == IDC_BUTTON7)
		{
			ShowWindow(hEdit_Game_OBJ, SW_SHOW);

			return (INT_PTR)TRUE;
		}

		// ���� ��ư
		if (LOWORD(wParam) == IDC_BUTTON8)
		{
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->Save();

			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}


// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK Editor_Img(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// �޺� �ڽ� �ڵ� ��������
		HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		// �޺� �ڽ��� �׸� �߰�
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level1_bg1"));
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)_T("Level0_bg3"));


		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			// �޺� �ڽ����� �׸��� ���õǾ��� ��
			HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			// ���õ� �׸��� �ؽ�Ʈ ��������
			wchar_t selectedText[256];
			SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

			// selectedText�� �ؽ��ĸ� ������
			CTexture* pTex = CAssetMgr::Get()->FindAsset<CTexture>(selectedText);

		}

		if (LOWORD(wParam) == IDCANCEL)	// X ��ư
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		// �̹��� �߰� ��ư
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			


			return (INT_PTR)TRUE;
		}


		break;

	}

	
	return (INT_PTR)FALSE;
}


// ��� Ÿ�� ����
INT_PTR CALLBACK Editor_Bg_Tile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hPictureControl = NULL;
	static wstring strPalette = L"";

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// �޺� �ڽ� �ڵ� ��������
		HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		// �޺� �ڽ��� �׸� �߰�
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
			30, 100, 240, 600, // ��ġ�� ũ�� ������
			hDlg,
			NULL,
			hInst,
			NULL
		);

		// BG Edit ���¿� ����
		CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
		if (pLevel)
			pLevel->EditBG(true);

		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			// �޺� �ڽ����� �׸��� ���õǾ��� ��
			HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			// ���õ� �׸��� �ؽ�Ʈ ��������
			wchar_t selectedText[256];
			SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);
			
			strPalette = selectedText;

			// selectedText�� �ؽ��ĸ� ������
			CTexture* pTex = CAssetMgr::Get()->FindAsset<CTexture>(strPalette);

			if (hPictureControl)
			{
				// Ŀ���� picture control�� �̹��� ���� �޽����� ���� (CTexture ������ ����)
				SendMessage(hPictureControl, STM_SETIMAGE, (WPARAM)pTex, NULL);

				// WM_PAINT �޽����� ȣ���ϱ� ���� ���������� â�� ��Ȱ��ȭ ��
				InvalidateRect(hDlg, NULL, TRUE);
			}
		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)	// X ��ư
		{
			EndDialog(hDlg, LOWORD(wParam));

			// BG Edit ���¿��� ���
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->EditBG(false);

			return (INT_PTR)TRUE;
		}



		break;
	}

	

	return (INT_PTR)FALSE;
	
}

// ���� Ÿ�� ����
INT_PTR CALLBACK Editor_Game_Tile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hPictureControl = NULL;
	static wstring strPalette = L"";

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// �޺� �ڽ� �ڵ� ��������
		HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		// �޺� �ڽ��� �׸� �߰�
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

		RegisterCustomPictureControl(hInst);

		hPictureControl = CreateWindowEx(
			0,
			L"CustomPictureControl",
			NULL,
			WS_CHILD | WS_VISIBLE,
			30, 100, 240, 600, // ��ġ�� ũ�� ������
			hDlg,
			NULL,
			hInst,
			NULL
		);


		// Game Edit ���¿� ����
		CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
		if (pLevel)
			pLevel->EditGame(true);

		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			// �޺� �ڽ����� �׸��� ���õǾ��� ��
			HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			// ���õ� �׸��� �ؽ�Ʈ ��������
			wchar_t selectedText[256];
			SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

			strPalette = selectedText;

			// selectedText�� �ؽ��ĸ� ������
			CTexture* pTex = CAssetMgr::Get()->FindAsset<CTexture>(strPalette);

			if (hPictureControl)
			{
				// Ŀ���� picture control�� �̹��� ���� �޽����� ���� (CTexture ������ ����)
				SendMessage(hPictureControl, STM_SETIMAGE, (WPARAM)pTex, NULL);

				// WM_PAINT �޽����� ȣ���ϱ� ���� ���������� â�� ��Ȱ��ȭ ��
				InvalidateRect(hDlg, NULL, TRUE);
			}
		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)	// X ��ư
		{
			EndDialog(hDlg, LOWORD(wParam));

			// Game Edit ���¿��� ���
			CLevel_MapEditor* pLevel = dynamic_cast<CLevel_MapEditor*>(CLevelMgr::Get()->GetCurLevel());
			if (pLevel)
				pLevel->EditGame(false);

			return (INT_PTR)TRUE;
		}



		break;	
	}



	return (INT_PTR)FALSE;

}