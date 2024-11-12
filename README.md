# Wizardry - A Multi-Level Interactive Game

**Wizardry** is a captivating multi-level game developed using Rylib and C++. The game offers a rich mix of item collection, maze navigation and riddle-solving mechanics. Each level introduces new challenges, engaging the player with innovative game mechanics.

## Table of Contents
1. [About](#about)
2. [Gameplay](#gameplay)
3. [Features](#features)
4. [Installation](#installation)
5. [How to Play](#how-to-play)
6. [Contributors](#contributors)


---

## About

**Wizardry** is designed with three unique levels that introduce a variety of mechanics:

- **Level 1**: The player (Harry) must collect snitches while avoiding falling bludgers. If a bludger hits Harry, he freezes temporarily.
- **Level 2**: In this level, the player uses the snitch count from Level 1 to remove ghosts from the maze and collects coins to increase the score. The goal is to reach Hermione at the end of the maze.
- **Level 3**: At the end of the maze, players face a riddle. Solving the riddle marks the completion of the game.

Through this project, we had the opportunity to apply our understanding of  C++ programming, and game design principles, while using Raylib, a simple yet powerful game development library.

---

## Gameplay

- **Level 1**:  
  The player controls Harry, who must collect snitches which appears one by one throughout the level. However, falling bludgers threaten the player. If a bludger touches Harry, he freezes temporarily and loses some progress. The level ends when Harry collects a certain number of snitches in the given time.

- **Level 2**:  
  The snitches collected in Level 1 are used as a resource to remove ghosts that sets player to initial position when collided. The player must navigate a maze while collecting coins to increase their score. The goal is to reach Hermione, who marks the end of the maze and completion of the level.

- **Level 3**:  
  At the end of the maze, a riddle is presented to the player. Solving the riddle will lead to a victory screen and the completion of the game.

---

## Features

- **Multi-level Gameplay**:  
  The game consists of three levels, each with new gameplay mechanics.
  
- **Item Collection and Score System**:  
  Players collect snitches in Level 1, which are used in Level 2 to remove ghosts. Coins collected in Level 2 contribute to the player’s score.

- **Ghosts and Hazards**:  
  Ghosts in Level 2 block the player's path. Bludgers in Level 1 present a hazard that can freeze the player when hit.

- **Puzzle Solving**:  
  A riddle at the end of Level 3 challenges the player’s problem-solving skills.

- **Smooth User Interface**:  
  Simple, intuitive controls and an engaging UI enhance the gameplay experience.

- **Graphics and Sound**:  
  Custom textures for characters and objects along with background music and sound effects that enhance immersion.

---
## Installation
1. **Install Dependencies**  
   Before running the game, make sure you have Raylib installed. You can follow the installation instructions from the [Raylib website](https://www.raylib.com) or use a package manager like `vcpkg` (on Windows) or `brew` (on macOS).
   <p align="center">
🎥 <a href="https://www.youtube.com/watch?v=PaAcVk5jUd8">Video Tutorial on YouTube</a>
</p>


3. **Build the Game**  
   After downloading or cloning the repository, you can compile the game by running the appropriate build command in your IDE or terminal:

   - **For Visual Studio**:  
     Open the project and press `F5` to compile and run the game.
   
   - **For Code::Blocks**:  
     Open the project, press `F5` to compile and run the game.
   
   - **For CLion**:  
     Open the project and press `Shift + F10` (or `F5` depending on your configuration) to compile and run the game.

   - **For VS Code with Makefile**:
     Ensure the `Makefile` is set up correctly (see the [Building the Game](#building-the-game) section for more details). Then press `F5` to run the game.

4. **Run the Game**  
   Once compiled, run the game by executing the generated binary or by pressing `F5` in your IDE. The game will start, and you can begin playing!

## How to Play

1. Start the game by executing the compiled file.
2. **Level 1**: Use the arrow keys or WSAD keys (shift + the keys: for faster speed) to navigate Harry and collect as many snitches as possible. Avoid falling bludgers.
3. **Level 2**: Continue collecting coins to increase your score and get more hints in the riddle asked in Level 3. Use the snitches collected in Level 1 to remove ghosts and navigate the maze.
4. **Level 3**: Solve the riddle presented at the end of the maze to win the game.

## Contributors

- [Shristi Pokhrel](https://github.com/Shri-29)
- [Shruti Maharjan](https://github.com/shruti-1007)
- [Swarnima Khadka](https://github.com/Swarnima-Khadka)
- [Yurisha Bajracharya](https://github.com/yurisha-bajracharya)
