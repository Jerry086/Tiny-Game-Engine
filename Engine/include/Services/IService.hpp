// TODO doc
class IService {
   public:
    virtual ~IService() = default;
    virtual void Update() = 0;
};

// TODO doc
class DummyService : public IService {
   public:
    void Update() override {}
};