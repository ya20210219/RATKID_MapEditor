#pragma once

#include "GameObject.h"
#define MAX_BLDG (3)

enum BldgType
{
	NORMAL,
	LARGE,
	HOUSE,
};

class Building : public GameObject
{
private:
	static Model* m_Model[3];
	class OBB* m_obb;
	ID3D11VertexShader*	m_VertexShader = NULL;
	ID3D11PixelShader*	m_PixelShader = NULL;
	ID3D11InputLayout*	m_VertexLayout = NULL;

	D3DXVECTOR3 m_Speed;
	D3DXVECTOR3 m_OldPosition;
	D3DXVECTOR3 m_OldRot;

	D3DXMATRIX m_EnemyMatrix;

	int m_Frame;
	float m_BlendRate;

	bool	m_isCorrection;
	bool	m_isEdit;

	BldgType m_Type;

public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

	void UpdateHeight();
	void UpdateMove();
	void CheckSlide();
	void UpdateOBB();
	void SaveData(FILE* fp);

	static void Load()
	{
		m_Model[0] = new Model();
		m_Model[0]->Load("asset\\model\\TestBldg2.obj");	//\\2個に注意「//」でもいい
		m_Model[1] = new Model();
		m_Model[1]->Load("asset\\model\\TestBldg5.obj");	//\\2個に注意「//」でもいい
		m_Model[2] = new Model();
		m_Model[2]->Load("asset\\model\\TestBldg6.obj");	//\\2個に注意「//」でもいい
	};
	static void UnLoad()
	{
		for (int i = 0; i < MAX_BLDG; i++)
		{
			m_Model[i]->Unload();
			delete m_Model[i];
		}
	};

	OBB* GetOBB()
	{
		return m_obb;
	}

	Model* GetModel(int num)
	{
		return m_Model[num];
	}

	void CreateBldg(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BldgType t);
	void SetOldPos(D3DXVECTOR3 pos)
	{
		m_OldPosition = pos;
	}

	D3DXVECTOR3 GetOldPos() { return m_OldPosition; }
	D3DXVECTOR3 GetOldRot() { return m_OldRot; }

	bool GetEdit() { return m_isEdit; }
	void SetEdit(bool enable) { m_isEdit = enable; }

	bool CheckMeshToRay();
	bool CheckFootMeshToRay(D3DXVECTOR3 dir);
	bool CheckWallMeshToRay(D3DXVECTOR3 dir);
};
