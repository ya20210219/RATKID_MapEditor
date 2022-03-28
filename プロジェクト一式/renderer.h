#pragma once

#define COLOR_RED (D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f))
#define COLOR_GREEN (D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f))
#define COLOR_BLUE (D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f))
#define COLOR_WHITE (D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f))
#define COLOR_GOLD (D3DXVECTOR4(0.94f, 0.68f, 0.0f, 1.0f))
#define COLOR_GRAY (D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f))

struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
};



struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];
};



struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
};



class Renderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;	//�v���p�e�B�A�����o�ϐ�

	static ID3D11Device*           m_Device;
	static ID3D11DeviceContext*    m_DeviceContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11Buffer*			m_CameraBuffer;


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;




public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	static void SetCameraPosition(D3DXVECTOR3 CameraPosition);

	static ID3D11Device* GetDevice( void ){ return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }
	static ID3D11RenderTargetView* GetRenderTargetView(void) { return m_RenderTargetView; }	static IDXGISwapChain* GetSwapChain(void) { return m_SwapChain; }

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);
};
