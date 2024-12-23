#pragma once
#include <iostream>
#include <mutex>
#include <string>

bool isThreadRunning = false;
std::mutex threadMutex;
std::string consoleOutput;  // This will hold the output for ImGui

void chooseMeal() {
    // Clear previous output
    consoleOutput.clear();

    threadMutex.lock();
    if (isThreadRunning) {
        consoleOutput += "Thread is already running\n";  // Update output instead of std::cout
        threadMutex.unlock();
        return;
    }

    isThreadRunning = true;
    threadMutex.unlock();

    std::string beef[7] = { "Shepherd's Pie", "Mac n Cheese + Steak", "Meatball Bake", "Chilli con carne", "Noodles + Beef + Broccoli", "Burgers", "Beef Stew" };
    std::string chicken[9] = { "Teriyaki Chicken", "Roast Chicken", "Pesto Pasta + Goujons", "Chicken Wraps", "Chicken Curry", "Chicken Breast + Rice + Veg", "Spanish Chicken + Peppers + Rice", "Herb Chicken + Roast potatoes", "Chicken + cacik + rice" };
    std::string pork[7] = { "Teriyaki Pork", "Gammon Steaks + Sweet Potatoes", "Sausages + Cauliflower + Potatoes", "Chipos + Chips + Apple sauce", "Pork Chops + Mash + Peas", "BBQ chipos", "Hot dogs" };
    std::string lamb[7] = { "Lamb + Mash + Aubergine", "Kavurma", "Roast Lamb", "Merguez + Couscous", "Lamb + Beans + Potatoes", "Lamb patties + couscous", "Fasulyia" };
    std::string fish[9] = { "Salmon + pasta + peas", "Fish fingers + mash + peas", "Salmon + Beans + potatoes", "Fish and chips", "White fish + Asparagus + Potatoes", "White fish + Salad + Potatoes", "Salmon + Noodles + Broccoli", "Tuna steaks + sweet potatoes + salad", "Fishcakes + Chips" };
    std::string pasta[7] = { "Bolognese", "Pasta + Aubergine", "Pesto pasta", "Carbonara", "Prawn Spaghetti", "Pasta bake", "Ravioli" };
    std::string soup[8] = { "Butternut Squash soup", "Carrot soup", "Lentil Soup", "Vegetable soup", "Potato and Fish soup", "Broccoli and Brie Soup", "Minestrone", "Leek and peas soup" };

    // Seed once per run
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    // Randomly select meals for each day of the week
    int beefIndex = std::rand() % 7;
    int chickenIndex = std::rand() % 9;
    int porkIndex = std::rand() % 7;
    int lambIndex = std::rand() % 7;
    int fishIndex = std::rand() % 9;
    int pastaIndex = std::rand() % 7;
    int soupIndex = std::rand() % 8;

    consoleOutput += "\nRandomly Selected Meals:\n\n";
    consoleOutput += "Monday: " + beef[beefIndex] + "\n\n";
    consoleOutput += "Tuesday: " + chicken[chickenIndex] + "\n\n";
    consoleOutput += "Wednesday: " + pork[porkIndex] + "\n\n";
    consoleOutput += "Thursday: " + lamb[lambIndex] + "\n\n";
    consoleOutput += "Friday: " + fish[fishIndex] + "\n\n";
    consoleOutput += "Saturday: " + pasta[pastaIndex] + "\n\n";
    consoleOutput += "Sunday: " + soup[soupIndex] + "\n\n";

    consoleOutput += "\nDo you want to reroll the meals? N will return to the main menu! (y/n): \n";

    char choice;
    std::cin >> choice;
    std::cin.ignore();  // Clear input buffer
    while (choice == 'y' || choice == 'Y') {
        chooseMeal();  // Recurse if reroll is chosen
    }

    threadMutex.lock();
    isThreadRunning = false;
    threadMutex.unlock();
}

void customRand() {
    // Clear previous output
    consoleOutput.clear();

    threadMutex.lock();
    if (isThreadRunning) {
        consoleOutput += "Thread is already running\n";  // Update output instead of std::cout
        threadMutex.unlock();
        return;
    }

    isThreadRunning = true;
    threadMutex.unlock();

    std::string days[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    std::string categories[7][7] = {
        { "Beef Stew", "Steak", "Burger", "Roast Beef", "Meatballs", "Lasagna", "Beef Wellington" }, // Beef
        { "Chicken Stir-fry", "Chicken Soup", "Chicken Salad", "Chicken Casserole", "Chicken Wrap", "Grilled Chicken", "Chicken Tacos" }, // Chicken
        { "Pork Roast", "Pulled Pork", "Sausage", "Pork Chops", "Pork Belly", "Bacon", "Pork Ribs" }, // Pork
        { "Lamb Curry", "Grilled Lamb", "Lamb Stew", "Lamb Chop", "Lamb Kebabs", "Lamb Shank", "Roast Lamb" }, // Lamb
        { "Salmon", "Tuna", "Shrimp", "Cod", "Mackerel", "Tilapia", "Sardines" }, // Fish
        { "Spaghetti", "Lasagna", "Fettucine", "Pasta Primavera", "Mac and Cheese", "Pasta Puttanesca", "Pasta Carbonara" }, // Pasta
        { "Tomato Soup", "Minestrone", "Lentil Soup", "Chicken Soup", "Vegetable Soup", "Clam Chowder", "Pea Soup" } // Soup
    };
    int categorySizes[7] = { 7, 7, 7, 7, 7, 7, 7 };  // Each category has 7 options

    // Output prompt for category selection
    consoleOutput += "Choose a category for each day:\n\n";
    consoleOutput += "[0] - Beef\n[1] - Chicken\n[2] - Pork\n[3] - Lamb\n[4] - Fish\n[5] - Pasta\n[6] - Soup\n";

    char rerollChoice;
    do {
        for (int i = 0; i < 7; ++i) {
            int choice;
            consoleOutput += days[i] + ": ";  // Display the day
            std::cin >> choice;

            // Input validation
            while (choice < 0 || choice >= 7) {
                consoleOutput += "Invalid choice. Please enter a number between 0 and 6: ";
                std::cin >> choice;
            }

            int mealIndex = std::rand() % categorySizes[choice];
            consoleOutput += days[i] + ": " + categories[choice][mealIndex] + "\n\n";  // Update output
        }

        consoleOutput += "\nDo you want to reroll the meals? N will return to the main menu! (y/n): \n";
        std::cin >> rerollChoice;

    } while (rerollChoice == 'y' || rerollChoice == 'Y');

    threadMutex.lock();
    isThreadRunning = false;
    threadMutex.unlock();
}
