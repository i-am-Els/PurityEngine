//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

namespace pnt::ecs{
    class IEntity{
    public:
        template<typename T>
        T *AddComponent();

        template<typename T>
        T *GetComponent();
    };
}
