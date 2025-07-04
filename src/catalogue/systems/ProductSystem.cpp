#include "catalogue/systems/ProductSystem.hpp"

using json = nlohmann::json;

ProductSystem::ProductSystem(ComponentManager* cm)
    : System(cm) {}

void ProductSystem::update() {
    auto products = exportAsJson();

    std::cout << "=== Liste JSON des produits ===\n";
    std::cout << products.dump(4) << std::endl; // jolis indentations
}

json ProductSystem::exportAsJson() const {
    json output = json::array();

    auto productEntities = componentManager->getAllWithComponent<TitleComponent>();

    for (const auto& [entity, titleRef] : productEntities) {
        json item;
        item["id"] = entity;
        item["title"] = titleRef.get().title;

        if (auto price = componentManager->getComponent<PriceComponent>(entity))
            item["price"] = price->get().price;

        if (auto currency = componentManager->getComponent<CurrencyComponent>(entity))
            item["currency"] = currency->get().currency;

        if (auto user = componentManager->getComponent<UserIdComponent>(entity))
            item["user_id"] = user->get().userId;

        if (auto desc = componentManager->getComponent<DescriptionComponent>(entity))
            item["description"] = desc->get().description;

        if (auto status = componentManager->getComponent<IsActiveComponent>(entity))
            item["is_active"] = status->get().isActive;

        if (auto views = componentManager->getComponent<ViewsComponent>(entity))
            item["views"] = views->get().views;

        // ✅ Images
        if (auto images = componentManager->getComponent<ImagesComponent>(entity)) {
            item["images"] = images->get().imageUrls;
        }

        if(auto brand_id = componentManager->getComponent<BrandIdComponent>(entity)){
            item["brand_id"] = brand_id->get().brandId;
        }


        // ✅ Champs dynamiques
        if (auto custom = componentManager->getComponent<CustomFieldsComponent>(entity)) {
            item["custom_fields"] = json::object();
            for (const auto& [key, value] : custom->get().fields) {
                item["custom_fields"][key] = value;
            }
        }

        output.push_back(item);
    }

    return output;
}

