//// Load config
//
//BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
//	char lpString[1024];
//	sprintf_s(lpString, sizeof(lpString), TEXT("%d"), nInteger);
//	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
//}
//
//BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
//	char lpString[1024];
//	sprintf_s(lpString, sizeof(lpString), TEXT("%f"), nInteger);
//	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
//}
//float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
//{
//	char szData[32];
//
//	GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);
//
//	return (float)atof(szData);
//}
//
//void savecfg(LPCSTR path)
//{
//	//Aimbot 
//
//
//	WritePrivateProfileInt(("Aimbot"), TEXT("Aimbot"), Aimbot::aimbot, path);
//	WritePrivateProfileInt(("Aimbot"), TEXT("Visible Check"), Aimbot::visible_check, path);
//	WritePrivateProfileInt(("Aimbot"), TEXT("Isdead"), Aimbot::is_dead, path);
//	WritePrivateProfileFloat(("Aimbot"), TEXT("Target Line"), Aimbot::target_line, path);
//	WritePrivateProfileFloat(("Aimbot"), TEXT("Aim Fov"), Aimbot::aim_fov, path);
//	WritePrivateProfileInt(("Aimbot"), TEXT("Hitbox"), Aimbot::g_hitbox, path);
//	WritePrivateProfileInt(("Aimbot"), TEXT("Aim Max Dist"), Aimbot::g_aim_max_dist, path);
//	WritePrivateProfileInt(("Aimbot"), TEXT("Smooth"), Aimbot::smooth, path);
//	WritePrivateProfileInt(("Aimbot"), TEXT("Render Fov"), Aimbot::fov_circle, path);
//	
//
//
//	// Visuals
//
//
//	WritePrivateProfileInt(("Visual"), TEXT("Enable_Esp"), Visuals::enable_esp, path);
//	//WritePrivateProfileInt(("Visual"), TEXT("Box Esp"), Visuals::g_box_esp, path);
//	
//	WritePrivateProfileInt(("Visual"), TEXT("Skeleton"), Visuals::skeleton, path);
//	
//	WritePrivateProfileInt(("Visual"), TEXT("Distance"), Visuals::distance, path);
//	WritePrivateProfileInt(("Visual"), TEXT("Username"), Visuals::username, path);
//	WritePrivateProfileInt(("Visual"), TEXT("Weapon Esp"), Visuals::weapon, path);
//	
//	WritePrivateProfileInt(("Visual"), TEXT("Platform"), Visuals::platform, path);
//	
//	WritePrivateProfileInt(("Visual"), TEXT("Line"), Misc::line_thick, path);
//	WritePrivateProfileInt(("Visual"), TEXT("Snapline"), Visuals::snapline, path);
//	WritePrivateProfileInt(("Visual"), TEXT("Outline"), Visuals::outline, path);
//	WritePrivateProfileInt(("Visual"), TEXT("Box Thick"), Misc::g_box_thick, path);
//
//	WritePrivateProfileInt(("Visual"), TEXT("Skeleton Thick"), Misc::g_skeleton_thick, path);
//	WritePrivateProfileInt(("Visual"), TEXT("Render Distance"), Visuals::render_distance, path);
//
//
//	// Misc
//
//
//	WritePrivateProfileInt(("Misc"), TEXT("Render Menu"), Misc::enable_menu, path);
//	WritePrivateProfileInt(("Misc"), TEXT("Fps"), Misc::fps, path);
//	WritePrivateProfileInt(("Misc"), TEXT("Weapon CFG"), Misc::g_weapon_cfg, path);
//
//
//	// Rifle Config
//
//
//	WritePrivateProfileInt(("Rifle"), TEXT("Rifle Aimbot1"), rifle::aimbot, path);
//	WritePrivateProfileInt(("Rifle"), TEXT("Ignore Downed1"), rifle::ignore_downed, path);
//	WritePrivateProfileInt(("Rifle"), TEXT("Ignore Bots1"), rifle::ignore_bots, path);
//	WritePrivateProfileInt(("Rifle"), TEXT("Visible Check1"), rifle::visible_check, path);
//	WritePrivateProfileInt(("Rifle"), TEXT("Target Line1"), rifle::target_line, path);
//	WritePrivateProfileInt(("Rifle"), TEXT("Aim Fov1"), rifle::aim_fov, path);
//	WritePrivateProfileInt(("Rifle"), TEXT("Smooth1"), rifle::smooth, path);
//	WritePrivateProfileInt(("Rifle"), TEXT("Hitbox1"), rifle::hitbox, path);
//	WritePrivateProfileInt(("Rifle"), TEXT("Aimkey1"), rifle::aimkey, path);
//
//
//	// Shotgun Config
//
//
//	WritePrivateProfileInt(("Shotgun"), TEXT("Shotgun Aimbot2"), shotgun::aimbot, path);
//	WritePrivateProfileInt(("Shotgun"), TEXT("Ignore Downed2"), shotgun::ignore_downed, path);
//	WritePrivateProfileInt(("Shotgun"), TEXT("Ignore Bot2"), shotgun::ignore_bots, path);
//	WritePrivateProfileInt(("Shotgun"), TEXT("Visible Check2"), shotgun::visible_check, path);
//	WritePrivateProfileInt(("Shotgun"), TEXT("Target Line2"), shotgun::target_line, path);
//	WritePrivateProfileInt(("Shotgun"), TEXT("Aim Fov2"), shotgun::aim_fov, path);
//	WritePrivateProfileInt(("Shotgun"), TEXT("Smooth2"), shotgun::smooth, path);
//	WritePrivateProfileInt(("Shotgun"), TEXT("Hitbox2"), shotgun::hitbox, path);
//	WritePrivateProfileInt(("Shotgun"), TEXT("Aimkey2"), shotgun::aimkey, path);
//	
//
//	// Smg Config
//
//
//	WritePrivateProfileInt(("Smg"), TEXT("Smg Aimbot3"), smg::aimbot, path);
//	WritePrivateProfileInt(("Smg"), TEXT("Ignore Downed3"), smg::ignore_downed, path);
//	WritePrivateProfileInt(("Smg"), TEXT("Ignore Bot3"), smg::ignore_bots, path);
//	WritePrivateProfileInt(("Smg"), TEXT("Visible Check3"), smg::visible_check, path);
//	WritePrivateProfileInt(("Smg"), TEXT("Target Line3"), smg::target_line, path);
//	WritePrivateProfileInt(("Smg"), TEXT("Aim Fov3"), smg::aim_fov, path);
//	WritePrivateProfileInt(("Smg"), TEXT("Smooth3"), smg::smooth, path);
//	WritePrivateProfileInt(("Smg"), TEXT("Hitbox3"), smg::hitbox, path);
//	WritePrivateProfileInt(("Smg"), TEXT("Aimkey3"), smg::aimkey, path);
//
//
//	// Sniper Config
//
//
//	WritePrivateProfileInt(("Sniper"), TEXT("Sniper Aimbot4"), sniper::aimbot, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Prediction4"), sniper::Prediction, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Ignore Downed4"), sniper::ignore_downed, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Ignore Bot4"), sniper::ignore_bots, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Visible Check4"), sniper::visible_check, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Target Line4"), sniper::target_line, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Aim Fov4"), sniper::aim_fov, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Smooth4"), sniper::smooth, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Hitbox4"), sniper::hitbox, path);
//	WritePrivateProfileInt(("Sniper"), TEXT("Aimkey4"), sniper::aimkey, path);
//}
//
//
//
//
//
//
//
//
//
//
//void loadcfg(LPCSTR path)
//{
//
//
//	// Aimbot
//
//	
//	Aimbot::aimbot = GetPrivateProfileIntA(("Aimbot"), TEXT("Aimbot"), Aimbot::aimbot, path);
//	Aimbot::visible_check = GetPrivateProfileIntA(("Aimbot"), TEXT("Visible Check"), Aimbot::visible_check, path);
//	Aimbot::is_dead = GetPrivateProfileIntA(("Aimbot"), TEXT("Isdead"), Aimbot::is_dead, path);
//	Aimbot::target_line = GetPrivateProfileIntA(("Aimbot"), TEXT("Target Line"), Aimbot::target_line, path);
//	Aimbot::aim_fov = GetPrivateProfileIntA(("Aimbot"), TEXT("Aim Fov"), Aimbot::aim_fov, path);
//	Aimbot::g_hitbox = GetPrivateProfileIntA(("Aimbot"), TEXT("Hitbox"), Aimbot::g_hitbox, path);
//	Aimbot::g_aim_max_dist = GetPrivateProfileIntA(("Aimbot"), TEXT("Aim Max Dist"), Aimbot::g_aim_max_dist, path);
//	Aimbot::smooth = GetPrivateProfileIntA(("Aimbot"), TEXT("Smooth"), Aimbot::smooth, path);
//	Aimbot::fov_circle = GetPrivateProfileIntA(("Aimbot"), TEXT("Render Fov"), Aimbot::fov_circle, path);
//	
//
//
//	// Visuals
//
//
//	Visuals::enable_esp = GetPrivateProfileIntA(("Visual"), TEXT("Enable visuals"), Visuals::enable_esp, path);
//	//Visuals::g_box_esp = GetPrivateProfileIntA(("Visual"), TEXT("Box Esp"), Visuals::g_box_esp, path);
//	
//	Visuals::skeleton = GetPrivateProfileIntA(("Visual"), TEXT("Skeleton"), Visuals::skeleton, path);
//	
//	Visuals::distance = GetPrivateProfileIntA(("Visual"), TEXT("Distance"), Visuals::distance, path);
//	Visuals::username = GetPrivateProfileIntA(("Visual"), TEXT("Username"), Visuals::username, path);
//	Visuals::weapon = GetPrivateProfileIntA(("Visual"), TEXT("Weapon Esp"), Visuals::weapon, path);
//
//	Visuals::platform = GetPrivateProfileIntA(("Visual"), TEXT("Platform"), Visuals::platform, path);
//	
//	Misc::line_thick = GetPrivateProfileIntA(("Visual"), TEXT("Line"), Misc::line_thick, path);
//	Visuals::snapline = GetPrivateProfileIntA(("Visual"), TEXT("Snapline"), Visuals::snapline, path);
//	Visuals::outline = GetPrivateProfileIntA(("Visual"), TEXT("Outline"), Visuals::outline, path);
//	Misc::g_box_thick = GetPrivateProfileIntA(("Visual"), TEXT("Box Thick"), Misc::g_box_thick, path);
//
//	Misc::g_skeleton_thick = GetPrivateProfileIntA(("Visual"), TEXT("Skeleton Thick"), Misc::g_skeleton_thick, path);
//	Visuals::render_distance = GetPrivateProfileIntA(("Visual"), TEXT("Render Distance"), Visuals::render_distance, path);
//
//
//	// Misc
//
//
//	Misc::enable_menu = GetPrivateProfileIntA(("Misc"), TEXT("Render Menu"), Misc::enable_menu, path);
//	Misc::fps = GetPrivateProfileIntA(("Misc"), TEXT("Fps"), Misc::fps, path);
//	Misc::g_weapon_cfg = GetPrivateProfileIntA(("Misc"), TEXT("Weapon CFG"), Misc::g_weapon_cfg, path);
//
//
//	// Rifle Config
//
//	rifle::aimbot = GetPrivateProfileIntA(("Rifle"), TEXT("Rifle Aimbot1"), rifle::aimbot, path);
//	rifle::ignore_downed = GetPrivateProfileIntA(("Rifle"), TEXT("Ignore Downed1"), rifle::ignore_downed, path);
//	rifle::ignore_bots = GetPrivateProfileIntA(("Rifle"), TEXT("Ignore Bots1"), rifle::ignore_bots, path);
//	rifle::visible_check = GetPrivateProfileIntA(("Rifle"), TEXT("Visible Check1"), rifle::visible_check, path);
//	rifle::target_line = GetPrivateProfileIntA(("Rifle"), TEXT("Target Line1"), rifle::target_line, path);
//	rifle::aim_fov = GetPrivateProfileIntA(("Rifle"), TEXT("Aim Fov1"), rifle::aim_fov, path);
//	rifle::smooth = GetPrivateProfileIntA(("Rifle"), TEXT("Smooth1"), rifle::smooth, path);
//	rifle::hitbox = GetPrivateProfileIntA(("Rifle"), TEXT("Hitbox1"), rifle::hitbox, path);
//	rifle::aimkey = GetPrivateProfileIntA(("Rifle"), TEXT("Aimkey1"), rifle::aimkey, path);
//
//
//	// Shotgun
//
//
//	shotgun::aimbot = GetPrivateProfileIntA(("Shotgun"), TEXT("Shotgun Aimbot2"), shotgun::aimbot, path);
//	shotgun::ignore_downed = GetPrivateProfileIntA(("Shotgun"), TEXT("Ignore Downed2"), shotgun::ignore_downed, path);
//	shotgun::ignore_bots = GetPrivateProfileIntA(("Shotgun"), TEXT("Ignore Bots2"), shotgun::ignore_bots, path);
//	shotgun::visible_check = GetPrivateProfileIntA(("Shotgun"), TEXT("Visible Check2"), shotgun::visible_check, path);
//	shotgun::target_line = GetPrivateProfileIntA(("Shotgun"), TEXT("Target Line2"), shotgun::target_line, path);
//	shotgun::aim_fov = GetPrivateProfileIntA(("Shotgun"), TEXT("Aim Fov2"), shotgun::aim_fov, path);
//	shotgun::smooth = GetPrivateProfileIntA(("Shotgun"), TEXT("Smooth2"), shotgun::smooth, path);
//	shotgun::hitbox = GetPrivateProfileIntA(("Shotgun"), TEXT("Hitbox2"), shotgun::hitbox, path);
//	shotgun::aimkey = GetPrivateProfileIntA(("Shotgun"), TEXT("Aimkey2"), shotgun::aimkey, path);
//
//
//	// Smg Config
//
//
//	smg::aimbot = GetPrivateProfileIntA(("Smg"), TEXT("Smg Aimbot3"), smg::aimbot, path);
//	smg::ignore_downed = GetPrivateProfileIntA(("Smg"), TEXT("Ignore Downed3"), smg::ignore_downed, path);
//	smg::ignore_bots = GetPrivateProfileIntA(("Smg"), TEXT("Ignore Bots3"), smg::ignore_bots, path);
//	smg::visible_check = GetPrivateProfileIntA(("Smg"), TEXT("Visible Check3"), smg::visible_check, path);
//	smg::target_line = GetPrivateProfileIntA(("Smg"), TEXT("Target Line3"), smg::target_line, path);
//	smg::aim_fov = GetPrivateProfileIntA(("Smg"), TEXT("Aim Fov3"), smg::aim_fov, path);
//	smg::smooth = GetPrivateProfileIntA(("Smg"), TEXT("Smooth3"), smg::smooth, path);
//	smg::hitbox = GetPrivateProfileIntA(("Smg"), TEXT("Hitbox3"), smg::hitbox, path);
//	smg::aimkey = GetPrivateProfileIntA(("Smg"), TEXT("Aimkey3"), smg::aimkey, path);
//
//
//	// Sniper Config
//
//
//	sniper::aimbot = GetPrivateProfileIntA(("Sniper"), TEXT("Sniper Aimbot4"), sniper::aimbot, path);
//	sniper::Prediction = GetPrivateProfileIntA(("Sniper"), TEXT("Prediction4"), sniper::Prediction, path);
//	sniper::ignore_downed = GetPrivateProfileIntA(("Sniper"), TEXT("Ignore Downed4"), sniper::ignore_downed, path);
//	sniper::ignore_bots = GetPrivateProfileIntA(("Sniper"), TEXT("Ignore Bots4"), sniper::ignore_bots, path);
//	sniper::visible_check = GetPrivateProfileIntA(("Sniper"), TEXT("Visible Check4"), sniper::visible_check, path);
//	sniper::target_line = GetPrivateProfileIntA(("Sniper"), TEXT("Target Line4"), sniper::target_line, path);
//	sniper::aim_fov = GetPrivateProfileIntA(("Sniper"), TEXT("Aim Fov4"), sniper::aim_fov, path);
//	sniper::smooth = GetPrivateProfileIntA(("Sniper"), TEXT("Smooth4"), sniper::smooth, path);
//	sniper::hitbox = GetPrivateProfileIntA(("Sniper"), TEXT("Hitbox4"), sniper::hitbox, path);
//	sniper::aimkey = GetPrivateProfileIntA(("Sniper"), TEXT("Aimkey4"), sniper::aimkey, path);
//}