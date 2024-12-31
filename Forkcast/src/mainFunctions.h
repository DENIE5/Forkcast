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

// Custom meal selection (longer process)
void customRand() {
    if (isCustomRandRunning) return; // Avoid starting if another process is running

    isCustomRandRunning = true;

    std::lock_guard<std::mutex> lock(consoleMutex); // Lock the mutex to safely modify consoleOutput
    consoleOutput.clear();

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
    int categorySizes[7] = { 7, 7, 7, 7, 7, 7, 7 };

    consoleOutput += "Choose a category for each day:\n\n";
    consoleOutput += "[0] - Beef\n[1] - Chicken\n[2] - Pork\n[3] - Lamb\n[4] - Fish\n[5] - Pasta\n[6] - Soup\n";

    for (int i = 0; i < 7; ++i) {
        int choice;
        consoleOutput += days[i] + ": ";
        std::cin >> choice;

        while (choice < 0 || choice >= 7) {
            consoleOutput += "Invalid choice. Please enter a number between 0 and 6: ";
            std::cin >> choice;
        }

        int mealIndex = std::rand() % categorySizes[choice];
        consoleOutput += categories[choice][mealIndex] + "\n\n";
    }

    consoleOutput += "\nDo you want to reroll the meals?\n";

    isCustomRandRunning = false; // Reset flag when done
}

// Start the custom randomization in a separate thread
void startCustomRandThread() {
    std::thread([]() {
        customRand(); // Run the function in its own thread
        }).detach(); // Detach the thread to let it run independently
}
