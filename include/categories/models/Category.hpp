#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <cstdint>
#include <string>
#include <optional>

class Category {
public:
    // ✅ Constructeur par défaut (utile pour les vecteurs, JSON, etc.)
    Category()
        : id_(0), name_(""), parent_id_(std::nullopt), image_url_("") {}

    // ✅ Constructeur principal
    Category(const std::string& name,
             const std::optional<std::uint32_t>& parent_id,
             const std::string& image_url)
        : id_(0), name_(name), parent_id_(parent_id), image_url_(image_url) {}

    // ✅ Constructeur de copie
    Category(const Category& other) = default;

    // ✅ Constructeur par move
    Category(Category&& other) noexcept = default;

    // ✅ Opérateurs
    Category& operator=(const Category& other) = default;
    Category& operator=(Category&& other) noexcept = default;

    // ✅ Accesseurs
    std::uint32_t getId() const { return id_; }
    void setId(const std::uint32_t id) { id_ = id; }

    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }

    std::optional<std::uint32_t> getParentId() const { return parent_id_; }
    void setParentId(const std::optional<std::uint32_t>& parent_id) { parent_id_ = parent_id; }

    const std::string& getImageUrl() const { return image_url_; }
    void setImageUrl(const std::string& image_url) { image_url_ = image_url; }

private:
    std::uint32_t id_ = 0;
    std::string name_;
    std::optional<std::uint32_t> parent_id_;
    std::string image_url_;
};

#endif // CATEGORY_HPP
