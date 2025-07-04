#ifndef SIZE_COMPONENT_HPP
#define SIZE_COMPONENT_HPP

#include <vector>

struct SizesComponent {
    std::vector<int> sizeIds;

    explicit SizesComponent(const std::vector<int>& sizes)
        : sizeIds(sizes) {}
};

#endif // SIZE_COMPONENT_HPP
