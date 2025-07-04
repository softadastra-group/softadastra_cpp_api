#pragma once
#include <string>
struct DescriptionComponent {
    std::string description;
    explicit DescriptionComponent(const std::string& d) : description(d) {}
};
