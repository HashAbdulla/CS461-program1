# CS461-program1
# Hashim Abdulla
## Route-finding using search algorithms program

This C++ program implements 5 search algorithms:  
**brute-force (blind search)**  
**breadth-first search**  
**depth-first search**  
**iterative deepening depth-first search (ID-DFS)**  
**best-first search**  
and A* Search

in order to find a route between two towns.   
Given a dataset of towns and their adjacencies, the program allows users to select a starting and ending town, choose a search method, and view the computed route along with execution time and total distance.  

I used the LLM **"DeepSeek"** in order to generate the C++ code, and the "assistant" to make minor changes and fixes in the code. The "assistant" is an LLM which is baked right into my chosen IDE (replit) and can help with making quick fixes to the code.  

## Prompts used  
**DEEPSEEK**

"Write a menu-driven route-finding program in C++ that allows the user to search for a path between two towns using different search algorithms. The program should loop until the user decides to quit. Follow these requirements:  
Read input from an csv file and a txt file:  
an csv file containing a list of towns with their latitude and longitude.  
a text file containing a list of adjacent town pairs (ensure bidirectional connections). (Names have been tweaked so that city names consisting of more than one word have an  
underscore rather than a space between the words (for instance South_Haven rather than South Haven), to simplify input.)  
Store the data using appropriate data structures (e.g., dictionaries, adjacency lists).  
Provide a menu system where the user can:  
Enter a starting and ending town (validate input).  
Choose a search algorithm:  
Brute-force (blind search)  
Breadth-First Search (BFS)  
Depth-First Search (DFS)  
Iterative Deepening DFS (ID-DFS)  
Best-First Search  
A Search (uses heuristic based on latitude/longitude distance)*  
Run the selected search and display:  
The path found.  
Total distance traveled.  
Execution time.  
again, MAKE SURE the program loops continuously until the user chooses to exit."  


**ASSISTANT**  
"whenever I put in an invalid input such as "rago" given the 7 options , the program bugs out and keeps showing the options over and over again very fast without giving me a chance to react , can you fix that"



