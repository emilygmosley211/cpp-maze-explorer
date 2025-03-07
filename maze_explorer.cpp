#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random maze
void generateMaze(char maze[40][40], int& width, int& height, int difficulty) {
    srand(time(0)); // Seed for random number generation

    // Set maze dimensions based on difficulty
    switch(difficulty) {
        case 1: // Easy
            width = rand() % 20 + 20;   // Width between 20 and 40
            height = rand() % 10 + 10;  // Height between 10 and 20
            break;
        case 2: // Medium
            width = rand() % 15 + 30;   // Width between 30 and 45
            height = rand() % 10 + 15;  // Height between 15 and 25
            break;
        case 3: // Hard
            width = rand() % 10 + 40;   // Width between 40 and 50
            height = rand() % 10 + 20;  // Height between 20 and 30
            break;
        default:
            width = 40;
            height = 20;
    }

    // Initialize all cells as walls
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            maze[y][x] = '#';
        }
    }

    // Create paths with random walls
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (rand() % 4 != 0) { // Randomly make some cells paths
                maze[y][x] = '.';
            }
        }
    }

    // Make sure the start point and exit are open
    maze[1][1] = '.';  // Start point
    maze[height - 1][width / 2] = '.';  // Exit at the bottom center

    // Ensure there are no walls blocking the exit
    if (maze[height - 2][width / 2] != '.') maze[height - 2][width / 2] = '.';
    if (maze[height - 1][width / 2 - 1] != '.') maze[height - 1][width / 2 - 1] = '.';
    if (maze[height - 1][width / 2 + 1] != '.') maze[height - 1][width / 2 + 1] = '.';

    // Place random $ symbols (collectibles) in the maze
    for (int i = 0; i < 5; i++) {
        int randX = rand() % (width - 2) + 1;
        int randY = rand() % (height - 2) + 1;
        if (maze[randY][randX] == '.') {
            maze[randY][randX] = '$';
        }
    }
}

// Function to display the maze
void displayMaze(char maze[40][40], int width, int height, int playerX, int playerY) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == playerX && y == playerY) {
                cout << 'P'; // Player's position
            } else {
                cout << maze[y][x];
            }
        }
        cout << endl;
    }
}

// Function to check if the player has reached the exit
bool isExit(int playerX, int playerY, int width, int height) {
    return (playerX == width / 2 && playerY == height - 1); // Exit is at the center of the bottom row
}

int main() {
    char maze[40][40];
    int playerX, playerY, points;
    bool gameOver, playAgain;
    int width, height;
    int difficulty;

    // Game loop for repeated play
    do {
        cout << "Choose Difficulty (1 = Easy, 2 = Medium, 3 = Hard): ";
        cin >> difficulty;

        // Ensure valid difficulty selection
        while (difficulty < 1 || difficulty > 3) {
            cout << "Invalid choice. Choose Difficulty (1 = Easy, 2 = Medium, 3 = Hard): ";
            cin >> difficulty;
        }

        playerX = 1; playerY = 1; // Starting position
        points = 0; // Initialize points
        gameOver = false;

        generateMaze(maze, width, height, difficulty);

        // Game loop
        while (!gameOver) {
            displayMaze(maze, width, height, playerX, playerY);

            if (isExit(playerX, playerY, width, height)) {
                cout << "Congratulations! You reached the exit!" << endl;
                cout << "Your total points: " << points << endl;
                break;
            }

            cout << "Move (W = up, S = down, A = left, D = right): ";
            char move;
            cin >> move;

            int nextX = playerX, nextY = playerY;

            // Determine next position based on user input
            if (move == 'W' || move == 'w') nextY--;  // Move up
            else if (move == 'S' || move == 's') nextY++; // Move down
            else if (move == 'A' || move == 'a') nextX--; // Move left
            else if (move == 'D' || move == 'd') nextX++; // Move right

            // Check if the next position is within bounds and not a wall
            if (nextX >= 0 && nextX < width && nextY >= 0 && nextY < height && maze[nextY][nextX] != '#') {
                playerX = nextX;
                playerY = nextY;

                // Check if the player collects a $
                if (maze[playerY][playerX] == '$') {
                    cout << "You collected a $!" << endl;
                    maze[playerY][playerX] = '.'; // Turn $ into a path block
                    points++; // Increase the player's points
                }
            } else {
                cout << "Invalid move! Try again." << endl;
            }
        }

        // Ask if the player wants to play again
        cout << "Do you want to play again? (1 for Yes, 0 for No): ";
        cin >> playAgain;

    } while (playAgain); // Repeat the game if the player chooses to play again

    cout << "Thank you for playing! Goodbye!" << endl;

    return 0;
}