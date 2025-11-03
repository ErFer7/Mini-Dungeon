#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "containers/container.hpp"

template <typename Object>
class VectorContainer : public Container<std::vector<Object>, unsigned int, Object> {
   public:
    typedef std::vector<Object> Vector;

   public:
    VectorContainer() = default;

    VectorContainer(GameCore *game_core) : Container<std::vector<Object>, unsigned int, Object>(game_core) {
        this->_vector = std::make_unique<Vector>();
    }

    virtual ~VectorContainer() override = default;

   protected:
    inline void insert(unsigned int identifier, const Object &object) override {
        this->_vector->insert(identifier, object);
    }

    inline void insert(unsigned int identifier, const Object &&object) override {
        this->_vector->insert(identifier, object);
    }

    void push_back(const Object &object) { this->_vector->push_back(object); }

    void push_back(const Object &&object) { this->_vector->push_back(object); }

    inline Object get(unsigned int identifier) const override { return this->_vector->at(identifier); };

    inline Object *get_ref(unsigned int identifier) const override { return &this->_vector->at(identifier); };

    void remove(unsigned int identifier) override { this->_vector->erase(this->_vector->begin() + identifier); }

    void remove(const Object &object) override {
        (*this->_vector).erase(std::find(this->_vector->begin(), this->_vector->end(), object));
    }

    inline void free() override { this->_vector->clear(); }

    inline size_t size() const override { this->_vector->size(); }

    inline Vector *get_data_structure() override { return this->_vector.get(); }

   private:
    std::unique_ptr<Vector> _vector;
};