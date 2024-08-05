//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "component.h"
#include "ecs_main.h"

namespace pnt::ecs{

    class ManipulativeBehaviour{
    public:

        virtual ~ManipulativeBehaviour() = default;

        template<typename T>
        T *AddComponent();

        template<typename T>
        T *GetComponent();

        template<typename T>
        void RemoveComponent(T* component);

        template<typename T>
        void RemoveComponents(T* component);

        template<typename T>
        void RemoveComponentByTag(T* component, std::string tag);

        template<typename T>
        void RemoveComponentsByTag(std::string tag);

        template<typename T>
        T* FindComponentByTag(std::string tag);

        template<typename T>
        std::vector<T*> FindComponentsByTag(std::string tag);
    };

}
