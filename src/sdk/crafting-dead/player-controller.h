#pragma once
#include <null-mono.h>

namespace sdk {
	class c_player_controller : public unity::c_mono_behaviour {
	public:
		vec3_t eye_pos() {
			static mono::method_t::invoker_t<vec3_t*(c_player_controller*)> invoker{ mono::method_t::parse("[Assembly-CSharp.dll] PlayerController->GetEyeLevelPosition()") };
			return *invoker(this);
		}

		bool& jump() {
			static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] PlayerController->jump")->offset() };
			return *(bool*)memory::address_t{ this }.offset(offset);
		}

		bool& sprint() {
			static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] PlayerController->sprint")->offset() };
			return *(bool*)memory::address_t{ this }.offset(offset);
		}

		bool& crouch() {
			static std::intptr_t offset{ mono::field_t::parse("[Assembly-CSharp.dll] PlayerController->crouch")->offset() };
			return *(bool*)memory::address_t{ this }.offset(offset);
		}
	};
}