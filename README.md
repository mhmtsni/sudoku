# Sudoku Solver and Generator
#### Video Demo:  (https://www.youtube.com/watch?v=a6MDT_mmJz4)
#### Description:
# Sudoku Solver and Generator

Sudoku is a classic puzzle game that has captivated players around the world for decades. The thrill of placing numbers in a 9x9 grid while adhering to specific rules can be both challenging and satisfying. To cater to enthusiasts and newcomers alike, this program, developed in C, serves as a powerful tool for generating and solving Sudoku puzzles. The following overview details the key features, development insights, and operational instructions for this comprehensive Sudoku solver and generator.

### Key Features

#### Unique Sudoku Generation
One of the standout features of this program is its ability to generate unique Sudoku puzzles. Using an advanced backtracking algorithm, the program ensures that every puzzle it creates has only one solution. This uniqueness is crucial because it guarantees that players can engage with a fair and challenging experience. Unlike many Sudoku generators that may produce multiple solutions or puzzles that are too simple, this program adheres strictly to the traditional rules of Sudoku. The result is a collection of puzzles that test the player's logic and deduction skills, providing an authentic gameplay experience.

#### Customizable Hints
Another significant aspect of the program is its customizable hints feature. When generating a Sudoku puzzle, users can specify the number of hints they want to be included in the puzzle. This feature allows players to tailor the difficulty of the puzzle according to their preference. For instance, beginners might prefer puzzles with more hints to guide them through the initial placements, while advanced players may opt for fewer hints to increase the challenge. However, it's essential to note that reducing the number of hints significantly—especially removing 56 or more—can lead to longer puzzle generation times. The program requires additional processing power to ensure that it can still find a valid solution under such conditions, making this feature not just user-friendly but also dynamically responsive to the complexity of Sudoku.

#### Backtracking Algorithm
At the heart of the solving process lies the backtracking algorithm, a fundamental method for exploring possible number placements in the grid. This algorithm works by placing a number in a cell and then moving on to the next cell. If it reaches a point where no valid number can be placed, the algorithm backtracks to the previous cell and tries the next possible number. This process continues until the puzzle is solved or deemed unsolvable. The backtracking method is particularly efficient for Sudoku because it leverages the constraints of the puzzle (where numbers must not repeat in rows, columns, and subgrids) to reduce the number of possibilities to be tested. This efficiency is a significant reason why the program can solve distinct Sudoku puzzles quickly and reliably.

#### Output Options
The ability to print generated puzzles to a file is another practical feature of the program. This function is especially valuable for educators, puzzle enthusiasts, or anyone who enjoys collecting Sudoku puzzles. By allowing users to save their creations, the program enables sharing and revisiting of puzzles over time. Teachers can create a variety of puzzles to challenge their students, while casual players can compile their favorite puzzles for later enjoyment. The output feature contributes to the program's versatility, making it suitable for various contexts, whether for casual play or educational purposes.

#### Interactive Terminal Experience
For those who appreciate a more immediate and engaging experience, the program also offers an interactive terminal option. Users can generate random Sudoku puzzles directly in the terminal, complete with customizable hints for a gameplay experience. This feature is perfect for players looking for a quick challenge without the need for extensive setup or preparation. Simply input the desired numbers to remove, and the program will generate a puzzle on the spot. This immediacy enhances user engagement and adds an element of spontaneity to the gameplay.

### Development Insights

Creating this program required careful navigation through complex recursion and algorithm design. The challenge of ensuring that each generated puzzle is both unique and solvable provided an opportunity to explore various programming concepts and techniques. It was essential to design an algorithm that could efficiently handle the rules of Sudoku while also being adaptable to different levels of difficulty. Additionally, implementing the backtracking algorithm involved a deep understanding of recursion and how to effectively manage state throughout the solving process.

The project not only demonstrates robust programming skills but also highlights the logical thinking and problem-solving required to tackle a complex challenge like Sudoku. Each successful generation or solution is a testament to the careful consideration given to the underlying logic and the elegance of the backtracking approach.

### Operational Instructions

As a command-line interface (CLI) program developed in C, users will need to use the terminal to run the application. After compiling the program, users can execute it by running `./sudoku` in the terminal to view the usage text. This usage text provides a comprehensive guide on how to interact with the program, but here’s a quick summary of the most common commands:

- **Generate Puzzles**: To generate a specified number of Sudoku puzzles and control the amount of numbers to remove (which determines the number of hints), users can run:
  ```
  ./sudoku generate [number of sudokus] [amount of numbers to remove]
  ```
  For example, to generate three puzzles with 30 hints removed, the command would be:
  ```
  ./sudoku generate 3 30
  ```

- **Solve a Distinct Sudoku**: To solve a specific Sudoku puzzle, users should format the puzzle correctly (similar to a text file) and run:
  ```
  ./sudoku solve "your sudoku goes here"
  ```
  This command allows the program to process and provide the solution based on the user's input.

- **Get a Random Sudoku**: For users wanting a quick challenge, simply entering:
  ```
  ./sudoku [amount of numbers to remove]
  ```
  will generate a random Sudoku puzzle with the specified number of hints removed.

### Final Notes

While the program is powerful and feature-rich, users should keep in mind some constraints. For instance, negative numbers or values larger than 81 for the amount of numbers to remove are invalid inputs. Additionally, attempting to generate a Sudoku puzzle with only 16 hints will not yield any puzzles, as this is below the threshold for solvability. It's recommended that users avoid excessive hint removal (56 or more) to ensure that puzzle generation remains efficient.

In summary, whether you're a casual player or a dedicated Sudoku enthusiast, this Sudoku Solver and Generator offers a robust and engaging experience. With its unique puzzle generation, customizable hints, and efficient solving capabilities, it stands out as an excellent tool for anyone looking to delve into the world of Sudoku.