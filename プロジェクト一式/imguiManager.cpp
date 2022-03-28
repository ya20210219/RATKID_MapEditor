#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

#include <tchar.h>
#include "DebugSystem.h"
#include "Scene.h"
#include "player.h"
#include "Building.h"
#include "Coin.h"
#include "Radar.h"
#include "Camera.h"
#include "OBB.h"
#include "imguiManager.h"
#include "WireTarget.h"
#include "MeshField.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


ID3D11Device* imguiManager::m_pd3dDevice = NULL;
ID3D11DeviceContext* imguiManager::m_pd3dDeviceContext = NULL;
IDXGISwapChain* imguiManager::m_pSwapChain = NULL;
ID3D11RenderTargetView* imguiManager::m_mainRenderTargetView = NULL;

float editPosx = 0.0f;
float editPosy = 0.0f;
float editPosz = 0.0f;

float editRotx = 0.0f;
float editRoty = 0.0f;
float editRotz = 0.0f;

void imguiManager::Init()
{
	m_pd3dDevice = Renderer::GetDevice();
	m_pd3dDeviceContext = Renderer::GetDeviceContext();
	m_mainRenderTargetView = Renderer::GetRenderTargetView();
	m_pSwapChain = Renderer::GetSwapChain();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	HWND window = GetWindow();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(m_pd3dDevice, m_pd3dDeviceContext);
}

void imguiManager::Update()
{
}

void imguiManager::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void imguiManager::Draw()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

	Scene* scene = Manager::GetScene();
	DebugSystem* d = scene->GetGameObject<DebugSystem>(SYSTEM);
	WireTarget* wt = scene->GetGameObject<WireTarget>(OBJ3D);
	bool show;
	if (d != nullptr)
	{
		show = d->GetDebug();
	}
	else
	{
		show = false;
	}

	if (show == true)
	{
		if (ImGui::Begin("debug", &show))
		{
			ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_Once);
			ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Once);

			ImGui::Text("Application average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
			ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
			if (ImGui::Button("BldgSpawn1"))
			{
				scene->AddGameObject<Building>(OBJ3D)->CreateBldg(wt->GetPos(), D3DXVECTOR3(0.0f,0.0f,0.0f), static_cast<BldgType>(0));
				return;														 
			}																 
			if (ImGui::Button("BldgSpawn2"))						 
			{																 
				scene->AddGameObject<Building>(OBJ3D)->CreateBldg(wt->GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), LARGE);
				return;														  
			}																  
			if (ImGui::Button("HugeSpawn1"))								  
			{																  
				scene->AddGameObject<Building>(OBJ3D)->CreateBldg(wt->GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), HOUSE);
				return;
			}
			
			if (ImGui::Button("Quit"))
			{
				d->SetDebug(false);
				return;
			}

			ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 200), ImGuiWindowFlags_NoTitleBar);
			MeshField* meshfield = scene->GetGameObject<MeshField>(OBJ3D);
			std::vector<D3DXVECTOR2> List = meshfield->Getdata();

			ImGui::Text("x = %f   z = %f", meshfield->GetMinPos().x, meshfield->GetMinPos().y);
			ImGui::Text("x = %f   z = %f", meshfield->GetMaxPos().x, meshfield->GetMaxPos().y);

			for (D3DXVECTOR2 v : List)
			{
				ImGui::Text("x = %f   z = %f", v.x, v.y);
			}
			ImGui::EndChild();
		}

		if (ImGui::Begin("PlayerStatus", &show))
		{
			ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
			ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Once);
			Scene* scene = Manager::GetScene();
			Player* player = scene->GetGameObject<Player>(OBJ3D);

			ImGui::Text("Player");
			ImGui::Text("X = %f\nY = %f\nZ = %f\n", player->GetPos().x, player->GetPos().y, player->GetPos().z);
			ImGui::Text("m_isFly = %s\nm_isCol = %s\nm_isGravity = %s", (player->GetisFly() ? "true" : "false"),
				(player->GetisCol() ? "true" : "false"),
				(player->GetisGravity() ? "true" : "false"));
			ImGui::Text("AniTypeNum = %d", player->GetAniType());
		}

		if (ImGui::Begin("CameraStatus", &show))
		{
			ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
			ImGui::SetNextWindowPos(ImVec2(250, 20), ImGuiCond_Once);
			Scene* scene = Manager::GetScene();
			Camera* cam = scene->GetGameObject<Camera>(SYSTEM);

			ImGui::Text("CameraRot");
			ImGui::Text("X = %f\nY = %f\nZ = %f\n", cam->GetRot().x, cam->GetRot().y, cam->GetRot().z);
			ImGui::Text("MoveX = %f\nMoveY = %f\nMoveZ = %f\n", cam->GetCamMove().x, cam->GetCamMove().y, cam->GetCamMove().z);
			ImGui::Text("Reverse = %s", (cam->GetCamReverse() ? "true" : "false"));
		}

		ImGui::End();

		if (ImGui::Begin("BldgStatus", &show))
		{
			ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(300, 200), ImGuiWindowFlags_NoTitleBar);
			std::vector<Building*> BuildingList = scene->GetGameObjects<Building>(OBJ3D);

			for (Building* bldg : BuildingList)
			{
				ImGui::Text("X = %f\nY = %f\nZ = %f\n", bldg->GetPos().x, bldg->GetPos().y, bldg->GetPos().z);
				ImGui::Text("RoofTop = %f", bldg->GetPos().y + bldg->GetOBB()->GetLen_W(1));			

				if (bldg->GetEdit())
				{
					if (Keyboard_IsTrigger(DIK_G))
					{
						editPosx = bldg->GetOldPos().x;
						editPosy = bldg->GetOldPos().y - bldg->GetOBB()->GetLen_W(1);
						editPosz = bldg->GetOldPos().z;

						editRotx = bldg->GetOldRot().x;
						editRoty = bldg->GetOldRot().y;
						editRotz = bldg->GetOldRot().z;
					}

					ImGui::SliderFloat("Edit posX", &editPosx, -100.0f, 100.0f);
					ImGui::SliderFloat("Edit posZ", &editPosz, -100.0f, 100.0f);

					bldg->SetPos(editPosx, editPosy + bldg->GetOBB()->GetLen_W(1), editPosz);

					ImGui::SliderFloat("Edit RotX", &editRotx, -10.0f, 10.0f);
					ImGui::SliderFloat("Edit RotY", &editRoty, -10.0f, 10.0f);
					ImGui::SliderFloat("Edit RotZ", &editRotz, -10.0f, 10.0f);

					bldg->SetRot(editRotx, editRoty, editRotz);

					if (ImGui::Button("Delete"))
					{
						bldg->SetDestroy();
						d->SetEditP(false);
						return;
					}


					if (ImGui::Button("EndEdit"))
					{
						bldg->SetOldPos(bldg->GetPos());
						bldg->SetEdit(false);
						d->SetEditP(false);
						return;
					}

					if (ImGui::Button("AddCoin"))
					{
						Scene* scene = Manager::GetScene();
						scene->AddGameObject<Coin>(OBJ3D)->SetPos(bldg->GetPos().x, 
																  bldg->GetPos().y + bldg->GetOBB()->GetLen_W(1) + 0.5f, 
																  bldg->GetPos().z);
					}
				}
			}
			ImGui::EndChild();
		}

		if (ImGui::Begin("CoinStatus", &show))
		{
			ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 200), ImGuiWindowFlags_NoTitleBar);
			std::vector<Coin*> CoinList = scene->GetGameObjects<Coin>(OBJ3D);

			for (Coin* coin : CoinList)
			{
				ImGui::Text("X = %f\nY = %f\nZ = %f\n", coin->GetPos().x, coin->GetPos().y, coin->GetPos().z);
			}
			ImGui::EndChild();
		}

		if (ImGui::Begin("RadarDotStatus", &show))
		{
			ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 200), ImGuiWindowFlags_NoTitleBar);
			std::vector<RadarDot*> RadarDotList = scene->GetGameObjects<RadarDot>(OBJ2D);

			for (RadarDot* dot : RadarDotList)
			{
				ImGui::Text("X = %f\nY = %f\nZ = %f\n", dot->GetPos().x, dot->GetPos().y, dot->GetPos().z);
			}
			ImGui::EndChild();

		}

		if (ImGui::Begin("SaveObjectData", &show))
		{
			ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
			ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Once);

			if (ImGui::Button("Save"))
			{				
				FILE *fp;
				fp = fopen("asset/ObjectData.txt", "w");
				Scene* scene = Manager::GetScene();
				MeshField* meshfield = scene->GetGameObject<MeshField>(OBJ3D);
				std::vector<Building*> BuildingList = scene->GetGameObjects<Building>(OBJ3D);
				std::vector<Coin*> CoinList = scene->GetGameObjects<Coin>(OBJ3D);

				//meshfield->SaveData(fp);

				fprintf(fp, "%d", BuildingList.size());
				fprintf(fp, "\n");

				for (Building* bldg : BuildingList)
				{
					bldg->SaveData(fp);
				}

				fprintf(fp, "%d", CoinList.size());
				fprintf(fp, "\n");

				for (Coin* coin : CoinList)
				{
					coin->SaveData(fp);
				}

				fclose(fp);
			}
		}
		if (ImGui::Begin("DestroyCoin", &show))
		{
			if (ImGui::Button("DESTROOOOY"))
			{
				Scene* scene = Manager::GetScene();
				std::vector<RadarDot*> RadarDotList = scene->GetGameObjects<RadarDot>(OBJ2D);
				std::vector<Coin*> CoinList = scene->GetGameObjects<Coin>(OBJ3D);
				for (Coin* coin : CoinList)
				{
					coin->SetDestroy();
				}
				for (RadarDot* dot : RadarDotList)
				{
					dot->SetDestroy();
				}
			}
		}

		ImGui::End();

		// Rendering
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}
