#pragma once

#include "catalogue/ecs/System.hpp"
#include "catalogue/ecs/ComponentManager.hpp"

// Composants produits
#include "catalogue/components/product/TitleComponent.hpp"
#include "catalogue/components/product/PriceComponent.hpp"
#include "catalogue/components/product/CurrencyComponent.hpp"
#include "catalogue/components/product/UserIdComponent.hpp"
#include "catalogue/components/product/DescriptionComponent.hpp"
#include "catalogue/components/product/IsActiveComponent.hpp"
#include "catalogue/components/product/ViewsComponent.hpp"
#include "catalogue/components/product/ImagesComponent.hpp"
#include "catalogue/components/product/CustomFieldsComponent.hpp"
#include "catalogue/components/product/BrandIdComponent.hpp"
#include "catalogue/components/product/OriginalPriceComponent.hpp"

#include <nlohmann/json.hpp>
#include <iostream>

class ProductSystem : public System {
public:
    explicit ProductSystem(ComponentManager* cm);

    void update() override;

    nlohmann::json exportAsJson() const;
};
