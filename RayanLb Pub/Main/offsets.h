enum OFFSETS {
	UWORLD = 0x11F26508,
	game_instance = 0x1D8,
	game_state = 0x160,
	local_player = 0x38,
	player_controller = 0x30,
	acknowledged_pawn = 0x338, // localpawn
	skeletal_mesh = 0x318,
	player_state = 0x2B0,
	root_component = 0x198,
	velocity = 0x168,
	relative_location = 0x120,
	relative_rotation = 0x138,
	team_index = 0x1251,
	player_array = 0x2A8,
	pawn_private = 0x308,
	component_to_world = 0x1c0, // C2w
	b_Allow_Targeting = 0xd3,
	location_under_reticle = 0x2530,
};

enum WeaponOffsets {

	CurrentWeapon = 0xA68,
	AmmoCount = 0xE54,
	WeaponData = 0x4F0,
	Tier = 0x13c,
	ItemName = 0x40,
};





enum boneID : int {
	Head = 110,
	Neck = 67,
	LHand = 11,
	RHand = 40,
	RElbow = 39,
	LElbow = 10,
	LShoulder = 9,
	RShoulder = 38,
	Chest = 66,
	Pelvis = 2,
	LHip = 71,
	RHip = 78,
	LKnee = 72,
	RKnee = 79,
	LFeet = 73,
	RFeet = 82,
	Root = 0
};


//enum WorldOffsets {
//	DisplayName = 0x30,
//	ItemDefinition = 0x18,
//	Tier1 = 0x13b,
//	RootComponent = 0x198,
//	ItemName1 = 0x38,
//	PrimaryPickupItemEntry = 0x350,
//};







