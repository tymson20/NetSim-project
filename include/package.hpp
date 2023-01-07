//
// Created by tymek on 07.01.2023.
//
#include <set>

#ifndef NETSIM_PROJECT_PACKAGE_HPP
#define NETSIM_PROJECT_PACKAGE_HPP

#include "types.hpp"

class Package {
public:
    Package();

    Package(ElementID id) : id_(id) {}

    Package(Package&&) = default;
    Package& operator = (Package&&) = default;

    const ElementID& get_id() const { return id_; };

    ~Package() {
        assigned_IDs.erase(id_);
        freed_IDs.insert(id_);
    }

private:
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID id_;
};

#endif //NETSIM_PROJECT_PACKAGE_HPP
