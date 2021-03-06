#include "main.h"
#include "renderer.h"
#include "Calculation.h"

#define	D3DX_PI2	(D3DX_PI * 2.0f)

//pxÌü`âÔ
float LerpRadian(double a, double b, float t)
{
	//tÌâ³
	t = std::min(std::max(t, 0.0f), 1.0f);

	return NormalizeRadian(a + t * NormalizeRadian(b - a));
}

//³K»
float NormalizeRadian(double rad)
{
	//2Îðíé
	int num = static_cast<int>(rad / D3DX_PI2);
	float temp = static_cast<float>(rad) - (D3DX_PI2 * num);

	AdjustmentRadian(temp);

	return temp;
}

//pxð-3.14`3.14ÌÔÉâ³
float AdjustmentRadian(float value)
{
	if (value < -D3DX_PI)
	{
		value += D3DX_PI2;
	}

	if (value > D3DX_PI)
	{
		value -= D3DX_PI2;
	}

	return value;
}

//£vª
float MeasureDist(D3DXVECTOR3 my, D3DXVECTOR3 target)
{
	D3DXVECTOR3 dir;
	dir = my - target;
	float length = D3DXVec3Length(&dir);
	return length;
}

//lÌü`âÔ
float LerpValue(float a, float b, float t)
{
	return a * (1.0f - t) + b * t;
}

//QÂÌxNgABÌÈ·pxÆðßé
int iAngleOf2Vector(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	float v1Length = D3DXVec3Length(&v1);
	float v2Length = D3DXVec3Length(&v2);

	float cosTheta = D3DXVec3Dot(&v1, &v2) / (v1Length * v2Length);

	float Theta = static_cast<float>(acos(cosTheta));

	Theta = static_cast<float>(Theta * 180.0)/ D3DX_PI;

	return static_cast<int>(Theta);
}

float fAngleOf2Vector(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	float v1Length = D3DXVec3Length(&v1);
	float v2Length = D3DXVec3Length(&v2);

	float cosTheta = D3DXVec3Dot(&v1, &v2) / (v1Length * v2Length);

	float Theta = static_cast<float>(acos(cosTheta));

	return Theta;
}