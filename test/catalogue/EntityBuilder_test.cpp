#include <gtest/gtest.h>
#include "catalogue/ecs/EntityManager.hpp"
#include "catalogue/ecs/ComponentManager.hpp"
#include "catalogue/systems/ProductSystem.hpp"
#include "catalogue/entities/EntityBuilder.hpp"
#include "catalogue/components/product/TitleComponent.hpp"
#include "catalogue/components/product/PriceComponent.hpp"
#include "catalogue/components/product/CurrencyComponent.hpp"
#include "catalogue/components/product/UserIdComponent.hpp"
#include "catalogue/components/product/DescriptionComponent.hpp"
#include "catalogue/components/product/IsActiveComponent.hpp"
#include "catalogue/components/product/ViewsComponent.hpp"
#include "catalogue/components/product/ImagesComponent.hpp"
#include "catalogue/components/product/CustomFieldsComponent.hpp"

using namespace std;

TEST(ProductSystemTest, ExportAsJson_ValidProduct_SerializesCorrectly) {
    EntityManager em;
    ComponentManager cm;
    ProductSystem system(&cm);

    Entity product = em.createEntity();
    cm.addComponent(product, make_shared<TitleComponent>(TitleComponent{"Robe Ougandaise"}));
    cm.addComponent(product, make_shared<PriceComponent>(PriceComponent{55.5f}));
    cm.addComponent(product, make_shared<CurrencyComponent>(CurrencyComponent{"UGX"}));
    cm.addComponent(product, make_shared<UserIdComponent>(UserIdComponent{77}));
    cm.addComponent(product, make_shared<DescriptionComponent>(DescriptionComponent{"Traditionnelle et élégante"}));
    cm.addComponent(product, make_shared<IsActiveComponent>(IsActiveComponent{true}));
    cm.addComponent(product, make_shared<ViewsComponent>(ViewsComponent{123}));
    cm.addComponent(product, make_shared<ImagesComponent>(ImagesComponent{{"img1.jpg", "img2.jpg"}}));
    cm.addComponent(product, make_shared<CustomFieldsComponent>(CustomFieldsComponent{{
        {"taille", "M"},
        {"couleur", "rouge"}
    }}));

    nlohmann::json result = system.exportAsJson();

    ASSERT_EQ(result.size(), 1);
    auto jsonProduct = result[0];
    EXPECT_EQ(jsonProduct["title"], "Robe Ougandaise");
    EXPECT_FLOAT_EQ(jsonProduct["price"], 55.5f);
    EXPECT_EQ(jsonProduct["currency"], "UGX");
    EXPECT_EQ(jsonProduct["user_id"], 77);
    EXPECT_EQ(jsonProduct["description"], "Traditionnelle et élégante");
    EXPECT_EQ(jsonProduct["is_active"], true);
    EXPECT_EQ(jsonProduct["views"], 123);
    EXPECT_EQ(jsonProduct["images"].size(), 2);
    EXPECT_EQ(jsonProduct["custom_fields"]["taille"], "M");
    EXPECT_EQ(jsonProduct["custom_fields"]["couleur"], "rouge");
}

TEST(ProductSystemTest, ExportAsJson_EmptyWhenNoTitleComponent) {
    EntityManager em;
    ComponentManager cm;
    ProductSystem system(&cm);

    // Création d'une entité sans TitleComponent
    Entity invalidProduct = em.createEntity();
    cm.addComponent(invalidProduct, make_shared<PriceComponent>(PriceComponent{99.9f}));

    nlohmann::json result = system.exportAsJson();
    ASSERT_TRUE(result.empty());
}
