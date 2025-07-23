#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/Steage/SteageBase.h"
#include"../../GameObject/Treasure/Treasure.h"


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
	std::shared_ptr<Treasure> treasure;
	std::shared_ptr<SteageBase> steage = std::make_shared<SteageBase>();
	const auto& nodes = steage->SteageModelNodes("Asset/Models/Treasure/Treasure3.gltf");
	for (const auto& node : nodes)
	{
		if (node.m_name == "Tresure")
		{
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
}
