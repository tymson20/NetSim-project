//
// Created by tymek on 07.01.2023.
//

#include "../include/package.hpp"

Package::Package() {
    if (!freed_IDs.empty()) {
        id_ = *(freed_IDs.begin());
        freed_IDs.erase(id_);
        assigned_IDs.insert(id_);
    }
    else{
        ElementID max_element = *(assigned_IDs.rbegin());
        id_ = max_element + 1;
        assigned_IDs.insert(id_);
    }
}