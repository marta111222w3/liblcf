/*
 * This file is part of liblcf. Copyright (c) 2020 liblcf authors.
 * https://github.com/EasyRPG/liblcf - https://easyrpg.org
 *
 * liblcf is Free/Libre Open Source Software, released under the MIT License.
 * For the full copyright and license information, please view the COPYING
 * file that was distributed with this source code.
 */

#include "lcf/config.h"
#include "lcf/rpg/actor.h"
#include "lcf/rpg/event.h"
#include "lcf/rpg/map.h"
#include "lcf/rpg/mapinfo.h"
#include "lcf/rpg/system.h"
#include "lcf/rpg/save.h"
#include "lcf/rpg/chipset.h"
#include "lcf/rpg/parameters.h"
#include "lcf/data.h"

namespace lcf {

void rpg::SaveMapInfo::Setup() {
	position_x = 0;
	position_y = 0;
	lower_tiles.resize(144);
	upper_tiles.resize(144);
	for (int i = 0; i < 144; i++) {
		lower_tiles[i] = i;
		upper_tiles[i] = i;
	}
}

void rpg::SaveMapInfo::Setup(const rpg::Map& map) {
	chipset_id = map.chipset_id;
	parallax_name = ToString(map.parallax_name);
	parallax_horz = map.parallax_loop_x;
	parallax_vert = map.parallax_loop_y;
	parallax_horz_auto = map.parallax_auto_loop_x;
	parallax_vert_auto = map.parallax_auto_loop_y;
	parallax_horz_speed = map.parallax_sx;
	parallax_vert_speed = map.parallax_sy;
}

void rpg::Save::Setup() {
	screen = rpg::SaveScreen();
	pictures.clear();
	actors.clear();
	actors.resize(lcf::Data::actors.size());
	map_info.Setup();

	party_location.move_speed = 4;
	boat_location.vehicle = rpg::SaveVehicleLocation::VehicleType_skiff;
	ship_location.vehicle = rpg::SaveVehicleLocation::VehicleType_ship;
	airship_location.vehicle = rpg::SaveVehicleLocation::VehicleType_airship;

	if (targets.empty()) {
		targets.resize(1);
	}
}

void rpg::Actor::Setup() {
	int max_final_level = 0;
	if (lcf::Data::system.ldb_id == 2003) {
		max_final_level = 99;
		if (final_level == -1) {
			final_level = max_final_level;
		}
		exp_base = exp_base == -1 ? 300 : exp_base;
		exp_inflation = exp_inflation == -1 ? 300 : exp_inflation;
	}
	else {
		max_final_level = 50;
		if (final_level == -1) {
			final_level = max_final_level;
		}
		exp_base = exp_base == -1 ? 30 : exp_base;
		exp_inflation = exp_inflation == -1 ? 30 : exp_inflation;
	}
	parameters.Setup(max_final_level);
}

void rpg::Parameters::Setup(int final_level) {
	size_t level = 0;
	if (final_level > 0) level = final_level;
	if (maxhp.size() < level) maxhp.resize(level, 1);
	if (maxsp.size() < level) maxsp.resize(level, 0);
	if (attack.size() < level) attack.resize(level, 1);
	if (defense.size() < level) defense.resize(level, 1);
	if (spirit.size() < level) spirit.resize(level, 1);
	if (agility.size() < level) agility.resize(level, 1);
}

} // namespace lcf
