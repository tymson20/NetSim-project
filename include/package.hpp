
#ifndef NETSIM_PROJECT_PACKAGE_HPP
#define NETSIM_PROJECT_PACKAGE_HPP

#include <set>
#include "types.hpp"

class Package {
public:
    Package();

    Package(ElementID id) : id_(id) {}

    Package(Package&& object) = default;
    Package& operator=(Package&& object) = default;

    ElementID get_id() const { return id_; }

    ~Package();

private:
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID id_;
};

#endif //NETSIM_PROJECT_PACKAGE_HPP
