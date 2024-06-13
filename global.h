#pragma once

#include "resource.h"

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <queue>
using std::queue;

#include <map>
using std::map;
using std::make_pair;

#include <array>
using std::array;

#include <string>
using std::string;
using std::wstring;

#include <unordered_map>
using std::unordered_map;

#include <functional>
using std::function;


// ################   라이브러리   ###################

// AlphaBlend
#pragma comment(lib, "Msimg32.lib")	

// png 파일 
#include <objidl.h>
#include <gdiplus.h>
// 라이브러리 = cpp 부분에 해당하는 내용. 헤더파일과 링크되도록
#pragma comment(lib, "GdiPlus.lib")	
using namespace Gdiplus;

// OPENFILENAME
#include "commdlg.h"

// ##################################################


#include "define.h"
#include "struct.h"
#include "function.h"

#include "CSelectObject.h"
