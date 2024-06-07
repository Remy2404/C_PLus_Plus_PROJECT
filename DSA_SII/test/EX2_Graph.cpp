#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
    int V; // Number of vertices
    list<int> *adj; // Pointer to an array containing adjacency lists

public:
    Graph(int V); // Constructor
    void addEdge(int v, int w); // Function to add an edge to the graph
    void printGraph(); // Function to print the adjacency list
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::printGraph() {
    for (int i = 0; i < V; i++) {
        cout << "\n Adjacency list of vertex " << i << "\n head ";
        for (auto x : adj[i])
            cout << "-> " << x;
        cout << "\n";
    }
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    cout << "Adjacency List of the given graph\n";
    g.printGraph();

    return 0;
}