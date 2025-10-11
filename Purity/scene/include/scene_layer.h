//
// Created by Eniola Olawale on 11/10/2025.
//

#pragma once
#include "layer.h"
#include "scene.h"

namespace purity::scene {

class PURITY_API SceneLayer final : public purity::PLayer{

    friend class PLayerService;
public:
    PURE_NODISCARD SceneLayer() = default;

    PURE_NODISCARD explicit SceneLayer(const std::string& name)
        : PLayer(name)
    {
    }

    void render() override;

    void update() override;
    void attached() override;
    void detached() override;
    void eventFired(Event& event) override;

    PURE_NODISCARD PURE_INLINE PScene* getAttachedScene() const { return attached_scene.get(); }

private:
    bool switchScene(std::unique_ptr<scene::PScene> scene);
    std::unique_ptr<PScene> attached_scene;
};

} // scene
// purity

