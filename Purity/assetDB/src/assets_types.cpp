//
// Created by Eniola Olawale on 9/16/2024.
//

#include "assets_types.h"
#include "scene.h"

namespace purity::assetDB
{
	void PTextureAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
		ar(cereal::make_nvp("tex_type", type));
	}

	void PTextureAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PSpriteAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PSpriteAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PShaderAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PShaderAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PMeshAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PMeshAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PSkeletonAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PSkeletonAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PStaticMeshAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PStaticMeshAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PMaterialAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PMaterialAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PSplineAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PSplineAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PP2DPolygonMeshAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PP2DPolygonMeshAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PSoundSourceAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PSoundSourceAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PP3DSoundSourceAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PP3DSoundSourceAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PLevelAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
		// if (!m_scene) return;
		//
		// ar(cereal::make_nvp("SceneName", m_scene->getName()));
		// ar(cereal::make_nvp("Version", m_scene->getVersion()));
		// ar(cereal::make_nvp("NodeCount", m_scene->GetNodeCount()));
		//
		// for (size_t i = 0; i < m_scene->GetNodeCount(); ++i)
		// {
		// 	const auto& node = m_scene->GetNode(i);
		// 	ar(cereal::make_nvp("Node_" + std::to_string(i), node));
		// }
	}

	void PLevelAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
		// if (!m_scene)
		// 	return; // Scene should exist
		//
		// std::string sceneName;
		// int version;
		// size_t nodeCount;
		//
		// ar(cereal::make_nvp("SceneName", sceneName));
		// ar(cereal::make_nvp("Version", version));
		// ar(cereal::make_nvp("NodeCount", nodeCount));
		//
		// m_scene->setName(sceneName);
		// m_scene->SetVersion(version);
		// m_scene->ResizeNodeContainer(nodeCount);
		//
		// for (size_t i = 0; i < nodeCount; ++i)
		// {
		// 	SceneNode node;
		// 	ar(cereal::make_nvp("Node_" + std::to_string(i), node));
		// 	m_scene->SetNode(i, std::move(node));
		// }
	}

	void PParticleAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PParticleAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PRenderMapAsset::Serialize(cereal::JSONOutputArchive& ar) const
	{
	}

	void PRenderMapAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
	}

	void PProjectAsset::Serialize(cereal::JSONOutputArchive& ar) const 
	{
		ar(CEREAL_NVP(projectDB), CEREAL_NVP(project_name), CEREAL_NVP(start_up_scene));
	}

	void PProjectAsset::Deserialize(cereal::JSONInputArchive& ar)
	{
		ar(CEREAL_NVP(projectDB), CEREAL_NVP(project_name), CEREAL_NVP(start_up_scene));
	}
}

CEREAL_REGISTER_TYPE(purity::assetDB::PTextureAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PSpriteAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PShaderAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PMeshAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PSkeletonAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PStaticMeshAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PMaterialAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PSplineAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PP2DPolygonMeshAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PSoundSourceAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PP3DSoundSourceAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PLevelAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PParticleAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PRenderMapAsset)
CEREAL_REGISTER_TYPE(purity::assetDB::PProjectAsset)

//CEREAL_REGISTER_POLYMORPHIC_RELATION(purity::assetDB::PAsset, purity::assetDB::PTextureAsset)