#ifndef SERVICE_LOCATOR_HPP
#define SERVICE_LOCATOR_HPP
#include <iostream>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "IService.hpp"

// TODO doc
class ServiceLocator {
   public:
    // Disable copy constructor and assignment operator
    ServiceLocator(const ServiceLocator &) = delete;
    ServiceLocator &operator=(const ServiceLocator &) = delete;

    // For Pybind reasons, need to be implemented in the header file
    template <typename T>
    static void RegisterService() {
        std::type_index type = typeid(T);
        ServiceLocator::instance().m_services[type] = &T::instance();
        ServiceLocator::instance().m_orderedKeys.push_back(type);
    }

    // For Pybind reasons, need to be implemented in the header file
    template <typename T>
    static T &GetService() {
        std::type_index type = typeid(T);
        auto it = ServiceLocator::instance().m_services.find(type);
        if (it != ServiceLocator::instance().m_services.end()) {
            return *static_cast<T *>(it->second);
        }
        std::cerr << "ServiceLocator::GetService: Service not found for type "
                  << typeid(T).name() << ". Creating a new one." << std::endl;
        RegisterService<T>();
        auto it2 = ServiceLocator::instance().m_services.find(type);
        return *static_cast<T *>(it2->second);
    }

    static void ShutDown() {
        for (auto it = ServiceLocator::instance().m_services.begin();
             it != ServiceLocator::instance().m_services.end(); ++it) {
            it->second->ShutDown();
        }
    }

    static void Update() {
        for (auto it = ServiceLocator::instance().m_orderedKeys.begin();
             it != ServiceLocator::instance().m_orderedKeys.end(); ++it) {
            auto service = ServiceLocator::instance().m_services.find(*it);
            service->second->Update();
        }
    }

    static void Render() {
        for (auto it = ServiceLocator::instance().m_orderedKeys.begin();
             it != ServiceLocator::instance().m_orderedKeys.end(); ++it) {
            auto service = ServiceLocator::instance().m_services.find(*it);
            service->second->Render();
        }
    }

    template <typename T>
    static void ResetService() {
        std::type_index type = typeid(T);
        auto it = ServiceLocator::instance().m_services.find(type);
        if (it == ServiceLocator::instance().m_services.end()) {
            std::cerr
                << "ServiceLocator::ResetService: Service not found for type "
                << typeid(T).name() << ". Creating a new one." << std::endl;
            RegisterService<T>();
            auto it2 = ServiceLocator::instance().m_services.find(type);
            it2->second->StartUp();
        } else {
            it->second->ShutDown();
            it->second->StartUp();
        }
    }

    static void ResetAllServices() {
        for (auto it = ServiceLocator::instance().m_services.begin();
             it != ServiceLocator::instance().m_services.end(); ++it) {
            it->second->ShutDown();
            it->second->StartUp();
        }
    }

   private:
    // Singleton
    static ServiceLocator &instance() {
        static ServiceLocator instance;
        return instance;
    }
    ServiceLocator() = default;
    std::unordered_map<std::type_index, IService *> m_services;
    std::vector<std::type_index> m_orderedKeys;
};

#endif