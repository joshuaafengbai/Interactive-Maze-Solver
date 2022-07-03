# Interactive Maze Solver
This project deals with the representation of mazes as data structures, and basic algorithms to solve them.

Consider the maze displayed in Figure 1 below. The circles, called nodes, can be thought of as rooms. The lines, called edges, connect one room to another. Note that each node has at most four edges in the maze, corresponding to
the four directions North, South, East, and West. Solving a maze consists in reaching the finish node (L here), starting from the start node (A here).

![Screenshot 2022-07-03 at 18 06 36](https://user-images.githubusercontent.com/65661697/177050026-075f00db-e071-4097-8ad6-a3073b6fbc87.png)

This problem can be broken down into 4 major steps:
1. Build the maze
2. Traverse the maze
3. Interactively Solving the maze
4. Improvements to solving algorithm using stacks and queues

# Getting Started
Open a new terminal window or cmd if you are on windows

Change the directory to the directory in which you have your source.cpp file. For example, if it is in C:/Users/Dell/Documents, enter your command line − `$ cd 'C:/Users/Dell/Documents'`

Enter the following command to compile the source file using g++ `$ g++ -o <name-you-want-to-give> source.cpp`

Run it! Now you can run the program using − `$ ./myprogram`
