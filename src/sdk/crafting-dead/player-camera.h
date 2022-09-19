#pragma once
#include <sdk/unity/mono-behaviour.h>
#include <sdk/unity/camera.h>

namespace sdk {
    class c_player_camera : public unity::c_mono_behaviour {
    public:
        static c_player_camera* singleton() {
            static memory::address_t address{ mono::field_t::parse("[Assembly-CSharp.dll] PlayerCamera->singleton")->address() };
            return memory::address_t{ address }.deref();
        }

    public:
        unity::c_camera* main_camera() {
            static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] PlayerCamera->mainCamera")->offset() };
            return memory::address_t{ this }.offset(offset).deref();
        }
    };
}