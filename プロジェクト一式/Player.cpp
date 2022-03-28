#include "main.h"
#include "Calculation.h"
#include "manager.h"
#include "renderer.h"
#include "AnimationModel.h"
#include "Player.h"
#include "MeshField.h"
#include "OBB.h"
#include "Building.h"
#include "WireTarget.h"
#include "Camera.h"
#include "audio.h"
#include "Input.h"
#include "DebugSystem.h"

void Player::Init()
{
	Scene* scene = Manager::GetScene();
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Akai_Idle.fbx");	//\\2�ɒ��Ӂu//�v�ł�����

	m_Model->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Slow Run.fbx", "SlowRun");
	m_Model->LoadAnimation("asset\\model\\Fast Run.fbx", "FastRun");
	m_Model->LoadAnimation("asset\\model\\Running Backward.fbx", "BackRun");
	m_Model->LoadAnimation("asset\\model\\Jump1.fbx", "Jump");
	m_Model->LoadAnimation("asset\\model\\Flying.fbx", "Fly");

	m_Position	= D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	m_Rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale		= D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Frame = 0;
	m_BlendRate = 0;
	m_Type = m_OldType = ANI_IDLE;

	m_Model->Update(m_Frame, "Idle");

	m_obb = scene->AddGameObject<OBB>(OBJ3D);
	m_obb->SetOBBPos(D3DXVECTOR3(m_Position.x, m_Position.y + 0.95f, m_Position.z));
	m_obb->SetDirect(0, GetRight());			//x���̌���
	m_obb->SetDirect(1, GetUp());				//y���̌���
	m_obb->SetDirect(2, GetForward()); //z���̌���
	m_obb->SetLen_W(0, 0.35f);	//x���ł̌���
	m_obb->SetLen_W(1, 0.95f);	//y���ł̌���
	m_obb->SetLen_W(2, 0.4f);	//z���ł̌���

	m_obb->SetAll(D3DXVECTOR3(m_obb->GetPos_W().x, m_obb->GetPos_W().y, m_obb->GetPos_W().z),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_obb->GetLen_W(0), m_obb->GetLen_W(1), m_obb->GetLen_W(2)),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		0.0f);

	m_PlayerSpd = PLAYER_WALKSPEED;
	m_WireActionSpd = PLAYER_WIREACTIONSPEED;
	m_OldPosition = m_Position;
	m_Direction = GetForward();
	m_isWireUse = false;
	m_isFly = false;
	m_isCol = false;
	m_isGravity = false;

	m_WireSE = scene->AddGameObject<Audio>(SYSTEM);
	m_WireSE->Load(SE_WIRE_SHOT);
}

void Player::UnInit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	Scene* scene = Manager::GetScene();
	DebugSystem* debug = scene->GetGameObject<DebugSystem>(SYSTEM);
	if (debug->GetDebug() == false)
	{
		//�����X�V�A����`�F�b�N
		UpdateWire();
		UpdateMove();
		if (!m_isFly)
		{
			CheckSlide();
		}
		if (!m_isWireUse)
		{
			UpdateHeight();
		}
		CheckAnimation();
		UpdateAnimation();
		UpdateOBB();

		//�����W�X�V
		m_OldPosition = m_Position;

		m_Frame++;
	}
}

void Player::Draw()
{	
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z); //Yaw = y Pitch = x Roll = z
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_PlayerMatrix = scale * rot * trans;

	Renderer::SetWorldMatrix(&m_PlayerMatrix);

	m_Model->Draw();
}

void Player::UpdateHeight()
{
	Scene* scene = Manager::GetScene();
	MeshField* meshField = scene->GetGameObject<MeshField>(OBJ3D);
	float y = meshField->GetHeight(m_Position, GetForward());

	//�����d�͂����݂̍����ɉ��Z�������A�n�ʂ̍����������ꍇ
	if (y > (m_Position.y + m_GravityForce))
	{
		//���������ɍ��킹��
		m_Position.y = meshField->GetHeight(m_Position, GetForward());
		m_Direction = GetForward();
		m_GravityForce = GRAVITY;
		m_isGravity = false;
	}
	else if(m_isFly == true)
	{
		m_isGravity = true;
	}

	if (m_isGravity == true)
	{
		m_Position.y += m_GravityForce;
		//�d�͉��Z���@�͌�����
		m_GravityForce *= 1.04f;
	}
}

void Player::UpdateMove()
{
	Scene* scene = Manager::GetScene();
	MeshField* meshField = scene->GetGameObject<MeshField>(OBJ3D);
	Camera* cam = scene->GetGameObject<Camera>(SYSTEM);

	//�^���̒n�ʂ̍������擾
	float y = meshField->GetHeight(m_Position, GetForward());

	if (m_isFly == true && y == m_Position.y)
	{
		m_isFly = false;
	}

	//���C���[���g���ĂȂ���Ε��ʂ̑���œ�����
	if (m_isWireUse == false)
	{
		if (Keyboard_IsPress(DIK_W))
		{
			//��ɃJ�����̌����Ă�������։�]������
			if (!Keyboard_IsPress(DIK_A) && !Keyboard_IsPress(DIK_D))
			{
				//float rot = (cam->GetRot().y + D3DX_PI);
				//rot = AdjustmentRadian(rot);
				////m_Rotation.y = LerpRadian(m_Rotation.y, rot, 0.075f);
				//m_Rotation.y = rot;
				//m_Rotation.y = AdjustmentRadian(m_Rotation.y);
			}

			if (m_isCol == false && Keyboard_IsPress(DIK_A) == false && Keyboard_IsPress(DIK_D) == false && Keyboard_IsPress(DIK_LCONTROL) == false)
			{
				if (m_isFly == false)
				{
					m_Direction = GetForward();
				}
			}
			m_Position -= m_Direction * m_PlayerSpd;
		}

		//�������ɐi��
		else if (Keyboard_IsPress(DIK_S))
		{
			m_Position += m_Direction * m_PlayerSpd;
		}

		//�L�����N�^�[�̉�]
		if (Keyboard_IsPress(DIK_A))
		{
			m_Rotation.y -= 0.05f;
			AdjustmentRadian(m_Rotation.y);
			if (m_isFly == false)
			{
				m_Direction = GetForward();
			}
		}

		if (Keyboard_IsPress(DIK_D))
		{
			m_Rotation.y += 0.05f;
			AdjustmentRadian(m_Rotation.y);	
			if (m_isFly == false)
			{
				m_Direction = GetForward();
			}
		}
	}

	if(m_isFly == true || m_isWireUse == true)
	{
		//���C���[���������Ă�����W�Ƃ̋��������ȏ�ł���΃��C���[�A�N�V�����̓���������
		if (MeasureDist(m_Position, m_TargetPos) > 0.5f)
		{
			if (m_isCol == false)
			{
				m_Position += m_Direction * m_WireActionSpd;
			}
		}
		//����ȊO�͓������Œ�
		else
		{
			m_Position = m_TargetPos;
		}
	}

	//�t�B�[���h�̌��E�l�ȏ�ł͂Ȃ����̃`�F�b�N�B�����Ă�����␳
	m_Position = meshField->MeshFieldWithinRange(m_Position);
}

void Player::UpdateWire()
{
	Scene* scene = Manager::GetScene();
	MeshField* meshField = scene->GetGameObject<MeshField>(OBJ3D);
	WireTarget* wt = scene->GetGameObject<WireTarget>(OBJ3D);
	Camera* cam = scene->GetGameObject<Camera>(SYSTEM);
	std::vector<Building*> BuildingList = scene->GetGameObjects<Building>(OBJ3D);

	//�N���b�N����ĂȂ��ꍇ
	if (!Mouse_IsLeftPress())
	{
		for (Building* bldg : BuildingList)
		{
			//���C���[�̃^�[�Q�b�g���W���X�V����
			bldg->CheckMeshToRay();
		}
	}

	//�N���b�N����Ă���ꍇ
	if (Mouse_IsLeftPress())
	{
		D3DXVECTOR3 dir = cam->GetForward();
		dir.y = GetForward().y;
		int deg = 0;
		deg = iAngleOf2Vector(-GetForward(), dir);

		if (deg < static_cast<int>(MAX_WIRE_ACTION_DEGREE))
		{
			if (m_isWireUse == false)
			{
				m_WireSE->Play(false);
			}
			m_isWireUse = true;
			m_GravityForce = GRAVITY;
			m_isGravity = false;

			for (Building* bldg : BuildingList)
			{
				if (m_obb->ColOBBs(*wt->GetOBB(), *bldg->GetOBB()))
				{
					//���C���[�̍��W���قډ���̋߂��̏ꍇ
					if (m_TargetPos.y > (bldg->GetPos().y + bldg->GetOBB()->GetLen_W(1) - 0.5f))
					{
						//����̍����֍��W��␳���A�r�����֏����ʒu�𒲐�����
						m_TargetPos = wt->GetPos();
						m_TargetPos = m_TargetPos + -(wt->GetTargetMeshDirection()) * 0.01f;
						m_TargetPos.y = (bldg->GetPos().y + bldg->GetOBB()->GetLen_W(1));
					}
					else
					{
						//�ǂɓ���Ȃ��悤�ǂ̊O���֏�����������
						m_TargetPos = wt->GetPos();
						m_TargetPos = m_TargetPos + wt->GetTargetMeshDirection() * 0.05f;
					}
				}
			}

			m_Direction = m_TargetPos - m_Position;
			D3DXVec3Normalize(&m_Direction, &m_Direction);
			m_Position += m_Direction * m_WireActionSpd;
		}
	}

	if (!Mouse_IsLeftPress() && m_isWireUse == true)
	{
		m_isWireUse = false;
		m_isFly = true;
	}
}

void Player::CheckSlide()
{
	Scene* scene = Manager::GetScene();
	MeshField* meshField = scene->GetGameObject<MeshField>(OBJ3D);

	//�^���̒n�ʂ̍������擾
	float y = meshField->GetHeight(m_Position, GetForward());

	//�����Ɠ����������ꍇ���ׂ�x�N�g�����擾�A���ׂ点��
	if (m_isFly == false && m_isCol == false)
	{
		m_SlipVector = meshField->RightVec(m_Position, GetForward());
		m_Position += m_SlipVector * m_PlayerSpd;
	}
}

void Player::UpdateOBB()
{
	m_obb->SetOBBPos(D3DXVECTOR3(m_Position.x, m_Position.y + 0.95f, m_Position.z));
	m_obb->SetDirect(0, GetRight());
	m_obb->SetDirect(1, GetUp());
	m_obb->SetDirect(2, GetForward());
	m_obb->SetPos(m_obb->GetPos_W().x, m_obb->GetPos_W().y, m_obb->GetPos_W().z);
	m_obb->SetRot(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	Scene* scene = Manager::GetScene();
	std::vector<Building*> BuildingList = scene->GetGameObjects<Building>(OBJ3D);
	MeshField* meshField = scene->GetGameObject<MeshField>(OBJ3D);
	float y = meshField->GetHeight(m_Position, GetForward());

	m_isCol = false;

	for (Building* bldg : BuildingList)
	{
		//�r����OBB�ƐڐG������ꍇ
		if (m_obb->ColOBBs(*m_obb, *bldg->GetOBB()))
		{
			m_isCol = true;

			//�����艺�ɂ�����
			if (m_Position.y < bldg->GetPos().y + bldg->GetOBB()->GetLen_W(1))
			{
				//�n�ʂƐڂ��Ă�����
				if (y == m_Position.y && m_isWireUse == false)
				{
					//�ǂɂ����Ċ��点��
					//if (Keyboard_IsPress(DIK_W))
					//{
					//	bldg->CheckWallMeshToRay(GetForward());
					//}
					//if (Keyboard_IsPress(DIK_S))
					//{
					//	//bldg->CheckWallMeshToRay(-GetForward());
					//}
					bldg->CheckWallMeshToRay(GetForward());
					D3DXVec3Normalize(&m_SlipVector, &m_SlipVector);
					D3DXVec3Normalize(&m_Direction, &(GetForward() - D3DXVec3Dot(&GetForward(), &m_SlipVector) * m_SlipVector));
				}
				//�n�ʂɐڂ��Ă��Ȃ���ԂŔ��ł����Ԃ̏ꍇ(���ォ��~���ۂɓ���Ȃ��悤�ɂ��邽��)
				else if(m_isFly == true)
				{
					m_Direction = GetUp();
				} 
			}
		}

		//�����Ƀr�����b�V��������A����̏�ɂ����Ԃł����
		if (bldg->CheckFootMeshToRay(-GetUp()) == true && m_Position.y > (bldg->GetPos().y + bldg->GetOBB()->GetLen_W(1) - 0.5f))
		{
			m_isCol = true;
			m_isFly = false;
			m_Position.y = bldg->GetPos().y + bldg->GetOBB()->GetLen_W(1);
			if (m_isWireUse == false)
			{
				m_Direction = GetForward();
			}
			m_GravityForce = GRAVITY;
			m_isGravity = false;
		}
		//�����Ƀr�����b�V�����Ȃ����
		if (bldg->CheckFootMeshToRay(-GetUp()) == false)
		{
			if (m_isWireUse == false)
			{
				m_isGravity = true;
			}
		}
	}
}

void Player::CheckAnimation()
{
	if (m_isJumpActive == false)
	{	
		//====�k���A�j���[�V����====================
		if (Keyboard_IsPress(DIK_W))
		{
			if (m_Type != ANI_FASTSLOWRUN && m_Type != ANI_FASTRUN)
			{
				m_Type = ANI_SLOWRUN;
				m_AniName = ANI_NAME_SLOWRUN;				
				m_PlayerSpd = PLAYER_WALKSPEED;

				//====�_�b�V���A�j���[�V����====================
				if (Keyboard_IsPress(DIK_LSHIFT))
				{
					m_Type = ANI_FASTSLOWRUN;
					m_AniName = ANI_NAME_FASTRUN;
					m_PlayerSpd = PLAYER_DASHSPEED;
				}
			}
		}
		//====��i�A�j���[�V����====================
		if (Keyboard_IsPress(DIK_S))
		{
			m_Type = ANI_BACKRUN;
			m_AniName = ANI_NAME_BACKRUN;
		}
	}

	//====�W�����v�A�j���[�V����====================
	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		m_OldType = m_Type;
		m_AniName = ANI_NAME_JUMP;
		m_Type = ANI_JUMP;
		m_JumpRate = 0.0f;
	}

	//�u�����h���[�g�X�V
	if (m_Type == ANI_SLOWRUN || m_Type == ANI_BACKRUN || m_Type == ANI_FASTRUN)
	{
		m_BlendRate += 0.02f;
		if (m_BlendRate >= 1.0f)
		{
			m_BlendRate = 1.0f;
		}
		if (m_Type == ANI_FASTRUN && !Keyboard_IsPress(DIK_LSHIFT))
		{
			m_Type = ANI_FASTSLOWRUN;
		}
	}

	//�k������_�b�V���ւ̑J�ڊǗ�
	if (m_Type == ANI_FASTSLOWRUN)
	{
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			m_DashRate += 0.05f;
			if (m_DashRate >= 1.0f)
			{
				m_DashRate = 1.0f;
				m_Type = ANI_FASTRUN;
				m_AniName = ANI_NAME_FASTRUN;
				m_PlayerSpd = PLAYER_DASHSPEED;
			}
		}

		//�_�b�V�������Ă��Ȃ�������
		if (!Keyboard_IsPress(DIK_LSHIFT))
		{
			m_DashRate -= 0.05f;
			if (m_DashRate <= 0.0f)
			{
				m_OldType = m_Type;
				m_DashRate = 0.0f;
				m_Type = ANI_SLOWRUN;
				m_AniName = ANI_NAME_SLOWRUN;
				m_PlayerSpd = PLAYER_WALKSPEED;
			}
		}
	}

	//�W�����v�̏ꍇ�ʏ���
	if (m_Type == ANI_JUMP)
	{
		m_isJumpActive = true;
		m_JumpRate++;
		if (m_isJumpEnd == false)
		{
			m_BlendRate += 0.05f;
			if (m_BlendRate >= 1.0f)
			{
				m_BlendRate = 1.0f;
			}
			if (m_JumpRate > 42.0f)
			{
				m_isJumpEnd = true;
			}
		}
		if (m_isJumpEnd == true)
		{
			m_BlendRate -= 0.05f;
			if (m_BlendRate <= 0.0f)
			{
				m_BlendRate = 0.0f;
				m_Type = ANI_IDLE;
				m_AniName = ANI_NAME_IDLE;
				m_isJumpEnd = false;
				m_isJumpActive = false;
				m_JumpRate = 0;
			}
		}
	}

	//�A�C�h����Ԃɖ߂�
	if (Keyboard_IsRelease(DIK_W) || Keyboard_IsRelease(DIK_S))
	{
		m_OldType = m_Type;
		m_OldAniName = m_AniName;
		m_Type = ANI_IDLE;
		m_AniName = ANI_NAME_IDLE;
	}

	//�A�j���[�V������k���֏��X�ɑJ�ڂ�����
	if (m_Type == ANI_IDLE)
	{
		m_BlendRate -= 0.02f;
		if (m_BlendRate < 0.0f)
		{
			m_BlendRate = 0.0f;
		}
		m_DashRate = m_JumpRate = 0.0f;
	}
}

void Player::UpdateAnimation()
{
	switch (m_Type)
	{
	case ANI_IDLE:
		if (m_OldType == ANI_SLOWRUN)
		{
			m_Model->Update(m_Frame, ANI_NAME_IDLE, ANI_NAME_SLOWRUN, m_BlendRate);
		}
		if (m_OldType == ANI_FASTRUN)
		{
			m_Model->Update(m_Frame, ANI_NAME_IDLE, ANI_NAME_FASTRUN, m_BlendRate);
		}
		if (m_OldType == ANI_BACKRUN)
		{
			m_Model->Update(m_Frame, ANI_NAME_IDLE, ANI_NAME_BACKRUN, m_BlendRate);
		}
		if (m_OldType == ANI_FASTSLOWRUN)
		{
			m_Model->Update(m_Frame, ANI_NAME_IDLE, m_AniName, m_BlendRate);
		}
		if (m_OldType == ANI_IDLE)
		{
			m_Model->Update(m_Frame, ANI_NAME_IDLE);
		}
		break;
	case ANI_SLOWRUN:
		m_Model->Update(m_Frame, ANI_NAME_IDLE, ANI_NAME_SLOWRUN, m_BlendRate);
		break;
	case ANI_FASTRUN:
		m_Model->Update(m_Frame, ANI_NAME_IDLE, ANI_NAME_FASTRUN, m_BlendRate);
		break;
	case ANI_BACKRUN:
		m_Model->Update(m_Frame, ANI_NAME_IDLE, ANI_NAME_BACKRUN, m_BlendRate);
		break;
	case ANI_JUMP:
		m_Model->Update(m_JumpRate, ANI_NAME_IDLE, ANI_NAME_JUMP, m_BlendRate);
		break;
	case ANI_FASTSLOWRUN:
		m_Model->Update(m_Frame, ANI_NAME_SLOWRUN, ANI_NAME_FASTRUN, m_DashRate);
		break;
	}

	switch (m_Type)
	{
	case ANI_IDLE:
		m_AniName = ANI_NAME_IDLE;
		break;
	case ANI_SLOWRUN:
		m_AniName = ANI_NAME_SLOWRUN;
		break;
	case ANI_FASTRUN:
		m_AniName = ANI_NAME_FASTRUN;
		break;
	case ANI_BACKRUN:
		m_AniName = ANI_NAME_BACKRUN;
		break;
	case ANI_JUMP:
		m_AniName = ANI_NAME_JUMP;
		break;
	}
}