#include "categories/services/CategoryCache.hpp"
#include "categories/services/CategoryRepositoryJson.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

CategoryCache::CategoryCache(const std::string& path)
    : jsonFilePath(path), isLoaded(false) {}

void CategoryCache::loadCategories() {
    CategoryRepositoryJson repo(jsonFilePath);

    auto leafCats = repo.getLeafSubcategories(0, 1000);
    auto topLevelCats = repo.getTopLevelCategories();
    auto allCats = repo.getAllCategories();

    auto serialize = [](const Category& c) -> json {
        json item = {
            {"id", c.getId()},
            {"name", c.getName()},
            {"image", c.getImageUrl()},
            {"product_count", c.getProductCount()}
        };
        item["parent_id"] = c.getParentId().has_value() ? json(c.getParentId().value()) : nullptr;
        return item;
    };

    json leafJsonObj;
    leafJsonObj["categories"] = json::array();
    for (const auto& c : leafCats) leafJsonObj["categories"].push_back(serialize(c));
    leafJson = leafJsonObj.dump();

    json topJsonObj;
    topJsonObj["categories"] = json::array();
    for (const auto& c : topLevelCats) topJsonObj["categories"].push_back(serialize(c));
    topLevelJson = topJsonObj.dump();

    json allJsonObj;
    allJsonObj["categories"] = json::array();
    for (const auto& c : allCats) allJsonObj["categories"].push_back(serialize(c));
    allJson = allJsonObj.dump();

    isLoaded = true;
}

std::string CategoryCache::getLeafCategoriesJson() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!isLoaded) loadCategories();
    return leafJson;
}

std::string CategoryCache::getTopLevelCategoriesJson() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!isLoaded) loadCategories();
    return topLevelJson;
}

std::string CategoryCache::getAllCategoriesJson() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!isLoaded) loadCategories();
    return allJson;
}

void CategoryCache::reload() {
    std::lock_guard<std::mutex> lock(mutex);
    loadCategories();
}
