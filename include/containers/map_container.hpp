#pragma once

#include <algorithm>
#include <memory>
#include <unordered_map>

#include "containers/container.hpp"

using utils::GameCoreDependencyInjector;

template <typename Identifier, typename Object>
class MapContainer : public Container<std::unordered_map<Identifier, Object>, Identifier, Object> {
   public:
    typedef std::unordered_map<Identifier, Object> Map;

   public:
    MapContainer() = default;

    MapContainer(GameCore *game_core)
        : Container<std::unordered_map<Identifier, Object>, Identifier, Object>(game_core) {
        this->_map = std::make_unique<Map>();
    }

    virtual ~MapContainer() override = default;

   protected:
    // TODO: Fix the cast here
    inline void insert(Identifier identifier, const Object object) override {
        this->_map->insert_or_assign(identifier, std::move(object));
    }

    inline Object &get(Identifier identifier) const override { return (*this->_map)[identifier]; };

    inline Object *get_ref(Identifier identifier) const override { return &(*this->_map)[identifier]; };

    inline bool contains(Identifier identifier) const { return this->_map->contains(identifier); }

    void remove(Identifier identifier) override { (*this->_map).erase(identifier); }

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
