#pragma once
#include"../SteageBase.h"
class Treasure;
class Steage01 : public SteageBase
{
public:
	Steage01() {}
	~Steage01() override {}

	void Init() override;

	void DrawUnLit() override;

private:
	std::shared_ptr<KdModelData> m_model = nullptr;

};
