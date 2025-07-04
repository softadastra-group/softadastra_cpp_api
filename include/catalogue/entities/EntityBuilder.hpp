#pragma once

#include <string>
#include <vector>
#include <map>

#include "catalogue/ecs/EntityManager.hpp"
#include "catalogue/ecs/ComponentManager.hpp"

// Composants de base du produit
#include "catalogue/components/product/TitleComponent.hpp"
#include "catalogue/components/product/PriceComponent.hpp"
#include "catalogue/components/product/OriginalPriceComponent.hpp"
#include "catalogue/components/product/CurrencyComponent.hpp"
#include "catalogue/components/product/StockComponent.hpp"
#include "catalogue/components/product/DescriptionComponent.hpp"
#include "catalogue/components/product/CategoryIdComponent.hpp"
#include "catalogue/components/product/UserIdComponent.hpp"
#include "catalogue/components/product/BrandIdComponent.hpp"
#include "catalogue/components/product/ConditionIdComponent.hpp"
#include "catalogue/components/product/PackageFormatIdComponent.hpp"
#include "catalogue/components/product/StatusComponent.hpp"
#include "catalogue/components/product/ViewsComponent.hpp"

// Métadonnées
#include "catalogue/components/product/SlugComponent.hpp"
#include "catalogue/components/product/CreatedAtComponent.hpp"
#include "catalogue/components/product/UpdatedAtComponent.hpp"
#include "catalogue/components/product/IsActiveComponent.hpp"

// Collections
#include "catalogue/components/product/ImagesComponent.hpp"
#include "catalogue/components/product/SizesComponent.hpp"
#include "catalogue/components/product/ColorsComponent.hpp"
#include "catalogue/components/product/CustomFieldsComponent.hpp"
#include "catalogue/components/product/SimilarProductsComponent.hpp"
#include "catalogue/validator/ProductValidator.hpp"

class EntityBuilder {
public:
    static Entity createProduct(EntityManager& em, ComponentManager& cm,
        const std::string& title,
        float price,
        float originalPrice,
        const std::string& currency,
        int quantity,
        const std::string& description,
        int categoryId,
        int userId,
        int brandId,
        int conditionId,
        int packageFormatId,
        const std::string& status,
        int views,

        const std::vector<std::string>& images = {},
        const std::vector<int>& sizeIds = {},
        const std::vector<int>& colorIds = {},
        const std::map<std::string, std::string>& customFields = {},
        const std::vector<int>& similarProducts = {}
    );
};
