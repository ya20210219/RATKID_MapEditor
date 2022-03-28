#pragma once

#include "Scene.h"


class GameScene : public Scene
{
private:
	class Fade* m_Fade;
	class Audio* m_BGM;
public:
	void Init();
	void UnInit();
	void Update();
};