#include "products/services/ProductService.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

ProductService::ProductService(const std::string& path)
    : jsonFilePath(path) {}

std::vector<Product> ProductService::getAllProducts() {
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier produits : " + jsonFilePath);
    }

    json j;
    file >> j;

    std::vector<Product> products;
    const auto& items = j["data"];

    for (const auto& item : items) {
        Product p;
        p.id = item["id"];
        p.title = item["title"];
        p.image_url = item["image_url"];
        p.city_name = item["city_name"];
        p.country_image_url = item["country_image_url"];
        p.currency = item["currency"];
        p.formatted_price = item["formatted_price"];
        p.converted_price = item["converted_price"];

        if (item.contains("sizes") && item["sizes"].is_array()) {
            for (const auto& s : item["sizes"]) p.sizes.push_back(s);
        }

        if (item.contains("colors") && item["colors"].is_array()) {
            for (const auto& c : item["colors"]) p.colors.push_back(c);
        }

        products.push_back(p);
    }

    return products;
}
