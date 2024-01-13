
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include "enet/include/enet.h"
#include <nlohmann/json.hpp>
#include "Item.h"
#include "Base.h"
#include "Player.h"
#include "Packet.h"
#include "Guilds.h"
#include "World.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
#include "NewPacket.h"

#pragma comment(lib, "Ws2_32.lib")

vector<thread> threads;

BOOL WINAPI ConsoleHandler(DWORD dwType)
{
	switch (dwType) {
	case CTRL_LOGOFF_EVENT: case CTRL_SHUTDOWN_EVENT: case CTRL_CLOSE_EVENT:
	{
		/*ofstream write_new_timeon("event_timer.txt");
		write_new_timeon << event_timer;
		write_new_timeon.close();*/
		trigger_save_();
		return TRUE;
	}
	default:
	{
		break;
	}
	}
	return FALSE;
}

long long last_time = 0, lw_time = 0, last_guild_save = time(NULL) + 60, last_time_ = 0, last_time2_ = 0, last_hm_time = 0, last_fake_sb = 0;
long long autofarm_delay = 0;
void loop_cheat() {
	long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	/*last_update_clash = ms_time + 600000;
	string directory = "db/clash/solo/";
	for (const auto& entry : filesystem::directory_iterator(directory)) {
		int budget = 0;
		string filename = entry.path().filename().string();
		string username = filename.substr(0, filename.size() - 6);
		if (filename.substr(filename.size() - 6) == "_.json") {
			ifstream ifs(entry.path());
			if (ifs.is_open()) {
				json j;
				ifs >> j;
				budget = j["points"].get<int>();
				ifs.close();
			}
			string find = username;
			vector<pair<int, string>>::iterator lb = find_if(topclash.begin(), topclash.end(), [find](const pair <int, string>& element) { return element.second == find; });
			if (lb != topclash.end()) topclash[lb - topclash.begin()].first = budget;
			else topclash.push_back(make_pair(budget, find));
			update_clash_leaderboard();
			save_clash_leaderboard();
		}
	}*/
	try {
		if (autofarm_delay - ms_time <= 0) {
			autofarm_delay = ms_time + 300;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world.empty() or pInfo(currentPeer)->tankIDName.empty()) continue;
				if (pInfo(currentPeer)->autofarm == true) {
					int playerx = pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -1 : 1);
					int playery = pInfo(currentPeer)->y / 32 + (pInfo(currentPeer)->y / 32 < pInfo(currentPeer)->y / 32 ? -1 : 1);
					int location = playerx / 32 + (playery / 32 * 100);
					string name_ = pInfo(currentPeer)->world;
					vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
					if (pInfo(currentPeer)->autofarm == true) {
						edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -1 : 1), pInfo(currentPeer)->y / 32, 18);
						int block = pInfo(currentPeer)->farmable;
						int c_ = 0;
						modify_inventory(currentPeer, block, c_);
						if (p != worlds.end()) {
							World* world_ = &worlds[p - worlds.begin()];
							WorldBlock* block_ = &world_->blocks[location];
							if (block != 5640) {
								if (c_ <= 1) {
									pInfo(currentPeer)->autofarm = 0, pInfo(currentPeer)->farmable = 0;
									gamepacket_t ps;
									ps.Insert("OnConsoleMessage");
									ps.Insert("`4Autofarm Stopped! `oYou don't have enough block to farm!");
									ps.CreatePacket(currentPeer);
								}
								if (block_->fg == 0 && block_->bg == 0) {
									edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -1 : 1), pInfo(currentPeer)->y / 32, block);

									edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -1 : 1), pInfo(currentPeer)->y / 32, 18);
									//if (block_->fg + 1 == 0 && block_->bg + 1 == 0)
									if (pInfo(currentPeer)->hand == 5480 || pInfo(currentPeer)->hand == 9772 || pInfo(currentPeer)->hand == 9846 || pInfo(currentPeer)->hand == 10362 || pInfo(currentPeer)->hand == 9770) {
										if (c_ <= 3) {
											pInfo(currentPeer)->autofarm = 0, pInfo(currentPeer)->farmable = 0;
											gamepacket_t ps;
											ps.Insert("OnConsoleMessage");
											ps.Insert("`4Autofarm Stopped! `oYou don't have enough block to farm!");
											ps.CreatePacket(currentPeer);
										}
										edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -2 : 2), pInfo(currentPeer)->y / 32, block);
										edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -3 : 3), pInfo(currentPeer)->y / 32, block);

										edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -2 : 2), pInfo(currentPeer)->y / 32, 18);
										edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -3 : 3), pInfo(currentPeer)->y / 32, 18);
									}
									if (pInfo(currentPeer)->hand == 9846 || pInfo(currentPeer)->hand == 10362 || pInfo(currentPeer)->hand == 9770) {
										if (c_ <= 4) {
											pInfo(currentPeer)->autofarm = 0, pInfo(currentPeer)->farmable = 0;
											gamepacket_t ps;
											ps.Insert("OnConsoleMessage");
											ps.Insert("`4Autofarm Stopped! `oYou don't have enough block to farm!");
											ps.CreatePacket(currentPeer);
										}
										edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -4 : 4), pInfo(currentPeer)->y / 32, block);

										edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -4 : 4), pInfo(currentPeer)->y / 32, 18);
									}
								}
							}
							else {
								for (int i_ = 0; i_ < world_->machines.size(); i_++) {
									WorldMachines machine = world_->machines[i_];
									if (machine.x == pInfo(currentPeer)->magnetron_x and machine.y == pInfo(currentPeer)->magnetron_y and machine.id == 5638) {
										if (machine.enabled) {
											WorldBlock* itemas = &world_->blocks[machine.x + (machine.y * 100)];
											if (itemas->magnetron and itemas->id == pInfo(currentPeer)->magnetron_id) {
												if (itemas->pr > 1) {
													if (block_->fg == 0) {
														itemas->pr--;
														edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -1 : 1), pInfo(currentPeer)->y / 32, itemas->id, true);
														edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -1 : 1), pInfo(currentPeer)->y / 32, 18);

														if (pInfo(currentPeer)->hand == 5480 || pInfo(currentPeer)->hand == 9772 || pInfo(currentPeer)->hand == 9846 || pInfo(currentPeer)->hand == 10362 || pInfo(currentPeer)->hand == 9770) {
															if (itemas->pr <= 3) {
																pInfo(currentPeer)->autofarm = 0, pInfo(currentPeer)->farmable = 0;
																gamepacket_t ps;
																ps.Insert("OnConsoleMessage");
																ps.Insert("`4Autofarm Stopped! `oYou don't have enough block to farm!");
																ps.CreatePacket(currentPeer);
															}
															itemas->pr--;
															edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -2 : 2), pInfo(currentPeer)->y / 32, itemas->id, true);
															edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -3 : 3), pInfo(currentPeer)->y / 32, itemas->id, true);

															edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -2 : 2), pInfo(currentPeer)->y / 32, 18);
															edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -3 : 3), pInfo(currentPeer)->y / 32, 18);
														}
														if (pInfo(currentPeer)->hand == 9846 || pInfo(currentPeer)->hand == 10362 || pInfo(currentPeer)->hand == 9770) {
															if (itemas->pr <= 4) {
																pInfo(currentPeer)->autofarm = 0, pInfo(currentPeer)->farmable = 0;
																gamepacket_t ps;
																ps.Insert("OnConsoleMessage");
																ps.Insert("`4Autofarm Stopped! `oYou don't have enough block to farm!");
																ps.CreatePacket(currentPeer);
															}
															itemas->pr--;
															edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -4 : 4), pInfo(currentPeer)->y / 32, itemas->id, true);
															edit_tile(currentPeer, pInfo(currentPeer)->x / 32 + (pInfo(currentPeer)->state == 16 ? -4 : 4), pInfo(currentPeer)->y / 32, 18);
														}
														if (itemas->pr <= 0) {
															PlayerMoving data_{};
															data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
															BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
															BYTE* blc = raw + 56;
															form_visual(blc, *itemas, *world_, NULL, false);
															for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																if (pInfo(currentPeer)->world == world_->name) {
																	send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																}
															}
															delete[] raw, blc;
														}
														break;

													}

												}
												else {
													pInfo(currentPeer)->autofarm = 0, pInfo(currentPeer)->farmable = 0;
													gamepacket_t ps;
													ps.Insert("OnConsoleMessage");
													ps.Insert("`4Autofarm Stopped! `oYou don't have enough block to farm!");
													ps.CreatePacket(currentPeer);
												}
											}
										}
									}
								}
							}
						}
					}
				}
				else {
					continue;
				}
			}
		}
	}
	catch (out_of_range) {
		return;
	}
}
void loop_worlds() {
	long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	if (last_hm_time - ms_time <= 0) {
		last_hm_time = ms_time + 60000;
		for (int i = 0; i < monitors.size(); i++) {
			string name_ = monitors[i].world_name;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds[p - worlds.begin()];
				WorldBlock* monitor = &world_->blocks[monitors[i].x + (monitors[i].y * 100)];
				if (!items[monitor->fg].heart_monitor) {
					monitors.erase(monitors.begin() + i);
					i--;
					continue;
				}
				monitors[i].active = 0;
				string find_mon = monitor->heart_monitor;
				if (find_mon.size() >= 2) find_mon.resize(find_mon.size() - 2); // remove `` is galo
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName == find_mon) {
						monitors[i].active = 1;
						break;
					}
				}
				PlayerMoving data_{};
				data_.packetType = 5, data_.punchX = monitors[i].x, data_.punchY = monitors[i].y, data_.characterState = 0x8;
				BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, monitor));
				BYTE* blc = raw + 56;
				form_visual(blc, *monitor, *world_, NULL, false, false, monitors[i].x, monitors[i].y);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == world_->name) {
						send_raw(currentPeer, 4, raw, 112 + alloc_(world_, monitor), ENET_PACKET_FLAG_RELIABLE);
					}
				}
				delete[] raw, blc;
			}
		}
	}
	if (last_time - ms_time <= 0) {
		last_time = ms_time + 1000;
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world.empty() or pInfo(currentPeer)->tankIDName.empty()) continue;
			if (pInfo(currentPeer)->last_fish_catch + pInfo(currentPeer)->fish_seconds < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() && pInfo(currentPeer)->fishing_used != 0 && rand() % 100 < (pInfo(currentPeer)->hand == 3010 ? 9 : 6)) {
				PlayerMoving data_{};
				data_.packetType = 17, data_.netID = 34, data_.YSpeed = 34, data_.x = pInfo(currentPeer)->f_x * 32 + 16, data_.y = pInfo(currentPeer)->f_y * 32 + 16;
				pInfo(currentPeer)->last_fish_catch = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				BYTE* raw = packPlayerMoving(&data_);
				gamepacket_t p3(0, pInfo(currentPeer)->netID);
				p3.Insert("OnPlayPositioned"), p3.Insert("audio/splash.wav");
				for (ENetPeer* currentPeer_event = server->peers; currentPeer_event < &server->peers[server->peerCount]; ++currentPeer_event) {
					if (currentPeer_event->state != ENET_PEER_STATE_CONNECTED or currentPeer_event->data == NULL or pInfo(currentPeer_event)->world != pInfo(currentPeer)->world) continue;
					send_raw(currentPeer_event, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE), p3.CreatePacket(currentPeer_event);
				}
				delete[] raw;
			}
			if (pInfo(currentPeer)->save_time + 60000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
				if (pInfo(currentPeer)->save_time != 0) {
					save_player(pInfo(currentPeer), false);
					save_guilds();
				}
				pInfo(currentPeer)->save_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			}
			if (pInfo(currentPeer)->hand == 3578 && pInfo(currentPeer)->hand_torch + 60000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
				if (pInfo(currentPeer)->hand_torch != 0) {
					int got = 0;
					modify_inventory(currentPeer, 3578, got);
					if (got - 1 >= 1) {
						gamepacket_t p;
						p.Insert("OnTalkBubble"), p.Insert(pInfo(currentPeer)->netID), p.Insert("`4My torch went out, but I have " + to_string(got - 1) + " more!``"), p.CreatePacket(currentPeer);
					}
					modify_inventory(currentPeer, 3578, got = -1);
				}
				pInfo(currentPeer)->hand_torch = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			}

			if (pInfo(currentPeer)->hand == 2204 and pInfo(currentPeer)->x != -1 and pInfo(currentPeer)->y != -1) {
				if (not has_playmod(pInfo(currentPeer), "Irradiated")) {
					if (pInfo(currentPeer)->geiger_x == -1 and pInfo(currentPeer)->geiger_y == -1) pInfo(currentPeer)->geiger_x = (rand() % 100) * 32, pInfo(currentPeer)->geiger_y = (rand() % 54) * 32;
					int a_ = pInfo(currentPeer)->geiger_x + ((pInfo(currentPeer)->geiger_y * 100) / 32), b_ = pInfo(currentPeer)->x + ((pInfo(currentPeer)->y * 100) / 32), diff = abs(a_ - b_) / 32;
					if (diff > 30) { // nieko

					}
					else if (diff >= 30) { // raudona
						if (pInfo(currentPeer)->geiger_time + 1500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							pInfo(currentPeer)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							PlayerMoving data_{};
							data_.packetType = 17, data_.x = pInfo(currentPeer)->x + 10, data_.y = pInfo(currentPeer)->y + 16, data_.characterState = 0x8, data_.XSpeed = 0, data_.YSpeed = 114;
							BYTE* raw = packPlayerMoving(&data_, 56);
							raw[3] = 114;
							double rotation = -4.13;
							memcpy(raw + 40, &rotation, 4);
							send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
							delete[] raw;
						}
					}
					else if (diff >= 15) { // geltona
						if (pInfo(currentPeer)->geiger_time + 1500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							pInfo(currentPeer)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							PlayerMoving data_{};
							data_.packetType = 17, data_.x = pInfo(currentPeer)->x + 10, data_.y = pInfo(currentPeer)->y + 16, data_.characterState = 0x8, data_.XSpeed = 1, data_.YSpeed = 114;
							BYTE* raw = packPlayerMoving(&data_, 56);
							raw[3] = 114;
							double rotation = -4.13;
							memcpy(raw + 40, &rotation, 4);
							send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
							delete[] raw;
						}
					}
					else { // zalia
						if (diff <= 1) { // surado
							{
								if (pInfo(currentPeer)->geiger_time + 2500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
									pInfo(currentPeer)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
									pInfo(currentPeer)->geiger_x = -1, pInfo(currentPeer)->geiger_y = -1;
									{
										int c_ = -1;
										modify_inventory(currentPeer, 2204, c_);
										int c_2 = 1;
										if (modify_inventory(currentPeer, 2286, c_2) != 0) {
											string name_ = pInfo(currentPeer)->world;
											vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
											if (p != worlds.end()) {
												World* world_ = &worlds[p - worlds.begin()];
												WorldDrop drop_block_{};
												drop_block_.id = 2286, drop_block_.count = 1, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = pInfo(currentPeer)->x + rand() % 17, drop_block_.y = pInfo(currentPeer)->y + rand() % 17;
												dropas_(world_, drop_block_);
											}
										}
										PlayMods give_playmod{};
										give_playmod.id = 10;
										give_playmod.time = time(nullptr) + 900;
										pInfo(currentPeer)->playmods.push_back(give_playmod);
										pInfo(currentPeer)->hand = 2286;
										update_clothes(currentPeer);
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert(a + "You are aglow with radiation! (`$Irradiated`` mod added, `$15 mins`` left)");
										p.CreatePacket(currentPeer);
										packet_(currentPeer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
									}
									int chanced = 0;
									add_role_xp(currentPeer, 1, "geiger");
									vector<int> geiger_items = { 6416,3196,2206,1500,1498,2806,2804,8270,8272,8274,2244,2246,2242,3792,3306,4676,4678,4680,4682,4652,4650,4648,4646,11186,10086 };
									vector<int> rare_cr = { 2248,2250,3792,10084 };
									vector<int> rarest = { 4654 , 9380 , 11562, 1486, 1796, 274, 276 };
									int item_ = geiger_items[rand() % geiger_items.size()];
									if (rand() % 50 < 10 + chanced) item_ = rare_cr[rand() % rare_cr.size()];
									if (rand() % 50 < 2 + chanced) item_ = rarest[rand() % rarest.size()];
									int c_ = 1;
									if (modify_inventory(currentPeer, item_, c_) != 0) {
										string name_ = pInfo(currentPeer)->world;
										vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
										if (p != worlds.end()) {
											World* world_ = &worlds[p - worlds.begin()];
											WorldDrop drop_block_{};
											drop_block_.id = item_, drop_block_.count = 1, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = pInfo(currentPeer)->x + rand() % 17, drop_block_.y = pInfo(currentPeer)->y + rand() % 17;
											dropas_(world_, drop_block_);
										}
									}
									gamepacket_t p;
									p.Insert("OnParticleEffect");
									p.Insert(48);
									p.Insert((float)pInfo(currentPeer)->x + 10, (float)pInfo(currentPeer)->y + 16);
									p.CreatePacket(currentPeer);
									{
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(currentPeer)->netID);
										p.Insert("I found `21 " + items[item_].name + "``!");
										p.Insert(0);
										p.CreatePacket(currentPeer);
										gamepacket_t p2;
										p2.Insert("OnConsoleMessage");
										p2.Insert(pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` found `21 " + items[item_].name + "``!");
										PlayerMoving data_{};
										data_.packetType = 19, data_.plantingTree = 0, data_.netID = 0;
										data_.punchX = item_;
										data_.x = pInfo(currentPeer)->x + 10, data_.y = pInfo(currentPeer)->y + 16;
										int32_t to_netid = pInfo(currentPeer)->netID;
										BYTE* raw = packPlayerMoving(&data_);
										raw[3] = 5;
										memcpy(raw + 8, &to_netid, 4);
										for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
											if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
											if (pInfo(currentPeer2)->world == pInfo(currentPeer)->world) {
												send_raw(currentPeer2, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												p2.CreatePacket(currentPeer2);
											}
										}
										delete[]raw;
									}
								}
							}
						}
						else {
							int t_ = 0;
							if (diff >= 6) t_ = 1350;
							else t_ = 1000;
							if (pInfo(currentPeer)->geiger_time + t_ < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
								pInfo(currentPeer)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
								PlayerMoving data_{};
								data_.packetType = 17, data_.x = pInfo(currentPeer)->x + 10, data_.y = pInfo(currentPeer)->y + 16, data_.characterState = 0x8;
								data_.XSpeed = 2, data_.YSpeed = 114;
								BYTE* raw = packPlayerMoving(&data_, 56);
								raw[3] = 114;
								double rotation = -4.13;
								memcpy(raw + 40, &rotation, 4);
								send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
								delete[] raw;
							}
						}
					}
				}
			}
			long long time_ = time(nullptr);
			for (int i_ = 0; i_ < pInfo(currentPeer)->playmods.size(); i_++) {
				if (pInfo(currentPeer)->playmods[i_].id == 12) {
					if (pInfo(currentPeer)->valentine_time + 2500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(currentPeer)->valentine_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						for (ENetPeer* valentine = server->peers; valentine < &server->peers[server->peerCount]; ++valentine) {
							if (valentine->state != ENET_PEER_STATE_CONNECTED or valentine->data == NULL) continue;
							if (pInfo(valentine)->world == pInfo(currentPeer)->world and pInfo(valentine)->tankIDName == pInfo(currentPeer)->playmods[i_].user) {
								if (not pInfo(valentine)->invis and not pInfo(currentPeer)->invis and pInfo(currentPeer)->x != -1 and pInfo(currentPeer)->y != -1 and pInfo(valentine)->x != -1 and pInfo(valentine)->y != -1) {
									gamepacket_t p;
									p.Insert("OnParticleEffect");
									p.Insert(13);
									p.Insert((float)pInfo(valentine)->x + 10, (float)pInfo(valentine)->y + 16);
									p.Insert((float)0), p.Insert((float)pInfo(currentPeer)->netID);
									bool double_send = false;
									for (int i_2 = 0; i_2 < pInfo(valentine)->playmods.size(); i_2++) {
										if (pInfo(valentine)->playmods[i_2].id == 12 and pInfo(valentine)->playmods[i_2].user == pInfo(currentPeer)->tankIDName) {
											double_send = true;
											break;
										}
									}
									gamepacket_t p2;
									p2.Insert("OnParticleEffect");
									p2.Insert(13);
									p2.Insert((float)pInfo(currentPeer)->x + 10, (float)pInfo(currentPeer)->y + 16);
									p2.Insert((float)0), p2.Insert((float)pInfo(valentine)->netID);
									for (ENetPeer* valentine_bc = server->peers; valentine_bc < &server->peers[server->peerCount]; ++valentine_bc) {
										if (valentine_bc->state != ENET_PEER_STATE_CONNECTED or valentine_bc->data == NULL) continue;
										if (pInfo(valentine_bc)->world == pInfo(currentPeer)->world) {
											p.CreatePacket(valentine_bc);
											if (double_send) p2.CreatePacket(valentine_bc);
										}
									}
								}
								break;
							}
						}
					}
				}
				if (pInfo(currentPeer)->playmods[i_].time - time_ < 0) {
					for (vector<string> get_ : info_about_playmods) {
						uint32_t playmod_id = atoi(get_[0].c_str());
						if (playmod_id == pInfo(currentPeer)->playmods[i_].id) {
							string playmod_name = get_[2];
							string playmod_on_remove = get_[4];
							pInfo(currentPeer)->playmods.erase(pInfo(currentPeer)->playmods.begin() + i_);
							packet_(currentPeer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert(playmod_on_remove + " (`$" + playmod_name + "`` mod removed)");
							p.CreatePacket(currentPeer);
							update_clothes(currentPeer);
							break;
						}
					}
				}
			}
		}
	}
}
int main() {
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	srand(unsigned int(time(nullptr)));
	if (items_dat() == -1) cout << "items.dat error" << endl;
	LoadConfig();
	threads.push_back(thread(board_world_loop));
	if (init_enet(server_port) == -1)
		cout << "enet error" << endl;
	else
		cout << server_name << " started with " << server_port << endl;
	cout << "Items Size: " << item_data_size << endl;
	SetConsoleTitle(L"Xoid Console");
	daily_quest();
	refreshBoard();
	refreshGuildBoard();
	for (const auto& entry : fs::directory_iterator("guilds")) {
		if (!fs::is_directory(entry.path())) {
			string guild_id = explode(".", entry.path().filename().string())[0];
			json guild_read;
			ifstream read_guild(entry.path(), ifstream::binary);
			read_guild >> guild_read;
			read_guild.close();
			Guild new_guild{};
			new_guild.guild_id = atoi(guild_id.c_str());
			new_guild.guild_name = guild_read["guild_name"].get<string>();
			new_guild.guild_description = guild_read["guild_description"].get<string>();
			new_guild.guild_mascot = guild_read["guild_mascot"].get<vector<uint16_t>>();
			new_guild.guild_level = guild_read["guild_level"].get<uint16_t>();
			new_guild.guild_xp = guild_read["guild_xp"].get<uint32_t>();
			new_guild.coleader_access = guild_read["coleader_access"].get<bool>();
			new_guild.coleader_elder_access = guild_read["coleader_elder_access"].get<bool>();
			new_guild.all_access = guild_read["all_access"].get<bool>();
			new_guild.guild_world = guild_read["guild_world"].get<string>();
			json a_ = guild_read["guild_members"].get<json>();
			for (int i_ = 0; i_ < a_.size(); i_++) {
				GuildMember new_member{};
				new_member.member_name = a_[i_]["member_name"].get<string>();
				new_member.role_id = a_[i_]["role_id"].get<int>();
				new_member.public_location = a_[i_]["public_location"].get<bool>();
				new_member.show_notifications = a_[i_]["show_notifications"].get<bool>();
				new_member.last_online = a_[i_]["last_online"].get<long long>();
				new_guild.guild_members.push_back(new_member);
			}
			json b_ = guild_read["guild_logs"].get<json>();
			for (int i_ = 0; i_ < b_.size(); i_++) {
				GuildLog new_log{};
				new_log.info = b_[i_]["info"].get<string>();
				new_log.display_id = b_[i_]["display_id"].get<uint16_t>();
				new_log.date = b_[i_]["date"].get<long long>();
				new_guild.guild_logs.push_back(new_log);
			}
			guilds.push_back(new_guild);
		}
	}
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	thedaytoday = newtime.tm_wday;
	{
		const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		string month = months[newtime.tm_mon], translated = "", str = to_string(today_day), locke = "";
		if (str == "01" || str == "21") translated = "st";
		else if (str == "02" || str == "22") translated = "nd";
		else if (str == "03") translated = "rd";
		else translated = "th";
	}
	if (thedaytoday == 1) theitemtoday = 5040;
	else if (thedaytoday == 2) theitemtoday = 5042;
	else if (thedaytoday == 3) theitemtoday = 5044;
	else if (thedaytoday == 4) theitemtoday = 5032;
	else if (thedaytoday == 5)theitemtoday = 5034;
	else if (thedaytoday == 6) theitemtoday = 5036;
	else if (thedaytoday == 0)theitemtoday = 5038;
	/*long long mss_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	if (event_timer - mss_time <= 0)
	{
		event_timer = mss_time + 604800000;
		cout << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << endl;
	}*/
	ENetEvent event;
	while (true) {
		while (enet_host_service(server, &event, 1000) > 0) {
			if (saving_ or f_saving_) continue;
			ENetPeer* peer = event.peer;
			switch (event.type) {
			case ENET_EVENT_TYPE_CONNECT:
			{
				char clientConnection[16];
				enet_address_get_host_ip(&peer->address, clientConnection, 16);

				send_(peer, 1, nullptr, 0);
				peer->data = new Player;

				pInfo(peer)->id = peer->connectID, pInfo(peer)->ip = clientConnection;
				string error = "";
				int logged = 0;

				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->ip != pInfo(currentPeer)->ip) continue;
					logged++;
				}

				struct tm newtime;
				time_t now = time(0);
				localtime_s(&newtime, &now);
				string datt = "" + to_string(newtime.tm_mday) + "/" + to_string(newtime.tm_mon + 1) + "/2023 " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min)) + ":" + to_string(newtime.tm_sec) + "";
				packet_(peer, "action|log\nmsg|`oYou had join on `4GT`0SG`o.``");
				if (logged > 3) error = "`4OOPS:`` Too many people logging in at once. Please press `5CANCEL`` and try again in a few seconds.";
				if (pInfo(peer)->ip != pInfo(peer)->meta and pInfo(peer)->meta != "") error = "action|log\nmsg|CT:[S]_ `4Can not make new account!`` Sorry, but IP " + pInfo(peer)->ip + " is not permitted to create NEW Growtopia accounts at this time. (This can be because there is an open proxy/VPN here or abuse has from this IP) Please try again from another IP address.";
				if (error != "") packet_(peer, error, ""), enet_peer_disconnect_later(peer, 0);
				break;

			}
			case ENET_EVENT_TYPE_RECEIVE:
			{
				loop_worlds();

				switch (message_(event.packet)) {
				case 2:
				{
					string cch = text_(event.packet);
					if (cch.size() > 1024) break;

					cout << cch << endl;

					if (pInfo(peer)->tracked) {
						ofstream trlog("track/" + pInfo(peer)->tankIDName + ".txt", ios::app);
						auto now = std::time(nullptr);
						if (cch.find("action|") != string::npos && cch.find("action|dialog_return") == string::npos) {
							trlog << "" << getDate() << "[ACTION] " << pInfo(peer)->tankIDName << ": " << cch << "\n";
						}
						if (cch.find("action|dialog_return") != string::npos) {
							trlog << "" << getDate() << "[DIALOG] " << pInfo(peer)->tankIDName << ": " << cch << "\n";
						}
						trlog.close();
					}
					if (panic_mode == 1) {
						ofstream trlog("logs/panic.txt", ios::app);
						auto now = std::time(nullptr);
						if (cch.find("action|") != string::npos && cch.find("action|dialog_return") == string::npos) {
							trlog << "" << getDate() << "[ACTION] " << pInfo(peer)->tankIDName << ": " << cch << "\n";
						}
						if (cch.find("action|dialog_return") != string::npos) {
							trlog << "" << getDate() << "[DIALOG] " << pInfo(peer)->tankIDName << ": " << cch << "\n";
						}
						trlog.close();
					} // memleak risk: track and panic logs
					if (cch == "action|getDRAnimations\n" || cch == "action|refresh_player_tribute_data\n") break;
					if (pInfo(peer)->lpps + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(peer)->pps = 0;
						pInfo(peer)->lpps = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					}
					else {
						pInfo(peer)->pps++;
						if (pInfo(peer)->pps >= 10) {
							enet_peer_disconnect_later(peer, 0);
							break;
						}
					}
					if (pInfo(peer)->requestedName.empty()) {
						if (pInfo(peer)->enter_game != 0 || pInfo(peer)->world != "") enet_peer_disconnect_later(peer, 0);
						else player_login(peer, cch), anansave(peer, cch);
					}


					else if (cch.find("action|input") != string::npos) {
						vector<string> t_ = explode("|", cch);
						if (t_.size() < 4) break;
						string msg = explode("\n", t_[3])[0];
						if (pInfo(peer)->tankIDName == "") break;
						if (msg.length() <= 0 || msg.length() > 120 || msg.empty() || std::all_of(msg.begin(), msg.end(), [](char c) {return std::isspace(c); })) continue;
						for (char c : msg) if (c < 0x20 || c>0x7A) continue;
						space_(msg);
						if (msg[0] == '/') SendCmd(peer, msg);
						else {
							if (msg[0] == '`' and msg.size() <= 2) break;
							if (pInfo(peer)->world == "") break;
							if (has_playmod(pInfo(peer), "duct tape") || has_playmod(pInfo(peer), "Iron MMMFF")) {
								string msg2 = "";
								for (int i = 0; i < msg.length(); i++) {
									if (isspace(msg[i])) msg2 += " ";
									else {
										if (isupper(msg[i])) msg2 += i % 2 == 0 ? "M" : "F";
										else msg2 += i % 2 == 0 ? "m" : "f";
									}
								}
								msg = msg2;
							}
							string check_ = msg;
							bool isown = false;
							transform(check_.begin(), check_.end(), check_.begin(), ::tolower);
							{
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									if (world_->owner_name == pInfo(peer)->tankIDName) isown = true;
									if (world_->silence and pInfo(peer)->superdev != 1 and world_->owner_name != pInfo(peer)->tankIDName and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end()) {
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("`1(Peasants must not speak)"), p.Insert(1), p.CreatePacket(peer);
										break;
									}
								}
							}
							bool warned = false;
							pInfo(peer)->not_same++;
							if (pInfo(peer)->last_input_text == msg) pInfo(peer)->same_input++;
							pInfo(peer)->last_input_text = msg;
							if (pInfo(peer)->last_spam_detection + 5000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) pInfo(peer)->last_spam_detection = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count(), pInfo(peer)->same_input = 0, pInfo(peer)->not_same = 0;
							if (pInfo(peer)->same_input >= 3 || pInfo(peer)->not_same >= 5) {
								gamepacket_t p;
								p.Insert("OnConsoleMessage"), p.Insert("`6>>`4Spam detected! ``Please wait a bit before typing anything else.  Please note, any form of bot/macro/auto-paste will get all your accounts banned, so don't do it!"), p.CreatePacket(peer);
							}
							else {
								gamepacket_t p, p2;
								p.Insert("OnConsoleMessage");
								p.Insert("CP:_PL:0_OID:_CT:[W]_ `6<`w" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "`6> `$" + (has_playmod(pInfo(peer), "Infected!") ? "`2" : "") + "" + ((pInfo(peer)->adminLevel >= 4 and pInfo(peer)->d_name.empty()) ? "`5" : ((pInfo(peer)->adminLevel == 3 or pInfo(peer)->adminLevel == 2 or pInfo(peer)->adminLevel == 4) and pInfo(peer)->d_name.empty()) ? "`1" : ((pInfo(peer)->adminLevel == 1 and pInfo(peer)->d_name.empty())) ? "`^" : "`$") + msg + "`````");
								p2.Insert("OnTalkBubble");
								p2.Insert(pInfo(peer)->netID);
								if (check_ != ":/" and check_ != ":p" and check_ != ":*" and check_ != ";)" and check_ != ":d" and check_ != ":o" and check_ != ":'(" and check_ != ":(") {
									p2.Insert("CP:_PL:0_OID:_player_chat=" + a + ((pInfo(peer)->adminLevel >= 4 and pInfo(peer)->d_name.empty()) ? "`5" : ((pInfo(peer)->adminLevel == 3 or pInfo(peer)->adminLevel == 2 or pInfo(peer)->adminLevel == 4) and pInfo(peer)->d_name.empty()) ? "`1" : ((pInfo(peer)->adminLevel == 1 and pInfo(peer)->d_name.empty())) ? "`^" : "`0") + msg);
								}
								else p2.Insert(msg);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == pInfo(peer)->world) {
										bool muted_ = false;
										for (int c_ = 0; c_ < pInfo(currentPeer)->friends.size(); c_++) {
											if (pInfo(currentPeer)->friends[c_].name == pInfo(peer)->tankIDName) {
												if (pInfo(currentPeer)->friends[c_].mute) {
													muted_ = true;
													break;
												}
											}
										} if (not muted_) {
											p.CreatePacket(currentPeer);
											p2.CreatePacket(currentPeer);
										}
									}
								}
							}
						}
						break;
					}
					else if (cch.find("action|mod_trade") != string::npos or cch.find("action|rem_trade") != string::npos) {
						vector<string> t_ = explode("|", cch);
						if (t_.size() < 3) break;
						int item_id = atoi(explode("\n", t_[2])[0].c_str()), c_ = 0;
						modify_inventory(peer, item_id, c_);
						if (c_ == 0) break;
						if (items[item_id].untradeable or item_id == 1424 or item_id == 9770 or item_id == 10362 or item_id == 9846 or item_id == 9772 or item_id == 5480) {
							gamepacket_t p;
							p.Insert("OnTextOverlay");
							p.Insert("You'd be sorry if you lost that!");
							p.CreatePacket(peer);
							break;
						} if (c_ == 1 or cch.find("action|rem_trade") != string::npos) {
							pInfo(peer)->onTrade = true; //exploit
							mod_trade(peer, item_id, c_, (cch.find("action|rem_trade") != string::npos ? true : false));
							break;
						}
						if (cch.find("action|rem_trade") == string::npos) {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`2Trade`` `w" + items[item_id].name + "``|left|" + to_string(item_id) + "|\nadd_textbox|`2Trade how many?``|left|\nadd_text_input|count||" + to_string(c_) + "|5|\nembed_data|itemID|" + to_string(item_id) + "\nend_dialog|trade_item|Cancel|OK|");
							p.CreatePacket(peer);
						}
						break;
					}
					else if (cch.find("action|trade_accept") != string::npos) {
						if (pInfo(peer)->trading_with != -1) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 3) break;
							string status_ = explode("\n", t_[2])[0];
							if (status_ != "1" and status_ != "0") break;
							bool f_ = false;
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (pInfo(currentPeer)->world == pInfo(peer)->world) {
									if (pInfo(currentPeer)->netID == pInfo(peer)->trading_with and pInfo(peer)->netID == pInfo(currentPeer)->trading_with) {
										string name_ = pInfo(peer)->world;
										vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
										if (p != worlds.end()) {
											World* world_ = &worlds[p - worlds.begin()];
											if (status_ == "1")
												pInfo(peer)->trade_accept = 1;
											else
												pInfo(peer)->trade_accept = 0;
											if (pInfo(peer)->trade_accept and pInfo(currentPeer)->trade_accept) {
												// check inv space   
												if (not trade_space_check(peer, currentPeer)) {
													pInfo(peer)->trade_accept = 0, pInfo(currentPeer)->trade_accept = 0;
													gamepacket_t p;
													p.Insert("OnTradeStatus");
													p.Insert(pInfo(peer)->netID);
													p.Insert("");
													p.Insert("`o" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``'s offer.``");
													p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\naccepted|0");
													p.CreatePacket(peer);
													{
														gamepacket_t p;
														p.Insert("OnTradeStatus");
														p.Insert(pInfo(peer)->netID);
														p.Insert("");
														p.Insert("`o" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``'s offer.``");
														p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|0");
														p.CreatePacket(currentPeer);
													}
													f_ = true;
													break;
												}
												else if (not trade_space_check(currentPeer, peer)) {
													pInfo(peer)->trade_accept = 0, pInfo(currentPeer)->trade_accept = 0;
													gamepacket_t p;
													p.Insert("OnTradeStatus");
													p.Insert(pInfo(currentPeer)->netID);
													p.Insert("");
													p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
													p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\naccepted|0");
													p.CreatePacket(currentPeer);
													{
														gamepacket_t p;
														p.Insert("OnTradeStatus");
														p.Insert(pInfo(currentPeer)->netID);
														p.Insert("");
														p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
														p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
														p.CreatePacket(peer);
													}
													f_ = true;
													break;
												}
												{
													gamepacket_t p;
													p.Insert("OnForceTradeEnd");
													p.CreatePacket(peer);
												}
												send_trade_confirm_dialog(peer, currentPeer);
												break;
											}
											gamepacket_t p;
											p.Insert("OnTradeStatus");
											p.Insert(pInfo(peer)->netID);
											p.Insert("");
											p.Insert("`o" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``'s offer.``");
											p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\naccepted|" + status_);
											p.CreatePacket(peer);
											{
												{
													gamepacket_t p;
													p.Insert("OnTradeStatus");
													p.Insert(pInfo(currentPeer)->netID);
													p.Insert("");
													p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
													p.Insert("locked|0\nreset_locks|1\naccepted|0");
													p.CreatePacket(currentPeer);
												}
												gamepacket_t p;
												p.Insert("OnTradeStatus");
												p.Insert(pInfo(currentPeer)->netID);
												p.Insert("");
												p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
												p.Insert("locked|0\naccepted|1");
												p.CreatePacket(currentPeer);
												{
													gamepacket_t p;
													p.Insert("OnTradeStatus");
													p.Insert(pInfo(currentPeer)->netID);
													p.Insert("");
													p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
													p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
													p.CreatePacket(currentPeer);
												}
												{
													gamepacket_t p;
													p.Insert("OnTradeStatus");
													p.Insert(pInfo(peer)->netID);
													p.Insert("");
													p.Insert("`o" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``'s offer.``");
													p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|" + status_);
													p.CreatePacket(currentPeer);
												}
											}
										}
										f_ = true;
										break;
									}
								}
							} if (not f_) {
								if (status_ == "1")
									pInfo(peer)->trade_accept = 1;
								else
									pInfo(peer)->trade_accept = 0;
							}
						}
						break;
					}
					else if (cch == "action|trade_cancel\n") cancel_trade(peer);
					if (pInfo(peer)->trading_with == -1) {

						if (cch.find("action|dialog_return\ndialog_name|information_pane\nbuttonClicked|warp_to_") != string::npos) {
							if (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1) {
								string world_name = cch.substr(67, cch.length() - 67);
								replace_str(world_name, "\n", "");
								replace_str(world_name, "reason|", "");
								join_world(peer, world_name);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|wishing_well\nbuttonClicked|wishing_well") != string::npos) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								world_->fresh_world = true;
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (not block_access(peer, world_, block_) or block_->fg != 10656 or block_->shelf_1 >= 200) break;
								int got = 0;
								modify_inventory(peer, 3402, got);
								if (got >= 5) {
									got = 5;
									int remove_ = -1 * got;
									modify_inventory(peer, 3402, remove_);
									block_->shelf_1 += got;
									drop_valentine_box(peer, world_, block_, pInfo(peer)->lastwrenchx, pInfo(peer)->lastwrenchy, true, 5);
									if (block_->shelf_1 >= 200) {
										block_->planted = 0;
										PlayerMoving data_{};
										data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
										int alloc = alloc_(world_, block_);
										BYTE* raw = packPlayerMoving(&data_, 112 + alloc);
										BYTE* blc = raw + 56;
										form_visual(blc, *block_, *world_, peer, false);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == world_->name) {
												send_raw(currentPeer, 4, raw, 112 + alloc, ENET_PACKET_FLAG_RELIABLE);
											}
										}
										delete[] raw, blc;
										if (block_->locked) upd_lock(*block_, *world_, peer);
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|pzr_") != string::npos) {
							int id = atoi(cch.substr(52, cch.length() - 52).c_str());

							int count = 1;

							int price = 0;

							if (id == 5078 || id == 5080 || id == 5082 || id == 5084 || id == 7166) price = (pInfo(peer)->adminLevel >= 6 ? 11 : 13);
							else if (id == 5126 || id == 5144 || id == 5162 || id == 5180 || id == 7168) price = (pInfo(peer)->adminLevel >= 6 ? 18 : 20);
							else if (id == 5128 || id == 5144 || id == 5164 || id == 5182 || id == 7180) price = (pInfo(peer)->adminLevel >= 6 ? 26 : 28);
							else if (id == 5130 || id == 5146 || id == 5166 || id == 5184 || id == 7182) price = (pInfo(peer)->adminLevel >= 6 ? 35 : 37);
							else if (id == 5132 || id == 5148 || id == 5168 || id == 5186 || id == 7184) price = (pInfo(peer)->adminLevel >= 6 ? 45 : 48);
							else if (id == 5134 || id == 5150 || id == 5170 || id == 5188 || id == 7186) price = (pInfo(peer)->adminLevel >= 6 ? 62 : 65);

							int mybgl = 0;

							modify_inventory(peer, 7188, mybgl);

							int mine = price * -1;
							if (mybgl >= price) {
								if (modify_inventory(peer, id, count) == 0) {
									modify_inventory(peer, 7188, mine);
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`2>> You claimed `0" + items[id].name + ".");
									p.CreatePacket(peer);
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`4You dont have enough enventory.");
									p.CreatePacket(peer);
									break;
								}
							}
							else {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4You dont have enough bgl.");
								p.CreatePacket(peer);
								break;
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|clc_") != string::npos) {
							int count = atoi(cch.substr(52, cch.length() - 52).c_str());

							int c_ = 5;
							if (pInfo(peer)->harvest_quest < 500 and pInfo(peer)->fishing_quest < 30) continue;

							if (modify_inventory(peer, 1486, c_) == 0) {
								if (pInfo(peer)->harvest_quest >= 500) pInfo(peer)->harvest_quest = 0;
								else if (pInfo(peer)->fishing_quest >= 30) pInfo(peer)->fishing_quest = 0;

								packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`2>> You collected " + to_string(count) + "x Growtokens!");
								p.CreatePacket(peer);
								tokenquests_dialog(peer);
							}
							else {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4You dont have enough enventory.");
								p.CreatePacket(peer);
								break;
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|bpo_") != string::npos) {
							int item = atoi(cch.substr(52, cch.length() - 52).c_str());
							if (item <= 0 || item >= items.size()) continue;
							int anan = 0;
							if (item == 9386) anan = 3000;
							else break;
							if (pInfo(peer)->bpoi >= anan) {
								int c_ = 1;
								if (modify_inventory(peer, item, c_) == 0) {
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`o>> You purchased " + items[item].name + "!");
									p.CreatePacket(peer);
									pInfo(peer)->bpoi -= anan;
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("No inventory space.");
									p.CreatePacket(peer);
								}
							}
							break;
						}
						else if (cch == "action|claimprogressbar\n") {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							if (cch == "action|claimprogressbar\n")p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wAbout Valentine's Event``|left|384|\nadd_spacer|small|\nadd_textbox|During Valentine's Week you will gain points for opening Golden Booty Chests. Claim enough points to earn bonus rewards.|left|\nadd_spacer|small|\nadd_textbox|Current Progress: " + to_string(pInfo(peer)->booty_broken) + "/100|left|\nadd_spacer|small|\nadd_textbox|Reward:|left|\nadd_label_with_icon|small|Super Golden Booty Chest|left|9350|\nadd_smalltext|             - 4x chance of getting a Golden Heart Crystal when opening!|left|" + (pInfo(peer)->booty_broken >= 100 ? "\nadd_spacer|small|\nadd_button|claimreward|Claim Reward|no_flags|0|0|" : "") + "\nend_dialog|valentines_quest||OK|\n");
							p.CreatePacket(peer);
							break;
							}
						else if (cch.find("action|dialog_return\ndialog_name|shop_dtest\nbuttonClicked|shop_dgrowtoken") != string::npos) {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Growtopia`wSG Growtoken|left|3394|\n"
								"add_spacer|small|\n"
								"add_textbox|`oHello, `w" + pInfo(peer)->tankIDName + "``. Welcome to our shop. Our items for current use are on this page. We have made the prices suitable for you. Thank you for reading this article.|left|\n"
								"add_spacer|small|\n"
								"add_label_with_icon|small|`2Buy the items here with Growtoken:|left|1486|\n"
								"add_spacer|small|\n"
								"" + sho3_list + ""
								"add_button_with_icon||END_LIST|noflags|0||\n"
								"end_dialog|shop|Cancel||");
							p.CreatePacket(peer);
					}
						else if (cch.find("action|dialog_return\ndialog_name|shop_dtest\nbuttonClicked|shop_dgems") != string::npos) {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Growtopia`wSG Gems|left|3394|\n"
								"add_spacer|small|\n"
								"add_textbox|`oHello, `w" + pInfo(peer)->tankIDName + "``. Welcome to our shop. Our items for current use are on this page. We have made the prices suitable for you. Thank you for reading this article.|left|\n"
								"add_spacer|small|\n"
								"add_label_with_icon|small|`4Buy the items here with Gems:|left|9438|\n"
								"add_spacer|small|\n"
								"" + shop_list + ""
								"add_button_with_icon||END_LIST|noflags|0||\n"
								"end_dialog|shop|Cancel||");
							p.CreatePacket(peer);
					}
						else if (cch.find("action|dialog_return\ndialog_name|shop_dtest\nbuttonClicked|shop_dfarm") != string::npos) {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Growtopia`wSG Balanced|left|3394|\n"
								"add_spacer|small|\n"
								"add_textbox|`oHello, `w" + pInfo(peer)->tankIDName + "``. Welcome to our shop. Our items for current use are on this page. We have made the prices suitable for you. Thank you for reading this article.|left|\n"
								"add_spacer|small|\n"
								"add_label_with_icon|small|`1Buy the items here with Diamond Locks:|left|1796|\n"
								"add_spacer|small|\n"
								"" + sho2_list + ""
								"add_button_with_icon||END_LIST|noflags|0||\n"
								"end_dialog|shop|Cancel||");
							p.CreatePacket(peer);
					}
						else if (cch.find("action|dialog_return\ndialog_name|punish_pane\nbuttonClicked|punish_player") != string::npos) {
						if (pInfo(peer)->adminLevel >= 1) {
							string result = cch.substr(74, cch.length() - 74);
							vector<string> hasil = split_string_by_newline(result);
							vector<string> days = explode("|", hasil[0]);
							vector<string> hours = explode("|", hasil[1]);
							vector<string> mins = explode("|", hasil[2]);
							vector<string> curse = explode("|", hasil[3]);
							vector<string> mute = explode("|", hasil[4]);
							vector<string> ban = explode("|", hasil[5]);
							vector<string> reason = explode("|", hasil[6]);
							if (not onlyDigit(days[1]) or not onlyDigit(hours[1]) or not onlyDigit(mins[1])) break;
							int Days = atoi(days[1].c_str());
							int Hours = atoi(hours[1].c_str());
							int Mins = atoi(mins[1].c_str());
							string Reason = reason[1];
							if (Reason.length() >= 180) break;
							if (Reason.length() <= 0) Reason = "No Reason Provided";
							int isMute = atoi(mute[1].c_str());
							int isCurse = atoi(curse[1].c_str());
							int isBan = atoi(ban[1].c_str());
							bool silly = false;
							long long int banTime = Days * 86400 + (Hours * 3600) + (Mins * 60);
							if (banTime == 0) {
								gamepacket_t p;
								p.Insert("OnTextOverlay");
								p.Insert("0? Are you kidding?");
								p.CreatePacket(peer);
								break;
							}
							if (isMute == 1 and isCurse == 0 and isBan == 0) {
								if (has_playmod(pInfo(peer), "Mute Cooldown Added.") && !CheckConfigS(server_owner, pInfo(peer)->tankIDName)) {
									gamepacket_t p;
									p.Insert("OnTextOverlay");
									p.Insert("You Have Mute Cooldown!");
									p.CreatePacket(peer);
									break;
								}
								if (to_lower(pInfo(peer)->last_wrenched) == to_lower(pInfo(peer)->tankIDName)) silly = true;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
										if (CheckConfigS(clist, pInfo(currentPeer)->tankIDName)) break;
										add_mute(currentPeer, banTime, Reason, (pInfo(peer)->d_name.empty() ? pInfo(peer)->name_color : "`0") + "" + (pInfo(peer)->d_name.empty() ? pInfo(peer)->tankIDName : pInfo(peer)->d_name) + "``");
										string messages = pInfo(peer)->tankIDName + " muted " + pInfo(currentPeer)->tankIDName;
										ofstream file("logs/mute.txt", ios::app);
										if (file.is_open()) {
											auto now = time(nullptr);
											file << "" << getDate() << " " << messages << "\n";
										}
										file.close();
										PlayMods new_playmod{};
										new_playmod.id = 102, new_playmod.time = time(nullptr) + 21600;
										pInfo(peer)->playmods.push_back(new_playmod);
									}
								}
							}
							else if (isMute == 0 and isCurse == 1 and isBan == 0) {
								if (has_playmod(pInfo(peer), "Curse Cooldown Added.") && !CheckConfigS(server_owner, pInfo(peer)->tankIDName)) {
									gamepacket_t p;
									p.Insert("OnTextOverlay");
									p.Insert("You Have Curse Cooldown!");
									p.CreatePacket(peer);
									break;
								}
								if (to_lower(pInfo(peer)->last_wrenched) == to_lower(pInfo(peer)->tankIDName)) silly = true;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
										if (CheckConfigS(clist, pInfo(currentPeer)->tankIDName)) break;
										add_curse(currentPeer, banTime, Reason, (pInfo(peer)->d_name.empty() ? pInfo(peer)->name_color : "`0") + "" + (pInfo(peer)->d_name.empty() ? pInfo(peer)->tankIDName : pInfo(peer)->d_name) + "``");
										string messages = pInfo(peer)->tankIDName + " cursed " + pInfo(currentPeer)->tankIDName;
										ofstream file("logs/curse.txt", ios::app);
										if (file.is_open()) {
											auto now = time(nullptr);
											file << "" << getDate() << " " << messages << "\n";
										}
										file.close();
										PlayMods new_playmod{};
										new_playmod.id = 101, new_playmod.time = time(nullptr) + 21600;
										pInfo(peer)->playmods.push_back(new_playmod);
									}
								}
							}
							else if (isMute == 0 and isCurse == 0 and isBan == 1) {
								if (has_playmod(pInfo(peer), "Ban Cooldown Added.") && !CheckConfigS(server_owner, pInfo(peer)->tankIDName)) {
									gamepacket_t p;
									p.Insert("OnTextOverlay");
									p.Insert("You Have Ban Cooldown!");
									p.CreatePacket(peer);
									break;
								}
								if (to_lower(pInfo(peer)->last_wrenched) == to_lower(pInfo(peer)->tankIDName)) silly = true;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
										if (CheckConfigS(clist, pInfo(currentPeer)->tankIDName)) break;
										add_mute(currentPeer, banTime, Reason, (pInfo(peer)->d_name.empty() ? pInfo(peer)->name_color : "`0") + "" + (pInfo(peer)->d_name.empty() ? pInfo(peer)->tankIDName : pInfo(peer)->d_name) + "``");
										string messages = pInfo(peer)->tankIDName + " banned " + pInfo(currentPeer)->tankIDName;
										ofstream file("logs/ban.txt", ios::app);
										if (file.is_open()) {
											auto now = time(nullptr);
											file << "" << getDate() << " " << messages << "\n";
										}
										file.close();
										add_ban(currentPeer, banTime, Reason, (pInfo(peer)->d_name.empty() ? pInfo(peer)->name_color : "`0") + "" + (pInfo(peer)->d_name.empty() ? pInfo(peer)->tankIDName : pInfo(peer)->d_name) + "``");
										PlayMods new_playmod{};
										new_playmod.id = 100, new_playmod.time = time(nullptr) + 21600;
										pInfo(peer)->playmods.push_back(new_playmod);

									}
								}
							}
							else {
								gamepacket_t p;
								p.Insert("OnTextOverlay");
								p.Insert("Please choose only one option within Mute/Curse/Ban.");
								p.CreatePacket(peer);
								break;
							}
							if (silly) {
								gamepacket_t p;
								p.Insert("OnTextOverlay");
								p.Insert("That would be weird if you punish yourself.");
								p.CreatePacket(peer);
								break;
							}
						}
						}
						else if (cch.find("action|dialog_return\ndialog_name|upgray\nbuttonClicked|nextlevel_") != string::npos) {
							int lvl = atoi(cch.substr(64, cch.length() - 64).c_str());
							int currentid = 0, giveid = 0, remid = 0, cnt = 0, art = 0, eks = 0, nbyn = 0;

							if (lvl == 1) currentid = 5480, giveid = 9772, remid = 5480, nbyn = 25000;

							else if (lvl == 2) currentid = 9772, giveid = 9846, remid = 9772, nbyn = 50000;

							else if (lvl == 3) currentid = 9846, giveid = 10362, remid = 9846, nbyn = 100000;

							else if (lvl == 4) currentid = 10362, giveid = 9770, remid = 10362, nbyn = 250000;

							else break;
							modify_inventory(peer, currentid, cnt);
							if (cnt >= 1 && pInfo(peer)->raybreak >= nbyn) modify_inventory(peer, remid, eks -= 1), modify_inventory(peer, giveid, art += 1), pInfo(peer)->raybreak = 0, pInfo(peer)->raylvl++, pInfo(peer)->lastray = giveid, raymanupg(peer);
							else {
								gamepacket_t k;
								k.Insert("OnConsoleMessage"), k.Insert("`4Error! `oYou don't have enough level or rayman in your inventory to upgrade!"), k.CreatePacket(peer);
								break;
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|buy") != string::npos) {
							if (cch.find("itemname|") != string::npos) {
							}
							else break;
							string name = explode("\n", explode("itemname|", cch)[1])[0];
							string buy_list_ = "";
							for (int i_ = 0; i_ < kainos.size(); i_++) {
								int item_id = kainos[i_][0];
								if (to_lower(items[item_id].name).find(to_lower(name)) != string::npos) {
									cout << item_id << endl;
									int price = 0;
									price = kainos[i_][1];
									buy_list_ += "\nadd_button_with_icon|buy_" + to_string(item_id) + "|`w" + items[item_id].ori_name + "``|staticBlueFrame|" + to_string(item_id) + "|" + (price == 0 ? "" : to_string(price)) + "|\n";
								}
							}
							if (buy_list_.empty()) {
								packet_(peer, "action|log\nmsg| `4Oops! `w" + name + "`o cannot found!", "");
								break;
							}
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("\ntext_scaling_string|asksksskxkwskkdk|\nadd_label_with_icon|big|`wFound item: " + name + "``|left|6016|\nadd_spacer|small|\nadd_spacer|big|\n" + buy_list_ + "add_quick_exit|\n");
							p.CreatePacket(peer);
						}
						else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|buy_") != string::npos) {
							int item_id = atoi(cch.substr(52, cch.length() - 52).c_str());
							int my_wls = 0, dlp = 0, wlp = 0, item_count = 0;
							if (item_id <= 0 || item_id >= items.size()) break;

							for (int i_ = 0; i_ < kainos.size(); i_++) {
								uint32_t item_ids = kainos[i_][0];
								if (item_ids <= 0 || item_ids >= items.size()) break;
								if (items[item_ids].ori_name == items[item_id].ori_name) {
									my_wls = get_wls(peer), dlp = kainos[i_][1] / 100, wlp = (kainos[i_][1] - (kainos[i_][1] / 100) * 100), item_count = kainos[i_][1];
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("\nadd_label_with_icon|big|`w" + items[kainos[i_][0]].name + "`|left|" + to_string(kainos[i_][0]) + "|\nadd_spacer|small|\nadd_label|small|`2Item Price:|left|\nadd_spacer|small|\nadd_label_with_icon|small|`w" + to_string(dlp) + " Diamond Lock`|left|1796|\nadd_label_with_icon|small|`w" + to_string(wlp) + " World Lock`|left|242|\nadd_spacer|small|\nadd_textbox|`oHow many will you buy?|\nadd_text_input|itemcoun|`oCount:||3|\nadd_spacer|small|\nadd_button|duy_" + to_string(item_id) + "|`0Purchase``|noflags|0|0|\nadd_quick_exit|\n");
									p.CreatePacket(peer);
									break;
								}
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|duy_") != string::npos) {
							int item_id = atoi(cch.substr(52, cch.length() - 52).c_str());

							if (cch.find("itemcoun|") != string::npos) {
							}
							else break;
							if (!onlyDigit(explode("\n", explode("itemcoun|", cch)[1])[0])) break;
							int item_count = atoi(explode("\n", explode("itemcoun|", cch)[1])[0].c_str());

							for (int i_ = 0; i_ < kainos.size(); i_++) {
								uint32_t item_ids = kainos[i_][0];
								if (item_ids <= 0 || item_ids >= items.size()) break;
								if (items[item_ids].ori_name == items[item_id].ori_name) {
									int item_price = kainos[i_][1] * item_count;
									if (item_ids == item_id) {
										if (item_price != kainos[i_][1] * item_count) break;
										int my_wls = get_wls(peer);
										if (kainos[i_][1] * item_count > my_wls) break;
										int free_slots = get_free_slots(pInfo(peer));
										if (free_slots == 0) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You don't have room in your backpack!");
											p.Insert(0), p.Insert(1);
											p.CreatePacket(peer);
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You don't have room in your backpack!");
												p.CreatePacket(peer);
											}
											break;
										}
										int diamond_lock = 0, world_lock = 0, grazinti_wl = 0;
										int is_viso_worldlock = kainos[i_][1] * item_count;
										while (is_viso_worldlock >= 100) {
											is_viso_worldlock -= 100;
											diamond_lock++;
										}
										world_lock = is_viso_worldlock;
										int c_ = 0;
										modify_inventory(peer, 242, c_);
										int turi_world_lock = c_, t_w = c_ * -1;
										c_ = 0;
										modify_inventory(peer, 1796, c_);
										int turi_diamond_lock = c_, t_d = c_ * -1;
										while (diamond_lock > turi_diamond_lock && turi_world_lock >= 100) {
											turi_diamond_lock++, turi_world_lock -= 100;
										} if (diamond_lock > turi_diamond_lock) break;
										while (world_lock > turi_world_lock && turi_diamond_lock >= 1) {
											turi_diamond_lock--, turi_world_lock += 100;
										} if (world_lock > turi_world_lock) break;
										turi_world_lock -= world_lock, turi_diamond_lock -= diamond_lock;
										int a_ = item_count;
										if (modify_inventory(peer, item_ids, a_) == 0) {
											modify_inventory(peer, 242, t_w), modify_inventory(peer, 1796, t_d);
											modify_inventory(peer, 242, turi_world_lock), modify_inventory(peer, 1796, turi_diamond_lock);
										}
										{
											PlayerMoving data_{};
											data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16;
											data_.packetType = 19, data_.plantingTree = 100;
											data_.punchX = item_ids, data_.punchY = pInfo(peer)->netID;
											int32_t to_netid = pInfo(peer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											memcpy(raw + 8, &to_netid, 4);
											send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[] raw;
										}
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnPlayPositioned");
										p.Insert("audio/cash_register.wav");
										p.CreatePacket(peer);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("`7[```9" + pInfo(peer)->tankIDName + " bought " + to_string(item_count) + " " + items[item_ids].ori_name + " for " + to_string(kainos[i_][1] * item_count) + " World Locks.```7]``");
											p.CreatePacket(peer);
										}
										break;
									}
									else break;
								}
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|blast\nname|") != string::npos) {
							if (pInfo(peer)->lastchoosenitem == 830 || pInfo(peer)->lastchoosenitem == 9164 || pInfo(peer)->lastchoosenitem == 9602 || pInfo(peer)->lastchoosenitem == 942 || pInfo(peer)->lastchoosenitem == 1060 || pInfo(peer)->lastchoosenitem == 1136 || pInfo(peer)->lastchoosenitem == 1402 || pInfo(peer)->lastchoosenitem == 9582 || pInfo(peer)->lastchoosenitem == 1532 || pInfo(peer)->lastchoosenitem == 3562 || pInfo(peer)->lastchoosenitem == 4774 || pInfo(peer)->lastchoosenitem == 7380 || pInfo(peer)->lastchoosenitem == 7588 || pInfo(peer)->lastchoosenitem == 9488 || pInfo(peer)->lastchoosenitem == 8556) {
								int blast = pInfo(peer)->lastchoosenitem, got = 0;
								modify_inventory(peer, blast, got);
								if (got == 0) break;
								string world = cch.substr(44, cch.length() - 44).c_str();
								replace_str(world, "\n", "");
								transform(world.begin(), world.end(), world.begin(), ::toupper);
								if (find_if(worlds.begin(), worlds.end(), [world](const World& a) { return a.name == world; }) != worlds.end() || not check_blast(world) || _access_s(("worlds/" + world + "_.json").c_str(), 0) == 0) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("That world name already exists. You'll have to be more original. Maybe add some numbers after it?"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
								}
								else {
									if (modify_inventory(peer, blast, got = -1) == 0) {
										create_world_blast(peer, world, blast);
										if (blast == 830) modify_inventory(peer, 834, got = -100);
										join_world(peer, world);
										//pInfo(peer)->worlds_owned.push_back(world);
										gamepacket_t p(750), p2(750);
										p.Insert("OnConsoleMessage"), p.Insert("** `5" + pInfo(peer)->tankIDName + " activates a " + items[blast].name + "! ``**"), p.CreatePacket(peer);
										p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("** `5" + pInfo(peer)->tankIDName + " activates a " + items[blast].name + "! ``**"), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
									}
								}
							}
							break;
						}
						else if (cch == "action|dialog_return\ndialog_name|world_spray\n") {
							int got = 0;
							modify_inventory(peer, 12600, got);
							if (got == 0) break;
							string name = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name](const World& a) { return a.name == name; });
							if (p != worlds.end()) {
								World* world = &worlds[p - worlds.begin()];
								if (world->owner_name == pInfo(peer)->tankIDName || pInfo(peer)->superdev) {
									int remove = -1;
									modify_inventory(peer, 12600, remove);
									for (int i_ = 0; i_ < world->blocks.size(); i_++) if (world->blocks[i_].fg % 2 != 0)  world->blocks[i_].planted = _int64(2.592e+6);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == name) {
											int x = pInfo(currentPeer)->x, y = pInfo(currentPeer)->y;
											exit_(currentPeer, true);
											join_world(currentPeer, name);
										}
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage"), p.Insert("`wYou must own the world!``"), p.CreatePacket(peer);
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|megaphone\nitemID|2480|\nwords|") != string::npos) {
							string text = cch.substr(62, cch.length() - 62).c_str();
							bool cansb = true;
							int c_ = 0;
							modify_inventory(peer, 2480, c_);
							if (c_ == 0) continue;
							if (has_playmod(pInfo(peer), "duct tape")) {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`6>> That's sort of hard to do while duct-taped.``");
								p.CreatePacket(peer);
								cansb = false;
								continue;
							}
							if (has_playmod(pInfo(peer), "megaphone!")) {
								int time_ = 0;
								for (PlayMods peer_playmod : pInfo(peer)->playmods) {
									if (peer_playmod.id == 13) {
										time_ = peer_playmod.time - time(nullptr);
										break;
									}
								}
								packet_(peer, "action|log\nmsg|>> (" + to_playmod_time(time_) + "before you can broadcast again)", "");
								break;
							}
							if (cansb) {
								replace_str(text, "\n", "");
								pInfo(peer)->usedmegaphone = 1;
								SendCmd(peer, "/sb " + text, false);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|cancel") != string::npos || cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|clear") != string::npos) {
							if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|clear") != string::npos) 	pInfo(peer)->note = "";
							send_wrench_self(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|save\n\npersonal_note|") != string::npos) {
							string btn = cch.substr(81, cch.length() - 81).c_str();
							replace_str(btn, "\n", "");
							if (btn.length() > 128) continue;
							pInfo(peer)->note = btn;
							send_wrench_self(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|shop\nbuttonClicked|shop_price_") != string::npos) {
							int item = atoi(cch.substr(63, cch.length() - 63).c_str());
							if (item <= 0 || item >= items.size() || items[item].shop_price == 0) continue;
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Purchase " + items[item].name + "``|left|" + to_string(items[item].id) + "|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `31/" + setGems(items[item].shop_price) + "`` `0Gems``|left|\nadd_spacer|small|\nadd_text_input|count|Count:|1|3|\nadd_spacer|small|\nadd_button|shop_items_" + to_string(item) + "|`0Purchase `9" + items[item].name + "``|noflags|0|0|\nend_dialog|shop|Cancel||");
							p.CreatePacket(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|shop\nbuttonClicked|sho2_price_") != string::npos) {
							int item = atoi(cch.substr(63, cch.length() - 63).c_str());
							if (item <= 0 || item >= items.size() || items[item].sho2_price == 0) continue;
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Purchase " + items[item].name + "``|left|" + to_string(items[item].id) + "|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `31/" + setGems(items[item].sho2_price) + "`` `0DL``|left|\nadd_spacer|small|\nadd_text_input|count|Count:|1|3|\nadd_spacer|small|\nadd_button|sho2_items_" + to_string(item) + "|`0Purchase `9" + items[item].name + "``|noflags|0|0|\nend_dialog|shop|Cancel||");
							p.CreatePacket(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|shop\nbuttonClicked|sho3_price_") != string::npos) {
							int item = atoi(cch.substr(63, cch.length() - 63).c_str());
							if (item <= 0 || item >= items.size() || items[item].sho3_price == 0) continue;
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Purchase " + items[item].name + "``|left|" + to_string(items[item].id) + "|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `31/" + setGems(items[item].sho3_price) + "`` `0GT``|left|\nadd_spacer|small|\nadd_text_input|count|Count:|1|3|\nadd_spacer|small|\nadd_button|sho3_items_" + to_string(item) + "|`0Purchase `9" + items[item].name + "``|noflags|0|0|\nend_dialog|shop|Cancel||");
							p.CreatePacket(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|shop\nbuttonClicked|shop_items_") != string::npos) {
							int item = atoi(cch.substr(63, cch.length() - 63).c_str());
							if (item <= 0 || item >= items.size() || items[item].shop_price <= 0) continue;

							if (cch.find("count|") != string::npos) {
							}
							else break;
							if (!onlyDigit(explode("\n", explode("count|", cch)[1])[0])) break;
							int count = atoi(explode("\n", explode("count|", cch)[1])[0].c_str());

							if (count > 200 || count < 1) {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4You can buy max 200 item at once.");
								p.CreatePacket(peer);
								break;
							}
							int total = items[item].shop_price * count;
							if (pInfo(peer)->gems >= total) {
								int c_ = count;
								if (modify_inventory(peer, item, c_) == 0) {
									pInfo(peer)->gems -= total;
									gamepacket_t g;
									g.Insert("OnSetBux");
									g.Insert(pInfo(peer)->gems);
									g.Insert(0);
									g.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
									if (pInfo(peer)->supp >= 2) {
										g.Insert((float)33796, (float)1, (float)0);
									}
									g.CreatePacket(peer);
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`2>> You purchased " + items[item].name + "!");
									p.CreatePacket(peer);
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`4No inventory space.");
									p.CreatePacket(peer);
								}
							}
							else {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4You need more gems.");
								p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|shop\nbuttonClicked|sho2_items_") != string::npos) {
							int item = atoi(cch.substr(63, cch.length() - 63).c_str());
							if (item <= 0 || item >= items.size() || items[item].sho2_price <= 0) continue;

							if (cch.find("count|") != string::npos) {
							}
							else break;
							if (!onlyDigit(explode("\n", explode("count|", cch)[1])[0])) break;
							int count = atoi(explode("\n", explode("count|", cch)[1])[0].c_str());

							if (count > 200 || count < 1) {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4You can buy max 200 item at once.");
								p.CreatePacket(peer);
								break;
							}
							int total = items[item].sho2_price * count;
							int mintotal = total * -1;
							int mydl = 0, mybgl = 0;
							modify_inventory(peer, 1796, mydl); modify_inventory(peer, 7188, mybgl);
							int mytotal = (mybgl * 100) + mydl;
							if (mytotal >= total) {
								int c_ = count;
								int eksidl = total * -1;
								int eksibgl = (total / 200) * -1;
								if (modify_inventory(peer, item, c_) == 0) {
									if (total <= 200 && mydl >= total) modify_inventory(peer, 1796, eksidl);
									else if (total % 100 == 0 && mybgl >= total) modify_inventory(peer, 7188, eksibgl);
									else {
										int lazimbgl = (total / 100) * -1;
										int lazimdl = (total % 100) * -1;
										modify_inventory(peer, 1796, lazimdl);
										modify_inventory(peer, 7188, lazimbgl);
									}
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`2>> You purchased " + items[item].name + "!");
									p.CreatePacket(peer);
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`4No inventory space.");
									p.CreatePacket(peer);
								}
							}
							else {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4You need more diamond locks.");
								p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|shop\nbuttonClicked|sho3_items_") != string::npos) {
							int item = atoi(cch.substr(63, cch.length() - 63).c_str());
							if (item <= 0 || item >= items.size() || items[item].sho3_price <= 0) continue;

							if (cch.find("count|") != string::npos) {
							}
							else break;
							if (!onlyDigit(explode("\n", explode("count|", cch)[1])[0])) break;
							int count = atoi(explode("\n", explode("count|", cch)[1])[0].c_str());

							if (count > 200 || count < 1) {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4You can buy max 200 item at once.");
								p.CreatePacket(peer);
								break;
							}
							int total = items[item].sho3_price * count;
							int mintotal = total * -1;
							int mygrowtoken = 0;
							modify_inventory(peer, 1486, mygrowtoken);
							if (mygrowtoken >= total) {
								int c_ = count;
								if (modify_inventory(peer, item, c_) == 0) {
									modify_inventory(peer, 1486, mintotal);
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`2>> You purchased " + items[item].name + "!");
									p.CreatePacket(peer);
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`4No inventory space.");
									p.CreatePacket(peer);
								}
							}
							else {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4You need more growtokens.");
								p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|email_verification\nbuttonClicked|itm") != string::npos) {
							if (cch.find("code|") != string::npos) {
							}
							else break;
							if (!onlyDigit(explode("\n", explode("code|", cch)[1])[0])) break;
							int code = atoi(explode("\n", explode("code|", cch)[1])[0].c_str());
							if (code < 111111 || code > 999999) break;

							pInfo(peer)->email_code = rand() % (999999 - 111111 + 1) + 111111;



						}
						else if (cch == "action|dialog_return\ndialog_name|backpack_menu\nbuttonClicked|backpack_upgrade\n\n") {
							if (pInfo(peer)->gems >= (1000 * ((pInfo(peer)->b_l * pInfo(peer)->b_l) + 25)) * 2) {
								if (pInfo(peer)->b_l * 10 > 200) {
									{
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have reached max slots!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
								else {
									pInfo(peer)->gems -= (1000 * ((pInfo(peer)->b_l * pInfo(peer)->b_l) + 25)) * 2;
									pInfo(peer)->b_l++;
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnSetBux");
									p.Insert(pInfo(peer)->gems);
									p.Insert(0);
									p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
									if (pInfo(peer)->supp >= 2) {
										p.Insert((float)33796, (float)1, (float)0);
									}
									p.CreatePacket(peer);
									{
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("Congratulations! You have upgraded your Backpack!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
									backpack_show(peer);
								}
							}
							else {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("You don't have enough gems!");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|backpack_menu\nbuttonClicked|") != string::npos) {
							int choosen_item = atoi(cch.substr(61, cch.length() - 61).c_str());
							if (choosen_item >= pInfo(peer)->bp.size() || choosen_item > 200 || choosen_item > pInfo(peer)->b_l * 10) break;
							for (int i_ = 0; i_ < pInfo(peer)->bp.size(); i_++) {
								if (choosen_item == i_) {
									if (pInfo(peer)->bp[choosen_item].first <= 0 || pInfo(peer)->bp[choosen_item].first >= items.size()) break;
									int pickedup = pInfo(peer)->bp[choosen_item].second;
									int count = pInfo(peer)->bp[choosen_item].second;
									if (modify_inventory(peer, pInfo(peer)->bp[choosen_item].first, count) == 0) {
										{
											gamepacket_t p, p2;
											p.Insert("OnConsoleMessage"), p.Insert("You picked up " + to_string(pickedup) + " " + items[pInfo(peer)->bp[choosen_item].first].name + "."), p.CreatePacket(peer);
											p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p.Insert("You picked up " + to_string(pickedup) + " " + items[pInfo(peer)->bp[choosen_item].first].name + "."), p2.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 19, data_.punchX = pInfo(peer)->bp[choosen_item].first, data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16;
										int32_t to_netid = pInfo(peer)->netID;
										BYTE* raw = packPlayerMoving(&data_);
										raw[3] = 5;
										memcpy(raw + 8, &to_netid, 4);
										send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										delete[]raw;
										pInfo(peer)->bp.erase(pInfo(peer)->bp.begin() + i_);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You don't have enough inventory space!"), p.CreatePacket(peer);
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|backpack_menu\nitemid|") != string::npos) {
							if (pInfo(peer)->bp.size() <= pInfo(peer)->b_l * 10) {
								int got = 0, item = atoi(cch.substr(54, cch.length() - 54).c_str());
								modify_inventory(peer, item, got);
								if (got <= 0) break;
								if (items[item].untradeable == 1 || item == 1424 || items[item].blockType == BlockTypes::FISH || item == 1796 || item == 7188 || item == 242 || item == 9770 || item == 10362 || item == 9846 || item == 9772 || item == 5480) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("You can't store this item!");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
								}
								else {
									pInfo(peer)->bp.push_back(make_pair(item, got));
									modify_inventory(peer, item, got *= -1);
									PlayerMoving data_{};
									data_.packetType = 19, data_.punchX = item, data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16;
									int32_t to_netid = pInfo(peer)->netID;
									BYTE* raw = packPlayerMoving(&data_);
									raw[3] = 5;
									memcpy(raw + 8, &to_netid, 4);
									send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									delete[]raw;
									backpack_show(peer);
								}
							}
							break;
						}

						else if (cch.find("action|dialog_return\ndialog_name|3898\nbuttonClicked|") != string::npos || cch == "action|dialog_return\ndialog_name|zurgery_back\nbuttonClicked|53785\n\n" || cch == "action|dialog_return\ndialog_name|zurgery_purchase\nbuttonClicked|chc4_1\n\n" || cch == "action|dialog_return\ndialog_name|wolf_back\nbuttonClicked|53785\n\n" || cch == "action|dialog_return\ndialog_name|wolf_purchase\nbuttonClicked|chc5_1\n\n" || cch == "action|dialog_return\ndialog_name|zombie_back\nbuttonClicked|53785\n\n") {
							string btn = cch.substr(52, cch.length() - 52).c_str();
							bool fail = false;
							if (cch == "action|dialog_return\ndialog_name|zurgery_back\nbuttonClicked|53785\n\n" || cch == "action|dialog_return\ndialog_name|wolf_back\nbuttonClicked|53785\n\n" || cch == "action|dialog_return\ndialog_name|zombie_back\nbuttonClicked|53785\n\n") btn = "53785";
							if (cch == "action|dialog_return\ndialog_name|zurgery_purchase\nbuttonClicked|chc4_1\n\n") btn = "chc4_1";
							if (cch == "action|dialog_return\ndialog_name|wolf_purchase\nbuttonClicked|chc5_1\n\n") btn = "chc5_1";
							replace_str(btn, "\n", "");
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							if (btn == "12345") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wCrazy Jim's Quest Emporium``|left|3902|\nadd_textbox|HEEEEYYY there Growtopian! I'm Crazy Jim, and my quests are so crazy they're KERRRRAAAAZZY!! And that is clearly very crazy, so please, be cautious around them. What can I do ya for, partner?|left|\nadd_button|chc1_1|Daily Quest|noflags|0|0|\nadd_button|gtoken_quests|`oToken Quests``|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
							else if (btn == "53785") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man``|left|4358|\nadd_textbox|It is I, Sales-Man, savior of the wealthy! Let me rescue you from your riches. What would you like to buy today?|left|\nadd_button|chc4_1|Surgery Items|noflags|0|0|\nadd_button|chc5_1|Wolfworld Items|noflags|0|0|\nadd_button|chc3_1|Zombie Defense Items|noflags|0|0|\nadd_button|chc2_1|Blue Gem Lock|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
							else if (btn == "chc1_1") {
								if (!pInfo(peer)->AlreadyDailyQ) {
									int haveitem1 = 0, haveitem2 = 0, received = 0;
									modify_inventory(peer, item1, haveitem1);
									modify_inventory(peer, item2, haveitem2);
									if (haveitem1 >= item1c && haveitem2 >= item2c) received = 1;
									if (haveitem1 >= item1c && haveitem2 >= item2c && has_playmod(pInfo(peer), "Delectable") && rand() % 50 + 1 < 25) received = 2;
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wCrazy Jim's Daily Quest``|left|3902|\nadd_textbox|I guess some people call me Crazy Jim because I'm a bit of a hoarder. But I'm very particular about what I want! And today, what I want is this:|left|\nadd_label_with_icon|small|`2" + to_string(item1c) + " " + items[item1].name + "|left|" + to_string(item1) + "|\nadd_smalltext|and|left|\nadd_label_with_icon|small|`2" + to_string(item2c) + " " + items[item2].name + "|left|" + to_string(item2) + "|\nadd_spacer|small|\nadd_smalltext|You shove all that through the phone (it works, I've tried it), and I will hand you one of the `2Growtokens`` from my personal collection!  But hurry, this offer is only good until midnight, and only one `2Growtoken`` per person!|left|\nadd_spacer|small|\nadd_smalltext|`6(You have " + to_string(haveitem1) + " " + items[item1].name + " and " + to_string(haveitem2) + " " + items[item2].name + ")``|left|\nadd_spacer|small|" + (received == 1 ? "\nadd_button|turnin|Turn in items|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_button|12345|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
								}
								else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wCrazy Jim's Daily Quest``|left|3902|\nadd_textbox|You've already completed my Daily Quest for today! Call me back after midnight to hear about my next cravings.|left|\nadd_button|12345|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
							}
							else if (btn == "turnin") {
								if (!pInfo(peer)->AlreadyDailyQ) {
									int haveitem1 = 0, haveitem2 = 0, received = 0, remove = -1, remove2 = -1, giveitem = 1;
									modify_inventory(peer, item1, haveitem1);
									modify_inventory(peer, item2, haveitem2);
									if (rand() % 100 + 1 < 25 and has_playmod(pInfo(peer), "Delectable") and haveitem1 >= item1c and haveitem2 >= item2c) received = 2;
									else if (haveitem1 >= item1c && haveitem2 >= item2c) received = 1;
									int giveToken = received;
									if (received != 0) {
										pInfo(peer)->AlreadyDailyQ = true;
										modify_inventory(peer, item1, remove *= item1c);
										modify_inventory(peer, item2, remove2 *= item2c);
										modify_inventory(peer, 1486, giveToken);
										{
											{
												string name_ = pInfo(peer)->world;
												vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
												if (p != worlds.end()) {
													World* world_ = &worlds[p - worlds.begin()];
													PlayerMoving data_{};
													data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
													data_.packetType = 19, data_.plantingTree = 500;
													data_.punchX = 1486, data_.punchY = pInfo(peer)->netID;
													int32_t to_netid = pInfo(peer)->netID;
													BYTE* raw = packPlayerMoving(&data_);
													raw[3] = 5;
													memcpy(raw + 8, &to_netid, 4);
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
														if (pInfo(currentPeer)->world == world_->name) {
															gamepacket_t p3;
															p3.Insert("OnParticleEffect");
															p3.Insert(198);
															p3.Insert((float)pInfo(peer)->x + 10, (float)pInfo(peer)->y + 16);
															p3.CreatePacket(currentPeer);
															send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
														}
													}
													delete[] raw;
												}
											}
											gamepacket_t p, p4;
											p.Insert("OnConsoleMessage");
											p.Insert("[`6You jammed " + to_string(item1c) + " " + items[item1].name + " and " + to_string(item2c) + " " + items[item2].name + " into the phone, and " + to_string(received) + " `2Growtoken`` popped out!``]");
											p4.Insert("OnTalkBubble");
											p4.Insert(pInfo(peer)->netID);
											p4.Insert("Thanks, pardner! Have " + to_string(received) + " `2Growtoken`w!");
											p4.Insert(0), p4.Insert(0);
											p.CreatePacket(peer), p4.CreatePacket(peer);
										}
									}
								}
								else {
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wCrazy Jim's Daily Quest``|left|3902|\nadd_textbox|You've already completed my Daily Quest for today! Call me back after midnight to hear about my next cravings.|left|\nadd_button|12345|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
									p.CreatePacket(peer);
								}
							}
							else if (btn == "gtoken_quests") {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wToken Quests|left|1486|\n"
									"add_spacer|mid|\n"
									"add_label_with_icon|small|`oHarvest Xp `0" + (pInfo(peer)->harvest_quest >= 500 ? "`o(`w500`o/`w500`o)" : "`o(`w" + to_string(pInfo(peer)->harvest_quest) + "`o/`w500`o)") + "|left|898|\n"
									"add_smalltext|Do you know harvest system how is work? You don't need tractor or sorrow. Because you have a hands!..|left|\n"
									"add_smalltext|Example: When you punch on a ready tree. It gonna drop some items on it. Because its ready!!..|left|\n"
									"add_smalltext|When you punch one tree you get 1 point of harvest point. If harvest point is 500. You can collect your 5 Growtoken.|left|\n"
									"" + (pInfo(peer)->harvest_quest >= 500 ? "add_button|clc_5|`oCollect 5 GrowToken|noflags|0|0|\n" : "add_progress_bar||small|`oHarvest|" + to_string(pInfo(peer)->harvest_quest) + "|500|`o(`w" + to_string(pInfo(peer)->harvest_quest) + "`o/`w500`o)|\n") + ""
									"add_spacer|mid|\n"

									"add_label_with_icon|small|`oFishing Xp `0" + (pInfo(peer)->fishing_quest >= 30 ? "`o(`w30`o/`w30`o)" : "`o(`w" + to_string(pInfo(peer)->fishing_quest) + "`o/`w30`o)") + "|left|2912|\n"
									"add_smalltext|Do you know fishing system how is work? You need a fishing rod for it.|left|\n"
									"add_smalltext|Example: Just take a one water and put on empty place. Then take your bait and fishing rod. Just click the bait on water. BOOMM!.. You got it.|left|\n"
									"" + (pInfo(peer)->fishing_quest >= 30 ? "add_button|clc_5|`oCollect 5 GrowToken|noflags|0|0|\n" : "add_progress_bar||small|`oFishing|" + to_string(pInfo(peer)->fishing_quest) + "|30|`o(`w" + to_string(pInfo(peer)->fishing_quest) + "`o/`w30`o)|\n") + ""
									"add_spacer|mid|\n"
									"add_button|12345|Back|noflags|0|0|\n"
									"end_dialog|3898|Hang Up||\n"
									"add_quick_exit|\n");
								p.CreatePacket(peer);
							}
							else if (btn == "clc_5") {

								int c_ = 5;
								if (pInfo(peer)->harvest_quest < 500 and pInfo(peer)->fishing_quest < 30) continue;

								if (modify_inventory(peer, 1486, c_) == 0) {
									if (pInfo(peer)->harvest_quest >= 500) pInfo(peer)->harvest_quest = 0;
									else if (pInfo(peer)->fishing_quest >= 30) pInfo(peer)->fishing_quest = 0;

									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`6You collected 5x Growtokens!");
									p.CreatePacket(peer);
									tokenquests_dialog(peer);
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`4You dont have enough enventory.");
									p.CreatePacket(peer);
									break;
								}
							}
							else if (btn == "chc2_1") {
								int c_ = 0;
								modify_inventory(peer, 1796, c_);
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlue Gem Lock``|left|7188|\nadd_textbox|Excellent! I'm happy to sell you a Blue Gem Lock in exchange for 100 Diamond Lock..|left|\nadd_smalltext|`6You have " + to_string(c_) + " Diamond Lock.``|left|" + (c_ >= 100 ? "\nadd_button|chc2_2_1|Thank you!|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
							}
							else if (btn == "chc2_2_1") {
								int c7188 = 0, c1796 = 0, additem = 0;
								modify_inventory(peer, 1796, c1796);
								if (c1796 < 100) continue;
								modify_inventory(peer, 7188, c7188);
								if (c7188 >= 200) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("You don't have room in your backpack!");
									p.Insert(0), p.Insert(1);
									p.CreatePacket(peer);
									{
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You don't have room in your backpack!");
										p.CreatePacket(peer);
									}
									fail = true;
									continue;
								}
								if (c1796 >= 100) {
									if (get_free_slots(pInfo(peer)) >= 2) {
										int cz_ = 1;
										if (modify_inventory(peer, 1796, additem = -100) == 0) {
											modify_inventory(peer, 7188, additem = 1);
											{
												PlayerMoving data_{};
												data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
												data_.packetType = 19, data_.plantingTree = 500;
												data_.punchX = 7188, data_.punchY = pInfo(peer)->netID;
												int32_t to_netid = pInfo(peer)->netID;
												BYTE* raw = packPlayerMoving(&data_);
												raw[3] = 5;
												memcpy(raw + 8, &to_netid, 4);
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
													if (pInfo(currentPeer)->world == pInfo(peer)->world) {
														send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													}
												}
												delete[] raw;
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("[`6You spent 100 Diamond Lock to get 1 Blue Gem Lock``]");
												p.CreatePacket(peer);
											}
										}
										else {
											fail = true;
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You don't have room in your backpack!");
											p.Insert(0), p.Insert(1);
											p.CreatePacket(peer);
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You don't have room in your backpack!");
												p.CreatePacket(peer);
											}
											continue;
										}
										int c_ = 0;
										modify_inventory(peer, 1796, c_);
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlue Gem Lock``|left|7188|\nadd_textbox|Excellent! I'm happy to sell you a Blue Gem Lock in exchange for 100 Diamond Lock..|left|\nadd_smalltext|`6You have " + to_string(c_) + " Diamond Lock.``|left|" + (c_ >= 100 ? "\nadd_button|chc2_2_1|Thank you!|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
									}
									else {
										fail = true;
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You don't have room in your backpack!");
										p.Insert(0), p.Insert(1);
										p.CreatePacket(peer);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("You don't have room in your backpack!");
											p.CreatePacket(peer);
										}
										continue;
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("You don't have enough inventory space!");
									p.CreatePacket(peer);
									fail = true;
								}
							}
							else if (btn == "chc3_1") {
								int zombie_brain = 0, pile = 0, total = 0;
								modify_inventory(peer, 4450, zombie_brain);
								modify_inventory(peer, 4452, pile);
								total += zombie_brain + (pile * 100);
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man: Zombie Defense``|left|4358|\nadd_textbox|Excellent! I'm happy to sell you Zombie Defense supplies in exchange for Zombie Brains.|left|\nadd_smalltext|You currently have " + setGems(total) + " Zombie Brains.|left|\nadd_spacer|small|\ntext_scaling_string|5,000ZB|\n" + zombie_list + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|53785|Back|noflags|0|0|\nend_dialog|zombie_back|Hang Up||\n");
								p.CreatePacket(peer);
							}
							else if (btn == "chc4_1") {
								int zombie_brain = 0, pile = 0, total = 0;
								modify_inventory(peer, 4298, zombie_brain);
								modify_inventory(peer, 4300, pile);
								total += zombie_brain + (pile * 100);
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man: Surgery``|left|4358|\nadd_textbox|Excellent! I'm happy to sell you rare and precious Surgery prizes in exchange for Caduceus medals.|left|\nadd_smalltext|You currently have " + setGems(total) + " Caducei.|left|\nadd_spacer|small|\ntext_scaling_string|50,000ZB|\n" + surgery_list + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|53785|Back|noflags|0|0|\nend_dialog|zurgery_back|Hang Up||\n");
								p.CreatePacket(peer);
							}
							/*else if (btn == "chc5_1") {
								int zombie_brain = 0, pile = 0, total = 0;
								modify_inventory(peer, 4354, zombie_brain);
								modify_inventory(peer, 4356, pile);
								total += zombie_brain + (pile * 100);
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man: Wolfworld``|left|4358|\nadd_textbox|Excellent! I'm happy to sell you rare and precious Woflworld prizes in exchange for Wolf Tickets.|left|\nadd_smalltext|You currently have " + setGems(total) + " Wolf Tickets.|left|\nadd_spacer|small|\ntext_scaling_string|50,000WT|\n" + wolf_list + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|53785|Back|noflags|0|0|\nend_dialog|wolf_back|Hang Up||\n");
								p.CreatePacket(peer);
							}*/
							else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wDisconnected``|left|774|\nadd_textbox|The number you have tried to reach is disconnected. Please check yourself before you wreck yourself.|left|\nend_dialog|3898|Hang Up||\n");
							if (btn != "turnin" && fail == false) p.CreatePacket(peer);
							break;
							}


						else if (cch.find("action|dialog_return\ndialog_name|socialportal\nbuttonClicked|gtoken_quests") != string::npos) {
							tokenquests_dialog(peer);
						}
						else if (cch.find("action|dialog_return\ndialog_name|socialportal\nbuttonClicked|backpacksystem") != string::npos) {
							backpack_show(peer);
						}
						else if (cch.find("action|dialog_return\ndialog_name|popup\nbuttonClicked|autofarm_menu") != string::npos) {
							autofarm_dialog(peer);
						}
						else if (cch.find("action|dialog_return\ndialog_name|autofarm_dialog\nbuttonClicked|autofarm") != string::npos) {

							bool nocip_0 = atoi(explode("\n", explode("autofarmsss|", cch)[1])[0].c_str());

							if (nocip_0) pInfo(peer)->autofarm = true;
							else pInfo(peer)->autofarm = false;

							gamepacket_t p;
							p.Insert("OnTextOverlay"), p.Insert("Saved Autofarm Settings!"), p.CreatePacket(peer);
						}
						else if (cch.find("action|dialog_return\ndialog_name|autofarm_dialog\nauto_farming_item|") != std::string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							int anan = atoi(explode("\n", t_[3])[0].c_str());
							if (items[anan].blockType != FOREGROUND && anan != 5640 && anan != 9162) {
								gamepacket_t k;
								k.Insert("OnConsoleMessage");
								k.Insert("`4Error! You can farm only blocks!");
								k.CreatePacket(peer);
								break;

							}
							else {
								pInfo(peer)->farmable = atoi(explode("\n", t_[3])[0].c_str());
								gamepacket_t k;
								k.Insert("OnConsoleMessage"), k.Insert("`2Successfully `0selected block!"), k.CreatePacket(peer);
								autofarm_dialog(peer);
								break;
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|leader_") != string::npos) {
							string target = cch.substr(55, cch.length() - 57).c_str();
							int lock = 0, itemcount = 0, itemid = 0, sayi = 0;
							string name = "", names = "";
							int gems = 0, level = 0, adml = 0, bpoi = 0;
							int dl = 0, bgl = 0, inv = 0, ggl = 0;
							int xp = 0;
							string path_ = "players/" + target + "_.json";
							//cout << path_ << endl;
							json j;
							ifstream files(path_, ifstream::binary);
							if (files.fail()) break;
							files >> j;
							adml = j["adminLevel"].get<int>();
							name = j["name"].get<string>();
							gems = j["gems"].get<int>();
							//opc = j["opc"].get<int>();
							xp = j["xp"].get<int>();
							level = j["level"].get<int>();
							//bpoi = j["bpoi"].get<int>();
							//lock += opc / 2;
							//lock += level / 3;
							lock += gems / 20000;
							//lock += bpoi / 500;
							json a_ = j["inv"].get<json>();
							json f_ = j["worlds_owned"].get<json>();
							for (int i_ = 0; i_ < a_.size(); i_++) {
								itemid = a_.at(i_)["i"].get<int>();
								itemcount = a_.at(i_)["c"].get<int>();
								if (itemid == 242) {
									lock += itemcount;
								}
								if (itemid == 1796) {
									lock += itemcount * 100;
									dl += itemcount;
								}
								if (itemid == 7188) {
									lock += itemcount * 10000;
									bgl += itemcount;
								}
								inv++;
							}
							gamepacket_t h;
							h.Insert("OnDialogRequest");
							h.Insert("\nadd_player_info|`0" + name + "``|" + to_string(level) + "|" + to_string(xp) + "|" + to_string(50 * ((level * level) + 2)) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`oAccount net worth: `$" + to_string(lock) + " Locks``|left|242|\nadd_spacer|small|\nadd_label_with_icon|small|`oTotal Gems: `$" + to_string(gems) + "|left|112|\nadd_spacer|small|\nadd_label_with_icon|small|`oTotal Blue Gem Locks: `$" + to_string(bgl) + "|left|7188|\nadd_label_with_icon|small|`oTotal Diamond Locks: `$" + to_string(dl) + "|left|1796|\nadd_spacer|small|\nadd_label_with_icon|small|`oInventory Size: `$" + to_string(inv) + " |left|9412|\nadd_label_with_icon|small|`oTotal Worlds Owned: `$" + to_string(f_.size()) + "|left|1424|\nadd_spacer|small|\nadd_quick_exit|\nend_dialog|socialportal||Back|");
							h.CreatePacket(peer);
						}



						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nitemid|") != string::npos) {
							int item = atoi(cch.substr(57, cch.length() - 57).c_str());
							if (item <= 0 || item >= items.size()) break;
							if (pInfo(peer)->lastwrenchb != 4516 and items[item].untradeable == 1 or item == 1796 || item == 7188 || item == 242 || item == 9770 || item == 10362 || item == 9846 || item == 9772 || item == 5480 or items[item].blockType == BlockTypes::FISH) {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You can't store Untradeable items there!"), p.CreatePacket(peer);
							}
							else if (pInfo(peer)->lastwrenchb == 4516 and items[item].untradeable == 0 or item == 18 || item == 32 || item == 6336 || item == 1424 || item == 1796 || item == 7188 || item == 242 || item == 9770 || item == 10362 || item == 9846 || item == 9772 || item == 5480 || items[item].blockType == BlockTypes::FISH) {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You can't store Tradeable items there!"), p.CreatePacket(peer);
							}
							else {
								int got = 0, receive = 0;
								modify_inventory(peer, item, got);
								if (got == 0) break;
								pInfo(peer)->lastchoosenitem = item;
								gamepacket_t p;
								p.Insert("OnDialogRequest"), p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items[pInfo(peer)->lastwrenchb].name + "``|left|" + to_string(pInfo(peer)->lastwrenchb) + "|\nadd_textbox|You have " + to_string(got) + " " + items[item].name + ". How many to store?|left|\nadd_text_input|itemcount||" + to_string(got) + "|3|\nadd_spacer|small|\nadd_button|do_add|Store Items|noflags|0|0|\nend_dialog|storageboxxtreme|Cancel||\n"), p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|itm") != string::npos) {
							int itemnr = atoi(cch.substr(67, cch.length() - 67).c_str()), itemcount = 0;
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								if (pInfo(peer)->tankIDName == world_->owner_name) {
									for (int i_ = 0; i_ < world_->sbox1.size(); i_++) {
										if (world_->sbox1[i_].x == pInfo(peer)->lastwrenchx and world_->sbox1[i_].y == pInfo(peer)->lastwrenchy) {
											itemcount++;
											if (itemnr == itemcount) {
												pInfo(peer)->lastchoosennr = itemnr;
												gamepacket_t p;
												p.Insert("OnDialogRequest"), p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items[pInfo(peer)->lastwrenchb].name + "``|left|" + to_string(pInfo(peer)->lastwrenchb) + "|\nadd_textbox|You have `w" + to_string(world_->sbox1[i_].count) + " " + items[world_->sbox1[i_].id].name + "`` stored.|left|\nadd_textbox|Withdraw how many?|left|\nadd_text_input|itemcount||" + to_string(world_->sbox1[i_].count) + "|3|\nadd_spacer|small|\nadd_button|do_take|Remove Items|noflags|0|0|\nadd_button|cancel|Back|noflags|0|0|\nend_dialog|storageboxxtreme|Exit||\n"), p.CreatePacket(peer);
											}
										}
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|donation_box_edit\nitemid|") != string::npos) {

							int item = atoi(cch.substr(58, cch.length() - 58).c_str()), got = 0;
							modify_inventory(peer, item, got);
							if (got == 0) break;
							if (items[item].untradeable == 1 || item == 1424 || item == 1796 || item == 7188 || item == 242 || item == 9770 || item == 10362 || item == 9846 || item == 9772 || item == 5480 || items[item].blockType == BlockTypes::FISH) {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("`7[```4You can't place that in the box, you need it!`7]``"), p.CreatePacket(peer);
							}
							else if (items[item].rarity == 1) {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("`7[```4This box only accepts items rarity 2+ or greater`7]``"), p.CreatePacket(peer);
							}
							else {
								pInfo(peer)->lastchoosenitem = item;
								gamepacket_t p;
								p.Insert("OnDialogRequest"), p.Insert("set_default_color|`o\nadd_label_with_icon|big|" + items[item].name + "``|left|" + to_string(item) + "|\nadd_textbox|How many to put in the box as a gift? (Note: You will `4LOSE`` the items you give!)|left|\nadd_text_input|count|Count:|" + to_string(got) + "|5|\nadd_text_input|sign_text|Optional Note:||128|\nadd_spacer|small|\nadd_button|give|`4Give the item(s)``|noflags|0|0|\nadd_spacer|small|\nadd_button|cancel|`wCancel``|noflags|0|0|\nend_dialog|give_item|||\n");
								p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|donation_box_edit\nbuttonClicked|takeall\n") != string::npos) {
							bool took = false, fullinv = false;
							gamepacket_t p3;
							p3.Insert("OnTalkBubble"), p3.Insert(pInfo(peer)->netID);
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) break;
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (!items[block_->fg].donation) break;
								for (int i_ = 0; i_ < block_->donates.size(); i_++) {
									int receive = block_->donates[i_].count;
									if (modify_inventory(peer, block_->donates[i_].item, block_->donates[i_].count) == 0) {
										took = true;
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`7[``" + pInfo(peer)->tankIDName + " receives `5" + to_string(receive) + "`` `w" + items[block_->donates[i_].item].name + "`` from `w" + block_->donates[i_].name + "``, how nice!`7]``");
										block_->donates.erase(block_->donates.begin() + i_);
										i_--;
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											p.CreatePacket(currentPeer);
										}
									}
									else fullinv = true;
								}
								if (block_->donates.size() == 0) {
									WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									PlayerMoving data_{};
									data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
									BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, &block_));
									BYTE* blc = raw + 56;
									form_visual(blc, block_, *world_, peer, false);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
										send_raw(currentPeer, 4, raw, 112 + alloc_(world_, &block_), ENET_PACKET_FLAG_RELIABLE);
									}
									delete[] raw, blc;
								}
							}
							if (fullinv) {
								p3.Insert("I don't have enough room in my backpack to get the item(s) from the box!");
								gamepacket_t p2;
								p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("`2(Couldn't get all of the gifts)``"), p2.CreatePacket(peer);
							}
							else if (took) p3.Insert("`2Box emptied.``");
							p3.CreatePacket(peer);
							break;
						}
						else if (cch == "action|dialog_return\ndialog_name|surge\n") {
							if (pInfo(peer)->lastwrenchb == 4296 || pInfo(peer)->lastwrenchb == 8558) {
								setstats(peer, rand() % 30, "", items[pInfo(peer)->lastwrenchb].name);
								pInfo(peer)->lastwrenchb = 0;
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|give_item\nbuttonClicked|give\n\ncount|") != string::npos) {
							string text = explode("\n", explode("name|", cch)[1])[0];
							int count = atoi(explode("\n", explode("count|", cch)[1])[0].c_str()), got = 0;

							replace_str(text, "\n", "");
							modify_inventory(peer, pInfo(peer)->lastchoosenitem, got);

							if (text.size() > 128 || got <= 0 || count <= 0 || count > items.size()) break;
							if (count > got || items[pInfo(peer)->lastchoosenitem].untradeable == 1 || pInfo(peer)->lastchoosenitem == 1796 || pInfo(peer)->lastchoosenitem == 7188 || pInfo(peer)->lastchoosenitem == 242 || pInfo(peer)->lastchoosenitem == 9770 || pInfo(peer)->lastchoosenitem == 10362 || pInfo(peer)->lastchoosenitem == 9846 || pInfo(peer)->lastchoosenitem == 9772 || pInfo(peer)->lastchoosenitem == 5480 || pInfo(peer)->lastchoosenitem == 1424 || items[pInfo(peer)->lastchoosenitem].blockType == BlockTypes::FISH) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								if (count > got) p.Insert("You don't have that to give!");
								else p.Insert("`7[```4You can't place that in the box, you need it!`7]``");
								p.CreatePacket(peer);
							}
							else {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									if (!items[block_->fg].donation) break;
									Donate donate_{};
									donate_.item = pInfo(peer)->lastchoosenitem, donate_.count = count, donate_.name = pInfo(peer)->tankIDName, donate_.text = text;
									block_->donates.push_back(donate_);
									{
										PlayerMoving data_{};
										data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
										BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, block_));
										BYTE* blc = raw + 56;
										form_visual(blc, *block_, *world_, peer, false, true);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 112 + alloc_(world_, block_), ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw, blc;
									}
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("`7[```5[```w" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + "`` places `5" + to_string(count) + "`` `2" + items[pInfo(peer)->lastchoosenitem].name + "`` into the " + items[pInfo(peer)->lastwrenchb].name + "`5]```7]``");
											p.Insert(0);
											p.CreatePacket(currentPeer);
										}
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("`7[```5[```w" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + "`` places `5" + to_string(count) + "`` `2" + items[pInfo(peer)->lastchoosenitem].name + "`` into the " + items[pInfo(peer)->lastwrenchb].name + "`5]```7]``");
											p.CreatePacket(currentPeer);
										}
									}
									modify_inventory(peer, pInfo(peer)->lastchoosenitem, count *= -1);

									string messages = pInfo(peer)->tankIDName + " donated " + to_string(count) + " " + items[pInfo(peer)->lastchoosenitem].name + " in " + pInfo(peer)->world;
									ofstream file("logs/donation.txt", ios::app);
									if (file.is_open()) {
										auto now = time(nullptr);
										file << "" << getDate() << " " << messages << "\n";
									}
									file.close();
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|cancel") != string::npos) {
							edit_tile(peer, pInfo(peer)->lastwrenchx, pInfo(peer)->lastwrenchy, 32);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|do_take\n\nitemcount|") != string::npos) {
							int itemnr = pInfo(peer)->lastchoosennr, countofremoval = atoi(cch.substr(83, cch.length() - 83).c_str()), removed = 0, itemcount = 0;
							removed = countofremoval;
							if (countofremoval <= 0) break;
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								if (pInfo(peer)->tankIDName == world_->owner_name) {
									for (int i_ = 0; i_ < world_->sbox1.size(); i_++) {
										if (world_->sbox1[i_].x == pInfo(peer)->lastwrenchx and world_->sbox1[i_].y == pInfo(peer)->lastwrenchy) {
											itemcount++;
											if (itemnr == itemcount and countofremoval < world_->sbox1[i_].count) {
												if (world_->sbox1[i_].count <= 0) break;
												world_->sbox1[i_].count -= removed;
												if (modify_inventory(peer, world_->sbox1[i_].id, countofremoval) == 0) {
													gamepacket_t p, p2;
													p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("Removed `w" + to_string(removed) + " " + items[world_->sbox1[i_].id].name + "`` in " + items[pInfo(peer)->lastwrenchb].name + "."), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
													p2.Insert("OnConsoleMessage"), p2.Insert("Removed `w" + to_string(removed) + " " + items[world_->sbox1[i_].id].name + "`` in the " + items[pInfo(peer)->lastwrenchb].name + "."), p2.CreatePacket(peer);
													PlayerMoving data_{};
													data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16, data_.packetType = 19, data_.plantingTree = 500, data_.punchX = world_->sbox1[i_].id, data_.punchY = pInfo(peer)->netID;
													int32_t to_netid = pInfo(peer)->netID;
													BYTE* raw = packPlayerMoving(&data_);
													raw[3] = 5;
													memcpy(raw + 8, &to_netid, 4);
													send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													delete[] raw;
													i_ = world_->sbox1.size();
												}
											}
											else if (itemnr == itemcount and world_->sbox1[i_].count == countofremoval) {
												if (world_->sbox1[i_].count <= 0) break;
												if (modify_inventory(peer, world_->sbox1[i_].id, countofremoval) == 0) {
													gamepacket_t p, p2;
													p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("Removed `w" + to_string(removed) + " " + items[world_->sbox1[i_].id].name + "`` in " + items[pInfo(peer)->lastwrenchb].name + "."), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
													p2.Insert("OnConsoleMessage"), p2.Insert("Removed `w" + to_string(removed) + " " + items[world_->sbox1[i_].id].name + "`` in the " + items[pInfo(peer)->lastwrenchb].name + "."), p2.CreatePacket(peer);
													PlayerMoving data_{};
													data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
													data_.packetType = 19, data_.plantingTree = 500;
													data_.punchX = world_->sbox1[i_].id, data_.punchY = pInfo(peer)->netID;
													int32_t to_netid = pInfo(peer)->netID;
													BYTE* raw = packPlayerMoving(&data_);
													raw[3] = 5;
													memcpy(raw + 8, &to_netid, 4);
													send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													delete[] raw;
													world_->sbox1.erase(world_->sbox1.begin() + i_);
													i_ = world_->sbox1.size();
												}
											}
										}
									}
								}
							}
							break;
						}

						else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|trans_") != string::npos) {
							int item = atoi(cch.substr(54, cch.length() - 54).c_str());
							if (item <= 0 || item >= items.size()) break;
							if (item == 256) {
								gamepacket_t p(0, pInfo(peer)->netID);
								p.Insert("OnFlagMay2019"), p.Insert(256);
								pInfo(peer)->flagmay = 256;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
									if (pInfo(peer)->world == pInfo(currentPeer)->world) p.CreatePacket(currentPeer);
								}
							}
							int got = 0;
							modify_inventory(peer, item, got);
							if (got == 0) break;
							if (items[item].flagmay == 256) break;
							gamepacket_t p(0, pInfo(peer)->netID);
							pInfo(peer)->flagmay = items[item].flagmay;
							p.Insert("OnFlagMay2019"), p.Insert(items[item].flagmay);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (pInfo(peer)->world == pInfo(currentPeer)->world) p.CreatePacket(currentPeer);
							}
							break;
						}
					    else if (cch.find("action|dialog_return\ndialog_name|view_inventory\nbuttonClicked|") != string::npos) {
							if (CheckConfigS(clist, pInfo(peer)->tankIDName)) {
								int item = atoi(cch.substr(62, cch.length() - 62).c_str());
								pInfo(peer)->choosenitem = item;
								if (item <= 0 || item > items.size()) break;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
										int got = 0;
										modify_inventory(currentPeer, pInfo(peer)->choosenitem, got);
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Take`` `w" + items[pInfo(peer)->choosenitem].name + " from`` `#" + pInfo(currentPeer)->tankIDName + "``|left|" + to_string(pInfo(peer)->choosenitem) + "|\nadd_textbox|How many to `4take``? (player has " + to_string(got) + ")|left|\nadd_text_input|count||" + to_string(got) + "|5|\nend_dialog|take_item|Cancel|OK|");
										p.CreatePacket(peer);
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|take_item\ncount|") != string::npos) {
							if (CheckConfigS(clist, pInfo(peer)->tankIDName)) {
								int count = atoi(cch.substr(49, cch.length() - 49).c_str()), receive = atoi(cch.substr(49, cch.length() - 49).c_str());
								int remove = count * -1;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
										if (count <= 0 || count > 200) break;
										if (modify_inventory(peer, pInfo(peer)->choosenitem, count) == 0) {
											int total = 0;
											modify_inventory(currentPeer, pInfo(peer)->choosenitem, total += remove);
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("Collected `w" + to_string(receive) + " " + items[pInfo(peer)->choosenitem].name + "``." + (items[pInfo(peer)->choosenitem].rarity > 363 ? "" : " Rarity: `w" + to_string(items[pInfo(peer)->choosenitem].rarity) + "``") + "");
											p.CreatePacket(peer);
											//send_logs(pInfo(peer)->tankIDName + " took " + to_string(receive) + " " + items[pInfo(peer)->choosenitem].name + " from " + pInfo(currentPeer)->tankIDName, "Inventory Steal");
											//send_logs("player: `" + pInfo(peer)->tankIDName + "` level: " + to_string(pInfo(peer)->level) + " (dropped item) collected `" + to_string(receive) + "` Blue gem locks " " in: [" + pInfo(peer)->world + "]", "1046804223515443210/Wsx7OIq4LGLXpysJ7aP_Fsg0qp0ZxcTw0zwL0c7foFXN-tlqRdU5PdenG858mHnDKNuS");
										}

									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|bulletin_edit\nbuttonClicked|clear\n") != string::npos) {
							{
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(items[pInfo(peer)->lastwrenchb].blockType == BlockTypes::MAILBOX ? "`2Mailbox emptied.``" : "`2Text cleared.``"), p.Insert(0), p.Insert(0), p.CreatePacket(peer);
							}
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								for (int i_ = 0; i_ < world_->bulletin.size(); i_++) {
									if (world_->bulletin[i_].x == pInfo(peer)->lastwrenchx and world_->bulletin[i_].y == pInfo(peer)->lastwrenchy) {
										world_->bulletin.erase(world_->bulletin.begin() + i_);
										i_--;
									}
								}
								if (items[pInfo(peer)->lastwrenchb].blockType == BlockTypes::MAILBOX) {
									WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									PlayerMoving data_{};
									data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
									BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, &block_));
									BYTE* blc = raw + 56;
									form_visual(blc, block_, *world_, peer, false);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
										send_raw(currentPeer, 4, raw, 112 + alloc_(world_, &block_), ENET_PACKET_FLAG_RELIABLE);
									}
									delete[] raw, blc;
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|remove_bulletin") != string::npos) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								int letter = 0;
								World* world_ = &worlds[p - worlds.begin()];
								for (int i_ = 0; i_ < world_->bulletin.size(); i_++) {
									if (world_->bulletin[i_].x == pInfo(peer)->lastwrenchx and world_->bulletin[i_].y == pInfo(peer)->lastwrenchy) {
										letter++;
										if (pInfo(peer)->lastchoosennr == letter) {
											world_->bulletin.erase(world_->bulletin.begin() + i_);
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("`2Bulletin removed.``");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
										}
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|bulletin_edit\nbuttonClicked|edit") != string::npos) {
							int count = atoi(cch.substr(65, cch.length() - 65).c_str()), letter = 0;
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								for (int i_ = 0; i_ < world_->bulletin.size(); i_++) {
									if (world_->bulletin[i_].x == pInfo(peer)->lastwrenchx and world_->bulletin[i_].y == pInfo(peer)->lastwrenchy) {
										letter++;
										if (count == letter) {
											pInfo(peer)->lastchoosennr = count;
											gamepacket_t p;
											p.Insert("OnDialogRequest");
											p.Insert("set_default_color|`o\nadd_label_with_icon|small|Remove`` \"`w" + world_->bulletin[i_].text + "\"`` from your board?|left|" + to_string(pInfo(peer)->lastwrenchb) + "|\nend_dialog|remove_bulletin|Cancel|OK|");
											p.CreatePacket(peer);
										}
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|bulletin_edit\nbuttonClicked|send\n\nsign_text|") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							string text = explode("\n", t_[4])[0].c_str();
							replace_str(text, "\n", "");
							if (text.length() <= 2 || text.length() >= 100) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("That's not interesting enough to post.");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(peer);
							}
							else {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									{
										World* world_ = &worlds[p - worlds.begin()];
										int letter = 0;
										for (int i_ = 0; i_ < world_->bulletin.size(); i_++) if (world_->bulletin[i_].x == pInfo(peer)->lastwrenchx and world_->bulletin[i_].y == pInfo(peer)->lastwrenchy) letter++;
										if (letter == 21) world_->bulletin.erase(world_->bulletin.begin() + 0);
										WorldBulletin bulletin_{};
										bulletin_.x = pInfo(peer)->lastwrenchx, bulletin_.y = pInfo(peer)->lastwrenchy;
										if (pInfo(peer)->adminLevel != 0) bulletin_.name = (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``";
										else bulletin_.name = "`0" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + "``";
										bulletin_.text = text;
										world_->bulletin.push_back(bulletin_);
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert(items[pInfo(peer)->lastwrenchb].blockType == BlockTypes::MAILBOX ? "`2You place your letter in the mailbox.``" : "`2Bulletin posted.``");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										if (items[pInfo(peer)->lastwrenchb].blockType == BlockTypes::MAILBOX) {
											WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
											PlayerMoving data_{};
											data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
											BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, &block_));
											BYTE* blc = raw + 56;
											form_visual(blc, block_, *world_, peer, false, true);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 112 + alloc_(world_, &block_), ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw, blc;
										}
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|b_claimreward") != string::npos) {
							int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
							vector<int> list{ 6896, 5212, 6948, 1068, 1966, 1836, 5080, 10754, 1874, 6946 };
							if (reward <= 0 || reward > list.size()) break;
							if (list[reward - 1] == 1068) count = 10;
							if (find(pInfo(peer)->bb_p.begin(), pInfo(peer)->bb_p.end(), lvl = reward * 5) == pInfo(peer)->bb_p.end()) {
								if (pInfo(peer)->bb_lvl >= lvl) {
									if (modify_inventory(peer, list[reward - 1], count) == 0) {
										pInfo(peer)->bb_p.push_back(lvl);
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received your Builder Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										{
											PlayerMoving data_{};
											data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
											int32_t to_netid = pInfo(peer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											memcpy(raw + 8, &to_netid, 4);
											send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[] raw;
										}
										builder_reward_show(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have full inventory space!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
							}
							break;
							}						else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|s_claimreward") != string::npos) {
							int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
							vector<int> list{ 6900, 6982, 6212, 3172, 9068, 6912, 10836, 3130, 8284 };
							if (reward <= 0 || reward > list.size()) break;
							if (list[reward - 1] == 10836) count = 100;
							if (list[reward - 1] == 6212) count = 50;
							if (list[reward - 1] == 3172 || list[reward - 1] == 6912) count = 25;
							if (find(pInfo(peer)->surg_p.begin(), pInfo(peer)->surg_p.end(), lvl = reward * 5) == pInfo(peer)->surg_p.end()) {
								if (pInfo(peer)->s_lvl >= lvl) {
									if (modify_inventory(peer, list[reward - 1], count) == 0) {
										pInfo(peer)->surg_p.push_back(lvl);
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received your Surgeon Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										{
											PlayerMoving data_{};
											data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
											int32_t to_netid = pInfo(peer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											memcpy(raw + 8, &to_netid, 4);
											send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[] raw;
										}
										surgery_reward_show(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have full inventory space!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
							}
							break;
						}

													else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|s_claimreward") != string::npos) {
							int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
							vector<int> list{ 6900, 6982, 6212, 3172, 9068, 6912, 10836, 3130, 8284 };
							if (reward <= 0 || reward > list.size()) break;
							if (list[reward - 1] == 10836) count = 100;
							if (list[reward - 1] == 6212) count = 50;
							if (list[reward - 1] == 3172 || list[reward - 1] == 6912) count = 25;
							if (find(pInfo(peer)->surg_p.begin(), pInfo(peer)->surg_p.end(), lvl = reward * 5) == pInfo(peer)->surg_p.end()) {
								if (pInfo(peer)->s_lvl >= lvl) {
									if (modify_inventory(peer, list[reward - 1], count) == 0) {
										pInfo(peer)->surg_p.push_back(lvl);
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received your Surgeon Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										{
											PlayerMoving data_{};
											data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
											int32_t to_netid = pInfo(peer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											memcpy(raw + 8, &to_netid, 4);
											send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[] raw;
										}
										surgery_reward_show(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have full inventory space!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
							}
							break;
						}
													else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|s_claimreward") != string::npos) {
														int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
														vector<int> list{ 6900, 6982, 6212, 3172, 9068, 6912, 10836, 3130, 8284 };
														if (reward <= 0 || reward > list.size()) break;
														if (list[reward - 1] == 10836) count = 100;
														if (list[reward - 1] == 6212) count = 50;
														if (list[reward - 1] == 3172 || list[reward - 1] == 6912) count = 25;
														if (find(pInfo(peer)->surg_p.begin(), pInfo(peer)->surg_p.end(), lvl = reward * 5) == pInfo(peer)->surg_p.end()) {
															if (pInfo(peer)->s_lvl >= lvl) {
																if (modify_inventory(peer, list[reward - 1], count) == 0) {
																	pInfo(peer)->surg_p.push_back(lvl);
																	packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
																	{
																		gamepacket_t p;
																		p.Insert("OnTalkBubble");
																		p.Insert(pInfo(peer)->netID);
																		p.Insert("Congratulations! You have received your Surgeon Reward!");
																		p.Insert(0), p.Insert(0);
																		p.CreatePacket(peer);
																	}
																	PlayerMoving data_{};
																	data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
																	BYTE* raw = packPlayerMoving(&data_);
																	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																		if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
																		send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																	}
																	delete[] raw;
																	{
																		PlayerMoving data_{};
																		data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
																		int32_t to_netid = pInfo(peer)->netID;
																		BYTE* raw = packPlayerMoving(&data_);
																		raw[3] = 5;
																		memcpy(raw + 8, &to_netid, 4);
																		send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																		delete[] raw;
																	}
																	surgery_reward_show(peer);
																}
																else {
																	gamepacket_t p;
																	p.Insert("OnTalkBubble");
																	p.Insert(pInfo(peer)->netID);
																	p.Insert("You have full inventory space!");
																	p.Insert(0), p.Insert(0);
																	p.CreatePacket(peer);
																}
															}
														}
														break;
														}
													else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|t_claimreward") != string::npos) {
														int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
														vector<int> list{ 98, 228, 1746, 1778, 1830, 5078, 1966, 6948, 6946, 4956 };
														if (reward <= 0 || reward > list.size()) break;
														if (list[reward - 1] == 228 || list[reward - 1] == 1746 || list[reward - 1] == 1778) count = 200;
														if (find(pInfo(peer)->t_p.begin(), pInfo(peer)->t_p.end(), lvl = reward * 5) == pInfo(peer)->t_p.end()) {
															if (pInfo(peer)->t_lvl >= lvl) {
																if (modify_inventory(peer, list[reward - 1], count) == 0) {
																	pInfo(peer)->t_p.push_back(lvl);
																	packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
																	{
																		gamepacket_t p;
																		p.Insert("OnTalkBubble");
																		p.Insert(pInfo(peer)->netID);
																		p.Insert("Congratulations! You have received your Farmer Reward!");
																		p.Insert(0), p.Insert(0);
																		p.CreatePacket(peer);
																	}
																	PlayerMoving data_{};
																	data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
																	BYTE* raw = packPlayerMoving(&data_);
																	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																		if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
																		send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																	}
																	delete[] raw;
																	{
																		PlayerMoving data_{};
																		data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
																		int32_t to_netid = pInfo(peer)->netID;
																		BYTE* raw = packPlayerMoving(&data_);
																		raw[3] = 5;
																		memcpy(raw + 8, &to_netid, 4);
																		send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																		delete[] raw;
																	}
																	farmer_reward_show(peer);
																}
																else {
																	gamepacket_t p;
																	p.Insert("OnTalkBubble");
																	p.Insert(pInfo(peer)->netID);
																	p.Insert("You have full inventory space!");
																	p.Insert(0), p.Insert(0);
																	p.CreatePacket(peer);
																}
															}
														}
														break;
														}
													else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|p_claimreward") != string::npos) {
														int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
														vector<int> list{ 1008,1044,872,10450,870,5084,876,6950,6952,1674 };
														if (reward <= 0 || reward > list.size()) break;
														if (list[reward - 1] == 1008) count = 5;
														if (list[reward - 1] == 1044) count = 50;
														if (list[reward - 1] == 872) count = 200;
														if (list[reward - 1] == 10450) count = 3;
														if (find(pInfo(peer)->p_p.begin(), pInfo(peer)->p_p.end(), lvl = reward * 5) == pInfo(peer)->p_p.end()) {
															if (pInfo(peer)->p_lvl >= lvl) {
																if (modify_inventory(peer, list[reward - 1], count) == 0) {
																	pInfo(peer)->p_p.push_back(lvl);
																	packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
																	{
																		gamepacket_t p;
																		p.Insert("OnTalkBubble");
																		p.Insert(pInfo(peer)->netID);
																		p.Insert("Congratulations! You have received your Provider Reward!");
																		p.Insert(0), p.Insert(0);
																		p.CreatePacket(peer);
																	}
																	PlayerMoving data_{};
																	data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
																	BYTE* raw = packPlayerMoving(&data_);
																	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																		if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																		if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
																		send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																	}
																	delete[] raw;
																	{
																		PlayerMoving data_{};
																		data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
																		int32_t to_netid = pInfo(peer)->netID;
																		BYTE* raw = packPlayerMoving(&data_);
																		raw[3] = 5;
																		memcpy(raw + 8, &to_netid, 4);
																		send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																		delete[] raw;
																	}
																	provider_reward_show(peer);
																}
																else {
																	gamepacket_t p;
																	p.Insert("OnTalkBubble");
																	p.Insert(pInfo(peer)->netID);
																	p.Insert("You have full inventory space!");
																	p.Insert(0), p.Insert(0);
																	p.CreatePacket(peer);
																}
															}
														}
														break;
														}
													else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|g_claimreward") != string::npos) {
															int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
															vector<int> list{ 4654,262,826,828,9712,3146,2266,5072,5070,9716 };
															if (reward <= 0 || reward > list.size()) break;
															if (list[reward - 1] == 262 || list[reward - 1] == 826 || list[reward - 1] == 828) count = 50;
															if (list[reward - 1] == 3146) count = 10;
															if (find(pInfo(peer)->g_p.begin(), pInfo(peer)->g_p.end(), lvl = reward * 5) == pInfo(peer)->g_p.end()) {
																if (pInfo(peer)->g_lvl >= lvl) {
																	if (modify_inventory(peer, list[reward - 1], count) == 0) {
																		pInfo(peer)->g_p.push_back(lvl);
																		packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
																		{
																			gamepacket_t p;
																			p.Insert("OnTalkBubble");
																			p.Insert(pInfo(peer)->netID);
																			p.Insert("Congratulations! You have received your Geiger Hunting Reward!");
																			p.Insert(0), p.Insert(0);
																			p.CreatePacket(peer);
																		}
																		PlayerMoving data_{};
																		data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
																		BYTE* raw = packPlayerMoving(&data_);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
																			send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																		}
																		delete[] raw;
																		{
																			PlayerMoving data_{};
																			data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
																			int32_t to_netid = pInfo(peer)->netID;
																			BYTE* raw = packPlayerMoving(&data_);
																			raw[3] = 5;
																			memcpy(raw + 8, &to_netid, 4);
																			send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																			delete[] raw;
																		}
																		geiger_reward_show(peer);
																	}
																	else {
																		gamepacket_t p;
																		p.Insert("OnTalkBubble");
																		p.Insert(pInfo(peer)->netID);
																		p.Insert("You have full inventory space!");
																		p.Insert(0), p.Insert(0);
																		p.CreatePacket(peer);
																	}
																}
															}
															break;
															}
													else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|f_claimreward") != string::npos) {
																int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
																vector<int> list{ 3010, 3018, 3020, 3044, 5740, 3042, 3098, 3100, 3040, 10262 };
																if (reward <= 0 || reward > list.size()) break;
																if (list[reward - 1] == 3018) count = 200;
																if (list[reward - 1] == 3020 || list[reward - 1] == 3098) count = 50;
																if (list[reward - 1] == 3044) count = 25;
																if (find(pInfo(peer)->ff_p.begin(), pInfo(peer)->ff_p.end(), lvl = reward * 5) == pInfo(peer)->ff_p.end()) {
																	if (pInfo(peer)->ff_lvl >= lvl) {
																		if (modify_inventory(peer, list[reward - 1], count) == 0) {
																			pInfo(peer)->ff_p.push_back(lvl);
																			packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
																			{
																				gamepacket_t p;
																				p.Insert("OnTalkBubble");
																				p.Insert(pInfo(peer)->netID);
																				p.Insert("Congratulations! You have received your Fishing Reward!");
																				p.Insert(0), p.Insert(0);
																				p.CreatePacket(peer);
																			}
																			PlayerMoving data_{};
																			data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
																			BYTE* raw = packPlayerMoving(&data_);
																			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																				if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
																				send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																			}
																			delete[] raw;
																			{
																				PlayerMoving data_{};
																				data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
																				int32_t to_netid = pInfo(peer)->netID;
																				BYTE* raw = packPlayerMoving(&data_);
																				raw[3] = 5;
																				memcpy(raw + 8, &to_netid, 4);
																				send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																				delete[] raw;
																			}
																			fishing_reward_show(peer);
																		}
																		else {
																			gamepacket_t p;
																			p.Insert("OnTalkBubble");
																			p.Insert(pInfo(peer)->netID);
																			p.Insert("You have full inventory space!");
																			p.Insert(0), p.Insert(0);
																			p.CreatePacket(peer);
																		}
																	}
																}
																break;
																}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|do_add\n\nitemcount|") != string::npos) {
							int count = atoi(cch.substr(82, cch.length() - 82).c_str());
							if (pInfo(peer)->lastchoosenitem <= 0 || pInfo(peer)->lastchoosenitem >= items.size()) break;
							if (pInfo(peer)->lastwrenchb != 4516 and items[pInfo(peer)->lastchoosenitem].untradeable == 1 or pInfo(peer)->lastchoosenitem == 1424 or pInfo(peer)->lastchoosenitem == 1424 || pInfo(peer)->lastchoosenitem == 1796 || pInfo(peer)->lastchoosenitem == 7188 || pInfo(peer)->lastchoosenitem == 242 || pInfo(peer)->lastchoosenitem == 9770 || pInfo(peer)->lastchoosenitem == 10362 || pInfo(peer)->lastchoosenitem == 9846 || pInfo(peer)->lastchoosenitem == 9772 || pInfo(peer)->lastchoosenitem == 5480 || items[pInfo(peer)->lastchoosenitem].blockType == BlockTypes::FISH) {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You can't store Untradeable items there!"), p.CreatePacket(peer);
							}
							else if (pInfo(peer)->lastwrenchb == 4516 and items[pInfo(peer)->lastchoosenitem].untradeable == 0 or pInfo(peer)->lastchoosenitem == 1424 || items[pInfo(peer)->lastchoosenitem].blockType == BlockTypes::FISH || pInfo(peer)->lastchoosenitem == 18 || pInfo(peer)->lastchoosenitem == 32 || pInfo(peer)->lastchoosenitem == 6336 || pInfo(peer)->lastchoosenitem == 9770 || pInfo(peer)->lastchoosenitem == 10362 || pInfo(peer)->lastchoosenitem == 9846 || pInfo(peer)->lastchoosenitem == 9772 || pInfo(peer)->lastchoosenitem == 5480 || pInfo(peer)->lastchoosenitem == 1424) {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You can't store Tradeable items there!"), p.CreatePacket(peer);
							}
							else {
								int got = 0, receive = 0;
								modify_inventory(peer, pInfo(peer)->lastchoosenitem, got);
								if (count <= 0 || count > got) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You don't have that many!"), p.CreatePacket(peer);
								}
								else {
									receive = count * -1;
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
										if (items[pInfo(peer)->lastchoosenitem].untradeable == 1 && block_.fg != 4516) break;
										gamepacket_t p1, p2;
										p1.Insert("OnTalkBubble"), p1.Insert(pInfo(peer)->netID), p1.Insert("Stored `w" + to_string(count) + " " + items[pInfo(peer)->lastchoosenitem].name + "`` in " + items[pInfo(peer)->lastwrenchb].name + "."), p1.CreatePacket(peer);
										p2.Insert("OnConsoleMessage"), p2.Insert("Stored `w" + to_string(count) + " " + items[pInfo(peer)->lastchoosenitem].name + "`` in the " + items[pInfo(peer)->lastwrenchb].name + "."), p2.CreatePacket(peer);
										modify_inventory(peer, pInfo(peer)->lastchoosenitem, receive);

										string messages = pInfo(peer)->tankIDName + " stored " + to_string(count) + " " + items[pInfo(peer)->lastchoosenitem].name + " in " + pInfo(peer)->world;
										ofstream file("logs/storage.txt", ios::app);
										if (file.is_open()) {
											auto now = time(nullptr);
											file << "" << getDate() << " " << messages << "\n";
										}
										file.close();

										bool dublicated = true;
										for (int i_ = 0; i_ < world_->sbox1.size(); i_++) {
											if (dublicated) {
												if (world_->sbox1[i_].x == pInfo(peer)->lastwrenchx and world_->sbox1[i_].y == pInfo(peer)->lastwrenchy and world_->sbox1[i_].id == pInfo(peer)->lastchoosenitem and world_->sbox1[i_].count + count <= 200) {
													world_->sbox1[i_].count += count;
													dublicated = false;
												}
											}
										}
										if (dublicated) {
											WorldSBOX1 sbox1_{};
											sbox1_.x = pInfo(peer)->lastwrenchx, sbox1_.y = pInfo(peer)->lastwrenchy;
											sbox1_.id = pInfo(peer)->lastchoosenitem, sbox1_.count = count;
											world_->sbox1.push_back(sbox1_);
										}
										PlayerMoving data_{};
										data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16, data_.packetType = 19, data_.plantingTree = 500, data_.punchX = pInfo(peer)->lastchoosenitem, data_.punchY = pInfo(peer)->netID;
										int32_t to_netid = pInfo(peer)->netID;
										BYTE* raw = packPlayerMoving(&data_);
										raw[3] = 5;
										memcpy(raw + 8, &to_netid, 4);
										send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										delete[] raw;
										edit_tile(peer, pInfo(peer)->lastwrenchx, pInfo(peer)->lastwrenchy, 32);
									}
								}
							}
							break;
						}
						else if (cch.find("action|drop") != string::npos) {
							string name_ = pInfo(peer)->world;
							if (pInfo(peer)->onTrade) break;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								int id_ = atoi(explode("\n", t_[3])[0].c_str()), c_ = 0;
								if (id_ <= 0 or id_ >= items.size()) break;
								if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 4758) != world_->active_jammers.end()) {
									if (world_->owner_name != (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) and not pInfo(peer)->dev and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end()) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("The Mini-Mod says no dropping items in this world!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
										break;
									}
								}
								if (items[id_].untradeable or id_ == 1424 or id_ == 9770 or id_ == 10362 or id_ == 9846 or id_ == 9772 or id_ == 5480 or id_ == 9770 or id_ == 10362 or id_ == 9846 or id_ == 9772 or id_ == 5480 or id_ == 1424) {
									gamepacket_t p;
									p.Insert("OnTextOverlay");
									p.Insert("You can't drop that.");
									p.CreatePacket(peer);
									break;
								}
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									int a_ = rand() % 12;
									int x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - (a_ + 20) : (pInfo(peer)->x + 20) + a_);
									int y = pInfo(peer)->y + rand() % 16;
									//BlockTypes type_ = FOREGROUND;
									int where_ = (pInfo(peer)->state == 16 ? x / 32 : round((double)x / 32)) + (y / 32 * 100);
									if (where_ < 0 || x < 0 || y < 0 || where_ > 5399) continue;
									WorldBlock* block_ = &world_->blocks[where_];
									if (items[block_->fg].collisionType == 1 || block_->fg == 6 || items[block_->fg].entrance || items[block_->fg].toggleable and is_false_state(world_->blocks[(pInfo(peer)->state == 16 ? x / 32 : round((double)x / 32)) + (y / 32 * 100)], 0x00400000)) {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert(items[block_->fg].blockType == BlockTypes::MAIN_DOOR ? "You can't drop items on the white door." : "You can't drop that here, face somewhere with open space.");
										p.CreatePacket(peer);
										break;
									}
									/*if (static_(type_, items[world_->blocks[((pInfo(peer)->state == 16 ? pInfo(peer)->x - 18 : pInfo(peer)->x + 22) / 32] + ((y / 32) * 100)).fg)) or static_(type_, items[world_->blocks[((pInfo(peer)->state == 16 ? pInfo(peer)->x - 24 : pInfo(peer)->x + 42) / 32] + ((y / 32) * 100)).fg))) {
										if (items[block_->fg].collisionType == 1) {
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert(type_ == MAIN_DOOR ? "You can't drop items on the white door." : "You can't drop that here, face somewhere with open space.");
											p.CreatePacket(peer);
											break;
										}
									}*/
									int count_ = 0;
									bool dublicated = false;
									for (int i_ = 0; i_ < world_->drop.size(); i_++) {
										if (abs(world_->drop[i_].y - y) <= 16 and abs(world_->drop[i_].x - x) <= 16) {
											count_ += 1;
										}
										if (world_->drop[i_].id == id_) if (world_->drop[i_].count < 200) dublicated = true;
									}
									if (!dublicated) {
										if (count_ > 20) {
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert("You can't drop that here, find an emptier spot!");
											p.CreatePacket(peer);
											break;
										}
									}
								}
								modify_inventory(peer, id_, c_);
								string message = pInfo(peer)->tankIDName + " dropped " + to_string(c_) + " " + items[id_].name + " in " + pInfo(peer)->world;
								ofstream file("logs/drop.txt", ios::app);
								if (file.is_open()) {
									auto now = time(nullptr);
									file << "" << getDate() << " " << message << "\n";
								}
								file.close();
								{
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|How many to drop?|left|\nadd_text_input|count||" + to_string(c_) + "|5|\nembed_data|itemID|" + to_string(id_) + "" + (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end()) ? "\nadd_textbox|If you are trying to trade an item with another player, use your wrench on them instead to use our Trade System! `4Dropping items is not safe!``|left|" : "") + "\nend_dialog|drop_item|Cancel|OK|");
									p.CreatePacket(peer);
								}
							}
							break;
						}
						else if (cch.find("action|setRoleIcon") != string::npos || cch.find("action|setRoleSkin") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 3) break;
							string id_ = explode("\n", t_[2])[0];
							if (not isdigit(id_[0])) break;
							uint32_t role_t = atoi(id_.c_str());
							if (cch.find("action|setRoleIcon") != string::npos) {
								if (role_t == 6) pInfo(peer)->roleIcon = role_t;
								else if (role_t == 0 and pInfo(peer)->t_lvl >= 50) pInfo(peer)->roleIcon = role_t;
								else if (role_t == 1 and pInfo(peer)->bb_lvl >= 50) pInfo(peer)->roleIcon = role_t;
								else if (role_t == 2 and pInfo(peer)->titleDoctor) pInfo(peer)->roleIcon = role_t;
								else if (role_t == 3 and pInfo(peer)->titleFisher) pInfo(peer)->roleIcon = role_t;
								else if (role_t == 4 and pInfo(peer)->titleChef) pInfo(peer)->roleIcon = role_t;
								else if (role_t == 5 and pInfo(peer)->titleStartopia) pInfo(peer)->roleIcon = role_t;
							}
							else {
								if (role_t == 6) pInfo(peer)->roleSkin = role_t;
								else if (role_t == 0 and pInfo(peer)->t_lvl >= 50) pInfo(peer)->roleSkin = role_t;
								else if (role_t == 1 and pInfo(peer)->bb_lvl >= 50) pInfo(peer)->roleSkin = role_t;
								else if (role_t == 2 and pInfo(peer)->unlockRoleSkin) pInfo(peer)->roleSkin = role_t;
								else if (role_t == 3 and pInfo(peer)->unlockRoleSkin) pInfo(peer)->roleSkin = role_t;
								else if (role_t == 4 and pInfo(peer)->unlockRoleSkin) pInfo(peer)->roleSkin = role_t;
								else if (role_t == 5 and pInfo(peer)->unlockRoleSkin) pInfo(peer)->roleSkin = role_t;
							}
							gamepacket_t p(0, pInfo(peer)->netID);
							p.Insert("OnSetRoleSkinsAndIcons"), p.Insert(pInfo(peer)->roleSkin), p.Insert(pInfo(peer)->roleIcon), p.Insert(0);
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != pInfo(peer)->world) continue;
								p.CreatePacket(currentPeer);
							}
							break;
						}
						else if (cch.find("action|setSkin") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 3) break;
							string id_ = explode("\n", t_[2])[0];
							if (not isdigit(id_[0])) break;
							char* endptr = NULL;
							unsigned int skin_ = strtoll(id_.c_str(), &endptr, 10);
							if (skin_ == 3531226367 and pInfo(peer)->supp == 2 or skin_ == 4023103999 and pInfo(peer)->supp == 2 or skin_ == 1345519520 and pInfo(peer)->supp == 2 or skin_ == 194314239 and pInfo(peer)->supp == 2) pInfo(peer)->skin = skin_;
							else if (skin_ == 3578898848 and pInfo(peer)->gp or skin_ == 3317842336 and pInfo(peer)->gp) pInfo(peer)->skin = skin_;
							else if (skin_ != 1348237567 and skin_ != 1685231359 and skin_ != 2022356223 and skin_ != 2190853119 and skin_ != 2527912447 and skin_ != 2864971775 and skin_ != 3033464831 and skin_ != 3370516479) {
								if (pInfo(peer)->supp >= 1) {
									if (skin_ != 2749215231 and skin_ != 3317842431 and skin_ != 726390783 and skin_ != 713703935 and skin_ != 3578898943 and skin_ != 4042322175) break;
									else pInfo(peer)->skin = skin_;
								}
								else break;
							}
							else pInfo(peer)->skin = skin_;
							update_clothes(peer);
							break;
						}
						else if (cch.find("action|trash") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							int id_ = atoi(explode("\n", t_[3])[0].c_str()), c_ = 0;
							if (id_ <= 0 or id_ >= items.size()) break;
							gamepacket_t p;
							if (id_ == 18 || id_ == 32 || id_ == 6336 || id_ == 8430) {
								packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
								p.Insert("OnTextOverlay"), p.Insert("You'd be sorry if you lost that!"), p.CreatePacket(peer);
								break;
							}
							modify_inventory(peer, id_, c_); // gauna itemo kieki 
							p.Insert("OnDialogRequest");
							if (pInfo(peer)->supp == 0) p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Trash`` `w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|How many to `4destroy``? (you have " + to_string(c_) + ")|left|\nadd_text_input|count||0|5|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|trash_item|Cancel|OK|");
							else {
								int item = id_, maxgems = 0, maximum_gems = 0;
								if (id_ % 2 != 0) item -= 1;
								maxgems = items[item].max_gems2;
								if (items[item].max_gems3 != 0) maximum_gems = items[item].max_gems3;
								string recycle_text = "0" + (maxgems == 0 ? "" : "-" + to_string(maxgems)) + "";
								if (maximum_gems != 0) recycle_text = to_string(maximum_gems);
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Recycle`` `w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|You will get " + recycle_text + " gems per item.|\nadd_textbox|How many to `4destroy``? (you have " + to_string(c_) + ")|left|\nadd_text_input|count||0|5|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|trash_item|Cancel|OK|");
							}
							p.CreatePacket(peer);
							break;
						}
						else if (cch.find("action|info") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							int id_ = atoi(explode("\n", t_[3])[0].c_str());
							if (id_ >= items.size()) break;
							if (id_ % 2 != 0) p.Insert("set_default_color|`o\nadd_label_with_ele_icon|big|`wAbout " + items[id_].ori_name + "``|left|" + to_string(id_) + "|" + to_string(items[id_ - 1].chi) + "|\nadd_spacer|small|\nadd_textbox|Plant this seed to grow a `0" + items[id_ - 1].ori_name + " Tree.``|left|\nadd_spacer|small|\nadd_textbox|Rarity: `0" + to_string(items[id_].rarity) + "``|left|\nadd_spacer|small|\nend_dialog|continue||OK|\n");
							else {
								string extra_ = "\nadd_textbox|";
								if (id_ == 18) {
									extra_ += "You've punched `w" + to_string(pInfo(peer)->punch_count) + "`` times.";
								} if (items[id_].blockType == BlockTypes::LOCK) {
									extra_ += "A lock makes it so only you (and designated friends) can edit an area.";
								} if (items[id_].r_1 == 0 or items[id_].r_2 == 0) {
									extra_ += "<CR>This item can't be spliced.";
								}
								else {
									extra_ += "Rarity: `w" + to_string(items[id_].rarity) + "``<CR><CR>To grow, plant a `w" + items[id_ + 1].name + "``.   (Or splice a `w" + items[items[id_].r_1].name + "`` with a `w" + items[items[id_].r_2].name + "``)<CR>";
								} if (items[id_].properties & Property_Dropless or items[id_].rarity == 999) {
									extra_ += "<CR>`1This item never drops any seeds.``";
								} if (items[id_].properties & Property_Untradable) {
									extra_ += "<CR>`1This item cannot be dropped or traded.``";
								} if (items[id_].properties & Property_AutoPickup) {
									extra_ += "<CR>`1This item can't be destroyed - smashing it will return it to your backpack if you have room!``";
								} if (items[id_].properties & Property_Wrenchable) {
									extra_ += "<CR>`1This item has special properties you can adjust with the Wrench.``";
								} if (items[id_].properties & Property_MultiFacing) {
									extra_ += "<CR>`1This item can be placed in two directions, depending on the direction you're facing.``";
								} if (items[id_].properties & Property_NoSelf) {
									extra_ += "<CR>`1This item has no use... by itself.``";
								}
								extra_ += "|left|";
								if (extra_ == "\nadd_textbox||left|") extra_ = "";
								else extra_ = replace_str(extra_, "add_textbox|<CR>", "add_textbox|");

								string extra_ore = "";
								if (id_ == 9386) extra_ore = rare_text;
								if (id_ == 7782) extra_ore = rainbow_text;
								p.Insert("set_default_color|`o\nadd_label_with_ele_icon|big|`wAbout " + items[id_].name + "``|left|" + to_string(id_) + "|" + to_string(items[id_].chi) + "|\nadd_spacer|small|\nadd_textbox|" + items[id_].description + "|left|" + (extra_ore != "" ? "\nadd_spacer|small|\nadd_textbox|This item also drops:|left|" + extra_ore : "") + "" + (id_ == 8552 ? "\nadd_spacer|small|\nadd_textbox|Angelic Healings: " + to_string(pInfo(peer)->surgery_done) + "|left|" : "") + "\nadd_spacer|small|" + extra_ + "\nadd_spacer|small|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|continue||OK|\n");
							}
							p.CreatePacket(peer);
							break;
							}
						else if (cch.find("action|wrench") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							int netID = atoi(explode("\n", t_[3])[0].c_str());
							if (pInfo(peer)->netID == netID) {
								send_wrench_self(peer);
							}
							else if (netID == 999931) {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|Growdice NPC|left|456|\nadd_spacer|small||\nadd_smalltext|`0Welcome to `$Growdice NPC``! Choose a game to play.|left|\nadd_spacer|small||\ntext_scaling_string|hooding category|\nadd_button_with_icon|growdice_mines|`0Mines|frame|6994||\nadd_button_with_icon|growdice_coinflip|`0Coin Flip|frame|752||\nadd_button_with_icon|growdice_roulette|`0Roulette|frame|758||\nadd_button_with_icon|growdice_chest|`0Unboxing|frame|13054||\nadd_button_with_icon|bonanza|`0Bonanza|frame|528||\nadd_button_with_icon|growdice_blackjack|`0Blackjack|frame|742||\nadd_button_with_icon||END_LIST|noflags|0|0||\nadd_quick_exit|\nend_dialog|growdice_category|||");
								p.CreatePacket(peer);
							}
							else {
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->netID == netID and pInfo(currentPeer)->world == pInfo(peer)->world) {
										bool already_friends = false, trade_blocked = false, muted = false;
										for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) {
											if (pInfo(peer)->friends[c_].name == pInfo(currentPeer)->tankIDName) {
												already_friends = true;
												if (pInfo(peer)->friends[c_].block_trade)
													trade_blocked = true;
												if (pInfo(peer)->friends[c_].mute)
													muted = true;
												break;
											}
										}
										pInfo(peer)->last_wrenched = pInfo(currentPeer)->tankIDName;
										string name_ = pInfo(peer)->world;
										vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
										if (p != worlds.end()) {
											World* world_ = &worlds[p - worlds.begin()];
											string msg2 = "";
											for (int i = 0; i < to_string(pInfo(currentPeer)->level).length(); i++) msg2 += "?";
											string inv_guild = "";
											string extra = "";
											if (pInfo(currentPeer)->guild_id != 0) {
												uint32_t guild_id = pInfo(currentPeer)->guild_id;
												vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
												if (find_guild != guilds.end()) {
													Guild* guild_information = &guilds[find_guild - guilds.begin()];
													for (GuildMember member_search : guild_information->guild_members) {
														if (member_search.member_name == pInfo(currentPeer)->tankIDName) {
															if (guild_information->guild_mascot[1] == 0 and guild_information->guild_mascot[0] == 0) {
																extra += "\nadd_label_with_icon|small|`9Guild: `2" + guild_information->guild_name + "``|left|5814|\nadd_textbox|`9Rank: `2" + (member_search.role_id == 0 ? "Member" : (member_search.role_id == 1 ? "Elder" : (member_search.role_id == 2 ? "Co-Leader" : "Leader"))) + "``|left|\nadd_spacer|small|";
															}
															else {
																extra += "\nadd_dual_layer_icon_label|small|`9Guild: `2" + guild_information->guild_name + "``|left|" + to_string(guild_information->guild_mascot[1]) + "|" + to_string(guild_information->guild_mascot[0]) + "|1.0|1|\nadd_smalltext|`9Rank: `2" + (member_search.role_id == 0 ? "Member" : (member_search.role_id == 1 ? "Elder" : (member_search.role_id == 2 ? "Co-Leader" : "Leader"))) + "``|left|\nadd_spacer|small|";
															}
															break;
														}
													}
												}
											} if (pInfo(peer)->guild_id != 0 and pInfo(currentPeer)->guild_id == 0) {
												uint32_t guild_id = pInfo(peer)->guild_id;
												vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
												if (find_guild != guilds.end()) {
													Guild* guild_information = &guilds[find_guild - guilds.begin()];
													for (GuildMember member_search : guild_information->guild_members) {
														if (member_search.member_name == pInfo(peer)->tankIDName) {
															if (member_search.role_id >= 1) {
																inv_guild = "\nadd_button|invitetoguild|`2Invite to Guild``|noflags|0|0|";
															}
															break;
														}
													}
												}
											}
											string surgery = "\nadd_spacer|small|\nadd_button|start_surg|`$Perform Surgery``|noflags|0|0|\nadd_smalltext|Surgeon Skill: " + to_string(pInfo(peer)->surgery_skill) + "|left|";
											for (int i_ = 0; i_ < pInfo(currentPeer)->playmods.size(); i_++) if (pInfo(currentPeer)->playmods[i_].id == 89) surgery = "\nadd_spacer|small|\nadd_textbox|Recovering from surgery...|left|";
											if (pInfo(currentPeer)->hospital_bed == false) surgery = "";
											gamepacket_t p;
											p.Insert("OnDialogRequest");
											p.Insert("embed_data|netID|" + to_string(pInfo(peer)->netID) + "\nset_default_color|`o\nadd_label_with_icon|big|" + (pInfo(currentPeer)->mod == 1 || pInfo(currentPeer)->dev == 1 ? pInfo(currentPeer)->name_color : "`0") + "" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->tankIDName) + "`` `0(```2" + (pInfo(currentPeer)->dev == 1 ? msg2 : to_string(pInfo(currentPeer)->level)) + "```0)``|left|18|" + surgery + "\nembed_data|netID|" + to_string(netID) + "\nadd_spacer|small|" + extra + (trade_blocked ? "\nadd_button||`4Trade Blocked``|disabled|||" : "\nadd_button|trade|`wTrade``|noflags|0|0|") + "\nadd_textbox|(No Battle Leash equipped)|left|\nadd_textbox|Your opponent needs a valid license to battle!|left|" + (world_->owner_name == pInfo(peer)->tankIDName or (guild_access(peer, world_->guild_id) or find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) != world_->admins.end()) or pInfo(peer)->dev + pInfo(peer)->mod > 0 ? "\nadd_button|kick|`4Kick``|noflags|0|0|\nadd_button|pull|`5Pull``|noflags|0|0|\nadd_button|worldban|`4World Ban``|noflags|0|0|" : "") + (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1 ? "\nadd_button|punish_view|`5Punish/View``|noflags|0|0|" : "") + inv_guild + (!already_friends ? "\nadd_button|friend_add|`wAdd as friend``|noflags|0|0|" : "") + (muted ? "\nadd_button|unmute_player|`wUnmute``|noflags|0|0|" : (already_friends ? "\nadd_button|mute_player|`wMute``|noflags|0|0|" : "")) + ""/*"\nadd_button|ignore_player|`wIgnore Player``|noflags|0|0|\nadd_button|report_player|`wReport Player``|noflags|0|0|"*/"\nadd_spacer|small|\nend_dialog|popup||Continue|\nadd_quick_exit|");
											p.CreatePacket(peer);
										}
										break;
									}
								}
							}
							break;
						}
						else if (cch.find("action|friends") != string::npos) {
							send_social(peer);
							break;
						}
							/*if (cch.find("action|eventmenu") != string::npos)
							{
								int contri = 0;
								uint32_t guild_id = pInfo(peer)->guild_id;
								vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
								int am = 0, amg = 0, rank = 0;
								std::string fileName = "db/clash/solo/" + pInfo(peer)->tankIDName + "_.json";
								std::ifstream checkFileExistsStream(fileName);
								if (checkFileExistsStream.good()) {
									ifstream ifs("db/clash/solo/" + pInfo(peer)->tankIDName + "_.json");
									if (ifs.is_open()) {
										json j;
										ifs >> j;
										am = j["points"].get<int>();
									}
								}
								vector<pair<int, string>> topPlayer = topclash;
								sort(topPlayer.begin(), topPlayer.end());
								reverse(topPlayer.begin(), topPlayer.end());
								for (uint8_t i = 0; i < topPlayer.size(); i++) {
									string modName = "", username = topPlayer[i].second;
									if (pInfo(peer)->tankIDName == username) rank = i + 1;
								}
								if (pInfo(peer)->guild_id != 0) {
									ifstream ifs("clash/guild/" + to_string(guild_id) + "_.json");
									json j;
									ifs >> j;
									contri = j["points"];
								}
								gamepacket_t ps;
								ps.Insert("OnDialogRequest");
								ps.Insert("\nadd_label_with_icon|big|Fishing Fanatics|left|6012|\nadd_smalltext|`@Rules|\nadd_smalltext|`wGet your anomalizing rods and start fishing, You get points based on lb of the fish you caught!|\nadd_spacer|small|\nadd_textbox|Event Time Left: `2" + timer_h(event_timer) + "|\nadd_spacer|small|\nadd_smalltext|Personal Event Rank: " + to_string(rank) + "    Contribution: " + to_string(am) + "|\nadd_button|guildlb|Personal Event Leaderboard|noflags|0|0|\nadd_button|3290rf8ufw|Back|noflags|0|0|\nadd_quick_exit|\nend_dialog|clashevent|||");
								ps.CreatePacket(peer);
							}
							else if (cch.find("action|dialog_return\ndialog_name|clashevent") != string::npos)
							{
								int contri = 0;
								uint32_t guild_id = pInfo(peer)->guild_id;
								vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
								int am = 0, amg = 0, rank = 0;
								std::string fileName = "db/clash/solo/" + pInfo(peer)->tankIDName + "_.json";
								std::ifstream checkFileExistsStream(fileName);
								if (checkFileExistsStream.good()) {
									ifstream ifs("db/clash/solo/" + pInfo(peer)->tankIDName + "_.json");
									if (ifs.is_open()) {
										json j;
										ifs >> j;
										am = j["points"].get<int>();
									}
								}
								vector<pair<int, string>> topPlayer = topclash;
								sort(topPlayer.begin(), topPlayer.end());
								reverse(topPlayer.begin(), topPlayer.end());
								for (uint8_t i = 0; i < topPlayer.size(); i++) {
									string modName = "", username = topPlayer[i].second;
									if (pInfo(peer)->tankIDName == username) rank = i + 1;
								}
								gamepacket_t ps;
								ps.Insert("OnDialogRequest");
								ps.Insert("\nadd_label_with_icon|big|Fishing Fanatics|left|6012|\nadd_smalltext|`@Rules|\nadd_smalltext|`wGet your anomalizing rods and start fishing, You get points based on lb of the fish you caught!|\nadd_smalltext|`4*The leaderboard updates every 10 minutes.|\nadd_spacer|small|" + top_clash_list + "|\nadd_quick_exit|");
								ps.CreatePacket(peer);
							}*/
						else if (cch == "action|storenavigate\nitem|main\nselection|deposit\n" || cch == "action|storenavigate\nitem|locks\nselection|upgrade_backpack\n" || cch == "action|storenavigate\nitem|main\nselection|bonanza\n" || cch == "action|storenavigate\nitem|main\nselection|calendar\n" || cch == "action|store\nlocation|bottommenu\n" || cch == "action|store\nlocation|gem\n" || cch == "action|store\nlocation|pausemenu\n" || cch == "action|storenavigate\nitem|main\nselection|gems_rain\n") {
							if (cch == "action|store\nlocation|bottommenu\n" || cch == "action|store\nlocation|gem\n" || cch == "action|store\nlocation|pausemenu\n") shop_tab(peer, "tab1");
							if (cch == "action|storenavigate\nitem|main\nselection|gems_rain\n") shop_tab(peer, "tab1_1");
							if (cch == "action|storenavigate\nitem|main\nselection|calendar\n") shop_tab(peer, "tab1_2");
							if (cch == "action|storenavigate\nitem|main\nselection|bonanza\n")	shop_tab(peer, "tab1_3");
							if (cch == "action|storenavigate\nitem|locks\nselection|upgrade_backpack\n") shop_tab(peer, "tab2_1");
							if (cch == "action|storenavigate\nitem|main\nselection|deposit\n") SendCmd(peer, "/deposit", true);
							break;
						}
						else if (cch.find("action|buy") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 3) break;
							string item = explode("\n", t_[2])[0];
							int price = 0, free = get_free_slots(pInfo(peer)), slot = 1, getcount = 0, get_counted = 0, random_pack = 0, token = 0;
							gamepacket_t p2;
							p2.Insert("OnStorePurchaseResult");
							if (item == "main") shop_tab(peer, "tab1");
							else if (item == "locks") shop_tab(peer, "tab2");
							else if (item == "itempack") shop_tab(peer, "tab3");
							else if (item == "bigitems") shop_tab(peer, "tab4");
							else if (item == "weather") shop_tab(peer, "tab5");
							else if (item == "token") shop_tab(peer, "tab6");
							else if (item == "upgrade_backpack") {
								price = 100 * ((((pInfo(peer)->inv.size() - 17) / 10) * ((pInfo(peer)->inv.size() - 17) / 10)) + 1);
								if (price > pInfo(peer)->gems) {
									packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
									p2.Insert("You can't afford `0Upgrade Backpack`` (`w10 Slots``)!  You're `$" + setGems(price - pInfo(peer)->gems) + "`` Gems short.");
								}
								else {
									if (pInfo(peer)->inv.size() < 246) {
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("You've purchased `0Upgrade Backpack`` (`010 Slots``) for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems - price) + "`` Gems left.");
											p.CreatePacket(peer);
										}
										p2.Insert("You've purchased `0Upgrade Backpack (10 Slots)`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems - price) + "`` Gems left.\n\n`5Received: ```0Backpack Upgrade``\n");
										pInfo(peer)->gems -= price;
										{
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											gamepacket_t p;
											p.Insert("OnSetBux");
											p.Insert(pInfo(peer)->gems);
											p.Insert(0);
											p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) {
												p.Insert((float)33796, (float)1, (float)0);
											}
											p.CreatePacket(peer);
										}
										for (int i_ = 0; i_ < 10; i_++) { // default inv dydis
											Items itm_{};
											itm_.id = 0, itm_.count = 0;
											pInfo(peer)->inv.push_back(itm_);
										}
										send_inventory(peer);
										update_clothes(peer);
										shop_tab(peer, "tab2");
									}
								}
								p2.CreatePacket(peer);
							}
							else {
								vector<int> list;
								vector<vector<int>> itemai;
								string item_name = "";
								ifstream ifs("db/shop/-" + item + ".json");
								if (ifs.is_open()) {
									json j;
									ifs >> j;
									price = j["g"].get<int>();
									item_name = j["p"].get<string>();
									if (j.find("itemai") != j.end()) { // mano sistema
										if (pInfo(peer)->gems < price) {
											packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
											p2.Insert("You can't afford `o" + item_name + "``!  You're `$" + setGems(price - pInfo(peer)->gems) + "`` Gems short."), p2.CreatePacket(peer);
											break;
										}
										itemai = j["itemai"].get<vector<vector<int>>>();
										int reik_slots = itemai.size();
										int turi_slots = get_free_slots(pInfo(peer));
										for (vector<int> item_info : itemai) {
											int turi_dabar = 0;
											modify_inventory(peer, item_info[0], turi_dabar);
											if (turi_dabar != 0) reik_slots--;
											if (turi_dabar + item_info[1] > 200) goto fail;
										}
										if (turi_slots < reik_slots) goto fail;
										{
											//if (item == "g4good_Gem_Charity") grow4good(peer, false, "donate_gems", 0);
											//if (item != "arm_guy" and item != "g4good_Gem_Charity") grow4good(peer, false, "gems", price);
											pInfo(peer)->gems -= price;
											gamepacket_t gem_upd;
											gem_upd.Insert("OnSetBux"), gem_upd.Insert(pInfo(peer)->gems), gem_upd.Insert(0), gem_upd.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) {
												gem_upd.Insert((float)33796, (float)1, (float)0);
											}
											gem_upd.CreatePacket(peer);
											vector<string> received_items{}, received_items2{};
											for (vector<int> item_info : itemai) {
												uint32_t item_id = item_info[0];
												int item_count = item_info[1];
												modify_inventory(peer, item_id, item_count);
												received_items.push_back("Got " + to_string(item_info[1]) + " `#" + items[item_id].ori_name + "``."), received_items2.push_back(to_string(item_info[1]) + " " + items[item_id].ori_name);
											}
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											//if (item == "arm_guy") grow4good(peer, false, "purchase_waving", 0);
											gamepacket_t p_;
											p_.Insert("OnConsoleMessage"), p_.Insert("You've purchased `o" + item_name + "`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems) + "`` Gems left." + "\n" + join(received_items, "\n")), p_.CreatePacket(peer);
											p2.Insert("You've purchased `o" + item_name + "`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems) + "`` Gems left." + "\n\n`5Received: ``" + join(received_items2, ", ") + "\n"), p2.CreatePacket(peer);
											break;
										}
									fail:
										packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
										p2.Insert("You don't have enough space in your inventory to buy that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
										p2.CreatePacket(peer);
										break;
									}
									list = j["i"].get<vector<int>>();
									getcount = j["h"].get<int>();
									get_counted = j["h"].get<int>();
									slot = j["c"].get<int>();
									token = j["t"].get<int>();
									random_pack = j["random"].get<int>();
									int totaltoken = 0, tokencount = 0, mega_token = 0, inventoryfull = 0;
									modify_inventory(peer, 1486, tokencount);
									modify_inventory(peer, 6802, mega_token);
									totaltoken = tokencount + (mega_token * 100);
									vector<pair<int, int>> receivingitems;
									if (token == 0 ? price > pInfo(peer)->gems : token > totaltoken) {
										packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
										p2.Insert("You can't afford `o" + item_name + "``!  You're `$" + (token == 0 ? "" + setGems(price - pInfo(peer)->gems) + "`` Gems short." : "" + setGems(token - totaltoken) + "`` Growtokens short."));
									}
									else {
										if (free >= slot) {
											string received = "", received2 = "";
											if (item == "basic_splice") {
												slot++;
												receivingitems.push_back(make_pair(11, 10));
											}
											if (item == "race_packa") {
												slot++;
												receivingitems.push_back(make_pair(11, 10));
											}
											for (int i = 0; i < slot; i++) receivingitems.push_back(make_pair((random_pack == 1 ? list[rand() % list.size()] : list[i]), getcount));
											for (int i = 0; i < slot; i++) {
												int itemcount = 0;
												modify_inventory(peer, receivingitems[i].first, itemcount);
												if (itemcount + getcount > 200) inventoryfull = 1;
											}
											if (inventoryfull == 0) {
												int i = 0;
												for (i = 0; i < slot; i++) {
													received += (i != 0 ? ", " : "") + items[receivingitems[i].first].name;
													received2 += "Got " + to_string(receivingitems[i].second) + " `#" + items[receivingitems[i].first].name + "``." + (i == (slot - 1) ? "" : "\n") + "";
													modify_inventory(peer, receivingitems[i].first, receivingitems[i].second);
												}
											}
											else {
												packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
												p2.Insert("You don't have enough space in your inventory that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
												p2.CreatePacket(peer);
												break;
											}
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You've purchased `o" + received + "`` for `$" + (token == 0 ? "" + setGems(price) + "`` Gems." : "" + setGems(token) + "`` Growtokens.") + "\nYou have `$" + (token == 0 ? "" + setGems(pInfo(peer)->gems - price) + "`` Gems left." : "" + setGems(totaltoken - token) + "`` Growtokens left.") + "\n" + received2);
												p.CreatePacket(peer);
											}
											p2.Insert("You've purchased `o" + received + "`` for `$" + (token == 0 ? "" + setGems(price) + "`` Gems." : "" + setGems(token) + "`` Growtokens.") + "\nYou have `$" + (token == 0 ? "" + setGems(pInfo(peer)->gems - price) + "`` Gems left." : "" + setGems(totaltoken - token) + "`` Growtokens left.") + "\n\n`5Received: ``" + (get_counted <= 1 ? "" : "`0" + to_string(get_counted)) + "`` " + received + "\n"), p2.CreatePacket(peer);
											if (token == 0) {
												pInfo(peer)->gems -= price;
												gamepacket_t p;
												p.Insert("OnSetBux");
												p.Insert(pInfo(peer)->gems);
												p.Insert(0);
												p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
												if (pInfo(peer)->supp >= 2) {
													p.Insert((float)33796, (float)1, (float)0);
												}
												p.CreatePacket(peer);
											}
											else {
												if (tokencount >= token) modify_inventory(peer, 1486, token *= -1);
												else {
													modify_inventory(peer, 1486, tokencount *= -1);
													modify_inventory(peer, 6802, mega_token *= -1);
													int givemegatoken = (totaltoken - token) / 100;
													int givetoken = (totaltoken - token) - (givemegatoken * 100);
													modify_inventory(peer, 1486, givetoken);
													modify_inventory(peer, 6802, givemegatoken);
												}
											}
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										}
										else {
											packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
											p2.Insert(slot > 1 ? "You'll need " + to_string(slot) + " slots free to buy that! You have " + to_string(free) + " slots." : "You don't have enough space in your inventory that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
										}
									}
								}
								else {
									packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
									p2.Insert("This item was not found. Server error.");
									p2.CreatePacket(peer);
								}
							}
							break;
						}
						else if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|builder_reward\n\n" || cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|fishing_reward\n\n" || cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|geiger_reward\n\n" || cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|farmer_reward\n\n" || cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|provider_reward\n\n") {
							if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|farmer_reward\n\n") farmer_reward_show(peer);
							if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|provider_reward\n\n")provider_reward_show(peer);
							if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|geiger_reward\n\n") geiger_reward_show(peer);
							if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|fishing_reward\n\n") 	fishing_reward_show(peer);
							if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|builder_reward\n\n")	builder_reward_show(peer);
							break;
						}
						else if (cch == "action|AccountSecurity\nlocation|pausemenu\n") {
							gamepacket_t p(500);
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wAdvanced Account Protection ``|left|3732|\nadd_textbox|`1You are about to enable the Advanced Account Protection.``|left|\nadd_textbox|`1After that, every time you try to log in from a new device and IP you will receive an dialog with a PIN confirmation button.``|left|\nadd_textbox|`1This will significantly increase your account security.``|left|\nend_dialog|secureaccount|Cancel|Ok|");
							p.CreatePacket(peer);
							break;
						}
						else if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|surgery_reward\n\n") {
							surgery_reward_show(peer);
							break;
						}
						else if (cch.find("action|respawn") != string::npos) SendRespawn(peer, false, 0, (cch.find("action|respawn_spike") != string::npos) ? false : true);
						else if (cch == "action|refresh_item_data\n") {
							int online_ = 0;
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								online_++;
							}
							online_ = online_ * 2;
							if (pInfo(peer)->world.empty()) {
								cout << pInfo(peer)->tankIDName << " updating items.dat " << pInfo(peer)->ip << " online: " << online_ << endl;
								packet_(peer, "action|log\nmsg|One moment, updating GTPS item data...");
								save_player(pInfo(peer), (f_saving_ ? false : true));
								enet_peer_send(peer, 0, enet_packet_create(item_data, item_data_size + 60, ENET_PACKET_FLAG_RELIABLE));
								enet_peer_disconnect_later(peer, 0);
							}
							else packet_(peer, "action|log\nmsg|CT:[S]_ `4OOPS:`` Too many people logging in at once. Please press `5CANCEL`` and try again in a few seconds.", "");
						}
						else if (cch == "action|enter_game\n") {
							pInfo(peer)->enter_game++;
							if (!CheckConfigS(whitelist, pInfo(peer)->tankIDName) && isWhitelist == 1) {
								//cout << "anan1" << endl;
								packet_(peer, "action|log\nmsg| `5Server is on maintenance for short time, please check news from our discord server.", "");
								break;
							}

							if (pInfo(peer)->isNew) {
								add_perma(pInfo(peer)->tankIDName, "acc.txt");
								pInfo(peer)->isNew = false;
							}

							if (check_perma(peer, "device.txt")) {
								string error = "";
								//error = "action|log\nmsg|CT:[S]_ `4Sorry, you are not allowed to enter the game from this location. Contact `5Discord Staff Team `4if you have any questions.";
								//if (error != "") packet_(peer, error, "");
								gamepacket_t p;
								p.Insert("OnRedirectServer"), p.Insert("127.0.0.1"), p.Insert(17091), p.Insert(1), p.CreatePacket(peer);
								break;
								//ghostban
							}
							/*if (check_perma(peer)) {
								enet_peer_disconnect_later(peer, 0);
							}*/
							if (pInfo(peer)->world == "" && pInfo(peer)->enter_game == 1) {
								if (pInfo(peer)->tankIDName.empty()) {
									if (check_perma(peer, "acc.txt")) {
										string error = "action|log\nmsg|CT:[S]_ `4Can not make new account!`` Sorry, but you are not permitted to create new accounts at this time. (This can be because there is an open proxy/VPN here or abuse has from this IP) Please try again from another device or IP Address.";
										packet_(peer, error, "");
										enet_peer_disconnect_later(peer, 0);
										break;
									}
									else {
										gamepacket_t p;
										p.Insert("OnDialogRequest"), p.Insert(r_dialog("")), p.CreatePacket(peer);
									}
								}
								else {

									pInfo(peer)->last_uptime = server_uptime;
									pInfo(peer)->tmod = pInfo(peer)->mod;
									pInfo(peer)->name_color = admincolor(pInfo(peer)->adminLevel);
									//string thetag = (pInfo(peer)->adminLevel >= 1 ? "@" : "");
									if (pInfo(peer)->drt) pInfo(peer)->d_name = (pInfo(peer)->drt ? "`4" : pInfo(peer)->name_color) + (pInfo(peer)->drt ? "Dr." : "") + pInfo(peer)->tankIDName + (pInfo(peer)->is_legend ? " of Legend" : "");
									int on_ = 0, t_ = 0;
									//if (gotall) pInfo(peer)->superdev = 1, pInfo(peer)->dev = 1, pInfo(peer)->mod = 1, pInfo(peer)->gems = 999999, pInfo(peer)->gtwl = 99999;
									vector<string> friends_;
									for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) friends_.push_back(pInfo(peer)->friends[c_].name);
									if (not pInfo(peer)->invis and not pInfo(peer)->m_h) {
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											t_ += 1 + rand() % 3 + 1;
											if (find(friends_.begin(), friends_.end(), pInfo(currentPeer)->tankIDName) != friends_.end()) {
												if (pInfo(currentPeer)->show_friend_notifications_) {
													gamepacket_t p;
													p.Insert("OnConsoleMessage"), p.Insert("`3FRIEND ALERT:`` " + (pInfo(peer)->name_color == "`0" ? "`o" : pInfo(peer)->name_color + "" + pInfo(peer)->tankIDName) + "`` has `2logged on``.");
													packet_(currentPeer, "action|play_sfx\nfile|audio/friend_logon.wav\ndelayMS|0");
													p.CreatePacket(currentPeer);
												}
												on_++;
											}
										}
									}
									{
										gamepacket_t p;
										p.Insert("OnEmoticonDataChanged");
										p.Insert(151749376);
										p.Insert("(wl)|ā|1&(yes)|Ă|1&(no)|ă|1&(love)|Ą|1&(oops)|ą|1&(shy)|Ć|1&(wink)|ć|1&(tongue)|Ĉ|1&(agree)|ĉ|1&(sleep)|Ċ|1&(punch)|ċ|1&(music)|Č|1&(build)|č|1&(megaphone)|Ď|1&(sigh)|ď|1&(mad)|Đ|1&(wow)|đ|1&(dance)|Ē|1&(see-no-evil)|ē|1&(bheart)|Ĕ|1&(heart)|ĕ|1&(grow)|Ė|1&(gems)|ė|1&(kiss)|Ę|1&(gtoken)|ę|1&(lol)|Ě|1&(smile)|Ā|1&(cool)|Ĝ|1&(cry)|ĝ|1&(vend)|Ğ|1&(bunny)|ě|1&(cactus)|ğ|1&(pine)|Ĥ|1&(peace)|ģ|1&(terror)|ġ|1&(troll)|Ġ|1&(evil)|Ģ|1&(fireworks)|Ħ|1&(football)|ĥ|1&(alien)|ħ|1&(party)|Ĩ|1&(pizza)|ĩ|1&(clap)|Ī|1&(song)|ī|1&(ghost)|Ĭ|1&(nuke)|ĭ|1&(halo)|Į|1&(turkey)|į|1&(gift)|İ|1&(cake)|ı|1&(heartarrow)|Ĳ|1&(lucky)|ĳ|1&(shamrock)|Ĵ|1&(grin)|ĵ|1&(ill)|Ķ|1&");
										p.CreatePacket(peer);
									}
									/*
									{
										gamepacket_t p;
										p.Insert("OnEmoticonDataChanged");
										p.Insert(151749376);
										string other = "";
										for (int i = 0; i < pInfo(peer)->gr.size(); i++) other += pInfo(peer)->gr[i];
										p.Insert(other + "" + (pInfo(peer)->supp == 2 ? "(yes)|Ă|1" : "(yes)|Ă|0") + "&" + (pInfo(peer)->supp != 0 ? "(no)|ă|1" : "(no)|ă|0") + "&" + (pInfo(peer)->supp == 2 ? "(love)|Ą|1" : "(love)|Ą|0") + "&" + (pInfo(peer)->supp != 0 ? "(shy)|Ć|1&(wink)|ć|1" : "(shy)|Ć|0&(wink)|ć|0") + "&" + (pInfo(peer)->level >= 5 ? "(tongue)|Ĉ|1" : "(tongue)|Ĉ|0") + "&" + (pInfo(peer)->friends.size() >= 20 ? "(agree)|ĉ|1" : "(agree)|ĉ|0") + "&" + (pInfo(peer)->supp != 0 ? "(music)|Č|1" : "(music)|Č|0") + "&" + (pInfo(peer)->friends.size() >= 50 ? "(build)|č|1" : "(build)|č|0") + "&" + (pInfo(peer)->supp == 2 ? "(megaphone)|Ď|1" : "(megaphone)|Ď|0") + "&" + (pInfo(peer)->level >= 5 ? "(sigh)|ď|1&(mad)|Đ|1&(wow)|đ|1" : "(sigh)|ď|0&(mad)|Đ|0&(wow)|đ|0") + "&" + (pInfo(peer)->friends.size() >= 40 ? "(dance)|Ē|1" : "(dance)|Ē|0") + "&" + (pInfo(peer)->friends.size() >= 30 ? "(see-no-evil)|ē|1" : "(see-no-evil)|ē|0") + "&" + (pInfo(peer)->supp == 2 ? "(heart)|ĕ|1" : "(heart)|ĕ|0") + "&" + (pInfo(peer)->friends.size() >= 10 ? "(kiss)|Ę|1" : "(kiss)|Ę|0") + "&" + (pInfo(peer)->supp != 0 ? "(lol)|Ě|1" : "(lol)|Ě|1") + "&" + (pInfo(peer)->level >= 5 ? "(smile)|Ā|1" : "(smile)|Ā|0") + "&" + (pInfo(peer)->supp == 2 ? "(cool)|Ĝ|1" : "(cool)|Ĝ|0") + "&(lucky)|ĳ|1&");
										p.CreatePacket(peer);
									}*/
									{
										gamepacket_t p;
										p.Insert("OnProgressUISet"), p.Insert(1), p.Insert(3402), p.Insert(pInfo(peer)->booty_broken), p.Insert(100), p.Insert(""), p.Insert(1);
										p.CreatePacket(peer);
									}
									if (!pInfo(peer)->inventory_sent) send_inventory(peer);
									if (pInfo(peer)->surgery_type == -1) pInfo(peer)->surgery_type = rand() % 30;

									if (CheckConfigS(server_owner, pInfo(peer)->tankIDName)) {
										if (pInfo(peer)->tankIDName == "Xoid") pInfo(peer)->adminLevel = 7;
										else pInfo(peer)->adminLevel = 6;
										pInfo(peer)->dev = true, pInfo(peer)->mod = true;
										pInfo(peer)->lgnd = true, pInfo(peer)->drtitle = true, pInfo(peer)->gp = true, pInfo(peer)->mp = true, pInfo(peer)->level = 125, pInfo(peer)->gems = 100000000;

										gamepacket_t p;
										p.Insert("OnSetBux");
										p.Insert(pInfo(peer)->gems);
										p.Insert(0);
										p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
										if (pInfo(peer)->supp >= 2) {
											p.Insert((float)33796, (float)1, (float)0);
										}
										p.CreatePacket(peer);
									}
									if (pInfo(peer)->adminLevel >= 1) pInfo(peer)->mod = true, pInfo(peer)->supp = 2, pInfo(peer)->hs = 1;
									else if (pInfo(peer)->adminLevel >= 2) pInfo(peer)->mod = true, pInfo(peer)->dev = true, pInfo(peer)->supp = 2, pInfo(peer)->hs = 1;
									if (pInfo(peer)->supp == 1) pInfo(peer)->supp = 2;
									gamepacket_t p1, p2, p5;
									p1.Insert("OnConsoleMessage"), p1.Insert("`oWelcome to server, `w" + (admincolor(pInfo(peer)->adminLevel) + pInfo(peer)->tankIDName) + "````." + (pInfo(peer)->friends.size() == 0 ? "" : (on_ != 0 ? " `w" + to_string(on_) + "`` friend is online." : " No friends are online."))), p1.CreatePacket(peer);
									if (isBeta == 1) {
										gamepacket_t p3;
										p3.Insert("OnConsoleMessage"), p3.Insert("`4BETA MODE! `oYour progress will not be saved, if you find any bugs contact with developer."), p3.CreatePacket(peer);
									}
									if (today_day != pInfo(peer)->dd) {
										pInfo(peer)->AlreadyDailyQ = false;
										pInfo(peer)->dd = today_day;
									}
									world_menu(peer);
									SendNews(peer);
									ServerLog("Logon: " + pInfo(peer)->requestedName + " GrowID: " + pInfo(peer)->tankIDName + " IP: " + pInfo(peer)->ip + " RID: " + pInfo(peer)->rid);
								}
							}
							else enet_peer_disconnect_later(peer, 0);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|account_security\nchange|") != string::npos) {
							string change = cch.substr(57, cch.length() - 57).c_str();
							replace_str(change, "\n", "");
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							if (change == "email") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|Having an up-to-date email address attached to your account is a great step toward improved account security.|left|\nadd_smalltext|Email: `5" + pInfo(peer)->email + "``|left|\nadd_spacer|small|\nadd_smalltext|Type your new `5email address``|left|\nadd_text_input|change|||50|\nend_dialog|change_email|OK|Continue|\n");
							else if (change == "password") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|A hacker may attempt to access your account more than once over a period of time.|left|\nadd_smalltext|Changing your password `2often reduces the risk that they will have frequent access``.|left|\nadd_spacer|small|\nadd_smalltext|Type your new `5password``|left|\nadd_text_input|change|||18|\nend_dialog|change_password|OK|Continue|\n");
							if (change == "email" or change == "password") p.CreatePacket(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|change_email\nchange|") != string::npos) {
							string change = cch.substr(53, cch.length() - 53).c_str();
							replace_str(change, "\n", "");
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							if (change == "") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|Having an up-to-date email address attached to your account is a great step toward improved account security.|left|\nadd_smalltext|Email: `5" + pInfo(peer)->email + "``|left|\nadd_spacer|small|\nadd_smalltext|Type your new `5email address``|left|\nadd_text_input|change|||50|\nend_dialog|change_email|OK|Continue|\n");
							else {
								pInfo(peer)->email = change;
								save_player(pInfo(peer), false);
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|Having an up-to-date email address attached to your account is a great step toward improved account security.|left|\nadd_smalltext|Your new Email: `5" + pInfo(peer)->email + "``|left|\nadd_spacer|small|\nend_dialog|changedemail|OK||\n");
							}
							p.CreatePacket(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|change_password\nchange|") != string::npos) {
							string change = cch.substr(56, cch.length() - 56).c_str();
							replace_str(change, "\n", "");
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							if (change == "") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|A hacker may attempt to access your account more than once over a period of time.|left|\nadd_smalltext|Changing your password `2often reduces the risk that they will have frequent access``.|left|\nadd_spacer|small|\nadd_smalltext|Type your new `5password``|left|\nadd_text_input|change|||18|\nend_dialog|change_password|OK|Continue|\n");
							else {
								{
									gamepacket_t p;
									p.Insert("SetHasGrowID"), p.Insert(1), p.Insert(pInfo(peer)->tankIDName), p.Insert(pInfo(peer)->tankIDPass = change);
									p.CreatePacket(peer);
								}
								save_player(pInfo(peer), false);
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|A hacker may attempt to access your account more than once over a period of time.|left|\nadd_smalltext|Changing your password `2often reduces the risk that they will have frequent access``.|left|\nadd_smalltext|Your new password: `5" + pInfo(peer)->tankIDPass + "``|left|\nadd_spacer|small|\nend_dialog|changedpassword|OK||\n");
							}
							p.CreatePacket(peer);
							break;
						}
												else if (cch.find("action|dialog_return\ndialog_name|world_swap\nname_box|") != string::npos) {
													string world = cch.substr(53, cch.length() - 54).c_str(), currentworld = pInfo(peer)->world;
													int got = 0;
													transform(world.begin(), world.end(), world.begin(), ::toupper);
													if (not check_blast(world) || currentworld == world) {
														gamepacket_t p;
														p.Insert("OnDialogRequest"), p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSwap World Names``|left|2580|\nadd_textbox|`4World swap failed - you don't own both worlds!``|left|\nadd_smalltext|This will swap the name of the world you are standing in with another world `4permanently``.  You must own both worlds, with a World Lock in place.<CR>Your `wChange of Address`` will be consumed if you press `5Swap 'Em``.|left|\nadd_textbox|Enter the other world's name:|left|\nadd_text_input|name_box|||32|\nadd_spacer|small|\nend_dialog|world_swap|Cancel|Swap 'Em!|"), p.CreatePacket(peer);
													}
													else create_address_world(peer, world, currentworld);
													break;
						}
												else if (cch.find("action|dialog_return\ndialog_name|change_guild_name\nbuttonClicked|confirm") != string::npos) {
													string newName = explode("\n", explode("new_guild_name|", cch)[1])[0];
													bool bad_name = false, already_taken = false;
													int adaBrp = 0;
													string check_name = to_lower(newName);
													for (int i = 0; i < swear_words.size(); i++) {
														if (check_name.find(swear_words[i]) != string::npos) {
															bad_name = true;
															break;
														}
													} for (Guild check_guild_name : guilds) {
														if (to_lower(check_guild_name.guild_name) == check_name) {
															already_taken = true;
															break;
														}
													}
													if (already_taken or bad_name or newName.size() < 3 or newName.size() > 15 or special_char(newName)) goto lad;
													if (modify_inventory(peer, 7190, adaBrp = -1) == 0) {
														if (pInfo(peer)->guild_id != 0) {
															uint32_t guild_id = pInfo(peer)->guild_id;
															uint32_t my_rank = 0;
															vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
															if (p != guilds.end()) {
																Guild* guild_information = &guilds[p - guilds.begin()];
																for (GuildMember member_search : guild_information->guild_members) {
																	if (member_search.member_name == pInfo(peer)->tankIDName) {
																		my_rank = member_search.role_id;
																		break;
																	}
																}
																if (my_rank == 3) {
																	Guild* set_guild = &guilds[p - guilds.begin()];
																	set_guild->guild_name = newName;
																	gamepacket_t p;
																	p.Insert("OnDialogRequest");
																	p.Insert(get_guild_info(peer));
																	p.CreatePacket(peer);
																}
															}
														}
													}
													break;
												lad: {
													uint32_t my_rank = 0;
													string guildName = "";
													if (pInfo(peer)->guild_id != 0) {
														uint32_t guild_id = pInfo(peer)->guild_id;
														vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
														if (p != guilds.end()) {
															Guild* guild_information = &guilds[p - guilds.begin()];
															for (GuildMember member_search : guild_information->guild_members) {
																guildName = guild_information->guild_name;
																if (member_search.member_name == pInfo(peer)->tankIDName) {
																	my_rank = member_search.role_id;
																	break;
																}
															}
														}
														if (my_rank == 3) {
															gamepacket_t p;
															p.Insert("OnDialogRequest");
															p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wChange Guild Name``|left|5814|\n"
																"add_textbox|Current Guild Name:" + guildName + "|left|\n"
																"add_smalltext|`4You can't use that name for your guild name or the name is already taken``|left|\n"
																"add_text_input|new_guild_name|Guild Name:||15|\n\n"
																"add_button|confirm|Confirm|noflags|0|0|\n"
																"end_dialog|change_guild_name|Close||");
															p.CreatePacket(peer);
														}
														else {
															gamepacket_t p;
															p.Insert("OnTextOverlay"), p.Insert("Only Guild Leader can Change Guild Name!"), p.CreatePacket(peer);
															break;
														}
													}
													else {
														gamepacket_t p;
														p.Insert("OnTextOverlay"), p.Insert("You must have Guild to use Guild Name Changer!"), p.CreatePacket(peer);
														break;
													}
													break;
													}
													}
												else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|ancientdialog\n\n") {
													int b = b = pInfo(peer)->ances;
													gamepacket_t p;
													p.Insert("OnDialogRequest");
													p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Ancient Goddess|left|5086|\nadd_textbox|`9You are upgrading ances to " + items[ancesupgradeto(peer, b)].name + "\nadd_textbox|`$I will gift a part of my power to enhance your miraculous|\nadd_textbox|`$device, but this exchange, you must bring me the answers|\nadd_textbox|`$to my riddles:|\nadd_spacer|small|" + ancientdialog(peer, b));
													p.CreatePacket(peer);
						}
												else if (cch == "action|dialog_return\ndialog_name|tolol12\nbuttonClicked|ancientaltar\n\n") {
													int b = b = pInfo(peer)->ances;
													int c = 0, loler12 = 0, ex = 0, n = ancesupgradeto(peer, b), d = ancientprice(b);

													if (modify_inventory(peer, n, ex += 1) == -1) {
														gamepacket_t p;
														p.Insert("OnDialogRequest");
														p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Ancient Goddess|left|5086|\nadd_spacer|small|\nadd_textbox|`$Something wrong...|\nadd_spacer|small|\nend_dialog||Return|");
														p.CreatePacket(peer);
														packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
													}
													else {
														modify_inventory(peer, 1796, d);
														modify_inventory(peer, b, loler12 -= 1);
														equip_clothes(peer, n);
														gamepacket_t p;
														p.Insert("OnDialogRequest");
														p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Ancient Goddess|left|5086|\nadd_spacer|small|\nadd_textbox|`6You've pleased me, clever one.|\nadd_spacer|small|\nend_dialog||Return|");
														p.CreatePacket(peer);
														gamepacket_t p2(0, pInfo(peer)->netID);
														p2.Insert("OnPlayPositioned");
														p2.Insert("audio/change_clothes.wav");
														p2.CreatePacket(peer);
													}
													}
												else if (cch.find("action|dialog_return\ndialog_name|checkoutcounter") != string::npos) {
													string name_ = pInfo(peer)->world;
													vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
													if (p != worlds.end()) {
														World* world_ = &worlds[p - worlds.begin()];
														world_->fresh_world = true;
														WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
														if (not block_access(peer, world_, block_)) break;
														vector<string> t_ = explode("|", cch);
														if (t_.size() > 4) {
															string button = explode("\n", t_[3])[0].c_str();
															if (button == "filterbytext") load_vendhub(peer, world_, block_, explode("\n", t_[4])[0].c_str());
															else if (button == "switchdirection") block_->spin = (block_->spin ? false : true);
															else {
																int i_ = atoi(explode("\n", t_[3])[0].c_str()), x_ = i_ % 100, y_ = i_ / 100;
																if (i_ > world_->blocks.size()) break;
																block_ = &world_->blocks[i_];
																if (items[world_->blocks[i_].fg].blockType != BlockTypes::VENDING) break;
																gamepacket_t p;
																p.Insert("OnDialogRequest");
																p.Insert(get_vending(peer, world_, block_, x_, y_));
																p.CreatePacket(peer);
															}
														}
													}
													break;
						}
					else if (cch.find("action|dialog_return\ndialog_name|name_change\nname_box|") != string::npos) {
						string name = cch.substr(54, cch.length() - 55).c_str();
						if (to_lower(name) != to_lower(pInfo(peer)->tankIDName)) {
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wChange your GrowID``|left|1280|\nadd_textbox|`4The name doesn't match your current name!``|left|\nadd_smalltext|This will change your GrowID `4permanently``.<CR>Your `wBirth Certificate`` will be consumed if you press `5Change It``.<CR>NOTE: The birth certificate only will change your name case (you can not change your whole GrowID)!``|left|\nadd_textbox|Enter your new name:|left|\nadd_text_input|name_box|||32|\nadd_spacer|small|\nend_dialog|name_change|Cancel|Change it!|");
							p.CreatePacket(peer);
						}
						else {
							int remove_ = -1;
							if (modify_inventory(peer, 1280, remove_) == 0) {
								pInfo(peer)->tankIDName = name;
								admincolor(pInfo(peer)->adminLevel) + name;
							}
						}
						break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|surgery\nbuttonClicked|tool") != string::npos) {
							if (pInfo(peer)->surgery_started) {
								int count = atoi(cch.substr(59, cch.length() - 59).c_str());
								if (count == 999) end_surgery(peer);
								else load_surgery(peer, count);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|statsblock\nisStatsWorldBlockUsableByPublic") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							bool world_public = atoi(explode("\n", t_[3])[0].c_str()), floating_public = atoi(explode("\n", t_[4])[0].c_str()), changed = false;
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								if (pInfo(peer)->tankIDName == world_->owner_name) {
									for (int i_ = 0; i_ < world_->gscan.size(); i_++) {
										if (world_->gscan[i_].x == pInfo(peer)->lastwrenchx and world_->gscan[i_].y == pInfo(peer)->lastwrenchy) {
											changed = true;
											world_->gscan[i_].world_public = world_public;
											world_->gscan[i_].floating_public = floating_public;
										}
									}
								}
								if (changed == false) {
									WorldGrowscan gscan_{};
									gscan_.x = pInfo(peer)->lastwrenchx, gscan_.y = pInfo(peer)->lastwrenchy;
									gscan_.world_public = world_public, gscan_.floating_public = floating_public;
									world_->gscan.push_back(gscan_);
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|statsblockworld\nbuttonClicked|back_to_gscan\n") != string::npos) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator pd = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (pd != worlds.end()) {
								World* world_ = &worlds[pd - worlds.begin()];
								world_->fresh_world = true;
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								growscan_load(peer, world_, block_);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|statsblock\nbuttonClicked|floatingItems\n") != string::npos) {
							send_growscan_floating(peer, "start", "1");
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|statsblock\nbuttonClicked|search_") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 5 || pInfo(peer)->world.empty()) break;
							string type = explode("\n", t_[3])[0].c_str(), search = explode("\n", t_[4])[0].c_str();
							replaceAll(type, "search_", "");
							send_growscan_floating(peer, search, type);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|statsblock\nbuttonClicked|worldBlocks\n") != string::npos || cch.find("action|dialog_return\ndialog_name|statsblockworld\nbuttonClicked|worldBlocks\n") != string::npos) {
							send_growscan_worldblocks(peer, "start", "1");
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|statsblockworld\nbuttonClicked|search_") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 5 || pInfo(peer)->world.empty()) break;
							string type = explode("\n", t_[3])[0].c_str(), search = explode("\n", t_[4])[0].c_str();
							replaceAll(type, "search_", "");
							send_growscan_worldblocks(peer, search, type);
							break;
						}
						if (cch.find("action|dialog_return\ndialog_name|billboard_edit\nbillboard_toggle|") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							int billboard_active = atoi(explode("\n", t_[3])[0].c_str());
							int billboard_price = atoi(explode("\n", t_[4])[0].c_str());
							int peritem = atoi(explode("\n", t_[5])[0].c_str());
							int perlock = atoi(explode("\n", t_[6])[0].c_str());
							bool update_billboard = true;
							if (peritem == perlock or peritem == 0 and perlock == 0 or peritem == 1 and perlock == 1) {
								update_billboard = false;
								gamepacket_t p, p2;
								p.Insert("OnConsoleMessage"), p.Insert("You need to pick one pricing method - 'locks per item' or 'items per lock'"), p.CreatePacket(peer);
								p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("You need to pick one pricing method - 'locks per item' or 'items per lock'"), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
							}
							else {
								if (peritem == 1) pInfo(peer)->b_w = 1;
								if (perlock == 1) pInfo(peer)->b_w = 0;
							}
							if (billboard_active == 1)pInfo(peer)->b_a = 1;
							else pInfo(peer)->b_a = 0;
							if (billboard_price < 0 or billboard_price > 99999) {
								update_billboard = false;
								gamepacket_t p, p2;
								p.Insert("OnConsoleMessage"), p.Insert("Price can't be negative. That's beyond science."), p.CreatePacket(peer);
								p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("Price can't be negative. That's beyond science."), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
							}
							else pInfo(peer)->b_p = billboard_price;
							if (update_billboard && pInfo(peer)->b_p != 0 && pInfo(peer)->b_i != 0) {
								gamepacket_t p(0, pInfo(peer)->netID);
								p.Insert("OnBillboardChange"), p.Insert(pInfo(peer)->netID), p.Insert(pInfo(peer)->b_i), p.Insert(pInfo(peer)->b_a), p.Insert(pInfo(peer)->b_p), p.Insert(pInfo(peer)->b_w);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != pInfo(peer)->world) continue;
									p.CreatePacket(currentPeer);
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|dialog_scarf_of_seasons\nbuttonClicked") != string::npos) {
							if (pInfo(peer)->necklace == 11818) pInfo(peer)->i_11818_1 = 0, pInfo(peer)->i_11818_2 = 0, update_clothes(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|title_edit\nbuttonClicked|") != string::npos) {
							try {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 5) break;
								if (pInfo(peer)->lgnd) pInfo(peer)->is_legend = atoi(explode("\n", explode("11111|", cch)[1])[0].c_str());
								if (pInfo(peer)->drtitle) {
									pInfo(peer)->drt = atoi(explode("\n", explode("22222|", cch)[1])[0].c_str());
									string thetag = (pInfo(peer)->mod || pInfo(peer)->dev ? "@" : "");
									pInfo(peer)->d_name = (pInfo(peer)->drt ? "`4" + thetag : pInfo(peer)->name_color) + (pInfo(peer)->drt ? "Dr." : "") + pInfo(peer)->tankIDName + (pInfo(peer)->is_legend ? " of Legend" : "");
									if (!pInfo(peer)->drt) pInfo(peer)->d_name = "";
									{
										gamepacket_t p2(0, pInfo(peer)->netID);
										p2.Insert("OnNameChanged"), p2.Insert((not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + (pInfo(peer)->is_legend ? " of Legend" : "") + "``");
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != pInfo(peer)->world) continue;
											p2.CreatePacket(currentPeer);
										}
									}
								}
								if (pInfo(peer)->gp) pInfo(peer)->donor = atoi(explode("\n", explode("33333|", cch)[1])[0].c_str());
								if (pInfo(peer)->mp) pInfo(peer)->master = atoi(explode("\n", explode("44444|", cch)[1])[0].c_str());
								if (pInfo(peer)->level >= 125) pInfo(peer)->lvl125 = atoi(explode("\n", explode("55555|", cch)[1])[0].c_str());
								update_clothes(peer);
							}
							catch (out_of_range) {
								break;
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|dialog_scarf_of_seasons\ncheckbox") != string::npos) {
							try {
								if (pInfo(peer)->necklace == 11818) {
									vector<string> t_ = explode("|", cch);
									if (t_.size() < 4) break;
									for (int i = 3; i <= 10; i++) {
										if (i <= 6 && atoi(explode("\n", t_.at(i)).at(0).c_str()) == 1) pInfo(peer)->i_11818_1 = i - 3;
										else if (atoi(explode("\n", t_.at(i)).at(0).c_str()) == 1) pInfo(peer)->i_11818_2 = i - 7;
									}
									update_clothes(peer);
								}
							}
							catch (out_of_range) {
								break;
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|bulletin_edit\nsign_text|\ncheckbox_locked|") != string::npos) {
							try {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								bool public_can_add = atoi(explode("\n", t_.at(4)).at(0).c_str()), hide_names = atoi(explode("\n", t_.at(5)).at(0).c_str());
								bool changed = false;
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									if (pInfo(peer)->tankIDName == world_->owner_name) {
										for (int i_ = 0; i_ < world_->bulletins.size(); i_++) {
											if (world_->bulletins.at(i_).x == pInfo(peer)->lastwrenchx and world_->bulletins.at(i_).y == pInfo(peer)->lastwrenchy) {
												changed = true;
												world_->bulletins.at(i_).public_can_add = public_can_add;
												world_->bulletins.at(i_).hide_names = hide_names;
											}
										}
									}
									if (changed == false) {
										WorldBulletinSettings set_{};
										set_.x = pInfo(peer)->lastwrenchx, set_.y = pInfo(peer)->lastwrenchy, set_.public_can_add = public_can_add, set_.hide_names = hide_names;
										world_->bulletins.push_back(set_);
									}
								}
							}
							catch (out_of_range) {
								break;
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|camera_edit\ncheckbox_showpick|") != string::npos) {
							try {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								bool show_item_taking = atoi(explode("\n", t_.at(3)).at(0).c_str()), show_item_dropping = atoi(explode("\n", t_.at(4)).at(0).c_str()), show_people_entering = atoi(explode("\n", t_.at(5)).at(0).c_str()), show_people_exiting = atoi(explode("\n", t_.at(6)).at(0).c_str()), dont_show_owner = atoi(explode("\n", t_.at(7)).at(0).c_str()), dont_show_admins = atoi(explode("\n", t_.at(8)).at(0).c_str()), dont_show_noaccess = atoi(explode("\n", t_.at(9)).at(0).c_str()), changed = false;
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									for (int i_ = 0; i_ < world_->cctv_settings.size(); i_++) {
										if (world_->cctv_settings.at(i_).x == pInfo(peer)->lastwrenchx and world_->cctv_settings.at(i_).y == pInfo(peer)->lastwrenchy) {
											changed = true;
											world_->cctv_settings.at(i_).show_item_taking = show_item_taking;
											world_->cctv_settings.at(i_).show_item_dropping = show_item_dropping;
											world_->cctv_settings.at(i_).show_people_entering = show_people_entering;
											world_->cctv_settings.at(i_).show_people_exiting = show_people_exiting;
											world_->cctv_settings.at(i_).dont_show_owner = dont_show_owner;
											world_->cctv_settings.at(i_).dont_show_admins = dont_show_admins;
											world_->cctv_settings.at(i_).dont_show_noaccess = dont_show_noaccess;
										}
									}
									if (changed == false) {
										WorldCCTVSettings cctvs_{};
										cctvs_.x = pInfo(peer)->lastwrenchx, cctvs_.y = pInfo(peer)->lastwrenchy;
										cctvs_.show_item_taking = show_item_taking, cctvs_.show_item_dropping = show_item_dropping, cctvs_.show_people_entering = show_people_entering, cctvs_.show_people_exiting = show_people_exiting, cctvs_.dont_show_owner = dont_show_owner, cctvs_.dont_show_admins = dont_show_admins, cctvs_.dont_show_noaccess = dont_show_noaccess;
										world_->cctv_settings.push_back(cctvs_);
									}
								}
							}
							catch (out_of_range) {
								break;
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|camera_edit\nbuttonClicked|clear") != string::npos) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								for (int i_ = 0; i_ < world_->cctv.size(); i_++)if (world_->cctv[i_].x == pInfo(peer)->lastwrenchx and world_->cctv[i_].y == pInfo(peer)->lastwrenchy) {
									if (i_ != 0) {
										world_->cctv.erase(world_->cctv.begin() + i_);
										i_--;
									}
								}
							}
							{
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("`2Camera log cleared.``"), p.Insert(0), p.Insert(0), p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|autoclave\nbuttonClicked|tool") != string::npos) {
							int itemtool = atoi(cch.substr(61, cch.length() - 61).c_str());
							if (itemtool == 1258 || itemtool == 1260 || itemtool == 1262 || itemtool == 1264 || itemtool == 1266 || itemtool == 1268 || itemtool == 1270 || itemtool == 4308 || itemtool == 4310 || itemtool == 4312 || itemtool == 4314 || itemtool == 4316 || itemtool == 4318) {
								int got = 0;
								modify_inventory(peer, itemtool, got);
								if (got >= 20) {
									pInfo(peer)->lastchoosenitem = itemtool;
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Autoclave``|left|4322|\nadd_spacer|small|\nadd_textbox|Are you sure you want to destroy 20 " + items[itemtool].ori_name + " in exchange for one of each of the other 12 surgical tools?|left|\nadd_button|verify|Yes!|noflags|0|0|\nend_dialog|autoclave|Cancel||");
									p.CreatePacket(peer);
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|autoclave\nbuttonClicked|verify") != string::npos) {
							int removeitem = pInfo(peer)->lastchoosenitem, inventory_space = 12, slots = get_free_slots(pInfo(peer)), got = 0;
							modify_inventory(peer, removeitem, got);
							if (got >= 20) {
								vector<int> noobitems{ 1262, 1266, 1264, 4314, 4312, 4318, 4308, 1268, 1258, 1270, 4310, 4316 };
								bool toobig = false;
								for (int i_ = 0, remove = 0; i_ < pInfo(peer)->inv.size(); i_++) for (int i = 0; i < noobitems.size(); i++) {
									if (pInfo(peer)->inv[i_].id == noobitems[i]) {
										if (pInfo(peer)->inv[i_].count == 200) toobig = true;
										else inventory_space -= 1;
									}
								}
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
								if (toobig == false && slots >= inventory_space) {
									modify_inventory(peer, removeitem, got = -20);
									for (int i = 0; i < noobitems.size(); i++) {
										if (noobitems[i] == removeitem) continue;
										modify_inventory(peer, noobitems[i], got = 1);
									}
									gamepacket_t p2;
									p.Insert("[`3I swapped 20 " + items[removeitem].ori_name + " for 1 of every other instrument!``]");
									p2.Insert("OnTalkBubble"), p2.Insert("[`3I swapped 20 " + items[removeitem].name + " for 1 of every other instrument!``]"), p2.CreatePacket(peer);
								}
								else p.Insert("No inventory space!");
								p.Insert(0), p.Insert(1), p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|extractor\nbuttonClicked|extractOnceObj_") != string::npos) {
							int got = 0;
							modify_inventory(peer, 6140, got);
							if (got >= 1) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									int uid = atoi(cch.substr(72, cch.length() - 72).c_str());
									if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) break;
									for (int i_ = 0; i_ < world_->drop.size(); i_++) {
										if (world_->drop[i_].id != 0 && world_->drop[i_].x > 0 && world_->drop[i_].y > 0 && world_->drop[i_].uid == uid) {
											gamepacket_t p;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
											int c_ = world_->drop[i_].count;
											if (modify_inventory(peer, world_->drop[i_].id, c_) == 0) {
												modify_inventory(peer, 6140, got = -1);
												p.Insert("You have extracted " + to_string(world_->drop[i_].count) + " " + items[world_->drop[i_].id].name + ".");
												int32_t to_netid = pInfo(peer)->netID;
												PlayerMoving data_{}, data2_{};
												data_.effect_flags_check = 1, data_.packetType = 14, data_.netID = 0, data_.plantingTree = world_->drop[i_].uid;
												data2_.x = world_->drop[i_].x, data2_.y = world_->drop[i_].y, data2_.packetType = 19, data2_.plantingTree = 500, data2_.punchX = world_->drop[i_].id, data2_.punchY = pInfo(peer)->netID;
												BYTE* raw = packPlayerMoving(&data_);
												BYTE* raw2 = packPlayerMoving(&data2_);
												raw2[3] = 5;
												memcpy(raw2 + 8, &to_netid, 4);
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
													send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													send_raw(currentPeer, 4, raw2, 56, ENET_PACKET_FLAG_RELIABLE);
												}
												delete[]raw, raw2;
												world_->drop[i_].id = 0, world_->drop[i_].x = -1, world_->drop[i_].y = -1;
											}
											else p.Insert("No inventory space.");
											p.CreatePacket(peer);
										}
									}
								}
							}
							break;
						}

						else if (cch.find("action|dialog_return\ndialog_name|donation_box_edit\nbuttonClicked|clear_selected\n") != string::npos) {
							try {
								bool took = false, fullinv = false;
								gamepacket_t p3;
								p3.Insert("OnTalkBubble"), p3.Insert(pInfo(peer)->netID);
								string name_ = pInfo(peer)->world;
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) break;
									WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									if (!items[block_->fg].donation) break;
									for (int i_ = 0, remove_ = 0; i_ < block_->donates.size(); i_++, remove_++) {
										if (atoi(explode("\n", t_.at(4 + remove_)).at(0).c_str())) {
											int receive = block_->donates[i_].count;
											if (modify_inventory(peer, block_->donates[i_].item, block_->donates[i_].count) == 0) {
												took = true;
												gamepacket_t p;
												p.Insert("OnConsoleMessage"), p.Insert("`7[``" + pInfo(peer)->tankIDName + " receives `5" + to_string(receive) + "`` `w" + items[block_->donates[i_].item].name + "`` from `w" + block_->donates[i_].name + "``, how nice!`7]``");
												block_->donates.erase(block_->donates.begin() + i_), i_--;
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world) continue;
													p.CreatePacket(currentPeer);
												}
											}
											else fullinv = true;
										}
									}
									if (block_->donates.size() == 0) {
										WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
										PlayerMoving data_{};
										data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
										BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, &block_));
										BYTE* blc = raw + 56;
										form_visual(blc, block_, *world_, peer, false);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 112 + alloc_(world_, &block_), ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw, blc;
									}
								}
								if (fullinv) {
									p3.Insert("I don't have enough room in my backpack to get the item(s) from the box!");
									gamepacket_t p2;
									p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("`2(Couldn't get all of the gifts)``"), p2.CreatePacket(peer);
								}
								else if (took) p3.Insert("`2Box emptied.``");
								p3.CreatePacket(peer);
							}
							catch (out_of_range) {
								break;
							}
							break;
						}

						else if (cch.find("action|dialog_return\ndialog_name|password_reply\npassword|") != string::npos) {
							string password = cch.substr(57, cch.length() - 57).c_str();
							string name_ = pInfo(peer)->world;
							vector<World>::iterator pa = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (pa != worlds.end()) {
								World* world_ = &worlds[pa - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (block_->fg == 762 && block_->door_id != "") {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									replace_str(password, "\n", "");
									transform(password.begin(), password.end(), password.begin(), ::toupper);
									if (block_->door_id != password) p.Insert("`4Wrong password!``");
									else {
										p.Insert(a + "`2The door opens!" + (block_->door_destination == "" ? " But nothing is behind it." : "") + "``");
										if (block_->door_destination != "") {
											gamepacket_t p3(0, pInfo(peer)->netID);
											p3.Insert("OnPlayPositioned"), p3.Insert("audio/door_open.wav"), p3.CreatePacket(peer);
											string door_target = block_->door_destination, door_id = "";
											World target_world = worlds[pa - worlds.begin()];
											int spawn_x = 0, spawn_y = 0;
											if (door_target.find(":") != string::npos) {
												vector<string> detales = explode(":", door_target);
												door_target = detales[0], door_id = detales[1];
											}
											int ySize = (int)target_world.blocks.size() / 100, xSize = (int)target_world.blocks.size() / ySize;
											if (not door_id.empty()) {
												for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
													WorldBlock block_data = target_world.blocks[i_];
													if (block_data.fg == 762) continue;
													if (block_data.fg == 1684 or items[block_data.fg].blockType == BlockTypes::DOOR or items[block_data.fg].blockType == BlockTypes::PORTAL) {
														if (block_data.door_id == door_id) {
															spawn_x = i_ % xSize, spawn_y = i_ / xSize;
															break;
														}
													}
												}
											}
											join_world(peer, target_world.name, spawn_x, spawn_y, 250, false, true);

										}
									}
									p.CreatePacket(peer);
								}
							}
							break;
						}
						else if (cch == "action|dialog_return\ndialog_name|2646\nbuttonClicked|off\n\n") {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world or block_->spotlight != pInfo(currentPeer)->tankIDName) continue;
									pInfo(currentPeer)->spotlight = false, update_clothes(currentPeer);
									gamepacket_t p;
									p.Insert("OnConsoleMessage"), p.Insert("Back to anonymity. (`$In the Spotlight`` mod removed)"), p.CreatePacket(currentPeer);
								}
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("Lights out!"), p.CreatePacket(peer);
								block_->spotlight = "";
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|2646\nID|") != string::npos) {
							int netID = atoi(cch.substr(41, cch.length() - 41).c_str());
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								string new_spotlight = "";
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world) continue;
									if (block_->spotlight == pInfo(currentPeer)->tankIDName || pInfo(currentPeer)->netID == netID) {
										if (pInfo(currentPeer)->netID == netID) {
											new_spotlight = pInfo(currentPeer)->tankIDName, pInfo(currentPeer)->spotlight = true;
											gamepacket_t p;
											p.Insert("OnConsoleMessage"), p.Insert("All eyes are on you! (`$In the Spotlight`` mod added)"), p.CreatePacket(currentPeer);
										}
										else {
											gamepacket_t p;
											p.Insert("OnConsoleMessage"), p.Insert("Back to anonymity. (`$In the Spotlight`` mod removed)"), p.CreatePacket(currentPeer);
											pInfo(currentPeer)->spotlight = false;
										}
										if (new_spotlight != "") for (int i_ = 0; i_ < world_->blocks.size(); i_++) if (world_->blocks[i_].spotlight == new_spotlight) world_->blocks[i_].spotlight = "";
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You shine the light on " + (new_spotlight == pInfo(peer)->tankIDName ? "yourself" : new_spotlight) + "!"), p.CreatePacket(peer);
										update_clothes(currentPeer);
									}
								}
								block_->spotlight = new_spotlight;
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|grinder\ncount|") != string::npos) {
							int count = atoi(cch.substr(47, cch.length() - 47).c_str()), item = pInfo(peer)->lastchoosenitem, got = 0;
							modify_inventory(peer, item, got);
							if (items[item].grindable_count == 0 || got == 0 || count <= 0 || count * items[item].grindable_count > got) break;
							int remove = (count * items[item].grindable_count) * -1;
							modify_inventory(peer, item, remove);
							gamepacket_t p, p2;
							p.Insert("OnConsoleMessage"), p.Insert("Ground up " + to_string(count * items[item].grindable_count) + " " + items[item].name + " into " + to_string(count) + " " + items[items[item].grindable_prize].name + "!"), p.CreatePacket(peer);
							p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("Ground up " + to_string(count * items[item].grindable_count) + " " + items[item].name + " into " + to_string(count) + " " + items[items[item].grindable_prize].name + "!"), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
							{
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									PlayerMoving data_{};
									data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16, data_.packetType = 19, data_.plantingTree = 500, data_.punchX = items[item].grindable_prize, data_.punchY = pInfo(peer)->netID;
									int32_t to_netid = pInfo(peer)->netID;
									BYTE* raw = packPlayerMoving(&data_);
									raw[3] = 5;
									memcpy(raw + 8, &to_netid, 4);
									send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									delete[] raw;
									int c_ = count;
									if (modify_inventory(peer, items[item].grindable_prize, c_) != 0) {
										WorldDrop drop_block_{};
										drop_block_.id = items[item].grindable_prize, drop_block_.count = count, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = pInfo(peer)->x + rand() % 17, drop_block_.y = pInfo(peer)->y + rand() % 17;
										dropas_(world_, drop_block_);
									}
									{
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 221, data_.YSpeed = 221, data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16, data_.XSpeed = item;
										BYTE* raw = packPlayerMoving(&data_);
										send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										delete[] raw;
									}
								}
							}
							break;
						}

						else if (cch.find("action|dialog_return\ndialog_name|billboard_edit\nbillboard_item|") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							int billboard_item = atoi(explode("\n", t_[3])[0].c_str());
							if (billboard_item > 0 && billboard_item < items.size()) {
								int got = 0;
								modify_inventory(peer, billboard_item, got);
								if (got == 0) break;
								if (items[billboard_item].untradeable == 1 or billboard_item == 1424 or items[billboard_item].blockType == BlockTypes::LOCK or items[billboard_item].blockType == BlockTypes::FISH) {
									gamepacket_t p, p2;
									p.Insert("OnConsoleMessage"), p.Insert("Item can not be untradeable."), p.CreatePacket(peer);
									p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("Item can not be untradeable."), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
								}
								else {
									pInfo(peer)->b_i = billboard_item;
									if (pInfo(peer)->b_p != 0 && pInfo(peer)->b_i != 0) {
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("OnBillboardChange"), p.Insert(pInfo(peer)->netID), p.Insert(pInfo(peer)->b_i), p.Insert(pInfo(peer)->b_a), p.Insert(pInfo(peer)->b_p), p.Insert(pInfo(peer)->b_w);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != pInfo(peer)->world) continue;
											p.CreatePacket(currentPeer);
										}
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return") != string::npos) {
							call_dialog(peer, cch);
							break;
						}
					}
					else if (cch.find("action|dialog_return") != string::npos) {
						call_dialog(peer, cch);
						break;
					}
					break;
				}
				case 3: // world/enter

				{ //memleak risk: world enter chrono
					//auto start = chrono::steady_clock::now();
					if (pInfo(peer)->trading_with != -1) {
						cancel_trade(peer, false);
						break;
					}
					string cch = text_(event.packet);
					if (pInfo(peer)->lpps2 + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(peer)->pps2 = 0;
						pInfo(peer)->lpps2 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					}
					else {
						pInfo(peer)->pps2++;
						if (pInfo(peer)->pps2 >= 10) {
							//cout << "Over packet 3 limit from " << pInfo(peer)->tankIDName << " in world " << pInfo(peer)->world << " packet was " << cch << endl;
							enet_peer_disconnect_later(peer, 0);
							break;
						}
					}
					cout << cch << endl;
					if (pInfo(peer)->tracked) {
						ofstream trlog("track/" + pInfo(peer)->tankIDName + ".txt", ios::app);
						auto now = std::time(nullptr);
						if (cch.find("action|") != string::npos && cch.find("action|dialog_return") == string::npos) {
							trlog << "" << getDate() << "[ACTION] " << pInfo(peer)->tankIDName << ": " << cch << "\n";
						}
						if (cch.find("action|dialog_return") != string::npos) {
							trlog << "" << getDate() << "[DIALOG] " << pInfo(peer)->tankIDName << ": " << cch << "\n";
						}
						trlog.close();
					}
					if (panic_mode == 1) {
						ofstream trlog("logs/panic.txt", ios::app);
						auto now = std::time(nullptr);
						if (cch.find("action|") != string::npos && cch.find("action|dialog_return") == string::npos) {
							trlog << "" << getDate() << "[ACTION] " << pInfo(peer)->tankIDName << ": " << cch << "\n";
						}
						if (cch.find("action|dialog_return") != string::npos) {
							trlog << "" << getDate() << "[DIALOG] " << pInfo(peer)->tankIDName << ": " << cch << "\n";
						}
						trlog.close();
					} // memleak risk: track and panic logs #2

					if (cch == "action|quit") { // kai quit issaugo dar bus settings ar captcha bypassed disconnect
						if (not pInfo(peer)->tankIDName.empty()) // jeigu yra growid   
							save_player(pInfo(peer)); // issaugoti zaidejo json   
						if (pInfo(peer)->trading_with != -1) {
							cancel_trade(peer, false);
						}
						enet_peer_disconnect_later(peer, 0); // turetu nesuveikti tada antra karta save
						delete peer->data;
						peer->data = NULL;
					}
					else if (cch == "action|quit_to_exit") {
						exit_(peer);
					}
					else if (cch.find("action|join_request") != string::npos) {
						if (pInfo(peer)->last_world_enter + 500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							save_player(pInfo(peer)); // memleak risk: save
							pInfo(peer)->last_world_enter = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 3) break;
							string world_name = explode("\n", t_[2])[0];
							transform(world_name.begin(), world_name.end(), world_name.begin(), ::toupper);
							join_world(peer, world_name);
						}
					}
					//auto end = chrono::steady_clock::now();
					//pInfo(peer)->world_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
					//if (!pInfo(peer)->world.empty() || pInfo(peer)->world != "EXIT") cout << "[REQUEST]" << pInfo(peer)->world << " request " << uztruko << "ms " << endl;
					break;
				}
				case 4:
				{
					//cout << "w: " << pInfo(peer)->world << endl;
					//auto start = chrono::steady_clock::now();
					if (pInfo(peer)->lpps23 + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(peer)->pps23 = 0;
						pInfo(peer)->lpps23 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					}
					else {
						pInfo(peer)->pps23++;
						if (pInfo(peer)->pps23 >= 400) {
							//cout << "Over packet 4 limit from " << pInfo(peer)->tankIDName << " in world " << pInfo(peer)->world << endl;
							enet_peer_disconnect_later(peer, 0);
							break;
						}
					}
					if (pInfo(peer)->world.empty()) break;
					//cout << "w2: " << pInfo(peer)->world << endl;
					BYTE* data_ = get_struct(event.packet);
					if (data_ == nullptr) break;
					PlayerMoving* p_ = unpackPlayerMoving(data_);
					switch (p_->packetType) {
					case 0: /*Kai zaidejas pajuda*/
					{
						loop_cheat();
						if ((int)p_->characterState == 268435472 || (int)p_->characterState == 268435488 || (int)p_->characterState == 268435504 || (int)p_->characterState == 268435616 || (int)p_->characterState == 268435632 || (int)p_->characterState == 268435456 || (int)p_->characterState == 224 || (int)p_->characterState == 112 || (int)p_->characterState == 80 || (int)p_->characterState == 96 || (int)p_->characterState == 224 || (int)p_->characterState == 65584 || (int)p_->characterState == 65712 || (int)p_->characterState == 65696 || (int)p_->characterState == 65536 || (int)p_->characterState == 65552 || (int)p_->characterState == 65568 || (int)p_->characterState == 65680 || (int)p_->characterState == 192 || (int)p_->characterState == 65664 || (int)p_->characterState == 65600 || (int)p_->characterState == 67860 || (int)p_->characterState == 64) {
							if (pInfo(peer)->lava_time + 5000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
								pInfo(peer)->lavaeffect = 0;
								pInfo(peer)->lava_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							}
							else {
								if (pInfo(peer)->lavaeffect >= (pInfo(peer)->feet == 250 ? 7 : 3) || pInfo(peer)->lavaeffect >= (pInfo(peer)->necklace == 5426 ? 7 : 3)) {
									pInfo(peer)->lavaeffect = 0;
									SendRespawn(peer, false, 0, true);
								}
								else pInfo(peer)->lavaeffect++;
							}
						}
						if (pInfo(peer)->fishing_used != 0) {
							if (pInfo(peer)->f_xy != pInfo(peer)->x + pInfo(peer)->y) pInfo(peer)->move_warning++;
							if (pInfo(peer)->move_warning > 1) stop_fishing(peer, true, "Sit still if you wanna fish!");
							if (p_->punchX > 0 && p_->punchY > 0) {
								pInfo(peer)->punch_warning++;
								if (pInfo(peer)->punch_warning >= 2) stop_fishing(peer, false, "");
							}
						}
						string name_ = pInfo(peer)->world;
						vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
						if (p != worlds.end()) {
							World* world_ = &worlds[p - worlds.begin()];
							if (pInfo(peer)->x != -1 and pInfo(peer)->y != -1) {
								//try {
								int x_ = (pInfo(peer)->state == 16 ? (int)p_->x / 32 : round((double)p_->x / 32));
								int y_ = (int)p_->y / 32;
								if (x_ < 0 or x_ >= 100 or y_ < 0 or y_ >= 60) continue;
								WorldBlock* block_ = &world_->blocks[x_ + (y_ * 100)];
								if (block_->fg == 1256) pInfo(peer)->hospital_bed = true;
								else pInfo(peer)->hospital_bed = false;
								// When player stand on tile
								if (pInfo(peer)->c_x * 32 != (int)p_->x and pInfo(peer)->c_y * 32 != (int)p_->y and not pInfo(peer)->ghost) {
									bool NoClip = patchNoClip(world_, pInfo(peer)->x, pInfo(peer)->y, block_, peer);
									if (NoClip) {
										if (items[block_->fg].actionType != 31 or items[block_->fg].actionType != 32 or items[block_->fg].actionType != 45) {
											gamepacket_t p(0, pInfo(peer)->netID);
											p.Insert("OnSetPos");
											p.Insert(pInfo(peer)->x, pInfo(peer)->y);
											p.CreatePacket(peer);
											SendRespawn(peer, true, 0, 1);
											break;
										}
									}
								}
								if (block_->fg == 428 and not world_->name.empty() and not pInfo(peer)->OnRace) {
									gamepacket_t p(0, pInfo(peer)->netID), p3(0, pInfo(peer)->netID);
									p3.Insert("OnPlayPositioned");
									p3.Insert("audio/race_start.wav");
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == pInfo(peer)->world) {
											p3.CreatePacket(currentPeer);
										}
									}
									p.Insert("OnRaceStart"), p.CreatePacket(peer);
									pInfo(peer)->OnRace = true;
									pInfo(peer)->Race_Time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
								}
								if (block_->fg == 430 and pInfo(peer)->OnRace and not world_->name.empty()) {
									int time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() - pInfo(peer)->Race_Time;
									gamepacket_t p(0, pInfo(peer)->netID), p2, p3(0, pInfo(peer)->netID);
									p2.Insert("OnConsoleMessage");
									p2.Insert((not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : (pInfo(peer)->d_name.empty() ? pInfo(peer)->name_color : "`0") + "" + (pInfo(peer)->d_name.empty() ? pInfo(peer)->tankIDName : pInfo(peer)->d_name)) + (pInfo(peer)->is_legend ? " of Legend" : "") + " `0finished in `$" + detailMSTime(time) + "`o!``");
									p3.Insert("OnPlayPositioned");
									p3.Insert("audio/race_end.wav");
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == pInfo(peer)->world) {
											p2.CreatePacket(currentPeer), p3.CreatePacket(currentPeer);
										}
									}
									p.Insert("OnRaceEnd"), p.Insert(time), p.CreatePacket(peer);
									pInfo(peer)->OnRace = false;
									pInfo(peer)->Race_Time = 0;
								}
								if (block_->fg == 1792 and not world_->name.empty()) {
									string world_name = "LEGENDARYMOUNTAIN";
									if (pInfo(peer)->world == world_name) {
										int adaBrp = 0;
										modify_inventory(peer, 1794, adaBrp);
										if (adaBrp != 0) {
											break;
										}
										else {
											int c = 1;
											modify_inventory(peer, 1794, c);
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("`9You have claimed a Legendary Orb!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);

											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == pInfo(peer)->world) {
													gamepacket_t p3;
													p3.Insert("OnParticleEffect");
													p3.Insert(46);
													p3.Insert((float)pInfo(peer)->x + 10, (float)pInfo(peer)->y + 16);
													p3.CreatePacket(currentPeer);
												}
											}
											break;
										}
									}
								}
								if (block_->fg == 3212 and not world_->name.empty()) {
									string world_name = "GROWCH";
									if (pInfo(peer)->world == world_name) {
										int adaBrp = 0;
										modify_inventory(peer, 3210, adaBrp);
										if (adaBrp != 0) {
											break;
										}
										else {
											int c = 1;
											modify_inventory(peer, 3210, c);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == pInfo(peer)->world) {
													gamepacket_t p3;
													p3.Insert("OnParticleEffect");
													p3.Insert(46);
													p3.Insert((float)pInfo(peer)->x + 10, (float)pInfo(peer)->y + 16);
													p3.CreatePacket(currentPeer);
												}
											}
											break;
										}
									}
								}
							}
							if (pInfo(peer)->hand == 2286) {
								if (rand() % 100 < 6) {
									pInfo(peer)->geiger_++;
									if (pInfo(peer)->geiger_ >= 100) {
										int c_ = -1;
										modify_inventory(peer, 2286, c_);
										int c_2 = 1;
										modify_inventory(peer, 2204, c_2);
										pInfo(peer)->hand = 2204;
										pInfo(peer)->geiger_ = 0;
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You are detecting radiation... (`$Geiger Counting`` mod added)");
										p.CreatePacket(peer);
										packet_(peer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
										update_clothes(peer);
									}
								}
							}
							move_(peer, p_);
							if (pInfo(peer)->update) {
								if (pInfo(peer)->x == -1 and pInfo(peer)->y == -1) {
									pInfo(peer)->update = false;
									update_clothes(peer);
								}
							}
							if (pInfo(peer)->x == -1 and pInfo(peer)->y == -1) { /*Atnaujinti clothes nes uzejo i worlda*/
								update_clothes(peer);
								if (pInfo(peer)->world == "START") {
									npc_set(peer, 999931, 68, 36, 48, 78, 0, 1438, 1206, 0, 0, 2864971775);
								}
								s_log(peer, "active worlds size is " + to_string(worlds.size()));
								uint32_t my_guild_role = -1;

								gamepacket_t p3(0, pInfo(peer)->netID);
								p3.Insert("OnSetRoleSkinsAndIcons");
								p3.Insert(pInfo(peer)->roleSkin);
								p3.Insert(pInfo(peer)->roleIcon);
								p3.Insert(0);

								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == world_->name) {
										p3.CreatePacket(currentPeer);

										if (pInfo(currentPeer)->netID != pInfo(peer)->netID) {
											if (pInfo(currentPeer)->roleSkin != 6 or pInfo(currentPeer)->roleIcon != 6) {
												gamepacket_t p_p(0, pInfo(currentPeer)->netID);
												p_p.Insert("OnSetRoleSkinsAndIcons");
												p_p.Insert(pInfo(currentPeer)->roleSkin);
												p_p.Insert(pInfo(currentPeer)->roleIcon);
												p_p.Insert(0);
												p_p.CreatePacket(peer);
											}
										}
									}
								}
								long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

							}

							pInfo(peer)->x = (int)p_->x, pInfo(peer)->y = (int)p_->y, pInfo(peer)->state = p_->characterState & 0x10;

						}

						break;
					}
					case 3: /*Kai zaidejas papunchina/wrenchina bloka*/
					{
						if (p_->plantingTree <= 0 || p_->plantingTree >= items.size()) break;
						if (p_->plantingTree != 18 and p_->plantingTree != 32) {
							int c_ = 0;
							modify_inventory(peer, p_->plantingTree, c_);
							if (c_ == 0) break;
						}
						if (pInfo(peer)->trading_with != -1 and p_->packetType != 0 and p_->packetType != 18) {
							cancel_trade(peer, false, true);
							break;
						}
						if (p_->plantingTree == 18 and (pInfo(peer)->hand == 5480 || pInfo(peer)->hand == 9772 || pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770)) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
								if (block_->fg == 0 and block_->bg == 0) break;

							}
							if (p_->plantingTree == 5638 || p_->plantingTree == 6948 || p_->plantingTree == 6946) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("`wRemove your rayman before put machine!");
								p.Insert(0), p.Insert(0);
								p.CreatePacket(peer);
								break;
							}
							if (p_->punchY == pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchX == pInfo(peer)->x / 32) {
								if (p_->punchY > pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
								}
							}
							else if (p_->punchY > pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
									if (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
								}
							}

						}
						else {
							bool empty = false;
							if (p_->plantingTree == 5640) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									for (int i_ = 0; i_ < world_->machines.size(); i_++) {
										WorldMachines machine = world_->machines[i_];
										if (machine.x == pInfo(peer)->magnetron_x and machine.y == pInfo(peer)->magnetron_y and machine.id == 5638) {
											if (machine.enabled) {
												WorldBlock* itemas = &world_->blocks[machine.x + (machine.y * 100)];
												if (itemas->magnetron and itemas->id == pInfo(peer)->magnetron_id) {
													if (itemas->pr > 0) {
														p_->plantingTree = itemas->id;
														if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) {
															itemas->pr--;
															if (itemas->pr <= 0) {
																PlayerMoving data_{};
																data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																BYTE* blc = raw + 56;
																form_visual(blc, *itemas, *world_, NULL, false);
																for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																	if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																	if (pInfo(currentPeer)->world == world_->name) {
																		send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																	}
																}
																delete[] raw, blc;
															}
															break;
														}
													}
													else {
														empty = true;
														gamepacket_t p;
														p.Insert("OnTalkBubble");
														p.Insert(pInfo(peer)->netID);
														p.Insert("The `2" + items[machine.id].name + "`` is empty!");
														p.Insert(0), p.Insert(0);
														p.CreatePacket(peer);
													}
												}
											}
											break;
										}
									}
								} if (p_->plantingTree == 5640 and not empty) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("There is no active `2" + items[5638].name + "``!");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
								}
								break;
							}
							if (pInfo(peer)->hand == 5480 || pInfo(peer)->hand == 9772 || pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770) {
								int bilmem = 0;
								int blockkoydu = p_->plantingTree;
								modify_inventory(peer, blockkoydu, bilmem);
								if (p_->plantingTree == 5638 || p_->plantingTree == 6948 || p_->plantingTree == 6946) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("`wRemove your rayman before put machine!");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
									break;
								}
								if (bilmem > 4 && (pInfo(peer)->hand == 9846 || pInfo(peer)->hand == 10362 || pInfo(peer)->hand == 9770)) {
									if (p_->characterState & 0x10) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
									}
								}
								else if (bilmem > 3 && (pInfo(peer)->hand == 5480 || pInfo(peer)->hand == 9772)) {
									if (p_->characterState & 0x10) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									}
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else {
								edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
							}
						}
						break;
					}
					case 7: /*Kai zaidejas ieina pro duris arba portal*/ /*2/16/2022 update: cia dar gali buti STEAM USE*/
					{
						string name_ = pInfo(peer)->world;
						vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
						if (p != worlds.end()) {
							World* world_ = &worlds[p - worlds.begin()];
							if (p_->punchX < 0 or p_->punchX >= 100 or p_->punchY < 0 or p_->punchY >= 60) break;
							WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];

							if (items[items[block_->fg ? block_->fg : block_->bg].id].blockType == BlockTypes::CHECKPOINT) {
								pInfo(peer)->c_x = p_->punchX, pInfo(peer)->c_y = p_->punchY;
								gamepacket_t p(0, pInfo(peer)->netID);
								p.Insert("SetRespawnPos");
								p.Insert(pInfo(peer)->c_x + (pInfo(peer)->c_y * 100));
								p.CreatePacket(peer);
							}
							else if (items[block_->fg ? block_->fg : block_->bg].id == 6) exit_(peer);
							else if (items[block_->fg].blockType == BlockTypes::DOOR or items[block_->fg].blockType == BlockTypes::PORTAL) {
								string door_target = block_->door_destination, door_id = "";
								World target_world = worlds[p - worlds.begin()];
								bool locked = (block_->open ? false : (target_world.owner_name == pInfo(peer)->tankIDName or pInfo(peer)->adminLevel >= 4 or target_world.open_to_public or target_world.owner_name.empty() or (guild_access(peer, target_world.guild_id) or find(target_world.admins.begin(), target_world.admins.end(), pInfo(peer)->tankIDName) != target_world.admins.end()) ? false : true));
								int spawn_x = 0, spawn_y = 0;
								if (not locked && block_->fg != 762) {
									if (door_target.find(":") != string::npos) {
										vector<string> detales = explode(":", door_target);
										door_target = detales[0], door_id = detales[1];
									} if (not door_target.empty() and door_target != world_->name) {
										if (not check_name(door_target)) {
											gamepacket_t p(250, pInfo(peer)->netID);
											p.Insert("OnSetFreezeState");
											p.Insert(1);
											p.CreatePacket(peer);
											{
												gamepacket_t p(250);
												p.Insert("OnConsoleMessage");
												p.Insert(door_target);
												p.CreatePacket(peer);
											}
											{
												gamepacket_t p(250);
												p.Insert("OnZoomCamera");
												p.Insert((float)10000.000000);
												p.Insert(1000);
												p.CreatePacket(peer);
											}
											{
												gamepacket_t p(250, pInfo(peer)->netID);
												p.Insert("OnSetFreezeState");
												p.Insert(0);
												p.CreatePacket(peer);
											}
											break;
										}
										target_world = get_world(door_target);
									}
									int ySize = (int)target_world.blocks.size() / 100, xSize = (int)target_world.blocks.size() / ySize, square = (int)target_world.blocks.size();
									if (not door_id.empty()) {
										for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
											WorldBlock block_data = target_world.blocks[i_];
											if (block_data.fg == 1684 or items[block_data.fg].blockType == BlockTypes::DOOR or items[block_data.fg].blockType == BlockTypes::PORTAL) {
												if (block_data.door_id == door_id) {
													spawn_x = i_ % xSize, spawn_y = i_ / xSize;
													break;
												}
											}
										}
									}
								}
								if (block_->fg == 762) {
									pInfo(peer)->lastwrenchx = p_->punchX, pInfo(peer)->lastwrenchy = p_->punchY;
									gamepacket_t p2;
									if (block_->door_id == "") p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("No password has been set yet!"), p2.Insert(0), p2.Insert(1);
									else p2.Insert("OnDialogRequest"), p2.Insert("set_default_color|`o\nadd_label_with_icon|big|`wPassword Door``|left|762|\nadd_textbox|The door requires a password.|left|\nadd_text_input|password|Password||24|\nend_dialog|password_reply|Cancel|OK|");
									p2.CreatePacket(peer);
									gamepacket_t p(250, pInfo(peer)->netID), p3(250), p4(250, pInfo(peer)->netID);
									p.Insert("OnSetFreezeState"), p.Insert(1), p.CreatePacket(peer);
									p3.Insert("OnZoomCamera"), p3.Insert((float)10000.000000), p3.Insert(1000), p3.CreatePacket(peer);
									p4.Insert("OnSetFreezeState"), p4.Insert(0), p4.CreatePacket(peer);
								}
								if (block_->fg != 762) join_world(peer, target_world.name, spawn_x, spawn_y, 250, locked, true);
							}
							else {
								switch (block_->fg) {
								case 3270: case 3496:
								{
									Position2D steam_connector = track_steams(world_, block_, p_->punchX, p_->punchY);
									if (steam_connector.x != -1 and steam_connector.y != -1) {
										WorldBlock* block_s = &world_->blocks[steam_connector.x + (steam_connector.y * 100)];
										switch (block_s->fg) {
										case 3286: //steam door
										{
											block_s->flags = (block_s->flags & 0x00400000 ? block_s->flags ^ 0x00400000 : block_s->flags | 0x00400000);
											PlayerMoving data_{};
											string target_ = pInfo(peer)->tankIDName;
											data_.packetType = 5, data_.punchX = steam_connector.x, data_.punchY = steam_connector.y, data_.characterState = 0x8;
											BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, block_s));
											BYTE* blc = raw + 56;
											form_visual(blc, *block_s, *world_, peer, false);
											visual_steam(peer, target_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == world_->name) {
													send_raw(currentPeer, 4, raw, 112 + alloc_(world_, block_s), ENET_PACKET_FLAG_RELIABLE);
												}
											}
											delete[] raw, blc;
											break;
										}
										case 3724: // spirit storage unit
										{
											uint32_t scenario = 20;
											{
												// check for ghost jars
												for (int i = 0; i < world_->drop.size(); i++) {
													WorldDrop* check_drop = &world_->drop[i];
													Position2D dropped_at{ check_drop->x / 32, check_drop->y / 32 };
													if (dropped_at.x == steam_connector.x and dropped_at.y == steam_connector.y) {
														if (check_drop->id == 3722) {
															uint32_t explo_chance = check_drop->count;
															// remove drop
															{
																PlayerMoving data_{};
																data_.packetType = 14, data_.netID = -2, data_.plantingTree = check_drop->uid;
																BYTE* raw = packPlayerMoving(&data_);
																int32_t item = -1;
																memcpy(raw + 8, &item, 4);
																for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																	if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																	if (pInfo(currentPeer)->world == name_) {
																		send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																	}
																}
																world_->drop[i].id = 0, world_->drop[i].x = -1, world_->drop[i].y = -1;
																delete[] raw;
															}
															block_s->c_ += explo_chance;
															// explode or not
															{
																if (block_s->c_ * 5 >= 105) {
																	float explosion_chance = (float)((block_s->c_ * 5) - 100) * 0.5;
																	if (explosion_chance > rand() % 100) {
																		//bam bam
																		block_s->fg = 3726;
																		// drop the prize
																		{
																			vector<int> all_p{ 3734, 3732, 3748, 3712, 3706, 3708, 3718, 11136, 3728, 10056, 3730, 3788, 3750, 3738, 6060, 3738, 6840, 3736, 7784 };
																			uint32_t prize = 0;
																			if (block_s->c_ * 5 <= 115) prize = 3734;
																			else if (block_s->c_ * 5 <= 130) prize = 3732;
																			else if (block_s->c_ * 5 <= 140) prize = 3748;
																			else if (block_s->c_ * 5 <= 170) {
																				vector<int> p_drops = {
																					3712, 3706, 3708, 3718, 11136
																				};
																				prize = p_drops[rand() % p_drops.size()];
																			}
																			else if (block_s->c_ * 5 <= 190)  prize = 3728;
																			else if (block_s->c_ * 5 <= 205)  prize = 10056;
																			else if (block_s->c_ * 5 <= 220)  prize = 3730;
																			else if (block_s->c_ * 5 == 225)  prize = 3788;
																			else if (block_s->c_ * 5 <= 240)  prize = 3750;
																			else if (block_s->c_ * 5 == 245)  prize = 3738;
																			else if (block_s->c_ * 5 <= 255)  prize = 6060;
																			else if (block_s->c_ * 5 <= 265 or explo_chance * 5 >= 265) {
																				if (explo_chance * 5 >= 265) prize = all_p[rand() % all_p.size()];
																				else prize = 3738;
																			}
																			else {
																				vector<int> p_drops = {
																					6840
																				};
																				if (block_s->c_ * 5 >= 270) p_drops.push_back(3736);
																				if (block_s->c_ * 5 >= 295) p_drops.push_back(7784);
																				prize = p_drops[rand() % p_drops.size()];
																			} if (prize != 0) {
																				WorldDrop drop_block_{};
																				drop_block_.x = steam_connector.x * 32 + rand() % 17;
																				drop_block_.y = steam_connector.y * 32 + rand() % 17;
																				drop_block_.id = prize, drop_block_.count = 1, drop_block_.uid = uint16_t(world_->drop.size()) + 1;
																				dropas_(world_, drop_block_);
																				{
																					PlayerMoving data_{};
																					data_.packetType = 0x11, data_.x = steam_connector.x * 32 + 16, data_.y = steam_connector.y * 32 + 16;
																					data_.YSpeed = 97, data_.XSpeed = 3724;
																					BYTE* raw = packPlayerMoving(&data_);
																					PlayerMoving data_2{};
																					data_2.packetType = 0x11, data_2.x = steam_connector.x * 32 + 16, data_2.y = steam_connector.y * 32 + 16;
																					data_2.YSpeed = 108;
																					BYTE* raw2 = packPlayerMoving(&data_2);
																					gamepacket_t p;
																					p.Insert("OnConsoleMessage");
																					p.Insert("`#[A `9Spirit Storage Unit`` exploded, bringing forth an `9" + items[prize].name + "`` from The Other Side!]``");
																					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																						if (pInfo(currentPeer)->world == world_->name) {
																							p.CreatePacket(currentPeer);
																							send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																							send_raw(currentPeer, 4, raw2, 56, ENET_PACKET_FLAG_RELIABLE);
																						}
																					}
																					delete[] raw, raw2;
																				}
																				scenario = 22;
																			}
																		}
																		block_s->c_ = 0;
																	}
																}
															}
															// update visuals
															{
																PlayerMoving data_{};
																data_.packetType = 5, data_.punchX = steam_connector.x, data_.punchY = steam_connector.y, data_.characterState = 0x8;
																BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, block_s));
																BYTE* blc = raw + 56;
																form_visual(blc, *block_s, *world_, peer, false);
																for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																	if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																	if (pInfo(currentPeer)->world == world_->name) {
																		send_raw(currentPeer, 4, raw, 112 + alloc_(world_, block_s), ENET_PACKET_FLAG_RELIABLE);
																	}
																}
																delete[] raw, blc;
															}
															break;
														}
													}
												}
											}
											PlayerMoving data_{};
											data_.packetType = 32; // steam update paketas
											data_.punchX = steam_connector.x;
											data_.punchY = steam_connector.y;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = scenario;
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw;
											break;
										}
										default:
											break;
										}
									}
									PlayerMoving data_{};
									data_.packetType = 32; // steam update paketas
									data_.punchX = p_->punchX;
									data_.punchY = p_->punchY;
									BYTE* raw = packPlayerMoving(&data_);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
										send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									}
									delete[] raw;
									break;
								}
								default:
									break;
								}
							}
							break;
						}
						//burada break olabilir?
					}
					case 10: /*Kai zaidejas paspaudzia du kartus ant inventory itemo*/
					{
						if (pInfo(peer)->trading_with != -1) {
							cancel_trade(peer, false);
							break;
						}
						if (p_->plantingTree <= 0 or p_->plantingTree >= items.size()) break;
						int c_ = 0;
						modify_inventory(peer, p_->plantingTree, c_);
						if (c_ == 0) break;
						if (items[p_->plantingTree].blockType != BlockTypes::CLOTHING) {
							int free = get_free_slots(pInfo(peer)), slot = 1;
							int c242 = 242, c1796 = 1796, c6802 = 6802, c1486 = 1486, countofused = 0, getdl = 1, getwl = 100, removewl = -100, removedl = -1, countwl = 0, c4450 = 4450, c4452 = 4452;
							int c4298 = 4298, c4300 = 4300;
							int c7188 = 7188;
							modify_inventory(peer, p_->plantingTree, countofused);
							if (free >= slot) {
								if (p_->plantingTree == 242 || p_->plantingTree == 1796) {
									modify_inventory(peer, p_->plantingTree == 242 ? c1796 : c242, countwl);
									if (p_->plantingTree == 242 ? countwl <= 199 : countwl <= 100) {
										if (p_->plantingTree == 242 ? countofused >= 100 : countofused >= 1) {
											modify_inventory(peer, p_->plantingTree == 242 ? c242 : c1796, p_->plantingTree == 242 ? removewl : removedl);
											modify_inventory(peer, p_->plantingTree == 242 ? c1796 : c242, p_->plantingTree == 242 ? getdl : getwl);
											gamepacket_t p, p2;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(p_->plantingTree == 242 ? "You compressed 100 `2World Lock`` into a `2Diamond Lock``!" : "You shattered a `2Diamond Lock`` into 100 `2World Lock``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
											p2.Insert("OnConsoleMessage"), p2.Insert(p_->plantingTree == 242 ? "You compressed 100 `2World Lock`` into a `2Diamond Lock``!" : "You shattered a `2Diamond Lock`` into 100 `2World Lock``!"), p2.CreatePacket(peer);
										}
									}
								}
								else if (p_->plantingTree == 7188) {
									modify_inventory(peer, c1796, countwl);
									if (countwl <= 100) {
										if (countofused >= 1) {
											modify_inventory(peer, c7188, removedl);
											modify_inventory(peer, c1796, getwl);
											gamepacket_t p, p2;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You shattered a `2Blue Gem Lock`` into 100 `2Diamond Lock``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
											p2.Insert("OnConsoleMessage"), p2.Insert("You shattered a `2Blue Gem Lock`` into 100 `2Diamond Lock``!"), p2.CreatePacket(peer);
										}
									}
								}
								else if (p_->plantingTree == 1486 || p_->plantingTree == 6802) {
									modify_inventory(peer, p_->plantingTree == 1486 ? c6802 : c1486, countwl);
									if (p_->plantingTree == 1486 ? countwl <= 199 : countwl <= 100) {
										if (p_->plantingTree == 1486 ? countofused >= 100 : countofused >= 1) {
											modify_inventory(peer, p_->plantingTree == 1486 ? c1486 : c6802, p_->plantingTree == 1486 ? removewl : removedl);
											modify_inventory(peer, p_->plantingTree == 1486 ? c6802 : c1486, p_->plantingTree == 1486 ? getdl : getwl);
											gamepacket_t p, p2;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(p_->plantingTree == 1486 ? "You compressed 100 `2Growtoken`` into a `2Mega Growtoken``!" : "You shattered a `2Mega Growtoken`` into 100 `2Growtoken``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
											p2.Insert("OnConsoleMessage"), p2.Insert(p_->plantingTree == 1486 ? "You compressed 100 `2Growtoken`` into a `2Mega Growtoken``!" : "You shattered a `2Mega Growtoken`` into 100 `2Growtoken``!"), p2.CreatePacket(peer);
										}
									}
								}
								else if (p_->plantingTree == 4450 || p_->plantingTree == 4452) {
									modify_inventory(peer, p_->plantingTree == 4450 ? c4452 : c4450, countwl);
									if (p_->plantingTree == 4450 ? countwl <= 199 : countwl <= 100) {
										if (p_->plantingTree == 4450 ? countofused >= 100 : countofused >= 1) {
											modify_inventory(peer, p_->plantingTree == 4450 ? c4450 : c4452, p_->plantingTree == 4450 ? removewl : removedl);
											modify_inventory(peer, p_->plantingTree == 4450 ? c4452 : c4450, p_->plantingTree == 4450 ? getdl : getwl);
											gamepacket_t p, p2;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(p_->plantingTree == 4450 ? "You compressed 100 `2Zombie Brain`` into a `2Pile of Zombie Brains``!" : "You shattered a `2Pile of Zombie Brains`` into 100 `2Zombie Brain``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
											p2.Insert("OnConsoleMessage"), p2.Insert(p_->plantingTree == 4450 ? "You compressed 100 `2Zombie Brain`` into a `2Pile of Zombie Brains``!" : "You shattered a `2Pile of Zombie Brains`` into 100 `2Zombie Brain``!"), p2.CreatePacket(peer);
										}
									}
								}
								else if (p_->plantingTree == 4298 || p_->plantingTree == 4300) {
									modify_inventory(peer, p_->plantingTree == 4298 ? c4300 : c4298, countwl);
									if (p_->plantingTree == 4298 ? countwl <= 199 : countwl <= 100) {
										if (p_->plantingTree == 4298 ? countofused >= 100 : countofused >= 1) {
											modify_inventory(peer, p_->plantingTree == 4298 ? c4298 : c4300, p_->plantingTree == 4298 ? removewl : removedl);
											modify_inventory(peer, p_->plantingTree == 4298 ? c4300 : c4298, p_->plantingTree == 4298 ? getdl : getwl);
											gamepacket_t p, p2;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(p_->plantingTree == 4298 ? "You compressed 100 `2Caduceus`` into a `2Golden Caduceus``!" : "You shattered a `2Golden Caduceus`` into 100 `2Caduceus``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
											p2.Insert("OnConsoleMessage"), p2.Insert(p_->plantingTree == 4298 ? "You compressed 100 `2Caduceus`` into a `2Golden Caduceus``!" : "You shattered a `2Golden Caduceus`` into 100 `2Caduceus``!"), p2.CreatePacket(peer);
										}
									}
								}
							}
							/*compress ir t.t*/
							break;
						}
						/*equip*/
						equip_clothes(peer, p_->plantingTree);
						break;
					}
					case 11: /*collect droped item*/
					{
						string name_ = pInfo(peer)->world;
						vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
						World* world_ = &worlds[p - worlds.begin()];
						if (p_->x < 0 || p_->y < 0) break;
						bool displaybox = true;
						if (p != worlds.end()) {
							World* world_ = &worlds[p - worlds.begin()];
							for (int i_ = 0; i_ < world_->drop.size(); i_++) {
								if (world_->drop[i_].id == 0 or world_->drop[i_].x / 32 < 0 or world_->drop[i_].x / 32 > 99 or world_->drop[i_].y / 32 < 0 or world_->drop[i_].y / 32 > 59) continue;
								WorldBlock* block_ = &world_->blocks[world_->drop[i_].x / 32 + (world_->drop[i_].y / 32 * 100)];
								if (world_->drop[i_].uid == p_->plantingTree) {
									if (block_->fg == 1422 || block_->fg == 2488) {
										displaybox = false;
										if (pInfo(peer)->adminLevel == 7 || pInfo(peer)->adminLevel == 6 || pInfo(peer)->adminLevel == 5 || pInfo(peer)->adminLevel == 4 || pInfo(peer)->adminLevel == 3 || pInfo(peer)->adminLevel == 2 || pInfo(peer)->adminLevel == 1 || world_->open_to_public || world_->owner_name == "" || world_->owner_name == pInfo(peer)->tankIDName || find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) != world_->admins.end()) displaybox = true;
									}
									if (abs((int)p_->x / 32 - world_->drop[i_].x / 32) > 1 || abs((int)p_->x - world_->drop[i_].x) >= 32 or abs((int)p_->y - world_->drop[i_].y) >= 32) displaybox = false;
									if (displaybox) {
										int c_ = world_->drop[i_].count;
										if (world_->drop[i_].id == world_->special_event_item && world_->special_event && world_->drop[i_].special) {
											world_->special_event_item_taken++;
											if (items[world_->special_event_item].event_total == world_->special_event_item_taken) {
												gamepacket_t p, p3;
												p.Insert("OnAddNotification"), p.Insert("interface/large/special_event.rttex"), p.Insert("`2" + items[world_->special_event_item].event_name + ":`` `oSuccess! " + (items[world_->special_event_item].event_total == 1 ? "`2" + pInfo(peer)->tankIDName + "`` found it!``" : "All items found!``") + ""), p.Insert("audio/cumbia_horns.wav"), p.Insert(0);
												p3.Insert("OnConsoleMessage"), p3.Insert("`2" + items[world_->special_event_item].event_name + ":`` `oSuccess!`` " + (items[world_->special_event_item].event_total == 1 ? "`2" + pInfo(peer)->tankIDName + "`` `ofound it!``" : "All items found!``") + "");
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
													if (items[world_->special_event_item].event_total != 1) {
														gamepacket_t p2;
														p2.Insert("OnConsoleMessage"), p2.Insert("`2" + items[world_->special_event_item].event_name + ":`` `0" + pInfo(peer)->tankIDName + "`` found a " + items[world_->special_event_item].name + "! (" + to_string(world_->special_event_item_taken) + "/" + to_string(items[world_->special_event_item].event_total) + ")``"), p2.CreatePacket(currentPeer);
													}
													p.CreatePacket(currentPeer);
													p3.CreatePacket(currentPeer);
												}
												world_->last_special_event = 0, world_->special_event_item = 0, world_->special_event_item_taken = 0, world_->special_event = false;
											}
											else {
												gamepacket_t p2;
												p2.Insert("OnConsoleMessage"), p2.Insert("`2" + items[world_->special_event_item].event_name + ":`` `0" + pInfo(peer)->tankIDName + "`` found a " + items[world_->special_event_item].name + "! (" + to_string(world_->special_event_item_taken) + "/" + to_string(items[world_->special_event_item].event_total) + ")``");
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
													p2.CreatePacket(currentPeer);
												}
											}
										}
										if (p_->x * 32 == world_->drop[i_].x * 32 && p_->y * 32 == world_->drop[i_].y * 32) break;
										if (modify_inventory(peer, world_->drop[i_].id, c_, false, true) == 0 or world_->drop[i_].id == 112) {
											string messages = pInfo(peer)->tankIDName + " collect " + to_string(world_->drop[i_].count) + " " + items[world_->drop[i_].id].name + " in " + pInfo(peer)->world;
											ofstream file("logs/collect.txt", ios::app);
											if (file.is_open()) {
												auto now = time(nullptr);
												file << "" << getDate() << " " << messages << "\n";
											}
											file.close();
											PlayerMoving data_{};
											data_.effect_flags_check = 1, data_.packetType = 14, data_.netID = pInfo(peer)->netID, data_.plantingTree = world_->drop[i_].uid;
											BYTE* raw = packPlayerMoving(&data_);
											if (world_->drop[i_].id == 112) pInfo(peer)->gems += c_;
											else {
												add_cctv(peer, "took", to_string(world_->drop[i_].count) + " " + items[world_->drop[i_].id].name);
												gamepacket_t p;
												p.Insert("OnConsoleMessage"), p.Insert("Collected `w" + to_string(world_->drop[i_].count) + "" + (items[world_->drop[i_].id].blockType == BlockTypes::FISH ? "lb." : "") + " " + items[world_->drop[i_].id].ori_name + "``." + (items[world_->drop[i_].id].rarity > 363 ? "" : " Rarity: `w" + to_string(items[world_->drop[i_].id].rarity) + "``") + ""), p.CreatePacket(peer);
											}
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[]raw;
											world_->drop[i_].id = 0, world_->drop[i_].x = -1, world_->drop[i_].y = -1;
										}
										else {
											if (c_ < 200 and world_->drop[i_].count >(200 - c_)) {
												int b_ = 200 - c_;
												world_->drop[i_].count -= b_;
												if (modify_inventory(peer, world_->drop[i_].id, b_, false) == 0) {
													add_cctv(peer, "took", to_string(world_->drop[i_].count) + " " + items[world_->drop[i_].id].name);
													WorldDrop drop_{};
													drop_.id = world_->drop[i_].id, drop_.count = world_->drop[i_].count, drop_.uid = uint16_t(world_->drop.size()) + 1, drop_.x = world_->drop[i_].x, drop_.y = world_->drop[i_].y;
													world_->drop.push_back(drop_);
													gamepacket_t p;
													p.Insert("OnConsoleMessage");
													p.Insert("Collected `w" + to_string(200 - c_) + " " + items[world_->drop[i_].id].ori_name + "``." + (items[world_->drop[i_].id].rarity > 363 ? "" : " Rarity: `w" + to_string(items[world_->drop[i_].id].rarity) + "``") + "");
													PlayerMoving data_{};
													data_.packetType = 14, data_.netID = -1, data_.plantingTree = world_->drop[i_].id, data_.x = world_->drop[i_].x, data_.y = world_->drop[i_].y;
													int32_t item = -1;
													float val = world_->drop[i_].count;
													BYTE* raw = packPlayerMoving(&data_);
													data_.plantingTree = world_->drop[i_].id;
													memcpy(raw + 8, &item, 4);
													memcpy(raw + 16, &val, 4);
													val = 0;
													data_.netID = pInfo(peer)->netID;
													data_.plantingTree = world_->drop[i_].uid;
													data_.x = 0, data_.y = 0;
													BYTE* raw2 = packPlayerMoving(&data_);
													BYTE val2 = 0;
													memcpy(raw2 + 8, &item, 4);
													memcpy(raw2 + 16, &val, 4);
													memcpy(raw2 + 1, &val2, 1);
													world_->drop[i_].id = 0, world_->drop[i_].x = -1, world_->drop[i_].y = -1;
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
														send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
														if (pInfo(currentPeer)->netID == pInfo(peer)->netID)
															p.CreatePacket(currentPeer);
														send_raw(currentPeer, 4, raw2, 56, ENET_PACKET_FLAG_RELIABLE);
													}
													delete[]raw, raw2;
												}
											}
										}
									}
								}
							}
						}
						break;
					}
					case 18: { //chat bubble kai raso
						move_(peer, p_);
						break;
					}
					case 23: /*Kai zaidejas papunchina kita*/
					{
						if (pInfo(peer)->last_inf + 5000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							pInfo(peer)->last_inf = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								bool can_cancel = true;
								if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 1276) != world_->active_jammers.end()) can_cancel = false;
								if (can_cancel) {
									if (pInfo(peer)->trading_with != -1 and p_->packetType != 0 and p_->packetType != 18) {
										cancel_trade(peer, false, true);
										break;
									}
								}
							}
						}

						break;
					}
					default:
					{
						break;
					}
					}
					break;
				}
				default:
					break;
				}
				enet_event_destroy(event);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				if (saving_) break;
				if (peer->data != NULL) {
					if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
					if (not pInfo(peer)->world.empty()) exit_(peer, true);
					if (not pInfo(peer)->invalid_data) {
						save_player(pInfo(peer), (f_saving_ ? false : true));
					}
					if (f_saving_) pInfo(peer)->saved_on_close = true;
					if (not f_saving_) {
						enet_host_flush(server);
						delete peer->data;
						peer->data = NULL;
					}
				}
				break;
			}
			default:
				break;
			}
		}
	}
	return 0;
}