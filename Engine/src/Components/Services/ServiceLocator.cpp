#include "./Services/ServiceLocator.hpp"

#include <typeinfo>

#include "./Services/IService.hpp"

template <typename T>
std::shared_ptr<T> ServiceLocator::GetService() {
    for (auto it = m_services.begin(); it != m_services.end(); it++) {
        if (std::dynamic_pointer_cast<T>(*it)) {
            return std::dynamic_pointer_cast<T>(*it);
        }
    }
    std::cerr << "ServiceLocator::GetService: Service not found for type "
              << typeid(T).name() << ". Creating a new one." << std::endl;

    std::shared_ptr<T> service = std::make_shared<T>();
    m_services.insert(service);
}