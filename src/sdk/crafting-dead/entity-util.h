#pragma once
#include <sdk/crafting-dead/entity-player.h>
#include <sdk/crafting-dead/entity-zombie.h>

namespace sdk {
	class c_entity_util {
	public:
		static std::collections::c_list<c_entity_zombie*>* zombies_by_distance(vec3_t pos, float dist) {
			static mono::method_t::invoker_t<std::collections::c_list<c_entity_zombie*>*(const vec3_t&, float)> invoker{ mono::method_t::parse("[Assembly-CSharp.dll] EntityUtil->FindZombiesWithin(UnityEngine:Vector3, single)") };
			return invoker(pos, dist);
		}
	};
}