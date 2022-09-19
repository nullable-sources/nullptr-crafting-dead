#pragma once
#include <sdk/unity/mono-behaviour.h>
#include <sdk/bolt/prefabs.h>

namespace bolt {
	class c_bolt_entity : public unity::c_mono_behaviour {
	public:
		e_prefabs& prefab_id() {
			static std::intptr_t offset{ mono::field_t::parse("[bolt.dll] BoltEntity->_prefabId")->offset() };
			return *(e_prefabs*)memory::address_t{ this }.offset(offset);
		}
	};
}