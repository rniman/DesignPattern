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

void CCameraRotateYCommand::execute(CGameObject& gameObject)
{
	// ������ â�� �ϳ���� �ʿ����.
	//if (GetCapture() != CBaseInputHandler::GetHWND())
	//	return;

	float deltaX, deltaY;

	POINT ptCursorPos;
	SetCursor(nullptr);
	GetCursorPos(&ptCursorPos);
	deltaX = (float)(ptCursorPos.x - CBaseInputHandler::m_sptOldCursorPos.x) / 3.0f;
	deltaY = (float)(ptCursorPos.y - CBaseInputHandler::m_sptOldCursorPos.y) / 3.0f;
	SetCursorPos(CBaseInputHandler::m_sptOldCursorPos.x, CBaseInputHandler::m_sptOldCursorPos.y);

	CPlayer* player = dynamic_cast<CPlayer*>(&gameObject);
	player->Rotate(deltaY, deltaX, 0.0f);
}

UCHAR CBaseInputHandler::m_spKeysBuffer[] = {};
POINT CBaseInputHandler::m_sptOldCursorPos = POINT(0,0);
HWND CBaseInputHandler::m_shWnd;

bool CBaseInputHandler::IsPressed(ButtonType buttonType)
{
	if (CBaseInputHandler::m_spKeysBuffer[m_mapButtonToKey[buttonType]] & 0xF0)
	{
		return true;
	}
	return false;
}



void CPlayerInputHandler::HandleInput(CGameObject& gameObject)
{
	if (IsPressed(ButtonType::BUTTON_MOVE_FORWARD)) button_forward->execute(gameObject);
	if (IsPressed(ButtonType::BUTTON_MOVE_BACKWARD)) button_backward->execute(gameObject);
	if (IsPressed(ButtonType::BUTTON_MOVE_RIGHT)) button_right->execute(gameObject);
	if (IsPressed(ButtonType::BUTTON_MOVE_LEFT)) button_left->execute(gameObject);
	if (IsPressed(ButtonType::BUTTON_CAMERA_ROTATE_Y)) button_camera_rotate_y->execute(gameObject);
}


