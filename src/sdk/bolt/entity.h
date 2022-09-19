#pragma once
#include <sdk/bolt/bolt-entity.h>

namespace bolt {
	class c_entity : mono::object_t {
	public:
		c_bolt_entity* unity_object() {
			static std::intptr_t offset{ mono::field_t::parse("[bolt.dll] Bolt:Entity->UnityObject")->offset() };
			return memory::address_t{ this }.offset(offset).deref();
		}
	};
}