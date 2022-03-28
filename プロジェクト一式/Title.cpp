#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Title.h"
#include "TitleLogo.h"
#include "Fade.h"
#include "Input.h"
#include "Tutorial.h"
#include "GameScene.h"

void Title::Init()
{
	Scene* scene = Manager::GetScene();

	AddGameObject<TitleLogo>(OBJ2D);
	m_Fade = scene->AddGameObject<Fade>(OBJ2D);

	RECT rc;
	GetWindowRect(GetWindow(), &rc);
	SetCursorPos(rc.left, rc.top);
	ShowCursor(false);

	//�J�[�\���͈͎w��
	POINT p;
	GetCursorPos(&p);

	rc.left = p.x + 10;
	rc.top = p.y + 35;						// �������Y���W
	rc.right = p.x + SCREEN_WIDTH - 5;		// �E������X���W
	rc.bottom = p.y + SCREEN_HEIGHT;      // �E������Y���W
	ClipCursor(&rc);
}

void Title::UnInit()
{
	Scene::UnInit();//�p����
}

void Title::Update()
{
	Scene::Update();

	Scene* scene = Manager::GetScene();

	if (Keyboard_IsPress(DIK_RETURN) || Keyboard_IsPress(DIK_SPACE))
	{
		m_Fade->SetFadeEnd(false);
		m_Fade->SetFade(true);
		m_Fade->SetFadeOut(true, 0.0f);
	}
	if (m_Fade->GetFadeStart() == true)
	{
		if (m_Fade->GetFadeEnd() == true)
		{
			m_Fade->SetFadeEnd(false);
			//Manager::SetScene<Tutorial>();
			Manager::SetScene<GameScene>();
		}
	}
}