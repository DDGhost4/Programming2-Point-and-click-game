#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <memory>
#include "Items.h"
#include "Player Save.h"
#include "Room.h"



SaveData::SaveData() : m_inventory(), m_stats(0, 0, 0), m_room(0) {};

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
	std::string itemType;
	for (size_t i = 0; i < inventoryCount; ++i) {
		if (!std::getline(ifs, itemType)) {
			ifs.close();
			return false;
		}
		else if (itemType == "HPotion") { out.addItem(std::make_unique<HPotion>()); }
		else if (itemType == "Sword") { out.addItem(std::make_unique<Swords>()); }
		else if (itemType == "Shield") { out.addItem(std::make_unique<Shields>()); }
	}


	ifs.close();
	return true;
}


bool SaveSystem::saveToFile(const std::filesystem::path& file, const SaveData& data) const {
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
			if (dynamic_cast<HPotion*>(item.get())) {
				ofs << "HPotion\n";
			}
			else if (dynamic_cast<Swords*>(item.get())) {
				ofs << "Sword\n";
			}
			else if (dynamic_cast<Shields*>(item.get())) {
				ofs << "Shield\n";
			}
		}
	}
	ofs.close();
	// if file was written and closed without errors, return true
	return !ofs.fail();
}


bool SaveSystem::createSaveFile(const std::filesystem::path& file) {
	std::ofstream create(file, std::ios::out);
	if (!create) {
		return false;
	}
	return !create.fail();
}

bool SaveSystem::deleteSaveFile(const std::filesystem::path& file) {
	remove(file);
	return !std::filesystem::exists(file);
}