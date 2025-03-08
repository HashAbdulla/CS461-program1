#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <limits>

using namespace std;
using namespace std::chrono;

// Structure to store town information
struct Town {
    string name;
    double latitude;
    double longitude;
};

// Structure to store graph edges
struct Edge {
    string dest;
    double distance;
};

// Global variables
unordered_map<string, Town> towns; // Dictionary to store towns
unordered_map<string, vector<Edge>> adjacencyList; // Adjacency list for the graph

// Function to calculate Euclidean distance between two towns
double calculateDistance(const Town& a, const Town& b) {
    double latDiff = a.latitude - b.latitude;
    double lonDiff = a.longitude - b.longitude;
    return sqrt(latDiff * latDiff + lonDiff * lonDiff);
}

// Function to load towns from CSV file
void loadTowns(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open towns file." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, lat, lon;
        getline(ss, name, ',');
        getline(ss, lat, ',');
        getline(ss, lon, ',');

        Town town = {name, stod(lat), stod(lon)};
        towns[name] = town;
    }
    file.close();
}

// Function to load adjacency data from text file
void loadAdjacency(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open adjacency file." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string town1, town2;
        ss >> town1 >> town2;

        // Add bidirectional edges
        double distance = calculateDistance(towns[town1], towns[town2]);
        adjacencyList[town1].push_back({town2, distance});
        adjacencyList[town2].push_back({town1, distance});
    }
    file.close();
}

// Brute-force search (blind search)
vector<string> bruteForceSearch(const string& start, const string& end) {
    // Not implemented for simplicity
    return {};
}

// Breadth-First Search (BFS)
vector<string> bfsSearch(const string& start, const string& end) {
    queue<vector<string>> paths;
    paths.push({start});
    unordered_map<string, bool> visited;

    while (!paths.empty()) {
        vector<string> currentPath = paths.front();
        paths.pop();
        string lastTown = currentPath.back();

        if (lastTown == end) {
            return currentPath;
        }

        if (!visited[lastTown]) {
            visited[lastTown] = true;
            for (const Edge& edge : adjacencyList[lastTown]) {
                vector<string> newPath = currentPath;
                newPath.push_back(edge.dest);
                paths.push(newPath);
            }
        }
    }
    return {};
}

// Depth-First Search (DFS)
vector<string> dfsSearch(const string& start, const string& end) {
    stack<vector<string>> paths;
    paths.push({start});
    unordered_map<string, bool> visited;

    while (!paths.empty()) {
        vector<string> currentPath = paths.top();
        paths.pop();
        string lastTown = currentPath.back();

        if (lastTown == end) {
            return currentPath;
        }

        if (!visited[lastTown]) {
            visited[lastTown] = true;
            for (const Edge& edge : adjacencyList[lastTown]) {
                vector<string> newPath = currentPath;
                newPath.push_back(edge.dest);
                paths.push(newPath);
            }
        }
    }
    return {};
}

// Iterative Deepening DFS (ID-DFS)
vector<string> idDfsSearch(const string& start, const string& end) {
    int depth = 0;
    while (true) {
        stack<vector<string>> paths;
        paths.push({start});
        unordered_map<string, bool> visited;

        while (!paths.empty()) {
            vector<string> currentPath = paths.top();
            paths.pop();
            string lastTown = currentPath.back();

            if (lastTown == end) {
                return currentPath;
            }

            if (currentPath.size() <= depth && !visited[lastTown]) {
                visited[lastTown] = true;
                for (const Edge& edge : adjacencyList[lastTown]) {
                    vector<string> newPath = currentPath;
                    newPath.push_back(edge.dest);
                    paths.push(newPath);
                }
            }
        }
        depth++;
    }
    return {};
}

// Best-First Search
vector<string> bestFirstSearch(const string& start, const string& end) {
    auto heuristic = [&](const string& town) {
        return calculateDistance(towns[town], towns[end]);
    };

    priority_queue<pair<double, vector<string>>, vector<pair<double, vector<string>>>, greater<>> pq;
    pq.push({heuristic(start), {start}});
    unordered_map<string, bool> visited;

    while (!pq.empty()) {
        auto [_, currentPath] = pq.top();
        pq.pop();
        string lastTown = currentPath.back();

        if (lastTown == end) {
            return currentPath;
        }

        if (!visited[lastTown]) {
            visited[lastTown] = true;
            for (const Edge& edge : adjacencyList[lastTown]) {
                vector<string> newPath = currentPath;
                newPath.push_back(edge.dest);
                pq.push({heuristic(edge.dest), newPath});
            }
        }
    }
    return {};
}

// A* Search
vector<string> aStarSearch(const string& start, const string& end) {
    auto heuristic = [&](const string& town) {
        return calculateDistance(towns[town], towns[end]);
    };

    priority_queue<pair<double, vector<string>>, vector<pair<double, vector<string>>>, greater<>> pq;
    pq.push({heuristic(start), {start}});
    unordered_map<string, double> costSoFar;
    costSoFar[start] = 0;

    while (!pq.empty()) {
        auto [_, currentPath] = pq.top();
        pq.pop();
        string lastTown = currentPath.back();

        if (lastTown == end) {
            return currentPath;
        }

        for (const Edge& edge : adjacencyList[lastTown]) {
            double newCost = costSoFar[lastTown] + edge.distance;
            if (!costSoFar.count(edge.dest) || newCost < costSoFar[edge.dest]) {
                costSoFar[edge.dest] = newCost;
                vector<string> newPath = currentPath;
                newPath.push_back(edge.dest);
                pq.push({newCost + heuristic(edge.dest), newPath});
            }
        }
    }
    return {};
}

// Function to display the menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Brute-force search\n";
    cout << "2. Breadth-First Search (BFS)\n";
    cout << "3. Depth-First Search (DFS)\n";
    cout << "4. Iterative Deepening DFS (ID-DFS)\n";
    cout << "5. Best-First Search\n";
    cout << "6. A* Search\n";
    cout << "7. Exit\n";
}

// Function to validate town names
bool validateTown(const string& town) {
    return towns.find(town) != towns.end();
}

// Function to calculate total distance of a path
double calculateTotalDistance(const vector<string>& path) {
    double totalDistance = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        for (const Edge& edge : adjacencyList[path[i]]) {
            if (edge.dest == path[i + 1]) {
                totalDistance += edge.distance;
                break;
            }
        }
    }
    return totalDistance;
}

int main() {
    // Load data
    loadTowns("coordinates.csv");
    loadAdjacency("Adjacencies.txt");

    while (true) {
        displayMenu();
        int choice;
        cout << "Enter your choice: ";
        
        // Check if input is a valid integer
        if (!(cin >> choice)) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }
        
        // Check if choice is in valid range
        if (choice < 1 || choice > 7) {
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
            continue;
        }

        if (choice == 7) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        string start, end;
        cout << "Enter starting town: ";
        cin >> start;
        cout << "Enter ending town: ";
        cin >> end;

        if (!validateTown(start) || !validateTown(end)) {
            cout << "Invalid town name(s). Please try again.\n";
            continue;
        }

        vector<string> path;
        auto startTime = high_resolution_clock::now();

        switch (choice) {
            case 1:
                path = bruteForceSearch(start, end);
                break;
            case 2:
                path = bfsSearch(start, end);
                break;
            case 3:
                path = dfsSearch(start, end);
                break;
            case 4:
                path = idDfsSearch(start, end);
                break;
            case 5:
                path = bestFirstSearch(start, end);
                break;
            case 6:
                path = aStarSearch(start, end);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                continue;
        }

        auto endTime = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(endTime - startTime);

        if (path.empty()) {
            cout << "No path found.\n";
        } else {
            cout << "Path found: ";
            for (const string& town : path) {
                cout << town << " -> ";
            }
            cout << "\nTotal distance: " << calculateTotalDistance(path) << " units\n";
        }
        cout << "Execution time: " << duration.count() << " ms\n";
    }

    return 0;
}
