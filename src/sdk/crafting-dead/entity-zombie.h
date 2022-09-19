#pragma once

namespace sdk {
	class c_entity_zombie : public unity::c_mono_behaviour {
	public:
		float& attack_delay() {
			static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] EntityZombie->attackDelay")->offset() };
			return *(float*)memory::address_t{ this }.offset(offset);
		}

		int& damage() {
			static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] EntityZombie->damage")->offset() };
			return *(int*)memory::address_t{ this }.offset(offset);
		}

		int& health() {
			static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] EntityZombie->health")->offset() };
			return *(int*)memory::address_t{ this }.offset(offset);
		}
	};
}