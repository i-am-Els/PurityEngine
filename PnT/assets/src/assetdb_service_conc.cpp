//
// Created by Eniola Olawale on 9/13/2024.
//

#include "assetdb_service_conc.h"

namespace pnt::assetDB{

    void PAssetDatabase::init() {
        // queryDBForAsset({QueryStaticMeshAssetSpec("gun", "gun.fbx", "material.ml"), QueryOperation::Read});
    }

    void PAssetDatabase::start() {

    }

    void PAssetDatabase::process() {

    }

    void PAssetDatabase::render() {

    }

    void PAssetDatabase::update(float deltaTime) {

    }

    void PAssetDatabase::destroy() {

    }

    PHandleBase* PAssetDatabase::queryDBForAsset(const PAssetDBQuery& assetDBQuery) {

        switch (assetDBQuery.operation)
        {
        case QueryOperation::Read:
            performGetOperation(assetDBQuery.spec);
            break;
        case QueryOperation::Write:
            performAddOperation(assetDBQuery.spec);
            break;
        case QueryOperation::Update:
            performUpdateOperation(assetDBQuery.spec);
            break;
        case QueryOperation::Delete:
            performDeleteOperation(assetDBQuery.spec);
            break;
        default:
            break;
        }
        return nullptr;
    }

    PHandleBase* PAssetDatabase::performGetOperation(const QuerySpec& spec)
    {
        return spec.strategy->ReadOperation();
    }

    PHandleBase* PAssetDatabase::performAddOperation(const QuerySpec& spec)
    {
        return spec.strategy->WriteOperation();
    }

    PHandleBase* PAssetDatabase::performUpdateOperation(const QuerySpec& spec)
    {
        return spec.strategy->UpdateOperation();
    }

    PHandleBase* PAssetDatabase::performDeleteOperation(const QuerySpec& spec)
    {
        return spec.strategy->DeleteOperation();
    }

}
