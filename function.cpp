#include "pch.h"
#include "function.h"
#include "CDebugMgr.h"
#include "CTaskMgr.h"

void Debug_Render(DEBUG_SHAPE _Shape, PEN_TYPE _Pen, BRUSH_TYPE _Brush, Vec2 _Pos, Vec2 _Scale, float _Duration)
{
	tDebugShapeInfo tDebug{};
	tDebug.Shape = _Shape;
	tDebug.Pen = _Pen;
	tDebug.Brush = _Brush;
	tDebug.Position = _Pos;
	tDebug.Scale = _Scale;
	tDebug.Duration = _Duration;
	tDebug.AccTime = 0.f;

	CDebugMgr::Get()->AddDebugShape(tDebug);
}

void ChangeLevel(LEVEL_TYPE _Type)
{
	tTask task{};
	task.TaskType = TASK_TYPE::CHANGE_LEVEL;
	task.wParam = (DWORD_PTR)_Type;

	CTaskMgr::Get()->AddTask(task);
}
