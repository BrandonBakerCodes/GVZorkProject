/*
* ---------------
* GVZork Project
* CIS 343-01
* October 5, 2023 
*
* Bailey Compton
* Brandon Baker
* Sarah Wight
* ---------------
*
* This class holds all the logic for a game instance.
*/

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
#include <functional>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "item.h"
#include "npc.h"
#include "location.h"
#include "game.h"

Game::Game(){

    // Create locations, items, and npcs
    createWorld();

    // Set first location to random location
    currentLocation = randomLocation();
    playerCarryWeight = 0;
    elfCaloriesLeft = 500;
    gameInprogress = true;

    // Start game loop
    play();
}

void Game::createWorld(){
    /*
    * ITEM SETUP
    */
    // Player can only carry 30 pounds, Elf must eat 500 calories
    Item macbook("Macbook", "Someone has vulnerable code on their macbook...", 0, 2.0f); 
    Item proteinBar("Protein_bar", "A protein bar left on a bench", 200, .5f);  
    Item bltSub("BLT_Sub_Sandwich", "A leftover sub on the counter of Subway", 200, 1.0f); 
    Item gum("Used_gum", "Someone's spit their gum out here", 0, 0.1f); 
    Item periodicTable("Periodic_table", "Sciency object used for crafting recipes", 0, 0.1f); 
    Item golfClubSet("Golf_Club_Set", "Some clubs people use on the course", 0, 15.0f); 
    Item mattress("Someone's_matress", "This is where a college student sleeps", 0, 25.0f); 
    Item toiletPaperRoll("Toilet_Paper", "Don't forget to wipe!", 0, 1.0f); 
    Item bigBagOfPopcorn("Popcorn", "Someone left this big bag of popcorn on the bleachers", 100, 2.0f); 
    Item basketBall("Basketball", "A flabby basketball used for free-throws only", 0, 3.0f); 
    Item chair("Chair", "This a comfy ahh seat", 0, 10.0f); 
    Item bagOfChips("Bag_of_Chips", "Some Doritos next to someone's bag", 100, 0.1f);   
    Item twoSlicesOfPizzahs("Two_Slices_of_Pizzahs", "Free pizza from a giveaway", 400, 2.0f); 
    Item backpack("Backpack", "This person got a lot of books", 0, 20.0f); 
    Item rubberDucky("Rubber_Ducky", "Someone's rubber duck on the loose.", 0, 0.1f); 
    Item smore("Smore", "A big juicy glob of goo", 500, 0.1f);
    
    /*
    * NPC SETUP
    */
    Npc brandon("Brandon_Baker", "Sweaty CS student, but also has a life");
    brandon.addMessage("Let's play pickleball!!");
    brandon.addMessage("It's pump time!");
    brandon.addMessage("Want to grab a bite?");
    brandon.addMessage("Too easy man.");

    Npc bailey("Bailey_Compton", "Wannabe penetration tester and PGA pro");
    bailey.addMessage("*Sarcastic tone* I can't believe I shot a 24 on 18 holes at Meadows Golf Course today!");
    bailey.addMessage("I am so ready to be done with college... 5 years is plenty!");
    bailey.addMessage("Did you know that EVERYTHING is 1s and 0s??? I swear!!");
    bailey.addMessage("Just tryna graduate at this point... ya know??");

    Npc sarah("Sarah_Wight", "Super senior ready to graduate");
    sarah.addMessage("Mackinac Hall is the most confusing building on campus!");
    sarah.addMessage("How to get to classroom B1118?");
    sarah.addMessage("Let's go to Einstein Bagels!");
    sarah.addMessage("I've been doing homework for 12 hours now. I basically live here.");

    Npc ira("Professor_Woodring", "All knowing computer wizard");
    ira.addMessage("Java is pass by COPY!!!!!!!");
    ira.addMessage("Computer scientist.. or wizard??");
    ira.addMessage("Grace Hopper is the GOAT.");
    ira.addMessage("*Sigh* I guess you can have an extension on the project.....");

    Npc vendMachine("Vendy", "Vendy the talking vending machine");
    vendMachine.addMessage("BEEP BOOP.. *Chips*");
    vendMachine.addMessage("Enter 123 for a nice refresher!");
    vendMachine.addMessage("Want some candy?");
    vendMachine.addMessage("Vendy getting eepy.. Power down..");

    Npc louie("Louie_the_Laker", "GVSU's biggest fan");
    louie.addMessage("ANCHOR UP!");
    louie.addMessage("Tune into the Lakers football game this Saturday!");
    louie.addMessage("Chick-fil-a is now available at Lubbers Stadium");
    louie.addMessage("Go Lakers!");

    /*
    * LOCATION SETUP
    */
    Location mackinacHall("Mackinac_Hall", "Lot of CS Classes going on in here.");
    Location padnosHall("Padnos_Hall", "Future Bill Nye's are at work here.");
    Location recCenter("GVSU_Rec_Center", " A place to play Wii sports in real life!");
    Location weightRoom("Rec_Center_Weight_Room", "Time to Get Big!");
    Location kirkhofCenter("Kirkhof_Center", "A good place to take a study break");
    Location foodCourt("Kirkof_Food_Court", "Looks like we grubbin today.");
    Location blueBridge("Blue_Bridge", "A nice place to look over the ravine");
    Location meadowsGc("Meadows_Golf_Course", "You see drunk people driving golf carts... What could go wrong!");
    Location lubbersStadium("GVSU_Lubbers_Stadium", "Try to catch a football, you might be able to keep it...");
    Location southApartments("South_Campus_Apartments", "*TOOT TOOT TOOT* You can hear the marching band practicing.");
    Location smellyBathroom("Dirty_Bathroom", "Smells like rotten eggs (maybe its sulfur?).");
    Location zumbergePond("Zumberge_Pond", "A nice peaceful place to watch the fountain.");
    Location woods("Woods", "You see an elf awaiting your arrival!");

    mackinacHall.addItem(backpack);
    mackinacHall.addItem(macbook);
    mackinacHall.addNpc(sarah);

    padnosHall.addItem(periodicTable);

    recCenter.addItem(basketBall);
    recCenter.addNpc(brandon);

    weightRoom.addItem(proteinBar);

    kirkhofCenter.addItem(chair);
    kirkhofCenter.addItem(bagOfChips);
    kirkhofCenter.addNpc(vendMachine);

    foodCourt.addItem(bltSub);

    blueBridge.addItem(gum);

    meadowsGc.addItem(golfClubSet);
    meadowsGc.addNpc(bailey);

    lubbersStadium.addItem(bigBagOfPopcorn);
    lubbersStadium.addItem(twoSlicesOfPizzahs);
    lubbersStadium.addNpc(louie);

    southApartments.addItem(mattress);

    smellyBathroom.addItem(toiletPaperRoll);
    smellyBathroom.addNpc(ira);

    zumbergePond.addItem(rubberDucky);

    woods.addItem(smore);

    // Add Locations to World
    worldLocations.push_back(mackinacHall); //[0]
    worldLocations.push_back(padnosHall); //[1]
    worldLocations.push_back(recCenter); //[2]
    worldLocations.push_back(weightRoom); //[3]
    worldLocations.push_back(kirkhofCenter); //[4]
    worldLocations.push_back(foodCourt); //[5]
    worldLocations.push_back(blueBridge); //[6]
    worldLocations.push_back(meadowsGc); //[7]
    worldLocations.push_back(lubbersStadium); //[8]
    worldLocations.push_back(smellyBathroom); //[9]
    worldLocations.push_back(southApartments); //[10]
    worldLocations.push_back(zumbergePond); //[11]
    worldLocations.push_back(woods); //[12]

    // Add neighbors 
    // Mackinac 
    worldLocations[0].addLocation("West", worldLocations[2]);
    worldLocations[0].addLocation("South", worldLocations[1]);

    // Padnos 
    worldLocations[1].addLocation("North", worldLocations[0]);
    worldLocations[1].addLocation("SouthEast", worldLocations[6]);
    worldLocations[1].addLocation("South", worldLocations[4]);

    // Rec Center
    worldLocations[2].addLocation("NorthWest", worldLocations[8]);
    worldLocations[2].addLocation("East", worldLocations[0]);
    worldLocations[2].addLocation("Inside", worldLocations[3]);
    worldLocations[2].addLocation("SouthEast", worldLocations[1]);
    worldLocations[2].addLocation("West", worldLocations[7]);

    // Weight Room
    worldLocations[3].addLocation("Outside", worldLocations[2]);

    // Kirkhof 
    worldLocations[4].addLocation("North", worldLocations[1]);
    worldLocations[4].addLocation("Inside", worldLocations[5]);
    worldLocations[4].addLocation("West", worldLocations[11]);
    worldLocations[4].addLocation("South East", worldLocations[10]);

    // Food Court 
    worldLocations[5].addLocation("Outside", worldLocations[4]);
    worldLocations[5].addLocation("Inside", worldLocations[9]);

    // Blue Bridge
    worldLocations[6].addLocation("NorthWest", worldLocations[1]);
    worldLocations[6].addLocation("SouthWest", worldLocations[11]);
    worldLocations[6].addLocation("West", worldLocations[12]);

    // Meadows Golf Course 
    worldLocations[7].addLocation("North", worldLocations[8]);
    worldLocations[7].addLocation("East", worldLocations[2]);

    // Lubbers Stadium 
    worldLocations[8].addLocation("South", worldLocations[7]);
    worldLocations[8].addLocation("SouthEast", worldLocations[2]);

    // South Apartment 
    worldLocations[9].addLocation("NorthWest", worldLocations[4]);
    worldLocations[9].addLocation("North", worldLocations[11]);

    // Smelly Bathroom 
    worldLocations[10].addLocation("Inside", worldLocations[5]);
    
    // Zumberge Pond 
    worldLocations[11].addLocation("North East", worldLocations[6]);
    worldLocations[11].addLocation("South", worldLocations[10]);
    worldLocations[11].addLocation("West", worldLocations[4]);
    
    // Woods
    worldLocations[12].addLocation("East", worldLocations[6]);
}

std::map<std::string, void (Game::*)(std::vector<std::string>)> Game::setupCommands(){
    std::map<std::string, void (Game::*)(std::vector<std::string>)> commandMap;
    
    // Add the function to the map with a string key.
    commandMap["take"] = &Game::take;
    commandMap["Take"] = &Game::take;
    commandMap["look"] = &Game::look;
    commandMap["Look"] = &Game::look;
    commandMap["show_items"] = &Game::show_items;
    commandMap["items"] = &Game::show_items;
    commandMap["Items"] = &Game::show_items;
    commandMap["inventory"] = &Game::show_items;
    commandMap["Inventory"] = &Game::show_items;
    commandMap["meet"] = &Game::meet;
    commandMap["Meet"] = &Game::meet;
    commandMap["give"] = &Game::give;
    commandMap["help"] = &Game::show_help;
    commandMap["Help"] = &Game::show_help;
    commandMap["show_help"] = &Game::show_help;
    commandMap["talk"] = &Game::talk;
    commandMap["Talk"] = &Game::talk;
    commandMap["go"] = &Game::go;
    commandMap["Go"] = &Game::go;
    commandMap["move"] = &Game::go;
    commandMap["Move"] = &Game::go;
    commandMap["quit"] = &Game::quit;
    commandMap["exit"] = &Game::quit;
    commandMap["leave"] = &Game::quit;
    commandMap["Quit"] = &Game::quit;
    commandMap["Exit"] = &Game::quit;
    commandMap["Leave"] = &Game::quit;
    commandMap["eat"] = &Game::eat;
    commandMap["Eat"] = &Game::eat;
    commandMap["Call"] = &Game::callNpc;
    commandMap["call"] = &Game::callNpc;
    commandMap["Request"] = &Game::callNpc;
    commandMap["request"] = &Game::callNpc;

    return commandMap;
}

Location Game::randomLocation(){

    // Random Generation Taken from *ChatGPT*
    std::random_device rand;
    std::mt19937 gen(rand());

    // Random Num Range
    int low = 0;
    int high = worldLocations.size() - 1;

    // Create a uniform distribution for the range
    std::uniform_int_distribution<int> distribution(low, high);

    // Generate a random number within the range
    int random_number = distribution(gen);

    worldLocations[random_number].setVisited();

    // TO WIN GAME, uncomment following line.
    // return worldLocations[12];
    return worldLocations[random_number];
}

int Game::case_insensitive_match(std::string s1, std::string s2) {
    // Code from *Stack Overflow*
    //convert s1 and s2 into lower case strings
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.compare(s2) == 0)
        return 1; //The strings are same
    return 0; //not matched
}

void Game::play(){
    // Setup all of the commands
    commands = Game::setupCommands();

    // Start up message
    std::cout << "Welcome to GV Zork. Your goal is to travel around GV campus and collect edible items \n"
                    "and take them to the elf that lives on campus. The elf needs 500 calories to save GV.\n"
                    "Have fun and good luck!\n"
                    "---------------------------------\n" << "\n"
                    "\nYou are currently inside of\n" << std::endl;

                    std::cout << currentLocation;

    // Game loop
    while (gameInprogress) {

        // Read in user input and tokenize string *Code from ChatGPT*
        std::cout << "What is your command?" << std::endl;

        // Read in line of user input
        std::string fullInput;
        std::getline(std::cin, fullInput);
        std::istringstream iss(fullInput);
        
        std::string commandInput;
        std::vector<std::string> target;

        // Read in first word, then rest of words
        if (iss >> commandInput) {
            std::string argument;
            while (iss >> argument) {
                target.push_back(argument);
            }
        }
        // END of *ChatGPT* Help, used to understand istringstream.

        // Check all keys in commands to make sure one matches command Input string.
        bool commandExists = false;
        for(auto it = commands.begin(); it != commands.end(); ++it){
            if(it->first == commandInput){
                commandExists = true;
            }
        }
        // Execute command if it exists
        if(commandExists){
            (*this.*commands[commandInput])(target);
            if (elfCaloriesLeft <= 0) {
                std::cout << "CONGRATULATIONS! \nThe elf is now full and can save campus from the Ferris State Bulldogs!\nYOU WIN!!\n";
                std::cout << "░░░░░░░░░░░░░░░░░░░░░░█████████\n"
                            "░░███████░░░░░░░░░░███▒▒▒▒▒▒▒▒███\n"
                            "░░█▒▒▒▒▒▒█░░░░░░░███▒▒▒▒▒▒▒▒▒▒▒▒▒███\n "
                            "░░░█▒▒▒▒▒▒█░░░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n "
                            "░░░░█▒▒▒▒▒█░░░██▒▒▒▒▒██▒▒▒▒▒▒██▒▒▒▒▒███\n "
                            "░░░░░█▒▒▒█░░░█▒▒▒▒▒▒████▒▒▒▒████▒▒▒▒▒▒██\n "
                            "░░░█████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n "
                            "░░░█▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒██\n "
                            "░██▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒██▒▒▒▒▒▒▒▒▒▒██▒▒▒▒██\n "
                            "██▒▒▒███████████▒▒▒▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒██\n "
                            "█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒████████▒▒▒▒▒▒▒██\n "
                            "██▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n "
                            "░█▒▒▒███████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n "
                            "██▒▒▒▒▒▒▒▒▒▒████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█ \n"
                            "░░████████████░░░█████████████████" << std::endl;
                gameInprogress = false;
            }
        } else {
            std::cout << commandInput << " command does not exist.";
        }

        std::cout << "\n" << std::endl;
    }
}

void Game::getCurrentTime(){
    // Code from *TutorialsPoint* Website
    time_t t;
    struct tm * tt;
    std::time (&t);
    tt = std::localtime(&t);

    int hour = tt->tm_hour;
    int minute = tt->tm_min;

    // Convert to 12 hour format, help from *ChatGPT*
    std::string am_pm = (hour < 12) ? "AM" : "PM";
    if (hour > 12) {
        hour -= 12;
    } else if (hour == 0) {
        hour = 12;
    }

    std::cout << "Current Time: " << hour << ":" << std::setfill('0') <<
     std::setw(2) << minute << am_pm << std::endl;
}

void Game::show_help(std::vector<std::string> target){

    // Help message and Current Time
    std::cout << "You have requested help!" << std::endl;
    getCurrentTime();

    // Display all game commands
    std::cout << "\nCommand Menu\n-----------------------------------------------------------" << std::endl;
    std::cout << "Help - Prints help message, list of all commands, and current time." << std::endl;
    std::cout << "Talk - Talk to the requested NPC (if they are in the room)." << std::endl;
    std::cout << "Meet - Get the requested NPC's description (if they are in the room)." << std::endl;
    std::cout << "Take - Removes requested item from the room and adds it to player inventory." << std::endl;
    std::cout << "Give - Remove requested item from player inventory and add to location. If elf is present, attempt to feed it." << std::endl;
    std::cout << "Go/Move - Go to requested location if it is neighbors with current location." << std::endl;
    std::cout << "Item/Inventory - Display's all items in player inventory." << std::endl;
    std::cout << "Look - Show current location and any items, npcs, and neighbors within it." << std::endl;
    std::cout << "Quit/Exit - Exits the game." << std::endl;
    std::cout << "Eat - Attempt to eat the requested item." << std::endl;
    std::cout << "Call - Calls the requested NPC to your current location." << std::endl;
}

void Game::talk(std::vector<std::string> target){
    std::vector<Npc>& npcList = currentLocation.getNPCs();
    std::vector<std::string>::iterator its;
    bool found = false;

    // Check target word matches npc name
    for(auto it = npcList.begin(); it != npcList.end(); ++it){
        for(its = target.begin(); its != target.end(); ++its){
            if(case_insensitive_match(it->getName(), *its)){
                std::cout << it->getCurrentMessage();
                found = true;
            }
        }
    }
    if(!found){
        std::cout << "Npc you are looking for is not in this room.";
    }
}

void Game::meet(std::vector<std::string> target){
    std::vector<Npc> npcList = currentLocation.getNPCs();
    std::vector<std::string>::iterator its;
    bool found = false;

    // Check target word matches npc name
    for(auto it = npcList.begin(); it != npcList.end(); ++it){
        for(its = target.begin(); its != target.end(); ++its){
            if(case_insensitive_match(it->getName(), *its)){
                std::cout << it->getDescription();
                found = true;
            }
        }
    }

    if(!found){
        std::cout << "Npc you are looking for is not in this room.";
    }
}

void Game::take(std::vector<std::string> target){
    if(target.empty()){
        std::cout << "No object requested";
        return;
    }

    std::vector<Item>& itemList = currentLocation.getItems();
    std::vector<std::string>::iterator its;
    std::string itemName;

    bool found = false;

    // Check item name is in target vector
    for(auto it = itemList.begin(); it != itemList.end(); ++it){
        for(its = target.begin(); its != target.end(); ++its){
            if(case_insensitive_match(it->getName(), *its)){
                found = true;
                playerInventory.push_back(*it);
                playerCarryWeight += it->getWeight();
                itemName = it->getName();
            }
        }
    }

    // Remove item from location, add to inventory.
    if(found){
        std::cout << "Added " << itemName << " to player inventory";
        currentLocation.removeItem(itemName);
    } else {
        std::cout << "Couldn't find requested object";
    }
}


void Game::give(std::vector<std::string> target){

    if(target.empty()){
        std::cout << "No object requested";
        return;
    }

    // Create flags for determining what to do
    std::vector<std::string>::iterator its;
    bool edible = false;
    bool found = false;
    std::string itemName;
    int calories;
    float weight;
    Item item("default", "default", 0, 1.0f);

    // Check if item is in player inventory
    for(auto it = playerInventory.begin(); it != playerInventory.end(); ++it){
        for(its = target.begin(); its != target.end(); ++its) {
            if(case_insensitive_match(it->getName(), *its)){
                found = true;
                item = *it;
                itemName = it->getName();
                weight = it->getWeight();
                
                // item is edible
                if (it->getCalories() != 0) {
                    calories = it->getCalories();
                    edible = true;
                } 
            }
        }
    }
    if(!found){
        std::cout << "Requested item is not in your inventory.";
    }
    // In woods and item is edible
    else if (edible && (currentLocation.getName() == "Woods")) {
        playerCarryWeight -= weight;
        elfCaloriesLeft -= calories;
        std::cout << "The Elf is pleased with your offering. \nThe elf needs " << elfCaloriesLeft << " more calories before saving campus\n" << std::endl;
        removeItem(itemName);
    }
    // In woods and item is inedible 
    else if (!edible && (currentLocation.getName() == "Woods")) {
        std::cout << "*The Elf spits out your item* BLEH! You tried to poison me!! Off you go!\n" << std::endl;
        playerCarryWeight -= weight;
        removeItem(itemName);
        currentLocation = randomLocation();
        std::cout << "You have been teleported to " << currentLocation.getName() << " for your wrong doings.."; 
    }
    // In a location outside of woods
    else {
        std::cout << "You dropped " << itemName << " from your inventory" << std::endl;
        playerCarryWeight -= weight;
        currentLocation.addItem(item);
        removeItem(itemName);
    }
}

void Game::removeItem(std::string itemName){
    int pos = 0;

    // Check item is in inventory
    for (int i = 0; i < playerInventory.size(); i++) {
        if(itemName == playerInventory[i].getName()){
            pos = i;
        }
     }

     // Remove item from inventory
     playerInventory.erase(playerInventory.begin() + pos);
}

void Game::go(std::vector<std::string> target){
    
    if(target.empty()){
        std::cout << "No location requested.";
    }

    // Player too heavy to move locations
    if(playerCarryWeight >= 30){
        std::cout << "Player too heavy to move locations.";
        return;
    }

    std::map<std::string, std::reference_wrapper<Location>> neighbors = currentLocation.getLocations();
    std::string directionToMove;
    Location newLocation;
    bool found = false;

    // Check direction is in neighbors map
    for(auto it = neighbors.begin(); it != neighbors.end(); ++it){
        std::string direction = it->first;
        for(auto its = target.begin(); its != target.end(); ++its){
            if(case_insensitive_match(direction, *its)){
                directionToMove = direction;
                it->second.get().setVisited();
                newLocation = it->second;
                found = true;
            }
        }
    }

    // Set new location
    if(found){
        currentLocation = newLocation;
        std::cout << currentLocation << std::endl;
    }
}

void Game::show_items(std::vector<std::string> target){
    
    // print all the items the player is carrying and the amount of weight, if any
    if (playerInventory.empty()) {
        std::cout << "Player has no items" << std::endl;
    } else {
        std::cout << "Player currently has the following items:" << std::endl;
        for(auto item : playerInventory) {
            std::cout << "\t -" << item << std::endl;
        }
        
    // Display player weight
    std::cout << "Player is currently carrying " << playerCarryWeight << " lbs" << std::endl;
    }
}

void Game::look(std::vector<std::string> target){
    
    // Print current location's stream
    std::cout << "Your current location is: ";
    std::cout << currentLocation << std::endl;
}

void Game::quit(std::vector<std::string> target){
    
    // Exit game
    std::cout << "Game has ended" << std::endl;
    exit(1);
}

void Game::eat(std::vector<std::string> target){

    if(target.empty()){
        std::cout << "Please request an item";
        return;
    }

    std::string itemName;
    int found = 0;

    // Check player inventory item matches target word
    for(auto it = playerInventory.begin(); it != playerInventory.end(); ++it){
        for(auto its = target.begin(); its != target.end(); ++its) {
            if(case_insensitive_match(it->getName(), *its)){
                // item found
                found = 1;
                itemName = it->getName();
                if (it->getCalories() > 0) {
                    
                    // item is edible
                    found = 2;
                }
            }
        }
    }

    // Not found
    if(found == 0){
        std::cout << "Requested item not found in inventory.";
    }
    // Not edible
    else if(found == 1){
        std::cout << itemName << " isn't edible";
    } 
    // Edible
    else {
        std::cout << "You just devoured " << itemName << ". YUM!!!";
        removeItem(itemName);
    }
}


void Game::callNpc(std::vector<std::string> target){

    if(target.empty()){
        std::cout << "Please request an NPC";
        return;
    }
    bool found = false;
    std::string npcName;
    Location loc;
    
    // Loop through all location's npc lists and check target matches an npc name
    for(auto it = worldLocations.begin(); it != worldLocations.end(); ++it){
        for (auto its = it->getNPCs().begin(); its != it->getNPCs().end(); ++its){
            for (auto it1 = target.begin(); it1 != target.end(); ++it1){
                if(case_insensitive_match(*it1, its->getName())){
                    currentLocation.addNpc(*its);
                    loc = *it;
                    npcName = *it1;
                    found = true;
                }   
            }
        }
    }

    // Transfer npc
    if(found){
        std::cout << npcName << " added to " << currentLocation.getName();
        loc.removeNpc(npcName);
    } else {
        std::cout << "Requested Npc not found";
    }
}

/**
 * Creates the game object that runs in the terminal.
*/
int main(){

    Game game;
    return 0;
}
