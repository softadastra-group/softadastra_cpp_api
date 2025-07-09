#ifndef PRODUCT_CACHE_HPP
#define PRODUCT_CACHE_HPP

#include "products/models/Product.hpp"
#include <string>
#include <vector>
#include <mutex>

class ProductCache {
public:
    explicit ProductCache(const std::string& jsonPath);

    // Retourne la réponse JSON pré-calculée (thread-safe)
    std::string getJsonResponse();

    // Force le rechargement des produits (thread-safe)
    void reload();

private:
    void loadProducts();

    std::string jsonFilePath;
    std::string cachedJson;
    bool isLoaded;
    std::mutex mutex;
};

#endif // PRODUCT_CACHE_HPP
