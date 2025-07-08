#include <catch2/catch_test_macros.hpp>
#include "products/services/ProductService.hpp"
#include "products/models/Product.hpp"
#include <fstream>
#include <cstdio> // pour remove()

TEST_CASE("ProductService::getAllProducts lit correctement les produits JSON") {
    const std::string testFilePath = "test_products.json";

    // Création d’un fichier JSON de test
    std::ofstream out(testFilePath);
    out << R"({
        "data": [
            {
                "id": 1,
                "title": "Test Product",
                "image_url": "https://example.com/img.jpg",
                "city_name": "Kampala",
                "country_image_url": "https://example.com/flag.jpg",
                "currency": "UGX",
                "formatted_price": "UGX 50,000",
                "converted_price": "13 USD",
                "sizes": ["M", "L"],
                "colors": ["Red", "Blue"]
            }
        ]
    })";
    out.close();

    // Initialisation du service avec le fichier
    ProductService service(testFilePath);

    // Appel de la méthode
    std::vector<Product> products;

    REQUIRE_NOTHROW(products = service.getAllProducts());
    REQUIRE(products.size() == 1);

    const Product& p = products[0];
    CHECK(p.getId() == 1);
    CHECK(p.getTitle() == "Test Product");
    CHECK(p.getImageUrl() == "https://example.com/img.jpg");
    CHECK(p.getCityName() == "Kampala");
    CHECK(p.getCountryImageUrl() == "https://example.com/flag.jpg");
    CHECK(p.getCurrency() == "UGX");
    CHECK(p.getFormattedPrice() == "UGX 50,000");
    CHECK(p.getConvertedPrice() == "13 USD");
    CHECK(p.getSizes() == std::vector<std::string>{"M", "L"});
    CHECK(p.getColors() == std::vector<std::string>{"Red", "Blue"});

    // Nettoyage du fichier temporaire
    std::remove(testFilePath.c_str());
}
