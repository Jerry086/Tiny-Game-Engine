#ifndef ISERVICE_HPP
#define ISERVICE_HPP
class IService {
   public:
    virtual ~IService() = default;
    virtual void ShutDown() = 0;
};
#endif