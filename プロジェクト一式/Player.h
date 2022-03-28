#pragma once

#include "GameObject.h"

#define ANI_NAME_IDLE	 "Idle"
#define ANI_NAME_SLOWRUN "SlowRun"
#define ANI_NAME_FASTRUN "FastRun"
#define ANI_NAME_BACKRUN "BackRun"
#define ANI_NAME_JUMP	 "Jump"
#define ANI_NAME_FLY	 "Fly"
#define PLAYER_WALKSPEED (0.075f)
#define PLAYER_DASHSPEED (0.125f)
#define PLAYER_WIREACTIONSPEED (0.5f)
#define MAX_WIRE_ACTION_DEGREE (30)

enum ANIMATION_TYPE
{
	ANI_IDLE,
	ANI_SLOWRUN,
	ANI_FASTRUN,
	ANI_JUMP,
	ANI_BACKRUN,
	ANI_FASTSLOWRUN,
	ANI_FLY
};

class Player : public GameObject
{
private:
	class AnimationModel* m_Model;
	class OBB* m_obb;
	class Audio* m_WireSE;
	ID3D11VertexShader*	m_VertexShader = NULL;
	ID3D11PixelShader*	m_PixelShader = NULL;
	ID3D11InputLayout*	m_VertexLayout = NULL;

	D3DXVECTOR3 m_Direction;
	D3DXVECTOR3 m_OldPosition;
	D3DXVECTOR3 m_SlipVector;
	float	m_PlayerSpd;
	float	m_WireActionSpd;
	float	m_GravityForce;


	int m_Frame;
	const char* m_AniName;
	const char* m_OldAniName;
	ANIMATION_TYPE m_Type;
	ANIMATION_TYPE m_OldType;
	float	m_BlendRate;
	float	m_JumpRate;
	float	m_JumpValue;
	float	m_DashRate;
	D3DXVECTOR3	m_TargetPos;
	bool	m_isWireUse;
	bool	m_isJumpActive;
	bool	m_isJumpEnd;
	bool	m_isFly;
	bool	m_isCol;
	bool	m_isGravity;

	D3DXMATRIX m_PlayerMatrix;

public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

	void UpdateHeight();
	void UpdateMove();
	void CheckSlide();
	void CheckAnimation();
	void UpdateAnimation();
	void UpdateOBB();
	void UpdateWire();

	D3DXMATRIX GetPlayerMatrix()
	{
		return m_PlayerMatrix;
	}

	OBB* GetOBB()
	{
		return m_obb;
	}

	D3DXVECTOR3 GetOldPos()
	{
		return m_OldPosition;
	}

	D3DXVECTOR3 GetDir()
	{
		return m_Direction;
	}

	bool GetisCol()
	{
		return m_isCol;
	}

	bool GetisFly()
	{
		return m_isFly;
	}

	bool GetisGravity()
	{
		return m_isGravity;
	}

	bool GetisWire()
	{
		return m_isWireUse;
	}

	void SetTargetPos(D3DXVECTOR3 pos)
	{
		m_TargetPos = pos;
	}

	void SetDirection(D3DXVECTOR3 dir)
	{
		m_Direction = dir;
	}

	void SetSlipVector(D3DXVECTOR3 dir)
	{
		m_SlipVector = dir;
	}

	int GetAniType()
	{
		return (int)m_Type;
	}

	void SetMouseP();
};