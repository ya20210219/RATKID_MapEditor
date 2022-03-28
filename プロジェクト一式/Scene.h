#pragma once

#include <list>		//���X�g�\��
#include <vector>
#include <typeinfo>
#include "GameObject.h"

#define LAYER_NUM (3)

enum LAYER_NUMBER
{
	SYSTEM,
	OBJ3D,
	OBJ2D,

	LAYER_MAX
};

enum SCENE_NAME
{
	SCENE_TITLE,
	SCENE_GAMESCENE,
	SCENE_RESULT,

	SCENE_MAX
};

class Scene
{
private:
	int m_Score;
	SCENE_NAME m_SceneName;
protected:
	std::list<GameObject*> m_GameObject[LAYER_NUM];	//STL�̃��X�g�\��

public:
	Scene(){}
	virtual ~Scene(){}

	virtual void Init() = 0;	//	�������z�֐�

	virtual void UnInit()
	{
		for (int i = 0; i < LAYER_NUM; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->UnInit();	//�|�����[�t�B�Y��(���Ԑ��F�C���X�^���X�̊֐����Ăяo�����)
				delete object;
			}

			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < LAYER_NUM; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();	//�|�����[�t�B�Y��(���Ԑ��F�C���X�^���X�̊֐����Ăяo�����)
			}

			m_GameObject[i].remove_if([](GameObject* object) { return object->Destroy(); });
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < LAYER_NUM; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();	//�|�����[�t�B�Y��(���Ԑ��F�C���X�^���X�̊֐����Ăяo�����)
			}
		}
	}

	template<typename T>
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		m_GameObject[layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template<typename T>
	T* GetGameObject(int layer)	//1�����̃I�u�W�F�N�g�擾
	{
		for (GameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T))	//�^�𒲂ׂ�(RTTI���I�^���)
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	template<typename T>	//�e���v���[�g�֐�
	std::vector<T*> GetGameObjects(int layer)	//�����̃I�u�W�F�N�g�擾
	{
		std::vector<T*> objects;
		for (GameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	void SetScore(int score)
	{
		m_Score = score;
	}

	int GetScore()
	{
		return m_Score;
	}

	void AddScore(int value)
	{
		m_Score = m_Score + value;
	}
	   
	void SetSceneName(SCENE_NAME name)
	{
		m_SceneName = name;
	}

	SCENE_NAME GetSceneName()
	{
		return m_SceneName;
	}
};
