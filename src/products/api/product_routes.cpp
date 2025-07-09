#include "products/services/ProductCache.hpp"
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cstdlib>
#include <memory>
#include <mutex>

static std::unique_ptr<ProductCache> g_productCache;

void registerProductRoutes(crow::App<crow::CORSHandler>& app) {
    CROW_ROUTE(app, "/api/products/all")
    ([] {
        const char* path = std::getenv("PRODUCT_JSON_PATH");
        if (!path) {
            return crow::response(500, "PRODUCT_JSON_PATH non défini");
        }

        static std::once_flag flag;
        std::call_once(flag, [&](){
            g_productCache = std::make_unique<ProductCache>(path);
        });

        try {
            auto& cache = *g_productCache;
            auto responseStr = cache.getJsonResponse();

            crow::response res(responseStr);
            res.set_header("Content-Type", "application/json");
            return res;
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur : ") + e.what());
        }
    });

    CROW_ROUTE(app, "/api/products/reload")
    .methods("POST"_method)
    ([] {
        if (!g_productCache) {
            return crow::response(500, "Cache non initialisé");
        }

        try {
            g_productCache->reload();
            return crow::response(200, "Cache rechargé avec succès");
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur lors du rechargement : ") + e.what());
        }
    });
}
