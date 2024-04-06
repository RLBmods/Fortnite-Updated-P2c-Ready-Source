#include "protection/spoofer.h"
#include "protection/SkCrypt.h"
#include "Functions/sdk.h"
#include "ImGui/imgui.h"
#include <d3d9.h>
#include "ImGui/imgui_impl_win32.h"
#include "Driver/driver.hpp"
#include "Functions/globals.h"
#include "protection/hooks.h"
ImFont* MenuFont;
ImFont* GameFont;
ImFont* ESPFont;
ImFont* IconsFont;

// esp font
ImFont* FpsFont;
ImFont* DistanceFont;
ImFont* UsernamePlatformFont;
ImFont* WeaponFont;

inline int center_x;
inline int center_y;

class entity {
public:
	uintptr_t
		actor,
		entity,
		skeletal_mesh,
		root_component,
		player_state;
	int
		team_index;
	fvector
		relative_location;
	float
		lastrendertime;
	bool
		is_visible;
};

std::vector<entity> entity_list;
std::vector<entity> temporary_entity_list;
namespace o {
class p
{
	public:

		uintptr_t
			uworld,
			game_instance,
			game_state,
			local_player,
			player_controller,
			acknowledged_pawn,
			skeletal_mesh,
			player_state,
			root_component,
			player_array;
		int
			team_index,
			player_array_size;
		fvector
			relative_location,
			velocity;
	};
} static o::p* Undetected = new o::p();




