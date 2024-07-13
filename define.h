#pragma once

#define SINGLE(type)	public:														   \
							static type* Get()								   \
							{														   \
								static type inst{};					   \
																					   \
								return &inst;										   \
							}														   \
																					   \
						public:														   \
							type(const type& _other) = delete;				   \
							type& operator = (const type& _other) = delete;	   \
																					   \
							type(type&& _other) = delete;						   \
							type& operator = (type&& _other) = delete;		   \
																					   \
						private:													   \
							type();											   \
																					   \
						public:														   \
							~type(); 	


#define GET_KEY(keyType)			CKeyMgr::Get()->GetKeyState(keyType)

#define KEY_TAP(keyType)			GET_KEY(keyType)==KEY_STATE::TAP
#define KEY_PRESSED(keyType)		GET_KEY(keyType)==KEY_STATE::PRESSED
#define KEY_RELEASED(keyType)		GET_KEY(keyType)==KEY_STATE::RELEASED
#define KEY_NONE(keyType)			GET_KEY(keyType)==KEY_STATE::NONE

#define DT		CTimeMgr::Get()->GetDT()
#define fDT		CTimeMgr::Get()->GetfDT()

#define MainDC	CEngine::Get()->GetMainDC()
#define BackDC	CEngine::Get()->GetBackDC()

//#ifdef _DEBUG
//	#ifndef DBG_NEW
//		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//		#define new DBG_NEW
//	#endif
//#endif

#define SELECT_PEN(DC, PEN)		CSelectObject SelectPen(DC,PEN)
#define SELECT_BRUSH(DC, BRUSH) CSelectObject SelectBrush(DC,BRUSH)


#define DEBUG_LOG(_Level, _strLog)	wchar_t strLine[5];																		  \
									wsprintf(strLine, L"%d", __LINE__);															  \
									tLog log{};																				  \
									log.Level = _Level;																		  \
									string str(__FUNCTION__);																  \
									log.strLog = wstring(str.begin(), str.end()) + L"  Line " + strLine + L" : " _strLog;		  \
									log.Time = 0.f;																			  \
									CLogMgr::Get()->AddLog(log)	

#define ALPHA_FULL	0xff000000
#define	ALPHA_HALF	0x80000000
//RGB(249,149,221)
#define PINK_BANG	0x00dd95f9
//RGB(172,50,50)
#define RED_BANG	0x003232ac
//RGB(95,205,228)
#define BLUE_BANG	0x00e4cd5f

#define PI			3.14159f

#define RENDER_POS(POS) GetRenderPosFromCam(POS)


#define DEFAULT_FRM_DURATION 0.07f


#define BANG_SCALE	50.f
#define BODY_SCALE	160.f
#define TILE_SCALE	40.f

#define ROOM_MOVE_DURATION 0.3f


// RigidBody Variables
#define PLAYER_MAX_SPEED	800.f
#define	PLAYER_RUN_SPEED	400.f
#define PLAYER_JUMP_SPEED	800.f
#define PLAYER_CLIMB_SPEED	300.f
#define PLAYER_SLIDE_SPEED	500.f
#define PLAYER_BOUNCE_SPEED	1500.f

#define ZIP_MAX_SPEED		3000.f
#define ZIP_RETURN_SPEED	300.f

#define DASH_TIME			0.25f


#define GRAVITY_COEF		1.5f
#define GRAVITY_COEF_JUMP	1.f

#define FRICTION		Vec2(9600.f,9600.f)
#define FRICTION_DASH	Vec2(1400.f,2800.f)
#define FRICTION_DEAD	Vec2(800.f,800.f)

