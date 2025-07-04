#ifndef COLOR_COMPONENT_HPP
#define COLOR_COMPONENT_HPP

#include <vector>

struct ColorsComponent {
    std::vector<int> colorIds;

    explicit ColorsComponent(const std::vector<int>& colors)
        : colorIds(colors) {}
};

#endif // COLOR_COMPONENT_HPP
