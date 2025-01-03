#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <windows.h>
#include <atomic>

// Shared output for ImGui and mutex for thread safety
std::string consoleOutput;
std::mutex consoleMutex;    
std::atomic<bool> isCustomRandRunning(false); // Flag for custom randomization

// Define days of the week
std::string days[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

// Define categories and meals
std::string categories[7][7] = {
    { "Beef Stew", "Steak", "Burger", "Roast Beef", "Meatballs", "Lasagna", "Beef Wellington" }, 
    { "Chicken Stir-fry", "Chicken Soup", "Chicken Salad", "Chicken Casserole", "Chicken Wrap", "Grilled Chicken", "Chicken Tacos" }, 
    { "Pork Roast", "Pulled Pork", "Sausage", "Pork Chops", "Pork Belly", "Bacon", "Pork Ribs" }, 
    { "Lamb Curry", "Grilled Lamb", "Lamb Stew", "Lamb Chop", "Lamb Kebabs", "Lamb Shank", "Roast Lamb" }, 
    { "Salmon", "Tuna", "Shrimp", "Cod", "Mackerel", "Tilapia", "Sardines" }, 
    { "Spaghetti", "Lasagna", "Fettucine", "Pasta Primavera", "Mac and Cheese", "Pasta Puttanesca", "Pasta Carbonara" }, 
    { "Tomato Soup", "Minestrone", "Lentil Soup", "Chicken Soup", "Vegetable Soup", "Clam Chowder", "Pea Soup" } 
};

int categorySizes[7] = { 7, 7, 7, 7, 7, 7, 7 };

// Function to initialize categories and days
void initializeCategoriesAndDays() {
    consoleOutput += "Choose a category for each day:\n\n";
    consoleOutput += "Beef\nChicken\nPork\nLamb\nFish\nPasta\nSoup\n\n";
}

// Function to get user input for a specific day
void getUserInputForDay(int dayIndex) {
    int choice;
    consoleOutput += days[dayIndex] + ": ";
    std::cin >> choice;

    // Validate input
    while (choice < 0 || choice >= 7) {
        consoleOutput += "Invalid choice. Please enter a number between 0 and 6: ";
        std::cin >> choice;
    }

    // Generate the meal for the selected category
    int mealIndex = std::rand() % categorySizes[choice];
    consoleOutput += categories[choice][mealIndex] + "\n\n";
}

// Function to generate the meal plan
void generateMealPlan() {
    for (int i = 0; i < 7; ++i) {
        getUserInputForDay(i); // Get user input for each day
    }
    consoleOutput += "\nDo you want to reroll the meals?\n";
}

// Main function for custom randomization
void customRand() {
    if (isCustomRandRunning) return;

    isCustomRandRunning = true;
    std::lock_guard<std::mutex> lock(consoleMutex); // Lock the mutex 
    consoleOutput.clear();

    // Step 1: Initialize categories and days
    initializeCategoriesAndDays();

    // Step 2: Generate meal plan based on user input
    generateMealPlan();

    isCustomRandRunning = false; // Reset flag 
}

// A second step that handles meal generation for a specific day (example)
void customStep2() {
    if (isCustomRandRunning) return; 

    isCustomRandRunning = true;
    std::lock_guard<std::mutex> lock(consoleMutex); // Lock the mutex 

    consoleOutput += "Tuesday: ";
    int mealIndex = std::rand() % 7;
    consoleOutput += categories[1][mealIndex] + "\n\n";
}

// Start the custom randomization in a separate thread
void startCustomRandThread() {
    std::thread([]() {
        customRand(); 
        }).detach(); 
}

