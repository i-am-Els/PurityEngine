//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once
#include "handle_base.h"
#include "core_macros.h"

namespace pnt::assetDB
{

    class PNT_API AssetOperationStrategy
    {
    public:
        virtual ~AssetOperationStrategy() = default;
        virtual PHandleBase* ReadOperation() = 0;
        virtual PHandleBase* WriteOperation() = 0;
        virtual PHandleBase* UpdateOperation() = 0;
        virtual PHandleBase* DeleteOperation() = 0;
    };

    class PNT_API TextureAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~TextureAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API SpriteAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~SpriteAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API ShaderAssetOperationStrategy final : public AssetOperationStrategy
    {
        ~ShaderAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API MeshAssetOperationStrategy final : public AssetOperationStrategy
    {
        ~MeshAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API SkeletonAssetOperationStrategy final : public AssetOperationStrategy
    {
        ~SkeletonAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API StaticMeshAssetOperationStrategy final : public AssetOperationStrategy
    {
        ~StaticMeshAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API MaterialAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~MaterialAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API SplineAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~SplineAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API P2DPolygonMeshAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~P2DPolygonMeshAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API SoundSourceAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~SoundSourceAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    // class PNT_API P3DSoundSourceAssetOperationStrategy final : public AssetOperationStrategy
    // {
    // public:
    //     ~P3DSoundSourceAssetOperationStrategy() override;
    //     PHandleBase* ReadOperation() override;
    //     PHandleBase* WriteOperation() override;
    //     PHandleBase* UpdateOperation() override;
    //     PHandleBase* DeleteOperation() override;
    // };

    class PNT_API LevelAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~LevelAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API ParticleAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~ParticleAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class PNT_API RenderMapAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~RenderMapAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };



}
