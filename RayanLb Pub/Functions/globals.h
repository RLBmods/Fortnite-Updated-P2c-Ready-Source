#include <mutex>
#include <memory>

namespace Aimbot {

	inline bool aimbot = 1;
	inline bool prediction = 0;
	inline bool visible_check = 1;



	inline bool fov_circle = 0;
	inline bool FovFilled = 0; 
	inline bool FOVlgbtq = 0;
	inline bool FOVdynamic = 0;


	inline bool target_text = 0;
	inline bool target_line;
	inline bool is_dead = 0;
	inline bool in_lobby;

	inline float aim_fov = 150;
	inline float smooth = 1;



	inline int g_hitbox = 0;
	inline float render_distance = 275; // 275

	
	inline int hitbox = 0; // 0 = niekas // 1 galva
}



namespace Visuals {
	
	inline bool enable_esp = 1;

	// BOXS
	inline bool Box_ESP = 1;
	


	inline int box_types = 0;
	inline int line_type = 0;
	inline int line_thick = 2;
	inline bool FilledBox = 1;
	inline bool HeadEsp = 0;


	inline bool skeleton = 0;
	inline bool snapline = 0;
	inline bool username = 0;
	inline bool distance = 1;
	inline bool weapon = 0;
	inline bool AmmoCount = 0;

	inline bool platform = 0;
	inline bool outline = 0;

	float render_distance = 275;


}





namespace Misc
{
	
	inline bool enable_menu = 0;
	inline int Selection = 1;

	inline bool fps = 1;
	inline bool Teamcheck = 1;
	inline bool VSYNC = 0;
	inline bool KillCount = 0;
	inline bool playerid = 0;
	inline bool playercount = 0;
	float fontsize = 14;

	inline bool Crosshair = 0;
	inline bool weapon_cfg = 1;


	inline int skeleton_thick = 1.5f;
	inline int box_thick = 1.5f;
	inline int line_thick = 1.5;
	inline int HeadSized = 1;

	// colors

	static float box_visible[3] = { 0.f, 1.f, 0.f };
	static float box_invisible[3] = { 1.f, 0.f, 0.f };

	static float box_filled_visible[3] = { 0.f, 1.f, 0.f };
	static float box_filled_invisible[3] = { 1.f, 0.f, 0.f };

	static float skeleton_visible[3] = { 0.f, 1.f, 0.f };
	static float skeleton_invisible[3] = { 1.f, 0.f, 0.f };

	static float text_visible[3] = { 1.0f, 1.0f, 0.0f };
	static float text_invisible[3] = { 1.0f, 1.0f, 0.0f };

	static float snaplines_visible[3] = { 0.f, 1.f, 0.f };
	static float snaplines_invisible[3] = { 1.f, 0.f, 0.f };

}

namespace WorldESP {
	inline bool WorldEnable = 1;
	inline bool DrawChest = 1;
	inline int lootEspDist = 275;
	inline bool DrawAmmoBox = 1;
	inline bool drawloot = 1;
	inline bool DrawVehicles = 1;



	inline bool uncommon = 1;
	inline bool rare = 1;
	inline bool purple = 1;
	inline bool gold = 1;
	inline bool mythic = 1;
	inline bool common = 1;


}




namespace Rifle
{
	inline int hitbox = 0;
	inline float aim_fov = 150;



	inline bool aimbot = 1;
	inline int aimkey;
	inline float smooth = 5;
}

namespace Shotgun
{
	inline int hitbox = 0;
	inline float aim_fov = 150;


	inline bool aimbot = 1;
	inline int aimkey;
	inline float smooth = 5;
}

namespace Smg
{
	inline int hitbox = 0;
	inline float aim_fov = 150;



	inline bool aimbot = 1;
	inline int aimkey;
	inline 	float smooth = 5;
}

namespace Sniper
{
	inline int hitbox = 0;
	inline float aim_fov = 150;



	inline bool aimbot = 1;
	inline bool prediction = 0;
	inline int aimkey;
	inline float smooth = 1;
}





namespace gay {
	float Gay = 20.0f;
}