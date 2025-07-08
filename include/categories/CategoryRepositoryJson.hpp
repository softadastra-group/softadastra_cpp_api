#ifndef CATEGORYREPOSITORYJSON_HPP
#define CATEGORYREPOSITORYJSON_HPP

#include <vector>
#include <string>
#include <cstdint>
#include "categories/Category.hpp"

class CategoryRepositoryJson {
public:
    CategoryRepositoryJson(const std::string& filepath);
    
    std::vector<Category> getLeafSubcategories(std::size_t offset = 0, std::size_t limit = 20);
    std::vector<Category> getTopLevelCategories();
    std::vector<Category> getAllCategories();

private:
    std::string jsonFilePath;
};

#endif // CATEGORYREPOSITORYJSON_HPP
