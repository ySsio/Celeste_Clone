#pragma once
#include "CLevel_Editor.h"

class CAnimation;

class CLevel_MapEditor :
    public CLevel_Editor
{
private:


public:
    void SaveMap();
    void LoadMap();


public:
    CLevel_MapEditor();
    ~CLevel_MapEditor();
};

