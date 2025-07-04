#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <memory>
#include "ComponentManager.hpp"

class System{
protected:
    ComponentManager* componentManager;

public:
    explicit System(ComponentManager* cm)
        : componentManager(cm){}

    virtual ~System() = default;

    virtual void update() = 0;
};

#endif // SYSTEM_HPP
