#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GameScene.h"
#include "Camera.h"
#include "Field.h"
#include "MeshField.h"
#include "model.h"
#include "Player.h"
#include "polygon2D.h"
#include "audio.h"
#include "Radar.h"
#include "DebugSystem.h"
#include "OBB.h"
#include "Fade.h"
#include "Building.h"
#include "WireTarget.h"
#include "Wire.h"
#include "Coin.h"
#include "Score.h"
#include "Result.h"
#include "DebugForwardRay.h"
#include "WireUI.h"

void GameScene::Init()
{
	OBB::Load();

	Building::Load();

	Coin::Load();

	Scene* scene = Manager::GetScene();

	AddGameObject<Camera>(SYSTEM);
	AddGameObject<DebugSystem>(SYSTEM);

	AddGameObject<MeshField>(OBJ3D);	
	
	int size;
	FILE* fp;
	fp = fopen("asset/ObjectData.txt", "r");            //ファイル読み込み
	fscanf(fp, "%d", &size);
	for (int i = 0; i < size; i++)
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int t;
		fscanf(fp, "%f,%f,%f", &pos.x, &pos.y, &pos.z);
		fscanf(fp, "%f,%f,%f", &rot.x, &rot.y, &rot.z);
		fscanf(fp, "%d", &t);
		AddGameObject<Building>(OBJ3D)->CreateBldg(pos, rot, static_cast<BldgType>(t));
	}

	fscanf(fp, "%d", &size);
	for (int i = 0; i < size; i++) 
	{
		D3DXVECTOR3 pos;
		fscanf(fp, "%f,%f,%f", &pos.x, &pos.y, &pos.z);
		AddGameObject<Coin>(OBJ3D)->SetPos(pos.x, pos.y, pos.z);
	}

	fclose(fp);

	/*AddGameObject<Building>(OBJ3D)->SetPos(-3.0f, 0.0f, 6.0f);
	AddGameObject<Coin>(OBJ3D)->SetPos(-3.0f, 10.0f, 6.0f);

	AddGameObject<Building>(OBJ3D)->SetPos(18.0f, 0.0f, 6.0f);
	AddGameObject<Coin>(OBJ3D)->SetPos(18.0f, 10.0f, 6.0f);

	AddGameObject<Building>(OBJ3D)->SetPos(-43.0f, 0.0f, 30.0f);
	AddGameObject<Coin>(OBJ3D)->SetPos(-43.0f, 10.0f, 30.0f);*/

	AddGameObject<MeshField>(OBJ3D);

	AddGameObject<Player>(OBJ3D);

	AddGameObject<WireTarget>(OBJ3D);

	AddGameObject<DebugForwardRay>(OBJ3D);

	AddGameObject<Wire>(OBJ3D);

	AddGameObject<Radar>(OBJ2D);

	AddGameObject<Score>(OBJ2D);

	AddGameObject<WireUI>(OBJ2D);

	Audio* bgm = AddGameObject<Audio>(SYSTEM);
	bgm->Load("asset\\audio\\Select.wav");
	//bgm->Play(true);

	m_Fade = scene->AddGameObject<Fade>(OBJ2D);

	m_Fade->SetFade(true);
	m_Fade->SetFadeIn(true, 1.0f);

	//RECT rc;
	//GetWindowRect(GetWindow(), &rc);
	//SetCursorPos(rc.left, rc.top);
	//ShowCursor(false);

	////カーソル範囲指定
	//POINT p;
	//GetCursorPos(&p);

	//rc.left = p.x + 10;
	//rc.top = p.y + 35;						// 左上隅のY座標
	//rc.right = p.x + SCREEN_WIDTH - 5;		// 右下隅のX座標
	//rc.bottom = p.y + SCREEN_HEIGHT + 15;      // 右下隅のY座標
	//ClipCursor(&rc);
}

void GameScene::UnInit()
{
	Scene::UnInit();//継承元

	OBB::UnLoad();

	Building::UnLoad();

	Coin::UnLoad();
}

void GameScene::Update()
{
	Scene::Update();

	Scene* scene = Manager::GetScene();
	Score* score = scene->GetGameObject<Score>(OBJ3D);
	DebugSystem* d = scene->GetGameObject<DebugSystem>(SYSTEM);

	if (d->GetDebug() == false)
	{
		std::vector<Coin*> coinList = scene->GetGameObjects<Coin>(OBJ3D);
		int count = coinList.size();

		if (count == 0 && m_Fade->GetFadeUse() == false && m_Fade->GetFadeEnd() == true && Keyboard_IsTrigger(DIK_L))
		{
			if (m_Fade->GetFadeStart() == false)
			{
				m_Fade->SetFade(true);
			}
			m_Fade->SetFadeOut(true, 0.0f);
		}

		if (m_Fade->GetFadeOut() == true && m_Fade->GetFadeUse() == false)
		{
			Manager::SetScene<Result>();
		}
	}
}

