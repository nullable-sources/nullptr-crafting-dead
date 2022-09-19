#pragma once
#include <sdk/unity/mono-behaviour.h>

namespace sdk {
	class c_entity_player : public unity::c_mono_behaviour {
	public:
		static c_entity_player* local_player() {
            static memory::address_t address{ mono::field_t::parse("[Assembly-CSharp.dll] EntityPlayer->localPlayer")->address() };
            return memory::address_t{ address }.deref();
		}

	public:
        int& max_health() {
            static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] EntityPlayer->maxHealth")->offset() };
            return *(int*)memory::address_t{ this }.offset(offset);
        }

        int& player_damage() {
            static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] EntityPlayer->playerDamage")->offset() };
            return *(int*)memory::address_t{ this }.offset(offset);
        }

        int health() {
            static mono::method_t::invoker_t<int(c_entity_player*)> invoker{ mono::method_t::parse("[Assembly-CSharp.dll] EntityPlayer->GetHealth()") };
            return invoker(this);
        }

        mono::string_t* user_name() {
            static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] EntityPlayer->username")->offset() };
            return memory::address_t{ this }.offset(offset).deref();
        }

        bool is_alive() {
            static mono::method_t::invoker_t<bool(c_entity_player*)> invoker{ mono::method_t::parse("[Assembly-CSharp.dll] EntityPlayer->IsAlive()") };
            return invoker(this);
        }
	};
}