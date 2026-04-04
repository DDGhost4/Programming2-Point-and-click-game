#include <fstream>
#include <filesystem>
#include <string>
#include <format>
#include <iostream>
#include "Player Save.h"

SaveData::SaveData() : m_inventory(), m_stats(0,0,0), m_room(0) {};

SaveSystem::SaveSystem() {};

bool SaveSystem::loadSaveFile(const std::filesystem::path& file, SaveData& out) {
	std::ifstream ifs(file, std::ios::in);
	if (!ifs) {
		return false;
	}
	
	// read room
	int room;
	if (!(ifs >> room)) {
		ifs.close();
		return false;
	}
	out.setCurrentRoom(room);
	
	// read stats
	Stats s;
	if (!(ifs >> s.ATT >> s.DEF >> s.HP)) {
		ifs.close();
		return false;
	}
	out.setCurrentStats(s);
	
	// read inventory count
	size_t inventoryCount;
	if (!(ifs >> inventoryCount)) {
		ifs.close();
		return false;
	}
	
	ifs.ignore(10000, '\n');
	
	// read each inventory item
	std::string item;
	for (size_t i = 0; i < inventoryCount; ++i) {
		if (!getline(ifs, item)) {
			ifs.close();
			return false;
		}
		out.addItem(item);
	}
	
	ifs.close();
	return true;
}


bool SaveSystem::saveToFile(const std::filesystem::path& file,const SaveData& data) const {
	std::ofstream ofs(file);
	if (!ofs) {
		return false;
	}
	else {
		
       // write basic player info
		ofs << data.getCurrentRoom() << '\n';
		Stats s = data.getCurrentStats();
		ofs << s.ATT << '\n' << s.DEF << '\n' << s.HP << '\n';

		// write inventory: first the count, then each item on its own line
		const auto& inv = data.getCurrentInventory();
		ofs << inv.size() << '\n';
		for (const auto& item : inv) {
			ofs << item << '\n';
		}

		ofs.close();
		// if file was written and closed without errors, return true
		return !ofs.fail();
	}
}




bool SaveSystem::deleteSaveFile(const std::filesystem::path& file) {
	remove(file);
	return !std::filesystem::exists(file);
}
