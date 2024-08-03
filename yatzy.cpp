#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <limits>

using namespace std;

// Constants
const int NUM_DICE = 5;           // Number of dice
const int NUM_SIDES = 6;          // Number of sides on each die
const int NUM_ROLLS = 3;          // Number of rolls per turn

// Enum for score categories in Yatzy
enum ScoreCategory {
    ONES, TWOS, THREES, FOURS, FIVES, SIXES,
    THREE_OF_A_KIND, FOUR_OF_A_KIND, FULL_HOUSE,
    SMALL_STRAIGHT, LARGE_STRAIGHT, YATZY, CHANCE
};

// Names of score categories for display
const vector<string> categoryNames = {
    "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes",
    "Three of a Kind", "Four of a Kind", "Full House",
    "Small Straight", "Large Straight", "Yatzy", "Chance"
};

// Game variables
vector<int> dice(NUM_DICE);               // Values of the dice
vector<bool> hold(NUM_DICE, false);       // Whether each die is held or not
vector<int> categoryScores(categoryNames.size(), 0);  // Scores for each category

// Functions to draw dice faces


void drawDie1() {
    cout << " -------\n"
         << "|       |\n"
         << "|   O   |\n"
         << "|       |\n"
         << " ------- \n";
}

void drawDie2() {
    cout << " -------\n"
         << "| O     |\n"
         << "|       |\n"
         << "|     O |\n"
         << " ------- \n";
}

void drawDie3() {
    cout << " -------\n"
         << "| O     |\n"
         << "|   O   |\n"
         << "|     O |\n"
         << " ------- \n";
}

void drawDie4() {
    cout << " -------\n"
         << "| O   O |\n"
         << "|       |\n"
         << "| O   O |\n"
         << " ------- \n";
}

void drawDie5() {
    cout << " -------\n"
         << "| O   O |\n"
         << "|   O   |\n"
         << "| O   O |\n"
         << " ------- \n";
}

void drawDie6() {
    cout << " -------\n"
         << "| O   O |\n"
         << "| O   O |\n"
         << "| O   O |\n"
         << " ------- \n";
}

// Draw the die based on the value (1-6)
void drawDie(int value) {
    switch (value) {
        case 1: drawDie1(); break;
        case 2: drawDie2(); break;
        case 3: drawDie3(); break;
        case 4: drawDie4(); break;
        case 5: drawDie5(); break;
        case 6: drawDie6(); break;
    }
}

// Roll the dice, considering which ones are held
void rollDice() {
    for (int i = 0; i < NUM_DICE; ++i) {
        if (!hold[i]) { // Roll only if the die is not held
            dice[i] = rand() % NUM_SIDES + 1; // Random number between 1 and 6
        }
    }
}

// Display all dice
void displayDice() {
    cout << "*Dice roll sound* Here's your dice:\n";
    for (int i = 0; i < NUM_DICE; ++i) {
        drawDie(dice[i]);
    }
}

// Display categories that haven't been scored yet
void displayRemainingCategories(const vector<bool>& scoredCategories) {
    cout << "Remaining score categories:\n";
    for (int i = 0; i < categoryNames.size(); ++i) {
        if (!scoredCategories[i]) {  // Only show categories that haven't been scored yet
            cout << i + 1 << ". " << categoryNames[i] << endl;
        }
    }
}

// Prompt the player to choose a category to score
ScoreCategory getPlayerCategoryChoice(const vector<bool>& scoredCategories) {
    int choice;
    while (true) {
        cout << "Enter the number of the category: ";
        cin >> choice;
        if (choice >= 1 && choice <= categoryNames.size() && !scoredCategories[choice - 1]) {
            return static_cast<ScoreCategory>(choice - 1);
        } else {
            cout << "Invalid choice!\n";
        }
    }
}

// Allow player to choose which dice to hold
void getPlayerChoices() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ensure the input buffer is clear

    cout << "Enter the positions (1-5) of dice to hold (separated by spaces), or 0 to roll all: ";
    string input;
    getline(cin, input);

    // Reset hold array
    hold.assign(NUM_DICE, false);

    if (input == "0") {
        return;
    }

    // Parse input to determine held dice
    istringstream ss(input);
    int pos;
    while (ss >> pos) {
        if (pos > 0 && pos <= NUM_DICE) {
            hold[pos - 1] = true; // Set hold for specified dice
        }
    }
}

// Calculate score for the given category based on current dice values
int calculateScore(const vector<int>& dice, ScoreCategory category) {
    vector<int> counts(NUM_SIDES, 0); // Count occurrences of each die face
    for (int die : dice) {
        counts[die - 1]++;
    }

    int score = 0;
    
    switch (category) {
        case ONES: case TWOS: case THREES: case FOURS: case FIVES: case SIXES:
            // Sum up the values of dice matching the category
            score = (category + 1) * counts[category];
            break;
            
        case THREE_OF_A_KIND:
            // Sum all dice if there are at least three of the same kind
            for (int i = 0; i < NUM_SIDES; ++i) {
                if (counts[i] >= 3) {
                    for (int die : dice) {
                        score += die;
                    }
                    break;
                }
            }
            break;
            
        case FOUR_OF_A_KIND:
            // Sum all dice if there are at least four of the same kind
            for (int i = 0; i < NUM_SIDES; ++i) {
                if (counts[i] >= 4) {
                    for (int die : dice) {
                        score += die;
                    }
                    break;
                }
            }
            break;
            
        case FULL_HOUSE:
            // 25 points for a full house (3 of one number and 2 of another)
            {
                bool threeOfAKind = false, pair = false;
                for (int count : counts) {
                    if (count == 3) threeOfAKind = true;
                    if (count == 2) pair = true;
                }
                if (threeOfAKind && pair) score = 25;
            }
            break;

        case SMALL_STRAIGHT:
            // 30 points for a small straight (sequence of four numbers)
            {
                if ((counts[0] >= 1 && counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1) ||
                    (counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1) ||
                    (counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1)) {
                    score = 30;
                }
            }
            break;
            
        case LARGE_STRAIGHT:
            // 40 points for a large straight (sequence of five numbers)
            {
                if ((counts[0] == 1 && counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1) ||
                    (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1)) {
                    score = 40;
                }
            }
            break;
            
        case YATZY:
            // 50 points for five of a kind
            for (int count : counts) {
                if (count == 5) {
                    score = 50;
                }
            }
            break;
            
        case CHANCE:
            // Sum of all dice
            for (int die : dice) {
                score += die;
            }
            break;
    }

    return score;
}

// Mark a category as scored and update the player's score
void markCategoryAsScored(vector<bool>& scoredCategories, ScoreCategory category, int score) {
    scoredCategories[category] = true;
    categoryScores[category] = score; // Store score for the category
}

// Suggest possible scoring options based on the current dice and available categories
vector<ScoreCategory> suggestScoringOptions(const vector<int>& dice, const vector<bool>& scoredCategories) {
    vector<ScoreCategory> options; // List of suggested categories
    vector<int> counts(NUM_SIDES, 0); // Count occurrences of each die face
    for (int die : dice) {
        counts[die - 1]++;
    }

    // Suggest single-number categories (Ones, Twos, etc.) if they can be scored
    for (int i = ONES; i <= SIXES; ++i) {
        if (counts[i] > 0 && !scoredCategories[i]) {
            options.push_back(static_cast<ScoreCategory>(i));
        }
    }

    // Check for three of a kind
    for (int i = 0; i < NUM_SIDES; ++i) {
        if (counts[i] >= 3 && !scoredCategories[THREE_OF_A_KIND]) {
            options.push_back(THREE_OF_A_KIND);
            break;
        }
    }

    // Check for four of a kind
    for (int i = 0; i < NUM_SIDES; ++i) {
        if (counts[i] >= 4 && !scoredCategories[FOUR_OF_A_KIND]) {
            options.push_back(FOUR_OF_A_KIND);
            break;
        }
    }

    // Check for full house
    bool threeOfAKind = false, pair = false;
    for (int count : counts) {
        if (count == 3) threeOfAKind = true;
        if (count == 2) pair = true;
    }
    if (threeOfAKind && pair && !scoredCategories[FULL_HOUSE]) options.push_back(FULL_HOUSE);

    // Check for small straight
    if (!scoredCategories[SMALL_STRAIGHT] &&
        ((counts[0] >= 1 && counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1) ||
         (counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1) ||
         (counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1))) {
        options.push_back(SMALL_STRAIGHT);
    }

    // Check for large straight
    if (!scoredCategories[LARGE_STRAIGHT] &&
        ((counts[0] == 1 && counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1) ||
         (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1))) {
        options.push_back(LARGE_STRAIGHT);
    }

    // Check for Yatzy
    for (int count : counts) {
        if (count == 5 && !scoredCategories[YATZY]) {
            options.push_back(YATZY);
        }
    }

    // Chance is always an option if not yet scored
    if (!scoredCategories[CHANCE]) {
        options.push_back(CHANCE);
    }

    return options;
}

// Main game loop
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
    vector<bool> scoredCategories(categoryNames.size(), false); // Track which categories have been scored

    // Main game loop
    while (true) {
        int rollsLeft = NUM_ROLLS; // Reset rolls for the turn

        // Reset hold for new turn
        hold.assign(NUM_DICE, false);

        // Allow the player to roll the dice up to NUM_ROLLS times
        while (rollsLeft > 0) {
            rollDice();
            displayDice();

            // Suggest scoring options based on current dice
            vector<ScoreCategory> options = suggestScoringOptions(dice, scoredCategories);

            // Check if there are no scoring options available
            if (options.empty()) {
                cout << "No valid scoring options available. You must choose a category and score 0.\n";
                break;  // End the current turn
            }

            // If there are rolls left, allow the player to choose dice to hold
            if (rollsLeft > 1) {
                getPlayerChoices();
            }

            --rollsLeft;
        }

        // Final roll result
        displayDice();
        cout << "Final roll complete." << endl;

        // Display remaining categories
        displayRemainingCategories(scoredCategories);

        // Display suggested scoring options
        vector<ScoreCategory> options = suggestScoringOptions(dice, scoredCategories);
        if (options.empty()) {
            cout << "No valid scoring options available. Game over!" << endl;
            break;
        }

        cout << "Suggested categories to score:\n";
        for (auto category : options) {
            if (!scoredCategories[category]) {
                cout << (category + 1) << ". " << categoryNames[category] << endl;
            }
        }

        // Allow player to choose category and score
        ScoreCategory chosenCategory = getPlayerCategoryChoice(scoredCategories);

        // Calculate and display score for the chosen category
        int score = calculateScore(dice, chosenCategory);
        cout << "Your score for " << categoryNames[chosenCategory] << ": " << score << endl;

        // Mark category as scored and update score
        markCategoryAsScored(scoredCategories, chosenCategory, score);

        // Check if all categories have been scored
        bool allScored = true;
        for (bool scored : scoredCategories) {
            if (!scored) {
                allScored = false;
                break;
            }
        }

        // End game if all categories are scored
        if (allScored) {
            cout << "All categories have been scored, game over!" << endl;

            // Calculate and display the total score
            int totalScore = 0;
            for (int categoryScore : categoryScores) {
                totalScore += categoryScore;
            }
            cout << "Total score: " << totalScore << endl;
            break;
        }
    }

    return 0;
}
