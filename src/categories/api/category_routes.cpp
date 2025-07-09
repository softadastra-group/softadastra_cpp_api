#include "categories/services/CategoryCache.hpp"
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cstdlib>
#include <memory>
#include <mutex>

// 🔸 Une instance de cache par fichier
static std::unique_ptr<CategoryCache> g_leafCache;
static std::unique_ptr<CategoryCache> g_topCache;
static std::unique_ptr<CategoryCache> g_allCache;

void registerCategoryRoutes(crow::App<crow::CORSHandler>& app) {

    // 🔹 Feuilles
    CROW_ROUTE(app, "/api/categories/leaf")
    ([] {
        const char* path = std::getenv("CATEGORY_JSON_PATH");
        if (!path) return crow::response(500, "CATEGORY_JSON_PATH non défini");

        static std::once_flag flagLeaf;
        std::call_once(flagLeaf, [&](){
            g_leafCache = std::make_unique<CategoryCache>(path);
        });

        try {
            return crow::response(g_leafCache->getLeafCategoriesJson());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });

    // 🔹 Top-level (racines)
    CROW_ROUTE(app, "/api/categories/top")
    ([] {
        const char* path = std::getenv("CATEGORY_JSON_PATH_TOP_LEVEL");
        if (!path) return crow::response(500, "CATEGORY_JSON_PATH_TOP_LEVEL non défini");

        static std::once_flag flagTop;
        std::call_once(flagTop, [&](){
            g_topCache = std::make_unique<CategoryCache>(path);
        });

        try {
            return crow::response(g_topCache->getTopLevelCategoriesJson());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });

    // 🔹 Toutes
    CROW_ROUTE(app, "/api/categories/all")
    ([] {
        const char* path = std::getenv("CATEGORY_JSON_PATH_ALL");
        if (!path) return crow::response(500, "CATEGORY_JSON_PATH_ALL non défini");

        static std::once_flag flagAll;
        std::call_once(flagAll, [&](){
            g_allCache = std::make_unique<CategoryCache>(path);
        });

        try {
            return crow::response(g_allCache->getAllCategoriesJson());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur serveur : ") + e.what());
        }
    });

    // 🔄 Rechargement manuel (utile après changement fichier)
    CROW_ROUTE(app, "/api/categories/reload")
    .methods("POST"_method)
    ([] {
        try {
            if (g_leafCache) g_leafCache->reload();
            if (g_topCache) g_topCache->reload();
            if (g_allCache) g_allCache->reload();
            return crow::response(200, "Caches rechargés avec succès");
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur lors du rechargement : ") + e.what());
        }
    });
}
