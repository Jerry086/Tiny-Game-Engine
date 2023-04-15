#include <memory>
#include <string>
#include <unordered_set>

// Forward declaration
class IService;

// TODO doc
class ServiceLocator {
   public:
    template <typename T>
    std::shared_ptr<T> GetService();

   private:
    std::unordered_set<std::shared_ptr<IService>> m_services;
};
