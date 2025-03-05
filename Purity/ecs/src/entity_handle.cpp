#include "entity_handle.h"
#include "scene.h"

namespace purity::ecs {

    void PEntityHandle::destroy() {
        PSystemFinder::GetScene()->DestroyEntity(*this);
        m_data = nullptr;
    }
}