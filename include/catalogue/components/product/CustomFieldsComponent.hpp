#pragma once
#include <map>
#include <string>

struct CustomFieldsComponent {
    std::map<std::string, std::string> fields; // Ex: { "RAM": "8GB", "ROM": "128GB" }
};
