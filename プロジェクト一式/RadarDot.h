#pragma once

#include "GameObject.h"

class RadarDot : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//�����[�X����^�C�~���O�Œ��g���������Ƃ��m�F���Ă�
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;

	class Coin* m_Coin;
	bool		m_isShow;

public:
	//Polygon2D();	//����͕s�v
	//~Polygon2D();

	void Init();
	void UnInit();
	void Update();
	void Draw();

	void SetMyCoin(Coin* coin)
	{
		m_Coin = coin;
	}

	Coin* GetMyCoin()
	{
		return m_Coin;
	}

	void SetDotShow(bool enable)
	{
		m_isShow = enable;
	}
};