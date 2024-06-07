#pragma once

#define SINGLE(type)	public:														   \
							static type* Get()								   \
							{														   \
								static type* inst = new type;					   \
																					   \
								return inst;										   \
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
