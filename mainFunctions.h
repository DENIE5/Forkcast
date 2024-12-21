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

void customRand() {
    // Meal categories arrays of arrays
    std::string categories[7][9] = {
        { "Shepherd's Pie", "Mac n Cheese + Steak", "Meatball Bake", "Chilli con carne", "Noodles + Beef + Broccoli", "Burgers", "Beef Stew" }, // beef
        { "Teriyaki Chicken", "Roast Chicken", "Pesto Pasta + Goujons", "Chicken Wraps", "Chicken Curry", "Chicken Breast + Rice + Veg", "Spanish Chicken + Peppers + Rice", "Herb Chicken + Roast potatoes", "Chicken + cacik + rice" }, // chicken
        { "Teriyaki Pork", "Gammon Steaks + Sweet Potatoes", "Sausages + Cauliflower + Potatoes", "Chipos + Chips + Apple sauce", "Pork Chops + Mash + Peas", "BBQ chipos", "Hot dogs" }, // pork
        { "Lamb + Mash + Aubergine", "Kavurma", "Roast Lamb", "Merguez + Couscous", "Lamb + Beans + Potatoes", "Lamb patties + couscous", "Fasulyia" }, // lamb
        { "Salmon + pasta + peas", "Fish fingers + mash + peas", "Salmon + Beans + potatoes", "Fish and chips", "White fish + Asparagus + Potatoes", "White fish + Salad + Potatoes", "Salmon + Noodles + Broccoli", "Tuna steaks + sweet potatoes + salad", "Fishcakes + Chips" }, // fish
        { "Bolognese", "Pasta + Aubergine", "Pesto pasta", "Carbonara", "Prawn Spaghetti", "Pasta bake", "Ravioli" }, // pasta
        { "Butternut Squash soup", "Carrot soup", "Lentil Soup", "Vegetable soup", "Potato and Fish soup", "Broccoli and Brie Soup", "Minestrone", "Leek and peas soup" } // soup
    };

    int categorySizes[7] = { 7, 9, 7, 7, 9, 7, 8 };
    std::string days[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

    std::cout << "Choose a category for each day:\n\n";
    std::cout << "[0] - Beef\n[1] - Chicken\n[2] - Pork\n[3] - Lamb\n[4] - Fish\n[5] - Pasta\n[6] - Soup\n";


    char rerollChoice;

    do {
        for (int i = 0; i < 7; ++i) {
            int choice;
            std::cout << days[i] << ": ";
            std::cin >> choice;

            // Validate input
            while (choice < 0 || choice >= 7) {
                std::cout << "Invalid choice. Please enter a number between 0 and 6: ";
                std::cin >> choice;
            }

            int mealIndex = std::rand() % categorySizes[choice];
            std::cout << days[i] << ": " << categories[choice][mealIndex] << "\n\n";

        }

        // Ask the user if they want to reroll
        std::cout << "\nDo you want to reroll the meals? N will return to the main menu! (y/n): ";
        std::cin >> rerollChoice;


        // Clear the input buffer to avoid unwanted issues with std::cin

    } while (rerollChoice == 'y' || rerollChoice == 'Y');

}