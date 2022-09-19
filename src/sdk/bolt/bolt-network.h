#pragma once
#include <null-mono.h>

namespace bolt {
    class c_bolt_network : mono::object_t {
    public:
        static bool is_connected() {
            static mono::method_t::invoker_t<bool()> invoker{ mono::property_t::parse("[bolt.dll] BoltNetwork->IsConnected")->getter() };
            return invoker();
        }
    };
}