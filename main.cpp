#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>  

void chooseMeal() {
    // The arrays of the meals
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
        std::cout << "\nRandomly Selected Meals:\n";
        std::cout << "Monday: " << beef[beefIndex] << "\n";
        std::cout << "Tuesday: " << chicken[chickenIndex] << "\n";
        std::cout << "Wednesday: " << pork[porkIndex] << "\n";
        std::cout << "Thursday: " << lamb[lambIndex] << "\n";
        std::cout << "Friday: " << fish[fishIndex] << "\n";
        std::cout << "Saturday: " << pasta[pastaIndex] << "\n";
        std::cout << "Sunday: " << soup[soupIndex] << "\n";

        // Ask the user if they want to reroll
        std::cout << "\nDo you want to reroll the meals? (y/n): ";
        std::cin >> choice;

        // Clear the input buffer to avoid unwanted issues with std::cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (choice == 'y' || choice == 'Y'); // Continue rerolling if user inputs 'y' or 'Y'
}

int main() {

    std::cout << 
        " __   __  _______  _______  ___      __   __  _______  ___   _  _______  ______   " << std::endl <<
        "|  |_|  ||       ||   _   ||   |    |  |_|  ||   _   ||   | | ||       ||    _ |  " << std::endl <<
        "|       ||    ___||  |_|  ||   |    |       ||  |_|  ||   |_| ||    ___||   | ||  " << std::endl <<
        "|       ||   |___ |       ||   |    |       ||       ||      _||   |___ |   |_||_ " << std::endl <<
        "|       ||    ___||       ||   |___ |       ||       ||     |_ |    ___||    __  |" << std::endl <<
        "| ||_|| ||   |___ |   _   ||       || ||_|| ||   _   ||    _  ||   |___ |   |  | |" << std::endl <<
        "|_|   |_||_______||__| |__||_______||_|   |_||__| |__||___| |_||_______||___|  |_|  " << std::endl <<
        " _______  __   __    __   __  _______  __    _  ___   _______                      " << std::endl <<
        "|  _    ||  | |  |  |  | |  ||   _   ||  |  | ||   | |       |                    " << std::endl <<
        "| |_|   ||  |_|  |  |  |_|  ||  |_|  ||   |_| ||   | |  _____|                    " << std::endl <<
        "|       ||       |  |       ||       ||       ||   | | |_____                      " << std::endl <<
        "|  _   | |_     _|  |_     _||       ||  _    ||   | |_____  |                     " << std::endl <<
        "| |_|   |  |   |      |   |  |   _   || | |   ||   |  _____| |                     " << std::endl <<
        "|_______|  |___|      |___|  |__| |__||_|  |__||___| |_______|                     " << std::endl;
    
    chooseMeal();

    return 0;
}
