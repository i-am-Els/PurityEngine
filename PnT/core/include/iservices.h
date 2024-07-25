//
// Created by emman on 7/10/2024.
//

#pragma once

#include <typeindex>

namespace pnt{

    class IService{
    public:
        virtual ~IService() = default;

        /// Virtual function to get the base type index of the service.
        /// Should be overridden in each service interface to return the typeid of the base interface.
        [[nodiscard]] virtual std::type_index getTypeIndex() const = 0;

        virtual void init() = 0;

        virtual void start() = 0;

        virtual void process() = 0;

        virtual void render() = 0;

        virtual void update(float deltaTime) = 0;

        virtual void destroy() = 0;
    };
}
