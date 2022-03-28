#pragma once

#include "GameObject.h"

class Camera : public GameObject
{
private:

	static class Camera* m_Camera;	//����class�Ƃ���Ɠǂݍ��߂�B�O���錾�Ƃ���
	D3DXVECTOR3 m_Target;		//�����_

	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectionMatrix;
	D3DXVECTOR3   m_CameraMove;
	float	m_Dist;				//�J�����ƒ����_�̋���
	D3DXVECTOR3 m_OldRot;
	D3DXVECTOR3 m_Dir;
	D3DXVECTOR3 m_OldDir;

	bool	m_Reverse;

public:
	//Polygon2D();	//����͕s�v
	//~Polygon2D();

	void Init();
	void UnInit();
	void Update();
	void Draw();

	void SetTargetPos(float posX, float posY, float posZ)
	{
		m_Target.x = posX;
		m_Target.y = posY;
		m_Target.z = posZ;
	}

	D3DXVECTOR3 GetTargetPos()
	{
		return m_Target;
	}	
	
	D3DXVECTOR3 GetCamMove()
	{
		return m_CameraMove;
	}

	float GetCameraDist()
	{
		return m_Dist;
	}

	bool GetCamReverse()
	{
		return m_Reverse;
	}

	Camera* GetCamera()
	{
		return m_Camera;
	}

	D3DXMATRIX GetViewMatrix()
	{
		return m_ViewMatrix;
	}

	D3DXMATRIX GetProjectionMatrix()
	{
		return m_ProjectionMatrix;
	}
};