#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "containers/container.hpp"
#include "utils/id.hpp"

template <typename Object>
class VectorContainer : public Container<std::vector<Object>, unsigned int, Object> {
   public:
    typedef std::vector<Object> Vector;

   public:
    VectorContainer() : Container<std::vector<Object>, unsigned int, Object>() {
        this->_vector = std::make_unique<Vector>();
    }

    virtual ~VectorContainer() override = default;

   protected:
    inline void insert(unsigned int local_identifier, Object &&object) override {
        this->_vector->insert(this->_vector->begin() + local_identifier, std::move(object));
    }

    void push_back(Object object) { this->_vector->push_back(std::move(object)); }

    inline Object &get(unsigned int local_identifier) const override { return this->_vector->at(local_identifier); };

    inline Object *get_ref(unsigned int local_identifier) const override {
        return &this->_vector->at(local_identifier);
    };

    void remove(unsigned int local_identifier) override {
        this->_vector->erase(this->_vector->begin() + local_identifier);
    }

    void remove(const Object &object) override {
        utils::Id object_id = static_cast<utils::Identified>(object).get_id();

        for (auto it = this->_vector->begin(); it != this->_vector->end(); ++it) {
            utils::Id it_id = static_cast<utils::Identified>(it).get_id();

            if (object_id == it_id) {
                this->_vector->erase(it);
            }
        }
    }

    inline void free() override { this->_vector->clear(); }

    inline size_t size() const override { return this->_vector->size(); }

    inline Vector *get_data_structure() override { return this->_vector.get(); }

   private:
    std::unique_ptr<Vector> _vector;
};
