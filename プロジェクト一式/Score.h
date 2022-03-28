#pragma once

#include "GameObject.h"

#define SCORE_WIDTH (30)
#define SCORE_HEIGHT (30)
#define MAX_SCORE_TEX_WIDTH (5)
#define MAX_SCORE_TEX_HEIGHT (2)
#define MAX_SCORE_DIGIT (6)
#define ADJUSTMENT_HEIGHT (50.0f)
#define SCORE_COIN (100)

class Score : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//リリースするタイミングで中身が無いことを確認してる
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;

public:
	//Polygon2D();	//今回は不要
	//~Polygon2D();

	void Init();
	void UnInit();
	void Update();
	void Draw();
};