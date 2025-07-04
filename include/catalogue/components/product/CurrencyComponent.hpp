#pragma once
#include <string>
struct CurrencyComponent {
    std::string currency;
    explicit CurrencyComponent(const std::string& c) : currency(c) {}
};
