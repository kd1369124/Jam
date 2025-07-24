#include "Treasure.h"
#include"../../Scene/SceneManager.h"
void Treasure::Init()
{
	m_spPoly = std::make_shared<KdPolygon>();
	// 四角形の2トライアングル分の頂点
	std::vector<KdPolygon::Vertex> verts(6);

	// 頂点設定
	verts[0].pos = { -0.5f, -0.5f, 0 }; verts[0].UV = { 0, 1 };
	verts[1].pos = { -0.5f,  0.5f, 0 }; verts[1].UV = { 0, 0 };
	verts[2].pos = { 0.5f,  0.5f, 0 }; verts[2].UV = { 1, 0 };

	verts[3].pos = { -0.5f, -0.5f, 0 }; verts[3].UV = { 0, 1 };
	verts[4].pos = { 0.5f,  0.5f, 0 }; verts[4].UV = { 1, 0 };
	verts[5].pos = { 0.5f, -0.5f, 0 }; verts[5].UV = { 1, 1 };

	m_spPoly->SetVertices(verts); // Setter を使用

	m_spPoly->SetMaterial("Asset/Textures/Treasure/oukann.png");
	HitFlg = false;
	m_pCollider = std::make_unique<KdCollider>();
	if (m_pCollider)
	{
		m_pCollider->RegisterCollisionShape("ground", m_spPoly, KdCollider::TypeEvent);

	}
}

void Treasure::Update()
{
	/*if (GetAsyncKeyState('A')&0x80000)
	{
		HitOn();
	}*/


	if (Scall < 10 && HitFlg)
	{
		Scall += 0.1f;
		m_pos.y += 0.1f;
	}
	Math::Matrix scal = Math::Matrix::CreateScale(Scall);
	Math::Matrix rollX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	Math::Matrix transu = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scal * rollX * transu;
}

void Treasure::DrawLit()
{
	if (HitFlg)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
	
	}
}

void Treasure::SetModel(int Num)
{

	switch (Num)
	{
	case 0:
		m_spPoly->SetMaterial("Asset/Textures/Treasure/oukann.png");
		break;
	case 1:
		m_spPoly->SetMaterial("Asset/Textures/Treasure/oukann.png");
		break;
	case 2:
		m_spPoly->SetMaterial("Asset/Textures/Treasure/oukann.png");
		break;
	case 3:
		m_spPoly->SetMaterial("Asset/Textures/Treasure/oukann.png");
		break;
	default:
		m_spPoly->SetMaterial("Asset/Textures/Treasure/oukann.png");
		break;
	}
	TreasureRank = Num;
}

void Treasure::HitOn()
{
	if (!HitFlg)
	{
		HitFlg = true;
		SceneManager::Instance().AddScore(10);
		m_isExpired = true; // Treasureを消す
	}
}
