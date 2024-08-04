//
// Created by emman on 8/4/2024.
//

#pragma once

#include <functional>

namespace pnt::ecs {

    // Generic ComponentTraits template
    template<typename T>
    struct ComponentTraits {
        using AddComponentCallback = std::function<T*()>;
        using GetComponentCallback = std::function<T*()>;
        using RemoveComponentCallback = std::function<void(T*)>;
    };

    // Specialize for PRenderComponent
    //    class PRenderComponent;
    //    template<>
    //    struct ComponentTraits<PRenderComponent> {
    //        using AddComponentCallback = std::function<PRenderComponent*()>;
    //        using GetComponentCallback = std::function<PRenderComponent*()>;
    //        using RemoveComponentCallback = std::function<void(PRenderComponent*)>;
//    };
}

