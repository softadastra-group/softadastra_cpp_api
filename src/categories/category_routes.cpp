#include "categories/category_routes.hpp"
#include "categories/CategoryRepositoryJson.hpp"
#include <nlohmann/json.hpp>
#include <cstdlib>

using json = nlohmann::json;

void registerCategoryRoutes(crow::App<crow::CORSHandler>& app) {
    CROW_ROUTE(app, "/api/categories/leaf")
    ([]() {
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
                responseJson["categories"].push_back({
                    {"id", c.getId()},
                    {"name", c.getName()},
                    {"image", c.getImageUrl()},
                    {"parent_id", c.getParentId()}
                });
            }

            crow::response res(responseJson.dump());
            res.set_header("Content-Type", "application/json");
            return res;

        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });
}
