#pragma once

class CGameObject;

enum class ButtonType
{
	BUTTON_FORWARD,
	BUTTON_BACKWARD,
	BUTTON_RIGHT,
	BUTTON_LEFT
};

class CBaseCommand
{
public:
	virtual ~CBaseCommand() {}
	virtual void execute(CGameObject& gameObject) = 0;
};

class CForwardCommand : public CBaseCommand
{
	virtual ~CForwardCommand() {}
	virtual void execute(CGameObject& gameObject) override;
};

class CBackwardCommand : public CBaseCommand
{
	virtual ~CBackwardCommand() {}
	virtual void execute(CGameObject& gameObject) override;
};

class CRightCommand : public CBaseCommand
{
	virtual ~CRightCommand() {}
	virtual void execute(CGameObject& gameObject) override;
};

class CLeftCommand : public CBaseCommand
{
	virtual ~CLeftCommand() {}
	virtual void execute(CGameObject& gameObject) override;
};

class CInputHandler 
{
public:
	UCHAR pKeysBuffer[256];

	CInputHandler() 
	{
		key_map[ButtonType::BUTTON_FORWARD] = VK_UP;
		key_map[ButtonType::BUTTON_BACKWARD] = VK_DOWN;
		key_map[ButtonType::BUTTON_RIGHT] = VK_RIGHT;
		key_map[ButtonType::BUTTON_LEFT] = VK_LEFT;

		button_forward = new CForwardCommand();
		button_backward = new CBackwardCommand();
		button_right = new CRightCommand();
		button_left = new CLeftCommand();
	}

	~CInputHandler()
	{
	}

	bool IsPressed(ButtonType buttonType);
	void HandleInput(CGameObject& gameObject);

	void ChangeKey();

private:
	std::unordered_map<ButtonType, WORD> key_map;

	CBaseCommand* button_forward;
	CBaseCommand* button_backward;
	CBaseCommand* button_right;
	CBaseCommand* button_left;
};
