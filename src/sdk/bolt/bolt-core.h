#pragma once
#include <sdk/bolt/bolt-double-list.h>
#include <sdk/bolt/entity.h>

namespace bolt {
	class c_bolt_core {
	public:
		static c_bolt_double_list<c_entity*>* entities() {
			static memory::address_t address{ mono::field_t::parse("[bolt.dll] BoltInternal:BoltCore->_entitiesOK")->address() };
			return memory::address_t{ address }.deref();
		}
	};
}