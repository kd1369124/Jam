#pragma once

class Treasure : public KdGameObject
{
public:
	Treasure() {};
	~Treasure() {};

	void Init() override;
	void Update() override;
	void DrawLit() override;
	void SetModel(int Num);
	void HitOn() override;


	void SetPos(const Math::Vector3& _pos)override { m_pos = _pos;}
	void SetPosp(Math::Matrix _mat) { m_mWorld = _mat;}

	bool IsOpen() const { return OpenFlb; }
private:
	

	float TreasureRank = 0;

	float Scall=2.0f;
	bool HitFlg = false;
	Math::Vector3 m_pos;
	std::shared_ptr<KdPolygon> m_spPoly = nullptr;//ポリゴンデータ

	bool OpenFlb = false; //開いているかどうか
};
