#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <vector>
#include <optional>
#include <cstdint>

class Product {
public:
    uint32_t id;
    std::string title;
    std::string image_url;
    std::string city_name;
    std::string country_image_url;
    std::string currency;
    std::string formatted_price;
    std::string converted_price;
    std::vector<std::string> sizes;
    std::vector<std::string> colors;
};

#endif // PRODUCT_HPP
