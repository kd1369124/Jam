#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/Steage/SteageBase.h"
#include"../../GameObject/Treasure/Treasure.h"
#include"../../GameObject/Player/Player.h"
#include"../../GameObject/Camera/TopDownCamera/TopDownCamera.h"
#include"../../GameObject/Steage/Steage01/Steage01.h"
void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

}

void GameScene::Init()
{


	std::shared_ptr<Steage01> steage01 = std::make_shared<Steage01>();
	steage01->Init();
	m_objList.push_back(steage01);


	std::shared_ptr<SteageBase> steage = std::make_shared<SteageBase>();
	const auto& nodes = steage->SteageModelNodes("Asset/Models/Treasure/Test1.gltf");



	for (const auto& node : nodes)
	{
		if (node.m_name.rfind("Tresure", 0) == 0)
		{
			std::shared_ptr<Treasure> treasure;
			treasure = std::make_shared<Treasure>();
			treasure->Init();
			Math::Vector3 pos = node.m_worldTransform.Translation();

			treasure->SetPos(pos);
			m_objList.push_back(treasure);

		}
		else if (node.m_name == "Wall")
		{

		}
		else if (node.m_name == "SkyBox")
		{

		}
	}

	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	player->SetPos(Math::Vector3(0.0f, 0.0f, 0.0f));
	m_objList.push_back(player);

	std::shared_ptr<TopDownCamera> camera = std::make_shared<TopDownCamera>();
	camera->Init();
	AddObject(camera);

	camera->SetPlayer(player);


}
