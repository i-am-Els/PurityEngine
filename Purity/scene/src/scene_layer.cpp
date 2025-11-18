//
// Created by Eniola Olawale on 11/10/2025.
//

#include "scene_layer.h"


namespace purity::scene {
    void SceneLayer::render()
    {
        PLayer::render();
    }

    void SceneLayer::update()
    {
    }

    void SceneLayer::attached()
    {
    }

    void SceneLayer::detached()
    {
    }

    void SceneLayer::eventFired(Event& event)
    {
    }

    bool SceneLayer::switchScene(std::unique_ptr<scene::PScene> scene)
    {
        if(scene == nullptr) { return false;}
        const auto temp = std::move(attached_scene);
        attached_scene = std::move(scene);
        return true;
    }
} // scene
// purity