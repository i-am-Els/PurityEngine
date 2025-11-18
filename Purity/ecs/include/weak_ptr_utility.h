//
// Created by Eniola Olawale on 23/10/2025.
//

#pragma once
#include <memory>

#include "core_macros.h"

namespace purity::ecs
{
        template<typename T>
        PURE_NODISCARD PURE_INLINE bool is_alive(const std::weak_ptr<T>& wp) noexcept { return !wp.expired(); }

        template<typename T>
        PURE_NODISCARD PURE_INLINE std::shared_ptr<T> fetch(const std::weak_ptr<T>& wp) noexcept { return wp.lock(); }


        // One-liner: lock or throw
        template<typename T>
        std::shared_ptr<T> fetch_or_throw(const std::weak_ptr<T>& wp, const std::string& debugName = "")
        {
                if (auto sp = wp.lock())
                        return sp;
                throw exceptions::NullPointerError(debugName.empty()
                    ? "Attempted to access expired weak pointer."
                    : ("Attempted to access expired weak pointer: " + debugName).c_str());
        }

        /// Use with a lambda
        template<typename T, typename F>
        PURE_NODISCARD PURE_INLINE void if_alive(const std::weak_ptr<T>& wp, F&& func)
        {
                if (auto sp = wp.lock())
                        std::invoke(std::forward<F>(func), sp);
        }

        template<typename T>
        bool weak_equal(const std::weak_ptr<T>& a, const std::weak_ptr<T>& b) {
                return !a.owner_before(b) && !b.owner_before(a);
        }

        // Optional macro for brevity
#define ECS_FETCH_OR_THROW(var, wp) auto var = ecs::fetch_or_throw(wp, #var)

        /**
        auto id = entity.AddComponent<PIDComponent>();

        // Option 1: Direct function
        auto sh_id = ecs::fetch_or_throw(id, "PIDComponent::setID");
        sh_id->setID (uuid);

        // Option 2: With macro
        ECS_FETCH_OR_THROW(sh_id, id);
        sh_id->setID (uuid);

        // Option 3: Functional
        ecs::if_alive(id, [&](auto idComp) { idComp->setID(uuid); });
        **/
}
