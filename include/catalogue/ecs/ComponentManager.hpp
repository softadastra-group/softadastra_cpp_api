#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <optional>
#include <memory>
#include <vector>
#include <functional>

using Entity = std::uint32_t;

class ComponentManager {
    std::unordered_map<std::type_index, std::unordered_map<Entity, std::any>> components;

    template<typename T>
    std::shared_ptr<T>* getRawPtr(Entity entity) {
        auto itType = components.find(typeid(T));
        if (itType == components.end())
            return nullptr;

        auto& innerMap = itType->second;
        auto itEntity = innerMap.find(entity);
        if (itEntity == innerMap.end())
            return nullptr;

        try {
            return &std::any_cast<std::shared_ptr<T>&>(itEntity->second);
        } catch (const std::bad_any_cast&) {
            return nullptr;
        }
    }

public:
    template<typename T>
    bool addComponent(Entity entity, std::shared_ptr<T> component) {
        if (hasComponent<T>(entity))
            return false;

        components[typeid(T)][entity] = component;
        return true;
    }

    template<typename T>
    std::optional<std::reference_wrapper<T>> getComponent(Entity entity) {
        auto ptr = getRawPtr<T>(entity);
        if (!ptr || !(*ptr))
            return std::nullopt;

        return std::ref(**ptr);
    }

    template<typename T>
    bool removeComponent(Entity entity) {
        auto ptr = getRawPtr<T>(entity);
        if (!ptr)
            return false;

        ptr->reset();

        auto& innerMap = components[typeid(T)];
        innerMap.erase(entity);

        if (innerMap.empty())
            components.erase(typeid(T));

        return true;
    }

    template<typename T>
    bool hasComponent(Entity entity) {
        auto ptr = getRawPtr<T>(entity);
        return ptr && *ptr != nullptr;
    }

    template<typename T>
    std::vector<std::pair<Entity, std::reference_wrapper<T>>> getAllWithComponent() const {
        std::vector<std::pair<Entity, std::reference_wrapper<T>>> result;

        auto itType = components.find(typeid(T));
        if (itType == components.end())
            return result;

        const auto& innerMap = itType->second;
        for (const auto& [entity, anyValue] : innerMap) {
            try {
                const auto& ptr = std::any_cast<const std::shared_ptr<T>&>(anyValue);
                if (ptr)
                    result.emplace_back(entity, std::ref(*ptr));
            } catch (const std::bad_any_cast&) {
                // Skip silently
            }
        }
        return result;
    }

    void clearAllComponents() {
        components.clear();
    }
};

#endif // COMPONENT_MANAGER_HPP





















