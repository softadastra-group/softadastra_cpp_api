#include "categories/services/CategoryCache.hpp"
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cstdlib>
#include <memory>
#include <mutex>

static std::unique_ptr<CategoryCache> g_categoryCache;

void registerCategoryRoutes(crow::App<crow::CORSHandler>& app) {
    CROW_ROUTE(app, "/api/categories/leaf")
    ([] {
        const char* path = std::getenv("CATEGORY_JSON_PATH");
        if (!path) return crow::response(500, "CATEGORY_JSON_PATH non défini");

        static std::once_flag flag;
        std::call_once(flag, [&](){
            g_categoryCache = std::make_unique<CategoryCache>(path);
        });

        try {
            return crow::response(g_categoryCache->getLeafCategoriesJson());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });

    CROW_ROUTE(app, "/api/categories/top")
    ([] {
        const char* path = std::getenv("CATEGORY_JSON_PATH_TOP_LEVEL");
        if (!path) return crow::response(500, "CATEGORY_JSON_PATH_TOP_LEVEL non défini");

        static std::once_flag flag;
        std::call_once(flag, [&](){
            g_categoryCache = std::make_unique<CategoryCache>(path);
        });

        try {
            return crow::response(g_categoryCache->getTopLevelCategoriesJson());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });

    CROW_ROUTE(app, "/api/categories/all")
    ([] {
        const char* path = std::getenv("CATEGORY_JSON_PATH_ALL");
        if (!path) return crow::response(500, "CATEGORY_JSON_PATH_ALL non défini");

        static std::once_flag flag;
        std::call_once(flag, [&](){
            g_categoryCache = std::make_unique<CategoryCache>(path);
        });

        try {
            return crow::response(g_categoryCache->getAllCategoriesJson());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });

    CROW_ROUTE(app, "/api/categories/reload")
    .methods("POST"_method)
    ([] {
        if (!g_categoryCache) return crow::response(500, "Cache non initialisé");
        try {
            g_categoryCache->reload();
            return crow::response(200, "Cache rechargé avec succès");
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur lors du rechargement : ") + e.what());
        }
    });
}
