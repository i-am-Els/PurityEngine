//
// Created by emman on 7/10/2024.
//

#pragma once

#include "purity_core_pch.h"

#define PNT_TYPE_INDEX_DEF() template<typename T>\
[[nodiscard]] static std::type_index s_getTypeIndex(){\
    return std::type_index(typeid(T));\
} \

namespace purity{

    class PURITY_API IService{
    public:
        virtual ~IService() = default;

        /// Virtual function to get the base type index of the service.
        /// Should be overridden in each service interface to return the typeid of the base interface.
        [[nodiscard]] virtual std::type_index getTypeIndex() const = 0;
    };
    // For initialization phases

    class PURITY_API IInitializable : public IService{
    public:
        virtual void preInit(std::any data) = 0;
        virtual void init() = 0;
        virtual void postInit() = 0;
        ~IInitializable() override = default;
    };

    // For runtime processing
    class PURITY_API IRunnable : public IService{
    public:
        virtual void start() = 0;
        virtual void process() = 0;
        ~IRunnable() override = default;
    };

    // For updating logic (like game logic or service state updates)
    class PURITY_API IUpdatable : public IService {
    public:
        virtual void update(float deltaTime) = 0;
        ~IUpdatable() override = default;
    };

    // For rendering phases
    class PURITY_API IRenderable : public IService {
    public:
        virtual void preRender() = 0;
        virtual void render() = 0;
        virtual void postRender() = 0;
        ~IRenderable() override = default;
    };

    // For termination or cleanup phases
    class PURITY_API ITerminable : public IService {
    public:
        virtual void destroy() = 0;
        virtual void exit() = 0;
        ~ITerminable() override = default;
    };

}
