#ifndef CATEGORY_CACHE_HPP
#define CATEGORY_CACHE_HPP

#include "categories/models/Category.hpp"
#include <string>
#include <mutex>

class CategoryCache {
public:
    explicit CategoryCache(const std::string& jsonPath);

    // Méthodes thread-safe pour récupérer les données en JSON
    std::string getLeafCategoriesJson();
    std::string getTopLevelCategoriesJson();
    std::string getAllCategoriesJson();

    // Forcer le rechargement du cache
    void reload();

private:
    void loadCategories();

    std::string jsonFilePath;
    std::string leafJson;
    std::string topLevelJson;
    std::string allJson;

    bool isLoaded;
    std::mutex mutex;
};

#endif // CATEGORY_CACHE_HPP
