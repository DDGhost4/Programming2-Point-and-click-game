#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <filesystem>
#include "Items.h"
#include "Room.h"


struct Stats {
    int HP; //health points
    int ATT; //attack
    int DEF; //defense
    Stats() : HP(0), ATT(0), DEF(0) {}
    Stats(int hp, int att, int def) : HP(hp), ATT(att), DEF(def) {}
};

class SaveData {
public:
    SaveData();

    void addItem(std::unique_ptr<Items> item) {
        m_inventory.push_back(std::move(item));
    }

    const std::vector<std::unique_ptr<Items>>& getCurrentInventory() const {
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
    std::vector<std::unique_ptr<Items>> m_inventory;
    Stats m_stats{};
    int m_room{ 0 };
};



class SaveSystem {
public:
    SaveSystem();

    bool loadSaveFile(const std::filesystem::path& file, SaveData& out); //Loads the save
    bool deleteSaveFile(const std::filesystem::path& file); //deletes save file
    void storeSaveName() {
        std::string filename;
        std::getline(std::cin, filename);
        m_filename = filename;
    }
    std::string getSaveName() {
        return m_filename;
    }
    bool createSaveFile(const std::filesystem::path& file);
    bool saveToFile(const std::filesystem::path& file, const SaveData& data) const; //saves to the file

private:
    std::string m_filename;

};