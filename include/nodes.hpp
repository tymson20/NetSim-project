
#ifndef NETSIM_PROJECT_NODES_HPP
#define NETSIM_PROJECT_NODES_HPP


#include <optional>
#include <list>
#include <memory>
#include <map>
#include <utility>

#include "package.hpp"
#include "helpers.hpp"
#include "storage_types.hpp"
#include "config.hpp"

enum class ReceiverType{
    Worker,
    Storehouse
};

class IPackageReceiver{
public:
    using const_iterator = IPackageStockpile::const_iterator;

    virtual ElementID get_id() const = 0;
    virtual void receive_package(Package&& p) = 0;
    #if (defined EXERCISE_ID && EXERCISE_ID != EXERCISE_ID_NODES)
    virtual ReceiverType get_receiver_type() const = 0;
    #endif

    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;

    virtual ~IPackageReceiver() = default;
};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator& pg = probability_generator) : pg_(pg) {}

    const_iterator cbegin() const { return map_preferences.cbegin(); }
    const_iterator begin() const { return map_preferences.begin(); }
    const_iterator cend() const { return map_preferences.cend(); }
    const_iterator end() const { return map_preferences.end(); }

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const { return map_preferences; }

    preferences_t map_preferences;
protected:
    void update_probability();

private:
    ProbabilityGenerator& pg_;
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

class Worker : public PackageSender, public IPackageReceiver{
public:

    using const_iterator = IPackageStockpile::const_iterator;

    // Constructor
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), stime_(0), q_(std::move(q)) {};

    void do_work(Time t);

    TimeOffset get_processing_duration() const {return pd_;};
    Time get_package_processing_start_time() const {return stime_;};
    IPackageQueue* get_queue() const {return q_.get();}
    const std::optional<Package>& get_processing_buffer() const {return worker_buffor_;};

    void receive_package(Package&& p) override {q_->push(std::move(p));};
    ElementID  get_id() const override {return id_;};
    #if (defined EXERCISE_ID && EXERCISE_ID != EXERCISE_ID_NODES)
    ReceiverType get_receiver_type() const override {return receiverType_;}
    #endif

    const_iterator begin() const override {return q_->begin();}
    const_iterator end() const override {return q_->end();}
    const_iterator cbegin() const override {return q_->cbegin();}
    const_iterator cend() const override {return q_->cend();}
private:
    ElementID id_;
    TimeOffset pd_;
    Time stime_;
    std::unique_ptr<IPackageQueue> q_;
    std::optional<Package> worker_buffor_;
    ReceiverType receiverType_ = ReceiverType::Worker;

};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::FIFO)) :
            id_(id), stockpile_ptr(std::move(d)) {}

    ElementID get_id() const override { return id_; }
    void receive_package(Package&& p) override { stockpile_ptr->push(std::move(p)); }
    #if (defined EXERCISE_ID && EXERCISE_ID != EXERCISE_ID_NODES)
    ReceiverType get_receiver_type() const override { return receiverType_; }
    #endif

    const_iterator cbegin() const override { return stockpile_ptr->cbegin(); }
    const_iterator begin() const override { return stockpile_ptr->begin(); }
    const_iterator cend() const override { return stockpile_ptr->cend(); }
    const_iterator end() const override { return stockpile_ptr->end(); }

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> stockpile_ptr;
    ReceiverType receiverType_ = ReceiverType::Storehouse;

};

#endif //NETSIM_PROJECT_NODES_HPP
