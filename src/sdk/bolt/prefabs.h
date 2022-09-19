#pragma once

namespace bolt {
	enum class e_prefabs : int {
		none,

		airdrop,

		entity_item,

		crate_common,
		crate_food,
		crate_medical,
		crate_military,
		crate_tools,
		crate_uncommon,
		
		entity_base_flag,
		entity_chest_large,
		entity_chest,
		entity_door_wood,
		entity_door,
		entity_furnace,
		entity_propane,
		entity_stash,
		entity_tnt,
		
		node_coal,
		node_gold,
		node_iron,
		node_stone,
		
		player,
		
		struct_floor,
		struct_foundation,
		struct_frame_door,
		struct_frame_window,
		struct_stairs,
		struct_wall_half,
		struct_wall,
		
		zombie,
		
		tree_dead,
		tree_forest_thin,
		tree_forest,
		tree_pine_snow,
		tree_pine_tall,
		tree_pine,
		tree_sapling_pine,
		tree_sapling,

		door,
		preview_entity_door,
	};
}