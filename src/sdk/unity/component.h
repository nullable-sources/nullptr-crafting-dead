#pragma once
#include <sdk/unity/game-object.h>
#include <sdk/unity/transform.h>

namespace unity {
	class c_component : public c_object {
	public:
		c_transform* transform() {
			static mono::method_t::invoker_t<c_transform* (c_component*)> invoker{ mono::property_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Component->transform")->getter() };
			return invoker(this);
		}

		c_game_object* game_object() {
			static mono::method_t::invoker_t<c_game_object* (c_component*)> invoker{ mono::property_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Component->gameObject")->getter() };
			return invoker(this);
		}

		mono::object_t* get_component(mono::type_t* type) {
			static mono::method_t::invoker_t<mono::object_t* (c_component*, mono::reflection_type_t*)> invoker{ mono::method_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Component->GetComponent(System:Type)") };
			return invoker(this, mono::mono.type_get_object(mono::domain_t::root(), type));
		}
	};
}