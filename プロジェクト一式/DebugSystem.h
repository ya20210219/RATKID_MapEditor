#pragma once
#include "Input.h"
#include "GameObject.h"

class DebugSystem : public GameObject
{
private:
	bool m_DebugUse;
	bool m_EditParameter;

public:
	void Init();
	void Update();
	void UnInit();
	void Draw();

	bool GetDebug() { return m_DebugUse; }
	bool GetEditP() { return m_EditParameter; }
	void SetDebug(bool use)
	{
		m_DebugUse = use;
	}
	void SetEditP(bool use)
	{
		m_EditParameter = use;
	}
};
