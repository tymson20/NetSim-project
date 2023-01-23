
#include "nodes.hpp"

void ReceiverPreferences::update_probability() {
    std::size_t number_of_elements = map_preferences.size();
    double probability = 1./((double)number_of_elements);
    for (auto& pair : map_preferences) {
        pair.second = probability;
    }
}

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    if (map_preferences.empty()) { map_preferences.emplace(r, 1.0); }
    else {
        map_preferences.emplace(r, 0.);
        update_probability();
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    if (map_preferences.size() == 1) {
        map_preferences.erase(r);
    }
    else {
        map_preferences.erase(r);
        update_probability();
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double probability_drawn = pg_();
    double sum_of_probabilities = 0.;
    for (auto& pair : map_preferences) {
        if (sum_of_probabilities <= probability_drawn <= sum_of_probabilities + pair.second) {
            return pair.first;
        }
        else {
            sum_of_probabilities += pair.second;
        }
    }
}

void PackageSender::send_package() {
    if(bufor_){
        (*receiver_preferences_.choose_receiver()).receive_package(std::move(*bufor_));
        bufor_.reset();
    }
}

void PackageSender::push_package(Package&& obj) {
    if(!bufor_) {
        bufor_ = std::move(obj);
    }
}

void Ramp::deliver_goods(Time t){
    if(t % di_ == 1){
        Package package;
        push_package(std::move(package));
    }
}

void Worker::do_work(Time t) {
    if(pd_ == 1){
        push_package(q_->pop());
        stime_ = t;
    }else {
        if (!worker_buffor_.has_value()) {
            if (!q_->empty()) {
                worker_buffor_.emplace(q_->pop());
                stime_ = t;
            }
        }
        if (t - stime_ == pd_ - 1) {
            push_package(std::move(worker_buffor_.value()));
            worker_buffor_ = std::nullopt;
        }
    }
}