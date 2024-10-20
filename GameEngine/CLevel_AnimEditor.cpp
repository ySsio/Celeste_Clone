#include "pch.h"
#include "CLevel_AnimEditor.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CAnimation.h"
#include "CTimeMgr.h"

#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CAnimEditorUI.h"
#include "CTextBoxUI.h"
#include "CTextUI.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"

CLevel_AnimEditor::CLevel_AnimEditor()
	: m_AnimEditorUI(nullptr)
	, m_BangFrm(0)
	, m_BodyFrm(0)
	, m_BangFrmCnt(0)
	, m_BodyFrmCnt(0)
	, m_BangFrmTxt(nullptr)
	, m_BodyFrmTxt(nullptr)
	, m_BangFrmCntTxt(nullptr)
	, m_BodyFrmCntTxt(nullptr)
	, m_BangName(nullptr)
	, m_BangOffsetX(nullptr)
	, m_BangOffsetY(nullptr)
	, m_BangDuration(nullptr)
	, m_BodyName(nullptr)
	, m_BodyOffsetX(nullptr)
	, m_BodyOffsetY(nullptr)
	, m_BodyDuration(nullptr)
{
}


CLevel_AnimEditor::~CLevel_AnimEditor()
{
}


void CLevel_AnimEditor::Enter()
{
	Vec2 vRes = CEngine::Get()->GetResolution();

	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetPos(Vec2(-1.f, -1.f));
	pPanel->SetScale(Vec2(vRes.x + 1, vRes.y + 1));
	pPanel->SetMovable(false);

	AddObject(pPanel, LAYER_TYPE::UI);

	m_AnimEditorUI = new CAnimEditorUI;
	m_AnimEditorUI->SetPos(Vec2(50.f, 50.f));
	m_AnimEditorUI->SetScale(Vec2(500.f, 500.f));

	pPanel->AddChild(m_AnimEditorUI);

	CButtonUI* pButton = new CButtonUI;
	pButton->SetPos(Vec2(200.f, 600.f));
	pButton->SetFunction([=]() {m_AnimEditorUI->DecrBangFrm();});
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_left.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(400.f, 600.f));
	pButton->SetFunction([=]() {m_AnimEditorUI->IncrBangFrm();});
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_right.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(200.f, 650.f));
	pButton->SetFunction([=]() {m_AnimEditorUI->DecrBodyFrm(); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_left.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(400.f, 650.f));
	pButton->SetFunction([=]() {m_AnimEditorUI->IncrBodyFrm(); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_right.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(200.f, 700.f));
	pButton->SetFunction([=]() {m_AnimEditorUI->DecrBangFrm(); m_AnimEditorUI->DecrBodyFrm(); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_left.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(400.f, 700.f));
	pButton->SetFunction([=]() {m_AnimEditorUI->IncrBangFrm(); m_AnimEditorUI->IncrBodyFrm(); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_right.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(500.f, 620.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\play.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {m_AnimEditorUI->Play(); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(500.f, 680.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\pause.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {m_AnimEditorUI->Stop(); });

	pPanel->AddChild(pButton);


	SetBkMode(BackDC, TRANSPARENT);

	CTextUI* pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(70.f, 600.f));
	pTextUI->SetText(L"Bang");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(70.f, 650.f));
	pTextUI->SetText(L"Body");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(70.f, 700.f));
	pTextUI->SetText(L"All");

	pPanel->AddChild(pTextUI);

	m_BangFrmTxt = new CTextUI();
	m_BangFrmTxt->SetPos(Vec2(300.f, 600.f));
	m_BangFrmTxt->SetText(L"Frame 0");

	pPanel->AddChild(m_BangFrmTxt);

	m_BodyFrmTxt = new CTextUI();
	m_BodyFrmTxt->SetPos(Vec2(300.f, 650.f));
	m_BodyFrmTxt->SetText(L"Frame 0");

	pPanel->AddChild(m_BodyFrmTxt);

	// 머리 애니메이션, 프레임 정보
	float tempX = 600.f;
	float tempY = 120.f;

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX - 20.f, tempY));
	pTextUI->SetText(L"애니메이션 정보");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, tempY + 40.f));
	pTextUI->SetText(L"애니메이션 이름");

	pPanel->AddChild(pTextUI);

	m_BangName = new CTextBoxUI();
	m_BangName->SetPos(Vec2(tempX + 10.f, tempY + 80.f));
	m_BangName->SetScale(Vec2(230.f, 20.f));

	pPanel->AddChild(m_BangName);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 250.f, tempY + 80.f));
	pTextUI->SetText(L".anim");

	pPanel->AddChild(pTextUI);

	m_BangFrmCntTxt = new CTextUI();
	m_BangFrmCntTxt->SetPos(Vec2(tempX, tempY + 140.f));
	m_BangFrmCntTxt->SetText(L"프레임 수 : 0");

	pPanel->AddChild(m_BangFrmCntTxt);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 170.f, tempY + 140.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\add.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {

		// 현재 편집중인 애니메이션이 없으면 오류
		if (!m_AnimEditorUI->GetBang())
		{
			MessageBox(CEngine::Get()->GetMainHwnd(), L"편집중인 애니메이션이 없습니다.\n새 애니메이션을 생성하거나 기존 애니메이션을 불러오세요.", L"애니메이션 편집 오류", MB_OK);
			return;
		}

		OPENFILENAME OFN{};
		wchar_t szFilePath[255]{};
		wchar_t filter[] = L"이미지\0*.png\0모든 파일\0*.*\0";

		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = CEngine::Get()->GetMainHwnd();	// 모달 채택할 윈도우를 지정해줌
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = szFilePath;
		OFN.Flags = OFN_ALLOWMULTISELECT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		OFN.nMaxFile = 255;	// 파일 문자열 최대 길이
		wstring strAnimPath = CPathMgr::Get()->GetContentPath() + L"\\texture";
		OFN.lpstrInitialDir = strAnimPath.c_str(); // 창을 켰을 때 디폴트 경로

		if (GetOpenFileName(&OFN)) {

			// 선택한 파일 이름을 저장하는 벡터
			vector<wstring> vecFileNames;

			// 문자열 포인터
			wchar_t* p = OFN.lpstrFile;

			// 파일이 존재하는 디렉토리를 받음 (파일 이름과 확장자를 제외한 파일의 위치, \\로 끝남)
			// 한 개의 파일을 선택한 경우, 원래대로 파일경로가 나오는데
			// 여러 개의 파일을 선택한 경우, 파일 디렉토리와 파일 이름이 공백으로 구분되어 나옴.
			// 예) 한 개 = D://file1.png, 여러 개 = D:// file1.png file2.png file3.png
			// wchar_t*를 wstring으로 변환하면 공백직전까지로 인식함.
			wstring FileDirectory = CPathMgr::Get()->GetFileDirectory(p);

			// 첫번째 파일 이름을 가리키는 곳으로 포인터를 이동
			p += FileDirectory.length();
			if (*p == ' ')
				++p;
			
			while (*p != '\0')
			{
				wstring FileNames = p;
				wstring FileName = FileNames.substr(0,FileNames.find(L".png")+4);

				vecFileNames.push_back(FileName);
				p += FileName.length() + 1;
			}

			for (const wstring& fileName : vecFileNames)
			{
				wstring fileDir = FileDirectory + fileName;

				wstring strExtension = CPathMgr::Get()->GetPathExtension(fileDir);

				if (wcscmp(strExtension.c_str(), L".png") == 0)
				{
					// 선택한 이미지를 텍스쳐로 불러옴
					CTexture* pTex = CAssetMgr::Get()->LoadAsset<CTexture>(CPathMgr::Get()->GetRelativePath(fileDir));
					pTex->Stretch(Vec2(BANG_SCALE, BANG_SCALE));

					// 새 프레임을 가장 마지막에 추가함
					tAnimFrm frm{};
					frm.Duration = DEFAULT_FRM_DURATION;
					frm.Offset = Vec2(0.f, 0.f);
					frm.Texture = pTex;

					m_AnimEditorUI->AddBangFrm(frm);

					// 불러온 애니메이션 초기값 세팅
					LoadBangVariables();
				}
					
			}
		}
		});

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 200.f, tempY + 140.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\remove.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {

		// 현재 편집중인 애니메이션이 없으면 오류
		if (!m_AnimEditorUI->GetBang())
		{
			MessageBox(CEngine::Get()->GetMainHwnd(), L"편집중인 애니메이션이 없습니다.\n새 애니메이션을 생성하거나 기존 애니메이션을 불러오세요.", L"애니메이션 편집 오류", MB_OK);
			return;
		}

		// 현재 보고 있는 프레임을 제거한다
		m_AnimEditorUI->EraseBangFrm(m_BangFrm);

		});

	pPanel->AddChild(pButton);

	

	// Bang 프레임 정보
	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX - 20.f, 360.f));
	pTextUI->SetText(L"프레임 정보");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 420.f));
	pTextUI->SetText(L"Offset");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 100.f, 420.f));
	pTextUI->SetText(L"x :");

	pPanel->AddChild(pTextUI);

	m_BangOffsetX = new CTextBoxUI();
	m_BangOffsetX->SetPos(Vec2(tempX + 130.f, 420.f));
	m_BangOffsetX->SetScale(Vec2(40.f, 40.f));
	m_BangOffsetX->SetInteger(true);

	pPanel->AddChild(m_BangOffsetX);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 140.f, 398.f));
	pButton->SetFunction([=]() {int val = m_BangOffsetX->GetIntValue(); m_BangOffsetX->SetNumValue(val + 1); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_up.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 140.f, 462.f));
	pButton->SetFunction([=]() {int val = m_BangOffsetX->GetIntValue(); m_BangOffsetX->SetNumValue(val - 1);  });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_down.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 180.f, 420.f));
	pTextUI->SetText(L"y :");

	pPanel->AddChild(pTextUI);

	m_BangOffsetY = new CTextBoxUI();
	m_BangOffsetY->SetPos(Vec2(tempX + 210.f, 420.f));
	m_BangOffsetY->SetScale(Vec2(40.f, 40.f));
	m_BangOffsetY->SetInteger(true);

	pPanel->AddChild(m_BangOffsetY);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 220.f, 398.f));
	pButton->SetFunction([=]() {int val = m_BangOffsetY->GetIntValue(); m_BangOffsetY->SetNumValue(val + 1); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_up.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 220.f, 462.f));
	pButton->SetFunction([=]() {int val = m_BangOffsetY->GetIntValue(); m_BangOffsetY->SetNumValue(val - 1); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_down.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 500.f));
	pTextUI->SetText(L"Duration : ");

	pPanel->AddChild(pTextUI);

	m_BangDuration = new CTextBoxUI();
	m_BangDuration->SetPos(Vec2(tempX + 130.f, 500.f));
	m_BangDuration->SetScale(Vec2(120.f, 20.f));
	m_BangDuration->SetFloat(true);

	pPanel->AddChild(m_BangDuration);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 40.f, 640.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\generate.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {

		// 이름이 없으면 오류
		if (wcscmp(m_BangName->GetValue().c_str(), L"") == 0)
		{
			MessageBox(CEngine::Get()->GetMainHwnd(), L"애니메이션 이름을 작성해주세요.", L"애니메이션 생성 오류", MB_OK);
			return;
		}

		// 이미 동일한 이름이 있으면 오류
		if (CAssetMgr::Get()->FindAsset<CAnimation>(m_BangName->GetValue()))
		{
			MessageBox(CEngine::Get()->GetMainHwnd(), L"이미 동일한 이름의 애니메이션이 존재합니다.\n 애니메이션 이름을 수정해주세요.", L"애니메이션 생성 오류", MB_OK);
			return;
		}

		// 새 애니메이션을 생성
		CAnimation* pAnim = new CAnimation;

		// 애셋매니저에 등록
		CAssetMgr::Get()->AddAsset<CAnimation>(m_BangName->GetValue(), pAnim);

		// AnimUI Bang에 등록
		m_AnimEditorUI->SetBang(pAnim);

		// 애니메이션 정보를 로드
		LoadBangVariables();

		// 애니메이션이 생성되었음을 알림
		MessageBox(CEngine::Get()->GetMainHwnd(), L"애니메이션이 생성되었습니다.", L"애니메이션 생성", MB_OK);

		});

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 100.f, 640.f));
	pButton->SetFunction([=]() {
		m_AnimEditorUI->GetBang()->SetName(m_BangName->GetValue());
		SaveBangAnimation(L"\\animation\\" + m_BangName->GetValue() + L".anim");
		m_OriBangFrm = m_AnimEditorUI->GetBang()->GetAllFrm();

		// 애니메이션이 저장되었음을 알림
		MessageBox(CEngine::Get()->GetMainHwnd(), L"애니메이션이 저장되었습니다.", L"애니메이션 저장 완료", MB_OK);
	});
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\save.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 160.f, 640.f));
	pButton->SetScale(Vec2(80.f, 30.f));
	pButton->SetFunction([=]() 
		{
			OPENFILENAME OFN{};
			wchar_t szFilePath[255]{};
			wchar_t filter[] = L"애니메이션\0*.anim\0모든 파일\0*.*\0";

			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = CEngine::Get()->GetMainHwnd();	// 모달 채택할 윈도우를 지정해줌
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = szFilePath;
			OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			OFN.nMaxFile = 255;	// 파일 문자열 최대 길이
			wstring strAnimPath = CPathMgr::Get()->GetContentPath() + L"\\animation";
			OFN.lpstrInitialDir = strAnimPath.c_str(); // 창을 켰을 때 디폴트 경로

			if (GetOpenFileName(&OFN)) {
				wstring strExtension = CPathMgr::Get()->GetPathExtension(szFilePath);

				if (wcscmp(strExtension.c_str(), L".anim") == 0)
				{
					// 편집중이던 애니메이션을 원래 상태로 되돌림
					if (m_AnimEditorUI->GetBang())
						m_AnimEditorUI->GetBang()->SetAllFrm(m_OriBangFrm);

					// 선택한 애니메이션을 불러옴
					SetBangAnim(CAssetMgr::Get()->LoadAsset<CAnimation>(CPathMgr::Get()->GetNaiveFileName(szFilePath), CPathMgr::Get()->GetRelativePath(szFilePath)));

					// 불러온 애니메이션 초기값 세팅
					LoadBangVariables();

					// 애니메이션의 원래 상태를 저장해둔다
					m_OriBangFrm = m_AnimEditorUI->GetBang()->GetAllFrm();
				}
			}
		});
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\load.png"));
	pButton->SetTexOffset(Vec2(25.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	// 몸 애니메이션, 프레임 정보
	tempX = 930.f;
	tempY = 120.f;

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX - 20.f, tempY));
	pTextUI->SetText(L"애니메이션 정보");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, tempY + 40.f));
	pTextUI->SetText(L"애니메이션 이름");

	pPanel->AddChild(pTextUI);

	m_BodyName = new CTextBoxUI();
	m_BodyName->SetPos(Vec2(tempX + 10.f, tempY + 80.f));
	m_BodyName->SetScale(Vec2(230.f, 20.f));

	pPanel->AddChild(m_BodyName);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 250.f, tempY + 80.f));
	pTextUI->SetText(L".anim");

	pPanel->AddChild(pTextUI);

	m_BodyFrmCntTxt = new CTextUI();
	m_BodyFrmCntTxt->SetPos(Vec2(tempX, tempY + 140.f));
	m_BodyFrmCntTxt->SetText(L"프레임 수 : 0");

	pPanel->AddChild(m_BodyFrmCntTxt);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 170.f, tempY + 140.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\add.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {

		// 현재 편집중인 애니메이션이 없으면 오류
		if (!m_AnimEditorUI->GetBody())
		{
			MessageBox(CEngine::Get()->GetMainHwnd(), L"편집중인 애니메이션이 없습니다. 새 애니메이션을 생성하거나 기존 애니메이션을 불러오세요.", L"애니메이션 편집 오류", MB_OK);
			return;
		}

		OPENFILENAME OFN{};
		wchar_t szFilePath[4096]{};
		wchar_t filter[] = L"이미지\0*.png\0모든 파일\0*.*\0";

		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = CEngine::Get()->GetMainHwnd();	// 모달 채택할 윈도우를 지정해줌
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = szFilePath;
		OFN.Flags = OFN_ALLOWMULTISELECT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		OFN.nMaxFile = 4096;	// 파일 문자열 최대 길이
		wstring strAnimPath = CPathMgr::Get()->GetContentPath() + L"\\texture";
		OFN.lpstrInitialDir = strAnimPath.c_str(); // 창을 켰을 때 디폴트 경로

		if (GetOpenFileName(&OFN)) {

			// 선택한 파일 이름을 저장하는 벡터
			vector<wstring> vecFileNames;

			// 문자열 포인터
			wchar_t* p = OFN.lpstrFile;

			// 파일이 존재하는 디렉토리를 받음 (파일 이름과 확장자를 제외한 파일의 위치, \\로 끝남)
			wstring FileDirectory = CPathMgr::Get()->GetFileDirectory(p);

			// 첫번째 파일 이름을 가리키는 곳으로 포인터를 이동
			p += FileDirectory.length();
			if (*p == ' ')
				++p;


			while (*p != '\0')
			{
				wstring FileNames = p;
				wstring FileName = FileNames.substr(0, FileNames.find(L".png") + 4);

				vecFileNames.push_back(FileName);
				p += FileName.length() + 1;
			}

			for (const wstring& fileName : vecFileNames)
			{
				wstring fileDir = FileDirectory + fileName;

				wstring strExtension = CPathMgr::Get()->GetPathExtension(fileDir);

				if (wcscmp(strExtension.c_str(), L".png") == 0)
				{
					// 선택한 이미지를 텍스쳐로 불러옴
					CTexture* pTex = CAssetMgr::Get()->LoadAsset<CTexture>(CPathMgr::Get()->GetRelativePath(fileDir));
					pTex->Stretch(Vec2(BODY_SCALE, BODY_SCALE));

					// 새 프레임을 가장 마지막에 추가함
					tAnimFrm frm{};
					frm.Duration = DEFAULT_FRM_DURATION;
					frm.Offset = Vec2(0.f, 0.f);
					frm.Texture = pTex;

					m_AnimEditorUI->AddBodyFrm(frm);

					// 불러온 애니메이션 초기값 세팅
					LoadBodyVariables();
				}
			}
		}
		});

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 200.f, tempY + 140.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\remove.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {

		// 현재 편집중인 애니메이션이 없으면 오류
		if (!m_AnimEditorUI->GetBody())
		{
			MessageBox(CEngine::Get()->GetMainHwnd(), L"편집중인 애니메이션이 없습니다.\n새 애니메이션을 생성하거나 기존 애니메이션을 불러오세요.", L"애니메이션 편집 오류", MB_OK);
			return;
		}
		
		// 현재 보고 있는 프레임을 제거한다
		m_AnimEditorUI->EraseBodyFrm(m_BodyFrm);

		});

	pPanel->AddChild(pButton);

	

	// Body 프레임 정보
	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX - 20.f, 360.f));
	pTextUI->SetText(L"프레임 정보");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 420.f));
	pTextUI->SetText(L"Offset");

	pPanel->AddChild(pTextUI);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 100.f, 420.f));
	pTextUI->SetText(L"x :");

	pPanel->AddChild(pTextUI);

	m_BodyOffsetX = new CTextBoxUI();
	m_BodyOffsetX->SetPos(Vec2(tempX + 130.f, 420.f));
	m_BodyOffsetX->SetScale(Vec2(40.f, 40.f));
	m_BodyOffsetX->SetInteger(true);

	pPanel->AddChild(m_BodyOffsetX);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 140.f, 398.f));
	pButton->SetFunction([=]() {int val = m_BodyOffsetX->GetIntValue(); m_BodyOffsetX->SetNumValue(val + 1); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_up.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 140.f, 462.f));
	pButton->SetFunction([=]() {int val = m_BodyOffsetX->GetIntValue(); m_BodyOffsetX->SetNumValue(val - 1); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_down.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX + 180.f, 420.f));
	pTextUI->SetText(L"y :");

	pPanel->AddChild(pTextUI);

	m_BodyOffsetY = new CTextBoxUI();
	m_BodyOffsetY->SetPos(Vec2(tempX + 210.f, 420.f));
	m_BodyOffsetY->SetScale(Vec2(40.f, 40.f));
	m_BodyOffsetY->SetInteger(true);

	pPanel->AddChild(m_BodyOffsetY);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 220.f, 398.f));
	pButton->SetFunction([=]() {int val = m_BodyOffsetY->GetIntValue(); m_BodyOffsetY->SetNumValue(val + 1); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_up.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 220.f, 462.f));
	pButton->SetFunction([=]() {int val = m_BodyOffsetY->GetIntValue(); m_BodyOffsetY->SetNumValue(val - 1); });
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\arrow_down.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);

	pPanel->AddChild(pButton);

	pTextUI = new CTextUI();
	pTextUI->SetPos(Vec2(tempX, 500.f));
	pTextUI->SetText(L"Duration : ");

	pPanel->AddChild(pTextUI);

	m_BodyDuration = new CTextBoxUI();
	m_BodyDuration->SetPos(Vec2(tempX + 130.f, 500.f));
	m_BodyDuration->SetScale(Vec2(120.f, 20.f));
	m_BodyDuration->SetFloat(true);

	pPanel->AddChild(m_BodyDuration);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 40.f, 640.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\generate.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {

		// 이름이 없으면 오류
		if (wcscmp(m_BodyName->GetValue().c_str(), L"") == 0)
		{
			MessageBox(CEngine::Get()->GetMainHwnd(), L"애니메이션 이름을 작성해주세요.", L"애니메이션 생성 오류", MB_OK);
			return;
		}

		// 이미 동일한 이름이 있으면 오류
		if (CAssetMgr::Get()->FindAsset<CAnimation>(m_BodyName->GetValue()))
		{
			MessageBox(CEngine::Get()->GetMainHwnd(), L"이미 동일한 이름의 애니메이션이 존재합니다.\n 애니메이션 이름을 수정해주세요.", L"애니메이션 생성 오류", MB_OK);
			return;
		}

		// 새 애니메이션을 생성
		CAnimation* pAnim = new CAnimation;

		// 애셋매니저에 등록
		CAssetMgr::Get()->AddAsset<CAnimation>(m_BodyName->GetValue(), pAnim);

		// AnimUI Bang에 등록
		m_AnimEditorUI->SetBody(pAnim);

		// 애니메이션 정보를 로드
		LoadBodyVariables();

		// 애니메이션이 생성되었음을 알림
		MessageBox(CEngine::Get()->GetMainHwnd(), L"애니메이션이 생성되었습니다.", L"애니메이션 생성", MB_OK);

		});

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 100.f, 640.f));
	pButton->SetScale(Vec2(50.f, 30.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\save.png"));
	pButton->SetTexOffset(Vec2(10.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {
		m_AnimEditorUI->GetBody()->SetName(m_BodyName->GetValue());
		SaveBodyAnimation(L"\\animation\\" + m_BodyName->GetValue() + L".anim");
		m_OriBodyFrm = m_AnimEditorUI->GetBody()->GetAllFrm();

		// 애니메이션이 저장되었음을 알림
		MessageBox(CEngine::Get()->GetMainHwnd(), L"애니메이션이 저장되었습니다.", L"애니메이션 저장 완료", MB_OK);
	});

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(tempX + 160.f, 640.f));
	pButton->SetScale(Vec2(80.f, 30.f));
	pButton->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\load.png"));
	pButton->SetTexOffset(Vec2(25.f, 10.f));
	pButton->SetFix(true);
	pButton->SetFunction([=]() {

		// 파일 탐색기에서 불러올 파일 선택
		OPENFILENAME OFN{};
		wchar_t szFilePath[255]{};
		wchar_t filter[] = L"애니메이션\0*.anim\0모든 파일\0*.*\0";

		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = CEngine::Get()->GetMainHwnd();	// 모달 채택할 윈도우를 지정해줌
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = szFilePath;
		OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		OFN.nMaxFile = 255;	// 파일 문자열 최대 길이
		wstring strAnimPath = CPathMgr::Get()->GetContentPath() + L"\\animation";
		OFN.lpstrInitialDir = strAnimPath.c_str(); // 창을 켰을 때 디폴트 경로

		if (GetOpenFileName(&OFN)) {

			wstring strExtension = CPathMgr::Get()->GetPathExtension(szFilePath);

			if (wcscmp(strExtension.c_str(), L".anim") == 0)
			{
				// 편집중이던 애니메이션을 원래 상태로 되돌림
				if (m_AnimEditorUI->GetBody())
					m_AnimEditorUI->GetBody()->SetAllFrm(m_OriBodyFrm);

				// 선택한 애니메이션을 불러옴
				SetBodyAnim(CAssetMgr::Get()->LoadAsset<CAnimation>(CPathMgr::Get()->GetNaiveFileName(szFilePath), CPathMgr::Get()->GetRelativePath(szFilePath)));

				// 불러온 애니메이션 초기값 세팅
				LoadBodyVariables();

				// 애니메이션의 원래 상태를 저장해둔다
				m_OriBodyFrm = m_AnimEditorUI->GetBody()->GetAllFrm();
			}
		}

		
	});

	pPanel->AddChild(pButton);
}

void CLevel_AnimEditor::Tick_Derived()
{
	// 에디터 화면으로 이동
	if (KEY_TAP(KEY::ESC))
	{
		Change_Level(LEVEL_TYPE::EDITOR);
	}

	// 값의 변화를 감지해서 화면에 표시되는 정보를 실시간 업데이트
	if (m_AnimEditorUI->GetBang())
	{
		if (m_BangFrmCnt != m_AnimEditorUI->GetBangFrmCnt())
		{
			m_BangFrmCnt = m_AnimEditorUI->GetBangFrmCnt();
			m_BangFrmCntTxt->SetText(L"프레임 수 : " + std::to_wstring(m_BangFrmCnt));
		}

		if (m_BangFrm != m_AnimEditorUI->GetBangFrm())
		{
			m_BangFrm = m_AnimEditorUI->GetBangFrm();
			LoadBangVariables();
		}
		else if (m_BangFrm < m_BangFrmCnt && m_BangFrmCnt > 0)
		{
			tAnimFrm& BangAnimFrm = m_AnimEditorUI->GetBang()->GetFrm(m_BangFrm);
			BangAnimFrm.Offset.x = (float)m_BangOffsetX->GetIntValue();
			BangAnimFrm.Offset.y = (float)m_BangOffsetY->GetIntValue();
			BangAnimFrm.Duration = m_BangDuration->GetFloatValue();
		}

	}

	if (m_AnimEditorUI->GetBody())
	{
		if (m_BodyFrmCnt != m_AnimEditorUI->GetBodyFrmCnt())
		{
			m_BodyFrmCnt = m_AnimEditorUI->GetBodyFrmCnt();
			m_BodyFrmCntTxt->SetText(L"프레임 수 : " + std::to_wstring(m_BodyFrmCnt));
		}

		if (m_BodyFrm != m_AnimEditorUI->GetBodyFrm())
		{
			m_BodyFrm = m_AnimEditorUI->GetBodyFrm();
			LoadBodyVariables();
		}
		else if (m_BodyFrm < m_BodyFrmCnt && m_BodyFrmCnt > 0)
		{
			tAnimFrm& BodyAnimFrm = m_AnimEditorUI->GetBody()->GetFrm(m_BodyFrm);
			BodyAnimFrm.Offset.x = (float)m_BodyOffsetX->GetIntValue();
			BodyAnimFrm.Offset.y = (float)m_BodyOffsetY->GetIntValue();
			BodyAnimFrm.Duration = m_BodyDuration->GetFloatValue();
		}


	}
}

void CLevel_AnimEditor::LoadBangVariables()
{
	// 불러온 애니메이션 초기값 세팅
	m_BangFrm = m_AnimEditorUI->GetBangFrm();
	m_BangFrmTxt->SetText(L"Frame " + std::to_wstring(m_BangFrm));
	m_BangFrmCnt = m_AnimEditorUI->GetBangFrmCnt();
	m_BangFrmCntTxt->SetText(L"프레임 수 : " + std::to_wstring(m_BangFrmCnt));

	m_BangName->SetText(m_AnimEditorUI->GetBang()->GetName());

	if (m_BangFrmCnt > 0)
	{
		tAnimFrm& BangAnimFrm = m_AnimEditorUI->GetBang()->GetFrm(m_BangFrm);
		m_BangOffsetX->SetNumValue((int)BangAnimFrm.Offset.x);
		m_BangOffsetY->SetNumValue((int)BangAnimFrm.Offset.y);
		m_BangDuration->SetNumValue(BangAnimFrm.Duration);
	}
}

void CLevel_AnimEditor::LoadBodyVariables()
{
	// 불러온 애니메이션 초기값 세팅
	m_BodyFrm = m_AnimEditorUI->GetBodyFrm();
	m_BodyFrmTxt->SetText(L"Frame " + std::to_wstring(m_BodyFrm));
	m_BodyFrmCnt = m_AnimEditorUI->GetBodyFrmCnt();
	m_BodyFrmCntTxt->SetText(L"프레임 수 : " + std::to_wstring(m_BodyFrmCnt));

	m_BodyName->SetText(m_AnimEditorUI->GetBody()->GetName());

	if (m_BodyFrmCnt > 0)
	{
		tAnimFrm& BodyAnimFrm = m_AnimEditorUI->GetBody()->GetFrm(m_BodyFrm);
		m_BodyOffsetX->SetNumValue((int)BodyAnimFrm.Offset.x);
		m_BodyOffsetY->SetNumValue((int)BodyAnimFrm.Offset.y);
		m_BodyDuration->SetNumValue(BodyAnimFrm.Duration);
	}
}

void CLevel_AnimEditor::SetBangAnim(CAnimation* _Anim)
{
	m_AnimEditorUI->SetBang(_Anim);
}

void CLevel_AnimEditor::SetBodyAnim(CAnimation* _Anim)
{
	m_AnimEditorUI->SetBody(_Anim);
}



void CLevel_AnimEditor::CreateBangAnimation()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();
	strContentPath += L"\\map";

	OPENFILENAME OFN{};
	wchar_t szFilePath[255]{};
	wchar_t filter[] = L"Animation\0*.anim\0모든 파일\0*.*\0";

	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = CEngine::Get()->GetMainHwnd();	// 모달 채택할 윈도우를 지정해줌
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = szFilePath;
	OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	OFN.nMaxFile = 255;	// 파일 문자열 최대 길이
	wstring strAnimPath = CPathMgr::Get()->GetContentPath() + L"\\animation";
	OFN.lpstrInitialDir = strAnimPath.c_str(); // 창을 켰을 때 디폴트 경로

	if (GetSaveFileName(&OFN))	// 확인 누르면 true
	{
		CAnimation* pAnim = new CAnimation;

		wstring strFilePath = szFilePath;

		wstring strExtension = CPathMgr::Get()->GetPathExtension(szFilePath);

		if (wcscmp(strExtension.c_str(), L".anim") != 0)
			strFilePath += L".anim";

		// 선택 경로로 애니메이션 저장
		pAnim->Save(strFilePath);

		// 파일 이름으로 애니메이션 이름 설정
		wstring strFileName = CPathMgr::Get()->GetNaiveFileName(strFilePath);
		CAssetMgr::Get()->AddAsset(strFileName, pAnim);
	}
}

void CLevel_AnimEditor::SaveBangAnimation(const wstring& _strRelativePath)
{
	m_AnimEditorUI->GetBang()->Save(_strRelativePath);
}

void CLevel_AnimEditor::LoadBangAnimation()
{
}

void CLevel_AnimEditor::CreateBodyAnimation()
{
}

void CLevel_AnimEditor::SaveBodyAnimation(const wstring& _strRelativePath)
{
	m_AnimEditorUI->GetBody()->Save(_strRelativePath);
}

void CLevel_AnimEditor::LoadBodyAnimation()
{
}
