#include "categories/CategoryRepositoryJson.hpp"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

CategoryRepositoryJson::CategoryRepositoryJson(const std::string& filepath)
    : jsonFilePath(filepath) {}

std::vector<Category> CategoryRepositoryJson::getLeafSubcategories(std::size_t offset, std::size_t limit) {
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
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

        Category cat(
            item["name"].get<std::string>(),
            item["parent_id"].get<std::uint32_t>(),
            item["image"].get<std::string>()
        );
        cat.setId(item["id"].get<std::uint32_t>());

        result.push_back(cat);
    }

    return result;
}
