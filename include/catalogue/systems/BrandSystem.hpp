#ifndef BRAND_SYSTEM_HPP
#define BRAND_SYSTEM_HPP

#include "catalogue/ecs/System.hpp"
#include "catalogue/components/brands/ImageComponent.hpp"
#include "catalogue/components/brands/NameComponent.hpp"
#include <iostream>

class BrandSystem: public System{
public:
    BrandSystem(ComponentManager* cm)
    : System(cm){}

    void update() override{
        auto names = componentManager->getAllWithComponent<NameComponent>();

        for(const auto& [entity, NameRef]: names){
            if(componentManager->hasComponent<ImageComponent>(entity)){
                auto imageOpt = componentManager->getComponent<ImageComponent>(entity);

                if(imageOpt){
                    const auto& name = NameRef.get().name;
                    const auto& image = imageOpt->get().image;

                    std::cout << "Name: " << name << ", Image: " << image << std::endl; 
                }
            }
        }
    }
};

#endif // BRAND_SYSTEM_HPP