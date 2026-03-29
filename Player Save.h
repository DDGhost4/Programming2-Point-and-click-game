#include <string>
#include <string_view>
#include <vector>


class SaveAndLoad {
public:
	
	

	void setCurrentInventory(std::string item);//Place the parameters for this before testing

	std::string_view getCurrentInventory() const;

	void setCurrentRoom(int );//Place the parameters for this before testing

	int getCurrentRoom() const;

	void setCurrentStats(int health, int attack, int defense);

	int getCurrentStats() const;



private:
	std::vector <std::string> m_invenotory;
	int m_attack;
	int m_defense;
	int m_health;
	int m_room;
	
};

class CreateSave {
public:
	void create()

private:
	bool m_created{};

};

class DeleteSave {
public:

private:
	
};