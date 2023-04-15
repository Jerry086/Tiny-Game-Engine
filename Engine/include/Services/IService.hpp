#ifndef ISERVICE_HPP
#define ISERVICE_HPP

/**
 * @brief Abstract class that defines the interface for all services
 */
class IService {
   public:
    virtual ~IService() = default;
    virtual void ShutDown() = 0;
    virtual void Update(){};
};
#endif