#include "products/services/ProductCache.hpp"
#include "products/services/ProductService.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ProductCache::ProductCache(const std::string& path)
    : jsonFilePath(path), isLoaded(false) {}

std::string ProductCache::getJsonResponse() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!isLoaded) {
        loadProducts();
    }
    return cachedJson;
}

void ProductCache::reload() {
    std::lock_guard<std::mutex> lock(mutex);
    loadProducts();
}

void ProductCache::loadProducts() {
    ProductService service(jsonFilePath);
    auto products = service.getAllProducts();

    json response;
    response["data"] = json::array();

    for (const auto& p : products) {
        response["data"].push_back({
            {"id", p.id},
            {"title", p.title},
            {"image_url", p.image_url},
            {"city_name", p.city_name},
            {"country_image_url", p.country_image_url},
            {"currency", p.currency},
            {"formatted_price", p.formatted_price},
            {"converted_price", p.converted_price},
            {"sizes", p.sizes},
            {"colors", p.colors}
        });
    }

    cachedJson = response.dump();
    isLoaded = true;
}
