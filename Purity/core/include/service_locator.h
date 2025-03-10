//
// Created by emman on 7/10/2024.
//

#pragma once

#include "purity_core_pch.h"

#include "iservices.h"

namespace purity{
    class PURITY_API PServiceLocator {
        std::vector<IInitializable*> m_initializables;
        std::vector<IUpdatable*> m_updatables;
        std::vector<IRenderable*> m_renderables;
        std::vector<IRunnable*> m_runnables;
        std::vector<ITerminable*> m_terminables;

        mutable std::mutex m_mutex;
        std::map<std::type_index, std::shared_ptr<IService>> services; // Owns all services


        // Register interfaces for a service
        template <typename T>
        void registerInterfaces(T* service) {
            if (auto* ptr = dynamic_cast<IInitializable*>(service)) {
                m_initializables.push_back(ptr);
            }
            if (auto* ptr = dynamic_cast<IUpdatable*>(service)) {
                m_updatables.push_back(ptr);
            }
            if (auto* ptr = dynamic_cast<IRenderable*>(service)) {
                m_renderables.push_back(ptr);
            }
            if (auto* ptr = dynamic_cast<IRunnable*>(service)) {
                m_runnables.push_back(ptr);
            }
            if (auto* ptr = dynamic_cast<ITerminable*>(service)) {
                m_terminables.push_back(ptr);
            }
        }

        // Unregister interfaces for a service
        template <typename T>
        void unregisterInterfaces(T* service) {
            auto removeFromList = [service](auto& list) {
                list.erase(
                    std::remove_if(list.begin(), list.end(),
                    [service](auto* ptr) {
                        return static_cast<IService*>(ptr) == static_cast<IService*>(service);
                    }),
                    list.end()
                );
            };

            removeFromList(m_initializables);
            removeFromList(m_updatables);
            removeFromList(m_renderables);
            removeFromList(m_runnables);
            removeFromList(m_terminables);
        }

    public:
        // Interface accessors
        [[nodiscard]] const std::vector<IInitializable*>& getInitializables() const { return m_initializables; }
        [[nodiscard]] const std::vector<IUpdatable*>& getUpdatables() const { return m_updatables; }
        [[nodiscard]] const std::vector<IRenderable*>& getRenderables() const { return m_renderables; }
        [[nodiscard]] const std::vector<IRunnable*>& getRunnables() const { return m_runnables; }
        [[nodiscard]] const std::vector<ITerminable*>& getTerminables() const { return m_terminables; }

        ~PServiceLocator()
        {
            PLog::echoMessage("Destroying Service Locator.");
            services.clear();
            m_initializables.clear();
            m_runnables.clear();
            m_updatables.clear();
            m_renderables.clear();
            m_terminables.clear();
        }

        template<typename T>
        void registerService(std::shared_ptr<T> service){
            static_assert(std::is_base_of<IService, T>::value, "T must be a subclass of IService");
            std::lock_guard<std::mutex> lock(m_mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            auto typeIndex = std::type_index(typeid(T)); //
            PLog::echoValue(typeIndex.name());
            if (services.find(typeIndex) != services.end()){
                throw std::runtime_error("Service already registered!");
            }
            services[typeIndex] = std::dynamic_pointer_cast<IService>(service);
            // services.emplace(std::make_pair(typeIndex, std::dynamic_pointer_cast<IService>(service)));
            registerInterfaces(service.get());
        }

        template<typename T>
        void unregisterService(){
            std::lock_guard<std::mutex> lock(m_mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            auto typeIndex = std::type_index(typeid(T));
            PLog::echoValue(typeIndex.name());
            auto service = services.find(typeIndex) ;
            if (service == services.end()){
                throw std::runtime_error("Service not registered!");
            }
            unregisterInterfaces(service->second.get());
            services.erase(typeIndex);
        }

        template<typename T>
        std::shared_ptr<T> tryGetService() const noexcept {
            std::lock_guard<std::mutex> lock(m_mutex);
            auto typeIndex = std::type_index(typeid(T));
            auto it = services.find(typeIndex);
            return (it != services.end()) ? std::dynamic_pointer_cast<T>(it->second) : nullptr;
        }

        template<typename T>
        std::shared_ptr<T> getService() const {
            std::lock_guard<std::mutex> lock(m_mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            auto typeIndex = std::type_index(typeid(T));
            auto it = services.find(typeIndex);
            PLog::echoValue(typeIndex.name());
            if (it == services.end()){
                throw std::runtime_error("Service not found!");
            }
            return std::dynamic_pointer_cast<T>(it->second); // Cast the IService into a std::shared_pointer of the type T.
        }
    };
}
