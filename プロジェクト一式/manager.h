#pragma once

#include "Scene.h"
#include "Title.h"
#include "GameScene.h"
#include "Result.h"
#include <string>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


class Manager
{
private:
	static class Scene* m_Scene;	//����class�Ƃ���Ɠǂݍ��߂�B�O���錾�Ƃ���
	static float m_Timer;
	static float m_isTimer;

public:	//���\�b�h�A�����o�֐�

	static void Init();		//����������
	static void Uninit();	//�I������
	static void Update();	//�X�V����
	static void Draw();		//�`�揈��

	static Scene* GetScene() { return m_Scene; }

	template<typename T>
	static void SetScene()
	{
		int score;
		if (m_Scene)
		{
			score = m_Scene->GetScore();
			m_Scene->UnInit();
			delete m_Scene;
		}

		T* scene = new T();
		m_Scene = scene;

		const type_info& id = typeid(*scene);

		if (typeid(Title) == id)
		{
			m_Scene->SetSceneName(SCENE_TITLE);
		}
		if (typeid(GameScene) == id)
		{
			m_Scene->SetSceneName(SCENE_GAMESCENE);
		}
		if (typeid(Result) == id)
		{
			m_Scene->SetSceneName(SCENE_RESULT);
		}
		scene->Init();
		if (m_Scene->GetSceneName() == SCENE_RESULT)
		{
			m_Scene->SetScore(score);
		}
	}

	void StartTimer(bool enable)
	{
		m_isTimer = enable;
	}
};