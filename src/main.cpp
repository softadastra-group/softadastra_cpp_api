// #include "crow.h"
// #include "product/routes/product_routes.hpp"

// int main() {
//     crow::SimpleApp app;

//     Routes::registerProductRoutes(app); 

//     app.port(8080).multithreaded().run();
// }
// #include "catalogue/ecs/EntityManager.hpp"
// #include "catalogue/ecs/ComponentManager.hpp"
// #include "catalogue/ecs/SystemManager.hpp"
// #include "catalogue/entities/EntityBuilder.hpp"
// #include "catalogue/systems/ProductSystem.hpp"

#include "utils/logger.hpp"
#include <vector>
#include "tools/ImageOptimizer.hpp"

int main() {
    using namespace Softadastra;
    
    enableColor(true);
    enableDailyLogRotation(true);
    enableFileLogging(true);
    // EntityManager em;
    // ComponentManager cm;
    // SystemManager sm;

    // // Ajout du système
    // sm.addSystem(std::make_unique<ProductSystem>(&cm));

    // // Créer un produit 1 avec images et champs dynamiques
    // Entity p1 = EntityBuilder::createProduct(
    //     em, cm,
    //     "Samsung Galaxy A34",
    //     229.99f,
    //     250.00f,
    //     "USD",
    //     10,
    //     "Smartphone performant avec bon rapport qualité/prix",
    //     3, // category_id
    //     101, // user_id
    //     5, // brand_id
    //     1, // condition_id
    //     2, // package_format_id
    //     "active",
    //     0, // views
    //     {"a34-front.jpg", "a34-back.jpg"},
    //     {1, 2}, // sizes
    //     {4, 5}, // colors
    //     {
    //         {"RAM", "6GB"},
    //         {"ROM", "128GB"},
    //         {"Battery", "5000mAh"}
    //     },
    //     { } // similar products
    // );

    // // Créer un produit 2 sans images ni champs dynamiques
    // Entity p2 = EntityBuilder::createProduct(
    //     em, cm,
    //     "Sac à dos Urban",
    //     49.99f,
    //     60.00f,
    //     "USD",
    //     5,
    //     "Sac robuste pour usage quotidien",
    //     7,
    //     102,
    //     3,
    //     1,
    //     1,
    //     "active",
    //     10
    // );

    // std::vector<int> v = {1,2,3,4,5,6};
    // Softadastra::print(v);


    log(LogLevel::INFO, "Application started");
    log(LogLevel::WARNING, "Disk usage is high.");
    log(LogLevel::ERROR, "Failed to connect to database.");

    std::string input = "test.jpg";
    std::string output = "output_compressed.jpg";

    if (Tools::ImageOptimizer::optimize(input, output, 800, 70)) {
        std::cout << "Image optimisée avec succès." << std::endl;
    } else {
        std::cout << "Échec de l’optimisation." << std::endl;
    }

    return 0;

    //sm.updateAll();

    return 0;
}

// Appel de updateAll() → affichage
// Inclure le symbole +, l’indicatif du pays et l’indicatif régional. 