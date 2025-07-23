#pragma once
namespace
{
	// CSVのファイルパスをここに書く
	std::string SteageModelDataPath01 = "Asset/Models/Treasure/Treasure3.gltf";
}
class SteageBase : public KdGameObject
{
public:
	SteageBase() {}
	virtual ~SteageBase()override {}

	virtual void Init() override{}

	virtual void DrawUnLit() override{}

	virtual void Update() override {}



	std::vector<KdModelData::Node> SteageModelNodes(std::string filepath);


protected:

	std::shared_ptr<KdModelData> m_SteageModelData = nullptr;




};
