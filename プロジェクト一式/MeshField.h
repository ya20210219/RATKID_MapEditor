#pragma once

#include "GameObject.h"
#include <vector>

#define MAX_MAP_WIDTH	(40)
#define MAX_MAP_HEIGHT	(40)

#define ADD_HEIGHT (0.1f)

class MeshField : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//リリースするタイミングで中身が無いことを確認してる
	ID3D11Buffer*				m_IndexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	VERTEX_3D	m_Vertex[MAX_MAP_WIDTH + 1][MAX_MAP_HEIGHT + 1];
	D3DXVECTOR3	m_EVertex[MAX_MAP_WIDTH + 1][MAX_MAP_HEIGHT + 1];

	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;

	std::vector<D3DXVECTOR2> data;
	D3DXVECTOR2 m_EditMinPos;
	D3DXVECTOR2 m_EditMaXPos;
	int			EditNum[100]{-1};
	int			MaxEditNum = 0;

public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void SaveData(FILE* fp);

	float GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 pV);
	D3DXVECTOR3 RightVec(D3DXVECTOR3 pos, D3DXVECTOR3 v1);
	D3DXVECTOR3 MeshFieldWithinRange(D3DXVECTOR3 pos);

	bool CheckMeshToRay();
	void EditMeshHeight();
	void EditMeshNum();

	int GetMaxEditNum()
	{
		return MaxEditNum;
	}

	int GetEditNum(int i)
	{
		return EditNum[i];
	}

	void SetMinPos(D3DXVECTOR2 pos)
	{
		m_EditMinPos = pos;
	}

	void SetMaxPos(D3DXVECTOR2 pos)
	{
		m_EditMaXPos = pos;
	}

	D3DXVECTOR2 GetMinPos()
	{
		return m_EditMinPos;
	}

	D3DXVECTOR2 GetMaxPos()
	{
		return m_EditMaXPos;
	}

	std::vector<D3DXVECTOR2> Getdata()
	{
		return data;
	}
};