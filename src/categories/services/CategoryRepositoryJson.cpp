#include "categories/services/CategoryRepositoryJson.hpp"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

CategoryRepositoryJson::CategoryRepositoryJson(const std::string& filepath)
    : jsonFilePath(filepath) {}

std::vector<Category> CategoryRepositoryJson::getLeafSubcategories(std::size_t offset, std::size_t limit) {
   std::ifstream file(jsonFilePath);
    if (!file) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + jsonFilePath);
    }

    json j;
    file >> j;

    const auto& all = j["categories"];
    std::vector<Category> result;

    std::size_t total = all.size();
    std::size_t end = std::min(offset + limit, total);

    for (std::size_t i = offset; i < end; ++i) {
        const auto& item = all[i];

        if (!item.contains("id") || !item.contains("name") || !item.contains("image")) continue;

        std::optional<uint32_t> parentId;
        if (item.contains("parent_id") && !item["parent_id"].is_null()) {
            parentId = item["parent_id"].get<uint32_t>();
        }

        Category cat(
            item["name"].get<std::string>(),
            parentId,
            item["image"].get<std::string>()
        );
        cat.setId(item["id"].get<std::uint32_t>());
        result.push_back(cat);
    }

    return result;
}

std::vector<Category> CategoryRepositoryJson::getTopLevelCategories() {
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + jsonFilePath);
    }

    json j;
    file >> j;

    if (!j.contains("data") || !j["data"].is_array()) {
        throw std::runtime_error("Fichier JSON invalide : clé 'data' manquante ou invalide");
    }

    const auto& all = j["data"];
    std::vector<Category> result;

    for (const auto& item : all) {
        if (!item.contains("id") || !item.contains("name") || !item.contains("image")) continue;

        std::optional<uint32_t> parentId;
        if (item.contains("parent_id") && !item["parent_id"].is_null()) {
            parentId = item["parent_id"].get<uint32_t>();
        }

        if (!parentId.has_value()) {
            Category cat(
                item["name"].get<std::string>(),
                std::nullopt,
                item["image"].get<std::string>()
            );
            cat.setId(item["id"].get<std::uint32_t>());
            result.push_back(cat);
        }
    }

    return result;
}

std::vector<Category> CategoryRepositoryJson::getAllCategories() {
    return getLeafSubcategories(0, 1000); // Assuming a large enough limit to fetch all categories
}