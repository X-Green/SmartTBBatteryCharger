//
// Created by xiaol on 2024/8/31.
//

#include "Tasks.hpp"

namespace Tasks {

    void updateChargers() {

    }

    void checkError() {

    }

    void init() {
    }

    void loop() {
    }
}

extern "C" {
void systemStart() {
    Tasks::init();
    Tasks::loop();
}
}
