#include "categories/api/category_routes.hpp"
#include "categories/services/CategoryRepositoryJson.hpp"
#include <nlohmann/json.hpp>
#include <cstdlib>

using json = nlohmann::json;

void registerCategoryRoutes(crow::App<crow::CORSHandler>& app) {

    auto serializeCategory = [](const Category& c) -> json {
        json item = {
            {"id", c.getId()},
            {"name", c.getName()},
            {"image", c.getImageUrl()},
        };
        item["parent_id"] = c.getParentId().has_value() ? json(c.getParentId().value()) : nullptr;
        return item;
    };

    CROW_ROUTE(app, "/api")
    ([] {
        json doc = {
            {"status", "Softadastra API en ligne 🚀"},
            {"endpoints", {
                {"GET /api/products/all", "Liste de tous les produits"},
                {"GET /api/categories/all", "Toutes les catégories"},
                {"GET /api/categories/leaf", "Sous-catégories (feuilles uniquement)"},
                {"GET /api/categories/top", "Catégories racines (top-level)"}
            }}
        };

        crow::response res(doc.dump(2));
        res.set_header("Content-Type", "application/json");
        return res;
    });


    // 🔹 Feuilles
    CROW_ROUTE(app, "/api/categories/leaf")
    ([&serializeCategory]() {
        try {
            const char* path = std::getenv("CATEGORY_JSON_PATH");
            if (!path) {
                return crow::response(500, "CATEGORY_JSON_PATH non défini dans .env");
            }

            CategoryRepositoryJson repo(path);
            auto categories = repo.getLeafSubcategories(0, 20);

            json responseJson;
            responseJson["categories"] = json::array();
            for (const auto& c : categories) {
                responseJson["categories"].push_back(serializeCategory(c));
            }

            crow::response res(responseJson.dump());
            res.set_header("Content-Type", "application/json");
            return res;

        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });

    // 🔹 Top Level
    CROW_ROUTE(app, "/api/categories/top")
    ([&serializeCategory]() {
        try {
            const char* path = std::getenv("CATEGORY_JSON_PATH_TOP_LEVEL");
            if (!path) {
                return crow::response(500, "CATEGORY_JSON_PATH_TOP_LEVEL non défini dans .env");
            }

            CategoryRepositoryJson repo(path);
            auto categories = repo.getTopLevelCategories();

            json responseJson;
            responseJson["categories"] = json::array();
            for (const auto& c : categories) {
                responseJson["categories"].push_back(serializeCategory(c));
            }

            crow::response res(responseJson.dump());
            res.set_header("Content-Type", "application/json");
            return res;

        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });

    // 🔹 All
    CROW_ROUTE(app, "/api/categories/all")
    ([&serializeCategory]() {
        try {
            const char* path = std::getenv("CATEGORY_JSON_PATH_ALL");
            if (!path) {
                return crow::response(500, "CATEGORY_JSON_PATH_ALL non défini dans .env");
            }

            CategoryRepositoryJson repo(path);
            auto categories = repo.getAllCategories();

            json responseJson;
            responseJson["categories"] = json::array();
            for (const auto& c : categories) {
                responseJson["categories"].push_back(serializeCategory(c));
            }

            crow::response res(responseJson.dump());
            res.set_header("Content-Type", "application/json");
            return res;

        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });
}
