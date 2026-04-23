# Dungeon Divers
This project leads the player into a point-and-click style dungeon adventure game where they will venture through 10 different randomized rooms. Where they will need to fight against different enemies and will be able to do different things like heal with potions, find new and better armorand weapons.

---
## Team Members
- Rafael Casillas
- Damien Provost
- Dillon Sitepu
- Oren Dagta
---
## How to Run
### Requirements
- Visual Studio 2022
- SFML
### Steps
1. Open the project in Visual Studio
2. Click **Local Windows Debugger** to run
### Notes
- Open the `.sln` file to open project
---
## Features
- automatically saves progress whenever the player enters a new room
- loads save file when player selects "load" at main menu
- multiple upgrades for items
- randomized rooms and chances for getting items between starting and ending rooms
---
## OOP Concepts Used
### Encapsulation
- The items’ health that is replenished and the effect of equipment on the player’s stats will be kept private and have to be called in the items function definition.
### Inheritance
- Used with the player class and the enemy class, which consists of the skeleton and ghost, which are derived classes from the base class Actor.
### Polymorphism
- Within the header file for the items, base class; items, contains multiple virtual functions that determine whether to execute equipping any armor, shield, or sword, or add health to the actor’s current health after using the health potion.
### Composition
- Player class has-a actress’ stats in the form of actor health, attack damage, and defense. Which appears for all actors player, skeleton, and ghost.
### Abstraction
- The Items class in Item.h file uses a pure virtual function to allow individual specific implementations of getName() for each item.
---
## Team Contributions
### Member 1: Damien Provost
- GUI
### Member 2: Oren Dagta
- Items and item functions
### Member 3: Rafael Casillas
- Save and load
- Actor and combat
### Member 4: Dillon Sitepu
- Inventory
- Rooms
- Actor and combat
---
## AI and External Resources Disclosure (Required)
You must clearly document **all external help used** in this project.
### AI Tools
List any AI tools used (e.g., ChatGPT, Copilot, etc.) and describe:
- ChatGPT: initialized multiple varients of an items and understood the significance of using virtual functions
- CoPilot: helped with understanding of what was going wrong and how to fix, and understand files stream and unique pointers
### External Resources
List all non-AI resources used:
- Stack Overflow
- https://www.sfml-dev.org/#sfml-is-multi-language (SFML multimedia library)
### Collaboration Policy Statement
All submitted work reflects our team’s understanding. Any external code
has been:
- Reviewed
- Modified as needed
- Integrated by our team
Failure to disclose AI or external resources may be considered an academic
integrity violation.
---
## Additional Notes (Optional)
- requires command prompt along with graphics window
- better graphics more features
