//
// Created by emman on 7/10/2024.
//

#pragma once
#include <typeindex>

namespace pnt{
    template<typename T>
    class PServiceBase : public T{
    public:
        /// Returns the type index of the base interface.
        [[nodiscard]] std::type_index getTypeIndex() const override {
            return std::type_index(typeid(T));
        }
    };
}
