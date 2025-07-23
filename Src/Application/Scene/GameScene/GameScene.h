#pragma once

#include"../BaseScene/BaseScene.h"
class Treasure;
class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

	void CreateTreasure(Math::Matrix _mat);

private:

	void Event() override;
	void Init()  override;

	friend class Steage01;

	std::shared_ptr<Steage01> steage01;

	std::shared_ptr<Treasure> m_Treasure; 
};
