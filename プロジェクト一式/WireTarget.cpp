#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "WireTarget.h"
#include "MeshField.h"
#include "OBB.h"
#include "Input.h"
#include "Player.h"

void WireTarget::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\sphere.obj");	//\\2�ɒ��Ӂu//�v�ł�����

	Scene* scene = Manager::GetScene();
	m_Position = D3DXVECTOR3(-3.0f, 6.0f, 3.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.125f, 0.125f, 0.125f);

	m_obb = scene->AddGameObject<OBB>(OBJ3D);
	m_obb->SetOBBPos(D3DXVECTOR3(m_Position.x, m_Position.y, m_Position.z));
	m_obb->SetDirect(0, GetRight());
	m_obb->SetDirect(1, GetUp());
	m_obb->SetDirect(2, GetForward());
	m_obb->SetLen_W(0, 0.125f);
	m_obb->SetLen_W(1, 0.125f);
	m_obb->SetLen_W(2, 0.125f);

	m_obb->SetAll(D3DXVECTOR3(m_obb->GetPos_W().x, m_obb->GetPos_W().y, m_obb->GetPos_W().z),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_obb->GetLen_W(0), m_obb->GetLen_W(1), m_obb->GetLen_W(2)),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		0.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}
void WireTarget::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void WireTarget::Update()
{
	UpdateOBB();
}

void WireTarget::Draw()
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
	m_TargetMatrix = scale * rot * trans;

	Renderer::SetWorldMatrix(&m_TargetMatrix);

	m_Model->Draw();
}

void WireTarget::UpdateOBB()
{
	m_obb->SetOBBPos(D3DXVECTOR3(m_Position.x, m_Position.y/* + m_obb->GetLen_W(1)*/, m_Position.z));
	m_obb->SetDirect(0, GetRight());
	m_obb->SetDirect(1, GetUp());
	m_obb->SetDirect(2, GetForward());

	m_obb->SetAll(D3DXVECTOR3(m_obb->GetPos_W().x, m_obb->GetPos_W().y, m_obb->GetPos_W().z),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_obb->GetLen_W(0), m_obb->GetLen_W(1), m_obb->GetLen_W(2)),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		0.0f);
}
