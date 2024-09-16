//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once
#include "handle_base.h"

namespace pnt::assetDB
{

    class AssetOperationStrategy
    {
    public:
        virtual ~AssetOperationStrategy() = default;
        virtual PHandleBase* ReadOperation() = 0;
        virtual PHandleBase* WriteOperation() = 0;
        virtual PHandleBase* UpdateOperation() = 0;
        virtual PHandleBase* DeleteOperation() = 0;
    };

    class TextureAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~TextureAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class SpriteAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~SpriteAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class ShaderAssetOperationStrategy final : public AssetOperationStrategy
    {
        ~ShaderAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class MeshAssetOperationStrategy final : public AssetOperationStrategy
    {
        ~MeshAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class SkeletonAssetOperationStrategy final : public AssetOperationStrategy
    {
        ~SkeletonAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class StaticMeshAssetOperationStrategy final : public AssetOperationStrategy
    {
        ~StaticMeshAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class MaterialAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~MaterialAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class SplineAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~SplineAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class P2DPolygonMeshAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~P2DPolygonMeshAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class SoundSourceAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~SoundSourceAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    // class P3DSoundSourceAssetOperationStrategy final : public AssetOperationStrategy
    // {
    // public:
    //     ~P3DSoundSourceAssetOperationStrategy() override;
    //     PHandleBase* ReadOperation() override;
    //     PHandleBase* WriteOperation() override;
    //     PHandleBase* UpdateOperation() override;
    //     PHandleBase* DeleteOperation() override;
    // };

    class LevelAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~LevelAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class ParticleAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~ParticleAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };

    class RenderMapAssetOperationStrategy final : public AssetOperationStrategy
    {
    public:
        ~RenderMapAssetOperationStrategy() override;
        PHandleBase* ReadOperation() override;
        PHandleBase* WriteOperation() override;
        PHandleBase* UpdateOperation() override;
        PHandleBase* DeleteOperation() override;
    };



}
