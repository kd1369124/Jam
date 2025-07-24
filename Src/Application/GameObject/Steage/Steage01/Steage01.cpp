#include "Steage01.h"
#include"../SteageBase.h"
#include"../../Treasure/Treasure.h"
#include"../../../Scene/SceneManager.h"
void Steage01::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Ground.gltf");

	m_mWorld = Math::Matrix::CreateScale(50.0f);
}


void Steage01::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
