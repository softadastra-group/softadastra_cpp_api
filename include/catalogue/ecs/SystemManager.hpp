#ifndef SYSTEM_MANAGER_HPP 
#define SYSTEM_MANAGER_HPP

#include <vector>
#include <memory>
#include "System.hpp"

class SystemManager{
protected:
    std::vector<std::unique_ptr<System>> systems;
public:
    SystemManager() = default;

     void addSystem(std::unique_ptr<System> system){
        systems.push_back(std::move(system));
     }

     void updateAll(){
        for(auto& system : systems){
            system->update();
        }
     }

     void clear(){
        systems.clear();
     }
};

#endif // SYSTEM_MANAGER_HPP 
