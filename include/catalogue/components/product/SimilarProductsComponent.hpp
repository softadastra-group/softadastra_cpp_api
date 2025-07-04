#ifndef SIMILAR_PRODUCTS_COMPONENT_HPP
#define SIMILAR_PRODUCTS_COMPONENT_HPP

#include <vector>

struct SimilarProductsComponent {
    std::vector<int> similarProductIds;

    explicit SimilarProductsComponent(const std::vector<int>& ids)
        : similarProductIds(ids) {}
};

#endif // SIMILAR_PRODUCTS_COMPONENT_HPP
