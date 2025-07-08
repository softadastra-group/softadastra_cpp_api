#ifndef PRODUCT_ROUTES_HPP
#define PRODUCT_ROUTES_HPP

#include <crow.h>
#include <crow/middlewares/cors.h>

void registerProductRoutes(crow::App<crow::CORSHandler>& app);

#endif
