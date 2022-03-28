#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "Camera.h"
#include "GameObject.h"
#include "model.h"
#include "Player.h"
#include "Input.h"
#include "Calculation.h"
#include "Scene.h"
#include "Manager.h"
#include "DebugSystem.h"
#include "MeshField.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 2.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dist = -5.0f;
}

void Camera::UnInit()
{
}

void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	DebugSystem* debug = scene->GetGameObject<DebugSystem>(SYSTEM);
	Player* player = scene->GetGameObject<Player>(OBJ3D);
	MeshField* meshField = scene->GetGameObject<MeshField>(OBJ3D);

	if (Keyboard_IsPress(DIK_LEFT)/* && !Keyboard_IsPress(DIK_LSHIFT)*/)
	{
		m_Rotation.y -= VALUE_ROTATE;
		m_Rotation.y = AdjustmentRadian(m_Rotation.y);
	}

	if (Keyboard_IsPress(DIK_RIGHT)/* && !Keyboard_IsPress(DIK_LSHIFT)*/)
	{
		m_Rotation.y += VALUE_ROTATE;
		m_Rotation.y = AdjustmentRadian(m_Rotation.y);
	}
	if (debug->GetDebug() == false)
	{
		m_CameraMove.x = static_cast<float>(Mouse_GetMoveX());
		m_Rotation.y += (m_CameraMove.x / 1000);
		m_Rotation.y = AdjustmentRadian(m_Rotation.y);

		m_CameraMove.y = static_cast<float>(Mouse_GetMoveY());
		m_Rotation.x += (m_CameraMove.y / 1000);
		m_Rotation.x = AdjustmentRadian(m_Rotation.x);
	}

	if (debug->GetDebug() == true)
	{
		if (static_cast<bool>(Mouse_IsCenterPress()) == true && debug->GetEditP() == false)
		{
			m_CameraMove.x = static_cast<float>(Mouse_GetMoveX());
			m_Rotation.y += (m_CameraMove.x / 1000);
			m_Rotation.y = AdjustmentRadian(m_Rotation.y);

			m_CameraMove.y = static_cast<float>(Mouse_GetMoveY());
			m_Rotation.x += (m_CameraMove.y / 1000);
			m_Rotation.x = AdjustmentRadian(m_Rotation.x);

			m_Target = m_Position + GetForward() * m_Dist;
		}

		if (Keyboard_IsPress(DIK_W))
		{
			m_Position += GetForward();
			m_Target = m_Position + GetForward() * m_Dist;
		}

		if (Keyboard_IsPress(DIK_S))
		{
			m_Position -= GetForward();
			m_Target = m_Position + GetForward() * m_Dist;
		}

		if (Keyboard_IsPress(DIK_A))
		{
			m_Position -= GetRight();
			m_Target = m_Position + GetForward() * m_Dist;
		}

		if (Keyboard_IsPress(DIK_D))
		{
			m_Position += GetRight();
			m_Target = m_Position + GetForward() * m_Dist;
		}

		if (Keyboard_IsPress(DIK_SPACE))
		{
			m_Position += GetUp();
			m_Target = m_Position + GetForward() * m_Dist;
		}

		//if (Keyboard_IsPress(DIK_5))
		//{
		//	m_Rotation.x = D3DX_PI / 2;
		//	m_Rotation.y = 0.0f;
		//	m_Rotation.z = 0.0f;

		//	m_Target = m_Position + -GetUp() * m_Dist;
		//}

		m_OldRot = m_Rotation;
		m_OldDir = m_Dir;

		meshField->CheckMeshToRay();
	}

	if (debug->GetDebug() == false)
	{
		m_Position.y = player->GetPos().y + 2.0f;

		//徐々にプレイヤー正面を向く
		//if (Keyboard_IsPress(DIK_R))
		//{
		//	//m_Rotation.y = cam->GetRot().y;

		//	m_Rotation.y = (float)LerpRadian(m_Rotation.y, AdjustmentRadian(player->GetRot().y + D3DX_PI), 0.2f);
		//}

		//m_Rotation.y = (float)LerpRadian(m_Rotation.y, AdjustmentRadian(player->GetRot().y + D3DX_PI), 0.2f);

		m_Target = D3DXVECTOR3(player->GetPos().x, m_Position.y, player->GetPos().z);

		D3DXVECTOR3 forward = player->GetForward();

		//m_Position = m_Target - -forward * 5.0f/* + D3DXVECTOR3(0.0f, 3.0f, 0.0f)*/;
		m_Position = m_Target + GetForward() * m_Dist;
	}
}

void Camera::Draw()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(OBJ3D);

	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&m_ViewMatrix);

	D3DXMATRIX mat_move;
	D3DXMatrixTranslation(&mat_move, m_Position.x, m_Position.y, m_Position.z);

	D3DXMATRIX mat_rot;
	D3DXMatrixRotationYawPitchRoll(&mat_rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

	D3DXMATRIX mat_rotmove;
	mat_rotmove = mat_rot * mat_move;
		
	D3DXMATRIX m_ViewMatrix;
	D3DXMatrixInverse(&m_ViewMatrix, NULL, &mat_rotmove);//カメラの逆行列を求める

	Renderer::SetViewMatrix(&m_ViewMatrix);


	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);

	Renderer::SetCameraPosition(m_Position);
}
