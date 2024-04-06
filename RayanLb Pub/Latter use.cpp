//auto loot_loop() -> void
		//{
		//	if (WorldESP::WorldEnable)
		//	{
		//		for (LootEntity Level : LootEntityList)
		//		{
		//			uintptr_t ItemRootComponent = read<uintptr_t>(Level.ACurrentItem + WorldOffsets::RootComponent); 
		//			fvector ItemPosition = read<fvector>(ItemRootComponent + 0x128);
		//			float ItemDist = camera_postion.location.distance(ItemPosition) / 100.0f;
		//			
		//			fvector2d ScreenPosition = Important->w2s(ItemPosition);
		//			if (WorldESP::DrawChest && strstr(Level.GNames.c_str(), ("Tiered_Chest")))
		//			{
		//				if (ItemDist < WorldESP::lootEspDist)
		//				{
		//					std::string Text = ("Chest [") + std::to_string((int)ItemDist) + ("m]");
		//					ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());
		//					ImGui::GetBackgroundDrawList()->AddText(ImVec2((ScreenPosition.x) - (TextSize.x / 2), (ScreenPosition.y)), ImColor(255, 165, 0), Text.c_str());
		//				}
		//			}
		//			if (WorldESP::DrawAmmoBox && strstr(Level.GNames.c_str(), ("Tiered_Ammo")))
		//			{
		//				if (ItemDist < WorldESP::lootEspDist)
		//				{
		//					std::string Text = ("AmmoBox [") + std::to_string((int)ItemDist) + ("m]");
		//					ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());
		//					ImGui::GetBackgroundDrawList()->AddText(ImVec2((ScreenPosition.x) - (TextSize.x / 2), (ScreenPosition.y)), ImColor(0, 255, 39), Text.c_str());
		//				}
		//			}
		//			if (WorldESP::drawloot && strstr(Level.GNames.c_str(), ("FortPickupAthena")) || strstr(Level.GNames.c_str(), ("Fort_Pickup_Creative_C")))
		//			{
		//				if (ItemDist < WorldESP::lootEspDist)
		//				{
		//					auto definition = read<uint64_t>(Level.ACurrentItem + WorldOffsets::PrimaryPickupItemEntry + WorldOffsets::ItemDefinition);
		//					BYTE tier = read<BYTE>(definition + WorldOffsets::Tier1); 
		//					fvector2d ChestPosition = Important->w2s(ItemPosition);

		//					auto DisplayName = read<uint64_t>(definition + WorldOffsets::DisplayName);
		//					auto WeaponLenght = read<uint32_t>(DisplayName + 0x30);
		//					wchar_t* WeaponName = new wchar_t[uint64_t(WeaponLenght) + 1];
		//					io::read1((DisplayName + WorldOffsets::ItemName1), WeaponName, WeaponLenght * sizeof(wchar_t)); // read_array



		//					std::string Text = wchar_to_char(WeaponName);
		//					std::string wtf2 = Text + "[" + std::to_string((int)ItemDist) + ("m");
		//					ImColor ColorLoot;
		//					if (tier == 2 && (WorldESP::uncommon))
		//					{
		//						ColorLoot = ImColor(0, 255, 0, 255);
		//					}
		//					else if ((tier = 3) && (WorldESP::rare))
		//					{
		//						ColorLoot = ImColor(0, 0, 255, 255);
		//					}
		//					else if ((tier = 4) && (WorldESP::purple))
		//					{
		//						ColorLoot = ImColor(128, 0, 128, 255);
		//					}
		//					else if ((tier = 5) && (WorldESP::gold))
		//					{
		//						ColorLoot = ImColor(255, 255, 0, 255);
		//					}
		//					else if ((tier = 6) && (WorldESP::mythic))
		//					{
		//						ColorLoot = ImColor(255, 255, 0, 255);
		//					}
		//					else if ((tier = 0) && (WorldESP::common))
		//					{
		//						ColorLoot = ImColor(255, 255, 255, 255);
		//					}
		//					ImVec2 TextSize = ImGui::CalcTextSize(wtf2.c_str());
		//					ImGui::GetBackgroundDrawList()->AddText(ImVec2((ScreenPosition.x) - (TextSize.x / 2), (ScreenPosition.y)), ColorLoot, wtf2.c_str());
		//				}
		//			}
		//			if (WorldESP::DrawVehicles && (strstr(Level.GNames.c_str(), ("MeatballVehicle_L_C"))) || (strstr(Level.GNames.c_str(), ("Valte_SportsC")))){
		//				if (ItemDist < WorldESP::lootEspDist) {
		//					std::string Text = ("Vehicle [") + std::to_string((int)ItemDist) + ("m]");
		//					ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());
		//					ImGui::GetBackgroundDrawList()->AddText(ImVec2((ScreenPosition.x) - (TextSize.x / 2), (ScreenPosition.y)), ImColor(220, 220, 220), Text.c_str());
		//				}
		//			}
		//		}
		//	}
		//}