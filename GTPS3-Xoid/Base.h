﻿#pragma once
using json = nlohmann::json;
BYTE* item_data;
int item_hash, item_data_size;
vector<string> swear_words = {};
ENetHost* server;
bool Harvest_Festival = false, Halloween = false, Thanksgiving = false, December = false, Winterfest = false, Comet_Dust = false, Zombie_Apocalypse = false;
vector<vector<int>> kainos = {

};
string shop_list = "", sho2_list = "", sho3_list = "", zombie_list = "", surgery_list = "", rare_text = "", rainbow_text = "";
vector<pair<int, int>> shop_item; vector<pair<int, int>> sho2_item; vector<pair<int, int>> sho3_item;

int server_port = 0, isWhitelist = 0, isBeta = 0, panic_mode = 1;
vector<string> whitelist, glist, clist, server_owner;
vector<int> onehit = { 2952 };
vector<int> extragems = {};
string server_name, cache_url, cache_path, discord_url, server_ip;

vector<vector<vector<int>>> crystal_receptai = {
	{{2242 /*red*/, 2}, {2244 /*green*/, 0}, {2246 /*blue*/, 0}, {2248 /*white*/, 3}, {2250 /*black*/, 0}, {2254, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 1}, {2246 /*blue*/, 0}, {2248 /*white*/, 3}, {2250 /*black*/, 0}, {2262, 1}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 3}, {2246 /*blue*/, 0}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {2942, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 0}, {2246 /*blue*/, 2}, {2248 /*white*/, 3}, {2250 /*black*/, 0}, {2258, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 1}, {2246 /*blue*/, 1}, {2248 /*white*/, 3}, {2250 /*black*/, 0}, {2264, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 3}, {2246 /*blue*/, 2}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {2944, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 2}, {2246 /*blue*/, 0}, {2248 /*white*/, 3}, {2250 /*black*/, 0}, {2256, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 0}, {2246 /*blue*/, 1}, {2248 /*white*/, 3}, {2250 /*black*/, 0}, {2260, 1}},
	{{2242 /*red*/, 3}, {2244 /*green*/, 0}, {2246 /*blue*/, 2}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {2940, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 0}, {2246 /*blue*/, 0}, {2248 /*white*/, 0}, {2250 /*black*/, 5}, {2212, 1}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 0}, {2246 /*blue*/, 2}, {2248 /*white*/, 1}, {2250 /*black*/, 0}, {2972, 1}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 1}, {2246 /*blue*/, 2}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {2268, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 2}, {2246 /*blue*/, 0}, {2248 /*white*/, 1}, {2250 /*black*/, 2}, {2266, 1}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 0}, {2246 /*blue*/, 0}, {2248 /*white*/, 0}, {2250 /*black*/, 3}, {2754, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 0}, {2246 /*blue*/, 0}, {2248 /*white*/, 3}, {2250 /*black*/, 1}, {2756, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 3}, {2246 /*blue*/, 0}, {2248 /*white*/, 2}, {2250 /*black*/, 0}, {2706, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 1}, {2246 /*blue*/, 1}, {2248 /*white*/, 0}, {2250 /*black*/, 2}, {3180, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 0}, {2246 /*blue*/, 0}, {2248 /*white*/, 2}, {2250 /*black*/, 3}, {4124, 1}},
	{{2242 /*red*/, 3}, {2244 /*green*/, 0}, {2246 /*blue*/, 0}, {2248 /*white*/, 2}, {2250 /*black*/, 0}, {5268, 1}},
	{{2242 /*red*/, 3}, {2244 /*green*/, 1}, {2246 /*blue*/, 0}, {2248 /*white*/, 1}, {2250 /*black*/, 0}, {5266, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 0}, {2246 /*blue*/, 0}, {2248 /*white*/, 1}, {2250 /*black*/, 4}, {6848, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 0}, {2246 /*blue*/, 3}, {2248 /*white*/, 2}, {2250 /*black*/, 0}, {6820, 1}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 2}, {2246 /*blue*/, 3}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {2272, 3}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 0}, {2246 /*blue*/, 3}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {2276, 5}},
	{{2242 /*red*/, 0}, {2244 /*green*/, 2}, {2246 /*blue*/, 1}, {2248 /*white*/, 2}, {2250 /*black*/, 0}, {2252, 1}},
	{{2242 /*red*/, 3}, {2244 /*green*/, 0}, {2246 /*blue*/, 1}, {2248 /*white*/, 1}, {2250 /*black*/, 0}, {2274, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 2}, {2246 /*blue*/, 2}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {2270, 10}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 1}, {2246 /*blue*/, 1}, {2248 /*white*/, 1}, {2250 /*black*/, 0}, {2590, 5}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 1}, {2246 /*blue*/, 1}, {2248 /*white*/, 1}, {2250 /*black*/, 0}, {2812, 1}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 2}, {2246 /*blue*/, 0}, {2248 /*white*/, 1}, {2250 /*black*/, 0}, {3424, 1}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 2}, {2246 /*blue*/, 1}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {3770, 3}},
	{{2242 /*red*/, 3}, {2244 /*green*/, 2}, {2246 /*blue*/, 0}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {3526, 20}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 2}, {2246 /*blue*/, 0}, {2248 /*white*/, 0}, {2250 /*black*/, 1}, {3582, 1}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 0}, {2246 /*blue*/, 2}, {2248 /*white*/, 0}, {2250 /*black*/, 1}, {4762, 1}},
	{{2242 /*red*/, 2}, {2244 /*green*/, 1}, {2246 /*blue*/, 0}, {2248 /*white*/, 2}, {2250 /*black*/, 0}, {5204, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 0}, {2246 /*blue*/, 2}, {2248 /*white*/, 2}, {2250 /*black*/, 0}, {5106, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 1}, {2246 /*blue*/, 1}, {2248 /*white*/, 2}, {2250 /*black*/, 0}, {5104, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 2}, {2246 /*blue*/, 1}, {2248 /*white*/, 1}, {2250 /*black*/, 0}, {5272, 10}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 3}, {2246 /*blue*/, 1}, {2248 /*white*/, 0}, {2250 /*black*/, 1}, {5274, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 1}, {2246 /*blue*/, 1}, {2248 /*white*/, 3}, {2250 /*black*/, 0}, {5270, 1}},
	{{2242 /*red*/, 1}, {2244 /*green*/, 3}, {2246 /*blue*/, 1}, {2248 /*white*/, 0}, {2250 /*black*/, 0}, {5280, 10}},
	{{2242 /*red*/, 3}, {2244 /*green*/, 0}, {2246 /*blue*/, 0}, {2248 /*white*/, 1}, {2250 /*black*/, 1}, {392, 1}}
};
vector<vector<vector<int>>> receptai = {
	{{914, 5}, {916, 5}, {924, 10}, {770, 1}},
	{{914, 30}, {916, 6}, {920, 5}, {906, 1}},
	{{914, 10}, {916, 5}, {918, 1}, {902, 3}},
	{{914, 5}, {924, 4}, {920, 2}, {926, 5}},
	{{914, 6}, {924, 3}, {918, 4}, {1114, 1}},
	{{914, 15}, {920, 4}, {918, 2}, {978, 4}},
	{{917, 10}, {924, 3}, {918, 3}, {772, 1}},
	{{917, 2}, {920, 4}, {918, 3}, {904, 1}},
	{{924, 20}, {920, 4}, {918, 5}, {922, 1}},
	{{914, 20}, {916, 10}, {922, 1}, {1162, 1}},
	{{914, 10}, {920, 2}, {922, 1}, {1746, 5}},
	{{914, 20}, {918, 15}, {922, 10}, {1542, 1}},
	{{916, 8}, {924, 4}, {922, 1}, {2588, 1}},
	{{916, 1}, {918, 1}, {922, 1}, {1866, 2}},
	{{924, 3}, {920, 3}, {922, 3}, {908, 1}},
	{{924, 4}, {918, 3}, {922, 1}, {1310, 1}},
	{{920, 200}, {918, 200}, {922, 200}, {910, 1}},
	{{914, 10}, {922, 10}, {1962, 10}, {4582, 1}},
	{{916, 9}, {924, 5}, {1962, 1}, {4552, 1}},
	{{6970, 50}, {7006, 50}, {6986, 50}, {6948, 1}},
	{{7156, 20}, {6986, 5}, {7154, 5}, {7150, 1}},
	{{7006, 10}, {6970, 5}, {6988, 5}, {7008, 1}},
	{{6828, 2}, {186, 100}, {6972, 20}, {6934, 1}},
	{{6834, 2}, {186, 100}, {6960, 2}, {6936, 1}},
	{{6250, 2}, {186, 100}, {6978, 20}, {6930, 1}},
	{{6940, 2}, {186, 100}, {6976, 2}, {6944, 1}},
	{{6236, 1}, {6962, 1}, {6992, 5}, {6918, 1}},
	{{6238, 1}, {6960, 5}, {7012, 1}, {6920, 1}},
	{{6988, 100}, {7010, 15}, {6976, 50}, {6946, 1}},
	{{6244, 1}, {260, 100}, {6962, 2}, {6928, 1}},
	{{6256, 1}, {260, 100}, {6994, 10}, {6932, 1}},
	{{6238, 1}, {260, 100}, {6960, 2}, {6926, 1}},
	{{7308, 1}, {260, 100}, {7012, 10}, {7306, 1}},
	{{6926, 1}, {6972, 1}, {7010, 1}, {6922, 1}},
	{{6240, 1}, {6972, 1}, {6992, 10}, {6924, 1}},
	{{7158, 20}, {7160, 3}, {6978, 3}, {7152, 1}},
	{{6994, 100}, {6978, 100}, {6964, 100}, {6950, 1}},
	{{6980, 100}, {6998, 100}, {7016, 100}, {6952, 1}},
	{{6984, 75}, {7018, 75}, {6968, 75}, {6954, 1}}
};
struct dotted : numpunct<char> {
	char do_thousands_sep()   const { return ','; }
	string do_grouping() const { return "\3"; }
	static void imbue(ostream& os) { os.imbue(locale(os.getloc(), new dotted)); }
};
string setGems(int gems) {
	stringstream ss;
	dotted::imbue(ss);
	ss << gems;
	return ss.str();
}
bool includesint(vector<int>& vec, int number) {
	for (const auto& item : vec) {
		if (item == number) return true;
	}
	return false;
}
vector<string> get_properties(unsigned char btype, unsigned char bcateg) {
	vector<string> list;
	if ((btype & 0x40) > 0) {
		list.push_back("NoShadow");
	} if ((btype & 0x20) > 0) {
		list.push_back("NoSelf");
	} if ((btype & 2) > 0) {
		list.push_back("Wrenchable");
	} if ((btype & 8) > 0) {
		list.push_back("Dropless");
	} if ((btype & 0x10) > 0) {
		list.push_back("NoSeed");
	} if ((btype & 4) > 0) {
		list.push_back("Permanent");
	} if ((btype & 1) > 0) {
		list.push_back("MultiFacing");
	} if ((btype & 0x80) > 0) {
		list.push_back("WorldLock");
	} if ((bcateg & 0x80) > 0) {
		list.push_back("Untradable");
	} if ((bcateg & 0x20) > 0) {
		list.push_back("Foreground");
	} if ((bcateg & 0x10) > 0) {
		list.push_back("Public");
	} if ((bcateg & 1) > 0) {
		list.push_back("Beta");
	} if ((bcateg & 4) > 0) {
		list.push_back("Mod");
	} if ((bcateg & 8) > 0) {
		list.push_back("RandomGrow");
	} if ((bcateg & 0x40) > 0) {
		list.push_back("Holiday");
	} if ((bcateg & 2) > 0) {
		list.push_back("AutoPickup");
	}
	return list;
}
string getItemCategory(const char actionType, string name_) {
	switch (actionType) {
	case 0:
		return "Fist";
	case 1:
		return "Wrench";
	case 2:
		return "Door";
	case 3:
		return "Lock";
	case 4:
		return "Gems";
	case 5:
		return "Treasure";
	case 6:
		return "Deadly_Block";
	case 7:
		return "Trampoline_Block";
	case 8:
		return "Consummable";
	case 9:
		return "Gateway";
	case 10:
		return "Sign";
	case 11:
		return "SFX_Foreground";
	case 12:
		return "Toggleable_Foreground";
	case 13:
		return "Main_Door";
	case 14:
		return "Platform";
	case 15:
		return "Bedrock";
	case 16:
		return "Pain_Block";
	case 17:
		return "Foreground_Block";
	case 18:
		return "Background_Block";
	case 19:
		return "Seed";
	case 20:
		return "Clothing";
	case 21:
		return "Animated_Foreground_Block";
	case 22:
		return "SFX_Background";
	case 23:
		return "Toggleable_Background";
	case 24:
		return "Bouncy";
	case 25:
		return "Spike";
	case 26:
		return "Portal";
	case 27:
		return "Checkpoint";
	case 28:
		return "Sheet_Music";
	case 29:
		return "Slippery_Block";
	case 48:
		return "Unknown";
	case 31:
		return "Switch_Block";
	case 32:
		return "Chest";
	case 33:
		return "Mailbox";
	case 34:
		return "Bulletin_Board";
	case 35:
		return "Event_Mystery_Block";
	case 36:
		return "Random_Block";
	case 37:
		return "Component";
	case 38:
		return "Provider";
	case 39:
		return "Chemical_Combiner";
	case 40:
		return "Achievement_Block";
	case 41:
		return "Weather_Machine";
	case 42:
		return "Scoreboard";
	case 43:
		return "Sungate";
	case 44:
		return "Profile";
	case 45:
		return "Toggleable_Deadly_Block";
	case 46:
		return "Heart_Monitor";
	case 47:
		return "Donation_Box";
	case 49:
		return "Mannequin";
	case 50:
		return "Security_Camera";
	case 51:
		return "Magic_Egg";
	case 52:
		return "Game_Block";
	case 53:
		return "Game_Generator";
	case 54:
		return "Xenonite";
	case 55:
		return "Phone_Booth";
	case 56:
		return "Crystal";
	case 57:
		return "Crime_Villain";
	case 58:
		return "Clothing_Compactor";
	case 59:
		return "Spotlight";
	case 60:
		return "Pushing_Block";
	case 61:
		return "Display";
	case 62:
		return "Vending";
	case 63:
		return "Fish";
	case 64:
		return "Fish_Tank_Port";
	case 65:
		return "Solar_Collector";
	case 66:
		return "Forge";
	case 67:
		return "Giving_Tree";
	case 68:
		return "Giving_Tree_Stump";
	case 69:
		return "Steam_Block";
	case 70:
		return "Steam_Pain_Block";
	case 71:
		return "Steam_Music_Block";
	case 72:
		return "Silkworm";
	case 73:
		return "Sewing_Machine";
	case 74:
		return "Country_Flag";
	case 75:
		return "Lobster_Trap";
	case 76:
		return "Painting_Easel";
	case 77:
		return "Battle_Pet_Cage";
	case 78:
		return "Pet_Trainer";
	case 79:
		return "Steam_Engine";
	case 80:
		return "Lock_Bot";
	case 81:
		return "Weather_Machine_S1";
	case 82:
		return "Spirit_Storage";
	case 83:
		return "Display_Shelf";
	case 84:
		return "VIP";
	case 85:
		return "Chal_Timer";
	case 86:
		return "Chal_Flag";
	case 87:
		return "Fish_Mount";
	case 88:
		return "Portrait";
	case 89:
		return "Weather_Machine_S2";
	case 90:
		return "Fossil";
	case 91:
		return "Fossil_Prep_Station";
	case 92:
		return "DNA_Processor";
	case 93:
		return "Blaster";
	case 94:
		return "Valhowla_Treasure";
	case 95:
		return "Chemsynth";
	case 96:
		return "Chemsynth_Tank";
	case 97:
		return "Untrade_A_Box";
	case 98:
		return "Oven";
	case 99:
		return "Audio";
	case 100:
		return "Geiger_Charger";
	case 101:
		return "Adventure_Reset";
	case 102:
		return "Tomb_Robber";
	case 103:
		return "Faction";
	case 104:
		return "Red_Faction";
	case 105:
		return "Green_Faction";
	case 106:
		return "Blue_Faction";
	case 107:
		return "Artifact";
	case 108:
		return "LemonJelly";
	case 109:
		return "FishTrainingTank";
	case 110:
		return "FishingBlock";
	case 111:
		return "ItemSucker";
	case 112:
		return "Planter";
	case 113:
		return "Robot";
	case 114:
		return "Command";
	case 115:
		return "Ticket";
	case 116:
		return "Stats_Block";
	case 117:
		return "Field_Node";
	case 118:
		return "Ouija_Board";
	case 119:
		return "Architect_Machine";
	case 120:
		return "Starship";
	case 121:
		return "Spike";
	case 122:
		return "Gravity_Well";
	case 123:
		return "Autobreak_Blocks";
	case 124:
		return "Autobreak_Trees";
	case 125:
		return "Autobreak";
	case 126:
		return "TimedBlock";
	case 127:
		return "TimedPlatform";
	case 128:
		return "Mud_Puddle";
	case 129:
		return "Root_Cutting";
	case 130:
		return "Safe_Vault";
	default:
		return "";
	}
}
string join(const vector<string> v, const char delimeter) {
	string str;
	for (auto p = v.begin(); p != v.end(); ++p) {
		str += *p;
		if (p != (v.end() - 1))
			str += delimeter;
	}
	return str;
}

inline vector<string> explode(const string& delimiter, const string& str) {
	vector<string> arr;
	SIZE_T strleng = str.length(); // buvo const int strleng = str.length();
	SIZE_T delleng = delimiter.length(); // buvo const int delleng = delimiter.length();
	if (delleng == 0)
		return arr;
	SIZE_T i = 0; // buvo int i = 0;
	SIZE_T k = 0; // buvo int k = 0;
	while (i < strleng) {
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng) {
			arr.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else {
			i++;
		}
	}
	arr.push_back(str.substr(k, i - k));
	return arr;
}

BlockTypes get_blocktype(string c_, string name_) {
	if (c_ == "Foreground_Block") {
		return BlockTypes::FOREGROUND;
	}
	else if (c_ == "Background_Block" || c_ == "Back" || c_ == "Sheet_Music") {
		return BlockTypes::BACKGROUND;
	}
	else if (c_ == "Mannequin") {
		return BlockTypes::MANNEQUIN;
	}
	else if (c_ == "Spirit_Storage") {
		return BlockTypes::Spirit_Storage;
	}
	else if (c_ == "Geiger_Charger") {
		return BlockTypes::GEIGER_CHARGER;
	}
	else if (c_ == "Autobreak_Blocks" || c_ == "Autobreak_Trees" || c_ == "Autobreak") {
		return BlockTypes::AUTO_BLOCK;
	}
	else if (c_ == "Seed") {
		return BlockTypes::SEED;
	}
	else if (c_ == "Display_Shelf") {
		return BlockTypes::Display_Shelf;
	}
	else if (c_ == "Country_Flag") {
		return BlockTypes::COUNTRY_FLAG;
	}
	else if (c_ == "Painting_Easel") {
		return BlockTypes::Painting_Easel;
	}

	else if (c_ == "Fish_Mount") {
		return BlockTypes::Fish_Mount;
	}
	else if (c_ == "Portrait") {
		return BlockTypes::PORTRAIT;
	}
	else if (c_ == "Heart_Monitor") {
		return BlockTypes::Heart_Monitor;
	}
	else if (c_ == "Consummable") {
		return BlockTypes::CONSUMABLE;
	}
	else if (c_ == "Kranken") {
		return BlockTypes::KRANKEN;
	}
	else if (c_ == "Pain_Block") {
		return BlockTypes::PAIN_BLOCK;
	}
	else if (c_ == "Main_Door") {
		return BlockTypes::MAIN_DOOR;
	}
	else if (c_ == "Chal_Timer") {
		return BlockTypes::TIMER;
	}
	else if (c_ == "Bedrock") {
		return BlockTypes::BEDROCK;
	}
	else if (c_ == "ItemSucker") {
		return BlockTypes::SUCKER;
	}
	else if (c_ == "Door") {
		return BlockTypes::DOOR;
	}
	else if (c_ == "Fist") {
		return BlockTypes::FIST;
	}
	else if (c_ == "Sign") {
		return BlockTypes::SIGN;
	}
	else if (c_ == "Wrench") {
		return BlockTypes::WRENCH;
	}
	else if (c_ == "Checkpoint") {
		return BlockTypes::CHECKPOINT;
	}
	else if (c_ == "Lock") {
		return BlockTypes::LOCK;
	}
	else if (c_ == "Gateway") {
		return BlockTypes::GATEWAY;
	}
	else if (c_ == "Clothing") {
		return BlockTypes::CLOTHING;
	}
	else if (c_ == "Security_Camera") {
		return BlockTypes::CCTV;
	}
	else if (c_ == "Platform") {
		return BlockTypes::PLATFORM;
	}
	else if (c_ == "SFX_Foreground") {
		return BlockTypes::SFX_FOREGROUND;
	}
	else if (c_ == "Gems") {
		return BlockTypes::GEMS;
	}
	else if (c_ == "Toggleable_Foreground") {
		return BlockTypes::TOGGLE_FOREGROUND;
	}
	else if (c_ == "Chemical_Combiner") {
		return BlockTypes::CHEMICAL_COMBINER;
	}
	else if (c_ == "Treasure") {
		return BlockTypes::TREASURE;
	}
	else if (c_ == "Deadly_Block") {
		return BlockTypes::DEADLY;
	}
	else if (c_ == "Trampoline_Block") {
		return BlockTypes::TRAMPOLINE;
	}
	else if (c_ == "Animated_Foreground_Block") {
		return BlockTypes::ANIM_FOREGROUND;
	}
	else if (c_ == "Portal") {
		return BlockTypes::PORTAL;
	}
	else if (c_ == "Random_Block") {
		return BlockTypes::RANDOM_BLOCK;
	}
	else if (c_ == "Bouncy") {
		return BlockTypes::BOUNCY;
	}
	else if (c_ == "Chest") {
		return BlockTypes::CHEST;
	}
	else if (c_ == "Switch_Block") {
		return BlockTypes::SWITCH_BLOCK;
	}
	else if (c_ == "Magic_Egg") {
		return BlockTypes::MAGIC_EGG;
	}
	else if (c_ == "Crystal") {
		return BlockTypes::CRYSTAL;
	}
	else if (c_ == "Mailbox") {
		return BlockTypes::MAILBOX;
	}
	else if (c_ == "Bulletin_Board") {
		return BlockTypes::BULLETIN_BOARD;
	}
	else if (c_ == "Faction") {
		return BlockTypes::FACTION;
	}
	else if (c_ == "Component") {
		return BlockTypes::COMPONENT;
	}
	else if (c_ == "Weather_Machine") {
		return BlockTypes::WEATHER;
	}
	else if (c_ == "ItemSucker") {
		return BlockTypes::SUCKER;
	}
	else if (c_ == "Fish_Tank_Port") {
		return BlockTypes::FISH;
	}
	else if (c_ == "Steam_Block") {
		return BlockTypes::STEAM;
	}
	else if (c_ == "ground_Block") {
		return BlockTypes::GROUND_BLOCK;
	}
	else if (c_ == "Display") {
		return BlockTypes::DISPLAY;
	}
	else if (c_ == "Untrade_A_Box" || c_ == "Safe_Vault") {
		return BlockTypes::STORAGE;
	}
	else if (c_ == "Vending") {
		return BlockTypes::VENDING;
	}
	else if (c_ == "Blaster") {
		return BlockTypes::TRICKSTER;
	}
	else if (c_ == "Giving_Tree") {
		return BlockTypes::GIVING_TREE;
	}
	else if (c_ == "VIP") {
		return BlockTypes::VIP_ENTRANCE;
	}
	else if (c_ == "Donation_Box") {
		return BlockTypes::DONATION;
	}
	else if (c_ == "Phone_Booth") {
		return BlockTypes::PHONE;
	}
	else if (c_ == "Sewing_Machine") {
		return BlockTypes::SEWINGMACHINE;
	}
	else if (c_ == "Crime_Villain") {
		return BlockTypes::CRIME_VILLAIN;
	}
	else if (c_ == "Provider") {
		return BlockTypes::PROVIDER;
	}
	else if (c_ == "Adventure_Reset") {
		return BlockTypes::ADVENTURE;
	}
	else if (c_ == "Game_Block") {
		return BlockTypes::GAME_BLOCK;
	}
	else if (c_ == "Game_Generator") {
		return BlockTypes::GAME_GENERATOR;
	}
	else {
		return BlockTypes::UNKNOWN;
	}
}
char* text_(ENetPacket* packet) {
	char zero = 0;
	memcpy(packet->data + packet->dataLength - 1, &zero, 1);
	return (char*)(packet->data + 4);
}
inline int message_(ENetPacket* packet) {
	if (packet->dataLength > 3u) {
		return *(packet->data);
	}
	return 0;
}
inline void send_(ENetPeer* peer, int num, char* data, const int len) {
	const auto packet = enet_packet_create(nullptr, len + 5, ENET_PACKET_FLAG_RELIABLE);
	memcpy(packet->data, &num, 4);
	if (data != nullptr) {
		memcpy(packet->data + 2, data, len);
	}
	char zero = 0;
	memcpy(packet->data + 2 + len, &zero, 1);
	enet_peer_send(peer, 0, packet);
}
int init_enet(int port) {
	enet_initialize();
	ENetAddress address;
	enet_address_set_host(&address, server_ip.c_str());
	address.port = port;
	server = enet_host_create(&address, 1024, 1, 0, 0);
	server->checksum = enet_crc32;
	enet_host_compress_with_range_coder(server);
	return 0;
}

ClothTypes get_clothtype(string t_, BlockTypes a_) {
	if (a_ == BlockTypes::CLOTHING) {
		if (t_ == "Hat") {
			return ClothTypes::HAIR;
		}
		else if (t_ == "Shirt") {
			return ClothTypes::SHIRT;
		}
		else if (t_ == "Pants") {
			return ClothTypes::PANTS;
		}
		else if (t_ == "Feet") {
			return ClothTypes::FEET;
		}
		else if (t_ == "Face") {
			return ClothTypes::FACE;
		}
		else if (t_ == "Hand") {
			return ClothTypes::HAND;
		}
		else if (t_ == "Back") {
			return ClothTypes::BACK;
		}
		else if (t_ == "Hair") {
			return ClothTypes::HAIR;
		}
		else if (t_ == "Chest") {
			return ClothTypes::NECKLACE;
		}
		else if (t_ == "Ances") {
			return ClothTypes::ANCES;
		}
		else if (t_ == "Mask") {
			return ClothTypes::MASK;
		}
		else if (t_ == "Necklace") {
			return ClothTypes::NECKLACE;
		}
		else {
			return ClothTypes::NONE;
		}
	}
	else {
		return ClothTypes::NONE;
	}
}
inline uint32_t get_hash(unsigned char* str, const int len) {
	unsigned char* n = static_cast<unsigned char*>(str);
	uint32_t acc = 0x55555555;
	if (len == 0) {
		while (*n)
			acc = (acc >> 27) + (acc << 5) + *n++;
	}
	else {
		for (int i = 0; i < len; i++)
			acc = (acc >> 27) + (acc << 5) + *n++;
	}
	return acc;
}

int get_punch_id(const int id_) {
	switch (id_) {
	case 138: return 1;
	case 366:
	case 1464:
		return 2;
	case 472: return 3;
	case 594:
	case 10130:
	case 5424:
	case 5456:
	case 4136:
		return 4;
	case 768: return 5;
	case 900:
	case 7760:
	case 9272:
	case 7758:
		return 6;
	case 910: return 7;
	case 930:
	case 1010:
	case 6382:
		return 8;
	case 1016: return 9;
	case 1204:
	case 9534:
		return 10;
	case 1378: return 11;
	case 1440: return 12;
	case 1484:
	case 5160:
		return 13;
	case 1512:
	case 1648:
		return 14;
	case 1542: return 15;
	case 1576: return 16;
	case 1676:
	case 7504:
		return 17;
	case 1748:
	case 8006:
	case 8008:
	case 8010:
	case 8012:
		return 19;
	case 1710:
	case 4644:
	case 1714:
	case 1712:
	case 6044:
	case 1570:
		return 18;
	case 1780: return 20;
	case 1782:
	case 5156:
		return 21;
	case 1804:
	case 5194:
		return 22;
	case 1868:
	case 1998:
		return 23;
	case 1874: return 24;
	case 1946:
	case 2800:
		return 25;
	case 1952:
	case 2854:
		return 26;
	case 1956: return 27;
	case 1960: return 28;
	case 2908:
	case 6312:
	case 9496:
	case 8554:
	case 3162:
	case 9536:
	case 4956:
	case 3466:
	case 4166:
	case 4506:
	case 2952:
	case 9520:
	case 9522:
	case 8440:
	case 3932:
	case 3934:
	case 8732:
	case 3108:
		return 29;
	case 1980: return 30;
	case 2066:
	case 4150:
	case 11082:
	case 11080:
	case 11078:
		return 31;
	case 2212:
	case 5174:
		return 32;
	case 2218: return 33;
	case 2220: return 34;
	case 2266: return 35;
	case 2386: return 36;
	case 2388: return 37;
	case 2450:
		return 38;
	case 2476:
	case 4208:
	case 10336:
		return 39;
	case 4748: return 40;
	case 2512: return 41;
	case 2572: return 42;
	case 2592:
	case 9396:
	case 2596:
		return 43;
	case 2720: return 44;
	case 2752: return 45;
	case 2754: return 46;
	case 2756: return 47;
	case 2802: return 49;
	case 2866: return 50;
	case 2876: return 51;
	case 2878:
	case 2880:
		return 52;
	case 2906:
	case 4170:
		return 53;
	case 2886: return 54;
	case 2890: return 55;
	case 2910: return 56;
	case 3066: return 57;
	case 3124: return 58;
	case 3168: return 59;
	case 3214:
	case 9194:
		return 60;
	case 7408:
	case 3238:
		return 61;
	case 3274: return 62;
	case 3300: return 64;
	case 3418: return 65;
	case 3476: return 66;
	case 3596: return 67;
	case 3686: return 68;
	case 3716: return 69;
	case 4290: return 71;
	case 4474: return 72;
	case 4464:
	case 9500:
		return 73;
	case 4746: return 75;
	case 4778:
	case 6026: case 7784:
		return 76;
	case 4996:
	case 3680:
	case 5176:
		return 77;
	case 4840: return 78;
	case 5206: return 79;
	case 5480: return 80;
	case 6110: return 81;
	case 6308: return 82;
	case 6310: return 83;
	case 6298: return 84;
	case 6756: return 85;
	case 7044: return 86;
	case 6892: return 87;
	case 6966: return 88;
	case 7088:
	case 11020:
		return 89;
	case 7098:
	case 9032:
		return 90;
	case 7192: return 91;
	case 7136:
	case 9738:
		return 92;
	case 3166: return 93;
	case 7216: return 94;
	case 7196:
	case 9340:
		return 95;
	case 7392: return 96;
	case 7384: return 98;
	case 7414: return 99;
	case 7402: return 100;
	case 7424: return 101;
	case 7470: return 102;
	case 7488: return 103;
	case 7586:
	case 7646:
		return 104;
	case 7650: return 105;
	case 6804: return 106;
	case 7568:
	case 7570:
	case 7572:
	case 7574:
		return 107;
	case 7668: return 108;
	case 7660:
	case 9060:
		return 109;
	case 7736:
	case 9116:
	case 9118:
	case 7826:
	case 7828:
	case 11440:
	case 11442:
	case 11312:
	case 7830:
	case 7832:
	case 10670:
	case 9120:
	case 9122:
	case 10680:
	case 10626:
	case 10578:
	case 10334:
	case 11380:
	case 11326:
	case 7912:
	case 11298:
	case 10498:
		return 111;
	case 7836:
	case 7838:
	case 7840:
	case 7842:
		return 112;
	case 7950: return 113;
	case 8002: return 114;
	case 8022: return 116;
	case 8036: return 118;
	case 9348: return 119;
	case 8038: return 120;
	case 8372: return 121;
	case 8816:
	case 8818:
	case 8820:
	case 8822:
		return 128;
	case 8910: return 129;
	case 8942: return 130;
	case 8944:
	case 5276:
		return 131;
	case 8432:
	case 8434:
	case 8436:
	case 8950:
		return 132;
	case 8946: return 133;
	case 8960: return 134;
	case 9006: return 135;
	case 9058: return 136;
	case 9082:
	case 9304:
		return 137;
	case 9066:
		return 138;
	case 9136: return 139;
	case 9138:
		return 140;
	case 9172: return 141;
	case 9254: return 143;
	case 9256: return 144;
	case 9236: return 145;
	case 9342: return 146;
	case 9378: return 148;
	case 9376: return 149;
	case 9410: return 150;
	case 9462: return 151;
	case 9606:
		return 152;
	case 9716:
	case 5192:
		return 153;
	case 10064: return 168;
	case 10046: return 169;
	case 10050: return 170;
	case 10128: return 171;
	case 10210: return 172;
	case 10330: return 178;
	case 10398: return 179;
	case 10388:
	case 9524:
		return 180;
	case 10442: return 184;
	case 10506: return 185;
	case 10652: return 188;
	case 10676: return 191;
	case 10694: return 193;
	case 10714: return 194;
	case 10724: return 195;
	case 10722: return 196;
	case 10754: return 197;
	case 10888: return 199;
	case 10886:
	case 11308:
		return 200;
	case 10890: return 202;
	case 10922: return 203;
	case 10990: return 205;
	case 10998: return 206;
	case 10952: return 207;
	case 11000: return 208;
	case 11006: return 209;
	case 11046: return 210;
	case 11052: return 211;
	case 10960: return 212;
	case 10956: return 213;
	case 10958: return 214;
	case 10954: return 215;
	case 11076: return 216;
	case 11084: return 217;
	case 11118: return 218;
	case 11120: return 219;
	case 11116: return 220;
	case 11158: return 221;
	case 11162: return 222;
	case 11142: return 223;
	case 11232: return 224;
	case 11140: return 225;
	case 11248: return 226;
	case 11240: return 227;
	case 11250: return 228;
	case 11284: return 229;
	case 11292: return 231;
	case 11314: return 233;
	case 11316: return 234;
	case 11324: return 235;
	case 11354: return 236;
	case 11760:
	case 11464:
	case 11438:
	case 11716:
	case 11718:
	case 11674:
	case 11630:
	case 11786:
	case 11872:
		return 237;
	case 11814:
		return 241;
	case 11548:
	case 11552:
		return 242;
	case 11506:
	case 11508:
	case 11562:
	case 11704:
	case 11706:
	case 11768:
	case 11882:
		return 245;
	case 11818:
	case 11876:
		return 248;

	}
	return 0;
}
string to_lower(string s) {
	for (char& c : s)
		c = tolower(c);
	return s;
}
string to_upper(string s) {
	for (char& c : s)
		c = toupper(c);
	return s;
}
string replace_str(string& str, const string& from, const string& to) {
	while (str.find(from) != string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}

string getDate() {
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	int year = now->tm_year + 1900, month = now->tm_mon + 1, day = now->tm_mday, hour = now->tm_hour, minute = now->tm_min;

	char buffer[20];
	std::snprintf(buffer, sizeof(buffer), "[%02d/%02d/%04d %02d:%02d]", day, month, year, hour, minute);

	return std::string(buffer);
} //memleak risk: buffer vs.

int items_dat() {
	string n_ = "items.dat";
	ifstream file(n_, ios::binary | ios::ate);
	__int64 size = file.tellg(); // buvo int size = file.tellg();
	if (size == -1) return -1;
	item_data_size = (int)size;
	char* data = new char[size];
	file.seekg(0, ios::beg);
	file.read((char*)(data), size);
	item_data = new BYTE[60 + size];
	int MessageType = 0x4, PacketType = 0x10, NetID = -1, CharState = 0x8;
	memset(item_data, 0, 60);
	memcpy(item_data, &MessageType, 4);
	memcpy(item_data + 4, &PacketType, 4);
	memcpy(item_data + 8, &NetID, 4);
	memcpy(item_data + 16, &CharState, 4);
	memcpy(item_data + 56, &size, 4);
	file.seekg(0, std::ios::beg);
	file.read((char*)(item_data + 60), size);
	item_hash = get_hash((unsigned char*)data, (const int)size);
	int memPos = 0, itemCount;
	int16_t itemsdatVersion = 0;
	memcpy(&itemsdatVersion, data + memPos, 1);
	memPos += 2;
	memcpy(&itemCount, data + memPos, 4);
	const string key_ = "PBG892FXX982ABC*";
	memPos += 4;
	for (int i = 0; i < itemCount; i++) {
		ItemDB def;
		memcpy(&def.id, data + memPos, 4);
		memPos += 4;
		def.editableType = data[memPos];
		if (def.editableType == 3 || def.editableType == 31 || def.editableType == 1 || def.editableType == 21 || def.editableType == 23) {
			def.multiple_sides = 1;
		}
		memPos += 1;
		def.itemCategory = data[memPos];
		memPos += 1;
		def.actionType = data[memPos];
		if (def.id == 6016) {
			def.growscan = 1;
		}
		if (def.id == 10258 || def.id == 1436 || def.id == 8246) {
			def.security_camera = 1;
		}
		else if (def.actionType == 84) {
			def.vipentrance = 1;
		}
		else if (def.actionType == 49) {
			def.mannequin = 1;
		}
		else if (def.actionType == 85) {
			def.timer = 1;
		}
		else if (def.actionType == 54) {
			def.xeno = 1;
		}
		else if (def.actionType == 9) {
			def.entrance = 1;
		}
		else if (def.actionType == -122) {
			def.infinitymachine = 1;
		}
		else if (def.actionType == 82) {
			def.spirit = 1;
		}
		else if (def.actionType == 100) {
			def.charger = 1;
		}
		else if (def.actionType == 34) {
			def.bulletin_board = 1;
		}
		else if (def.actionType == 19) {
			def.magic_egg = 1;
		}
		else if (def.actionType == 51) {
			def.bunny_egg = 1;
		}
		else if (def.actionType == 47) {
			def.donation = 1;
		}
		else if (def.actionType == 97) {
			def.storage_box = 1;
		}
		else if (def.actionType == 46) {
			def.heart_monitor = 1;
		}
		else if (def.actionType == 38) {
			def.well_of_love = 1;
		}
		else if (def.actionType == 88) {
			def.portrait = 1;
		}
		else if (def.actionType == 76) {
			def.easel = 1;
		}
		else if (def.actionType == 33) {
			def.mailbox = 1;
		}
		else if (def.actionType == 83) {
			def.dshelf = 1;
		}
		else if (def.actionType == 63) {
			def.fish_port = 1;
		}
		else if (def.actionType == 59) {
			def.spotlight = 1;
		}
		else if (def.actionType == 87) {
			def.vall_mount = 1;
		}
		else if (def.actionType == 55) {
			def.trans = 1;
		}
		else if (def.actionType == 93) {
			def.trickster = 1;
		}
		else if (def.actionType == 12 or def.actionType == 45 or def.actionType == 32 or def.actionType == 31 or def.actionType == 122) {
			if (def.actionType == 31) {
				def.can_be_changed_to_public = 1;
			}
			else if (def.actionType == 12) {
				def.can_be_changed_two_types = 1;
			}
			def.toggleable = 1;
		}
		else if (def.actionType == 124 or def.actionType == 123) {
			def.magplant = 1;
		}
		else if (def.actionType == 111) {
			def.item_sucker = 1;
		}
		else if (def.actionType == 125) {
			def.mag_multiple = 1;
		}
		memPos += 1;
		def.hitSoundType = data[memPos];
		memPos += 1;
		int16_t strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.name += data[memPos] ^ (key_[(j + def.id) % key_.length()]);
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.texture += data[memPos];
			memPos++;
		}
		memcpy(&def.textureHash, data + memPos, 4);
		memPos += 4;
		def.itemKind = memPos[data];
		memPos += 1;
		memcpy(&def.val1, data + memPos, 4);
		memPos += 4;
		def.textureX = data[memPos];
		memPos += 1;
		def.textureY = data[memPos];
		memPos += 1;
		def.spreadType = data[memPos];
		memPos += 1;
		def.isStripeyWallpaper = data[memPos];
		memPos += 1;
		def.collisionType = data[memPos];
		if (def.collisionType == 1) {
			def.solid = 1;
		}
		memPos += 1;
		def.breakHits = data[memPos];
		if (def.breakHits <= 0 or def.breakHits > 42 * 6)
			def.breakHits = 42 * 6;
		memPos += 1;
		memcpy(&def.dropChance, data + memPos, 4);
		memPos += 4;
		def.clothingType = data[memPos];
		memPos += 1;
		memcpy(&def.rarity, data + memPos, 2);
		memPos += 2;
		def.maxAmount = data[memPos];
		memPos += 1;
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.extraFile += data[memPos];
			memPos++;
		}
		memcpy(&def.extraFileHash, data + memPos, 4);
		memPos += 4;
		memcpy(&def.audioVolume, data + memPos, 4);
		memPos += 4;
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.petName += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.petPrefix += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.petSuffix += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.petAbility += data[memPos];
			memPos++;
		}
		def.seedBase = data[memPos];
		memPos += 1;
		def.seedOverlay = data[memPos];
		memPos += 1;
		def.treeBase = data[memPos];
		memPos += 1;
		def.treeLeaves = data[memPos];
		memPos += 1;
		memcpy(&def.seedColor, data + memPos, 4);
		memPos += 4;
		memcpy(&def.seedOverlayColor, data + memPos, 4);
		memPos += 4;
		memPos += 4;
		memcpy(&def.growTime, data + memPos, 4);
		memPos += 4;
		memcpy(&def.val2, data + memPos, 2);
		memPos += 2;
		memcpy(&def.isRayman, data + memPos, 2);
		memPos += 2;
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.extraOptions += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.texture2 += data[memPos];
			memPos++;
		}
		strLen = *(int16_t*)&data[memPos];
		memPos += 2;
		for (int j = 0; j < strLen; j++) {
			def.extraOptions2 += data[memPos];
			memPos++;
		}
		memPos += 80;
		if (itemsdatVersion >= 11) {
			strLen = *(int16_t*)&data[memPos];
			memPos += 2;
			for (int j = 0; j < strLen; j++) {
				def.punchOptions += data[memPos];
				memPos++;
			}
		}
		if (itemsdatVersion >= 12) memPos += 13;
		if (itemsdatVersion >= 13) memPos += 4;
		if (itemsdatVersion >= 14) memPos += 4;
		if (itemsdatVersion >= 15) {
			memPos += 25;
			int16_t strLen = *(int16_t*)&data[memPos];
			memPos += 2 + strLen;
		}
		if (i != def.id) return -1;
		string category = getItemCategory(def.actionType, def.name);
		if (def.actionType == 125 || def.actionType == 130 || def.actionType == 127 || def.actionType == 126 || def.actionType == 118 || def.actionType == 117 || def.actionType == 116 || def.actionType == 115 || def.actionType == 113 || def.actionType == 109 || def.actionType == 106 || def.actionType == 105 || def.actionType == 104 || def.actionType == 103 || def.actionType == 102 || def.actionType == 101 || def.actionType == 99 || def.actionType == 98 || def.actionType == 96 || def.actionType == 92 || def.actionType == 91 || def.actionType == 89 || def.actionType == 86 || def.actionType == 80 || def.actionType == 79 || def.actionType == 78 || def.actionType == 77 || def.actionType == 75 || def.actionType == 74 || def.actionType == 73 || def.actionType == 72 || def.actionType == 71 || def.actionType == 68 || def.actionType == 67 || def.actionType == 66 || def.actionType == 65 || def.actionType == 57 || def.actionType == 54 || def.actionType == 53 || def.actionType == 52 || def.actionType == 50 || def.actionType == 48 || def.actionType == -126 || def.actionType == 43 || def.actionType == 40) def.blocked_place = true;
		if (def.id == 10258) def.blocked_place = true;
		if (def.id == 3832 || def.id == 6016 || def.id == 1436 || def.id == 8246 || def.id == 10258 || def.id == 2646) def.blocked_place = false;
		string clothingType_ = "";
		if (def.actionType == 107) {
			category = "Clothing";
			clothingType_ = "Ances";
		}
		if (def.actionType == 20) {
			switch (def.clothingType) {
			case 0: clothingType_ = "Hair";
				break;
			case 1: clothingType_ = "Shirt";
				break;
			case 2: clothingType_ = "Pants";
				break;
			case 3: clothingType_ = "Feet";
				break;
			case 4: clothingType_ = "Face";
				break;
			case 5: clothingType_ = "Hand";
				break;
			case 6: clothingType_ = "Back";
				break;
			case 7: clothingType_ = "Mask";
				break;
			case 8: clothingType_ = "Necklace";
				break;
			case 9: clothingType_ = "Ances";
				break;
			default: break;
			}
		}
		if ((def.id % 2) == 1) category = "Seed";
		vector<string> prop_ = get_properties(def.actionType, def.itemCategory);
		string thisss = (prop_.empty() ? "0" : join(prop_, ','));
		vector<string> properties = explode(",", thisss);
		def.properties = Property_Zero;
		for (string& prop : properties) {
			if (prop == "NoSeed") {
				def.properties += Property_NoSeed;
			} if (prop == "Dropless") {
				def.properties += Property_Dropless;
			} if (prop == "Beta") {
				def.properties += Property_Beta;
			} if (prop == "Mod") {
				def.properties += Property_Mod;
			} if (prop == "Untradable") {
				def.properties += Property_Untradable;
				def.untradeable = 1;
				if (def.id == 278 || def.id == 11818 || def.id == 9524 || def.id == 9526 || def.id == 9520 || def.id == 9522 || def.id == 9492 || def.id == 9168 || def.id == 7962 || def.id == 5190 || def.id == 8428 || def.id == 5196 || def.id == 5194 || def.id == 11478 || def.id == 1442 || def.id == 11466 || def.id == 11288 || def.id == 11134 || def.id == 10396 || def.id == 11562 || def.id == 5156 || def.id == 5160 || def.id == 5172 || def.id == 5174 || def.id == 5176 || def.id == 5154 || def.id == 9532 || def.id == 9534 || def.id == 9540) def.untradeable = 0; // rift wings 
			} if (prop == "Wrenchable") {
				def.properties += Property_Wrenchable;
			} if (prop == "MultiFacing") {
				def.properties += Property_MultiFacing;
			} if (prop == "Permanent") {
				def.properties += Property_Permanent;
			} if (prop == "AutoPickup") {
				def.properties += Property_AutoPickup;
			} if (prop == "WorldLock") {
				def.properties += Property_WorldLock;
			} if (prop == "NoSelf") {
				def.properties += Property_NoSelf;
			} if (prop == "RandomGrow") {
				def.properties += Property_RandomGrow;
			} if (prop == "Public") {
				def.properties += Property_Public;
			} if (prop == "Foreground") {
				def.properties += Property_Foreground;
			} if (prop == "OnlyCombiner") {
				def.properties += Property_Chemical;
			}
		}
		if (def.id == 8430) def.untradeable = 1;
		def.blockType = get_blocktype(category, def.name);
		if (def.id == 11138) def.blockType = VIP_ENTRANCE;
		def.clothType = get_clothtype(clothingType_, def.blockType);
		def.effect = get_punch_id(def.id);
		if (def.actionType == 81) {
			def.blockType = WEATHER;
			def.ext_weather = true;
		}
		def.ori_name = def.name;
		items.push_back(def);
		if (items[def.id].properties & Property_RandomGrow) {
			if (def.name.find("Tangram Block") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Tangram Block Seed" : "Tangram Block");
			else if (def.name.find("Card Block") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Card Block Seed" : "Card Block");
			else if (def.name.find("Growsaber") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Growsaber Seed" : "Growsaber");
			else if (def.name.find("Surgical") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Surgical Tool Seed" : "Surgical Tool");
			else if (def.name.find("Super Shirt") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Super Shirt Seed" : "Super Shirt");
			else if (def.name.find("Muscle Shirt") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Muscle Shirt Seed" : "Muscle Shirt");
			else if (def.name.find("Heroic Tights") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Heroic Tights Seed" : "Heroic Tights");
			else if (def.name.find("Super Tights") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Super Tights Seed" : "Super Tights");
			else if (def.name.find("Heroic Boots") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Heroic Boots Seed" : "Heroic Boots");
			else if (def.name.find("Superhero Mask") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Superhero Mask Seed" : "Superhero Mask");
			else if (def.name.find("Crimefighter Mask") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Crimefighter Mask Seed" : "Crimefighter Mask");
			else if (def.name.find("Super Cape") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Super Cape Seed" : "Super Cape");
			else if (def.name.find("Superheroine Top") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Superheroine Top Seed" : "Superheroine Top");
			else if (def.name.find("Super Eye Mask") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Super Eye Seed" : "Super Eye");
			else if (def.name.find("Super Logo") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Super Logo Seed" : "Super Logo");
			else if (def.name.find("Superpower") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Superpower Seed" : "Superpower");
			else if (def.name.find("Villain Portrait") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Villain Portrait Seed" : "Villain Portrait");
			else if (def.name.find("Super Logo") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Super Logo Seed" : "Super Logo");
			else if (def.name.find("Fashionable Dress") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Fashionable Dress Seed" : "Fashionable Dress");
			else if (def.name.find("Stylin' Dress") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Stylin' Dress Seed" : "Stylin' Dress");
			else if (def.name.find("High Heels") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "High Heels Seed" : "High Heels");
			else if (def.name.find("Fashion Purse") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Fashion Purse Seed" : "Fashion Purse");
			else if (def.name.find("Number Block") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Number Block Seed" : "Number Block");
			else if (def.name.find("Number") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Number Seed" : "Number");
			else if (def.name.find("Paint Bucket") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Paint Bucket Seed" : "Paint Bucket");
			else if (def.name.find("Crayon") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Crayon Block Seed" : "Crayon Block");
			else if (def.name.find("Command") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Command Tool Seed" : "Command Tool");
			else if (def.name.find("Growmoji") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Growmoji Seed" : "Growmoji");
			else if (def.name.find("Guild Flag") != string::npos)
				items[def.id].name = (def.name.find("Seed") != string::npos ? "Guild Flag Seed" : "Guild Flag");
			else {
				int a_ = 0;
				int last_id = 0;
				while (items[def.id - a_].properties & Property_RandomGrow) {
					if (items[def.id - a_].blockType != BlockTypes::SEED) last_id = def.id - a_;
					a_++;
				}
				items[def.id].name = (def.name.find("Seed") != string::npos ? items[last_id + 1].name : items[last_id].name);
			}
		}


		//shop gems category
		if (i == 2480)  items[i].shop_price = 20000;

		if (items[i].shop_price != 0) shop_item.push_back(make_pair(items[i].shop_price, i));

		//shop dl category
		if (i == 898)  items[i].sho2_price = 1;
		if (i == 5022)  items[i].sho2_price = 5;
		if (i == 12600)  items[i].sho2_price = 7;
		if (i == 5480)  items[i].sho2_price = 25;
		if (i == 9902)  items[i].sho2_price = 75;
		if (i == 6948)  items[i].sho2_price = 100;
		if (i == 6946)  items[i].sho2_price = 200;
		if (i == 5638)  items[i].sho2_price = 750;
		if (items[i].sho2_price != 0) sho2_item.push_back(make_pair(items[i].sho2_price, i));

		//shop growtoken category
		if (i == 1488)  items[i].sho3_price = 5;
		if (i == 1492)  items[i].sho3_price = 50;
		if (i == 1804)  items[i].sho3_price = 100;
		if (i == 1204)  items[i].sho3_price = 150;
		if (i == 1438)  items[i].sho3_price = 200;
		if (items[i].sho3_price != 0) sho3_item.push_back(make_pair(items[i].sho3_price, i));


		if (i == 834 || i == 611 || i == 914 || i == 916 || i == 918 || i == 920 || i == 874)items[i].max_gems3 = 1;
		if (i == 202)items[i].max_gems3 = 5;
		if (i == 838 || i == 840 || i == 844 || i == 390 || i == 540 || i == 922 || i == 388 || i == 386)items[i].max_gems3 = 10;
		if (i == 204) items[i].max_gems3 = 20;
		if (i == 8534)items[i].max_gems3 = 25;
		if (i == 720 || i == 206 || i == 528 || i == 8500) items[i].max_gems3 = 50;
		if (i == 366 || i == 932 || i == 542 || i == 882)items[i].max_gems3 = 100;
		if (i == 242 || i == 710)items[i].max_gems3 = 200;
		if (i == 930 || i == 768 || i == 672 || i == 830 || i == 1008 || i == 8542)items[i].max_gems3 = 250;
		if (i == 1240)items[i].max_gems3 = 400;
		if (i == 362 || i == 692)items[i].max_gems3 = 500;
		if (i == 898) items[i].max_gems3 = 750;
		if (i == 946 || i == 934 || i == 984 || i == 276 || i == 274 || i == 408 || i == 10394)items[i].max_gems3 = 1000;
		if (i == 574 || i == 592 || i == 766 || i == 760 || i == 1012) items[i].max_gems3 = 2500;
		if (i == 1400 || i == 900)items[i].max_gems3 = 5000;
		if (i == 1796) items[i].max_gems3 = 20000;
		if (i == 7188) items[i].max_gems3 = 200000;
		if (i == 5138)items[i].max_gems3 = 10000;
		if (i == 5140)items[i].max_gems3 = 50000;
		if (i == 5142)items[i].max_gems3 = 100000;

		//grindable recipe
		if (i == 326) {
			items[i].grindable_count = 30;
			items[i].grindable_prize = 4586;
		}
		if (i == 4422 || i == 2564 || i == 2566 || i == 5372) {
			items[i].grindable_count = 20;
			items[i].grindable_prize = 4610;
		}
		if (i == 6956) {
			items[i].grindable_count = 1;
			items[i].grindable_prize = 6958;
		}
		if (i == 6972) {
			items[i].grindable_count = 5;
			items[i].grindable_prize = 6974;
		}
		if (i == 7002) {
			items[i].grindable_count = 12;
			items[i].grindable_prize = 7004;
		}
		if (i == 7050) {
			items[i].grindable_count = 20;
			items[i].grindable_prize = 7054;
		}
		if (i == 4668) {
			items[i].grindable_count = 50;
			items[i].grindable_prize = 4670;
		}
		if (i == 7012) {
			items[i].grindable_count = 1;
			items[i].grindable_prize = 7014;
		}
		if (i == 440) {
			items[i].grindable_count = 100;
			items[i].grindable_prize = 6314;
		}
		if (i == 880) {
			items[i].grindable_count = 50;
			items[i].grindable_prize = 4562;
		}
		if (i == 5348 || i == 5354 || i == 5352 || i == 5350) {
			items[i].grindable_count = 100;
			items[i].grindable_prize = 5416;
		}
		if (i == 4578) {
			items[i].grindable_count = 1;
			items[i].grindable_prize = 4580;
		}
		if (i == 7460) {
			items[i].grindable_count = 25;
			items[i].grindable_prize = 7462;
		}
		if (i == 192 || i == 1004) {
			items[i].grindable_count = 50;
			items[i].grindable_prize = 4564;
		}
		if (i == 4982) {
			items[i].grindable_count = 100;
			items[i].grindable_prize = 4984;
		}
		if (i == 4584) {
			items[i].grindable_count = 100;
			items[i].grindable_prize = 4570;
		}
		if (i == 712 || i == 960) {
			items[i].grindable_count = 1;
			items[i].grindable_prize = 4570;
		}
		if (i == 2734) {
			items[i].grindable_count = 50;
			items[i].grindable_prize = 4764;
		}
		if (i == 6988) {
			items[i].grindable_count = 10;
			items[i].grindable_prize = 6990;
		}
		if (i == 4566) {
			items[i].grindable_count = 100;
			items[i].grindable_prize = 4568;
		}
		if (i == 6998) {
			items[i].grindable_count = 2;
			items[i].grindable_prize = 7000;
		}
		if (i == 3404 || i == 3836) {
			items[i].grindable_count = 20;
			items[i].grindable_prize = 4572;
		}
		if (i == 3406) {
			items[i].grindable_count = 10;
			items[i].grindable_prize = 4572;
		}
		if (i == 954) {
			items[i].grindable_count = 100;
			items[i].grindable_prize = 4572;
		}
		if (i == 10268) {
			items[i].grindable_count = 3;
			items[i].grindable_prize = 10272;
		}

		//consumable recipe
		if (i == 2410) {
			items[i].consume_needed = 200;
			items[i].consume_prize = 2408;
		}
		if (i == 4490) {
			items[i].consume_needed = 200;
			items[i].consume_prize = 4455;
		}
		if (i == 2036) {
			items[i].consume_needed = 200;
			items[i].consume_prize = 2037;
		}
		if (i == 1152) {
			items[i].consume_needed = 10;
			items[i].consume_prize = 1150;
		}
		if (i == 1212) {
			items[i].consume_needed = 25;
			items[i].consume_prize = 1190;
		}
		if (i == 2034) {
			items[i].consume_needed = 200;
			items[i].consume_prize = 2035;
		}
		if (i == 1234) {
			items[i].consume_needed = 4;
			items[i].consume_prize = 1206;
		}
		if (i == 3110) {//vampire cape
			items[i].consume_needed = 25;
			items[i].consume_prize = 1166;
		}
		if (i == 2000) {//skeletal dragon
			items[i].consume_needed = 20;
			items[i].consume_prize = 1998;
		}
		if (i == 7590) {
			items[i].consume_needed = 100;
			items[i].consume_prize = 7592;
		}
		if (i == 11656) {
			items[i].consume_needed = 100;
			items[i].consume_prize = 11658;
		}
		if (i == 2290) {
			items[i].consume_needed = 100;
			items[i].consume_prize = 2282;
		}
		if (i == 3122) {
			items[i].consume_needed = 16;
			items[i].consume_prize = 3120;
		}
		if (i == 3762) {
			items[i].consume_needed = 100;
			items[i].consume_prize = 3744;
		}
		if (i == 8534) {
			items[i].consume_needed = 100;
			items[i].consume_prize = 8536;
		}
		if (i == 5256) {
			items[i].consume_needed = 100;
			items[i].consume_prize = 5224;
		}

		//growganoth
		/*
		if (i == 1950) items[i].consume_prize = 4152;
		if (i == 2722) items[i].consume_prize = 3114;
		if (i == 910) items[i].consume_prize = 1250;
		if (i == 11046) items[i].consume_prize = 11314;
		if (i == 94 || i == 604 || i == 2636 || i == 2908) items[i].consume_prize = 3108;
		if (i == 274 || i == 276) items[i].consume_prize = 1956;
		if (i == 6300) items[i].consume_prize = 7102;
		if (i == 10730) items[i].consume_prize = 11332;
		if (i == 10734) items[i].consume_prize = 11336;
		if (i == 10732) items[i].consume_prize = 11334;
		if (i == 6176) items[i].consume_prize = 9042;
		if (i == 3040) items[i].consume_prize = 3100;
		if (i == 6144) items[i].consume_prize = 7104;
		if (i == 7998) items[i].consume_prize = 9048;
		if (i == 1162) items[i].consume_prize = 3126;
		if (i == 9322) items[i].consume_prize = 10184;
		if (i == 7696) items[i].consume_prize = 10186;
		if (i == 1474) items[i].consume_prize = 1990;
		if (i == 1506) items[i].consume_prize = 1968;
		if (i == 2386) items[i].consume_prize = 4166;
		if (i == 9364) items[i].consume_prize = 10206;
		if (i == 10576) items[i].consume_prize = 11322;
		if (i == 4960) items[i].consume_prize = 5208;
		if (i == 6196) items[i].consume_prize = 9056;
		if (i == 4326) items[i].consume_prize = 7122;
		if (i == 2860 || i == 2268) items[i].consume_prize = 4172;
		if (i == 1114) items[i].consume_prize = 4156;
		if (i == 362) items[i].consume_prize = 1234;
		if (i == 4334) items[i].consume_prize = 5250;
		if (i == 1408) items[i].consume_prize = 5254;
		if (i == 4338) items[i].consume_prize = 5252;
		if (i == 3288) items[i].consume_prize = 4138;
		if (i == 3296) items[i].consume_prize = 4146;
		if (i == 3290) items[i].consume_prize = 4140;
		if (i == 3292) items[i].consume_prize = 4142;
		if (i == 3298) items[i].consume_prize = 4148;
		if (i == 3294) items[i].consume_prize = 4144;
		//Dragon bone
		if (i == 900 || i == 7754 || i == 7136 || i == 1576 || i == 7752 || i == 1378 || i == 7758 || i == 7760 || i == 7748) items[i].consume_prize = 2000;
		//...
		if (i == 1746) items[i].consume_prize = 1960;
		if (i == 5018) items[i].consume_prize = 5210;
		if (i == 1252) items[i].consume_prize = 1948;
		if (i == 1190) items[i].consume_prize = 1214;
		if (i == 2868) items[i].consume_prize = 7100;
		if (i == 1830) items[i].consume_prize = 1966;
		if (i == 916 || i == 918 || i == 920 || i == 922 || i == 924 || i == 2038 || i == 2206 || i == 4444) items[i].consume_prize = 1962;
		if (i == 3556) items[i].consume_prize = 4188;//same drop different item
		if (i == 762) items[i].consume_prize = 4190;
		if (i == 3818) items[i].consume_prize = 10192;
		if (i == 366) items[i].consume_prize = 4136;
		if (i == 9262) items[i].consume_prize = 10212;
		if (i == 1294) items[i].consume_prize = 5236;
		if (i == 1242) items[i].consume_prize = 5216;
		if (i == 1244) items[i].consume_prize = 5218;
		if (i == 1248) items[i].consume_prize = 5220;
		if (i == 1246) items[i].consume_prize = 5214;
		if (i == 3016) items[i].consume_prize = 4248;
		if (i == 5528) items[i].consume_prize = 4248;
		if (i == 3018) items[i].consume_prize = 4248;
		if (i == 5526) items[i].consume_prize = 4248;
		if (i == 242) items[i].consume_prize = 1212;
		if (i == 2972) items[i].consume_prize = 4182;
		if (i == 3014 || i == 3012 || i == 2914) items[i].consume_prize = 4246;
		if (i == 1460) items[i].consume_prize = 1970;
		if (i == 2392) items[i].consume_prize = 9114;
		if (i == 3218) items[i].consume_prize = 3098;
		if (i == 3020) items[i].consume_prize = 3098;
		if (i == 3792) items[i].consume_prize = 5244;
		if (i == 10634) items[i].consume_prize = 11318;
		if (i == 1198) items[i].consume_prize = 5256;
		if (i == 8468) items[i].consume_prize = 10232;
		if (i == 2984) items[i].consume_prize = 3118;
		if (i == 4360) items[i].consume_prize = 10194;
		if (i == 5754) items[i].consume_prize = 8530; //black devil
		if (i == 8428) items[i].consume_prize = 9488; //kitsune mask
		if (i == 10828 || i == 10830 || i == 10832 || i == 6808 || i == 6810 || i == 6812 || i == 7218 || i == 7220 || i == 7222 || i == 10528 || i == 10530 || i == 10532 || i == 414 || i == 416 || i == 418 || i == 420 || i == 422 || i == 424 || i == 426 || i == 4634 || i == 4636 || i == 4638 || i == 4640 || i == 4642 || i == 5370 || i == 5726 || i == 5728 || i == 5730 || i == 6030 || i == 6032 || i == 6034) items[i].consume_prize = 4192;
		if (i == 5012 || i == 1018 || i == 592) items[i].consume_prize = 1178;
		if (i == 10406) items[i].consume_prize = 11316;
		if (i == 882) items[i].consume_prize = 1232;
		if (i == 1934) items[i].consume_prize = 3124;
		if (i == 10626) items[i].consume_prize = 11312;
		if (i == 6160) items[i].consume_prize = 9040;
		if (i == 3794) items[i].consume_prize = 10190;
		if (i == 8018) items[i].consume_prize = 9034;
		if (i == 2390) items[i].consume_prize = 3122;
		if (i == 5246) items[i].consume_prize = 9050;
		if (i == 6798) items[i].consume_prize = 7126;
		if (i == 9722 || i == 9724) items[i].consume_prize = 10200;
		if (i == 9388) items[i].consume_prize = 10234;
		if (i == 4732) items[i].consume_prize = 7124;
		if (i == 10804) items[i].consume_prize = 11320;
		if (i == 5000 || i == 5112 || i == 5654 || i == 6854 || i == 7644 || i == 10286 || i == 934 || i == 946 || i == 984 || i == 1364 || i == 1490 || i == 1750 || i == 2046 || i == 2248 || i == 2744 || i == 3252 || i == 3446 || i == 3534 || i == 3694 || i == 3832 || i == 4242 || i == 4486 || i == 4776 || i == 4892) items[i].consume_prize = 1210;

		if (i == 10328) {// dark king
			items[i].noob_item = { {10236,1},{4152, 1 }, { 3114, 1 }, { 1250, 1 }, { 11314, 1 }, { 3108, 1 }, { 1956, 1 }, { 11332, 1 }, { 11336, 1 }, { 11334, 1 }, { 9042, 1 }, {9048, 1 }, { 3126, 1 }, { 10186, 1 }, { 1990, 1 }, { 1968, 1 }, { 4166, 1 }, { 5208, 1 }, { 9056, 1 }, { 7122, 1 }, { 4172, 1 }, { 4156, 1 }, { 1234, 1 }, { 5250, 1 }, { 5254, 1 }, { 5252, 1 }, { 4138, 1 }, { 4146, 1 }, { 4140, 1 }, { 4142, 1 }, { 4148, 1 }, { 4144, 1 }, { 2000, 1 }, { 1960, 1 }, { 5210, 1 }, { 1948, 1 }, { 1214, 1 }, { 7100, 1 }, { 1966, 1 }, { 1962, 1 }, { 4188, 1 }, { 4186, 1 }, { 4190, 1 }, { 10192, 1 }, { 4136, 1 }, { 10212, 1 }, { 5236, 1 }, { 5216, 1 }, { 5218, 1 }, { 5220, 1 }, { 5214, 1 }, { 4248, 1 }, { 4182, 1 }, { 4246, 1 }, { 3098, 1 }, { 5244, 1 }, { 5256, 1 }, { 10232, 1 }, { 3118, 1 }, { 10194, 1 }, { 4192, 1 }, { 1178, 1 }, { 11316, 1 }, { 1232, 1 }, { 3124, 1 }, { 11312, 1 }, { 9040, 1 }, { 10190, 1 }, { 9034, 1 }, { 3122, 1 }, { 9050, 1 }, { 9054, 1 }, { 9052, 1 }, { 7126, 1 }, { 10200, 1 }, { 10234, 1 }, { 7124, 1 }, { 11320, 1 }, { 1210, 1 } };
			items[i].rare_item = { {9488, 1}, {1970, 1}, {9114, 1}, {11322 , 1}, {7104, 1},{10206, 1}, {11318, 1}, {10184 , 1}, {3100 , 1}, {7102 , 1} };
			items[i].newdropchance = 3500;
		}*/

		//supply crates
		if (i == 10836) items[i].noob_item = { { 8558, 5 }, { 4296, 1 }, { 1258, 5 }, { 1260, 5 }, { 1262, 5 }, { 1264, 5 }, { 1266, 5 }, { 1268, 5 }, { 1270, 5 }, { 4318, 5 }, { 4312, 5 }, { 4308, 5 }, { 4314, 5 }, { 4310, 5 }, { 4316, 5} };
		if (i == 10838) items[i].noob_item = { { 2914, 25}, { 3012, 15}, { 3014, 10}, { 3016, 5}, { 3018, 2}, { 3020, 1} };
		if (i == 10840) items[i].noob_item = { {10854 , 1}, { 10852 , 1}, { 10850 , 1}, { 10848 , 1}, { 10846 , 1}, { 10844, 1}, { 956 , 1}, {3468, 1}, { 4564, 1}, { 3836, 1}, { 676, 1}, { 874, 1}, { 4562, 1}, { 868, 1}, { 196, 1}, { 4580, 1}, { 4586, 1}, { 962, 1}, { 540, 1}, { 3428, 1}, { 3472, 1}, { 4588, 1}, { 4602,1} };
		if (i == 10834) items[i].noob_item = { {6520, 2}, {6538, 2}, {6522, 2}, {6528, 2}, {6540, 2}, {6518, 2}, {6530, 2}, {6524, 2}, {6536, 2}, {6534, 2}, {6532, 2}, {6526, 2} };
		if (i == 10842) items[i].noob_item = { {2382, 1}, { 2300, 1}, { 2298, 1}, { 2296, 1}, { 2294, 1}, { 2292, 1}, { 2316, 1}, { 2314, 1}, { 2312, 1}, { 2310, 1}, { 2308, 1}, { 2328, 1}, { 2326, 1}, { 2324, 1}, { 2322, 1}, { 2320, 1}, { 2332, 1}, { 2334, 1}, { 2336, 1}, { 2338, 1}, { 2340,1} };

		// growmoji chest
		if (i == 11156) items[i].randomitem = { 6278,6744,6824,6894,7370,7474,7656,7684,7932,8028 };
		if (i == 7628) items[i].randomitem = { 7764, 7592, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590, 7590 };

		//just consumables
		if (i == 1360) {
			items[i].noob_item = { { 3566,1},{ 12,1},{ 56,1},{ 16,1},{ 380,1},{ 1138,1},{ 20,1},{ 100,1},{ 378,1},{ 116,1},{ 370,1},{ 26,1},{ 22,1},{ 580,1},{ 194,1},{ 104,1},{ 190,1},{ 376,1},{ 1306,1},{ 696,1},{ 880,1},{ 166,1},{ 184,1},{ 1322,1},{ 164,1},{ 3578,1},{ 3782,1},{ 368,1},{ 24,1},{ 170,1},{ 372,1},{ 374,1},{ 52,1},{ 102,1},{ 178,1},{ 42,1},{ 68,1},{ 40,1},{ 28,1},{ 248,1},{ 176,1},{ 130,1},{ 270,1},{ 1324,1},{ 236,1},{ 142,1},{ 336,1},{ 694,1},{ 10034,1},{ 140,1},{ 76,1},{ 48,1},{ 188,1},{ 44,1},{ 34,1},{ 168,1},{ 54,1},{ 222,1},{ 174,1},{ 884,1},{ 118,1},{ 3572,1},{ 198,1},{ 548,1},{ 36,1},{ 680,1},{ 654,1},{ 122,1},{ 238,1},{ 106,1},{ 66,1},{ 38,1},{ 90,1},{ 208,1},{ 162,1},{ 30,1},{ 272,1},{ 670,1},{ 888,1},{ 144,1},{ 886,1},{ 192,1},{ 126,1},{ 1432,1},{ 2938,1},{ 172,1},{ 7630,1},{ 412,1},{ 3570,1},{ 3568,1},{ 2808,1},{ 354,1},{ 138,1},{ 9392,1},{ 214,1},{ 11202,1},{ 224,1},{ 342,1},{ 1846,1},{ 110,1},{ 108,1},{ 210,1},{ 234,1},{ 200,1},{ 58,1},{ 11202,1 } };
			items[i].newdropchance = 0;
		}
		if (i == 1680) {//sfw
			items[i].noob_item = { { 8616,1},{ 8618,1},{ 1676,1},{ 8590,1},{ 9732,1},{ 2868,1},{ 4822,1},{ 1668,1},{ 11046,1},{ 1678,1},{ 1664,1},{ 844,1},{ 2864,1},{ 3764,1},{ 6308,1},{ 6310,1},{ 6306,1},{ 6322,1},{ 1670,1},{ 4816,1},{ 4818,1},{ 2870,1},{ 2872,1},{ 2874,1},{ 2802,1},{ 1666,1},{ 4814,1 } };
			items[i].rare_item = { { 1674,1},{ 2854,1},{ 3696,1},{ 4820,1},{ 6312,1},{ 8588,1},{ 9730,1},{ 11008,1 } };
			items[i].newdropchance = 120;
		}
		if (i == 11036) {
			items[i].noob_item = { { 11024,1},{11022,1},{11032,3},{11034,3 } };
			items[i].rare_item = { { 11030,1},{ 10922,1},{ 11026,1},{ 11028,1 } };
			items[i].newdropchance = 40;
		}
		if (i == 10386) {
			items[i].noob_item = { { 11330,1},{1988,1},{1208,1},{11348,1 },{1992,1},{5256,1},{1222,1} ,{11342,1} ,{1198,1} ,{1982,1} ,{1200,1} ,{4160,1} ,{1220,1} ,{10198,1} ,{5240,1} ,{1202,1} ,{1238,1} ,{5238,1} ,{4162,1} ,{10316,1} ,{10196,1} ,{7116,1} ,{9044,1} ,{1168,1} ,{3116,1} ,{4164,1} ,{1172,1} ,{1230,1} ,{1192,1} ,{11340,1} ,{1194,1} ,{10202,1} ,{1226,1} ,{7108,1} ,{1196,1} ,{9046,1},{1980,1},{1972,1},{7110,1},{1182,1},{1994,1},{1184,1},{1186,1},{1188,1},{11330,1},{10204,1},{5222,1},{3102,1},{4154,1},{5232,1},{5224,1} };
			items[i].rare_item = { { 10326,1},{ 10322,1},{ 10324,1} };
			items[i].newdropchance = 350;
		}
		if (i == 11860) {
			items[i].noob_item = { { 11858,10},{ 11852,10},{ 11854,10},{ 11856,10},{ 11850,10},{11844,10},{11846,10},{11848,10},{11858,10},{ 11852,10},{ 11854,10},{ 11856,10},{ 11850,10},{11844,10},{11846,10},{11848,10},{11842,1},{11836,1},{11838,1},{11840,1},{11868,1},{11862,1},{11864,1},{11866,1 } };
			items[i].rare_item = { { 11826,1},{ 11820,1},{11822,1},{11824,1},{11834,1},{11828,1},{11830,1},{11832,1},{ 11818,1 } };
			items[i].newdropchance = 150;
		}
		if (i == 9680) {
			items[i].noob_item = { { 2738,1},{10906,1},{2730,1},{9670,1},{9662,2},{2760,1},{4772,1},{3624,1},{9666,1},{2752,1},{9664,4},{9650,1},{10912,1},{9652,1},{8514,1},{9654,1},{9668,8},{8570,8},{ 9658, 2} };
			items[i].newdropchance = 0;
		}
		if (i == 7346) {
			items[i].noob_item = { { 7362,5},{ 7364,5},{9126,5},{11374,5},{9128,5},{7358,5},{7354,5},{7360,5},{7352,5},{7356,5},{10256,5},{11376,5},{10282,5},{9134,5},{7348,5},{10268,5},{9130,5},{11370,5},{7342,5},{5294,5},{11354,5},{9132,5},{5298,5},{5288,5},{5292,5 } };
			items[i].newdropchance = 0;
		}
		if (i == 9286) {
			items[i].noob_item = { { 5768,1},{5766,1},{5744,1},{11628,1},{10664,1},{10596,1},{7698,1},{9282,1},{9280,1},{11656,1},{10592,1},{10590,1},{9290,1},{5758,1},{5756,1},{5760,1},{5762,1},{10598,1},{9284,1},{10582,1},{11632,1},{11634,1} };
			items[i].rare_item = { { 5754,1},{7696,1},{9272,1},{10576,1},{10578,1},{11622,1} };
			items[i].newdropchance = 50;
		}
		if (i == 5750) {
			items[i].noob_item = { { 202,1},{204,1},{206,1},{5766,1},{5768,1},{5744,1},{7688,1},{7690,1},{7694,1},{7686,1},{7692,1 } };
			items[i].rare_item = { { 9286,1},{9286,1},{9286,1},{4994,1},{ 2978,1},{ 5766,1},{ 5768,1},{5756,1},{5758,1},{5760,1},{5762,1},{5754,1},{7698,1},{7696,1},{9286,1},{9272,1},{9286,1},{9286,1},{9286,1 } };
			items[i].newdropchance = 1500;
		}
		if (i == 2306) {
			items[i].noob_item = { { 10560,1},{10558,1},{10546,1},{1408,1},{1410,1},{1412,1},{1414,1},{1416,1},{1418,1},{2280,1},{2290,1},{2288,1},{3274,1},{4372,1},{4378,1},{4370,1},{4366,1},{5504,1},{5508,1},{5512,1},{5490,1},{5514,1},{5496,1},{9242,1},{9244,1},{9246,1},{9248,1},{9258,1},{9260,1},{11584,1 } };
			items[i].rare_item = { { 7672,1},{10526,1 } };
			items[i].newdropchance = 40;
		}
		if (i == 7672) {
			items[i].noob_item = { { 7668,2},{7666,5},{7662,3},{11574,3},{11572,1},{7664,3},{10568,1},{1406,1 } };
			items[i].rare_item = { { 9256,1},{ 11544,1},{ 10492,1},{ 9262,1},{ 7660,1},{ 10494,1},{ 11534,1},{ 10534,1 } };
			items[i].newdropchance = 5;
		}
		if (i == 11476) { // Black Friday Black Box Xtreme
			items[i].noob_item = { { 10334,1},{ 10330,1},{ 10336,1},{10338,1},{ 10332,1},{ 11384,1},{ 11386,1},{ 11382,1},{ 11380,1},{ 11378,1 } };
			items[i].rare_item = { {10332,1} };
			items[i].newdropchance = 50;
		}
		if (i == 10396) {
			items[i].noob_item = { { 10340,1 }, { 10342,1 }, { 10344,1 }, { 10346,1 }, { 10348,1 }, { 10330,1 }, { 10332,1 }, { 10334,1 }, { 10336,1 }, { 10338,1 }, { 11380,1 }, { 11476,1 }, { 11378,1 }, { 11382,1 }, { 11394,1 }, { 11384,1 }, { 11386,1 }, { 11392,1 }, { 1388,1 } };
			items[i].rare_item = { {11476,1} };
			items[i].newdropchance = 50;
		}
		if (i == 5404) {
			items[i].noob_item = { {5398,1} , {5420,1}, {5436,1}, {5438,1}, {5540,1}, {5426,1}, {5444,1}, {7400,1} };
			items[i].rare_item = { {5424,1} , {5422,1}, {5456,1}, {7398,1}, {7414,1}, {7396,1}, {9194,1}, {9172,1} };
			items[i].newdropchance = 25;
		}
		if (i == 5402) {
			items[i].noob_item = { { 5394,1 }, { 9180,1 }, { 5474,1 }, { 5384,1 }, { 7458,1 }, { 1778,1 }, { 5348,1 }, { 5350,1 }, { 5352,1 }, { 5354,1 }, { 5476,1 }, { 228,1 }, { 5472,1 }, { 7454,1 }, { 9196,1 }, { 5364,1 }, { 5386,1 }, { 5358,1 }, { 5360,1 }, { 5362,1 }, { 7436,1 }, { 5400,1 }, { 5478,1 }, { 5370,1 }, { 5368,1 }, { 5396,1 }, { 5470,1 }, { 7438,1 }, { 3204,1 }, { 5372,1 }, { 7446,1 }, { 7448,1 } };
			items[i].rare_item = { {5404,1} };
			items[i].newdropchance = 120;
		}
		if (i == 11758) {
			items[i].noob_item = { {11756,3},{10778,1},{10782,1},{10774,1},{10784,1},{10780,1},{10776,1},{10786,1},{10758,1},{10754,1},{10394,1} };
			items[i].rare_item = { {10748,1}, {11884, 1}, {11768,1}, {11760,1}, {1674,1}, {8944,1}, {1970,1}, {11118,1}, {1460,1}, {9036,1}, {9758,1}, {10026,1}, {8284,1}, {10388,1}, {11318,1}, {10252,1}, {5754,1}, {9446,1}, {1458,1}, {4664,1}
			};
			items[i].newdropchance = 2500;
		}
		if (i == 11756) {
			items[i].noob_item = { {9522,5},{9526,1}, {10842,1},{10834,1}, {10840,1}, {10394, 1}, {10784,1},{10838,1},{10836,1},{10782,1}, {10786,1}, {10776,1}, {11782,2}, {11778,2},{11780,2} };
			items[i].rare_item = { {10778,1},{11758,1}, {10780, 1} };
			items[i].newdropchance = 1000;
		}
		if (i == 10536) {//Special Winter Wish
			items[i].noob_item = { {7414,1}, {5404, 1}, {11454, 1}, {9194, 1}, {5426, 1}, {11480, 1}, {7398, 1}, {10404, 1}, {5422, 1}, {7406, 1}, {5424, 1} };
			items[i].rare_item = { {11466,1},{10498,1}, {10412, 1}, {10410, 1}, {10424, 1}, {11478, 1} };
			items[i].newdropchance = 2150;
		}
		if (i == 9018) {//dark ticket
			items[i].noob_item = { {9026, 5}, {9028, 5}, {9024, 5}, {9030, 5}, {11346, 1} };
			items[i].rare_item = { {10210, 1}, {9058, 1}, {11328, 1}, {11344, 1}, {9036, 1}, {11324, 1}, {9032, 1}, {9038, 1}, {7098, 1} };
			items[i].newdropchance = 500;
		}
		if (i == 11398) {//Alien Landing POD
			items[i].noob_item = { {10990, 1}, {11000, 1}, {11410, 1}, {11426, 1}, {10996, 1}, {11408, 1}, {11448, 1}, {11450, 1}, {11452, 1}, {11412, 1}, {11414, 2}, {10998, 1}, {11422, 5}, {10994, 1} };
			items[i].rare_item = { {10952, 1}, {10954, 1}, {10956, 1}, {10958, 1}, {10960, 1}, {} };
			items[i].newdropchance = 500;
		}
		if (i == 8410) {//Mutant food
			items[i].noob_item = { {8332, 1}, {8798, 5}, {8814, 1}, {8348, 1}, {8346, 1}, {8350, 1}, {8804, 1}, {8806, 1}, {8808, 1}, {8340, 5}, {8342, 5}, {8800, 5}, {8802, 5}, {8368, 1},{8812, 1}, {8810, 1}, {8334, 5}, {8794, 1}, {8330, 1}, {8796, 5} };
			items[i].rare_item = { {8372, 1}, {8358, 1}, {8422, 1}, {8332, 1}, {8798, 5}, {8814, 1}, {8348, 1}, {8346, 1}, {8350, 1}, {8804, 1}, {8806, 1}, {8808, 1}, {8340, 5}, {8342, 5}, {8800, 5}, {8802, 5} };
			items[i].newdropchance = 3000;
		}

		if (i == 8408) {//Mutant food
			items[i].noob_item = { {8332, 1}, {8798, 5}, {8814, 1}, {8348, 1}, {8346, 1}, {8350, 1}, {8804, 1}, {8806, 1}, {8808, 1}, {8340, 5}, {8342, 5}, {8800, 5}, {8802, 5}, {8368, 1},{8812, 1}, {8810, 1}, {8334, 5}, {8794, 1}, {8330, 1}, {8796, 5} };
			items[i].rare_item = { {8372, 1}, {8358, 1}, {8422, 1}, {8332, 1}, {8798, 5}, {8814, 1}, {8348, 1}, {8346, 1}, {8350, 1}, {8804, 1}, {8806, 1}, {8808, 1}, {8340, 5}, {8342, 5}, {8800, 5}, {8802, 5} };
			items[i].newdropchance = 3000;
		}

		if (i == 8414) {//Mutant food
			items[i].noob_item = { {8332, 1}, {8798, 5}, {8814, 1}, {8348, 1}, {8346, 1}, {8350, 1}, {8804, 1}, {8806, 1}, {8808, 1}, {8340, 5}, {8342, 5}, {8800, 5}, {8802, 5}, {8368, 1},{8812, 1}, {8810, 1}, {8334, 5}, {8794, 1}, {8330, 1}, {8796, 5} };
			items[i].rare_item = { {8372, 1}, {8358, 1}, {8422, 1}, {8332, 1}, {8798, 5}, {8814, 1}, {8348, 1}, {8346, 1}, {8350, 1}, {8804, 1}, {8806, 1}, {8808, 1}, {8340, 5}, {8342, 5}, {8800, 5}, {8802, 5} };
			items[i].newdropchance = 3000;
		}

		if (i == 8412) {//Mutant food
			items[i].noob_item = { {8332, 1}, {8798, 5}, {8814, 1}, {8348, 1}, {8346, 1}, {8350, 1}, {8804, 1}, {8806, 1}, {8808, 1}, {8340, 5}, {8342, 5}, {8800, 5}, {8802, 5}, {8368, 1},{8812, 1}, {8810, 1}, {8334, 5}, {8794, 1}, {8330, 1}, {8796, 5} };
			items[i].rare_item = { {8372, 1}, {8358, 1}, {8422, 1}, {8332, 1}, {8798, 5}, {8814, 1}, {8348, 1}, {8346, 1}, {8350, 1}, {8804, 1}, {8806, 1}, {8808, 1}, {8340, 5}, {8342, 5}, {8800, 5}, {8802, 5} };
			items[i].newdropchance = 3000;
		}
		if (i == 7954) {//spring chest
			items[i].noob_item = { {7930, 1}, {7928, 1}, {7926, 1}, {7924, 1}, {7922, 1}, {7920, 1}, {7918, 1}, {7906, 1}, {7904, 1}, {7902, 1}, {7900, 1}, {7898, 1}, {7896, 1}, {7894, 1}, {7892, 1}, {7890, 1}, {7888, 3}, {7886, 1}, {7884, 1}, {7882, 1}, {7880, 1}, {7878, 1}, {7876, 1}, {7874, 1}, {7872, 1}, {7870, 1}, {7868, 1}, {7866, 1}, {7864, 1}, {7862, 1}, {7860, 1}, {7858, 1}, {7856, 1}, {7854, 1}, {7852, 1}, {7850, 1}, {7848, 1}, {7846, 1}, {7290, 5} };
			items[i].rare_item = { {7916, 1}, {7914, 1}, {7912, 1}, {7910, 1}, {7908, 1} };
			items[i].newdropchance = 500;
		}

		if (i == 7484) {//winter chest
			items[i].noob_item = { {7292, 1}, {7230, 5}, {7226, 5}, {7248, 1}, {7282, 1}, {7294, 1}, {7268, 1}, {7236, 5}, {7238, 5}, {7324, 5}, {7326, 5}, {7284, 5}, {7218, 5}, {7296, 1}, {7274, 5}, {7290, 5}, {7270, 5}, {7224, 5}, {7272, 5}, {7320, 5}, {7322, 5}, {7246, 1}, {7266, 1}, {7264, 1}, {7262, 1}, {7302, 1}, {7240, 5}, {7486, 5}, {7228, 5}, {7242, 5}, {7244, 5}, {7288, 5} };
			items[i].rare_item = { {7304, 1}, {7260, 1}, {7298, 1}, {7278, 1}, {7280, 1}, {7276, 1}, {7250, 1}, {7252, 1}, {7254, 1}, {7256, 1}, {7300, 1}, {7258, 1} };
			items[i].newdropchance = 500;
		}

		if (i == 5948) {//Gold guild chest
			items[i].noob_item = { {6216, 1}, {6218, 1}, {6220, 1}, {6222, 1}, {6224, 5}, {6282, 1}, {6188, 1}, {6190, 1}, {6192, 1}, {6158, 1}, {6160, 1}, {6168, 5}, {6178, 5}, {6180, 5}, {6182, 5}, {6184, 5}, {6186, 5} };
			items[i].rare_item = { {6008, 1}, {6196, 1}, {6284, 1}, {6006, 1}, {6004, 1}, {6224, 5},{6190, 1},{6190, 1},{6188, 1}, {6282, 1},{6222, 1},{6180, 5}, {6004, 1}, {6196, 1}, {6284, 1}, {6006, 1}, {6004, 1}, {6196, 1}, {6284, 1}, {6006, 1}, {6004, 1} };
			items[i].newdropchance = 5500;
		}




		if (i == 5090) items[i].hand_scythe_text = "`2It makes for a very tasty salad!``";
		if (i == 3088) items[i].hand_scythe_text = "`2How was there a gong in this tree!?``";
		if (i == 5198) items[i].hand_scythe_text = "`2It takes FOREVER to pick out the right grains of sand!``";
		if (i == 3086) items[i].hand_scythe_text = "`2These leaves would make a lovely crown.``";
		if (i == 3074) items[i].hand_scythe_text = "`2What's this huge leaf!?``";
		if (i == 5200) items[i].hand_scythe_text = "`2Are you feeling comfy ?``";
		if (i == 8910) items[i].hand_scythe_text = "`2Leaf Blower....``";
		if (i == 7034) items[i].hand_scythe_text = "`2What as an umbrella doing in a tree ?``";
		if (i == 11248) items[i].hand_scythe_text = "`2What's cooking? Marshmallow that's what!``";
		if (i == 10132) items[i].hand_scythe_text = "`2One with nature?``";



		if (i == 4774) items[i].event_name = "Jungle Blast";
		if (i == 1396) items[i].event_name = "What's that?";
		if (i == 942) items[i].event_name = "Desert Blast";
		if (i == 263) items[i].event_name = "Beautiful Crystal";
		if (i == 5002 || i == 5004 || i == 5006 || i == 5008) items[i].event_name = "Playful Sprite";
		if (i == 1056) items[i].event_name = "Songpyeon Event";
		if (i == 121) items[i].event_name = "Magical Seeds";
		if (i == 1636) items[i].event_name = "Awkward Friendly Unicorn";
		if (i == 2798) items[i].event_name = "Well, Well, Well";
		if (i == 2704) items[i].event_name = "Lost Gold";
		if (i == 3786) items[i].event_name = "That's Puzzling...";
		if (i == 528) items[i].event_name = "Luck of the Growish";
		if (i == 4522) items[i].event_name = "Lucky Kitty";

		if (i == 2034) items[i].event_total = 15;
		if (i == 611 || i == 3786) items[i].event_total = 20;
		if (i == 263 || i == 1396 || i == 4774 || i == 942 || i == 5002 || i == 1636 || i == 2704 || i == 4522)  items[i].event_total = 1;
		if (i == 1056 || i == 2798) items[i].event_total = 3;
		if (i == 121) items[i].event_total = 4;
		if (i == 528) items[i].event_total = 5;



		if (i == 6286 || i == 4516) items[i].box_size = 20;
		if (i == 6288) items[i].box_size = 40;
		if (i == 6290) items[i].box_size = 90;

		if (i == 3000) items[i].fish_max_lb = 15;
		if (i == 3026) items[i].fish_max_lb = 30;
		if (i == 3030 || i == 3458 || i == 5450) items[i].fish_max_lb = 50;
		if (i == 5542 || i == 5548) items[i].fish_max_lb = 60;
		if (i == 3038) items[i].fish_max_lb = 70;
		if (i == 3032) items[i].fish_max_lb = 90;
		if (i == 8606 || i == 3452) items[i].fish_max_lb = 100;
		if (i == 3034 || i == 5552 || i == 3222) items[i].fish_max_lb = 120;
		if (i == 3450 || i == 3224 || i == 3434 || i == 3436 || i == 3550 || i == 3620 || i == 3746 || i == 5100 || i == 10264 || i == 3440 || i == 3820 || i == 3438 || i == 3544) items[i].fish_max_lb = 150;
		if (i == 3036 || i == 3814 || i == 5538) items[i].fish_max_lb = 160;
		if (i == 3226) items[i].fish_max_lb = 180;
		if (i == 5580 || i == 5574) items[i].fish_max_lb = 190;
		if (i == 4958 || i == 3024 || i == 7744 || i == 3454 || i == 3460 || i == 3094 || i == 3092 || i == 3096 || i == 3220 || i == 5448) items[i].fish_max_lb = 200;
		if (i == 2914) items[i].randomitem = { 846,344,8964,3000,3000,3034, 3034,3038, 3038,3028,3012 };
		if (i == 3012) items[i].randomitem = { 3000,3000,3030, 3030,3038, 3038,3036, 3036,846,444,8966,344,3028,3022,3014,3000,3000,3030, 3030,3038, 3038,3036, 3036,846,444,8966,344,3028,3022,3014,11166 };
		if (i == 3014) items[i].randomitem = { 3030, 3030, 3026, 3026,3038, 3038, 3000,3000 , 3032, 3032 ,344 ,444 ,846 ,8966 ,8964 ,1520 ,1542 ,3016 ,10786 };
		if (i == 3016) items[i].randomitem = { 846,3026, 3026,3038, 3038,3032, 3032,3036, 3036,444,1522,8256,8964,3184,1542,3018,10786, 846,3026, 3026,3038, 3038,3032, 3032,3036, 3036,444,1522,8256,8964,3184,1542,3018,10786, 10566 };
		if (i == 3018) items[i].randomitem = { 846, 3036, 3036, 3034, 3034, 3032, 3032, 3024, 846, 3036, 3036, 3034, 3034, 3032, 3032, 3024, 4958, 1520, 8966, 344, 1522, 3022, 3810, 3448, 3008, 3184, 3020 };
		if (i == 3020) items[i].randomitem = { 1542,3022,1520,1522,3028,3038, 3038,3026, 3026,3030,3036, 3036, 3030,7744,3032, 3032,3000,3000,3034, 3034,4958,3024, 1542,3022,1520,1522,3028,3038, 3038,3026, 3026,3030,3036, 3036, 3030,7744,3032, 3032,3000,3000,3034, 3034,4958,3024, 3814 };
		if (i == 3098) items[i].randomitem = { 3096,3094,3092,1208,1238,1992,1200,1202,1198,3096,3094,3092,1208,1238,1992,1200,1202,1198,1220 };
		if (i == 3218) items[i].randomitem = { 3204,1360,3228,3222,3224,5450,5448,3220,3226,3020 };
		if (i == 4246) items[i].randomitem = { 3096,3094,1208,1992,1200,1198 };
		if (i == 4248) items[i].randomitem = { 3096,3094,3092,1208,1238,1992,1200,1202,1198,3096,3094,3092,1208,1238,1992,1200,1202,1198,1220 };
		if (i == 5526) items[i].randomitem = { 3584,8254,5542,5538,5620,5622,5612,5526,5580,3020,11734 };
		if (i == 5528) items[i].randomitem = { 3584,5574,8968,5552,5548,5618,5624,5602,5528,5614,8252,11052,5616,3020 };
		if (i == 11406) items[i].randomitem = { 11446, 11444, 11424, 11450, 11420, 11434, 11418, 11414, 11416, 11428, 11430 };
		if (i == 962 || i == 16 || i == 3472 || i == 954 || i == 880 || i == 188 || i == 190 || i == 22) {
			items[i].randomitem.push_back(882);
			items[i].chance = 1500;
		}
		else if (i == 866) {
			items[i].randomitem.push_back(870);
			items[i].chance = 5000;
		}
		else if (i == 872) {
			items[i].randomitem.push_back(876);
			items[i].chance = 5000;
		}
		else if (i == 440 || i == 1344) {
			items[i].randomitem.push_back(2800);
			items[i].chance = 5000;
		}
		else if (i == 166) {
			items[i].randomitem.push_back(1190);
			items[i].chance = 3000;
		}
		else if (i == 280) {
			items[i].randomitem.push_back(10068);
			items[i].chance = 2000;
		}
		else if (i == 326) {
			items[i].randomitem.push_back(878);
			items[i].chance = 5000;
		}
		else if (i == 1044) {
			items[i].randomitem.push_back(10070);
			items[i].chance = 5000;
		}
		else if (i == 1004) {
			items[i].randomitem.push_back(1104);
			items[i].chance = 100;
		}
		else if (i == 192) {
			items[i].randomitem.push_back(1004);
			items[i].chance = 100;
		}
		else if (items[i].blockType == BACKGROUND && items[i].rarity > 11) {
			items[i].randomitem.insert(items[i].randomitem.end(), { 2988 ,2990 });
			items[i].chance = 75;
		}
		else if (i == 3258 || i == 3262 || i == 3264 || i == 3266 || i == 3268 || i == 3270 || i == 3280 || i == 3282 || i == 3284 || i == 3286) {
			items[i].randomitem.push_back(3310);
			items[i].chance = 1000;
		}
		else if (i == 4762 || i == 262 || i == 826 || i == 5270 || i == 828 || i == 2812 || i == 3606 || i == 3424) {
			items[i].randomitem.push_back(5282);
			items[i].chance = 10;
		}
		else if (i == 3782) {
			items[i].randomitem.push_back(3784);
			items[i].chance = 25;
		}
		else if (i == 100) {
			items[i].randomitem.push_back(2792);
			items[i].chance = 25;
		}
		else if (i == 4702) {
			items[i].randomitem.push_back(4794);
			items[i].chance = 25;
		}
		else if (i == 324 || i == 322 || i == 786) {
			items[i].randomitem.push_back(1354);
			items[i].chance = 2000;
		}
		else if (i == 2708) {
			items[i].randomitem.push_back(2710);
			items[i].chance = 25;
		}
		else if (i == 2710) {
			items[i].randomitem.push_back(2712);
			items[i].chance = 25;
		}
		else if (i == 2712) {
			items[i].randomitem.push_back(2714);
			items[i].chance = 25;
		}
		else if (i == 2714) {
			items[i].randomitem.push_back(2716);
			items[i].chance = 25;
		}
		else if (i == 1520) {
			items[i].randomitem.push_back(3762);
			items[i].chance = 25;
		}
		else if (i == 616) {
			items[i].randomitem.push_back(618);
			items[i].chance = 5;
		}
	}
	delete[] data;
	ifstream file_info("informacija.txt");
	if (file_info.is_open()) {
		string line_info;
		while (getline(file_info, line_info)) {
			vector<string> d_ = explode("|", line_info);
			if (d_[1] == "Earth") items[atoi(d_[0].c_str())].chi = 0;
			else if (d_[1] == "Fire") items[atoi(d_[0].c_str())].chi = 1;
			else if (d_[1] == "Wind") items[atoi(d_[0].c_str())].chi = 2;
			else if (d_[1] == "Water") items[atoi(d_[0].c_str())].chi = 3;
			else items[atoi(d_[0].c_str())].chi = 4;
			items[atoi(d_[0].c_str())].description = d_[6];
			if (d_[2] != "" and d_[3] != "" and isdigit(d_[2][0]) and isdigit(d_[3][0])) {
				items[atoi(d_[0].c_str())].r_1 = atoi(d_[2].c_str()), items[atoi(d_[0].c_str())].r_2 = atoi(d_[3].c_str());
			}
			if (d_[4] != "") {
				items[atoi(d_[0].c_str())].on_equip = d_[4];
			}
			if (d_[5] != "") {
				items[atoi(d_[0].c_str())].on_remove = d_[5];
			}
			if (d_[8] != "" and isdigit(d_[8][0])) {
				items[atoi(d_[0].c_str())].max_gems = atoi(d_[8].c_str());
			}
			if (d_[10] != "") {
				items[atoi(d_[0].c_str())].playmod = d_[10];
			}
		}
		file_info.close();
		{
			ifstream file_info("en");
			if (file_info.is_open()) {
				string line_info;
				while (getline(file_info, line_info)) {
					transform(line_info.begin(), line_info.end(), line_info.begin(), ::toupper);
					swear_words.push_back(line_info);
				}
			}
			file_info.close();
			{
				ifstream file_info("farmables.txt");
				if (file_info.is_open()) {
					string line_info;
					while (getline(file_info, line_info)) {
						for (int i_ = 0; i_ < items.size(); i_++) {
							if (items[i_].name == line_info)
								items[i_].farmable = true;
						}
					}
				}
				file_info.close();
				{
					ifstream file_info("combiner.txt");
					if (file_info.is_open()) {
						string line_info;
						while (getline(file_info, line_info)) {
							vector<vector<int>> form_recipe;
							vector<string> ok = explode("|", line_info);
							for (string lalala : ok) {
								vector<string> beveik = explode(" ", lalala);
								string check_ = beveik[0];
								int count_ = 1;
								if (isdigit(check_[0])) {
									count_ = atoi(check_.c_str());
								}
								if (count_ != 1) {
									replace_str(lalala, check_ + " ", "");
								}
								if (lalala.find("pairs of ") != string::npos or lalala.find("pair of ") != string::npos)
									lalala = explode((lalala.find("pairs of ") != string::npos ? "pairs of " : "pair of "), lalala)[1];
								string ex = lalala;
								ex.erase(ex.size() - 1);
								for (int i_ = 0; i_ < items.size(); i_++) {
									if (items[i_].name == lalala or items[i_].name == ex) {
										form_recipe.push_back({ items[i_].id, count_ });
										break;
									}
								}
							}
							if (form_recipe.size() == 4) receptai.push_back(form_recipe);
						}
					}
					file_info.close();
					{
						ifstream file_info("kainos.txt");
						if (file_info.is_open()) {
							string line_info;
							while (getline(file_info, line_info)) {
								vector<string> ok = explode("|", line_info);
								kainos.push_back({ atoi(ok[0].c_str()), atoi(ok[1].c_str()) });
							}
						}
						file_info.close();
					}
				}
			}
		}
	}
	items[5000].blockType = WEATHER;
	items[3832].blockType = WEATHER;

	for (int i = 0; i < itemCount; i++) {
		if (items[i].blockType == BlockTypes::PLATFORM) items[i].collisionType = 0;
		if (i == 11560 || i == 11554 || i == 11556 || i == 11558 || i == 10956 || i == 10958 || i == 10954 || i == 10952 || i == 10960) items[i].flagmay = 1929312;
		if (i == 10426) items[i].flagmay = 1929156;
		if (i == 10412) items[i].flagmay = 1929;
		if (items[i].clothingType == 6 and i % 2 == 0 and i != 8430 and i != 9532) {
			rare_text += "\nadd_label_with_icon|small| " + items[i].name + "|left|" + to_string(i) + "|";
			items[9902].randomitem.push_back(i);
		}
		if (items[i].clothingType == 5 and i % 2 == 0) items[9384].randomitem.push_back(i);
		if (items[i].r_1 != 0 or items[i].r_2 != 0 and items[i].rarity > 1 and i != 1790) items[9380].randomitem.push_back(i);
		if (items[i].blockType == BlockTypes::LOCK and i != 5814 and i != 9640) {
			rainbow_text += "\nadd_label_with_icon|small| " + items[i].name + "|left|" + to_string(i) + "|";
			items[5136].randomitem.push_back(i);
		}
		items[i].newdropchance = 36 - items[i].rarity / 8;
		if (items[i].newdropchance <= 26)  items[i].newdropchance = 26;
		if (items[i].farmable) items[i].newdropchance += 3;
		if (i == 5078 || i == 5084 || i == 9212 || i == 5152 || i == 5170) items[i].chance = 5;
		if (i == 5126 || i == 5180 || i == 7174 || i == 5150 || i == 5168) items[i].chance = 6;
		if (i == 5128 || i == 5182 || i == 7172 || i == 5148 || i == 5166) items[i].chance = 7;
		if (i == 5130 || i == 5184 || i == 7170 || i == 5146 || i == 5164) items[i].chance = 8;
		if (i == 5132 || i == 5186 || i == 7168 || i == 5144 || i == 5162) items[i].chance = 9;
		if (i == 5134 || i == 5188 || i == 7166 || i == 5080 || i == 5082) items[i].chance = 10;
		if (i == 5804) items[i].emoji = "(oops)|ą|1&";
		if (i == 5806) items[i].emoji = "(sleep)|Ċ|1&";
		if (i == 5808) items[i].emoji = "(punch)|ċ|1&";
		if (i == 5810) items[i].emoji = "(bheart)|Ĕ|1&";
		if (i == 5812) items[i].emoji = "(cry)|ĝ|1&";
		if (i == 6822) items[i].emoji = "(party)|Ĩ|1&";
		if (i == 5770) items[i].emoji = "(wl)|ā|1&";
		if (i == 5772) items[i].emoji = "(grow)|Ė|1&";
		if (i == 5774) items[i].emoji = "(gems)|ė|1&";
		if (i == 5776) items[i].emoji = "(gtoken)|ę|1&";
		if (i == 5778) items[i].emoji = "(vend)|Ğ|1&";
		if (i == 6002) items[i].emoji = "(bunny)|ě|1&";
		if (i == 6052) items[i].emoji = "(cactus)|ğ|1&";
		if (i == 6272) items[i].emoji = "(peace)|ģ|1&";
		if (i == 6274) items[i].emoji = "(terror)|ġ|1&";
		if (i == 6276) items[i].emoji = "(troll)|Ġ|1&";
		if (i == 7232) items[i].emoji = "(halo)|Į|1&";
		if (i == 7234) items[i].emoji = "(nuke)|ĭ|1&";
		if (i == 6122) items[i].emoji = "(pine)|Ĥ|1&";
		if (i == 6672) items[i].emoji = "(football)|ĥ|1&";
		if (i == 6322) items[i].emoji = "(fireworks)|Ħ|1&";
		if (i == 7062) items[i].emoji = "(song)|ī|1&";
		if (i == 7130) items[i].emoji = "(ghost)|Ĭ|1&";
		if (i == 6278) items[i].emoji = "(evil)|Ģ|1&";
		if (i == 6824) items[i].emoji = "(pizza)|ĩ|1&";
		if (i == 6744) items[i].emoji = "(alien)|ħ|1&";
		if (i == 6894) items[i].emoji = "(clap)|Ī|1&";
		if (i == 7370) items[i].emoji = "(turkey)|į|1&";
		if (i == 7474) items[i].emoji = "(gift)|İ|1&";
		if (i == 7656) items[i].emoji = "(cake)|ı|1&";
		if (i == 7684) items[i].emoji = "(heartarrow)|Ĳ|1&";
		if (i == 7932) items[i].emoji = "(shamrock)|Ĵ|1&";
		if (i == 8028) items[i].emoji = "(grin)|ĵ|1&";
		if (i == 8416) items[i].emoji = "(ill)|Ķ|1&";
		if (i == 10114) items[i].emoji = "(eyes)|ķ|1&";
		if (i == 10116) items[i].emoji = "(weary)|ĸ|1&";
		if (items[i].rarity == 0 || items[i].rarity > 363)items[i].max_gems2 = 0;
		else if (items[i].r_1 == 0 or items[i].r_2 == 0) items[i].max_gems2 = 0;
		else items[i].max_gems2 = items[i].max_gems;
	}
	sort(shop_item.begin(), shop_item.end());
	for (int i = 0; i < shop_item.size(); i++) shop_list += "text_scaling_string|   100000 Gems   |\nadd_button_with_icon|shop_price_" + to_string(shop_item[i].second) + "|" + to_string(shop_item[i].first) + " Gems|noflags|" + to_string(shop_item[i].second) + "||\n";

	sort(sho2_item.begin(), sho2_item.end());
	for (int i = 0; i < sho2_item.size(); i++) sho2_list += "text_scaling_string|     200 DL     |\nadd_button_with_icon|sho2_price_" + to_string(sho2_item[i].second) + "|" + to_string(sho2_item[i].first) + " DL|noflags|" + to_string(sho2_item[i].second) + "||\n";

	sort(sho3_item.begin(), sho3_item.end());
	for (int i = 0; i < sho3_item.size(); i++) sho3_list += "text_scaling_string|     200 GT     |\nadd_button_with_icon|sho3_price_" + to_string(sho3_item[i].second) + "|" + to_string(sho3_item[i].first) + " GT|noflags|" + to_string(sho3_item[i].second) + "||\n";

	return 0;
}

string replace_str2(string str, const string& from, const string& to) {
	while (str.find(from) != string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}

bool special_char(const string& str_) {
	if (str_.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != string::npos)
		return true;
	return false;
}

bool email(const string& str) {
	if (str.size() > 64 or str.empty())
		return false;
	const string::const_iterator at = std::find(str.cbegin(), str.cend(), '@'), dot = std::find(at, str.cend(), '.');
	if ((at == str.cend()) or (dot == str.cend()))
		return false;
	if (std::distance(str.cbegin(), at) < 1 or std::distance(at, str.cend()) < 5)
		return false;
	return true;
}

uint32_t bgra(uint8_t b, uint8_t g, uint8_t r, uint8_t a) {

	return (static_cast<uint32_t>(a) << 24) |
		(static_cast<uint32_t>(r) << 16) |
		(static_cast<uint32_t>(g) << 8) |
		static_cast<uint32_t>(b);
}

bool CheckConfigS(const std::vector<std::string>& str, const std::string& data) {
	return std::find(str.begin(), str.end(), data) != str.end();
}

bool CheckConfigT(const std::vector<int>& inte, int data) {
	return std::find(inte.begin(), inte.end(), data) != inte.end();
}
/*
void LoadBot(int count) {
	ifstream bot("bot.txt");
	string line;
	int added;
	if (count > 250) count = 250;
	while (getline(bot, line)) {
		if (added >= count) break;
		bots.push_back(line);
		added++;
	}
}

string RefreshBot(int count) {
	if (count > 500) count = 500;
	return bots[rand() % count / 2];
}
*/
void LoadConfig() {
	string data = "";
	ifstream config("config.txt");
	if (config.fail()) cout << "config.txt not found" << endl, system("PAUSE");
	while (std::getline(config, data)) {
		auto it = data.find('|');
		if (it == std::string::npos || data.starts_with('#') || data.starts_with(' ')) continue;
		std::string conf = data.substr(0, it), value = data.substr(it + 1);
		if (conf == "server_ip") {
			server_ip = value;
		}
		if (conf == "server_port") {
			server_port = stoi(value);
		}
		if (conf == "server_name") {
			server_name = value;
		}
		if (conf == "cache_url") {
			cache_url = value;
		}
		if (conf == "cache_path") {
			cache_path = value;
		}
		if (conf == "discord_url") {
			discord_url = value;
		}
		if (conf == "add_whitelist") {
			whitelist.push_back(value);
		}
		if (conf == "add_clist") {
			clist.push_back(value);
		}
		if (conf == "add_glist") {
			glist.push_back(value);
		}
		if (conf == "add_owner") {
			server_owner.push_back(value);
		}
		if (conf == "whitelist") {
			isWhitelist = stoi(value);
		}
		if (conf == "beta") {
			isBeta = stoi(value);
		}
		//if (conf == "panic_mode") {
		//	panic_mode = stoi(value);
		//}

	}
}
int g_rand(int min, int max) {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	int sayi = dist(gen);
	return sayi;
}
vector<string> split_string_by_newline(const string& str)
{
	auto result = vector<string>{};
	auto ss = stringstream{ str };

	for (string line; getline(ss, line, '\n');)
		result.push_back(line);

	return result;
}

bool onlyDigit(string& text_) {
	for (char c : text_) if ((c < '0' || c>'9')) {
		return false;
	}
}
string admincolor(int level) {

	switch (level) {
	case -1: // vip
		return "`cVIP `0";
	case 0: // player
		return "`0";
	case 1: // moderator
		return "`#@";
	case 2: // admin
		return "`r@";
	case 3: // developer
		return "`6@";
	case 4: // manager
		return "`e@";
	case 5: // creator
		return "`4@";
	case 6: // founder
		return "`9@";
	case 7: // god
		return "`b@";
	default:
		return "`0";
	}
}

void space_(string& usrStr) {
	char cha1, cha2;
	for (int i = 0; i < usrStr.size() - 1; ++i) {
		cha1 = usrStr[i], cha2 = usrStr[i + 1];
		if ((cha1 == ' ') && (cha2 == ' ')) {
			usrStr.erase(usrStr.begin() + 1 + i);
			--i;
		}
	}
}

string join(const vector<string>& v, const string& delimiter) {
	string result;
	for (size_t i = 0; i < v.size(); ++i) {
		result += (i ? delimiter : "") + v[i];
	}
	return result;
}