#include "TopDownCamera.h"
#include"../../../GameObject/Player/Player.h"

void TopDownCamera::Init()
{
	CameraBase::Init();
}

void TopDownCamera::Update()
{
	Math::Vector3 camPos = { 0, 40, 0 };

	Math::Matrix rotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));

	Math::Matrix translation = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());

	m_mWorld = rotationX * translation;

	m_spCamera->SetCameraMatrix(m_mWorld);
}


