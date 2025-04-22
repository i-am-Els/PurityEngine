//
// Created by emman on 7/10/2024.
//

#pragma once

#include "purity_core_pch.h"

#include "iservices.h"



namespace purity{
    class PURITY_API PServiceLocator {
        std::vector<IInitializableService*> m_initializables;
        std::vector<IUpdatableService*> m_updatables;
        std::vector<IRenderableService*> m_renderables;
        std::vector<IRunnableService*> m_runnables;
        std::vector<ITerminableService*> m_terminables;

        mutable std::mutex mutex;
        std::map<std::type_index, std::shared_ptr<IService>> services; // Owns all services


        // Register interfaces for a service
        template<typename Abstract>
        void registerInterfaces(Abstract* service) {
            if (auto* init = dynamic_cast<IInitializableService*>(service)) {
                m_initializables.push_back(init);
            }
            if (auto* upd = dynamic_cast<IUpdatableService*>(service)) {
                m_updatables.push_back(upd);
            }
            if (auto* rend = dynamic_cast<IRenderableService*>(service)) {
                m_renderables.push_back(rend);
            }
            if (auto* run = dynamic_cast<IRunnableService*>(service)) {
                m_runnables.push_back(run);
            }
            if (auto* term = dynamic_cast<ITerminableService*>(service)) {
                m_terminables.push_back(term);
            }
        }

        // Unregister interfaces for a service
        template<typename Abstract>
        void unregisterInterfaces(const Abstract* service) {
            auto removeFromList = [service](auto& list) {
                list.erase(
                    std::remove_if(
                        list.begin(), list.end(),
                        [service](const auto* ptr) {
                            // Compare the raw pointer addresses by converting to void*
                            return reinterpret_cast<const void*>(ptr) == reinterpret_cast<const void*>(service);
                        }
                    ),
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
        [[nodiscard]] const std::vector<IInitializableService*>& getInitializables() const
        {
            std::lock_guard<std::mutex> lock(mutex);
            return m_initializables;
        }
        [[nodiscard]] const std::vector<IUpdatableService*>& getUpdatables() const
        {
            std::lock_guard<std::mutex> lock(mutex);
            return m_updatables;
        }
        [[nodiscard]] const std::vector<IRenderableService*>& getRenderables() const
        {
            std::lock_guard<std::mutex> lock(mutex);
            return m_renderables;
        }
        [[nodiscard]] const std::vector<IRunnableService*>& getRunnables() const
        {
            std::lock_guard<std::mutex> lock(mutex);
            return m_runnables;
        }
        [[nodiscard]] const std::vector<ITerminableService*>& getTerminables() const
        {
            std::lock_guard<std::mutex> lock(mutex);
            return m_terminables;
        }

        ~PServiceLocator()
        {
            PLog::echoMessage("Destroying Service Locator.");
            // Clear all interface vectors
            {
                std::lock_guard<std::mutex> lock(mutex);
                m_initializables.clear();
                m_runnables.clear();
                m_updatables.clear();
                m_renderables.clear();
                m_terminables.clear();
                services.clear();
            }
        }

        template<typename Abstract, typename Concrete>
        void registerService(std::shared_ptr<Concrete> service){
            static_assert(std::is_base_of_v<IService, Abstract>, "Abstract must be a subclass of IService");
            std::lock_guard<std::mutex> lock(mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            const auto typeIndex = std::type_index(typeid(Abstract)); //
            PLog::echoValue(typeIndex.name());

            if (services.find(typeIndex) != services.end()){
                throw std::runtime_error("Service already registered!");
            }

            services[typeIndex] = service;
            registerInterfaces(service.get());
        }

        template<typename Abstract>
        void unregisterService(){
            std::lock_guard<std::mutex> lock(mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            const auto typeIndex = std::type_index(typeid(Abstract));
            PLog::echoValue(typeIndex.name());

            const auto it = services.find(typeIndex);
            if (it == services.end()){
                throw std::runtime_error("Service not registered!");
            }

            unregisterInterfaces(it->second.get());
            services.erase(it);
        }

        template<typename Abstract, typename Concrete>
        std::shared_ptr<Concrete> getService() const {
            std::lock_guard<std::mutex> lock(mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            const auto typeIndex = std::type_index(typeid(Abstract));
            const auto it = services.find(typeIndex);
            PLog::echoValue(typeIndex.name());

            if (it == services.end()){
                throw std::runtime_error("Service not found!");
            }

            return std::dynamic_pointer_cast<Concrete>(it->second);
        }
    };
}
