//
// Created by emman on 7/8/2024.
//

#pragma once

#include <limits.h>
#include "entity_index.h"
#include "component.h"

namespace purity::ecs {
    class PURITY_API IPoolBase {
    public:
        virtual ~IPoolBase() = default;
    };

    template<typename T>
    struct PURITY_API SparseSet {
        static constexpr size_t INVALID_INDEX = (std::numeric_limits<size_t>::max)();
        SparseSet(size_t max_val) {
            sparse.resize(max_val, INVALID_INDEX);
        }

        std::shared_ptr<T> Add(size_t index) {
            size_t sparseSize = sparse.size();
            if (index >= sparseSize)
            {
                sparse.resize(
                    (std::max)(sparseSize * 2, index + 1),
                    INVALID_INDEX
                );
            }

            if (Has(index)) return Get(index);
            sparse[index] = denseItems.size();
            denseItems.emplace_back(std::make_shared<T>());
            denseEntities.emplace_back(index);
            return denseItems.back();
        }

        std::shared_ptr<T> Get(size_t index) {
            size_t denseIndex = sparse[index];
            if (Has(index)) {
                return denseItems[denseIndex];
            }
            return nullptr;
        }

        void Remove(size_t index) {
            if (!Has(index)) return;

            size_t denseIndex = sparse[index];
            size_t back_id = denseEntities.back();

            denseEntities[denseIndex] = denseEntities.back(); // std::swap(dense[id], dense.back());
            denseItems[denseIndex] = denseItems.back(); // std::swap(denseItems[id], denseItems.back());

            sparse[back_id] = denseIndex;
            sparse[index] = INVALID_INDEX;
            denseEntities.pop_back();
            denseItems.pop_back();
        }

        bool Has(size_t index) const {
            if (index >= sparse.size())
                return false;
            size_t denseIndex = sparse[index];
            return (denseIndex != INVALID_INDEX && denseIndex < denseEntities.size() && denseEntities[denseIndex] == index);
        }

    private:
        std::vector<std::shared_ptr<T>> denseItems;
        std::vector<size_t> denseEntities;
        std::vector<size_t> sparse;
    };


    template<typename ComponentType>
    class PURITY_API PoolManager : public IPoolBase, public SparseSet<ComponentType> {
    public:
        using Base = SparseSet<ComponentType>;

        PoolManager() : SparseSet<ComponentType>(32){}

        std::weak_ptr<ComponentType> addComponent(PEntityIndex index) {
            return Base::Add(index.index);
        }
        
        std::weak_ptr<ComponentType> getComponent(PEntityIndex index) {
            return Base::Get(index.index);
        }

        void removeComponent(PEntityIndex index) {
            Base::Remove(index.index);
        }

        bool contains(PEntityIndex index) const {
            return Base::Has(index.index);
        }

        virtual ~PoolManager() override {}
    };

}
