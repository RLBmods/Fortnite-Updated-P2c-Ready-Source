#include <list>
#include <string>
#include "Main/offsets.h"
#include <string.h>
#include "protection/xorst.h"
#include "Functions/functions.h"
#include <iostream>
#include "Cheat info/aimbot.h"




using namespace Important1;
#define debug_cache false
#define debug_weapons  false
#define M_PI 3.14159265358979323846


static float radius = 200.f;
static bool fill = false;
static bool Rainbow = false;
static bool toMouse = false;












namespace game_loop {
	class game_loop1 {
	public:

		fvector2d head;
		fvector2d neck;
		fvector2d Chest;
		fvector2d Spine;
		fvector2d pelvis;
		fvector2d left_Hip;
		fvector2d right_Hip;
		fvector2d left_Femur;
		fvector2d right_Femur;
		fvector2d left_Knee;
		fvector2d right_Knee;
		fvector2d left_Tibia;
		fvector2d right_Tibia;
		fvector2d left_Fibula;
		fvector2d right_Fibula;
		fvector2d left_Heel;
		fvector2d right_Heel;
		fvector2d left_feet;
		fvector2d right_feet;
		fvector2d root;
		fvector2d left_shoulder;
		fvector2d left_elbow;
		fvector2d left_hand;
		fvector2d right_shoulder;
		fvector2d right_elbow;
		fvector2d right_hand;
		fvector2d left_knee;

		auto cache_entities() -> void {

			temporary_entity_list.clear();

			Undetected->uworld = read <uintptr_t>(base_address + OFFSETS::UWORLD);
			Undetected->game_instance = read <uintptr_t>(Undetected->uworld + OFFSETS::game_instance);
			Undetected->local_player = read <uintptr_t>(read <uintptr_t>(Undetected->game_instance + OFFSETS::local_player));
			Undetected->player_controller = read <uintptr_t>(Undetected->local_player + OFFSETS::player_controller);
			Undetected->acknowledged_pawn = read <uintptr_t>(Undetected->player_controller + OFFSETS::acknowledged_pawn);
			Undetected->skeletal_mesh = read <uintptr_t>(Undetected->acknowledged_pawn + OFFSETS::skeletal_mesh);
			Undetected->player_state = read <uintptr_t>(Undetected->acknowledged_pawn + OFFSETS::player_state);
			Undetected->root_component = read <uintptr_t>(Undetected->acknowledged_pawn + OFFSETS::root_component);
			Undetected->relative_location = read <fvector>(Undetected->root_component + OFFSETS::relative_location);
			Undetected->team_index = read <int>(Undetected->player_state + OFFSETS::team_index);

			Undetected->game_state = read <uintptr_t>(Undetected->uworld + OFFSETS::game_state);
			Undetected->player_array = read <uintptr_t>(Undetected->game_state + OFFSETS::player_array);
			Undetected->player_array_size = read <int>(Undetected->game_state + (OFFSETS::player_array + sizeof(uintptr_t)));

			for (int i = 0; i < Undetected->player_array_size; ++i) {
				auto player_state = read <uintptr_t>(Undetected->player_array + (i * sizeof(uintptr_t)));
				auto current_actor = read <uintptr_t>(player_state + OFFSETS::pawn_private);
				auto root_component = read <uintptr_t>(current_actor + OFFSETS::root_component);
				auto relative_location = read <fvector>(root_component + OFFSETS::relative_location);
				auto pawn_private = read <uintptr_t>(player_state + OFFSETS::pawn_private);
				auto skeletalmesh = read <uintptr_t>(current_actor + OFFSETS::skeletal_mesh);
				if (!skeletalmesh) continue;
				auto base_bone = Important->get_bone_3d(skeletalmesh, boneID::Root);
				if (base_bone.x == 0 && base_bone.y == 0 && base_bone.z == 0) continue;
				if (!camera->in_screen(Important->w2s(Important->get_bone_3d(skeletalmesh, boneID::Pelvis)))) continue;
				auto is_despawning = (read<char>(current_actor + 0x758) >> 3);
				if (is_despawning) continue;

				if (Misc::Teamcheck)
				{
					if (Undetected->acknowledged_pawn)
					{
						auto team_index = read<int>(player_state + OFFSETS::team_index);
						if (Undetected->team_index == team_index) continue;
					}
				}

				entity cached_actors{ };
				cached_actors.entity = current_actor;
				cached_actors.skeletal_mesh = read<uintptr_t>(current_actor + OFFSETS::skeletal_mesh);;
				cached_actors.root_component = Undetected->root_component;
				cached_actors.relative_location = relative_location;
				cached_actors.player_state = player_state;
				cached_actors.team_index = Undetected->team_index;

				temporary_entity_list.push_back(cached_actors);
			}


			entity_list.clear();
			entity_list = temporary_entity_list;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));

		}

		fvector2d head_box;
		fvector2d root_box;
		fvector2d root_box1;

		


		auto weapon_loop()
		{
			if (Undetected->acknowledged_pawn)
			{
				uint64_t player_weapon = read <uint64_t>(Undetected->acknowledged_pawn + WeaponOffsets::CurrentWeapon);

				if (is_valid(player_weapon))
				{
					uint64_t weapon_data = read <uint64_t>(player_weapon + WeaponOffsets::WeaponData);

					if (is_valid(weapon_data))
					{
						uint64_t ftext_ptr = read <uint64_t>(weapon_data + WeaponOffsets::ItemName);

						if (is_valid(ftext_ptr))
						{
							uint64_t ftext_data = read <uint64_t>(ftext_ptr + 0x28);
							int ftext_length = read <int>(ftext_ptr + 0x30);
							if (ftext_length > 0 && ftext_length < 50) {
								wchar_t* ftext_buf = new wchar_t[ftext_length];
								io::read1(ftext_data, ftext_buf, ftext_length * sizeof(wchar_t));
								std::wstring wstr_buf(ftext_buf);
								LocalPlayerWeapon = std::string(wstr_buf.begin(), wstr_buf.end());
								wchar_t* WeaponName = ftext_buf;

								delete[] ftext_buf;
								if (Misc::weapon_cfg)
								{
									if (wcsstr(WeaponName, E(L"Assault Rifle")) || wcsstr(WeaponName, E(L"Havoc Suppressed Assault Rifle")) || wcsstr(WeaponName, E(L"Red-Eye Assault Rifle"))
										|| wcsstr(WeaponName, E(L"Suppressed Assault Rifle")) || wcsstr(WeaponName, E(L"Striker Burst Rifle")) || wcsstr(WeaponName, E(L"Burst Assault Rifle"))
										|| wcsstr(WeaponName, E(L"Ranger Assault Rifle")) || wcsstr(WeaponName, E(L"Flapjack Rifle")) || wcsstr(WeaponName, E(L"Heavy Assault Rifle"))
										|| wcsstr(WeaponName, E(L"MK-Seven Assault Rifle")) || wcsstr(WeaponName, E(L"MK-Alpha Assault Rifle")) || wcsstr(WeaponName, E(L"Combat Assault Rifle"))
										|| wcsstr(WeaponName, E(L"Nemesis AR")) || wcsstr(WeaponName, E(L"Ambush Striker AR")) || wcsstr(WeaponName, E(L"Striker AR"))
										|| wcsstr(WeaponName, E(L"Tactical Assault Rifle")) || wcsstr(WeaponName, E(L"Hammer Assault Rifle")) || wcsstr(WeaponName, E(L"Sideways Rifle")) || wcsstr(WeaponName, E(L"Makeshift Rifle")) || wcsstr(WeaponName, E(L"Drum Gun"))) {
										HeldWeaponType = EFortWeaponType::rifle;
										Aimbot::aimbot = Rifle::aimbot;
										Aimbot::aim_fov = Rifle::aim_fov;
										Aimbot::smooth = Rifle::smooth;
										Aimbot::hitbox = Rifle::hitbox;
										aimkey = Rifle::aimkey;
										if (debug_weapons)
										{
											std::cout << E("Rifle") << std::endl;
										}
									}
									if (wcsstr(WeaponName, E(L"Shotgun")) || wcsstr(WeaponName, E(L"Frenzy Auto Shotgun")) || wcsstr(WeaponName, E(L"Iron Warrior Hammer Pump Shogtun")) || wcsstr(WeaponName, E(L"Peter Griffin's Pump Shotgun")) || wcsstr(WeaponName, E(L"PETER GRIFFIN'S PUMP SHOTGUN"))) {
										HeldWeaponType = EFortWeaponType::shotgun;
										Aimbot::aimbot = Shotgun::aimbot;	
										Aimbot::aim_fov = Shotgun::aim_fov;
										Aimbot::smooth = Shotgun::smooth;
										Aimbot::hitbox = Shotgun::hitbox;
										aimkey = Shotgun::aimkey;
										if (debug_weapons)
										{
											std::cout << E("Shogtun") << std::endl;
										}
									}
									if (wcsstr(WeaponName, E(L"smg")) || wcsstr(WeaponName, E(L"Ambush Hyper SMG")) || wcsstr(WeaponName, E(L"Submachine Gun")) || wcsstr(WeaponName, E(L"Combat Smg")) || wcsstr(WeaponName, E(L"Pistol")) || wcsstr(WeaponName, E(L"Machine Smg"))

										|| wcsstr(WeaponName, E(L"Scoped Burst SMG")) || wcsstr(WeaponName, E(L"Hyper SMG")) || wcsstr(WeaponName, E(L"THUNGER BURST SMG"))) {
										HeldWeaponType = EFortWeaponType::smg;
										Aimbot::aimbot = Smg::aimbot;	
										Aimbot::aim_fov = Smg::aim_fov;
										Aimbot::smooth = Smg::smooth;
										Aimbot::hitbox = Smg::hitbox;
										aimkey = Smg::aimkey;
										if (debug_weapons)
										{
											std::cout << E("Smg") << std::endl;
										}
									}
									if (wcsstr(WeaponName, E(L"Hunting Rifle")) || wcsstr(WeaponName, E(L"Heavy Sniper Rifle")) || wcsstr(WeaponName, E(L"Suppressed Sniper Rifle"))
										|| wcsstr(WeaponName, E(L"Storm Scout")) || wcsstr(WeaponName, E(L"Bolt-Action Sniper Rifle")) || wcsstr(WeaponName, E(L"Automatic Sniper Rifle"))
										|| wcsstr(WeaponName, E(L"DMR")) || wcsstr(WeaponName, E(L"Thermal DMR")) || wcsstr(WeaponName, E(L"Hunter Bolt-Action Sniper"))
										|| wcsstr(WeaponName, E(L"Reaper Sniper Rifle")) || wcsstr(WeaponName, E(L"Semi-Auto Sniper Rifle"))
										|| wcsstr(WeaponName, E(L"Crossbow")) || wcsstr(WeaponName, E(L"Mechanical Bow")) || wcsstr(WeaponName, E(L"Hand Cannon"))) {
										HeldWeaponType = EFortWeaponType::sniper;
										Aimbot::aimbot = Sniper::aimbot;
										Aimbot::aim_fov = Sniper::aim_fov;
										Aimbot::smooth = Sniper::smooth;
										Aimbot::hitbox = Sniper::hitbox;
										aimkey = Sniper::aimkey;
										if (debug_weapons)
										{
											std::cout << ("Sniper") << std::endl;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		


		auto actor_loop() -> void
		{
			ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
			ImGui::PushFont(GameFont);


			float target_dist = FLT_MAX;
			uintptr_t target_entity = 0;



			int dynamicFOV = (Important->dynamicFOV - 80) + Aimbot::aim_fov;



			if (Aimbot::fov_circle)
			{
				if (Aimbot::FOVdynamic)
				{
					FovCircle(dynamicFOV, Aimbot::FovFilled, Aimbot::FOVlgbtq, false);
				}
				else
				{
					FovCircle(Aimbot::aim_fov, Aimbot::FovFilled, Aimbot::FOVlgbtq, false);
				}
		}




			

			if (Misc::fps) {
				ImGui::PushFont(ESPFont);
				char storage_pointer[256];
				sprintf_s(storage_pointer, E("RayanLB Public --> Frame Rate: %.1f").decrypt(), ImGui::GetIO().Framerate);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 10), ImColor(255, 255, 255, 255), storage_pointer);
			}

		
				
			// Crosshair
			if (Misc::Crosshair) {
				draw_list->AddLine(ImVec2(screen_width / 2 - 2, screen_height / 2), ImVec2(screen_width / 2 - 9, screen_height / 2), ImColor(0, 0, 0), 2);
				draw_list->AddLine(ImVec2(screen_width / 2 + 2, screen_height / 2), ImVec2(screen_width / 2 + 9, screen_height / 2), ImColor(0, 0, 0), 2);

				draw_list->AddLine(ImVec2(screen_width / 2, screen_height / 2 - 2), ImVec2(screen_width / 2, screen_height / 2 - 9), ImColor(0, 0, 0), 2);
				draw_list->AddLine(ImVec2(screen_width / 2, screen_height / 2 + 2), ImVec2(screen_width / 2, screen_height / 2 + 9), ImColor(0, 0, 0), 2);

			}
			



			const float centerWidth = screen_width / 2;
			const float centerHeight = screen_height / 2;

			for (auto& cached : entity_list)
			{
				auto root_bone = Important->get_bone_3d(cached.skeletal_mesh, boneID::Root);
				root = Important->w2s(root_bone);
				root_box1 = Important->w2s(fvector(root_bone.x, root_bone.y, root_bone.z - 15));

				auto head_bone = Important->get_bone_3d(cached.skeletal_mesh, boneID::Head);
				head = Important->w2s(head_bone);
				head_box = Important->w2s(fvector(head_bone.x, head_bone.y, head_bone.z + 15));
				auto head_location = Important->get_bone_3d(cached.skeletal_mesh, 69);

				float box_height = abs(head.y - root_box1.y);
				float box_width = box_height * 0.50f; // normalus 0.50f;
				float distance = camera_postion.location.distance(root_bone) / 100;



				if (distance > Visuals::render_distance && Undetected->acknowledged_pawn) continue;

				if (Aimbot::aimbot) {

					auto dx = head.x - (screen_width / 2);
					auto dy = head.y - (screen_height / 2);
					auto dist = sqrtf(dx * dx + dy * dy);

					if (Aimbot::visible_check) {
						if (Important->is_visible(cached.skeletal_mesh)) {
							if (dist < Aimbot::aim_fov && dist < target_dist) {

								target_dist = dist;
								target_entity = cached.entity;
							}
						}
					}
					else {
						if (dist < Aimbot::aim_fov && dist < target_dist) {


							target_dist = dist;
							target_entity = cached.entity;
						}
					}
				}

				bool inlobby;

				if (Undetected->acknowledged_pawn == NULL)
				{
					inlobby = true;
				}
				else
				{
					inlobby = false;
				}









				
		
				
				ImColor box_filled;
				ImColor box_full;
				ImColor skeleton;
				ImColor text;
				ImColor snaplines;

				if (Important->is_visible(cached.skeletal_mesh))
				{

					box_full = ImGui::GetColorU32({ Misc::box_visible[0], Misc::box_visible[1], Misc::box_visible[2],  1.0f }); // Green for visible
					box_filled = ImGui::GetColorU32({ Misc::box_filled_visible[0], Misc::box_filled_visible[1], Misc::box_filled_visible[2], 0.2f }); // Green for visible
					skeleton = ImGui::GetColorU32({ Misc::skeleton_visible[0], Misc::skeleton_visible[1], Misc::skeleton_visible[2],  1.0f }); // Green for visible
					text = ImGui::GetColorU32({ Misc::text_visible[0], Misc::text_visible[1], Misc::text_visible[2],  1.0f }); // Green for visible
					snaplines = ImGui::GetColorU32({ Misc::snaplines_visible[0], Misc::snaplines_visible[1], Misc::snaplines_visible[2],  1.0f }); // Green for visible
				}
				else
				{
					box_full = ImGui::GetColorU32({ Misc::box_invisible[0], Misc::box_invisible[1], Misc::box_invisible[2],  1.0f }); // Red for non-visible
					box_filled = ImGui::GetColorU32({ Misc::box_filled_invisible[0], Misc::box_filled_invisible[1], Misc::box_filled_invisible[2],  0.2f }); // Red for non-visible
					skeleton = ImGui::GetColorU32({ Misc::skeleton_invisible[0], Misc::skeleton_invisible[1], Misc::skeleton_invisible[2],  1.0f }); // Red for non-visible
					text = ImGui::GetColorU32({ Misc::text_invisible[0], Misc::text_invisible[1], Misc::text_invisible[2],  1.0f }); // Red for non-visible
					snaplines = ImGui::GetColorU32({ Misc::snaplines_invisible[0], Misc::snaplines_invisible[1], Misc::snaplines_invisible[2],  1.0f }); // Red for non-visible
				}
















				if (Visuals::skeleton) 
				{
					auto neck = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::Neck));
					auto chest = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::Chest));

					auto left_shoulder = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::LShoulder));
					auto right_shoulder = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::RShoulder));

					auto left_elbow = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::LElbow));
					auto right_elbow = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::RElbow));

					auto left_hand = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::LHand));
					auto right_hand = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::RHand));

					auto pelvis = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::Pelvis));

					auto left_hip = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::LHip));
					auto right_hip = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::RHip));

					auto left_knee = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::LKnee));
					auto right_knee = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::RKnee));


					auto left_foot = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::LFeet));
					auto right_foot = Important->w2s(Important->get_bone_3d(cached.skeletal_mesh, boneID::RFeet));
					


					


					if (Visuals::outline)
					{
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head.x, head.y), ImVec2(neck.x, neck.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(neck.x, neck.y), ImVec2(chest.x, chest.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(right_shoulder.x, right_shoulder.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_shoulder.x, left_shoulder.y), ImVec2(chest.x, chest.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_shoulder.x, left_shoulder.y), ImVec2(left_elbow.x, left_elbow.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_elbow.x, left_elbow.y), ImVec2(left_hand.x, left_hand.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(right_shoulder.x, right_shoulder.y), ImVec2(right_elbow.x, right_elbow.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(right_elbow.x, right_elbow.y), ImVec2(right_hand.x, right_hand.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(pelvis.x, pelvis.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(left_hip.x, left_hip.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_hip.x, left_hip.y), ImVec2(left_knee.x, left_knee.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_knee.x, left_knee.y), ImVec2(left_foot.x, left_foot.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(right_hip.x, right_hip.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(right_hip.x, right_hip.y), ImVec2(right_knee.x, right_knee.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(right_knee.x, right_knee.y), ImVec2(right_foot.x, right_foot.y), ImColor(0, 0, 0), Misc::skeleton_thick + 2.5);
					}


					
					
						

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head.x, head.y), ImVec2(neck.x, neck.y), skeleton, Misc::skeleton_thick);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(neck.x, neck.y), ImVec2(chest.x, chest.y), skeleton, Misc::skeleton_thick);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(right_shoulder.x, right_shoulder.y), skeleton, Misc::skeleton_thick);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_shoulder.x, left_shoulder.y), ImVec2(chest.x, chest.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_shoulder.x, left_shoulder.y), ImVec2(left_elbow.x, left_elbow.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_elbow.x, left_elbow.y), ImVec2(left_hand.x, left_hand.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(right_shoulder.x, right_shoulder.y), ImVec2(right_elbow.x, right_elbow.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(right_elbow.x, right_elbow.y), ImVec2(right_hand.x, right_hand.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(pelvis.x, pelvis.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(left_hip.x, left_hip.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_hip.x, left_hip.y), ImVec2(left_knee.x, left_knee.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(left_knee.x, left_knee.y), ImVec2(left_foot.x, left_foot.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(right_hip.x, right_hip.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(right_hip.x, right_hip.y), ImVec2(right_knee.x, right_knee.y), skeleton, Misc::skeleton_thick);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(right_knee.x, right_knee.y), ImVec2(right_foot.x, right_foot.y), skeleton, Misc::skeleton_thick);
					
				}





				








				// Boxs esps

				if (Visuals::Box_ESP && Visuals::enable_esp) {

					if (Visuals::box_types == 0) // box esp
					{
						if (Visuals::outline)
						{
							draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), head_box.y), ImVec2(root.x + (box_width / 2), head_box.y), ImColor(0, 0, 0), Misc::box_thick + 2);
							draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), head_box.y), ImVec2(head_box.x - (box_width / 2), root.y), ImColor(0, 0, 0), Misc::box_thick + 2);
							draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), root.y), ImVec2(root.x + (box_width / 2), root.y), ImColor(0, 0, 0), Misc::box_thick + 2);
							draw_list->AddLine(ImVec2(root.x + (box_width / 2), head_box.y), ImVec2(root.x + (box_width / 2), root.y), ImColor(0, 0, 0), Misc::box_thick + 2);
						}
						draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), head_box.y), ImVec2(root.x + (box_width / 2), head_box.y), box_full, Misc::box_thick);
						draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), head_box.y), ImVec2(head_box.x - (box_width / 2), root.y), box_full, Misc::box_thick);
						draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), root.y), ImVec2(root.x + (box_width / 2), root.y), box_full, Misc::box_thick);
						draw_list->AddLine(ImVec2(root.x + (box_width / 2), head_box.y), ImVec2(root.x + (box_width / 2), root.y), box_full, Misc::box_thick);
					}
					if (Visuals::box_types == 1) // rounded
					{
						draw_list->AddRect(ImVec2(head_box.x - box_width / 2, head_box.y), ImVec2((head_box.x - box_width / 2) + box_width, head_box.y + box_height), box_full, 10, ImDrawCornerFlags_All, Misc::box_thick);
					}
					if (Visuals::box_types == 2) // Cornered ESP
					{
						colorbox(root.x - (box_width / 2), head_box.y, box_width, box_height, Misc::box_thick, 0, true);
					}
					if (Visuals::box_types == 3) // Filled box
					{
						if (Visuals::outline)
						{
							draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), head_box.y), ImVec2(root.x + (box_width / 2), head_box.y), ImColor(0, 0, 0), Misc::box_thick + 2);
							draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), head_box.y), ImVec2(head_box.x - (box_width / 2), root.y), ImColor(0, 0, 0), Misc::box_thick + 2);
							draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), root.y), ImVec2(root.x + (box_width / 2), root.y), ImColor(0, 0, 0), Misc::box_thick + 2);
							draw_list->AddLine(ImVec2(root.x + (box_width / 2), head_box.y), ImVec2(root.x + (box_width / 2), root.y), ImColor(0, 0, 0), Misc::box_thick + 2);
						}
						draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), head_box.y), ImVec2(root.x + (box_width / 2), head_box.y), box_filled, Misc::box_thick);
						draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), head_box.y), ImVec2(head_box.x - (box_width / 2), root.y), box_filled, Misc::box_thick);
						draw_list->AddLine(ImVec2(head_box.x - (box_width / 2), root.y), ImVec2(root.x + (box_width / 2), root.y), box_filled, Misc::box_thick);
						draw_list->AddLine(ImVec2(root.x + (box_width / 2), head_box.y), ImVec2(root.x + (box_width / 2), root.y), box_filled, Misc::box_thick);
						const float halfWidth = box_width / 2.0f;
						const ImVec2 topLeft(head_box.x - halfWidth, head_box.y);
						const ImVec2 bottomRight(root.x + halfWidth, root.y);
						draw_list->AddRectFilled(topLeft, bottomRight, box_filled, 0.0f, ImDrawCornerFlags_All);
					}

				}












				

				









				// Snaplines

				if (Visuals::snapline)
				{
					if (Visuals::line_type == 0) // Head
					{
						draw_list->AddLine(ImVec2(screen_width / 2, 0), ImVec2(head_box.x, head_box.y), snaplines, Misc::line_thick);
					}
					if (Visuals::line_type == 1) // Buttom
					{
						draw_list->AddLine(ImVec2(screen_width / 2, screen_height - 5), ImVec2(root.x, root.y), snaplines, Misc::line_thick);
					}
				}









				// Head Esp

				if (Visuals::HeadEsp && Visuals::enable_esp) {


					if (!Undetected->acknowledged_pawn)
					{
						fvector2d head_2d = Important->w2s(fvector(head_bone.x, head_bone.y, head_bone.z + 20));

						fvector delta = head_bone - camera_postion.location;
						float distance = delta.length();

						const float constant_circle_size = Misc::HeadSized;

						float circle_radius = constant_circle_size * (screen_height / (2.0f * distance * tanf(camera_postion.fov * (float)M_PI / 360.f)));

						float y_offset = +70.0f;
						head_2d.y += y_offset;

						int segments = 50;



						if (Visuals::outline)
						{
							ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, ImColor(0, 0, 0, 255), segments, Misc::skeleton_thick + 2);
						}
						ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, skeleton, segments, Misc::skeleton_thick);

					}
					else
					{
						fvector2d head_2d = Important->w2s(fvector(head_bone.x, head_bone.y, head_bone.z));

						fvector delta = head_bone - camera_postion.location;
						float distance = delta.length();

						const float constant_circle_size = Misc::HeadSized;

						float circle_radius = constant_circle_size * (screen_height / (2.0f * distance * tanf(camera_postion.fov * (float)M_PI / 360.f)));

						float y_offset = +12.0f;

						int segments = 50;


						if (Visuals::outline)
						{
							ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, ImColor(0, 0, 0, 255), segments, Misc::skeleton_thick + 2);
						}
						ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, skeleton, segments, Misc::skeleton_thick);
					}

				}









				// Weapon esp

	/*			if (Visuals::weapon && Visuals::enable_esp)
				{
					if (Undetected->acknowledged_pawn)
					{

						WeaponInformation held_weapon{ };

						uint64_t player_weapon = read <uint64_t>(cached.entity + WeaponOffsets::CurrentWeapon);

						if (is_valid(player_weapon)) {
							held_weapon.ammo_count = read <int32_t>(player_weapon + WeaponOffsets::AmmoCount);

							uint64_t weapon_data = read <uint64_t>(player_weapon + WeaponOffsets::WeaponData);

							if (is_valid(weapon_data)) {
								held_weapon.tier = read <BYTE>(weapon_data + WeaponOffsets::Tier);

								uint64_t ftext_ptr = read <uint64_t>(weapon_data + WeaponOffsets::ItemName);

								if (is_valid(ftext_ptr)) {
									uint64_t ftext_data = read <uint64_t>(ftext_ptr + 0x28);
									int ftext_length = read <int>(ftext_ptr + 0x30);
									if (ftext_length > 0 && ftext_length < 50) {
										wchar_t* ftext_buf = new wchar_t[ftext_length];

										io::read1(ftext_data, ftext_buf, ftext_length * sizeof(wchar_t));
										std::wstring wstr_buf(ftext_buf);
										held_weapon.weapon_name = std::string(wstr_buf.begin(), wstr_buf.end());
										delete[] ftext_buf;
									}
								}

							}

							WeaponInfo = held_weapon;

							std::string final = ("") + WeaponInfo.weapon_name + ("");

							ImVec2 TextSize = ImGui::CalcTextSize(final.c_str());

							ImVec2 text_size = ImGui::CalcTextSize(final.c_str());
							int add;
							if (Visuals::distance)
							{
								add = 25;
							}
							else
							{
								add = 5;
							}

							if (Visuals::weapon)
							{
								if (WeaponInfo.tier == 0)
								{
									if (strstr(WeaponInfo.weapon_name.c_str(), E("Pickaxe")) != nullptr)
									{
										DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(255, 255, 255), false, true, final.c_str());
									}
									else
									{
										std::string fina1l = ("Building Plan");
										ImVec2 TextSiz1e = ImGui::CalcTextSize(fina1l.c_str());
										DrawString(15, (root.x) - (TextSiz1e.x / 2), (root.y + add), ImColor(255, 255, 255), false, true, fina1l.c_str());
									}

								}
								if (WeaponInfo.tier == 1)
								{
									std::string combined_text;
									if (Visuals::AmmoCount) {
										char text_ammo_count3[256];
										sprintf_s(text_ammo_count3, "[%d]", WeaponInfo.ammo_count);
										combined_text = final + " " + text_ammo_count3;
									}
									else {
										combined_text = final;
									}
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(170, 165, 169), false, true, combined_text.c_str());
								}

								if (WeaponInfo.tier == 2)
								{
									std::string combined_text;
									if (Visuals::AmmoCount) {
										char text_ammo_count3[256];
										sprintf_s(text_ammo_count3, "[%d]", WeaponInfo.ammo_count);
										combined_text = final + " " + text_ammo_count3;
									}
									else {
										combined_text = final;
									}
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(30, 255, 0), false, true, combined_text.c_str());

								}
								if (WeaponInfo.tier == 3)
								{
									std::string combined_text;
									if (Visuals::AmmoCount) {
										char text_ammo_count3[256];
										sprintf_s(text_ammo_count3, "[%d]", WeaponInfo.ammo_count);
										combined_text = final + " " + text_ammo_count3;
									}
									else {
										combined_text = final;
									}
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(0, 112, 221), false, true, combined_text.c_str());
								}
								if (WeaponInfo.tier == 4)
								{
									std::string combined_text;
									if (Visuals::AmmoCount) {
										char text_ammo_count3[256];
										sprintf_s(text_ammo_count3, "[%d]", WeaponInfo.ammo_count);
										combined_text = final + " " + text_ammo_count3;
									}
									else {
										combined_text = final;
									}
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(163, 53, 238), false, true, combined_text.c_str());
								}
								if (WeaponInfo.tier == 5)
								{
									std::string combined_text;
									if (Visuals::AmmoCount) {
										char text_ammo_count3[256];
										sprintf_s(text_ammo_count3, "[%d]", WeaponInfo.ammo_count);
										combined_text = final + " " + text_ammo_count3;
									}
									else {
										combined_text = final;
									}
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(255, 128, 0), false, true, combined_text.c_str());
								}
								if (WeaponInfo.tier == 6)
								{
									std::string combined_text;
									if (Visuals::AmmoCount) {
										char text_ammo_count3[256];
										sprintf_s(text_ammo_count3, "[%d]", WeaponInfo.ammo_count);
										combined_text = final + " " + text_ammo_count3;
									}
									else {
										combined_text = final;
									}
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(255, 255, 0), false, true, combined_text.c_str());
								}
							}
							else
							{
								if (WeaponInfo.tier == 0)
								{
									if (strstr(WeaponInfo.weapon_name.c_str(), E("Pickaxe")) != nullptr)
									{
										DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), visibleColor, false, true, final.c_str());
									}
									else
									{
										std::string fina1l = ("Building Plan");
										ImVec2 TextSiz1e = ImGui::CalcTextSize(fina1l.c_str());
										DrawString(15, (root.x) - (TextSiz1e.x / 2), (root.y + add), visibleColor, false, true, fina1l.c_str());
									}
								}
								else
								{
									DrawString(14, root.x - (text_size.x / 2), root.y + 20, visibleColor, false, true, final.c_str());
								}

							}
						}

					}
				}*/






				



				if (Visuals::weapon && Visuals::enable_esp && Undetected->acknowledged_pawn) {
					ImGui::PushFont(WeaponFont);
					WeaponInformation held_weapon{};

					uint64_t player_weapon = read<uint64_t>(cached.entity + WeaponOffsets::CurrentWeapon);
					if (is_valid(player_weapon)) {
						held_weapon.ammo_count = read<int32_t>(player_weapon + WeaponOffsets::AmmoCount);

						uint64_t weapon_data = read<uint64_t>(player_weapon + WeaponOffsets::WeaponData);
						if (is_valid(weapon_data)) {
							held_weapon.tier = read<BYTE>(weapon_data + WeaponOffsets::Tier);

							uint64_t ftext_ptr = read<uint64_t>(weapon_data + WeaponOffsets::ItemName);
							if (is_valid(ftext_ptr)) {
								uint64_t ftext_data = read<uint64_t>(ftext_ptr + 0x28);
								int ftext_length = read<int>(ftext_ptr + 0x30);
								if (ftext_length > 0 && ftext_length < 50) {
									wchar_t* ftext_buf = new wchar_t[ftext_length];
									io::read1(ftext_data, ftext_buf, ftext_length * sizeof(wchar_t));
									std::wstring wstr_buf(ftext_buf);
									held_weapon.weapon_name = std::string(wstr_buf.begin(), wstr_buf.end());
									delete[] ftext_buf;
								}
							}
						}



						WeaponInfo = held_weapon;
						ImColor textColor;


						std::string final = WeaponInfo.weapon_name;
						if (Visuals::AmmoCount) {
							final = WeaponInfo.weapon_name + " (" + std::to_string(WeaponInfo.ammo_count) + ")";
						}

						ImVec2 text_size = ImGui::CalcTextSize(final.c_str());


						int add = Visuals::distance ? 25 : 5;

						
						if (Visuals::weapon) 
						{
							switch (WeaponInfo.tier) {
							case 0: textColor = strstr(WeaponInfo.weapon_name.c_str(), "Pickaxe") != nullptr ? ImColor(255, 255, 255) : ImColor(255, 255, 255); break; // Modify color as needed
							case 1: textColor = ImColor(170, 165, 169); break;
							case 2: textColor = ImColor(30, 255, 0); break;
							case 3: textColor = ImColor(0, 112, 221); break;
							case 4: textColor = ImColor(163, 53, 238); break;
							case 5: textColor = ImColor(255, 128, 0); break;
							case 6: textColor = ImColor(255, 255, 0); break;
							}
						}
						else {
							//textColor = WeaponInfo.tier == 0 ? ImColor(255, 255, 255) : visibleColor;
						}
						
							DrawString(Misc::fontsize, head_box.x - (text_size.x / 2), head_box.y - 15, textColor, false, true, final.c_str());
						
					}
				}



				
				
				// Username + platform


				if (Visuals::username && Visuals::enable_esp && Visuals::platform && Visuals::enable_esp) // name + platform
				{
					ImGui::PushFont(UsernamePlatformFont);
					std::string username_str = Important->get_player_name(cached.player_state);
					std::string platform_str = Important->platform(cached.player_state);


					ImVec2 text_size1 = ImGui::CalcTextSize(username_str.c_str());
					ImVec2 text_size2 = ImGui::CalcTextSize(platform_str.c_str());


					ImVec2 textPosition(text_size1.x, text_size2.y);

					std::string combinedText = username_str + " - (" + platform_str + ")";
					DrawString(Misc::fontsize, head_box.x - 20 - (textPosition.x / 2), head_box.y - 25, text, false, true, combinedText.c_str());
				}

				


				// Username

				else if (Visuals::username && Visuals::enable_esp)
				{
					ImGui::PushFont(UsernamePlatformFont);
					std::string username_str = Important->get_player_name(cached.player_state);
					ImVec2 text_size = ImGui::CalcTextSize(username_str.c_str());
					DrawString(Misc::fontsize, head_box.x - (text_size.x / 2), head_box.y - 25, text, false, true, username_str.c_str());
				}


				// Platform

				else if (Visuals::platform && Visuals::enable_esp)
				{
					ImGui::PushFont(UsernamePlatformFont);
					std::string platform_str = Important->platform(cached.player_state);
					ImVec2 text_size = ImGui::CalcTextSize(platform_str.c_str());
					DrawString(Misc::fontsize, head_box.x - (text_size.x / 2), head_box.y - 25, text, false, true, platform_str.c_str());
				}



		







				if (Visuals::distance && Visuals::enable_esp) // distance
				{
					ImGui::PushFont(DistanceFont);
					std::string distance_str = (std::string)("(") + std::to_string((int)distance) + (std::string)("m)");
					ImVec2 text_size = ImGui::CalcTextSize(distance_str.c_str());

					DrawString(Misc::fontsize, head_box.x - (text_size.x / 2), head_box.y - 35, text, false, true, distance_str.c_str());
				}



				

			









				if (Misc::KillCount) {
					int KillCount = read<int>(cached.player_state + 0x1264);
					std::string kills_display = "Kills -> " + std::to_string(KillCount);
					ImVec2 TextSize = ImGui::CalcTextSize(kills_display.c_str());
					DrawString(Misc::fontsize, (head_box.x + 80) - (TextSize.x / 2), (head_box.y + 35), ImColor(255, 255, 255), false, true, kills_display.c_str());
				}


				if (Misc::playerid) {
					int player_id_count = read<int>(cached.player_state + 0x294);

					std::string player_id_display = "ID -> " + std::to_string(player_id_count);
					ImVec2 player_id_text_size = ImGui::CalcTextSize(player_id_display.c_str());
					DrawString(Misc::fontsize, (head_box.x + 80) - (player_id_text_size.x / 2), (head_box.y + 25), ImColor(255, 255, 255), false, true, player_id_display.c_str());
				}





				if (Misc::playercount)
				{
					int visiblePlayers = 0;

					for (int i = 0; i < Undetected->player_array_size; ++i)
					{
						uintptr_t player = read<uintptr_t>(Undetected->player_array + i * sizeof(uintptr_t));
						if (is_valid(player))
						{
							if (Important->is_visible(player) && distance <= 275)
							{
								visiblePlayers++;
							}
						}
					}

					char playerCountText[256];
					sprintf_s(playerCountText, "Rendering -> %d", visiblePlayers);
					ImVec2 screenSize = ImGui::GetIO().DisplaySize;
					ImVec2 textSize = ImGui::CalcTextSize(playerCountText);

					ImGui::GetBackgroundDrawList()->AddText(ImVec2((screenSize.x - textSize.x) * 0.5f, 5), ImColor(255, 0, 0), playerCountText);
				}


				





			}



			// Prediction 

			if (target_entity && Aimbot::aimbot) {

				auto closest_mesh = read<uint64_t>(target_entity + OFFSETS::skeletal_mesh);
				auto root = read<uintptr_t>(target_entity + OFFSETS::root_component);
				fvector Velocity = read<fvector>(root + OFFSETS::velocity);

				
				fvector hitbox;
				float projectileSpeed = 60000.f; // 60000.f
				float projectileGravityScale = 3.5f; // 3.5f

				

				switch (Aimbot::hitbox) {
				case 0:

					hitbox = Important->get_bone_3d(closest_mesh, boneID::Head);;
					break;
				case 1:

					hitbox = Important->get_bone_3d(closest_mesh, boneID::Neck);;
					break;
				case 2:

					hitbox = Important->get_bone_3d(closest_mesh, boneID::Chest);;
					break;
				case 3:

					hitbox = Important->get_bone_3d(closest_mesh, boneID::Pelvis);;
					break;
				}



			
				


				if (Sniper::prediction) {
					if (EFortWeaponType::sniper)
					{
						if (strstr(LocalPlayerWeapon.c_str(), ("Reaper Sniper Rifle"))) {

						projectileSpeed = 64590; // 62000
						projectileGravityScale = 4.0; // 3.5

						auto Distance = camera_postion.location.distance(hitbox);

						hitbox = Important->Anis_Target_Prediction(hitbox, Velocity, projectileSpeed, projectileGravityScale, Distance);

					}
					}
				}


				fvector2d hitbox_screen = Important->w2s(hitbox);

				if (hitbox.x != 0 || hitbox.y != 0 && (get_cross_distance(hitbox.x, hitbox.y, screen_width / 2, screen_height / 2) <= Aimbot::aim_fov))
				{
					if (Aimbot::target_line) // Target Line
					{
						ImGui::GetForegroundDrawList()->AddLine(ImVec2(screen_width / 2, screen_height / 2), ImVec2(hitbox_screen.x, hitbox_screen.y), ImColor(255, 255, 255, 255), 1); // 2 size
					}


					if (Aimbot::target_text) // Target Text
					{
						DrawString(20, hitbox_screen.x - 6, hitbox_screen.y - 30, ImColor(255, 255, 255, 255), true, true, E("[T]"));
					}

					{
					

					if (GetAsyncKeyState_Spoofed(aimkey))
						input->move(hitbox_screen);


				}
			}
		}
					//else {
						//target_dist = FLT_MAX;
					//	target_entity = NULL;
					ImGui::PopFont();
		}
	};
} static game_loop::game_loop1* loop_game = new game_loop::game_loop1();
