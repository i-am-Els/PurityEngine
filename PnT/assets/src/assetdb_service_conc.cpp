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
            performGetOperarion(assetDBQuery.spec);
            break;
        case QueryOperation::Write:
            performAddOperarion(assetDBQuery.spec);
            break;
        case QueryOperation::Update:
            performUpdateOperarion(assetDBQuery.spec);
            break;
        case QueryOperation::Delete:
            performDeleteOperarion(assetDBQuery.spec);
            break;
        default:
            break;
        }
        return nullptr;
    }

    PHandleBase* PAssetDatabase::performGetOperarion(const QuerySpec& spec)
    {
        return spec.strategy->ReadOperation();
    }

    PHandleBase* PAssetDatabase::performAddOperarion(const QuerySpec& spec)
    {
        return spec.strategy->WriteOperation();
    }

    PHandleBase* PAssetDatabase::performUpdateOperarion(const QuerySpec& spec)
    {
        return spec.strategy->UpdateOperation();
    }

    PHandleBase* PAssetDatabase::performDeleteOperarion(const QuerySpec& spec)
    {
        return spec.strategy->DeleteOperation();
    }

}
