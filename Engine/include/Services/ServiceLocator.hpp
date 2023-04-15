#ifndef SERVICE_LOCATOR_HPP
#define SERVICE_LOCATOR_HPP
#include <iostream>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "IService.hpp"

// TODO doc
class ServiceLocator {
   public:
    // Disable copy constructor and assignment operator
    ServiceLocator(const ServiceLocator &) = delete;
    ServiceLocator &operator=(const ServiceLocator &) = delete;

    // Singleton
    static ServiceLocator &instance() {
        static ServiceLocator instance;
        return instance;
    }

    // For Pybind reasons, need to be implemented in the header file
    template <typename T>
    static void RegisterService() {
        std::type_index type = typeid(T);
        ServiceLocator::instance().m_services[type] = &T::instance();
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

   private:
    ServiceLocator() = default;
    std::unordered_map<std::type_index, IService *> m_services;
};

#endif