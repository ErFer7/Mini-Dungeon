#pragma once

#include <algorithm>
#include <memory>
#include <unordered_map>

#include "containers/container.hpp"

template <typename LocalIdentifier, typename Object>
class MapContainer : public Container<std::unordered_map<LocalIdentifier, Object>, LocalIdentifier, Object> {
   public:
    typedef std::unordered_map<LocalIdentifier, Object> Map;

   public:
    MapContainer() : Container<std::unordered_map<LocalIdentifier, Object>, LocalIdentifier, Object>() {
        this->_map = std::make_unique<Map>();
    }

    virtual ~MapContainer() override = default;

   protected:
    // TODO: Fix the cast here
    inline void insert(LocalIdentifier local_identifier, Object &&object) override {
        this->_map->insert_or_assign(local_identifier, std::move(object));
    }

    inline Object &get(LocalIdentifier local_identifier) const override { return (*this->_map)[local_identifier]; };

    inline bool contains(LocalIdentifier local_identifier) const { return this->_map->contains(local_identifier); }

    void remove(LocalIdentifier local_identifier) override { (*this->_map).erase(local_identifier); }

    // TODO: This is probabily slow...
    void remove(const Object &object) override {
        auto it = std::find_if(
            this->_map->begin(), this->_map->end(), [&object](const auto &pair) { return &pair.second == &object; });

        if (it != this->_map->end()) {
            this->_map->erase(it);
        }
    }

    inline void free() override { this->_map->clear(); }

    inline size_t size() const override { return this->_map->size(); }

    inline Map *get_data_structure() override { return this->_map.get(); }

   private:
    std::unique_ptr<Map> _map;
};
