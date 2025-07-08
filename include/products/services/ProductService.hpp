#ifndef PRODUCT_SERVICE_HPP
#define PRODUCT_SERVICE_HPP

#include "products/models/Product.hpp"
#include <vector>
#include <string>

class ProductService {
public:
    ProductService(const std::string& jsonPath);
    std::vector<Product> getAllProducts();

private:
    std::string jsonFilePath;
};

#endif
