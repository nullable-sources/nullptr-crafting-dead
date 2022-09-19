#pragma once
#include <null-mono.h>

namespace unity {
    class c_transform : public mono::object_t {
    public:
        vec3_t get_position() {
            static mono::method_t::invoker_t<vec3_t*(c_transform*)> invoker{ mono::property_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Transform->position")->getter() };
            return *invoker(this);
        }

        void set_position(const vec3_t& vec) {
            static mono::method_t::invoker_t<void(c_transform*, const vec3_t&)> invoker{ mono::property_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Transform->position")->setter() };
            invoker(this, vec);
        }
    };
}