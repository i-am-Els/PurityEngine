//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once
#include "handle_base.h"
#include "core_macros.h"
#include "ref_counted.h"
#include "assets_types.h"

using namespace purity::fileIO;

namespace purity::assetDB
{
    template<class AssetTypeRef>
    class PURITY_API AssetOperationStrategy
    {
    public:
        virtual ~AssetOperationStrategy() = default;
        virtual Ref<AssetTypeRef> ReadOperation() = 0;
        virtual Ref<AssetTypeRef> WriteOperation() = 0;
        virtual Ref<AssetTypeRef> UpdateOperation() = 0;
        virtual Ref<AssetTypeRef> DeleteOperation() = 0;
    };

    class PURITY_API TextureAssetOperationStrategy final : public AssetOperationStrategy<PTextureAsset>
    {
    public:
        ~TextureAssetOperationStrategy() override;
        Ref<PTextureAsset> ReadOperation() override;
        Ref<PTextureAsset> WriteOperation() override;
        Ref<PTextureAsset> UpdateOperation() override;
        Ref<PTextureAsset> DeleteOperation() override;
    };

    class PURITY_API SpriteAssetOperationStrategy final : public AssetOperationStrategy<PSpriteAsset>
    {
    public:
        ~SpriteAssetOperationStrategy() override;
        Ref<PSpriteAsset> ReadOperation() override;
        Ref<PSpriteAsset> WriteOperation() override;
        Ref<PSpriteAsset> UpdateOperation() override;
        Ref<PSpriteAsset> DeleteOperation() override;
    };

    class PURITY_API ShaderAssetOperationStrategy final : public AssetOperationStrategy<PShaderAsset>
    {
        ~ShaderAssetOperationStrategy() override;
        Ref<PShaderAsset> ReadOperation() override;
        Ref<PShaderAsset> WriteOperation() override;
        Ref<PShaderAsset> UpdateOperation() override;
        Ref<PShaderAsset> DeleteOperation() override;
    };

    class PURITY_API MeshAssetOperationStrategy final : public AssetOperationStrategy<PMeshAsset>
    {
        ~MeshAssetOperationStrategy() override;
        Ref<PMeshAsset> ReadOperation() override;
        Ref<PMeshAsset> WriteOperation() override;
        Ref<PMeshAsset> UpdateOperation() override;
        Ref<PMeshAsset> DeleteOperation() override;
    };

    class PURITY_API SkeletonAssetOperationStrategy final : public AssetOperationStrategy<PSkeletonAsset>
    {
        ~SkeletonAssetOperationStrategy() override;
        Ref<PSkeletonAsset> ReadOperation() override;
        Ref<PSkeletonAsset> WriteOperation() override;
        Ref<PSkeletonAsset> UpdateOperation() override;
        Ref<PSkeletonAsset> DeleteOperation() override;
    };

    class PURITY_API StaticMeshAssetOperationStrategy final : public AssetOperationStrategy<PStaticMeshAsset>
    {
        ~StaticMeshAssetOperationStrategy() override;
        Ref<PStaticMeshAsset> ReadOperation() override;
        Ref<PStaticMeshAsset> WriteOperation() override;
        Ref<PStaticMeshAsset> UpdateOperation() override;
        Ref<PStaticMeshAsset> DeleteOperation() override;
    };

    class PURITY_API MaterialAssetOperationStrategy final : public AssetOperationStrategy<PMaterialAsset>
    {
    public:
        ~MaterialAssetOperationStrategy() override;
        Ref<PMaterialAsset> ReadOperation() override;
        Ref<PMaterialAsset> WriteOperation() override;
        Ref<PMaterialAsset> UpdateOperation() override;
        Ref<PMaterialAsset> DeleteOperation() override;
    };

    class PURITY_API SplineAssetOperationStrategy final : public AssetOperationStrategy<PSplineAsset>
    {
    public:
        ~SplineAssetOperationStrategy() override;
        Ref<PSplineAsset> ReadOperation() override;
        Ref<PSplineAsset> WriteOperation() override;
        Ref<PSplineAsset> UpdateOperation() override;
        Ref<PSplineAsset> DeleteOperation() override;
    };

    class PURITY_API P2DPolygonMeshAssetOperationStrategy final : public AssetOperationStrategy<PP2DPolygonMeshAsset>
    {
    public:
        ~P2DPolygonMeshAssetOperationStrategy() override;
        Ref<PP2DPolygonMeshAsset> ReadOperation() override;
        Ref<PP2DPolygonMeshAsset> WriteOperation() override;
        Ref<PP2DPolygonMeshAsset> UpdateOperation() override;
        Ref<PP2DPolygonMeshAsset> DeleteOperation() override;
    };

    class PURITY_API SoundSourceAssetOperationStrategy final : public AssetOperationStrategy<PSoundSourceAsset>
    {
    public:
        ~SoundSourceAssetOperationStrategy() override;
        Ref<PSoundSourceAsset> ReadOperation() override;
        Ref<PSoundSourceAsset> WriteOperation() override;
        Ref<PSoundSourceAsset> UpdateOperation() override;
        Ref<PSoundSourceAsset> DeleteOperation() override;
    };

     class PURITY_API P3DSoundSourceAssetOperationStrategy final : public AssetOperationStrategy<PP3DSoundSourceAsset>
     {
     public:
         ~P3DSoundSourceAssetOperationStrategy() override;
         Ref<PP3DSoundSourceAsset> ReadOperation() override;
         Ref<PP3DSoundSourceAsset> WriteOperation() override;
         Ref<PP3DSoundSourceAsset> UpdateOperation() override;
         Ref<PP3DSoundSourceAsset> DeleteOperation() override;
     };

    class PURITY_API LevelAssetOperationStrategy final : public AssetOperationStrategy<PLevelAsset>
    {
    public:
        ~LevelAssetOperationStrategy() override;
        Ref<PLevelAsset> ReadOperation() override;
        Ref<PLevelAsset> WriteOperation() override;
        Ref<PLevelAsset> UpdateOperation() override;
        Ref<PLevelAsset> DeleteOperation() override;
    };

    class PURITY_API ParticleAssetOperationStrategy final : public AssetOperationStrategy<PParticleAsset>
    {
    public:
        ~ParticleAssetOperationStrategy() override;
        Ref<PParticleAsset> ReadOperation() override;
        Ref<PParticleAsset> WriteOperation() override;
        Ref<PParticleAsset> UpdateOperation() override;
        Ref<PParticleAsset> DeleteOperation() override;
    };

    class PURITY_API RenderMapAssetOperationStrategy final : public AssetOperationStrategy<PRenderMapAsset>
    {
    public:
        ~RenderMapAssetOperationStrategy() override;
        Ref<PRenderMapAsset> ReadOperation() override;
        Ref<PRenderMapAsset> WriteOperation() override;
        Ref<PRenderMapAsset> UpdateOperation() override;
        Ref<PRenderMapAsset> DeleteOperation() override;
    };

}
