#include "stdafx.h"
#include "Command.h"
#include "Object.h"
#include "Player.h"


void CForwardCommand::execute(CGameObject& gameObject)
{
	CPlayer* player = dynamic_cast<CPlayer*>(&gameObject);
	XMFLOAT3 shift = Vector3::Add(XMFLOAT3(0.0f, 0.0f, 0.0f), player->GetLook(), 0.25f);
	player->Move(shift, true);
}

void CBackwardCommand::execute(CGameObject& gameObject)
{
	CPlayer* player = dynamic_cast<CPlayer*>(&gameObject);
	XMFLOAT3 shift = Vector3::Add(XMFLOAT3(0.0f, 0.0f, 0.0f), player->GetLook(), -0.25f);
	player->Move(shift, true);
}

void CRightCommand::execute(CGameObject& gameObject)
{
	CPlayer* player = dynamic_cast<CPlayer*>(&gameObject);
	XMFLOAT3 shift = Vector3::Add(XMFLOAT3(0.0f, 0.0f, 0.0f), player->GetRight(), 0.25f);
	player->Move(shift, true);
}

void CLeftCommand::execute(CGameObject& gameObject)
{
	CPlayer* player = dynamic_cast<CPlayer*>(&gameObject);
	XMFLOAT3 shift = Vector3::Add(XMFLOAT3(0.0f, 0.0f, 0.0f), player->GetRight(), -0.25f);
	player->Move(shift, true);
}

bool CInputHandler::IsPressed(ButtonType buttonType)
{
	if (pKeysBuffer[key_map[buttonType]] & 0xF0)
	{
		return true;
	}
	return false;
}

void CInputHandler::HandleInput(CGameObject& gameObject)
{
	if (!GetKeyboardState(pKeysBuffer))
	{
		return;
	}

	if (IsPressed(ButtonType::BUTTON_FORWARD)) button_forward->execute(gameObject);
	if (IsPressed(ButtonType::BUTTON_BACKWARD)) button_backward->execute(gameObject);
	if (IsPressed(ButtonType::BUTTON_RIGHT)) button_right->execute(gameObject);
	if (IsPressed(ButtonType::BUTTON_LEFT)) button_left->execute(gameObject);
}

void CInputHandler::ChangeKey()
{
}