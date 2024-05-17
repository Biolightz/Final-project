/*finalP.cpp
Alexx DeLacy, CISP 360
5/16/24
Final Project - Text-based RPG Adventure
Professor Caleb Fowler
*/



#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

/*Map for you professor after you play!

- .... . / -- .- .--. / .. ... / .-.. / ... .... .- .--. .

*/



//There are 3 possible endings. (EXIT, Secret Hatch, Cthulhu instant game over)
// "Zone" instead of "room" sounds better for "RPG" asepects/theme
// This took an outline and 2 1/2 itterations. Completely retyped after getting lost and melting my code. >.>
// Pretty much works. Some bugs I couldn't fix without breaking something else.
// Outline before coding is in canvas as well.

//monsters //Space Marine
           //Xenomorph
           //Corrupted Human
           //Boss - Cthulhu
                    
struct Monsters {       // Struct as taught in lecture. For monster container.
    string name;
    string details;
    int health;
    int damage;
};


struct Player {  //Struct system for player health in combat container.
    int health;
    int damage;
};

//Function Prototypes
// Speciﬁcation C2 - Three Functions
void filelogMesg(const string& message);
void ProgGreet();   // Greeting before start of game
void gameLOOP();    // Main gameloop
void mainMENU();    // Full main menu with 3 options
void underttlINTRO();   // Game intro for uhhh "Role playing reasons? Why not"
void playerCOMB(Player& player, Monsters& monster); // Combat function for player vs monster.


// Speciﬁcation C1 - Main Data Structure 
struct Zone {           // Visible Main Data Structure
    string name_zone;
    string details_zone;
    bool occ_monster;   // Monster occupies room
    int id_zone;        // Zone ID details
    char escapes[4]; // NSEW navigation directions
    Monsters monster; // Monster to spawn in a zone
};

// Speciﬁcation C3 - Function Activity to Disk
void filelogMesg(const string& strtext){    //live outputs to file in log.text
    ofstream logfile("log.txt", ios::app); // Opens append mode to log to file.
    if (logfile.is_open()) {
    time_t live = time(0); // Pulls current time of execution.
    tm* cfts = localtime(&live); // Current time as a string. cfts = Call function, time, string   
    logfile << "[" << 1900 + cfts->tm_year << "-" << 1 + cfts->tm_mon << "-" << cfts->tm_mday << " "; // Year, month and day of month
    logfile << cfts->tm_hour << ":" << cfts->tm_min << ":" << cfts->tm_sec << "] " << strtext << endl; // Minutes, seconds, string
    }

}


int main() {
    filelogMesg("Game starting...............");
    // Speciﬁcation C2 - Three Functions
    ProgGreet();
    mainMENU();
    return 0;
}
//Function Descriptions 
void ProgGreet() {
    cout << "                     Welcome to Lightz - Text-based RPG Adventure!" << endl;
    cout << "                                     Let's begin!" << endl;
    filelogMesg("Greeting has been displayed successfully.");
}


void mainMENU() {
    filelogMesg("Main menu has been displayed successfully.");
    int choice;
    bool valid_choice = false;

    while (!valid_choice) {
        cout << "                     +-------------------------------------------+\n";
        cout << "                     | +=======================================+ |\n";
        cout << "                     | |  -  Now Entering: Project Solaris  -  | |\n";
        cout << "                     | +=======================================+ |\n";
        cout << "                     |                                           |\n";
        cout << "                     |                 < MAIN MENU >             |\n";
        cout << "                     |                                           |\n";
        cout << "                     |        ~{     1. > Start Game     }~      |\n"; // Will start game & INTRO
        cout << "                     |                                           |\n";
        cout << "                     |        ~{     2. > How to Play    }~      |\n";
        cout << "                     |                                           |\n";
        cout << "                     |        ~{     3. > Quit Game      }~      |\n";
        cout << "                     |                                           |\n";
        cout << "                     +-------------------------------------------+\n";
        cout << "                      > Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                // Speciﬁcation C2 - Three Functions
                underttlINTRO(); // Display introduction wihtout input
                gameLOOP(); // Start the main game loop to continue forward
                valid_choice = true;
                break;
            case 2:                  // Display how to play instructions upon typing 2.             
                cout << "How to Play: \n"
                     << "\n"
                     << "1. You are to explore the ship using N, S, W, E  (L)commands.\n"
                     // Specification B1 - Abbreviated Room Description
                     // Speciﬁcation B2 - Detailed Look
                     << "2. Type 'L' to look around the zone and provide current adventure/zone/monster details.\n"
                     << "3. Combat is automated and damage is random. Infection after monster death. Damage happens simultaneously.\n"
                     << "4. Caps sensitive (instructions say in all caps N, S, E, W)\n"
                     << "5. Good luck in there!! For Democracy!!\n"
                     << "\n"
                     << "OBJECTIVE: Find the Command Center and escape with the ship. [Or your life]\n"
                     << "\n";
                cout << "Please press 1 to return to main menu.\n";
                cin >> choice;
                
                while (choice != 1) {
                    // Specification B3 - Input Validation
                    cout << "Invalid choice. Please press 1 to return to main menu.\n";
                    cin >> choice;
                }
                break;
            case 3: // Exits the game upon 3.
                cout << "Exiting the game. Goodbye!\n";
                exit(0);
                break;
            default:
            // Specification B3 - Input Validation
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                break;
        }
    }
}

void underttlINTRO() {
    filelogMesg("Introduction has been displayed successfully.");
    cout << "**************************************************************************************************\n"
         << "* The story begins with a maiden voyage of The Aurora Voyager. Named after the old Stellar God.  *\n"
         << "* The docking onto a derelict ship is currently taking place. You are facing the airlock panel.  *\n"
         << "*                                                                                                *\n"
         << "*      > The door to the derelict Ship has been opened.                                          *\n"
         << "**************************************************************************************************\n"
         << "* As the door to the airlock slowly glides open. You walk forward. Steam starts to fill the zone *\n"
         << "* as the door shuts behind you, much faster than before. You feel chills up your spine... as     *\n"
         << "* if... something is wrong. It starts to appear very quiet as your eyes start to close......     *\n"
         << "*                                                                                                *\n"
         << "* You have woken up in a dimly lit zone. Confused..... subtle pain aching in your head. Where am *\n"
         << "* I?..... you ask yourself? As you slowly wake and return to your feet. You notice multiple      *\n"
         << "* doors in all directions. This looks like a hangar? Even a maze infact. So many doors?!?!?!     *\n"
         << "**************************************************************************************************\n";
}
// Specification A1 - Add Feature (Add Combat)
void playerCOMB(Player& player, Monsters& monster) { // Kept getting Arithmetic exception here; eventually due to monster damage determining 0 (zero)
    filelogMesg("Player Combat has been displayed and calculated successfully.");
    //cout << "Player Damage: " << player.damage << endl;         //Used to Debug
    //cout << "Monster Damage: " << monster.damage << endl;     //Used to Debug
    int player_damage = rand() % (player.damage / 2) + (player.damage / 2);     //Rand for generation of integer
    int monster_damage = rand() % (monster.damage / 2) + (monster.damage / 2);  // "/" for halving player and monster damage
                                                                                // makes sure the damage value lands between 
                                                                                // both full and half players damage. Same for Monster damage.
    player.health -= monster_damage;
    monster.health -= player_damage;

    cout << "You inflicted [" << player_damage << "] damage to: " << monster.name << "." << endl;
    cout << monster.name << " has dealt [" << monster_damage << "] damage to you." << endl;
    cout << "-----------------------+\n";
    cout << "Current health: [ " << player.health <<" ]" << endl;
    cout << "Monster health: [ " << monster.health <<" ]" << endl;
    cout << "-----------------------+\n";

    if (player.health <= 0) {
        cout << "- DEFEAT: Your run has come to and end. " << monster.name << ", Has prevailed and RNG did not have you." << endl;
        exit(0);
    } else if (monster.health <= 0) {
        cout << "- VICTORY! You defeated " << monster.name << "!\n"<< endl;
        return;

    }
}

void gameLOOP() {
    filelogMesg( "Main Game Loop has been displayed successfully.");
    Zone zones[6]; // 5 zones in the dungeon
    Player player = {100, 20}; // Player attributes: health and damage

    // Initialize all 6 zones with their respective details using array
    // True if occupied, false if not.
    // Directional commands and print statements
    // Specification B1 - Abbreviated Room Description
    // Speciﬁcation B2 - Detailed Look
    // Specification A2 - Add Feature ("Add more rooms")
    // Specification A3 - Add Feature ("Add more Monsters")
    zones[0] = {"ENTRANCE [Hangar]", "You are in a dimly lit aircraft hangar.\n", true, 0, {'N', 'S', 'E', 'W'}, {"SPACE MARINE", "A menacing combatant of the Cabal.\n", 50, 10}};
    zones[1] = {"[MAIN SHIP HALLWAY]", "This place feels rather creepy and quiet.... too quiet.....\n", false, 1, {'N', 'S', 'E', 'W'}, {"", "", 0, 0}};
    zones[2] = {"[INCUBATION CHAMBER]", "You see clones and oddly shaped pods everywhere.\n", true, 2, {'N', 'S', 'E', 'W'}, {"XenoMorph", "An alien Pokemon\n", 70, 15}};
    zones[3] = {"[SHIP TREASURY]", "You see a shining object across the zone. What could it be?.\n", true, 3, {'N', 'S', 'E', 'W'}, {"Corrupted Human", "he bleeds red diamonds.\n", 20, 10}};
    zones[4] = {"[SECRET ZONE]", "Cthulhu.....my memories......you suddenly die?", true, 4, {'N', 'S', 'E', 'W'}, {"Cthulhu", "no words speak truth. Your death is now. GG\n", 1, 999}};
    zones[5] = {"[A WAY OUT!] EXIT!", "GOOD JOB! That was a close one! Last door to get out is forward!\n", false, 5, {'N', 'S', 'E', 'W'}, {"", "", 0, 0}};

    // Live zone tracking index
    int zones_live = 0;
    bool located_exit = false;

    while (!located_exit) {     // while looping display zone information
        cout << zones[zones_live].name_zone << endl;
        if (zones[zones_live].details_zone != "" && zones[zones_live].id_zone != 4) {
            cout << zones[zones_live].details_zone << endl;
        }

        
        if (zones[zones_live].occ_monster) {    // To check for occupied monster if so initiate combat
            Monsters& current_monster = zones[zones_live].monster;
            cout << "A " << current_monster.name << " has appeared from behind rubble or whatever its called! \nDETAILS: " << current_monster.details << endl;
            playerCOMB(player, current_monster);        // Initiate combat
        }

        
        cout << "Potential Escapes: ";      // Simply prompt user for input
        for (int i = 0; i < 4; ++i) {
            if (zones[zones_live].escapes[i] != ' ') {
                cout << zones[zones_live].escapes[i] << " ";
            }
        }
        cout << endl;

        char choice;
        cout << "Pick a direction: \n";
        cin >> choice;

        // Input Validation incase user enters invalid direction
        // Specification B1 - Abbreviated Room Description
        // Speciﬁcation B2 - Detailed Look
        // Specification B3 - Input Validation
        while (choice != 'N' && choice != 'S' && choice != 'E' && choice != 'W' && choice != 'L') { 
            cout << "Invalid command. Please enter N, S, E, W, or L: ";
            cin >> choice;
        }

                    // Move to next zone or perform action based on input
        switch (choice) {
            case 'N':
                if (zones_live > 0 && zones[zones_live].escapes[0] == 'N') {
                    zones_live--;
                } else {
                    cout << "+========================================================================+" << endl;
                    cout << "|<DEAD END> There is no exit if you continue in that direction <DEAD END>|" << endl;
                    cout << "+========================================================================+" << endl;
                }
                break;
            case 'S':
                if (zones_live < 5 && zones[zones_live].escapes[1] == 'S') {
                    zones_live++;
                } else {
                    cout << "+========================================================================+" << endl;
                    cout << "|<DEAD END> There is no exit if you continue in that direction <DEAD END>|" << endl;
                    cout << "+========================================================================+" << endl;
                }
                break;
            case 'E':
                if (zones_live < 4 && zones[zones_live].escapes[2] == 'E') {
                    zones_live += 2;
                } else {
                    cout << "+========================================================================+" << endl;
                    cout << "|<DEAD END> There is no exit if you continue in that direction <DEAD END>|" << endl;
                    cout << "+========================================================================+" << endl;
                }
                break;
            case 'W':
                if (zones_live > 1 && zones[zones_live].escapes[3] == 'W') {
                    zones_live -= 2;
                } else {
                    cout << "+========================================================================+" << endl;
                    cout << "|<DEAD END> There is no exit if you continue in that direction <DEAD END>|" << endl;
                    cout << "+========================================================================+" << endl;
                }
                break;
                // Specification B1 - Abbreviated Room Description
                // Speciﬁcation B2 - Detailed Look
            case 'L':
                cout << zones[zones_live].name_zone << endl;
                cout << zones[zones_live].details_zone << endl;
                break;
        }

        // Check if player found the exit and print if so. (This is secret exit)
        if (zones_live == 5) {
            cout << endl;
            cout << "+======================================================================================================+\n" 
             << "| You have managed to find a secret hatch through the vents that leads into the Command Center of      |\n" 
             << "| the ship. You have survived the demise of your ship and crew. You have made it to The Command Center |\n" 
             << "| at the center of the ship. You have full control of this vessel. Congratulations my friend!          |\n" 
             << "| Lets get out of here!!! [You found the secret ending]                                                |\n" 
             << "+======================================================================================================+" << endl;
             filelogMesg("Secret Exit prompt been displayed and calculated successfully.");
            located_exit = true;
        }
    }
}


/*#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//Map for you professor after you play!

// - .... . / -- .- .--. / .. ... / .-.. / ... .... .- .--. .





//There are 3 possible endings. (EXIT, Secret Hatch, Cthulhu instant game over)
// "Zone" instead of "room" sounds better for "RPG" asepects/theme
// This took an outline and 2 1/2 itterations. Completely retyped after getting lost and melting my code. >.>
// Pretty much works. Some bugs I couldn't fix without breaking something else.
// Outline before coding is in canvas as well.

//monsters //Space Marine
           //Xenomorph
           //Corrupted Human
           //Boss - Cthulhu
                    
struct Monsters {       // Struct as taught in lecture. For monster container.
    string name;
    string details;
    int health;
    int damage;
};


struct Player {  //Struct system for player health in combat container.
    int health;
    int damage;
};

//Function Prototypes
// Speciﬁcation C2 - Three Functions
void filelogMesg(const string& message);
void ProgGreet();   // Greeting before start of game
void gameLOOP();    // Main gameloop
void mainMENU();    // Full main menu with 3 options
void underttlINTRO();   // Game intro for uhhh "Role playing reasons? Why not"
void playerCOMB(Player& player, Monsters& monster); // Combat function for player vs monster.


// Speciﬁcation C1 - Main Data Structure 
struct Zone {           // Visible Main Data Structure
    string name_zone;
    string details_zone;
    bool occ_monster;   // Monster occupies room
    int id_zone;        // Zone ID details
    char escapes[4]; // NSEW navigation directions
    Monsters monster; // Monster to spawn in a zone
};

// Speciﬁcation C3 - Function Activity to Disk
void filelogMesg(const string& strtext){    //live outputs to file in log.text
    ofstream logfile("log.txt", ios::app); // Opens append mode to log to file.
    if (logfile.is_open()) {
    time_t live = time(0); // Pulls current time of execution.
    tm* cfts = localtime(&live); // Current time as a string. cfts = Call function, time, string   
    logfile << "[" << 1900 + cfts->tm_year << "-" << 1 + cfts->tm_mon << "-" << cfts->tm_mday << " "; // Year, month and day of month
    logfile << cfts->tm_hour << ":" << cfts->tm_min << ":" << cfts->tm_sec << "] " << strtext << endl; // Minutes, seconds, string
    }

}


int main() {
    filelogMesg("Game starting...............");
    // Speciﬁcation C2 - Three Functions
    ProgGreet();
    mainMENU();
    return 0;
}
//Function Descriptions 
void ProgGreet() {
    cout << "                     Welcome to Lightz - Text-based RPG Adventure!" << endl;
    cout << "                                     Let's begin!" << endl;
    filelogMesg("Greeting has been displayed successfully.");
}


void mainMENU() {
    filelogMesg("Main menu has been displayed successfully.");
    int choice;
    bool valid_choice = false;

    while (!valid_choice) {
        cout << "                     +-------------------------------------------+\n";
        cout << "                     | +=======================================+ |\n";
        cout << "                     | |  -  Now Entering: Project Solaris  -  | |\n";
        cout << "                     | +=======================================+ |\n";
        cout << "                     |                                           |\n";
        cout << "                     |                 < MAIN MENU >             |\n";
        cout << "                     |                                           |\n";
        cout << "                     |        ~{     1. > Start Game     }~      |\n"; // Will start game & INTRO
        cout << "                     |                                           |\n";
        cout << "                     |        ~{     2. > How to Play    }~      |\n";
        cout << "                     |                                           |\n";
        cout << "                     |        ~{     3. > Quit Game      }~      |\n";
        cout << "                     |                                           |\n";
        cout << "                     +-------------------------------------------+\n";
        cout << "                      > Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                // Speciﬁcation C2 - Three Functions
                underttlINTRO(); // Display introduction wihtout input
                gameLOOP(); // Start the main game loop to continue forward
                valid_choice = true;
                break;
            case 2:                  // Display how to play instructions upon typing 2.             
                cout << "How to Play: \n"
                     << "\n"
                     << "1. You are to explore the ship using N, S, E, W (L)commands.\n"
                     // Specification B1 - Abbreviated Room Description
                     // Speciﬁcation B2 - Detailed Look
                     << "2. Type 'L' to look around the zone and provide current adventure/zone/monster details.\n"
                     << "3. Combat is automated and damage is random. Infection after monster death. Damage happens simultaneously.\n"
                     << "4. Caps lock sensitive (instructions say in all caps N, S, E, W)\n"
                     << "5. Good luck in there!! For Democracy!!\n"
                     << "\n"
                     << "OBJECTIVE: Find the Command Center and escape with the ship. [Or your life]\n"
                     << "\n";
                cout << "Please press 1 to return to main menu.\n";
                cin >> choice;
                
                while (choice != 1) {
                    // Specification B3 - Input Validation
                    cout << "Invalid choice. Please press 1 to return to main menu.\n";
                    cin >> choice;
                }
                break;
            case 3: // Exits the game upon 3.
                cout << "Exiting the game. Goodbye!\n";
                exit(0);
                break;
            default:
            // Specification B3 - Input Validation
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                break;
        }
    }
}

void underttlINTRO() {
    filelogMesg("Introduction has been displayed successfully.");
    cout << "**************************************************************************************************\n"
         << "* The story begins with a maiden voyage of The Aurora Voyager. Named after the old Stellar God.  *\n"
         << "* The docking onto a derelict ship is currently taking place. You are facing the airlock panel.  *\n"
         << "*                                                                                                *\n"
         << "*      > The door to the derelict Ship has been opened.                                          *\n"
         << "**************************************************************************************************\n"
         << "* As the door to the airlock slowly glides open. You walk forward. Steam starts to fill the zone *\n"
         << "* as the door shuts behind you, much faster than before. You feel chills up your spine... as     *\n"
         << "* if... something is wrong. It starts to appear very quiet as your eyes start to close......     *\n"
         << "*                                                                                                *\n"
         << "* You have woken up in a dimly lit zone. Confused..... subtle pain aching in your head. Where am *\n"
         << "* I?..... you ask yourself? As you slowly wake and return to your feet. You notice multiple      *\n"
         << "* doors in all directions. This looks like a hangar? Even a maze infact. So many doors?!?!?!     *\n"
         << "**************************************************************************************************\n";
}
// Specification A1 - Add Feature (Add Combat)
void playerCOMB(Player& player, Monsters& monster) { // Kept getting Arithmetic exception here; eventually due to monster damage determining 0 (zero)
    filelogMesg("Player Combat has been displayed and calculated successfully.");
    //cout << "Player Damage: " << player.damage << endl;         //Used to Debug
    //cout << "Monster Damage: " << monster.damage << endl;     //Used to Debug
    int player_damage = rand() % (player.damage / 2) + (player.damage / 2);     //Rand for generation of integer
    int monster_damage = rand() % (monster.damage / 2) + (monster.damage / 2);  // "/" for halving player and monster damage
                                                                                // makes sure the damage value lands between 
                                                                                // both full and half players damage. Same for Monster damage.
    player.health -= monster_damage;
    monster.health -= player_damage;

    cout << "You inflicted [" << player_damage << "] damage to: " << monster.name << "." << endl;
    cout << monster.name << " has dealt [" << monster_damage << "] damage to you." << endl;
    cout << "-----------------------+\n";
    cout << "Current health: [ " << player.health <<" ]" << endl;
    cout << "Monster health: [ " << monster.health <<" ]" << endl;
    cout << "-----------------------+\n";

    if (player.health <= 0) {
        cout << "- DEFEAT: Your run has come to and end. " << monster.name << ", Has prevailed and RNG did not have you." << endl;
        exit(0);
    } else if (monster.health <= 0) {
        cout << "- VICTORY! You defeated " << monster.name << "!\n"<< endl;
        return;

    }
}

void gameLOOP() {
    filelogMesg( "Main Game Loop has been displayed successfully.");
    Zone zones[6]; // 5 zones in the dungeon
    Player player = {100, 20}; // Player attributes: health and damage

    // Initialize all 6 zones with their respective details using array
    // True if occupied, false if not.
    // Directional commands and print statements
    // Specification B1 - Abbreviated Room Description
    // Speciﬁcation B2 - Detailed Look
    // Specification A2 - Add Feature ("Add more rooms")
    // Specification A3 - Add Feature ("Add more Monsters")
    zones[0] = {"ENTRANCE [Hangar]", "You are in a dimly lit aircraft hangar.\n", true, 0, {'N', 'S', 'E', 'W'}, {"SPACE MARINE", "A menacing combatant of the Cabal.\n", 50, 10}};
    zones[1] = {"[MAIN SHIP HALLWAY]", "This place feels rather creepy and quiet.... too quiet.....\n", false, 1, {'N', 'S', 'E', 'W'}, {"", "", 0, 0}};
    zones[2] = {"[INCUBATION CHAMBER]", "You see clones and oddly shaped pods everywhere.\n", true, 2, {'N', 'S', 'E', 'W'}, {"XenoMorph", "An alien Pokemon\n", 70, 15}};
    zones[3] = {"[SHIP TREASURY]", "You see a shining object across the zone. What could it be?.\n", true, 3, {'N', 'S', 'E', 'W'}, {"Corrupted Human", "he bleeds red diamonds.\n", 20, 10}};
    zones[4] = {"[SECRET ZONE]", "Cthulhu.....my memories......you suddenly die?", true, 4, {'N', 'S', 'E', 'W'}, {"Cthulhu", "no words speak truth. Your death is now. GG\n", 1, 999}};
    zones[5] = {"[A WAY OUT!] EXIT!", "GOOD JOB! That was a close one! Last door to get out is forward!\n", false, 5, {'N', 'S', 'E', 'W'}, {"", "", 0, 0}};

    // Live zone tracking index
    int zones_live = 0;
    bool located_exit = false;

    while (!located_exit) {     // while looping display zone information
        cout << zones[zones_live].name_zone << endl;
        if (zones[zones_live].details_zone != "" && zones[zones_live].id_zone != 4) {
            cout << zones[zones_live].details_zone << endl;
        }

        
        if (zones[zones_live].occ_monster) {    // To check for occupied monster if so initiate combat
            Monsters& current_monster = zones[zones_live].monster;
            cout << "A " << current_monster.name << " has appeared from behind rubble or whatever its called! \nDETAILS: " << current_monster.details << endl;
            playerCOMB(player, current_monster);        // Initiate combat
        }

        
        cout << "Potential Escapes: ";      // Simply prompt user for input
        for (int i = 0; i < 4; ++i) {
            if (zones[zones_live].escapes[i] != ' ') {
                cout << zones[zones_live].escapes[i] << " ";
            }
        }
        cout << endl;

        char choice;
        cout << "Pick a direction: \n";
        cin >> choice;

        // Input Validation incase user enters invalid direction
        // Specification B1 - Abbreviated Room Description
        // Speciﬁcation B2 - Detailed Look
        // Specification B3 - Input Validation
        while (choice != 'N' && choice != 'S' && choice != 'E' && choice != 'W' && choice != 'L') { 
            cout << "Invalid command. Please enter N, S, E, W, or L: ";
            cin >> choice;
        }

                    // Move to next zone or perform action based on input
        switch (choice) {
            case 'N':
                if (zones_live > 0 && zones[zones_live].escapes[0] == 'N') {
                    zones_live--;
                } else {
                    cout << "+===========================================================+" << endl;
                    cout << "|X - There is no exit if you continue in that direction. - X|" << endl;
                    cout << "+===========================================================+" << endl;
                }
                break;
            case 'S':
                if (zones_live < 5 && zones[zones_live].escapes[1] == 'S') {
                    zones_live++;
                } else {
                    cout << "+===========================================================+" << endl;
                    cout << "|X - There is no exit if you continue in that direction. - X|" << endl;
                    cout << "+===========================================================+" << endl;
                }
                break;
            case 'E':
                if (zones_live < 4 && zones[zones_live].escapes[2] == 'E') {
                    zones_live += 2;
                } else {
                    cout << "+===========================================================+" << endl;
                    cout << "|X - There is no exit if you continue in that direction. - X|" << endl;
                    cout << "+===========================================================+" << endl;
                }
                break;
            case 'W':
                if (zones_live > 1 && zones[zones_live].escapes[3] == 'W') {
                    zones_live -= 2;
                } else {
                    cout << "+===========================================================+" << endl;
                    cout << "|X - There is no exit if you continue in that direction. - X|" << endl;
                    cout << "+===========================================================+" << endl;
                }
                break;
                // Specification B1 - Abbreviated Room Description
                // Speciﬁcation B2 - Detailed Look
            case 'L':
                cout << zones[zones_live].name_zone << endl;
                cout << zones[zones_live].details_zone << endl;
                break;
        }

        // Check if player found the exit and print if so. (This is secret exit)
        if (zones_live == 5) {
            cout << endl;
            cout << "+======================================================================================================+\n" 
             << "| You have managed to find a secret hatch through the vents that leads into the Command Center of      |\n" 
             << "| the ship. You have survived the demise of your ship and crew. You have made it to The Command Center |\n" 
             << "| at the center of the ship. You have full control of this vessel. Congratulations my friend!          |\n" 
             << "| Lets get out of here!!! [You found the secret ending]                                                |\n" 
             << "+======================================================================================================+" << endl;
             filelogMesg("Secret Exit prompt been displayed and calculated successfully.");
            located_exit = true;
        }
    }
}*/