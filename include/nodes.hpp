
#ifndef NETSIM_PROJECT_NODES_HPP
#define NETSIM_PROJECT_NODES_HPP


#include <optional>
#include <list>
#include "package.hpp"

class ReceiverPreferences {

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

class Worker : public PackageSender {

};




#endif //NETSIM_PROJECT_NODES_HPP
