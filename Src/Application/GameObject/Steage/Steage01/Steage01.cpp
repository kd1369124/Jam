#include "Steage01.h"
#include"../SteageBase.h"
#include"../../Treasure/Treasure.h"
#include"../../../Scene/SceneManager.h"
void Steage01::Init()
{
	if (!m_SteageModelData)
	{
		m_SteageModelData = std::make_shared<KdModelData>();
		m_SteageModelData->Load(SteageModelDataPath01);
	}
	const auto& nodes = m_SteageModelData->GetOriginalNodes();

	for (const auto& node : nodes)
	{
		if(node.m_name == "Tresure")
		{

			treasure = std::make_shared<Treasure>();
			treasure->Init();
			treasure->SetPosp(node.m_worldTransform);
			SceneManager::Instance().AddObject(treasure);

		}
		else if (node.m_name == "Wall")
		{
		
		}
		else if (node.m_name == "SkyBox")
		{
	
		}
	}
}

void Steage01::Update()
{

}

void Steage01::DrawUnLit()
{
	if (!m_SteageModelData)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_SteageModelData, m_mWorld);
}
