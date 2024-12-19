# 🥄 Forkcast
Forkcast is a playful and interactive meal-planning tool written in C++. It generates a randomized weekly meal plan or allows users to customize their meal choices for each day. Perfect for anyone looking for variety or a little inspiration in their weekly menus!

---

## 📋 Features
1. **Full Randomization**:  
   Automatically generates a meal plan for the week with one random dish for each day.

2. **Custom Randomization**:  
   Choose a category (e.g., Beef, Chicken, Fish, etc.) for each day, and Forkcast will randomly select a dish from the chosen category.

3. **Re-roll Options**:  
   - Reroll the meals for an entirely new plan.
   - Return to the main menu to start over or exit.

4. **User-Friendly Console Menu**:  
   An intuitive menu system makes it easy to navigate and use.

---

## 🍽️ Meal Categories
Forkcast offers a wide selection of meal options, categorized as follows:<br>

Beef<br>
Chicken<br>
Pork<br>
Lamb<br>
Fish<br>
Pasta<br>
Soup<br>
Each category contains multiple unique dishes, ensuring variety.<br>

## 🛠️ Technical Details
Language: C++ <br>
Randomization: Utilizes std::srand() and std::rand() seeded with the current time for randomized meal selection.<br>
Error Handling: Includes input validation to ensure smooth user interaction.<br>
Platform: Console-based application.<br>

## 🌟 Future Improvements
Allow users to save their generated meal plans to a file.<br>
Enable custom meal entries by users.<br>
