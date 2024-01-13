#pragma once
#include <sstream>
struct GuildMember
{
	string member_name = "";
	uint8_t role_id = 0; // 3 -> Leader 2 -> Co-Leader 1 -> Elder 0 -> Member
	bool public_location = true;
	bool show_notifications = true;
	string display_name = "";
	long long last_online = 0;
};
struct GuildLog
{
	string info = "";
	uint16_t display_id = 0;
	long long date = 0;
};
struct Guild
{
	uint32_t guild_id = 0;
	uint16_t guild_level = 1;
	uint32_t guild_xp = 0;
	string guild_name = "";
	string guild_description = "";
	vector<GuildMember> guild_members{};
	vector<uint16_t> guild_mascot{ 0, 0 };
	uint8_t unlocked_mascot = 1;
	bool coleader_access = false;
	bool coleader_elder_access = false;
	bool all_access = false;
	string guild_world = "";
	vector<GuildLog> guild_logs{};
};
vector<vector<int>> guild_lvl{
	{405000, 100000}, // 1 >> 2
	{1215000, 125000}, // 2 >> 3
	{2430000, 150000}, // 3 >> 4
	{4050000, 200000}, // 4 >> 5
	{7290000, 250000}, // 5 >> 6
	{11430000, 300000}, // 6 >> 7
	{16200000, 350000}, // 7 >> 8
	{21870000, 400000}, // 8 >> 9
	{28350000, 500000}, // 9 >> 10
	{38700000, 600000}, // 10 >> 11
	{48600000, 700000}, // 11 >> 12
	{60547500, 800000}, // 12 >> 13
	{73710000, 900000}, // 13 >> 14
	{91125000, 1000000}, // 14 >> 15
	{100000000, 1500000} // 15 >> 15
};
vector<Guild> guilds{};
uint32_t guild_create_gem_requirement = 200000;
string comma(int sum) {
	stringstream ss;
	dotted::imbue(ss);
	ss << sum;
	return ss.str();
}
void save_guilds() {
	for (Guild to_save : guilds) {
		json save_, guild_members = json::array(), guild_logs = json::array();
		save_["guild_level"] = to_save.guild_level;
		save_["guild_xp"] = to_save.guild_xp;
		save_["guild_name"] = to_save.guild_name;
		save_["guild_description"] = to_save.guild_description;
		save_["unlocked_mascot"] = to_save.unlocked_mascot;
		save_["guild_mascot"] = to_save.guild_mascot;
		save_["coleader_access"] = to_save.coleader_access;
		save_["coleader_elder_access"] = to_save.coleader_elder_access;
		save_["all_access"] = to_save.all_access;
		save_["guild_world"] = to_save.guild_world;
		for (GuildMember guild_member : to_save.guild_members) {
			json save_member;
			save_member["member_name"] = guild_member.member_name;
			save_member["role_id"] = guild_member.role_id;
			save_member["public_location"] = guild_member.public_location;
			save_member["show_notifications"] = guild_member.show_notifications;
			save_member["last_online"] = guild_member.last_online;
			guild_members.push_back(save_member);
		}
		for (GuildLog guild_log : to_save.guild_logs) {
			json save_log;
			save_log["info"] = guild_log.info;
			save_log["display_id"] = guild_log.display_id;
			save_log["date"] = guild_log.date;
			guild_logs.push_back(save_log);
		}
		save_["guild_members"] = guild_members;
		save_["guild_logs"] = guild_logs;
		//cout << "saved guild " << to_save.guild_name << endl;
		ofstream w_("guilds/" + to_string(to_save.guild_id) + ".json");
		if (w_.fail()) continue;
		w_ << save_ << endl;
		w_.close();
	}
}
string get_mascot_dialog(const ENetPeer* peer, int fg, int bg, string s_ = "") {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id == 0) {
		return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Welcome to Grow Guilds where you can create a Guild! With a Guild you can compete in Guild Leaderboards to earn rewards and level up the Guild to add more members.|left|\nadd_spacer|small|\nadd_textbox|To create a Guild you must either be a  `2Supporter`` or `2Super Supporter``.|left|\nadd_textbox|The cost for `2Super Supporters`` is: `6" + comma(guild_create_gem_requirement / 2) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|You will be charged: `6" + comma((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement)) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|`8Caution``: A guild can only be created in a world owned by you and locked with a `5World Lock``!|left|\nadd_spacer|small|\nadd_button|showcreateguild|Create a Guild|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
	}
	uint32_t my_role = 0;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		for (GuildMember search_member : guild_information->guild_members) {
			if (search_member.member_name == pInfo(peer)->tankIDName) {
				my_role = search_member.role_id;
				break;
			}
		} if (my_role <= 2) {
			return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||";
		}
		string alalal = (not s_.empty() ? "\nadd_textbox|" + s_ + "|left|" : "");
		string guild_foreground = to_string(fg);
		string guild_background = to_string(bg);
		return "add_label|big|`wChange Guild Mascot``|left|\nadd_spacer|small|" + alalal + "\nadd_textbox|Create a unique Guild Mascot for your guild! Only `950,000 Gems! ``Choose items from your inventory to use as your Guild Mascot.|left|\nadd_spacer|small|\nadd_item_picker|select_bg_mascot|`wChoose Background Item``|Choose a Background for Guild Mascot|\nadd_item_picker|select_fg_mascot|`wChoose Foreground Item``|Choose a Foreground for Guild Mascot|\nadd_spacer|small|\nadd_dual_layer_icon_label|small|`wGuild Mascot Preview:``|left|" + guild_background + "|" + guild_foreground + "|3.0|1|\nadd_spacer|small|\nadd_button|confirm_mascot|Confirm Guild Mascot|\nend_dialog|make_mascotss|Cancel||";
	}
	return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||";
}

string get_guild_create(const ENetPeer* peer, const string& notification_ = "", const string& guild_name_ = "", const string& guild_description_ = "", const bool con_ = false) {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id != 0) return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|You're already in a guild!|left|\nend_dialog|guildalreadyjoined|Close||";
	uint32_t peer_gems = pInfo(peer)->gems;
	if ((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement) > peer_gems) {
		return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|You need `4" + to_string((pInfo(peer)->supp == 1 ? (guild_create_gem_requirement / 2) - peer_gems : guild_create_gem_requirement - peer_gems)) + " more Gems`` to be able to create the guild!|left|\nend_dialog|missingguildcreationgems|Close||";
	} if (con_) {
		return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|`1Guild Name: ``" + guild_name_ + "|left|\nadd_textbox|`1Guild Statement: ``" + guild_description_ + "|left|\nembed_data|guildname|" + guild_name_ + "\nembed_data|guilddesc|" + guild_description_ + "\nadd_spacer|small|\nadd_textbox|Cost: `4" + to_string((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement)) + " Gems``|left|\nadd_spacer|small|\nadd_button|confirmguild|Create Guild|noflags|0|0|\nend_dialog|confirmguild|Cancel||";
	}
	return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild Creation``|left|5814|" + (not notification_.empty() ? "\nadd_textbox|" + notification_ + "|left|" : "") + "\nadd_text_input|guildname|Guild Name:|" + guild_name_ + "|15|\nadd_text_input|guilddesc|Guild Statement:|" + guild_description_ + "|24|\nadd_spacer|small|\nadd_textbox|Confirm your guild settings by selecting `2Create Guild`` below to create your guild.|left|\nadd_textbox|`8Remember``: A guild can only be created in a world owned by you and locked with a `5World Lock``!|left|\nadd_spacer|small|\nadd_textbox|`4Warning!`` The guild name cannot be changed once you have confirmed the guild settings!|left|\nadd_spacer|small|\nadd_button|createguild|Create Guild|noflags|0|0|\nend_dialog|createguild|Close||";
}
bool guild_access(const ENetPeer* peer, const uint32_t guild_id) {
	if (guild_id == 0 or pInfo(peer)->guild_id == 0 or pInfo(peer)->guild_id != guild_id) return false;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		uint32_t my_rank = 0;
		for (GuildMember member_search : guild_information->guild_members) {
			if (member_search.member_name == pInfo(peer)->tankIDName) {
				my_rank = member_search.role_id;
				break;
			}
		}
		if (my_rank == 3) return false;
		if (guild_information->all_access) {
			return true;
		}
		else {
			if (guild_information->coleader_elder_access and my_rank >= 1 and my_rank != 3 or guild_information->coleader_access and my_rank == 2) {
				return true;
			}
		}
	}
	return false;
}
void create_guild_log(Guild* guild_information, string log_text, int log_display) {
	GuildLog new_log{};
	new_log.info = log_text;
	new_log.display_id = log_display;
	new_log.date = time(nullptr);
	guild_information->guild_logs.push_back(new_log);
	if (guild_information->guild_logs.size() > 10) {
		guild_information->guild_logs.erase(guild_information->guild_logs.begin());
	}
}

void leave_guild(ENetPeer* peer) {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id == 0) return;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		__int64 id_ = p - guilds.begin();
		Guild* guild_information = &guilds[p - guilds.begin()];
		for (GuildMember member_search : guild_information->guild_members) {
			if (member_search.member_name == pInfo(peer)->tankIDName) {
				if (member_search.role_id == 3) {
					if (guild_information->guild_members.size() != 1) return;
					break;
				}
			}
		}
		gamepacket_t p(0, pInfo(peer)->netID);
		p.Insert("OnGuildDataChanged");
		p.Insert(0), p.Insert(0), p.Insert(0), p.Insert(0);
		{
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert("`5[GUILD ALERT]`` You left the guild!");
			p.CreatePacket(peer);
		}
		/*
		gamepacket_t p2(0, pInfo(peer)->netID);
		p2.Insert("OnCountryState");
		p2.Insert(pInfo(peer)->country + "|showGuild");*/
		gamepacket_t p_leave;
		p_leave.Insert("OnConsoleMessage");
		p_leave.Insert("`5[GUILD ALERT]`` " + pInfo(peer)->tankIDName + " left the guild!");
		if (pInfo(peer)->world == guild_information->guild_world and guild_access(peer, guild_information->guild_id)) {
			gamepacket_t p3(0, pInfo(peer)->netID);
			{
				p3.Insert("OnNameChanged");
				if (pInfo(peer)->mod == 0 && pInfo(peer)->dev == 0) pInfo(peer)->name_color = "`0";
				p3.Insert((not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : (pInfo(peer)->d_name.empty() ? pInfo(peer)->name_color : "`0") + "" + (pInfo(peer)->d_name.empty() ? pInfo(peer)->tankIDName : pInfo(peer)->d_name)) + (pInfo(peer)->is_legend ? " of Legend" : "") + "``");
			}
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->world == pInfo(peer)->world) {
					p.CreatePacket(currentPeer);
					//p2.CreatePacket(currentPeer);
					p3.CreatePacket(currentPeer);
				} if (pInfo(currentPeer)->netID != pInfo(peer)->netID and pInfo(currentPeer)->guild_id == guild_id) {
					p_leave.CreatePacket(currentPeer);
				}
			}
		}
		else {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->world == pInfo(peer)->world) {
					p.CreatePacket(currentPeer);
					//p2.CreatePacket(currentPeer);
				} if (pInfo(currentPeer)->netID != pInfo(peer)->netID and pInfo(currentPeer)->guild_id == guild_id) {
					p_leave.CreatePacket(currentPeer);
				}
			}
		} pInfo(peer)->guild_id = 0;
		for (int i_ = 0; i_ < guild_information->guild_members.size(); i_++) {
			GuildMember* member_search = &guild_information->guild_members[i_];
			if (member_search->member_name == pInfo(peer)->tankIDName) {
				if (member_search->role_id == 3) {
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
						if (pInfo(currentPeer)->world == pInfo(peer)->world) {
							if (pInfo(currentPeer)->guild_id == guild_information->guild_id) {
								if (guild_access(currentPeer, guild_information->guild_id)) {
									gamepacket_t p3(0, pInfo(currentPeer)->netID);
									{
										p3.Insert("OnNameChanged");
										if (pInfo(currentPeer)->mod == 0 && pInfo(currentPeer)->dev == 0) pInfo(currentPeer)->name_color = "`0";
										p3.Insert((not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + (pInfo(currentPeer)->is_legend ? " of Legend" : "") + "``");
									} for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
										if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
										if (pInfo(currentPeer2)->world == pInfo(peer)->world) {
											p3.CreatePacket(currentPeer2);
										}
									}
								}
							}
						}
					}
					string path_ = "guilds/" + to_string(guild_information->guild_id) + ".json";
					if (_access_s(path_.c_str(), 0) == 0) {
						remove(path_.c_str());
					}
					guilds.erase(guilds.begin() + id_);
					break;
				}
				guild_information->guild_members.erase(guild_information->guild_members.begin() + i_);
				create_guild_log(guild_information, "`$" + pInfo(peer)->tankIDName + "`` `wleft the guild", 5948);
			}
		}

	}
}

string get_guild_statement_edit(const ENetPeer* peer, string s_ = "") {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id == 0) {
		return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Welcome to Grow Guilds where you can create a Guild! With a Guild you can compete in Guild Leaderboards to earn rewards and level up the Guild to add more members.|left|\nadd_spacer|small|\nadd_textbox|To create a Guild you must either be a  `2Supporter`` or `2Super Supporter``.|left|\nadd_textbox|The cost for `2Super Supporters`` is: `6" + comma(guild_create_gem_requirement / 2) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|You will be charged: `6" + comma((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement)) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|`8Caution``: A guild can only be created in a world owned by you and locked with a `5World Lock``!|left|\nadd_spacer|small|\nadd_button|showcreateguild|Create a Guild|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
	}
	uint32_t my_role = 0;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		for (GuildMember search_member : guild_information->guild_members) {
			if (search_member.member_name == pInfo(peer)->tankIDName) {
				my_role = search_member.role_id;
				break;
			}
		} if (my_role <= 2) {
			return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||";
		}
		string alalal = (not s_.empty() ? "\nadd_textbox|" + s_ + "|left|" : "");
		return "add_label_with_icon|big|`wEdit Guild Statement``|left|5814|" + alalal + "\nadd_text_input|guilddesc|Guild Statement:|" + guild_information->guild_description + "|24|\nadd_spacer|small|\nadd_button|changestatementsubmit|Confirm|noflags|0|0|\nend_dialog|guildpage|Close||";
	}
	return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||";
}
void send_guild_member_info(ENetPeer* peer, string member_name) {
	if (pInfo(peer)->guild_id == 0) return;
	uint32_t guild_id = pInfo(peer)->guild_id;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		uint32_t my_rank = 0;
		for (GuildMember member_search : guild_information->guild_members) {
			if (member_search.member_name == pInfo(peer)->tankIDName) {
				my_rank = member_search.role_id;
				break;
			}
		}
		for (int i_ = 0; i_ < guild_information->guild_members.size(); i_++) {
			GuildMember* member_search = &guild_information->guild_members[i_];
			if (member_search->member_name == member_name) {
				if (member_search->display_name == "") {
					member_search->display_name = "`o" + member_search->member_name;
					ifstream ifs("players/" + member_search->member_name + "_.json");
					if (ifs.is_open()) {
						json j;
						ifs >> j;
						if (j["adminLevel"] == -1) member_search->display_name = "`0[`cVIP`0]" + member_search->member_name;
						if (j["adminLevel"] == 1) member_search->display_name = "`0[`#SM`0]`##" + member_search->member_name;
						if (j["adminLevel"] == 2) member_search->display_name = "`0[`rSA`0]`r#" + member_search->member_name;
						if (j["adminLevel"] == 3) member_search->display_name = "`0[`6SD`0]`6#" + member_search->member_name;
						if (j["adminLevel"] == 4) member_search->display_name = "`0[`eSM`0]`e#" + member_search->member_name;
						if (j["adminLevel"] == 5) member_search->display_name = "`0[`4SC`0]`4#" + member_search->member_name;
						if (j["adminLevel"] == 6) member_search->display_name = "`0[`bSF`0]`b#" + member_search->member_name;
						if (j["adminLevel"] == 7) member_search->display_name = "`0[`9CODER`0]`9#" + member_search->member_name;

					}
				}
				string guild_foreground = (guild_information->guild_mascot[1] == 0 ? "5814" : to_string(guild_information->guild_mascot[1]));
				string guild_background = (guild_information->guild_mascot[0] == 0 ? "0" : to_string(guild_information->guild_mascot[0]));
				if (member_search->member_name == pInfo(peer)->tankIDName) {
					gamepacket_t p;
					p.Insert("OnDialogRequest");
					p.Insert("set_default_color|`o\nadd_dual_layer_icon_label|big|" + member_search->display_name + "``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nembed_data|guildmemberid|" + member_search->member_name + "\nembed_data|guildmembername|" + member_search->member_name + "\nadd_textbox|`oRank: " + (member_search->role_id == 3 ? "Leader" : member_search->role_id == 2 ? "Co-Leader" : member_search->role_id == 1 ? "Elder" : "Member") + "|left|\nadd_spacer|small|\nadd_textbox|`oThis is you. |left|\nadd_spacer|small|\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|guild_member_edit|||\nadd_quick_exit|");
					p.CreatePacket(peer);
					return;
				}
				string permissions_ = "";
				if (member_search->role_id != 3) {
					if (member_search->role_id == 1 and my_rank == 3) {
						permissions_ += "\nadd_button|promote|`wPromote to Co-Leader``|noflags|0|0|\nadd_smalltext|Promoting to Co-Leader will allow this player to:|left|\nadd_smalltext|`2Invite other players to join the guild.``|left|\nadd_smalltext|`2Kick players of rank Elder or lower from the guild.``|left|\nadd_smalltext|`2Promote players to rank Elder.``|left|\nadd_smalltext|`2Change the Guild Statement.``|left|\nadd_button|demote|`wDemote to Member``|noflags|0|0|\nadd_smalltext|Demoting to Member will remove the ability of this player to:|left|\nadd_smalltext|`4Invite other players to join the guild.``|left|\nadd_smalltext|`4Kick players from the guild.``|left|";
					}
					else if (member_search->role_id == 2 and my_rank == 3) {
						permissions_ += "\nadd_button|demote|`wDemote to Elder``|noflags|0|0|\nadd_smalltext|Demoting to Elder will remove the ability of this player to:|left|\nadd_smalltext|`4Kick players of rank Elder from the guild.``|left|\nadd_smalltext|`4Promote players to rank Elder.``|left|\nadd_smalltext|`4They will still be able to perform these functions on players of rank Member.``|left|\nadd_smalltext|`4Change the Guild Statement.``|left|";
					}
					else if (member_search->role_id != 3 and my_rank >= 2 and member_search->role_id != 2) {
						permissions_ += "\nadd_button|promote|`wPromote to Elder``|noflags|0|0|\nadd_smalltext|Promoting to Elder will allow this player to:|left|\nadd_smalltext|`2Invite other players to join the guild.``|left|\nadd_smalltext|`2Kick players of rank Member from the guild.``|left|";
					}
				}
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->invis) continue;
					if (pInfo(currentPeer)->tankIDName == member_search->member_name) {
						gamepacket_t p;
						p.Insert("OnDialogRequest");
						p.Insert("set_default_color|`o\nadd_dual_layer_icon_label|big|" + member_search->display_name + "``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nembed_data|guildmemberid|" + member_search->member_name + "\nembed_data|guildmembername|" + member_search->member_name + "\nadd_textbox|`oRank: " + (member_search->role_id == 3 ? "Leader" : member_search->role_id == 2 ? "Co-Leader" : member_search->role_id == 1 ? "Elder" : "Member") + "|left|\nadd_spacer|small|\nadd_textbox|`o" + member_search->member_name + " is `2online`` now in the world `5" + pInfo(currentPeer)->world + "``.|left|\nadd_spacer|small|\nadd_button|goto|Warp to `5" + pInfo(currentPeer)->world + "``|noflags|0|0|\nadd_button|msg|`5Send message``|noflags|0|0|" + permissions_ + (my_rank >= 1 and member_search->role_id < my_rank ? "\nadd_button|remove|`wKick from Guild``|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|guild_member_edit|||\nadd_quick_exit|");
						p.CreatePacket(peer);
						return;
					}
				}
				gamepacket_t p;
				p.Insert("OnDialogRequest");
				p.Insert("set_default_color|`o\nadd_dual_layer_icon_label|big|" + member_search->display_name + "``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nembed_data|guildmemberid|" + member_search->member_name + "\nembed_data|guildmembername|" + member_search->member_name + "\nadd_textbox|`oRank: " + (member_search->role_id == 3 ? "Leader" : member_search->role_id == 2 ? "Co-Leader" : member_search->role_id == 1 ? "Elder" : "Member") + "|left|\nadd_spacer|small|\nadd_textbox|`o" + member_search->member_name + " is `4offline``.|left|" + permissions_ + (my_rank >= 1 and member_search->role_id < my_rank ? "\nadd_button|remove|`wKick from Guild``|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|guild_member_edit|||\nadd_quick_exit|");
				p.CreatePacket(peer);
				break;
			}
		}
	}
}
string get_guild_info(const ENetPeer* peer, bool all_ = false) {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id == 0) {
		return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Welcome to Grow Guilds where you can create a Guild! With a Guild you can compete in Guild Leaderboards to earn rewards and level up the Guild to add more members.|left|\nadd_spacer|small|\nadd_textbox|To create a Guild you must either be a  `2Supporter`` or `2Super Supporter``.|left|\nadd_textbox|The cost for `2Super Supporters`` is: `6" + comma(guild_create_gem_requirement / 2) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|You will be charged: `6" + comma((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement)) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|`8Caution``: A guild can only be created in a world owned by you and locked with a `5World Lock``!|left|\nadd_spacer|small|\nadd_button|showcreateguild|Create a Guild|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
	}
	uint32_t my_role = 0;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		for (GuildMember search_member : guild_information->guild_members) {
			if (search_member.member_name == pInfo(peer)->tankIDName) {
				my_role = search_member.role_id;
				break;
			}
		}
		vector<string> online_guild_members{};
		vector<string> ok{};
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->invis or pInfo(currentPeer)->m_h) continue;
			for (GuildMember search_member : guild_information->guild_members) {
				if (search_member.member_name == pInfo(currentPeer)->tankIDName) {
					string display_color = (pInfo(currentPeer)->adminLevel == 7 ? "`0[`9CODER`0]`9#" : (pInfo(currentPeer)->adminLevel == 6) ? "`0[`bSF`0]`b#" : (pInfo(currentPeer)->adminLevel == 5) ? "`0[`4SC`0]`4#" : (pInfo(currentPeer)->adminLevel == 4) ? "`0[`eSM`0]`e#" : (pInfo(currentPeer)->adminLevel == 3) ? "`0[`6SD`0]`6#" : (pInfo(currentPeer)->adminLevel == 2) ? "`0[`rSA`0]`r#" : (pInfo(currentPeer)->adminLevel == 1) ? "`0[`#SM`0]`##" : (pInfo(currentPeer)->adminLevel == -1) ? "`0[`cVIP`0]" : "`0");
					ok.push_back(pInfo(currentPeer)->tankIDName);
					online_guild_members.push_back("\nadd_button|" + pInfo(currentPeer)->tankIDName + "|`2ONLINE: ``" + display_color + pInfo(currentPeer)->tankIDName + "``" + (search_member.role_id != 0 ? (search_member.role_id == 1 ? " `9(GE)``" : (search_member.role_id == 2 ? " `6(GC)``" : (search_member.role_id == 3 ? " `e(GL)``" : ""))) : "") + "|0|0|");
					break;
				}
			}
		} if (all_) {
			long long time_t = time(NULL);
			for (int i_ = 0; i_ < guild_information->guild_members.size(); i_++) {
				GuildMember* search_member = &guild_information->guild_members[i_];
				if (find(ok.begin(), ok.end(), search_member->member_name) == ok.end()) {
					if (search_member->display_name == "") {
						search_member->display_name = "`o" + search_member->member_name;
						ifstream ifs("players/" + search_member->member_name + "_.json");
						if (ifs.is_open()) {
							json j;
							ifs >> j;
							if (j["adminLevel"] == -1) search_member->display_name = "`0[`cVIP`0]" + search_member->member_name;
							if (j["adminLevel"] == 1) search_member->display_name = "`0[`#SM`0]`##" + search_member->member_name;
							if (j["adminLevel"] == 2) search_member->display_name = "`0[`rSA`0]`r#" + search_member->member_name;
							if (j["adminLevel"] == 3) search_member->display_name = "`0[`6SD`0]`6#" + search_member->member_name;
							if (j["adminLevel"] == 4) search_member->display_name = "`0[`eSM`0]`e#" + search_member->member_name;
							if (j["adminLevel"] == 5) search_member->display_name = "`0[`4SC`0]`4#" + search_member->member_name;
							if (j["adminLevel"] == 6) search_member->display_name = "`0[`bSF`0]`b#" + search_member->member_name;
							if (j["adminLevel"] == 7) search_member->display_name = "`0[`9CODER`0]`9#" + search_member->member_name;

						}
					}
					long long friend_last_online_ = time_t - search_member->last_online;
					online_guild_members.push_back("\nadd_button|" + search_member->member_name + "|`4OFFLINE:(" + (friend_last_online_ < 60 ? to_string(friend_last_online_) + "s" : (friend_last_online_ < 3600 ? to_string(friend_last_online_ / 60) + "m" : (friend_last_online_ < 86400 ? to_string(friend_last_online_ / 3600) + "h" : to_string(friend_last_online_ / 86400) + "d"))) + ") " + search_member->display_name + "``" + (search_member->role_id != 0 ? (search_member->role_id == 1 ? " `9(GE)``" : (search_member->role_id == 2 ? " `6(GC)``" : (search_member->role_id == 3 ? " `e(GL)``" : ""))) : "") + "``|0|0|");
				}
			}
		}
		string guild_foreground = (guild_information->guild_mascot[1] == 0 ? "5814" : to_string(guild_information->guild_mascot[1]));
		string guild_background = (guild_information->guild_mascot[0] == 0 ? "0" : to_string(guild_information->guild_mascot[0]));
		return "set_default_color|`o\nadd_dual_layer_icon_label|big|`wGuild Home``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nadd_textbox|`o" + guild_information->guild_name + "``|left|\nadd_textbox|`o" + guild_information->guild_description + "``|left|\nadd_textbox|`oGuild size: " + to_string(guild_information->guild_members.size()) + "/" + to_string(guild_information->guild_level * 5) + " members``|left|\nadd_spacer|small|\nadd_button|guild_logs|`wGuild Logs``|noflags|0|0|\nadd_spacer|small|" + (all_ ? "" : "\nadd_button|guild_members_all|`wShow offline too``|noflags|0|0|") + "\nadd_button|warphome|`wGo to Guild Home``|noflags|0|0|\nadd_button|guild_members_options|`wGuild Member Options``|noflags|0|0|" + (my_role >= 2 ? "\nadd_button|changestatement|`wEdit Guild Statement``|noflags|0|0|" : "") + (my_role != 3 ? "\nadd_button|leave_guild|`4Leave Guild``|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_spacer|small|\nadd_textbox|`5" + to_string(online_guild_members.size()) + " of " + to_string(guild_information->guild_members.size()) + "`` `wGuild Members Online``|left|" + (ok.size() == 1 ? "\nadd_textbox|`oNone of your guild friends are currently online.``|left|\nadd_spacer|small|" : "") + join(online_guild_members, "") + "\nadd_spacer|small|\nadd_button|back|`wBack``|noflags|0|0|\nadd_button||`wClose``|noflags|0|0|\nend_dialog|guildmembers|||\nadd_quick_exit|";
	}
	return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||";
}