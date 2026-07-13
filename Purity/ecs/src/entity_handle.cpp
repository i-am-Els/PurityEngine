#include "entity_handle.h"

#include "scene.h"

namespace purity::ecs {

	void PEntityHandle::destroy()
	{
		if (auto e = m_data.lock()) {
			// TODO: or whatever your entity cleanup function is
			m_data.reset();
		}
		if (auto scene = m_registry->GetOwningScene()) {
			scene->DestroyEntity(*this);
		}
	}


	PECSService& PEntityHandle::getECSService() {
		if (auto scene = m_registry->GetOwningScene()) {
			return scene->GetECSService();
		}
		PLOG_ERROR("PEntityHandle::_getECSService called with no valid owning scene.");
		throw std::runtime_error("PEntityHandle::_getECSService: no valid owning scene.");
	}
}