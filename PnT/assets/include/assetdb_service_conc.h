//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "service_base.h"
#include "handle_base.h"
#include "assetdb_enums.h"
#include "assetdb_service.h"
#include "assetdb_query_specs.h"
#include "assets_types.h"

namespace pnt::assetDB{

    // TODO - Fill all the Derived Query Spec with their personalized information...
    // TODO - Implement the Specs GetAssetHandle methods...


    struct PNT_API PAssetDBQuery{
        PAssetDBQuery(const QuerySpec& spec, QueryOperation operation)
            : spec(spec),
              operation(operation)
        {
        }

        QuerySpec spec;
        QueryOperation operation;
    };

    class PNT_API PAssetDatabase final : public PServiceBase<IAssetDBService>{
    public:
        ~PAssetDatabase() override = default;

        void init() override;

        void start();

        void process();

        void render();

        void update(float deltaTime);

        void destroy() override;

        static PHandleBase* queryDBForAsset(const PAssetDBQuery& assetDBQuery);

        void setupAsset();


    private:
        [[nodiscard]]static PHandleBase* performGetOperation(const QuerySpec& spec);
        [[nodiscard]]static PHandleBase* performAddOperation(const QuerySpec& spec);
        [[nodiscard]]static PHandleBase* performUpdateOperation(const QuerySpec& spec);
        [[nodiscard]]static PHandleBase* performDeleteOperation(const QuerySpec& spec); // handle id is nullptr in this case if deletion succeeded...

        // Switch on QueryType...
        std::vector<PTextureAsset*> m_textureAssetContainer;
        std::vector<PSpriteAsset*> m_spriteAssetContainer;
        std::vector<PShaderAsset*> m_shaderAssetContainer;
        std::vector<PMeshAsset*> m_meshAssetContainer;
        std::vector<PSkeletonAsset*> m_skeletonAssetContainer;
        std::vector<PStaticMeshAsset*> m_staticMeshAssetContainer;
        std::vector<PMaterialAsset*> m_materialAssetContainer;
        std::vector<PSplineAsset*> m_splineAssetContainer;
        std::vector<PP2DPolygonMeshAsset*>m_p2DPolygonMeshAssetContainer;
        std::vector<PSoundSourceAsset*> m_soundSourceAssetContainer;
        std::vector<PP3DSoundSourceAsset*> m_p3DSoundSourceAssetContainer;
        std::vector<PLevelAsset*> m_levelAssetContainer;
        std::vector<PParticleAsset*> m_particleAssetContainer;
        std::vector<PRenderMapAsset*> m_renderMapAssetContainer;

    };
}



