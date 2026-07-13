#pragma once

#include "core_macros.h"

namespace purity::ecs {
	struct PURITY_API PEntityIndex {
		size_t index;
		size_t generation;

		bool operator==(const PEntityIndex& other) const {
			return index == other.index && generation == other.generation;
		}
	};
}