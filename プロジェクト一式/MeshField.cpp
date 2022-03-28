#include "main.h"
#include"renderer.h"
#include "MeshField.h"
#include "Calculation.h"
#include "manager.h"
#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "WireTarget.h"
#include "DebugSystem.h"
#include <vector> 
#include <DirectXMath.h>
/*
float g_FieldHeight[MAX_MAP_WIDTH + 1][MAX_MAP_HEIGHT + 1] =
{
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 5.0f,  5.0f , 5.0f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 5.0f,  5.0f , 5.0f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 5.0f,  5.0f , 5.0f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 5.0f,  5.0f , 5.0f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 5.0f,  5.0f , 5.0f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 5.0f,  5.0f , 5.0f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 5.0f,  5.0f , 5.0f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,},
	{0.0f, 1.0f, 2.0f, 4.0f, 7.5f, 3.0f, 1.5f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,}
};

//仮の平坦MAP
float g_FieldHeight1[MAX_MAP_WIDTH + 1][MAX_MAP_HEIGHT + 1] =
{
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,},
	{8.0f, 8.0f, 8.0f, 8.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,}
};
*/
void MeshField::Init()
{
	//頂点バッファ生成
	{
		for (int x = 0; x <= MAX_MAP_WIDTH; x++)
		{
			for (int z = 0; z <= MAX_MAP_HEIGHT; z++)
			{
				m_Vertex[x][z].Position = D3DXVECTOR3((x - (MAX_MAP_WIDTH / 2)) * 5.0f, 0.0f, (z - (MAX_MAP_HEIGHT / 2)) * -5.0f);	//平坦な床
				/*if (z < 10)
				{
					m_Vertex[x][z].Position.y = 15.0f;
				}
				if (z >= 10)
				{
					if (x < MAX_MAP_WIDTH / 2)
					{
						m_Vertex[x][z].Position.y = 15.0f - ((z - 10) * 2);
					}
					if (x < MAX_MAP_WIDTH / 2)
					{
						m_Vertex[x][z].Position.y = 15.0f - (z - 10);
					}
					if ((z - 10) > 15)
					{
						m_Vertex[x][z].Position.y = 0.0f;
					}
				}*/
				//m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, sinf(x * 0.5f) * 4.0f, (z - 10) * -5.0f);	//波打つ床
				//m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, sinf(x) * sinf(z) * 2.0f, (z - 10) * -5.0f);	//ぼこぼこな床
				//m_Vertex[x][z].Position = D3DXVECTOR3((x - (MAX_MAP_WIDTH / 2)) * 5.0f, g_FieldHeight[z][x], (z - (MAX_MAP_HEIGHT / 2)) * -5.0f);
				m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル
				m_Vertex[x][z].Diffuse = COLOR_WHITE;
				m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);

				m_EVertex[x][z] = m_Vertex[x][z].Position;
			}
		}

		//法線ベクトル算出
		for (int x = 1; x <= MAX_MAP_WIDTH - 1; x++)
		{
			for (int z = 1; z <= MAX_MAP_HEIGHT - 1; z++)
			{
				D3DXVECTOR3 vx, vz, vn;

				vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position;	//右から左
				vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position;	//奥から手前

				D3DXVec3Cross(&vn, &vz, &vx);//外積
				D3DXVec3Normalize(&vn, &vn);//正規化（長さ1にする）
				m_Vertex[x][z].Normal = vn;
			}
		}


		//頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * (MAX_MAP_WIDTH + 1) * (MAX_MAP_HEIGHT + 1);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	//インデックスバッファ生成
	{
		unsigned int index[((MAX_MAP_WIDTH + 2) * 2) * MAX_MAP_HEIGHT - 2];

		int i = 0;
		for (int x = 0; x < MAX_MAP_WIDTH; x++)
		{
			for (int z = 0; z < MAX_MAP_HEIGHT + 1; z++)
			{
				index[i] = x * (MAX_MAP_WIDTH + 1) + z;
				i++;

				index[i] = (x + 1) * (MAX_MAP_HEIGHT + 1) + z;
				i++;
			}

			if (x == MAX_MAP_WIDTH - 1)
				break;

			index[i] = (x + 1) * (MAX_MAP_WIDTH + 1) + MAX_MAP_HEIGHT;
			i++;

			index[i] = (x + 1) * (MAX_MAP_HEIGHT + 1);
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * (((MAX_MAP_WIDTH + 2) * 2) * MAX_MAP_HEIGHT - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	//テクスチャの読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Asphalt.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);//テクスチャが上手く読み込まれてるか確認

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");//画像をコンパイルして表示
	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void MeshField::UnInit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void MeshField::Update()
{
	Scene* scene = Manager::GetScene();
	DebugSystem* debug = scene->GetGameObject<DebugSystem>(SYSTEM);
	if (debug->GetDebug() == true)
	{
		EditMeshHeight();
	}
}

void MeshField::Draw()
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	for (int x = 0; x <= MAX_MAP_WIDTH; x++)
	{
		for (int z = 0; z <= MAX_MAP_HEIGHT; z++)
		{
			m_Vertex[x][z].Position = D3DXVECTOR3(m_Vertex[x][z].Position.x, m_Vertex[x][z].Position.y, m_Vertex[x][z].Position.z);
			m_Vertex[x][z].Diffuse = COLOR_WHITE;
			m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
		}
	}

	for (int x = 1; x <= MAX_MAP_WIDTH - 1; x++)
	{
		for (int z = 1; z <= MAX_MAP_HEIGHT - 1; z++)
		{
			D3DXVECTOR3 vx, vz, vn;

			vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position;	//右から左
			vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position;	//奥から手前

			D3DXVec3Cross(&vn, &vz, &vx);//外積
			D3DXVec3Normalize(&vn, &vn);//正規化（長さ1にする）
			m_Vertex[x][z].Normal = vn;
		}
	}

	memcpy(vertex, m_Vertex, sizeof(m_Vertex));

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定（2D描画用ポリゴン）
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトロポジ設定（どのようにポリゴンを描くか）
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描写
	Renderer::GetDeviceContext()->DrawIndexed(((MAX_MAP_WIDTH + 2) * 2) * MAX_MAP_HEIGHT - 2, 0, 0);//頂点数
}

float MeshField::GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 pV)
{
	int x, z;

	//ブロック番号算出
	x = static_cast<int>(pos.x / 5.0f + (MAX_MAP_WIDTH / 2));
	z = static_cast<int>(pos.z / -5.0f + (MAX_MAP_HEIGHT / 2));

	D3DXVECTOR3 pos0, pos1, pos2, pos3;	//周りの4頂点の座標

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;

	v12 = pos2 - pos1;	//三角形上側
	v1p = pos - pos1;	//三角形下側

	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;

	if (c.y > 0.0f)
	{
		//左上ポリゴン
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
		D3DXVec3Normalize(&n, &n);
	}
	else
	{
		//右下ポリゴン
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
		D3DXVec3Normalize(&n, &n);
	}

	py = -((pos.x - pos1.x) * n.x + (pos.z - pos1.z) * n.z) / n.y + pos1.y;

	//int deg;
	//deg = iAngleOf2Vector(pV, n);

	////char str1[50];
	////sprintf(str1, "%f", deg);
	////SetWindowText(GetWindow(), str1);

	return py;
}

D3DXVECTOR3 MeshField::RightVec(D3DXVECTOR3 pos, D3DXVECTOR3 v1)
{
	int x, z;

	//ブロック番号算出
	x = static_cast<int>(pos.x / 5.0f + (MAX_MAP_WIDTH / 2));
	z = static_cast<int>(pos.z / -5.0f + (MAX_MAP_HEIGHT / 2));

	D3DXVECTOR3 pos0, pos1, pos2, pos3;	//周りの4頂点の座標

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;

	v12 = pos2 - pos1;	//三角形上側
	v1p = pos - pos1;	//三角形下側

	D3DXVec3Cross(&c, &v12, &v1p);

	D3DXVECTOR3 n;

	if (c.y > 0.0f)
	{
		//左上ポリゴン
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
		D3DXVec3Normalize(&n, &n);
	}
	else
	{
		//右下ポリゴン
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
		D3DXVec3Normalize(&n, &n);
	}

	D3DXVECTOR3 v = v1;
	D3DXVECTOR3 tmp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//tmpとnの角度０またはそれに近いなら、別なベクトルを用意
	if (iAngleOf2Vector(tmp, n) < 0.0174533) //0.00174533rad=1degree
	{
		tmp = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}
	//外積を求める
	D3DXVec3Cross(&v, &n, &tmp);
	D3DXVec3Cross(&v, &v, &n);

	return -v;	//マイナス無しで坂道を上る
}

//フィールドの範囲内にいるよう補正する関数
D3DXVECTOR3 MeshField::MeshFieldWithinRange(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 Pos = pos;

	Pos.x = std::fmax(Pos.x, -(MAX_MAP_WIDTH / 2) * 5.0f + 0.1f);
	Pos.x = std::fmin(Pos.x, (MAX_MAP_WIDTH / 2) * 5.0f - 0.1f);

	Pos.z = std::fmax(Pos.z, -(MAX_MAP_HEIGHT / 2) * 5.0f + 0.1f);
	Pos.z = std::fmin(Pos.z, (MAX_MAP_HEIGHT / 2) * 5.0f - 0.1f);

	return Pos;
}

bool MeshField::CheckMeshToRay()
{
	float RayDistance;
	float RecentRayDistance = 1000.0f;
	bool bRayHit;
	D3DXVECTOR3 wPos[3];
	D3DXVECTOR3 wDir;

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(OBJ3D);
	Camera* cam = scene->GetGameObject<Camera>(SYSTEM);
	WireTarget* wt = scene->GetGameObject<WireTarget>(OBJ3D);

	for (int x = 0; x <= MAX_MAP_WIDTH; x++)
	{
		for (int z = 0; z <= MAX_MAP_HEIGHT; z++)
		{
			D3DXVECTOR3 pos0 = m_Vertex[x][z].Position;
			D3DXVECTOR3 pos1 = m_Vertex[x + 1][z].Position;
			D3DXVECTOR3 pos2 = m_Vertex[x][z + 1].Position;
			D3DXVECTOR3 pos3 = m_Vertex[x + 1][z + 1].Position;

			//レイの開始点
			DirectX::XMVECTOR pos = DirectX::XMVectorSet(cam->GetPos().x, cam->GetPos().y, cam->GetPos().z, 0.0f);

			//レイを飛ばす方向
			DirectX::XMVECTOR dir = DirectX::XMVectorSet(cam->GetForward().x, cam->GetForward().y, cam->GetForward().z, 0.0f);

			DirectX::XMVECTOR v0 = DirectX::XMVectorSet(pos0.x, pos0.y, pos0.z, 0.0f);
			DirectX::XMVECTOR v1 = DirectX::XMVectorSet(pos1.x, pos1.y, pos1.z, 0.0f);
			DirectX::XMVECTOR v2 = DirectX::XMVectorSet(pos2.x, pos2.y, pos2.z, 0.0f);
			DirectX::XMVECTOR v3 = DirectX::XMVectorSet(pos2.x, pos2.y, pos2.z, 0.0f);

			bRayHit = DirectX::TriangleTests::Intersects(pos, DirectX::XMVector3Normalize(dir), v0, v1, v2, RayDistance);
			if (bRayHit)
			{
				//すべての三角形を調べて、一番近い所を採用
				//当たった点との距離で一番短い物を衝突点との距離として採用する			
				if (RecentRayDistance > RayDistance)
				{
					RecentRayDistance = RayDistance;
				}
				D3DXVECTOR3 pos = cam->GetPos() + cam->GetForward() * RecentRayDistance;
				wt->SetTargetPos(pos);

				if (Mouse_IsLeftTrigger())
				{
					float mX = wt->GetPos().x / 5.0f + (MAX_MAP_WIDTH / 2);
					float mZ = wt->GetPos().z / -5.0f + (MAX_MAP_HEIGHT / 2);

					//data.push_back(D3DXVECTOR2(mX, mZ));
					//std::sort(data.begin(), data.end());
					//data.erase(std::unique(data.begin(), data.end()), data.end());
				}
			}

			bRayHit = DirectX::TriangleTests::Intersects(pos, DirectX::XMVector3Normalize(dir), v1, v3, v2, RayDistance);
			if (bRayHit)
			{
				//すべての三角形を調べて、一番近い所を採用
				//当たった点との距離で一番短い物を衝突点との距離として採用する			
				if (RecentRayDistance > RayDistance)
				{
					RecentRayDistance = RayDistance;
				}
				D3DXVECTOR3 pos = cam->GetPos() + cam->GetForward() * RecentRayDistance;
				wt->SetTargetPos(pos);

				if (Mouse_IsLeftTrigger())
				{
					float mX = wt->GetPos().x / 5.0f + (MAX_MAP_WIDTH / 2);
					float mZ = wt->GetPos().z / -5.0f + (MAX_MAP_HEIGHT / 2);

					//data.push_back(D3DXVECTOR2(mX, mZ));
					//std::sort(data.begin(), data.end());
					//data.erase(std::unique(data.begin(), data.end()), data.end());
				}
			}
		}
	}

	return false;
}

void MeshField::EditMeshHeight()
{
	if (Keyboard_IsPress(DIK_U))
	{
		//m_Vertex[static_cast<int>(TargetMeshNum.x)][static_cast<int>(TargetMeshNum.y)].Position.y += ADD_HEIGHT;
		//m_Vertex[static_cast<int>(TargetMeshNum.x) + 1][static_cast<int>(TargetMeshNum.y)].Position.y += ADD_HEIGHT;
		//m_Vertex[static_cast<int>(TargetMeshNum.x)][static_cast<int>(TargetMeshNum.y) + 1].Position.y += ADD_HEIGHT;
		//m_Vertex[static_cast<int>(TargetMeshNum.x) + 1][static_cast<int>(TargetMeshNum.y) + 1].Position.y += ADD_HEIGHT;

		//for (int i = 0; i < data.size(); i++)
		//{
		//	m_Vertex[static_cast<int>(data[i].x)][static_cast<int>(data[i].y)].Position.y += ADD_HEIGHT;
		//	m_Vertex[static_cast<int>(data[i].x) + 1][static_cast<int>(data[i].y)].Position.y += ADD_HEIGHT;
		//	m_Vertex[static_cast<int>(data[i].x)][static_cast<int>(data[i].y) + 1].Position.y += ADD_HEIGHT;
		//	m_Vertex[static_cast<int>(data[i].x) + 1][static_cast<int>(data[i].y) + 1].Position.y += ADD_HEIGHT;
		//}
	}

	if (Keyboard_IsPress(DIK_J))
	{
		//m_Vertex[static_cast<int>(TargetMeshNum.x)][static_cast<int>(TargetMeshNum.y)].Position.y -= ADD_HEIGHT;
		//m_Vertex[static_cast<int>(TargetMeshNum.x) + 1][static_cast<int>(TargetMeshNum.y)].Position.y -= ADD_HEIGHT;
		//m_Vertex[static_cast<int>(TargetMeshNum.x)][static_cast<int>(TargetMeshNum.y) + 1].Position.y -= ADD_HEIGHT;
		//m_Vertex[static_cast<int>(TargetMeshNum.x) + 1][static_cast<int>(TargetMeshNum.y) + 1].Position.y -= ADD_HEIGHT;
	}
}

void MeshField::EditMeshNum()
{
	data.clear();

	int x1,x2, y1, y2 = 0;
	x1 = m_EditMinPos.x;
	y1 = m_EditMinPos.y;
	x2 = m_EditMaXPos.x;
	y2 = m_EditMaXPos.y;

	for (int i = x1; i <= x2; i++)
	{
		for (int n = y1; n > y2; n--)
		{
			data.push_back(D3DXVECTOR2(i, n));
		}
	}

	std::sort(data.begin(), data.end());
	data.erase(std::unique(data.begin(), data.end()), data.end());
}

void MeshField::SaveData(FILE* fp)
{
	for (int x = 0; x <= MAX_MAP_WIDTH; x++)
	{
		for (int z = 0; z <= MAX_MAP_HEIGHT; z++)
		{
			fprintf(fp, "%f ", m_Vertex[x][z].Position.y);
			if (z == MAX_MAP_HEIGHT)
			{
				fprintf(fp, "\n");
			}
		}
	}
}