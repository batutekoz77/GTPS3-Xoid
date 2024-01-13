#pragma once
#include <chrono>
#include "enet/dirent.h"
#include <sstream>
#include <filesystem>
#include "NewPacket.h"
#include <sstream>
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
int Heart_Size = 0, Last_Heart_Size = 0, Progress_Making_Happy = 0;
long long int Growch_Happy_Time = 0;

inline void Save_Winterfest_File() {
	if (!Winterfest) return;
	json save_;
	save_["Heart_Size"] = Heart_Size;
	save_["Last_Heart_Size"] = Last_Heart_Size;
	save_["Progress_Making_Happy"] = Progress_Making_Happy;
	save_["Growch_Happy_Time"] = Growch_Happy_Time;
	ofstream w_("WinterFest/WinterFest.json");
	if (w_.fail()) {
		cout << "failed to save winterfest file " << endl;
		return;
	}
	w_ << save_ << endl;
	w_.close();
}
inline void Load_Winterfest_File() {
	if (!Winterfest) return;
	string path_ = "WinterFest/WinterFest.json";
	if (_access_s(path_.c_str(), 0) == 0) {
		try {
			json r_;
			ifstream f_(path_, ifstream::binary);
			if (f_.fail()) {
				cout << "failed reading data for winterfest file " << endl;
			}
			f_ >> r_;
			f_.close();
			Heart_Size = r_["Heart_Size"].get<int>();
			Last_Heart_Size = r_["Last_Heart_Size"].get<int>();
			Progress_Making_Happy = r_["Progress_Making_Happy"].get<int>();
			Growch_Happy_Time = r_["Growch_Happy_Time"].get<long long int>();
		}
		catch (exception) {
			Save_Winterfest_File();
		}
	}
}

inline void GrowchHeartSystem() {
	if (!Winterfest) return;
	string name_ = "GROWCH";
	vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
	if (p != worlds.end()) {
		World* world_ = &worlds[p - worlds.begin()];
		if (Heart_Size != Last_Heart_Size) {
			world_->weather = 13;
			Growch_Happy_Time = time(nullptr) + (300 * 60);
			gamepacket_t p, p1, p2, p3;
			p.Insert("OnSetCurrentWeather"); p.Insert(13);
			p1.Insert("OnConsoleMessage");
			if (Heart_Size == 1) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Tangyuan``, `#Elf Hat``, `#Icicles``, `#Snow Crust Block``, `#Partridge in a Pear Tree`` ***``");
			if (Heart_Size == 2) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Candy Cane Block``, `#Reindeer Bell``, `#Lumber Axe``, `#Gingerbread Man Mask``, `#Snowy Rocks Platform`` ***``");
			if (Heart_Size == 3) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Snowball``, `#Yeti Hat``, `#Festivus Pole``, `#Abominable Snowman Suit``, `#Abominable Snowman Mask``, `#Last Christmas Cut`` ***``");
			if (Heart_Size == 4) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Giant Candle``, `#Buckskin Pants``, `#Snow Husky``, `#Winterfest Checkpoint`` ***``");
			if (Heart_Size == 5) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Candy Cane Fence``, `#Buckskin Jacket``, `#Winter Flu Vaccine``, `#Pumpkin Pie``, `#Eggnog``, `#Zamgrowni``, `#Dinosaur in Ice Block`` ***``");
			if (Heart_Size == 6) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Antler Hat``, `#Buckskin Hood``, `#Snowmobile``, `#Ice Sculptures``, `#Chocolate Checkpoint`` ***``");
			if (Heart_Size == 7) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Glowing Nose``, `#Candy Cane Platform``, `#Sock On The Wall``, `#Candy Cane Streetlamp``, `#Dancing Snow Globe`` ***``");
			if (Heart_Size == 8) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Holiday Cheer Bomb``, `#Parka Hood - Orange``, `#Ice Dragon Hand``, `#Parka Hood - Blue``, `#Puffy Blue Jacket``, `#Cloak of Fire and Ice``, `#Malanka Mask`` ***``");
			if (Heart_Size == 9) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Yeonnalligi``, `#Magic Reindeer Bell``, `#Riding Winter Wolf``, `#Armored WinterBot - Feet``, `#Ice Shard Hair`` ***``");
			if (Heart_Size == 10) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Holiday Gift Box``, `#Mighty Snow Rod``, `#Gingerbread Man``, `#Snow Leopard Shawl`` ***``");
			if (Heart_Size == 11) p1.Insert("`w*** `2The Growch's heart has grown a size bigger``! New items available: `#Snow Leopard Tail``, `#Snow Husky Sledge``, `#Armored WinterBot - Fists``, `#Aura Antlers`` ***``");
			p2.Insert("OnAddNotification"), p3.Insert("OnConsoleMessage");
			p2.Insert("interface/large/special_event.rttex"), p2.Insert("`2Party With The Growch!:`` `oCelebrate the holidays with your ol' buddy, the `2Growch``!``"), p2.Insert("audio/gong.wav"), p2.Insert(0);
			p3.Insert("`2Party With The Growch!:`` `oCelebrate the holidays with your ol' buddy, the `2Growch``!``");
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				packet_(currentPeer, "action|play_sfx\nfile|audio/love_in.wav\ndelayMS|0");
				p1.CreatePacket(currentPeer);
				if (pInfo(currentPeer)->world == world_->name) {
					p.CreatePacket(currentPeer), p2.CreatePacket(currentPeer), p3.CreatePacket(currentPeer);
					packet_(currentPeer, "action|play_music\nfile|audio/mp3/loop_disco.mp3\ndelayMS|0");
					packet_(currentPeer, "action|play_sfx\nfile|audio/love_in.wav\ndelayMS|0");
				}
			}
			Save_Winterfest_File();
		}
		if (Growch_Happy_Time - time(nullptr) <= 0) {
			world_->weather = 12;
			Last_Heart_Size = Heart_Size;
			Progress_Making_Happy = 0;
			gamepacket_t p;
			p.Insert("OnSetCurrentWeather"); p.Insert(12);
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->world == world_->name) {
					p.CreatePacket(currentPeer);
				}
			}
			Save_Winterfest_File();
		}
	}
}

