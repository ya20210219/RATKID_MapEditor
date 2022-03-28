#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "AnimationModel.h"
#include "GameObject.h"
#include "Building.h"
#include "Calculation.h"
#include "MeshField.h"
#include "OBB.h"
#include "Player.h"
#include "Camera.h"
#include "WireTarget.h"
#include "Input.h"
#include "DebugSystem.h"


Model* Building::m_Model[3];

void Building::Init()
{
	Scene* scene = Manager::GetScene();
	MeshField* meshField = scene->GetGameObject<MeshField>(OBJ3D);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Frame = 0;
	m_BlendRate = 0;
}

void Building::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_obb->SetDestroy();
}

void Building::Update()
{
	Scene* scene = Manager::GetScene();
	DebugSystem* debug = scene->GetGameObject<DebugSystem>(SYSTEM);
	WireTarget* wt = scene->GetGameObject<WireTarget>(OBJ3D);

	if (debug->GetDebug() == true)
	{
		CheckMeshToRay();
	}

	//高さ更新、滑りチェック
	UpdateMove();
	UpdateHeight();
	CheckSlide();
	UpdateOBB();

	m_Frame++;
}

void Building::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z); //Yaw = y Pitch = x Roll = z
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_EnemyMatrix = scale * rot * trans;

	Renderer::SetWorldMatrix(&m_EnemyMatrix);

	m_Model[static_cast<int>(m_Type)]->Draw();
}

void Building::UpdateHeight()
{
	if (m_isCorrection == false)
	{
		Scene* scene = Manager::GetScene();
		MeshField* meshField = scene->GetGameObject<MeshField>(OBJ3D);

		float y = meshField->GetHeight(m_Position, GetForward());
		m_Position.y = y + m_obb->GetLen_W(1);

		m_isCorrection = true;
	}
}

void Building::UpdateMove()
{
	if (Keyboard_IsPress(DIK_RIGHTARROW))
	{
		m_Position.x -= 0.01f;
	}
	if (Keyboard_IsPress(DIK_LEFTARROW))
	{
		m_Position.x += 0.01f;
	}
}

void Building::CheckSlide()
{

}

void Building::UpdateOBB()
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

	Scene* scene = Manager::GetScene();
	DebugSystem* debug = scene->GetGameObject<DebugSystem>(SYSTEM);
	WireTarget* wt = scene->GetGameObject<WireTarget>(OBJ3D);
	std::vector<Building*> BuildingList = scene->GetGameObjects<Building>(OBJ3D);
	if (debug->GetDebug() == true)
	{
		if (m_obb->ColOBBs(*m_obb, *wt->GetOBB()))
		{
			if (Keyboard_IsTrigger(DIK_G))
			{
				m_OldPosition = m_Position;
				m_OldRot = m_Rotation;
				for (Building* bldg : BuildingList)
				{
					bldg->SetEdit(false);
				}
				m_isEdit = true;
				debug->SetEditP(true);
			}
		}
	}
}

void Building::CreateBldg(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BldgType t)
{
	Scene* scene = Manager::GetScene();
	m_Position = pos;
	m_Rotation = rot;
	m_Type = t;

	m_obb = scene->AddGameObject<OBB>(OBJ3D);
	m_obb->SetOBBPos(D3DXVECTOR3(m_Position.x, m_Position.y, m_Position.z));
	m_obb->SetDirect(0, GetRight());
	m_obb->SetDirect(1, GetUp());
	m_obb->SetDirect(2, GetForward());

	switch (m_Type)
	{
	case NORMAL:
		m_obb->SetLen_W(0, 5.0f);
		m_obb->SetLen_W(1, 10.0f);
		m_obb->SetLen_W(2, 5.0f);
		break;
	case LARGE:
		m_obb->SetLen_W(0, 5.0f);
		m_obb->SetLen_W(1, 20.0f);
		m_obb->SetLen_W(2, 5.0f);
		break;
	case HOUSE:
		m_obb->SetLen_W(0, 20.0f);
		m_obb->SetLen_W(1, 40.0f);
		m_obb->SetLen_W(2, 20.0f);
		break;
	}

	m_obb->SetAll(D3DXVECTOR3(m_obb->GetPos_W().x, m_obb->GetPos_W().y, m_obb->GetPos_W().z),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_obb->GetLen_W(0), m_obb->GetLen_W(1), m_obb->GetLen_W(2)),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		0.0f);

	m_isCorrection = false;
}

bool Building::CheckMeshToRay()
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

	unsigned int maxnum;
	maxnum = m_Model[static_cast<int>(m_Type)]->GetIndexNum();

	for (unsigned int i = 0; i < maxnum; i += 3)
	{
		VERTEX_3D *vertex = m_Model[static_cast<int>(m_Type)]->GetVertexArray();
		unsigned int *nownum = m_Model[static_cast<int>(m_Type)]->GetIndexArray();

		D3DXVECTOR3 pos0;
		pos0.x = (vertex + *(nownum + (i + 0)))->Position.x + m_Position.x;
		pos0.y = (vertex + *(nownum + (i + 0)))->Position.y + m_Position.y;
		pos0.z = (vertex + *(nownum + (i + 0)))->Position.z + m_Position.z;
		D3DXVECTOR3 pos1;
		pos1.x = (vertex + *(nownum + (i + 1)))->Position.x + m_Position.x;
		pos1.y = (vertex + *(nownum + (i + 1)))->Position.y + m_Position.y;
		pos1.z = (vertex + *(nownum + (i + 1)))->Position.z + m_Position.z;
		D3DXVECTOR3 pos2;
		pos2.x = (vertex + *(nownum + (i + 2)))->Position.x + m_Position.x;
		pos2.y = (vertex + *(nownum + (i + 2)))->Position.y + m_Position.y;
		pos2.z = (vertex + *(nownum + (i + 2)))->Position.z + m_Position.z;

		//レイの開始点
		DirectX::XMVECTOR pos = DirectX::XMVectorSet(cam->GetPos().x, cam->GetPos().y, cam->GetPos().z, 0.0f);

		//レイを飛ばす方向
		DirectX::XMVECTOR dir = DirectX::XMVectorSet(cam->GetForward().x, cam->GetForward().y, cam->GetForward().z, 0.0f);

		DirectX::XMVECTOR v0 = DirectX::XMVectorSet(pos0.x, pos0.y, pos0.z, 0.0f);
		DirectX::XMVECTOR v1 = DirectX::XMVectorSet(pos1.x, pos1.y, pos1.z, 0.0f);
		DirectX::XMVECTOR v2 = DirectX::XMVectorSet(pos2.x, pos2.y, pos2.z, 0.0f);

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
			if (Mouse_IsLeftPress() == false)
			{
				player->SetTargetPos(pos);
			}
			D3DXVECTOR3 pDir = pos - player->GetPos();
			D3DXVec3Normalize(&pDir, &pDir);
			wt->SetTargetPos(pos);
			wPos[0] = D3DXVECTOR3(pos0.x, pos0.y, pos0.z);
			wPos[1] = D3DXVECTOR3(pos1.x, pos1.y, pos1.z);
			wPos[2] = D3DXVECTOR3(pos2.x, pos2.y, pos2.z);

			D3DXVECTOR3 v10 = wPos[1] - wPos[0];
			D3DXVECTOR3 v12 = wPos[2] - wPos[1];

			wDir = *D3DXVec3Cross(&wDir, &v10, &v12);
			D3DXVec3Normalize(&wDir, &wDir);
			wt->SetTargetMeshDirection(wDir);
		}
	}

	return false;
}

bool Building::CheckFootMeshToRay(D3DXVECTOR3 dir)
{
	float RayDistance;
	float RecentRayDistance = 1000.0f;
	bool bRayHit;

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(OBJ3D);
	Camera* cam = scene->GetGameObject<Camera>(SYSTEM);
	WireTarget* wt = scene->GetGameObject<WireTarget>(OBJ3D);

	unsigned int maxnum;
	maxnum = m_Model[static_cast<int>(m_Type)]->GetIndexNum();

	for (unsigned int i = 0; i < maxnum; i += 3)
	{
		VERTEX_3D *vertex = m_Model[static_cast<int>(m_Type)]->GetVertexArray();
		unsigned int *nownum = m_Model[static_cast<int>(m_Type)]->GetIndexArray();

		//(a + (*b + c))->Position.x

		D3DXVECTOR3 pos0;
		pos0.x = (vertex + *(nownum + (i + 0)))->Position.x + m_Position.x;
		pos0.y = (vertex + *(nownum + (i + 0)))->Position.y + m_Position.y;
		pos0.z = (vertex + *(nownum + (i + 0)))->Position.z + m_Position.z;
		D3DXVECTOR3 pos1;
		pos1.x = (vertex + *(nownum + (i + 1)))->Position.x + m_Position.x;
		pos1.y = (vertex + *(nownum + (i + 1)))->Position.y + m_Position.y;
		pos1.z = (vertex + *(nownum + (i + 1)))->Position.z + m_Position.z;
		D3DXVECTOR3 pos2;
		pos2.x = (vertex + *(nownum + (i + 2)))->Position.x + m_Position.x;
		pos2.y = (vertex + *(nownum + (i + 2)))->Position.y + m_Position.y;
		pos2.z = (vertex + *(nownum + (i + 2)))->Position.z + m_Position.z;

		//レイの開始点
		DirectX::XMVECTOR pos = DirectX::XMVectorSet(player->GetPos().x, player->GetPos().y, player->GetPos().z, 0.0f);

		//レイを飛ばす方向
		DirectX::XMVECTOR pDir = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);

		DirectX::XMVECTOR v0 = DirectX::XMVectorSet(pos0.x, pos0.y, pos0.z, 0.0f);
		DirectX::XMVECTOR v1 = DirectX::XMVectorSet(pos1.x, pos1.y, pos1.z, 0.0f);
		DirectX::XMVECTOR v2 = DirectX::XMVectorSet(pos2.x, pos2.y, pos2.z, 0.0f);

		bRayHit = DirectX::TriangleTests::Intersects(pos, DirectX::XMVector3Normalize(pDir), v0, v1, v2, RayDistance);
		if (bRayHit)
		{
			return bRayHit;
		}
	}

	return false;
}

bool Building::CheckWallMeshToRay(D3DXVECTOR3 dir)
{
	float RayDistance;
	float RecentRayDistance = 1000.0f;
	bool bRayHit;
	D3DXVECTOR3 wPos[3];
	D3DXVECTOR3 wDir;

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(OBJ3D);
	WireTarget* wt = scene->GetGameObject<WireTarget>(OBJ3D);

	unsigned int maxnum;
	maxnum = m_Model[static_cast<int>(m_Type)]->GetIndexNum();

	for (int n = 0; n < 2; n++)
	{
		for (unsigned int i = 0; i < maxnum; i += 3)
		{
			VERTEX_3D *vertex = m_Model[static_cast<int>(m_Type)]->GetVertexArray();
			unsigned int *nownum = m_Model[static_cast<int>(m_Type)]->GetIndexArray();
		
			D3DXVECTOR3 pos0;
			pos0.x = (vertex + *(nownum + (i + 0)))->Position.x + m_Position.x;
			pos0.y = (vertex + *(nownum + (i + 0)))->Position.y + m_Position.y;
			pos0.z = (vertex + *(nownum + (i + 0)))->Position.z + m_Position.z;
			D3DXVECTOR3 pos1;
			pos1.x = (vertex + *(nownum + (i + 1)))->Position.x + m_Position.x;
			pos1.y = (vertex + *(nownum + (i + 1)))->Position.y + m_Position.y;
			pos1.z = (vertex + *(nownum + (i + 1)))->Position.z + m_Position.z;
			D3DXVECTOR3 pos2;
			pos2.x = (vertex + *(nownum + (i + 2)))->Position.x + m_Position.x;
			pos2.y = (vertex + *(nownum + (i + 2)))->Position.y + m_Position.y;
			pos2.z = (vertex + *(nownum + (i + 2)))->Position.z + m_Position.z;

			//レイの開始点
			DirectX::XMVECTOR pos = DirectX::XMVectorSet(player->GetPos().x, player->GetPos().y + 0.5f, player->GetPos().z, 0.0f);

			//レイを飛ばす方向
			DirectX::XMVECTOR Raydir;
			if (n == 0)
			{
				Raydir = DirectX::XMVectorSet(-dir.x, -dir.y, -dir.z, 0.0f);
			}
			if (n == 1)
			{
				Raydir = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
			}

			DirectX::XMVECTOR v0 = DirectX::XMVectorSet(pos0.x, pos0.y, pos0.z, 0.0f);
			DirectX::XMVECTOR v1 = DirectX::XMVectorSet(pos1.x, pos1.y, pos1.z, 0.0f);
			DirectX::XMVECTOR v2 = DirectX::XMVectorSet(pos2.x, pos2.y, pos2.z, 0.0f);

			bRayHit = DirectX::TriangleTests::Intersects(pos, DirectX::XMVector3Normalize(Raydir), v0, v1, v2, RayDistance);
			if (bRayHit)
			{
				//すべての三角形を調べて、一番近い所を採用
				//当たった点との距離で一番短い物を衝突点との距離として採用する			
				if (RecentRayDistance > RayDistance)
				{
					RecentRayDistance = RayDistance;
					if (RecentRayDistance < 1.0f)
					{
						wPos[0] = D3DXVECTOR3(pos0.x, pos0.y, pos0.z);
						wPos[1] = D3DXVECTOR3(pos1.x, pos1.y, pos1.z);
						wPos[2] = D3DXVECTOR3(pos2.x, pos2.y, pos2.z);

						D3DXVECTOR3 v10 = wPos[1] - wPos[0];
						D3DXVECTOR3 v12 = wPos[2] - wPos[1];

						wDir = *D3DXVec3Cross(&wDir, &v10, &v12);
						D3DXVec3Normalize(&wDir, &wDir);
						player->SetSlipVector(wDir);
					}
				}
			}
		}
	}

	return false;
}

void Building::SaveData(FILE * fp)
{
	fprintf(fp, "%f,%f,%f ", m_Position.x, m_Position.y, m_Position.z);
	fprintf(fp, "\n");
	fprintf(fp, "%f,%f,%f ", m_Rotation.x, m_Rotation.y, m_Rotation.z);
	fprintf(fp, "\n");
	fprintf(fp, "%d", static_cast<int>(m_Type));
	fprintf(fp, "\n");
}