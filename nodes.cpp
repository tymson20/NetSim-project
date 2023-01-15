

#include "nodes.hpp"

void PackageSender::send_package() {
    if(bufor_){

        //receiver_preferences_ = *bufor_;
        // !!!!
        //

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