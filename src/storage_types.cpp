#include "storage_types.hpp"

void PackageQueue::push(Package&& package) {
    packages_.emplace_back(std::move(package));
}

Package PackageQueue::pop() {
    Package package_deleted;
    switch (queueType_) {
        case PackageQueueType::FIFO:
            package_deleted = std::move(packages_.front());
            packages_.pop_front();
            break;
        case PackageQueueType::LIFO:
            package_deleted = std::move(packages_.back());
            packages_.pop_back();
            break;
    }
    return package_deleted;
}