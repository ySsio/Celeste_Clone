#pragma once

#include "resource.h"

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
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


// ################   ���̺귯��   ###################

// AlphaBlend
#pragma comment(lib, "Msimg32.lib")	

// png ���� 
#include <objidl.h>
#include <gdiplus.h>
// ���̺귯�� = cpp �κп� �ش��ϴ� ����. ������ϰ� ��ũ�ǵ���
#pragma comment(lib, "GdiPlus.lib")	
using namespace Gdiplus;

// OPENFILENAME
#include "commdlg.h"

// ##################################################


#include "define.h"
#include "struct.h"
#include "function.h"

#include "CSelectObject.h"
