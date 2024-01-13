#include "header.hpp"

using Graph = vector<list<int>>;

// Kosaraju's algorithm

void Kosaraju(Graph& graph);
void DFSVisit(Graph& graph, int u, vector<string>& colors, stack<int>& stack);
void DFSVisit(Graph& graph, int u, vector<string>& colors, vector<int>& component);

void transposeGraph(Graph& graph);

void printGraph(Graph& graph);
void readGraph(const string& filename, Graph& graph);

int main() {
    Graph graph;
    readGraph("../tests/q3/grafo3.txt", graph);

    printGraph(graph);
    cout << endl;

    Kosaraju(graph);

    return 0;
}

void Kosaraju(Graph& graph) {
    vector<string> colors;
    stack<int> stack;
    vector<int> component, componentCopy;
    vector<vector<int>> SCCs;

    size_t verticesNum = graph.size();
    colors.resize(verticesNum);

    for (int i = 0; i < verticesNum; ++i)
        colors.push_back("White");
    

    // First DFS traversal
    for (int u = 0; u < verticesNum; ++u)
        if (colors[u] == "White")
            DFSVisit(graph, u, colors, stack);


    // Transpose the graph
    transposeGraph(graph);

    // Reset colors map to all vertices set to "White"
    for (auto& color : colors)
        color = "White";

    // Second DFS traversal to find strongly connected components
    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();

        if (colors[u] == "White") {
            DFSVisit(graph, u, colors, component);
            componentCopy = component;
            component.clear();
            SCCs.push_back(componentCopy);
        }
    }

    // Print the strongly connected components
    for (const auto& SCC : SCCs) {
        for (int u : SCC)
            cout << u << " ";
        cout << endl;
    }
}

void DFSVisit(Graph& graph, int u, vector<string>& colors, stack<int>& stack) {
    colors[u] = "Gray";

    for (int v : graph.at(u))
        if (colors[v] == "White")
            DFSVisit(graph, v, colors, stack);

    colors[u] = "Black";
    stack.push(u);
}

void DFSVisit(Graph& graph, int u, vector<string>& colors, vector<int>& component) {
    colors[u] = "Gray";
    component.push_back(u);

    for (int v : graph.at(u))
        if (colors[v] == "White")
            DFSVisit(graph, v, colors, component);

    colors[u] = "Black";
}

void transposeGraph(Graph& graph) {
    size_t verticesNum = graph.size();
    Graph transposedGraph(verticesNum);

    for (int u = 0; u < verticesNum; ++u) {
        for (int v : graph[u]) {
            transposedGraph[v].push_back(u);
        }
    }

    graph = move(transposedGraph);
}


void readGraph(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        exit(1);
    }

    int edgesNum, verticesNum;
    file >> verticesNum >> edgesNum;

    for (int i = 0; i < verticesNum; ++i)
        graph.push_back({});

    for (int i = 0; i < edgesNum; ++i) {
        int u, v;
        file >> u >> v;
        graph[u].push_back(v);
    }

    file.close();
}

void printGraph(Graph& graph) {
    for (int u = 0; u < graph.size(); ++u) {
        cout << u << ": ";
        for (int v : graph[u]) {
            cout << v << " ";
        }
        cout << endl;
    }
}
