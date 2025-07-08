#include "products/api/product_routes.hpp"
#include "products/services/ProductService.hpp"
#include <nlohmann/json.hpp>
#include <cstdlib>

using json = nlohmann::json;

void registerProductRoutes(crow::App<crow::CORSHandler>& app) {

    CROW_ROUTE(app, "/api/products/all")
    ([] {
        try {
            const char* path = std::getenv("PRODUCT_JSON_PATH");
            if (!path) {
                return crow::response(500, "PRODUCT_JSON_PATH non défini");
            }

            ProductService service(path);
            auto products = service.getAllProducts();

            json response;
            response["data"] = json::array();

            for (const auto& p : products) {
                json productJson = {
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
                };
                response["data"].push_back(productJson);
            }

            crow::response res(response.dump());
            res.set_header("Content-Type", "application/json");
            return res;

        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erreur : ") + e.what());
        }
    });
}
