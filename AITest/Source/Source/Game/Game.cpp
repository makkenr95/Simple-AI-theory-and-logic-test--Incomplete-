#include "stdafx.h"
#include <tga2d/Engine.h>
#include "Game.h"

#include "tga2d/math/matrix44.h"
#include <tga2d/error/error_manager.h>
#include "tga2d/d3d/direct_3d.h"
#include "tga2d/engine.h"

using namespace std::placeholders;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;

#ifdef _DEBUG
#pragma comment(lib,"TGA2D_Debug.lib")
std::wstring BUILD_NAME = L"Debug";
#endif // DEBUG
#ifdef _RELEASE
#pragma comment(lib,"TGA2D_Release.lib")
std::wstring BUILD_NAME = L"Release";
#endif // DEBUG
#ifdef _RETAIL
#pragma comment(lib,"TGA2D_Retail.lib")
std::wstring BUILD_NAME = L"Retail";
#endif // DEBUG

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

CGame::CGame()
{
}


CGame::~CGame()
{
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	lParam;
	wParam;
	hWnd;
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	}

	return 0;
}



bool CGame::Init(const std::wstring& aVersion, HWND /*aHWND*/)
{
    Tga2D::SEngineCreateParameters createParameters;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
	createParameters.myWinProcCallback = std::bind(&CGame::WinProc, this, _1, _2, _3, _4);
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myApplicationName = L"TGA 2D " + BUILD_NAME + L"[" + aVersion + L"] ";
	createParameters.myWindowWidth = SCREEN_WIDTH;
	createParameters.myWindowHeight = SCREEN_HEIGHT;
	createParameters.myRenderWidth = SCREEN_WIDTH;
	createParameters.myRenderHeight = SCREEN_HEIGHT;
	createParameters.myTargetWidth = SCREEN_WIDTH;
	createParameters.myTargetHeight = SCREEN_HEIGHT;
	createParameters.myActivateDebugSystems = Tga2D::eDebugFeature_Fps |
		Tga2D::eDebugFeature_Mem |
		Tga2D::eDebugFeature_Drawcalls |
		Tga2D::eDebugFeature_Cpu |
		Tga2D::eDebugFeature_Filewatcher |
		Tga2D::eDebugFeature_OptimiceWarnings;
			
	if (!Tga2D::CEngine::Start(createParameters))
    {
        ERROR_PRINT( "Fatal error! Engine could not start!" );
		system("pause");
		return false;
    }

	// End of program
	return true;
}

void CGame::InitCallBack()
{
    myGameWorld.Init();
}

void CGame::UpdateCallBack()
{
	myGameWorld.Update(Tga2D::CEngine::GetInstance()->GetDeltaTime());
}
