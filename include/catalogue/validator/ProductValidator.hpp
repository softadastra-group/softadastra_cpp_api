// include/catalogue/validators/ProductValidator.hpp
#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>

namespace catalogue {
    namespace validators {

        class ProductValidator {
        public:
            static void validate(
                const std::string& title,
                float price,
                float originalPrice,
                const std::string& currency,
                int quantity,
                const std::string& description,
                int categoryId,
                int userId,
                int brandId,
                int conditionId,
                int packageFormatId,
                const std::string& status,
                int views,
                const std::vector<std::string>& images,
                const std::vector<int>& sizeIds,
                const std::vector<int>& colorIds,
                const std::map<std::string, std::string>& customFields,
                const std::vector<int>& similarProducts
            ) {
                if (title.empty() || title.size() < 3)
                    throw std::invalid_argument("Title must be at least 3 characters long.");

                if (price <= 0)
                    throw std::invalid_argument("Price must be positive.");

                if (originalPrice < price)
                    throw std::invalid_argument("Original price must be >= current price.");

                if (currency.empty())
                    throw std::invalid_argument("Currency must not be empty.");

                if (quantity < 0)
                    throw std::invalid_argument("Quantity cannot be negative.");

                if (description.empty())
                    throw std::invalid_argument("Description must not be empty.");

                if (categoryId <= 0 || userId <= 0 || brandId <= 0 || conditionId <= 0 || packageFormatId <= 0)
                    throw std::invalid_argument("IDs must be positive integers.");

                static const std::vector<std::string> validStatuses = {"active", "inactive", "draft"};
                if (std::find(validStatuses.begin(), validStatuses.end(), status) == validStatuses.end())
                    throw std::invalid_argument("Invalid status. Must be 'active', 'inactive', or 'draft'.");

                if (views < 0)
                    throw std::invalid_argument("Views cannot be negative.");

                for (const auto& image : images) {
                    if (image.empty())
                        throw std::invalid_argument("Image URL cannot be empty.");
                }

                for (const auto& [key, value] : customFields) {
                    if (key.empty() || value.empty())
                        throw std::invalid_argument("Custom fields must not have empty keys or values.");
                }

                (void)sizeIds;
                (void)colorIds;
                (void)similarProducts;
            }
        };

    } // namespace validators
} // namespace catalogue
