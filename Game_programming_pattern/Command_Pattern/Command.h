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
public:
	virtual ~CForwardCommand() {}
	virtual void execute(CGameObject& gameObject) override;
};

class CBackwardCommand : public CBaseCommand
{
public:
	virtual ~CBackwardCommand() {}
	virtual void execute(CGameObject& gameObject) override;
};

class CRightCommand : public CBaseCommand
{
public:
	virtual ~CRightCommand() {}
	virtual void execute(CGameObject& gameObject) override;
};

class CLeftCommand : public CBaseCommand
{
public:
	virtual ~CLeftCommand() {}
	virtual void execute(CGameObject& gameObject) override;
};

class CBaseInputHandler
{
public:
	CBaseInputHandler()
	{
	}

	virtual ~CBaseInputHandler()
	{
	}

	bool IsPressed(ButtonType buttonType);
	virtual void HandleInput(CGameObject& gameObject) = 0;

	void ChangeKey() {};

	static UCHAR pKeysBuffer[256];

protected:
	std::unordered_map<ButtonType, WORD> m_mapButtonToKey;
};

class CPlayerInputHandler : public CBaseInputHandler
{
public:
	CPlayerInputHandler()
		: CBaseInputHandler()
	{
		m_mapButtonToKey[ButtonType::BUTTON_FORWARD] = VK_UP;
		m_mapButtonToKey[ButtonType::BUTTON_BACKWARD] = VK_DOWN;
		m_mapButtonToKey[ButtonType::BUTTON_RIGHT] = VK_RIGHT;
		m_mapButtonToKey[ButtonType::BUTTON_LEFT] = VK_LEFT;

		button_forward = make_unique<CForwardCommand>();
		button_backward = make_unique<CBackwardCommand>();
		button_right = make_unique<CRightCommand>();
		button_left = make_unique<CLeftCommand>();
	}

	virtual ~CPlayerInputHandler() {};

	virtual void HandleInput(CGameObject& gameObject) override;

private:
	std::unique_ptr<CBaseCommand> button_forward;
	std::unique_ptr<CBaseCommand> button_backward;
	std::unique_ptr<CBaseCommand> button_right;
	std::unique_ptr<CBaseCommand> button_left;
};
