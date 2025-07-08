#include "utils/EnvLoader.hpp"
#include "categories/api/category_routes.hpp"
#include "products/api/product_routes.hpp"

#include <crow.h>
#include <crow/middlewares/cors.h>

int main() {
    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Content-Type", "Authorization")
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .max_age(86400);

    EnvLoader::load("../.env");

    registerCategoryRoutes(app);
    registerProductRoutes(app);

    app.port(18080).multithreaded().run();

    return 0;
}
