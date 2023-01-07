
#include "package.hpp"

std::set<ElementID> Package::assigned_IDs = std::set<ElementID>();
std::set<ElementID> Package::freed_IDs = std::set<ElementID>();

Package::Package() {
    if (!freed_IDs.empty()) {
        id_ = *(freed_IDs.begin());
        freed_IDs.erase(id_);
        assigned_IDs.insert(id_);
    }
    else{
        if (assigned_IDs.empty()) {
            id_ = 1;
            assigned_IDs.insert(id_);
        }
        else{
            ElementID max_element = *(assigned_IDs.rbegin());
            id_ = max_element + 1;
            assigned_IDs.insert(id_);
        }
    }
}

Package::~Package() {
    assigned_IDs.erase(id_);
    freed_IDs.insert(id_);
}
