#pragma once
#include <iostream>

void chooseMeal() {
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
        std::srand(std::time(0));
        seeded = true;
    }

    char choice;
    do {
        // Randomly selecting meals
        int beefIndex = std::rand() % 7;
        int chickenIndex = std::rand() % 9;
        int porkIndex = std::rand() % 7;
        int lambIndex = std::rand() % 7;
        int fishIndex = std::rand() % 9;
        int pastaIndex = std::rand() % 7;
        int soupIndex = std::rand() % 8;

        // Print the randomly selected meals
        std::cout << "\nRandomly Selected Meals:\n\n";
        std::cout << "Monday: " << beef[beefIndex] << "\n\n";
        std::cout << "Tuesday: " << chicken[chickenIndex] << "\n\n";
        std::cout << "Wednesday: " << pork[porkIndex] << "\n\n";
        std::cout << "Thursday: " << lamb[lambIndex] << "\n\n";
        std::cout << "Friday: " << fish[fishIndex] << "\n\n";
        std::cout << "Saturday: " << pasta[pastaIndex] << "\n\n";
        std::cout << "Sunday: " << soup[soupIndex] << "\n\n";

        // Ask the user if they want to reroll
        std::cout << "\nDo you want to reroll the meals? N will return to the main menu! (y/n): ";
        std::cin >> choice;

        // Clear the input buffer to avoid unwanted issues with std::cin
        std::cin.ignore();

    } while (choice == 'y' || choice == 'Y'); // Continue rerolling if user inputs 'y' or 'Y'
}
