#include "stdafx.h"
#include "PlayerController.h"

#include "PollingStation.h"
#include "Actor.h"
#include "EventManager.h"

PlayerController::PlayerController()
{

}

Tga2D::Vector2f PlayerController::Update(const Tga2D::Vector2f& aPosition)
{
	DoMouseInput();
	return { 0, 0 };
}

void PlayerController::DoMouseInput()
{
	if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(*Tga2D::CEngine::GetInstance()->GetHWND(), &p);

		Tga2D::Vector2f normPos = { (float)p.x / (float)Tga2D::CEngine::GetInstance()->GetWindowSize().x, (float)p.y / (float)Tga2D::CEngine::GetInstance()->GetWindowSize().y };
		myTargetPosition = normPos;
	}
}
