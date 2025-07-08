#include <catch2/catch_test_macros.hpp>
#include "categories/services/CategoryRepositoryJson.hpp"

#include <fstream>
#include <cstdio>

TEST_CASE("CategoryRepositoryJson retourne les catégories feuilles") {
    const std::string path = "categories_test.json";

    std::ofstream out(path);
    out << R"({
        "categories": [
            {
                "id": 1,
                "name": "Electronics",
                "image": "img.jpg",
                "parent_id": null
            },
            {
                "id": 2,
                "name": "Phones",
                "image": "img2.jpg",
                "parent_id": 1
            }
        ]
    })";
    out.close();

    CategoryRepositoryJson repo(path);
    auto cats = repo.getLeafSubcategories(0, 10);

    REQUIRE(cats.size() == 2);
    CHECK(cats[0].getId() == 1);
    CHECK(cats[1].getParentId().value() == 1);

    std::remove(path.c_str());
}
