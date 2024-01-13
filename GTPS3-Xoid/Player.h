#pragma once
struct Items {
	uint16_t id = 0, count = 0;
};
struct Friends {
	string name = "";
	bool mute = false, block_trade = false;
	long long last_seen = 0;
};
struct PlayMods {
	int id = 0;
	long long time = 0;
	string user = "";
};
struct Player {
	bool proxy = false;
	int tpy = 0;
	int tpx = 0;
	int pos2y = 0;
	int pos2x = 0;
	int pos1y = 0;
	int pos1x = 0;

	int total_profit = 0;
	int spin_amount = 0;
	string multiplayer_string = "";
	string last_game_unboxing = "";
	string lastround = "";
	string last_game_roulette = "";
	bool game_started1 = false;
	bool lostt = false;
	bool mineend = false;
	int coin_hit = 0;
	double multiplayer = 0.0;
	int gems_coinflip = 0;
	int minesleft = 0;
	int foundg = 0;
	int gems_mines = 0;
	int bM = 0;
	int gems_roulette = 0;
	bool game_started = false;
	bool game_started2 = false;

	vector<int> mines{};
	vector<int> clickm{};

	int bj_gems = 0;
	string kurpiyer = "";
	int kurpiyer_emoji = 0;
	bool bj_test = false;

	int total_masakart = 0;
	int total_playerkart = 0;



	int harvest_quest = 0;
	int fishing_quest = 0;

	int email_code = 0;
	string ip = "", lo = ""; //real ip 
	vector<string> last_visited_worlds{}, worlds_owned{};
	vector<map<int, int>> trade_items{};
	string name_color = "`0";
	int id = 0, netID = 0, state = 0, trading_with = -1;
	bool trade_accept = false, accept_the_offer = false;
	int x = -1, y = -1;
	int lastx = 0, lasty = 0, last_uptime = 0;
	int gems = 0;
	bool autofarm = false;
	int bpoi = 0;
	long long int asbk = 0;
	int farmable = 0;
	int confirm_pass = 0;
	bool onTrade = false;
	int lastray = 0, raybreak = 0, raylvl = 0;
	long long int xp = 0;
	bool teleport = false;
	int lastpx = 0, lastpy = 0, lastsel = 0, totalc = 0;
	bool enetshit = false;
	bool tracked = false;
	bool usedmegaphone = 0;
	bool inventory_sent = false;
	bool update = false;
	map<int, int> ac_{};
	int world_ms = 0;
	bool hit1 = false;
	int skin = 0x8295C3FF;
	int punched = 0;
	bool b_logs = false;
	int enter_game = 0;
	int lock = 0;
	int flagmay = 256;
	int lockeitem = 0;
	bool ghost = false, invis = false;
	int n = 0; //newbie passed save
	string note = "";
	int supp = 0, hs = 0;
	int mod = 0, dev = 0, m_h = 0;
	int wls = 0;
	int csn = -1;
	long long int b_t = 0, b_s = 0; // ban seconds
	//int last_infected = 0;
	string b_r = "", b_b = ""; // ban reason ir banned by
	string m_r = "", m_b = "";
	int hair = 0, shirt = 0, pants = 0, feet = 0, face = 0, hand = 0, back = 0, mask = 0, necklace = 0, ances = 0; /*clothes*/
	string tankIDName = "", tankIDPass = "", requestedName = "", world = "", email = "", country = "", home_world = "", last_wrenched = "";
	string d_name = "";
	vector<Items> inv{};
	vector<Friends> friends{};
	vector<int> last_friends_selection{};
	vector<string> pending_friends{};
	vector<string> bans{}, logs{};
	string last_edit = "";

	int i_11818_1 = 0, i_11818_2 = 0;
	int8_t random_fossil = rand() % 3 + 4;

	int opc = 0;
	int cc = 0;
	bool bb = false;
	int vip = 0, rb = 0;
	int gp = 0, gd = 0, glo = 0, mp = 0, lgnd = 0;
	int w_w = 0, w_d = 0;
	int mds = 0;
	int offergems = 0;
	int adminLevel = 0;
	int confirm_reset = 0;
	bool show_location_ = true, show_friend_notifications_ = true;
	int level = 1, firesputout = 0, carnivalgameswon = 0;
	long long playtime = 0;
	long long int account_created = 0, seconds = 0;
	int pickup_limits = 0;
	long long int pickup_time = 0, pickup_limit = 0, teleport_time = 0;
	string rid = "", mac = "", meta = "", vid = "", platformid = "", wk = "", aid = "", gid = "";
	map<string, int> achievements{};
	string lastmsg = "", lastmsgworld = "";
	int gtwl = 0;
	int c_x = 0, c_y = 0;
	bool isNew = false;
	int lavaeffect = 0;
	//event
	string personal_event = "", guild_event = "";
	long long last_personal_update = 0;
	int participated = 0;
	bool wls_participated = false;
	//valentine
	int booty_broken = 0;
	bool ghc = false;
	bool valentine = false;
	//winterfest
	int staged = 0;
	int s4tb = 0;
	//race time
	long long Race_Time = 0;
	bool OnRace = false;
	//clash event
	int clash_contri = 0;
	//cooldowns
	long long int i240 = 0, i756 = 0, i758 = 0;
	bool tmod = 0, unlockRoleSkin = false, titleDoctor = false, titleFisher = false, titleChef = false, titleStartopia = false;
	//billboard
	int b_i = 0, b_a = 0, b_w = 0, b_p = 0;
	int laststorebuycount = 0, laststorebuyid = 0, laststorebuyprice = 0;
	string last_item_search3 = "";
	//
	int same_input = 0, not_same = 0;
	string last_input_text = "";
	long long int last_inf = 0, last_text_input = 0, last_spam_detection = 0, last_consumable = 0, last_world_enter = 0, last_kickall = 0, last_fish_catch = 0, respawn_time = 0, hand_torch = 0, punch_time = 0, lava_time = 0, world_time = 0, geiger_time = 0, valentine_time = 0, remind_time = 0, warp_time = 0, name_time = 0, address_change = 0;
	int dds = 0;
	int hack_ = 0;
	bool cancel_enter = false;
	int lastwrenchx = 0, lastwrenchy = 0, lastwrenchb = 0, lastchoosenitem = 0, lastchoosennr = 0;
	bool invalid_data = false;
	int pps = 0;
	long long lpps = 0;
	long long int punch_count = 0;
	int received = 0;
	int geiger_ = 0;
	int fishing_used = 0, f_x = 0, f_y = 0, move_warning = 0, f_xy = 0, punch_warning = 0, fish_seconds = 0;
	vector<int> glo_p, lvl_p;
	int geiger_x = -1, geiger_y = -1;
	int t_xp = 0, bb_xp = 0, g_xp = 0, p_xp = 0, t_lvl = 0, bb_lvl = 0, g_lvl = 0, p_lvl = 0, ff_xp = 0, ff_lvl = 0, s_lvl = 0, s_xp = 0;
	vector<int> t_p, bb_p, p_p, g_p, ff_p, surg_p;
	bool saved_on_close = false;
	int dd = 0;
	bool AlreadyDailyQ = false;
	vector<PlayMods> playmods{};
	int b_l = 1;
	vector<pair<int, int>> bp;
	int choosenitem = 0;
	int promo = 0, flagset = 0;
	int radio = 0;
	int tk = 0;
	int b_ra = 0, b_lvl = 1;
	int magnetron_id = 0;
	int magnetron_x = 0;
	int magnetron_y = 0;
	vector<string> gr;
	long long int save_time = 0;
	vector<vector<long long>> completed_blarneys{
		{1, 0},
		{2, 0},
		{3, 0},
		{4, 0},
		{5, 0},
		{6, 0},
		{7, 0},
		{8, 0},
		{9, 0},
	};
	bool block_trade = false;
	int p_x = 0;
	int p_y = 0;
	int guild_id = 0;
	uint32_t pending_guild = 0;
	int choose_fg = 0, choose_bg = 0;
	bool is_legend = false;
	int pps2 = 0;
	long long lpps2 = 0;
	int pps23 = 0;
	long long lpps23 = 0;
	int superdev = 0;
	int roleIcon = 6;
	int roleSkin = 6;
	vector<int> available_surg_items;
	// Stats variables
	bool sounded = false;
	bool labworked = false;
	bool fixed = false;
	bool fixable = false;
	bool flu = false;
	int pulse = 40;
	int site = 0;
	int sleep = 0;
	int dirt = 0;
	int broken = 0;
	int shattered = 0;
	int incisions = 0;
	int bleeding = 0;
	int incneeded = 0;
	int heart = 0;
	double temp = 98.6;
	double fever = 0.0;
	string pretext = "";
	string fixtext = "";
	string postext = "";
	string scantext = "";
	string tooltext = "The patient is prepped for surgery.";
	string endtext = "";
	int failchance = 0;
	bool s = true;
	bool antibs = false;

	int spongUsed = 0;
	int scalpUsed = 0;
	int stitcUsed = 0;
	int antibUsed = 0;
	int antisUsed = 0;
	int ultraUsed = 0;
	int labkiUsed = 0;
	int anestUsed = 0;
	int defibUsed = 0;
	int splinUsed = 0;
	int pinsUsed = 0;
	int clampUsed = 0;
	int transUsed = 0;

	int surgery_skill = 0;
	int surgery_done = 0;
	int su_8552_1 = 0;
	int su_8552_2 = 0;
	bool surgery_started = false;
	int started_type = 0;
	string surgery_world = "";
	string surged_person = "";
	string surged_display = "";
	int surgery_type = -1;
	string surgery_name = "";
	bool hospital_bed = false;
	int egg = 0;

	bool mercy = false;
	bool drtitle = false;
	bool drt = false;
	bool lvl125 = false;
	bool donor = false;
	bool spotlight = false;
	bool master = false;
};
#define pInfo(peer) ((Player*)(peer->data))
struct PlayerMoving {
	int32_t netID, effect_flags_check;
	int packetType, characterState, plantingTree, punchX, punchY, secondnetID;
	float x, y, XSpeed, YSpeed;
};
struct FishMoving {
	int8_t packetType = 31, stopped_fishing;
	int32_t netID, x, y;
};

BYTE* packPlayerMoving(PlayerMoving* dataStruct, int size_ = 56) {
	BYTE* data = new BYTE[size_];
	memset(data, 0, size_);
	memcpy(data + 0, &dataStruct->packetType, 4);
	memcpy(data + 4, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 20, &dataStruct->plantingTree, 4);
	memcpy(data + 24, &dataStruct->x, 4);
	memcpy(data + 28, &dataStruct->y, 4);
	memcpy(data + 32, &dataStruct->XSpeed, 4);
	memcpy(data + 36, &dataStruct->YSpeed, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	return data;
}
BYTE* packFishMoving(FishMoving* dataStruct, int size_ = 56) {
	BYTE* data = new BYTE[size_];
	memset(data, 0, size_);
	memcpy(data + 0, &dataStruct->packetType, 4);
	memcpy(data + 3, &dataStruct->stopped_fishing, 4);
	memcpy(data + 4, &dataStruct->netID, 4);
	memcpy(data + 44, &dataStruct->x, 4);
	memcpy(data + 48, &dataStruct->y, 4);
	return data;
}
void send_raw(ENetPeer* peer, int a1, void* packetData, int packetDataSize, int packetFlag) {
	ENetPacket* p;
	if (peer) {
		if (a1 == 4 && *((BYTE*)packetData + 12) & 8) {
			p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
			int four = 4;
			memcpy(p->data, &four, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			memcpy((char*)p->data + packetDataSize + 4, 0, *((DWORD*)packetData + 13));
		}
		else {
			p = enet_packet_create(0, packetDataSize + 5, packetFlag);
			memcpy(p->data, &a1, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
		}
		enet_peer_send(peer, 0, p);
	}
}

void send_inventory(ENetPeer* peer) {
	if (pInfo(peer)->inventory_sent == false) pInfo(peer)->inventory_sent = true;
	__int16 inv_size = pInfo(peer)->inv.size(), packetLen = 66 + (inv_size * 4) + 4;
	BYTE* d_ = new BYTE[packetLen];
	memset(d_, 0, packetLen);
	*(__int8*)(d_) = 4;
	*(__int8*)(d_ + 4) = 9;
	*(__int8*)(d_ + 8) = -1;
	*(__int8*)(d_ + 16) = 8;
	*(int*)(d_ + 56) = 6 + (inv_size * 4) + 4;
	*(__int8*)(d_ + 60) = 1;
	*(int*)(d_ + 61) = inv_size;
	*(int*)(d_ + 65) = inv_size;
	vector<pair<uint16_t, uint8_t>> send_later;
	int offset = 67;
	for (__int16 i_ = 0; i_ < inv_size; ++i_) {
		if (pInfo(peer)->inv[i_].id == 7782 || pInfo(peer)->inv[i_].id == 9636 || pInfo(peer)->inv[i_].id == 9500 || pInfo(peer)->inv[i_].id == 9584 || pInfo(peer)->inv[i_].id == 9586 || pInfo(peer)->inv[i_].id == 9588 || pInfo(peer)->inv[i_].id == 9590 || pInfo(peer)->inv[i_].id == 9550 || pInfo(peer)->inv[i_].id == 9582 || pInfo(peer)->inv[i_].id == 9580 || pInfo(peer)->inv[i_].id == 9578 || pInfo(peer)->inv[i_].id == 9572 || pInfo(peer)->inv[i_].id == 9570 || pInfo(peer)->inv[i_].id == 9568 || pInfo(peer)->inv[i_].id == 9566 || pInfo(peer)->inv[i_].id == 9564 || pInfo(peer)->inv[i_].id == 9562 || pInfo(peer)->inv[i_].id == 9560 || pInfo(peer)->inv[i_].id == 9558 || pInfo(peer)->inv[i_].id == 9490 || pInfo(peer)->inv[i_].id == 9492 || pInfo(peer)->inv[i_].id == 9490 || pInfo(peer)->inv[i_].id == 9492 || pInfo(peer)->inv[i_].id == 9516 || pInfo(peer)->inv[i_].id == 9540) {
			send_later.push_back(make_pair(pInfo(peer)->inv[i_].id, pInfo(peer)->inv[i_].count));
		}
		else {
			*(__int16*)(d_ + offset) = pInfo(peer)->inv[i_].id; offset += 2;
			*(__int8*)(d_ + offset) = pInfo(peer)->inv[i_].count; offset += 2;
		}
	}
	ENetPacket* const p_ = enet_packet_create(d_, packetLen, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p_);
	delete[] d_;
	if (send_later.size() > 0) {
		PlayerMoving data_{};
		data_.packetType = 13;
		for (int i = 0; i < send_later.size(); i++) {
			data_.plantingTree = send_later[i].first;
			BYTE* raw = packPlayerMoving(&data_);
			raw[3] = send_later[i].second;
			send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
			delete[]raw;
		}
	}
}