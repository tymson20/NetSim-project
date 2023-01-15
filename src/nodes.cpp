

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