#pragma once

#include "GameObject.h"

class Camera : public GameObject
{
private:

	static class Camera* m_Camera;	//頭にclassとつけると読み込める。前方宣言という
	D3DXVECTOR3 m_Target;		//注視点

	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectionMatrix;
	D3DXVECTOR3   m_CameraMove;
	float	m_Dist;				//カメラと注視点の距離
	D3DXVECTOR3 m_OldRot;
	D3DXVECTOR3 m_Dir;
	D3DXVECTOR3 m_OldDir;

	bool	m_Reverse;

public:
	//Polygon2D();	//今回は不要
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