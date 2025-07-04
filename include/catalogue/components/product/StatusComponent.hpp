#pragma once
#include <string>

struct StatusComponent {
    std::string status;

    explicit StatusComponent(const std::string& s) : status(s) {}
};
