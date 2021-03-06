#pragma once

#include "GameObject.h"

#define WIRE_UI_FILE "asset/texture/TargetMarker.png"

class WireUI : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;	//リリースするタイミングで中身が無いことを確認してる
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;

public:

	void Init();
	void UnInit();
	void Update();
	void Draw();
	void SetScreenPos();
};