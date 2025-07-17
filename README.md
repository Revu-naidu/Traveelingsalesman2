TSP Optimization with Greedy and Heuristic Approaches
This project provides a complete solution to the Travelling Salesman Problem (TSP) using an initial greedy approach followed by a series of heuristic optimization techniques. It is designed to take a dataset of cities and distances, generate an initial route, and iteratively improve it using several methods until an optimal path is found.

What It Does
Reads input from a file provided by the user.
The input includes:

Number of cities

Number of distribution points

Number of effective points to be covered from each distribution point

Beta value and limit distance

A matrix representing road distances between cities

Generates an initial path using a greedy algorithm.

Selects nearest unvisited cities

Prioritizes distribution and delivery centers within a specified range

Applies multiple heuristic optimizations to improve the route:

2-opt: Swaps two edges to reduce path length

3-opt: Tries different segment reversals for further reduction

Optimized Swap: Selectively swaps nodes if the distance improves

i-to-j Swap: Tries swapping every pair of nodes (except depot)

Random Swap: Randomly picks nodes to swap and checks for improvement

Repeats the optimization process until the output remains unchanged for 100 iterations, indicating that the route has reached its best possible form under the given methods.

Features
Works with user-generated datasets

Handles real constraints like delivery ranges and effective delivery points

Focuses on route efficiency and delivery planning

Modular code structure with clearly separated optimization functions

Handles memory dynamically to allow large datasets

Input Format
The input file must start with:

php-template
Copy
Edit
<number_of_nodes> <distribution_points> <effective_points> <beta> <limit_distance> <range>
<distance_matrix>
Example:

Copy
Edit
6 2 2 0.5 100.0 50
0 29 20 21 16 31
29 0 15 17 28 40
20 15 0 25 34 45
21 17 25 0 18 23
16 28 34 18 0 10
31 40 45 23 10 0
Output
The program will print:

The greedy path and the number of cities it covers

The optimized path using each heuristic

Total distances after each step

Final best path after repeated improvement

Compilation & Usage
bash
Copy
Edit
gcc tsp.c -o tsp
./tsp input.txt
Replace tsp.c with your actual filename and input.txt with the path to your dataset.

Project Structure
main() — Handles file I/O and initiates processing

tsp_greedy() — Greedy path construction

twoopt(), thhreeopt(), optimizeswap(), randomswap(), itojswap() — Optimization methods

checkdistance() — Computes total route distance

printpath() — Prints the current path

Notes
The code is written in standard C and can be compiled with any modern C compiler.

Designed for educational and experimental use with real-world logistics-inspired constraints.

Can be adapted further to support coordinates, live maps, or real-time optimization
