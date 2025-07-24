#pragma once
#include"../CameraBase.h"

class Player;

class TopDownCamera : public CameraBase
{
public:
	TopDownCamera(){}
	~TopDownCamera()override {}

	void Init()override;
	void Update()override;

	void SetPlayer(std::shared_ptr<Player> player) { m_player = player; }

private:

	std::shared_ptr<Player> m_player;
};