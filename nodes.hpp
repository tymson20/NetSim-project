
#ifndef NETSIM_PROJECT_NODES_HPP
#define NETSIM_PROJECT_NODES_HPP


#include <optional>
#include <list>
#include <memory>

#include "package.hpp"
#include "types.hpp"
#include "storage_types.hpp"

enum class ReceiverType{
    Worker,
    Storehouse
};


class IPackageReceiver{
public:
    using const_iterator = IPackageStockpile::const_iterator;

    virtual ElementID get_id() const = 0;
    virtual void receive_package(Package&& p) = 0;
    virtual ReceiverType get_receiver_type() const = 0;

    virtual const_iterator cbegin()  = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend()  = 0;
    virtual const_iterator cend() const = 0;

    virtual ~IPackageReceiver() = default;

};



class ReceiverPreferences {
    //TODO implemntacja całej klasy
};

class PackageSender {
public:
    PackageSender() = default;
    PackageSender(PackageSender&&) = default;

    ReceiverPreferences receiver_preferences_;

    void send_package();
    std::optional<Package>& get_sending_buffer() { return bufor_; }

protected:
    void push_package(Package&& obj);

private:
    std::optional<Package> bufor_;

};


class Ramp : public PackageSender {
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}

    void deliver_goods(Time t);
    ElementID get_id() const { return id_; }
    TimeOffset get_delivery_interval() const { return di_; }

private:
    ElementID id_;
    TimeOffset di_;

};

class Worker : public PackageSender, public IPackageReceiver,public IPackageQueue{
public:

    using const_iterator = IPackageStockpile::const_iterator;

    // Constructor
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), stime_(0), q_(std::move(q)) {};

    void do_work(Time t);

    TimeOffset get_processing_duration() const {return pd_;};
    Time get_package_processing_start_time() const {return stime_;};
    IPackageQueue* get_queue() const {return q_.get();};
    const std::optional<Package>& get_processing_buffer() const {return worker_buffor_;};

    void receive_package(Package&& p) override {q_->push(std::move(p));};
    ElementID  get_id() const override {return id_;};
    ReceiverType get_receiver_type() const override {return receiverType_;};

    void push(Package&& p) override {q_->push(std::move(p));};
    bool empty() const override {return q_->empty();};
    std::size_t size() const override {return q_->size();};
    PackageQueueType get_queue_type() const override {return q_->get_queue_type();};
    Package pop() override {return q_->pop();};

    const_iterator begin() const override {return q_->cbegin();};
    const_iterator end() const override {return q_->cend();};
    const_iterator cbegin() const override {return q_->cbegin();};
    const_iterator cend() const override {return q_->cend();};


private:
    ElementID id_;
    TimeOffset pd_;
    Time stime_;
    std::unique_ptr<IPackageQueue> q_;
    std::optional<Package> worker_buffor_;
    ReceiverType receiverType_ = ReceiverType::Worker;

};




#endif //NETSIM_PROJECT_NODES_HPP
