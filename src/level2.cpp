#include "C:\raylib\raylib\src\raylib.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include<iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include "hermione.h"
#include "globals.h"

Hermione hermione;        // Create Hermione object
bool gameWon = false;     // Flag to track if the game is won
bool gameOver = false;    // Flag to track if the game is over
const int numrows = 20;   // Number of rows
const int ncols = 39;     // Number of columns
const int cellSize =655/ numrows; // Size of each cell
const int numGhosts = 10; // Number of ghosts
const int numCoinss = 35;
int coinsCollected = 0;           // Counter for collected coins
float blastDisplayTime = 0.0f;    // Timer for blast display duration
const float blastDuration = 1.0f; // Duration to display the blast (in seconds)
float moveCooldown = 0.2f;        // cooldown time between moves in sec
float moveTimer = 0.0f;
Color customGreen = { 1, 50, 35, 255 };




void extraLife()
{
    CollectibleCount = CollectibleCount / 5;
}

// Cell structure definition
struct Cell
{
    bool visited = false;
    bool walls[4] = {true, true, true, true}; // Top, Right, Bottom, Left
    int r, c;                                 // Row and Column
    std::vector<Cell *> neighbors;            // Neighboring cells
};

// Player structure definition
struct Player
{
    int r, c;          // Player's row and column position
    Texture2D texture; // Player texture
};

// Blast structure definition
struct Blast
{
    int r, c;          // Blast's row and column position
    Texture2D texture; // Blast texture
};
// Blast object
Blast blast = {-1, -1};

// Ghost structure definition
struct Ghost
{
    int r, c;          // Ghost's row and column position
    Texture2D texture; // Ghost texture
};
struct Coin
{
    int r, c;          // Coin's row and column position
    Texture2D texture; // Coin texture
};



// Global variables
std::vector<Cell> grid(numrows *ncols);
Cell *current = nullptr;
std::vector<Cell *> stack;
bool play = false;
Player player = {0, 0};    // Initialize player at the starting position
std::vector<Ghost> ghosts; // List of ghosts
std::vector<Coin> coins;   // List of coins
Sound collide;             // Collision sound
Sound attack;             // Attack sound
Sound move;                // Move sound
Sound coincollected;       // Coin collection sound
Music music;               // Music stream
Sound gameover;            // Game over sound
Sound win;                // Win sound
Texture2D bgTexture;

// Collision management variables
bool isColliding = false;   // Track if the player has collided
float collisionTime = 5.0f; // Timer for how long to pause the music

// Timer variables
auto startTime = std::chrono::steady_clock::now();
auto endTime = startTime + std::chrono::minutes(6);
void Initnew2() //Reset level2
{
    gameWon=false;
    gameOver=false;
    coinsCollected=0;
    startTime = std::chrono::steady_clock::now();
    endTime = startTime + std::chrono::minutes(6);
    isColliding = false; 
    player.r=0;
    player.c=0;
    isColliding=false;
    play=false;
    for (auto &cell : grid)
    {
        cell.walls[0] = true;
        cell.walls[1] = true;
        cell.walls[2] = true;
        cell.walls[3] = true;
        cell.visited = false;
    }
    
    
}

// Function to initialize the grid
// Function to initialize the grid
void InitGrid()
{
    for (int r = 0; r < numrows; r++)
    {
        for (int c = 0; c < ncols; c++)
        {
            grid[r * ncols + c].r = r;
            grid[r * ncols + c].c = c;
            if (r > 0)
                grid[r * ncols + c].neighbors.push_back(&grid[(r - 1) * ncols + c]); // Top neighbor
            if (c < ncols - 1)
                grid[r * ncols + c].neighbors.push_back(&grid[r * ncols + (c + 1)]); // Right neighbor
            if (r < numrows - 1)
                grid[r * ncols + c].neighbors.push_back(&grid[(r + 1) * ncols + c]); // Bottom neighbor
            if (c > 0)
                grid[r * ncols + c].neighbors.push_back(&grid[r * ncols + (c - 1)]); // Left neighbor
        }
    }
}

void DrawMaze()
{
    DrawTexture(bgTexture, 0, 0, WHITE); 
    // Define the height for the score display section (top part)
    const int scoreSectionHeight = 50;

    // Start drawing the maze from just below the score section
    int startY = scoreSectionHeight;

    // Draw the maze (cells, walls, player, ghosts, coins) below the score section
    for (int r = 0; r < numrows; r++)
    {
        for (int c = 0; c < ncols; c++)
        {
            Cell &cell = grid[r * ncols + c];
            int drawY = startY + r * cellSize; // Y position adjusted to start below the score section

            // Draw cell background
            if (cell.visited)
            {
                // RGB values with alpha 255 (fully opaque)
                DrawRectangle(c * cellSize, drawY, cellSize, cellSize, customGreen);

            }
            
            // Draw walls
            if (cell.walls[0]) // Top wall
                DrawLine(c * cellSize, drawY, (c + 1) * cellSize, drawY, BLACK);
            if (cell.walls[1]) // Right wall
                DrawLine((c + 1) * cellSize, drawY, (c + 1) * cellSize, drawY + cellSize, BLACK);
            if (cell.walls[2]) // Bottom wall
                DrawLine(c * cellSize, drawY + cellSize, (c + 1) * cellSize, drawY + cellSize, BLACK);
            if (cell.walls[3]) // Left wall
                DrawLine(c * cellSize, drawY, c * cellSize, drawY + cellSize, BLACK);
        }
    }
   

    // Draw the player (Harry) texture
    int playerFrameX = player.c * cellSize;
    int playerFrameY = startY + player.r * cellSize; // Adjust player Y position based on maze start below score section
    DrawRectangle(playerFrameX, playerFrameY, cellSize - 1, cellSize - 1, customGreen); // Player frame background
    float playerScale = 0.1f; // Scale player texture
    DrawTextureEx(player.texture,
                  Vector2{playerFrameX + (cellSize - player.texture.width * playerScale) / 2,
                          playerFrameY + (cellSize - player.texture.height * playerScale) / 2},
                  0.0f, playerScale, WHITE);
    // Draw the blast texture if it's within the grid
    if (blast.r >= 0 && blast.c >= 0)
    {
        int blastFrameX = blast.c * cellSize;                                           // X position of the blast's frame
        int blastFrameY = blast.r * cellSize;                                           // Y position of the blast's frame
        DrawRectangle(blastFrameX, blastFrameY, cellSize - 1, cellSize - 1, DARKGREEN); // Frame background
        float blastScale = 0.1f; // Scale the blast texture to 5% of original size
        DrawTextureEx(blast.texture,
                      Vector2{blastFrameX + (cellSize - blast.texture.width * blastScale) / 2,
                              blastFrameY + (cellSize - blast.texture.height * blastScale) / 2},
                      0.0f, blastScale, customGreen);
    }

    // Draw ghosts inside a frame
    float ghostScale = 0.05f; // Scale ghosts to 5% of their original size
    for (const Ghost &ghost : ghosts)
    {
        int ghostFrameX = ghost.c * cellSize;
        int ghostFrameY = startY + ghost.r * cellSize; // Adjust ghost Y position
        DrawTextureEx(ghost.texture,
                      Vector2{ghostFrameX + (cellSize - ghost.texture.width * ghostScale) / 2,
                              ghostFrameY + (cellSize - ghost.texture.height * ghostScale) / 2},
                      0.0f, ghostScale, WHITE); // Draw the ghost texture
    }

    // Draw coins inside a frame
    float coinScale = 0.06f; // Scale coins to 6% of their original size
    for (const Coin &coin : coins)
    {
        int coinFrameX = coin.c * cellSize;
        int coinFrameY = startY + coin.r * cellSize; // Adjust coin Y position
        DrawTextureEx(coin.texture,
                      Vector2{coinFrameX + (cellSize - coin.texture.width * coinScale) / 2,
                              coinFrameY + (cellSize - coin.texture.height * coinScale) / 2},
                      0.0f, coinScale, WHITE); // Draw the coin texture
    }


}


void MazeGenerator()
{
    if (!current->visited)
    {
        current->visited = true;
        stack.push_back(current);
    }

    std::vector<Cell *> unvisited;
    for (Cell *neigh : current->neighbors)
    {
        if (!neigh->visited)
        {
            unvisited.push_back(neigh);
        }
    }

    if (!unvisited.empty())
    {
        int randomIndex = std::rand() % unvisited.size();
        Cell *next = unvisited[randomIndex];

        // Remove walls
        if (current->r - next->r == 1)
        { // Top
            current->walls[0] = false;
            next->walls[2] = false;
        }
        else if (current->c - next->c == 1)
        { // Left
            current->walls[3] = false;
            next->walls[1] = false;
        }
        else if (current->r - next->r == -1)
        { // Bottom
            current->walls[2] = false;
            next->walls[0] = false;
        }
        else if (current->c - next->c == -1)
        { // Right
            current->walls[1] = false;
            next->walls[3] = false;
        }

        current = next;
    }
    else if (!stack.empty())
    {
        current = stack.back();
        stack.pop_back();
    }
    else
    {
        play = true; // Maze generation completed
    }
}





void UpdatePlayer()
{
    // update the movement timer
    moveTimer += GetFrameTime();

    // Check for player movement
    if (moveTimer >= moveCooldown)
    {

        if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && !grid[player.r * ncols + player.c].walls[0])
        { // Up
            player.r--;
            PlaySound(move); // Play move sound
            moveTimer = 0.0f; // reset timer
        }
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && !grid[player.r * ncols + player.c].walls[1])
        { // Right
            player.c++;
            moveTimer = 0.0f;
            PlaySound(move); // Play move sound
        }
        if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && !grid[player.r * ncols + player.c].walls[2])
        { // Down
            player.r++;
            moveTimer = 0.0f;
            PlaySound(move); // Play move sound
        }
        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && !grid[player.r * ncols + player.c].walls[3])
        { // Left
            player.c--;
            moveTimer = 0.0f;
            PlaySound(move); // Play move sound
        }
    }

    // Check for collision with Hermione
    if (player.r == numrows-1 && player.c == ncols-1)
    {
        gameWon = true; // Set the win flag
     
    }
 

    // Check for collision with coins
    for (auto it = coins.begin(); it != coins.end();)
    {
        if (player.r == it->r && player.c == it->c)
        {
            coinsCollected++;         // Increment the coin counter
            StopSound(move); // Stop the coin collection sound
            PlaySound(coincollected); // coin collection sound
            it = coins.erase(it);     // Remove the collected coin
        }
        else
        {
            ++it;
        }
    }
}
// Function to initialize ghosts
void InitGhosts()
{
    for (int i = 0; i < numGhosts; i++)
    {
        Ghost ghost;
        ghost.r = std::rand() % numrows;
        ghost.c = std::rand() % ncols;
        ghost.texture = LoadTexture("./images/ghost.png"); // Load ghost texture
        ghosts.push_back(ghost);
    }
}
void InitCoins()
{
    for (int i = 0; i < numCoinss; i++)
    {
        Coin coin;
        coin.r = std::rand() % numrows;
        coin.c = std::rand() % ncols;
        coin.texture = LoadTexture("./images/coin.png"); // Load coin texture
        coins.push_back(coin);
    }
}

// Function to update ghosts
void UpdateGhosts()
{
    for (auto it = ghosts.begin(); it != ghosts.end();)
    {
        Ghost &ghost = *it;
        int direction = std::rand() % 4; // Random direction: 0 = up, 1 = right, 2 = down, 3 = left

        int newR = ghost.r;
        int newC = ghost.c;

        switch (direction)
        {
        case 0:
            newR--;
            break; // Up
        case 1:
            newC++;
            break; // Right
        case 2:
            newR++;
            break; // Down
        case 3:
            newC--;
            break; // Left
        }

        // Check for valid move
        if (newR >= 0 && newR < numrows && newC >= 0 && newC < ncols &&
            !grid[ghost.r * ncols + ghost.c].walls[direction])
        {
            ghost.r = newR;
            ghost.c = newC;
        }

        // Check for collision with player
        if (ghost.r == player.r && ghost.c == player.c)
        {
            // If there are collectibles, remove the collided ghost
            if (CollectibleCount > 0)
            {
                blast.r = ghost.r;
                blast.c = ghost.c;
                PlaySound(attack);     // Play collision sound
                --CollectibleCount;    // Decrease the collectibles count
                it = ghosts.erase(it); // Remove the collided ghost
                // Optionally, you can add a sound or effect here for ghost removal
            }
            else
            {
                // If no collectibles, reset player to initial position
                PlaySound(collide); // Play collision sound
                player.r = 0;
                player.c = 0;

                // Stop the music and set collision flag
                StopMusicStream(music);
                isColliding = true;
                collisionTime = 3.0f; // Set collision duration (3 seconds)
                ++it;                 // Continue to the next ghost after handling collision
            }
        }
        else
        {
            ++it; // Continue to the next ghost if no collision
        }
    }
}

// Function to draw the remaining time
void DrawRemainingTime()
{
    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(endTime - now).count();

    if (remaining <= 0)
    {
        gameOver = true;
        remaining = 0;
    }

    DrawText(
    TextFormat(": %02d:%02d", remaining / 60, remaining % 60),
    270,  
    15,   
    25, 
    BLACK   // Color
);

    // coins collected
    DrawText(TextFormat(": %d", coinsCollected),
             520, 15, 25, BLACK);
}

// UPDATE level 2 function, including all elements
void UpdateLevel2()
{
    static bool initialized = false; // Static variable to track initialization

    if (!initialized)
    {
        // Load sounds and music after initializing audio device
        collide = LoadSound("./Audio/ghostcollide.wav");      // Load collision sound
        music = LoadMusicStream("./Audio/sound.wav");         // Load music stream
        coincollected = LoadSound("./Audio/chime-sound.mp3"); // Load coin collection sound
        attack = LoadSound("./Audio/attack.mp3");             // Load attack sound
        gameover = LoadSound("./Audio/gameover.wav");         // Load game over sound
        win = LoadSound("./Audio/win.mp3");                   // Load win sound
        move = LoadSound("./Audio/step.mp3");                 // Load move sound
        PlayMusicStream(music);                               // Start playing music

        std::srand(static_cast<unsigned>(std::time(0))); // Seed random number generator

        InitGrid();         // Initialize the grid
        current = &grid[0]; // Start from the first cell

        // Load player texture
        player.texture = LoadTexture("./images/harry.png");
        hermione.texture = LoadTexture("./images/hermione.png");
        blast.texture = LoadTexture("./images/blast.png");
        bgTexture = LoadTexture("./images/score.png");
        


        hermione.r = numrows; // Set Hermione's position to the last row
        hermione.c = ncols-1;   // Set Hermione's position to the last column
        InitGhosts();             // Initialize ghosts
        InitCoins();              // Initialize coins

        initialized = true; // Set initialization flag to true
    }

    if (!play)
    {
        MazeGenerator(); // Continue generating the maze until complete
        // Update the music stream
        UpdateMusicStream(music); // Ensure music plays smoothly
    }
    else
    {
        if (!gameOver && !gameWon)
        {
            UpdatePlayer(); // Update player position once the maze is generated
            UpdateGhosts(); // Update ghosts
        }
    }

    // Handle collision timing
    if (isColliding)
    {
        collisionTime -= GetFrameTime(); // Decrease the collision timer
        if (collisionTime <= 0.2f)
        {
            isColliding = false; // Reset collision flag
        }
    }

    // Update blast display timer
    if (blast.r >= 0 && blast.c >= 0)
    {
        blastDisplayTime += GetFrameTime(); // Increment the timer
        if (blastDisplayTime >= blastDuration)
        {
            blast.r = -1; // Reset blast position
            blast.c = -1;
            blastDisplayTime = 0.0f; // Reset the timer
        }
    }
}
// DRAW level 2 function
void DrawLevel2()
{
    ClearBackground(DARKGREEN);            // Clear the screen
    DrawMaze();                       // Draw the maze
    DrawHermione(hermione, cellSize); // Draw Hermione

    // Draw the remaining time
    DrawRemainingTime();
    // Display remaining collectibles
    std::string collectibleText = ": " + std::to_string(CollectibleCount);
    DrawText(collectibleText.c_str(), 90, 15, 25, BLACK); // Adjust position and color as needed

    // If the game is won, display the "You Win!" message
    // if (gameWon)
    // {
    //     PlaySound(win);
    // }

    // // If the game is over, display the "Game Over" message
    // if (gameOver)
    // {
    //     PlaySound(gameover); // Play game over sound
    // }
}

void UnloadLevel2Textures()
{
    UnloadTexture(player.texture); // Unload player texture
    UnloadTexture(hermione.texture); // Unload Hermione texture
    UnloadTexture(blast.texture); // Unload blast texture
    UnloadTexture(bgTexture); // Unload background texture

    for (auto &ghost : ghosts)
    {
        UnloadTexture(ghost.texture); // Unload ghost textures
    }

    for (auto &coin : coins)
    {
        UnloadTexture(coin.texture); // Unload coin textures
    }

    UnloadSound(collide);      // Unload collision sound
    UnloadSound(attack);      // Unload attack sound
    UnloadSound(move);         // Unload move sound
    UnloadSound(coincollected); // Unload coin collection sound
    UnloadMusicStream(music);  // Unload music stream
    UnloadSound(gameover);     // Unload game over sound
    UnloadSound(win);         // Unload win sound
}