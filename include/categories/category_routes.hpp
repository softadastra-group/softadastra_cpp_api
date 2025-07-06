#ifndef CATEGORY_ROUTES_HPP
#define CATEGORY_ROUTES_HPP

#include <crow.h>
#include <crow/middlewares/cors.h>

void registerCategoryRoutes(crow::App<crow::CORSHandler>& app);

#endif
