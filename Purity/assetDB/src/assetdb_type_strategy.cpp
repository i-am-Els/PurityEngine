//
// Created by Eniola Olawale on 9/13/2024.
//

#include "assetdb_type_strategy.h"
#include "assets_types.h"

namespace purity::assetDB
{
    // Texture Strategy

    TextureAssetOperationStrategy::~TextureAssetOperationStrategy() {
        PLog::echoMessage("Destroying Texture Strategy.");
    }

    Ref<PTextureAsset> TextureAssetOperationStrategy::ReadOperation() {
        return Ref<PTextureAsset>();
    }

    Ref<PTextureAsset> TextureAssetOperationStrategy::WriteOperation() {
        return Ref<PTextureAsset>();
    }

    Ref<PTextureAsset> TextureAssetOperationStrategy::UpdateOperation() {
        return Ref<PTextureAsset>();
    }

    Ref<PTextureAsset> TextureAssetOperationStrategy::DeleteOperation() {
        return Ref<PTextureAsset>();
    }

    // Sprite Strategy

    SpriteAssetOperationStrategy::~SpriteAssetOperationStrategy() {
        PLog::echoMessage("Destroying Sprite Strategy.");
    }

    Ref<PSpriteAsset> SpriteAssetOperationStrategy::ReadOperation() {
        return Ref<PSpriteAsset>();
    }

    Ref<PSpriteAsset> SpriteAssetOperationStrategy::WriteOperation() {
        return Ref<PSpriteAsset>();
    }

    Ref<PSpriteAsset> SpriteAssetOperationStrategy::UpdateOperation() {
        return Ref<PSpriteAsset>();
    }

    Ref<PSpriteAsset> SpriteAssetOperationStrategy::DeleteOperation() {
        return Ref<PSpriteAsset>();
    }

    // Shader Strategy

    ShaderAssetOperationStrategy::~ShaderAssetOperationStrategy() {
        PLog::echoMessage("Destroying Shader Strategy.");
    }

    Ref<PShaderAsset> ShaderAssetOperationStrategy::ReadOperation() {
        return Ref<PShaderAsset>();
    }

    Ref<PShaderAsset> ShaderAssetOperationStrategy::WriteOperation() {
        return Ref<PShaderAsset>();
    }

    Ref<PShaderAsset> ShaderAssetOperationStrategy::UpdateOperation() {
        return Ref<PShaderAsset>();
    }

    Ref<PShaderAsset> ShaderAssetOperationStrategy::DeleteOperation() {
        return Ref<PShaderAsset>();
    }

    // Mesh Strategy

    MeshAssetOperationStrategy::~MeshAssetOperationStrategy() {
        PLog::echoMessage("Destroying Mesh Strategy.");
    }

    Ref<PMeshAsset> MeshAssetOperationStrategy::ReadOperation() {
        return Ref<PMeshAsset>();
    }

    Ref<PMeshAsset> MeshAssetOperationStrategy::WriteOperation() {
        return Ref<PMeshAsset>();
    }

    Ref<PMeshAsset> MeshAssetOperationStrategy::UpdateOperation() {
        return Ref<PMeshAsset>();
    }

    Ref<PMeshAsset> MeshAssetOperationStrategy::DeleteOperation() {
        return Ref<PMeshAsset>();
    }

    // Skeleton Strategy

    SkeletonAssetOperationStrategy::~SkeletonAssetOperationStrategy() {
        PLog::echoMessage("Destroying Skeleton Strategy.");
    }

    Ref<PSkeletonAsset> SkeletonAssetOperationStrategy::ReadOperation() {
        return Ref<PSkeletonAsset>();
    }

    Ref<PSkeletonAsset> SkeletonAssetOperationStrategy::WriteOperation() {
        return Ref<PSkeletonAsset>();
    }

    Ref<PSkeletonAsset> SkeletonAssetOperationStrategy::UpdateOperation() {
        return Ref<PSkeletonAsset>();
    }

    Ref<PSkeletonAsset> SkeletonAssetOperationStrategy::DeleteOperation() {
        return Ref<PSkeletonAsset>();
    }

    // StaticMesh Strategy

    StaticMeshAssetOperationStrategy::~StaticMeshAssetOperationStrategy() {
        PLog::echoMessage("Destroying Static Mesh Strategy.");
    }

    Ref<PStaticMeshAsset> StaticMeshAssetOperationStrategy::ReadOperation() {
        return Ref<PStaticMeshAsset>();
    }

    Ref<PStaticMeshAsset> StaticMeshAssetOperationStrategy::WriteOperation() {
        return Ref<PStaticMeshAsset>();
    }

    Ref<PStaticMeshAsset> StaticMeshAssetOperationStrategy::UpdateOperation() {
        return Ref<PStaticMeshAsset>();
    }

    Ref<PStaticMeshAsset> StaticMeshAssetOperationStrategy::DeleteOperation() {
        return Ref<PStaticMeshAsset>();
    }

    // Material Strategy

    MaterialAssetOperationStrategy::~MaterialAssetOperationStrategy() {
        PLog::echoMessage("Destroying Material Strategy.");
    }

    Ref<PMaterialAsset> MaterialAssetOperationStrategy::ReadOperation() {
        return Ref<PMaterialAsset>();
    }

    Ref<PMaterialAsset> MaterialAssetOperationStrategy::WriteOperation() {
        return Ref<PMaterialAsset>();
    }

    Ref<PMaterialAsset> MaterialAssetOperationStrategy::UpdateOperation() {
        return Ref<PMaterialAsset>();
    }

    Ref<PMaterialAsset> MaterialAssetOperationStrategy::DeleteOperation() {
        return Ref<PMaterialAsset>();
    }

    // Spline Strategy

    SplineAssetOperationStrategy::~SplineAssetOperationStrategy() {
        PLog::echoMessage("Destroying Spline Strategy.");
    }

    Ref<PSplineAsset> SplineAssetOperationStrategy::ReadOperation() {
        return Ref<PSplineAsset>();
    }

    Ref<PSplineAsset> SplineAssetOperationStrategy::WriteOperation() {
        return Ref<PSplineAsset>();
    }

    Ref<PSplineAsset> SplineAssetOperationStrategy::UpdateOperation() {
        return Ref<PSplineAsset>();
    }

    Ref<PSplineAsset> SplineAssetOperationStrategy::DeleteOperation() {
        return Ref<PSplineAsset>();
    }

    // P2DPolygonMesh Strategy

    P2DPolygonMeshAssetOperationStrategy::~P2DPolygonMeshAssetOperationStrategy() {
        PLog::echoMessage("Destroying 2DPolygon Strategy.");
    }

    Ref<PP2DPolygonMeshAsset> P2DPolygonMeshAssetOperationStrategy::ReadOperation() {
        return Ref<PP2DPolygonMeshAsset>();
    }

    Ref<PP2DPolygonMeshAsset> P2DPolygonMeshAssetOperationStrategy::WriteOperation() {
        return Ref<PP2DPolygonMeshAsset>();
    }

    Ref<PP2DPolygonMeshAsset> P2DPolygonMeshAssetOperationStrategy::UpdateOperation() {
        return Ref<PP2DPolygonMeshAsset>();
    }

    Ref<PP2DPolygonMeshAsset> P2DPolygonMeshAssetOperationStrategy::DeleteOperation() {
        return Ref<PP2DPolygonMeshAsset>();
    }

    // SoundSource Strategy

    SoundSourceAssetOperationStrategy::~SoundSourceAssetOperationStrategy() {
        PLog::echoMessage("Destroying Sound Strategy.");
    }

    Ref<PSoundSourceAsset> SoundSourceAssetOperationStrategy::ReadOperation() {
        return Ref<PSoundSourceAsset>();
    }

    Ref<PSoundSourceAsset> SoundSourceAssetOperationStrategy::WriteOperation() {
        return Ref<PSoundSourceAsset>();
    }

    Ref<PSoundSourceAsset> SoundSourceAssetOperationStrategy::UpdateOperation() {
        return Ref<PSoundSourceAsset>();
    }

    Ref<PSoundSourceAsset> SoundSourceAssetOperationStrategy::DeleteOperation() {
        return Ref<PSoundSourceAsset>();
    }

    // Level Strategy

    LevelAssetOperationStrategy::~LevelAssetOperationStrategy() {
        PLog::echoMessage("Destroying Level Strategy.");
    }

    Ref<PLevelAsset> LevelAssetOperationStrategy::ReadOperation() {
        return Ref<PLevelAsset>();
    }

    Ref<PLevelAsset> LevelAssetOperationStrategy::WriteOperation() {
        return Ref<PLevelAsset>();
    }

    Ref<PLevelAsset> LevelAssetOperationStrategy::UpdateOperation() {
        return Ref<PLevelAsset>();
    }

    Ref<PLevelAsset> LevelAssetOperationStrategy::DeleteOperation() {
        return Ref<PLevelAsset>();
    }

    // Particle Strategy

    ParticleAssetOperationStrategy::~ParticleAssetOperationStrategy() {
        PLog::echoMessage("Destroying Particle Strategy.");
    }

    Ref<PParticleAsset> ParticleAssetOperationStrategy::ReadOperation() {
        return Ref<PParticleAsset>();
    }

    Ref<PParticleAsset> ParticleAssetOperationStrategy::WriteOperation() {
        return Ref<PParticleAsset>();
    }

    Ref<PParticleAsset> ParticleAssetOperationStrategy::UpdateOperation() {
        return Ref<PParticleAsset>();
    }

    Ref<PParticleAsset> ParticleAssetOperationStrategy::DeleteOperation() {
        return Ref<PParticleAsset>();
    }

    // RenderMapAsset

    RenderMapAssetOperationStrategy::~RenderMapAssetOperationStrategy() {
        PLog::echoMessage("Destroying Render Map Strategy.");
    }

    Ref<PRenderMapAsset> RenderMapAssetOperationStrategy::ReadOperation() {
        return Ref<PRenderMapAsset>();
    }

    Ref<PRenderMapAsset> RenderMapAssetOperationStrategy::WriteOperation() {
        return Ref<PRenderMapAsset>();
    }

    Ref<PRenderMapAsset> RenderMapAssetOperationStrategy::UpdateOperation() {
        return Ref<PRenderMapAsset>();
    }

    Ref<PRenderMapAsset> RenderMapAssetOperationStrategy::DeleteOperation() {
        return Ref<PRenderMapAsset>();
    }

    P3DSoundSourceAssetOperationStrategy::~P3DSoundSourceAssetOperationStrategy()
    {
    }

    Ref<PP3DSoundSourceAsset> P3DSoundSourceAssetOperationStrategy::ReadOperation()
    {
        return Ref<PP3DSoundSourceAsset>();
    }

    Ref<PP3DSoundSourceAsset> P3DSoundSourceAssetOperationStrategy::WriteOperation()
    {
        return Ref<PP3DSoundSourceAsset>();
    }

    Ref<PP3DSoundSourceAsset> P3DSoundSourceAssetOperationStrategy::DeleteOperation()
    {
        return Ref<PP3DSoundSourceAsset>();
    }

    Ref<PP3DSoundSourceAsset> P3DSoundSourceAssetOperationStrategy::UpdateOperation()
    {
        return Ref<PP3DSoundSourceAsset>();
    }

}