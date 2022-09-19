#pragma once
#include <sdk/unity/behaviour.h>
#include <sdk/unity/screen.h>

namespace unity {
	class c_camera : public c_behaviour {
	public:
		static c_camera* current() {
			static mono::method_t::invoker_t<c_camera* ()> invoker{ mono::property_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Camera->current")->getter() };
			return invoker();
		}

		static c_camera* main() {
			static mono::method_t::invoker_t<c_camera* ()> invoker{ mono::property_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Camera->main")->getter() };
			return invoker();
		}

	public:
		bool world_to_screen(vec3_t world_pos, vec2_t& screen_pos) {
			static mono::method_t::invoker_t<vec3_t* (c_camera*, vec3_t*)> invoker{ mono::method_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Camera->WorldToScreenPoint(UnityEngine:Vector3)") };
			vec3_t result{ *invoker(this, &world_pos) };
			screen_pos = { result.x, c_screen::get_height() - result.y };
			return result.z >= 0.f;
		}
	};
}