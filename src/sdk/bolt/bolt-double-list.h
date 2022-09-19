#pragma once
#include <null-mono.h>

namespace bolt {
    template <typename element_t>
    class c_bolt_double_list : public mono::object_t {
    public:
        element_t next(const element_t& node) {
            static mono::method_t::invoker_t<element_t(c_bolt_double_list*, element_t)> invoker{ parent_class()->find_method("Next", 1) };
            return invoker(this, node);
        }

        element_t first() {
            static std::intptr_t offset{ parent_class()->find_field("_first")->offset() };
            return *(element_t*)memory::address_t{ this }.offset(offset);
        }

        element_t last() {
            static mono::method_t::invoker_t<element_t(c_bolt_double_list*)> invoker{ parent_class()->find_property("last")->getter() };
            return invoker(this);
        }

        element_t at(int idx) {
            static mono::method_t::invoker_t<element_t(c_bolt_double_list*, int)> invoker{ parent_class()->find_property("Item")->getter() };
            return invoker(this, idx);
        }

        int count() {
            static std::intptr_t offset{ parent_class()->find_field("_count")->offset() };
            return *(int*)memory::address_t{ this }.offset(offset);
        }
    };
}