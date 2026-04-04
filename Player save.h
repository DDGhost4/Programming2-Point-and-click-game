#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

struct Stats {
    int HP; //health points
    int ATT; //attack
    int DEF; //defense
    Stats() :HP(0), ATT(0), DEF(0) {}
    Stats(int hp, int att, int def) : HP(hp), ATT(att), DEF(def) {}
};

class SaveData {
public:
    SaveData();

    void addItem(const std::string& item) {
        m_inventory.push_back(item);
    }

    const std::vector<std::string>& getCurrentInventory() const {
        return m_inventory;
    }

    void setCurrentRoom(int roomnum) {
        m_room = roomnum;
    }

    int getCurrentRoom() const {
        return m_room;
    }

    void setCurrentStats(const Stats& s) {
        m_stats = s;
    }

    Stats getCurrentStats() const {
        return m_stats;
    }

private:
    std::vector<std::string> m_inventory;
    Stats m_stats{};
    int m_room{0};
};



class SaveSystem {
public:

    SaveSystem();

	bool loadSaveFile(const std::filesystem::path& file, SaveData& out); //Loads the save
	bool deleteSaveFile(const std::filesystem::path& file); //deletes save file
	bool saveToFile(const std::filesystem::path& file, const SaveData& data) const ; //saves to the file

};
