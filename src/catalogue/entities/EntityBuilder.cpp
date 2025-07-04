#include "catalogue/entities/EntityBuilder.hpp"

Entity EntityBuilder::createProduct(EntityManager& em, ComponentManager& cm,
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

    const std::vector<std::string>& images,
    const std::vector<int>& sizeIds,
    const std::vector<int>& colorIds,
    const std::map<std::string, std::string>& customFields,
    const std::vector<int>& similarProducts
) {
    Entity entity = em.createEntity();

    catalogue::validators::ProductValidator::validate(
        title, price, originalPrice, currency, quantity, description,
        categoryId, userId, brandId, conditionId, packageFormatId,
        status, views, images, sizeIds, colorIds, customFields, similarProducts
    );

    cm.addComponent<TitleComponent>(entity, std::make_shared<TitleComponent>(title));
    cm.addComponent<PriceComponent>(entity, std::make_shared<PriceComponent>(price));
    cm.addComponent<OriginalPriceComponent>(entity, std::make_shared<OriginalPriceComponent>(originalPrice));
    cm.addComponent<CurrencyComponent>(entity, std::make_shared<CurrencyComponent>(currency));
    cm.addComponent<StockComponent>(entity, std::make_shared<StockComponent>(quantity));
    cm.addComponent<DescriptionComponent>(entity, std::make_shared<DescriptionComponent>(description));
    cm.addComponent<CategoryIdComponent>(entity, std::make_shared<CategoryIdComponent>(categoryId));
    cm.addComponent<UserIdComponent>(entity, std::make_shared<UserIdComponent>(userId));
    cm.addComponent<BrandIdComponent>(entity, std::make_shared<BrandIdComponent>(brandId));
    cm.addComponent<ConditionIdComponent>(entity, std::make_shared<ConditionIdComponent>(conditionId));
    cm.addComponent<PackageFormatIdComponent>(entity, std::make_shared<PackageFormatIdComponent>(packageFormatId));
    cm.addComponent<StatusComponent>(entity, std::make_shared<StatusComponent>(status));
    cm.addComponent<ViewsComponent>(entity, std::make_shared<ViewsComponent>(views));

    if (!images.empty()) {
        cm.addComponent<ImagesComponent>(entity, std::make_shared<ImagesComponent>(ImagesComponent{images}));
    }

    if (!sizeIds.empty()) {
        cm.addComponent<SizesComponent>(entity, std::make_shared<SizesComponent>(SizesComponent{sizeIds}));
    }

    if (!colorIds.empty()) {
        cm.addComponent<ColorsComponent>(entity, std::make_shared<ColorsComponent>(ColorsComponent{colorIds}));
    }

    if (!customFields.empty()) {
        cm.addComponent<CustomFieldsComponent>(entity, std::make_shared<CustomFieldsComponent>(CustomFieldsComponent{customFields}));
    }

    if (!similarProducts.empty()) {
        cm.addComponent<SimilarProductsComponent>(entity, std::make_shared<SimilarProductsComponent>(SimilarProductsComponent{similarProducts}));
    }

    // Optionnels : si tu veux gérer slug / timestamps / isActive ailleurs, tu peux les ignorer ou les ajouter ici :
    cm.addComponent<SlugComponent>(entity, std::make_shared<SlugComponent>(SlugComponent{"auto-generated-slug"}));
    cm.addComponent<CreatedAtComponent>(entity, std::make_shared<CreatedAtComponent>(CreatedAtComponent{"2025-06-25T12:00:00Z"}));
    cm.addComponent<UpdatedAtComponent>(entity, std::make_shared<UpdatedAtComponent>(UpdatedAtComponent{"2025-06-25T12:00:00Z"}));
    cm.addComponent<IsActiveComponent>(entity, std::make_shared<IsActiveComponent>(IsActiveComponent{true}));

    return entity;
}
