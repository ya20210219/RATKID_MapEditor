#pragma once

#include "GameObject.h"

class Coin : public GameObject
{
private:
	static Model* m_Model;
	class OBB* m_obb;
	class RadarDot* m_Dot;
	class Audio* m_CoinSE;
	ID3D11VertexShader*	m_VertexShader = NULL;
	ID3D11PixelShader*	m_PixelShader = NULL;
	ID3D11InputLayout*	m_VertexLayout = NULL;

	D3DXVECTOR3 m_Speed;
	D3DXVECTOR3 m_OldPosition;

	D3DXMATRIX m_EnemyMatrix;

	int m_Frame;
	float m_BlendRate;

public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

	void UpdateHeight();
	void UpdateMove();
	void UpdateOBB();
	void SaveData(FILE* fp);

	static void Load()
	{
		m_Model = new Model();
		m_Model->Load("asset\\model\\coin001.obj");	//\\2�ɒ��Ӂu//�v�ł�����
	};
	static void UnLoad()
	{
		m_Model->Unload();
		delete m_Model;
	};

	OBB* GetOBB()
	{
		return m_obb;
	}

	Model* GetModel()
	{
		return m_Model;
	}

	void SetDot(RadarDot* dot)
	{
		m_Dot = dot;
	}

	RadarDot* GetDot()
	{
		return m_Dot;
	}
};
