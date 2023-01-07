
#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

# include <list>
#include "package.hpp"


enum class PackageQueueType{
    FIFO,
    LIFO
};


class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;

    virtual void push(Package&&) = 0;

    virtual ~IPackageStockpile() = default;
};

class IPackageQueue : public IPackageStockpile{
public:
    virtual Package pop() = 0;
};

class PackageQueue: public IPackageQueue{
public:
    Package pop() override;

private:
    std::list<Package> products_;
    PackageQueueType PQ_type_;
};

#endif //NETSIM_STORAGE_TYPES_HPP