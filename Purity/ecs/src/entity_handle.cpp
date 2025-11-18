#include "entity_handle.h"

#include "scene.h"

namespace purity::ecs {

	void PEntityHandle::destroy()
	{
		if (auto e = m_data.lock()) {
			// TODO:  or whatever your entity cleanup function is
			m_data.reset();
		}
		PSystemFinder::GetScene()->DestroyEntity(*this);
	}
}