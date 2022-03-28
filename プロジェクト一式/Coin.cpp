#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "GameObject.h"
#include "Coin.h"
#include "Calculation.h"
#include "MeshField.h"
#include "Building.h"
#include "OBB.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "Score.h"
#include "Effect.h"
#include "RadarDot.h"
#include "audio.h"

Model* Coin::m_Model;	//static�����o�ϐ���cpp���ōēx�錾����K�v������

void Coin::Init()
{
	Scene* scene = Manager::GetScene();
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Frame = 0;
	m_BlendRate = 0;

	m_obb = scene->AddGameObject<OBB>(OBJ3D);
	m_obb->SetOBBPos(D3DXVECTOR3(m_Position.x, m_Position.y, m_Position.z));
	m_obb->SetDirect(0, GetRight());
	m_obb->SetDirect(1, GetUp());
	m_obb->SetDirect(2, GetForward());
	m_obb->SetLen_W(0, 0.05f);
	m_obb->SetLen_W(1, 0.5f);
	m_obb->SetLen_W(2, 0.5f);

	m_obb->SetAll(D3DXVECTOR3(m_obb->GetPos_W().x, m_obb->GetPos_W().y, m_obb->GetPos_W().z),
		D3DXVECTOR3(m_Rotation.x, m_Rotation.y, m_Rotation.z),
		D3DXVECTOR3(m_obb->GetLen_W(0), m_obb->GetLen_W(1), m_obb->GetLen_W(2)),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		0.0f);

	m_CoinSE = scene->AddGameObject<Audio>(SYSTEM);
	m_CoinSE->Load(SE_GET_COIN);

	m_OldPosition = m_Position;

	//m_Dot = scene->AddGameObject<RadarDot>(OBJ2D);
	//m_Dot->SetMyCoin(this);
}

void Coin::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_obb->SetDestroy();
}

void Coin::Update()
{
	//�����X�V�A����`�F�b�N
	UpdateMove();
	UpdateOBB();
	UpdateHeight();

	//�����W�X�V
	m_OldPosition = m_Position;
}

void Coin::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z); //Yaw = y Pitch = x Roll = z
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_EnemyMatrix = scale * rot * trans;

	Renderer::SetWorldMatrix(&m_EnemyMatrix);

	m_Model->Draw();
}

void Coin::UpdateHeight()
{
	Scene* scene = Manager::GetScene();
	std::vector<Building*> BuildingList = scene->GetGameObjects<Building>(OBJ3D);
	for (Building* bldg : BuildingList)
	{
		if (m_obb->ColOBBs(*m_obb, *bldg->GetOBB()))
		{
			m_Position.y = bldg->GetOBB()->GetPos().y + bldg->GetOBB()->GetLen_W(1) + m_Scale.y;
		}
	}
}

void Coin::UpdateMove()
{
	m_Rotation.y += 0.01f;
	m_Rotation.y = AdjustmentRadian(m_Rotation.y);
}

void Coin::UpdateOBB()
{
	m_obb->SetOBBPos(D3DXVECTOR3(m_Position.x, m_Position.y/* + m_obb->GetLen_W(1)*/, m_Position.z));
	m_obb->SetDirect(0, GetRight());
	m_obb->SetDirect(1, GetUp());
	m_obb->SetDirect(2, GetForward());

	m_obb->SetAll(D3DXVECTOR3(m_obb->GetPos_W().x, m_obb->GetPos_W().y, m_obb->GetPos_W().z),
		D3DXVECTOR3(m_Rotation.x, m_Rotation.y, m_Rotation.z),
		D3DXVECTOR3(m_obb->GetLen_W(0), m_obb->GetLen_W(1), m_obb->GetLen_W(2)),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		0.0f);

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(OBJ3D);
	Score* score = scene->GetGameObject<Score>(OBJ2D);

	if (m_obb->ColOBBs(*m_obb, *player->GetOBB()))
	{
		scene->AddScore(SCORE_COIN);
		m_CoinSE->Play(false);
		m_Dot->SetDestroy();
		SetDestroy();
		scene->AddGameObject<Effect>(OBJ3D)->SetEffectAll(m_Position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Scale, EFFECT_COIN);
	}
}

void Coin::SaveData(FILE * fp)
{
	fprintf(fp, "%f,%f,%f ", m_Position.x, m_Position.y, m_Position.z);
	fprintf(fp, "\n");
}