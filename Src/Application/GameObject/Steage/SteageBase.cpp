#include "SteageBase.h"

std::vector<KdModelData::Node> SteageBase::SteageModelNodes(std::string filepath)
{

	if (!m_SteageModelData)
	{
		m_SteageModelData = std::make_shared<KdModelData>();
		m_SteageModelData->Load(filepath);
	}
	auto modelData = m_SteageModelData->GetOriginalNodes();
	return modelData;
}
