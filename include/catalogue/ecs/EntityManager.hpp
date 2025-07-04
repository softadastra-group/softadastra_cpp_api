#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <cstdint>
#include <vector>

using Entity = std::uint32_t;

class EntityManager{
   Entity nextEntityId = 1;

public:
    Entity createEntity(){
        return nextEntityId++;
    }
};

#endif // ENTITY_MANAGER_HPP
