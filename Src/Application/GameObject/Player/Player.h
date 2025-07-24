#pragma once

// テスト用
struct TreasureBox
{
	Math::Vector3 position;  // 宝箱の位置
	bool isOpened = false;   // 開封済みかどうか

	TreasureBox(const Math::Vector3& pos) : position(pos) {}
};

class Player : public KdGameObject
{
public:

	Player() {}
	~Player() override {}

	void Init()	override;
	void Update()	override;
	void DrawLit()	override;


	void GetItemFromTreasure(); // 宝箱からアイテムを取得する処理

private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;

	float m_angle = 0;          
	Math::Vector3 m_pos = Math::Vector3::Zero;
};