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
        // 🔒 Validation obligatoire
        if (!item.contains("id") || !item["id"].is_number_unsigned()) {
            throw std::runtime_error("Produit sans ID trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("title") || !item["title"].is_string()) {
            throw std::runtime_error("Produit sans titre trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("image_url") || !item["image_url"].is_string()) {
            throw std::runtime_error("Produit sans image_url trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("city_name") || !item["city_name"].is_string()) {
            throw std::runtime_error("Produit sans city_name trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("country_image_url") || !item["country_image_url"].is_string()) {
            throw std::runtime_error("Produit sans country_image_url trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("currency") || !item["currency"].is_string()) {
            throw std::runtime_error("Produit sans currency trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("formatted_price") || !item["formatted_price"].is_string()) {
            throw std::runtime_error("Produit sans formatted_price trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("converted_price") || !item["converted_price"].is_string()) {
            throw std::runtime_error("Produit sans converted_price trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("sizes") || !item["sizes"].is_array()) {
            throw std::runtime_error("Produit sans sizes trouvé dans le fichier JSON : " + jsonFilePath);
        }
        if (!item.contains("colors") || !item["colors"].is_array()) {
            throw std::runtime_error("Produit sans colors trouvé dans le fichier JSON : " + jsonFilePath);
        }

        // ✅ Création directe du produit
        Product p(
            item["title"].get<std::string>(),
            item["image_url"].get<std::string>(),
            item["city_name"].get<std::string>(),
            item["country_image_url"].get<std::string>(),
            item["currency"].get<std::string>(),
            item["formatted_price"].get<std::string>(),
            item["converted_price"].get<std::string>(),
            item["sizes"].get<std::vector<std::string>>(),
            item["colors"].get<std::vector<std::string>>()
        );

        p.setId(item["id"].get<uint32_t>());

        products.push_back(std::move(p)); // 👈 Move pour éviter copie inutile
    }

    return products;
}
