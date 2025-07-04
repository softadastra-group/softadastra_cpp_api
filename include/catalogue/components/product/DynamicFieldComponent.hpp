#ifndef DYNAMIC_FIELD_COMPONENT_HPP
#define DYNAMIC_FIELD_COMPONENT_HPP

#include <unordered_map>
#include <string>

struct DynamicFieldComponent {
    std::unordered_map<std::string, std::string> fields;

    explicit DynamicFieldComponent(const std::unordered_map<std::string, std::string>& data)
        : fields(data) {}
};

#endif // DYNAMIC_FIELD_COMPONENT_HPP
