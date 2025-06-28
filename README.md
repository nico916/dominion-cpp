# Dominion C++ Implementation

![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/platform-Console-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

A console-based implementation of the deck-building card game **Dominion**, written in modern C++ as an academic project. This project focuses on applying Object-Oriented Programming principles to build a complete and playable game engine.

 
<!-- 
  TODO: Replace the URL above with a real screenshot URL. 
  You can upload an image to your GitHub repo or use a service like Imgur.
  A good screenshot would be one showing a player's turn.
-->

## Table of Contents

- [About The Project](#about-the-project)
- [Key Features](#key-features)
- [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation & Compilation](#installation--compilation)
- [Usage](#usage)
- [Technical Deep Dive](#technical-deep-dive)
  - [Object-Oriented Design](#object-oriented-design)
  - [Modern C++ & Memory Management](#modern-c--memory-management)
  - [Modular Structure](#modular-structure)
- [Challenges & Solutions](#challenges--solutions)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## About The Project

This project is a C++ implementation of the deck-building game *Dominion*. The primary goal was to apply theoretical programming concepts learned in our "Programming Tools and C++" course into a tangible, interactive application.

The game engine is built from the ground up, focusing on a robust class structure to represent the game's components (cards, players, game board) and logic. It's a 2-4 player game that runs entirely in the terminal.

## Key Features

-   **Complete Game Engine**: Manages game phases (Action, Buy, Clean-up), player decks, hands, and discard piles.
-   **2-4 Player Support**: The game can be configured to be played by two, three, or four human players.
-   **Basic AI Opponent**: Includes an option to play against an AI with a simple decision-making strategy.
-   **Save/Load Functionality**: Players can save the game state at the end of their turn and resume it later. The state is serialized to a CSV file.
-   **Customizable Card Kingdom**: Before starting a new game, players can choose the 10 Action cards that will be available in the supply, allowing for strategic variety.
-   **Styled Console Interface**: Uses ANSI escape codes to add color to the terminal output, making the game state easier to read and more visually appealing.

## Built With

-   **C++17**
-   **C++ Standard Library** (`<vector>`, `<memory>`, `<string>`, `<map>`, `<chrono>`)
-   **Compiler:** g++ (MinGW)
-   **IDE:** Code::Blocks

## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

You will need a C++ compiler that supports C++17. `g++` is recommended.
-   **On Windows:** You can use [MinGW](http://www.mingw.org/) or WSL.
-   **On macOS:** Install Xcode Command Line Tools.
-   **On Linux:** Install `build-essential` (`sudo apt-get install build-essential`).

### Installation & Compilation

1.  **Clone the repository:**
    ```sh
    git clone https://github.com/[your-github-username]/[your-repo-name].git
    cd [your-repo-name]
    ```

2.  **Compile the project:**
    A `Makefile` is the recommended way. If one is not provided, you can compile manually using the command below from the root directory:
    ```sh
    g++ -std=c++17 -I include/ -o dominion main.cpp src/*.cpp
    ```
    This command compiles all `.cpp` files in the `src` directory, includes the headers from the `include` directory, and creates an executable named `dominion`.

3.  **Run the game:**
    ```sh
    ./dominion
    ```

## Usage

Once the application is running, it will guide you through a series of prompts in the console:
1.  **Load Game**: Choose to start a new game or resume from a saved `save.csv` file.
2.  **Number of Players**: Select between 2 and 4 players.
3.  **AI Player**: Decide if one of the players should be controlled by the AI.
4.  **Card Selection**: Choose to play with the 10 standard Action cards or to manually select 10 cards for the game's supply.

During a turn, you will be prompted to take actions, buy cards, or end your turn, with your hand and available resources displayed at each step.

## Technical Deep Dive

### Object-Oriented Design

The project is heavily based on OOP principles to create a modular and extensible architecture.
-   **Inheritance & Polymorphism**: A base `Card` class defines a common interface. Derived classes like `CardTreasure`, `CardVictory`, and `CardAction` implement specific behaviors. This allows us to store all cards in a polymorphic collection (e.g., `std::vector<std::shared_ptr<Card>>`) and handle them uniformly.
-   **Encapsulation**: Classes like `Player` and `PlateauJeu` (GameBoard) encapsulate their own state and logic, exposing only necessary methods to interact with them.

### Modern C++ & Memory Management

To ensure robust and safe memory management, this project leverages modern C++ features:
-   **Smart Pointers**: `std::shared_ptr` is used extensively to manage the lifecycle of `Card` and `Player` objects. This completely avoids manual `new`/`delete` calls, prevents memory leaks, and handles shared ownership of cards between the game board, player decks, and hands. It also made safe down-casting with `std::dynamic_pointer_cast` straightforward.

### Modular Structure

The codebase is organized to separate interfaces from implementations, a standard practice in C++ development.
-   **Header Files (`.h`)**: Located in the `include/` directory, these files declare the classes and their public members, defining their "contract".
-   **Source Files (`.cpp`)**: Located in the `src/` directory, these files contain the implementation of the methods declared in the headers. This separation improves code organization and can reduce compilation times in larger projects.

## Challenges & Solutions

-   **Challenge**: Managing different card types with unique actions in a uniform way.
    -   **Solution**: Implemented a virtual `executeAction()` method in the `CardAction` class. Each specific action card (e.g., `Village`, `Smithy`) overrides this method to provide its unique logic.

-   **Challenge**: Correctly updating player state (deck, hand) without creating unintended copies.
    -   **Solution**: Using `std::shared_ptr<Joueur>` ensured that all parts of the program were referencing the exact same player object, not a copy, making state management consistent and reliable.

## License

Distributed under the MIT License. See `LICENSE` file for more information.
