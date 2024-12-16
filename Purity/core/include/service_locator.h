//
// Created by emman on 7/10/2024.
//

#pragma once

#include "purity_core_pch.h"

#include "iservices.h"

namespace purity{
    class PURITY_API PServiceLocator{
    private:
        std::map<std::type_index, std::shared_ptr<IService>> services;
        mutable std::mutex mutex;

    public:
        template<typename T>
        void registerService(std::shared_ptr<T> service){
            static_assert(std::is_base_of<IService, T>::value, "T must be a subclass of IService");
            std::lock_guard<std::mutex> lock(mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            std::type_index typeIndex =std::type_index(typeid(T)); //
            PLog::echoValue(typeIndex.name());

            if (services.find(typeIndex) != services.end()){
                throw std::runtime_error("Service already registered!");
            }

            services[typeIndex] = service;
        }

        template<typename T>
        void unregisterService(){
            std::lock_guard<std::mutex> lock(mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            auto typeIndex = std::type_index(typeid(T));
            PLog::echoValue(typeIndex.name());

            if (services.find(typeIndex) == services.end()){
                throw std::runtime_error("Service not registered!");
            }

            services.erase(typeIndex);
        }

        template<typename T>
        std::shared_ptr<T> getService() const {
            std::lock_guard<std::mutex> lock(mutex); // 'lock' here is the lock_guard variable to lock the thread with.
            auto typeIndex = std::type_index(typeid(T));
            auto it = services.find(typeIndex);
            PLog::echoValue(typeIndex.name());

            if (it == services.end()){
                throw std::runtime_error("Service not found!");
            }

            return std::static_pointer_cast<T>(it->second); // Cast the IService into a std::shared_pointer of the type T.
        }

        template<typename Interface, typename Concrete>
        Concrete* getConcreteService(){
            return dynamic_cast<Concrete*>(getService<Interface>().get());
        }

        ~PServiceLocator() {
            PLog::echoMessage("Destroying Service Locator.");
        }
    };
}
