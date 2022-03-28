#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "model.h"
#include "Scene.h"
#include "Radar.h"
#include "Camera.h"
#include "RadarMain.h"
#include "RadarDot.h"
#include "Coin.h"
#include "Player.h"
#include "Calculation.h"

void Radar::Init()
{
	Scene* scene = Manager::GetScene();
	scene->AddGameObject<RadarMain>(OBJ2D)->SetPos(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 100.0f,0.0f);

	std::vector<Coin*> CoinList = scene->GetGameObjects<Coin>(OBJ3D);

	for (Coin* coin : CoinList)
	{
		coin->SetDot(scene->AddGameObject<RadarDot>(OBJ2D));
		coin->GetDot()->SetMyCoin(coin);
	}
}

void Radar::UnInit()
{
}

void Radar::Update()
{
	Scene* scene = Manager::GetScene();
	std::vector<Coin*> CoinList = scene->GetGameObjects<Coin>(OBJ3D);

	for (Coin* coin : CoinList)
	{
		if (coin->GetDot() == nullptr)
		{
			coin->SetDot(scene->AddGameObject<RadarDot>(OBJ2D));
			coin->GetDot()->SetMyCoin(coin);
		}
	}

	UpdateDotPos();
}

void Radar::Draw()
{
}

void Radar::UpdateDotPos()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(OBJ3D);
	Camera* cam = scene->GetGameObject<Camera>(SYSTEM);
	std::vector<Coin*> CoinList = scene->GetGameObjects<Coin>(OBJ3D);
	RadarMain* radarMain = scene->GetGameObject<RadarMain>(OBJ2D);
	std::vector<RadarDot*> RadarDotList = scene->GetGameObjects<RadarDot>(OBJ2D);

	for (RadarDot* dot : RadarDotList)
	{
		/*if (dot->GetMyCoin() == nullptr)
		{
			dot->SetDestroy();
			break;
		}*/
		D3DXVECTOR3 vec = player->GetPos() - dot->GetMyCoin()->GetPos();
		vec.y = vec.z;
		vec.z = 0.0f;
		vec.x *= -1;

		D3DXVECTOR3 fixVec;
		fixVec.x = cosf(-cam->GetRot().y) * vec.x - sinf(-cam->GetRot().y) * vec.y;
		fixVec.y = sinf(-cam->GetRot().y) * vec.x + cosf(-cam->GetRot().y) * vec.y;
		fixVec.z = 0.0f;

		D3DXVECTOR3 pos = dot->GetPos();

		pos = radarMain->GetPos() + fixVec * 1.0f;

		dot->SetPos(pos.x, pos.y, 0.0f);
		if (MeasureDist(dot->GetPos(), radarMain->GetPos()) > 100.0f)
		{
			dot->SetDotShow(false);
		}
		else
		{
			dot->SetDotShow(true);
		}
	}
}

void Radar::SetCoinDot()
{
//	Scene* scene = Manager::GetScene();
//	std::vector<Coin*> CoinList = scene->GetGameObjects<Coin>(OBJ3D);
//	std::vector<RadarDot*> RadarDotList = scene->GetGameObjects<RadarDot>(OBJ2D);
//	for (Coin* coin : CoinList)
//	{
//		for (RadarDot* dot : RadarDotList)
//		{
//			if (dot->GetisUse() == false)
//			{
//				dot->SetMyCoin(coin);
//				coin->SetDot(dot);
//
//				dot->SetisUse(true);
//				break;
//			}
//		}
//	}
}
