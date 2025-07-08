#ifndef CATEGORY_CPP
#define CATEGORY_CPP

#include <cstdint>
#include <string>
#include <optional>

class Category {

public:
    Category(const std::string& name, const std::optional<std::uint32_t>& parent_id, const std::string& image_url)
        : name_(name), parent_id_(parent_id), image_url_(image_url) {}

    std::uint32_t getId() const {
        return id_;
    }

    void setId(const std::uint32_t id) {
        id_ = id;
    }

    const std::string& getName() const {
        return name_;
    }

    void setName(const std::string& name) {
        name_ = name;
    }

    std::optional<std::uint32_t> getParentId() const {
        return parent_id_;
    }

    void setParentId(const std::optional<std::uint32_t>& parent_id) {
        parent_id_ = parent_id;
    }

    const std::string& getImageUrl() const {
        return image_url_;
    }

    void setImageUrl(const std::string& image_url) {
        image_url_ = image_url;
    }

private:
    std::uint32_t id_;
    std::string name_;
    std::optional<std::uint32_t> parent_id_;  // ✅ DOIT être optional
    std::string image_url_;
};

#endif // CATEGORY_CPP
