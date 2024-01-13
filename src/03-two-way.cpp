/**
 * @file 03-two-way.cpp
 * @authors Antônio Joabe Alves Morais (539029)
 *          Iarley Natã Lopes Souza (535779)
 * @brief Nesta solução, direcionamos todas as arestas de um grafo
 *        não direcionado, de forma que o resultado seja um grafo
 *        fortemente conexo. 
 * @version 0.1
 * @date 2023-07-04
 */

#include "header.hpp"

using Graph = vector<list<int>>;

/**
 * @brief Imprime todas as arestas de um grafo
 * 
 * @param graph Grafo a ser impresso
 */
void printEdges(Graph& graph);
/**
 * @brief Lê um arquivo de nome filename e monta
 *        um grafo com base nos dados que o arquivo
 *        providencia.
 * 
 * @param filename Nome e caminho do arquivo
 * @param graph Grafo que vai ser gerado
 */
void readGraph(const string& filename, Graph& graph);

/**
 * @brief Faz uma DFS modificada no grafo, de forma que
 *        além do executar o algoritmo normal, a função também
 *        encontra as arestas que são pontes.
 * 
 * @param graph Grafo a ser analisado
 * @param bridges Lista de arestas que são pontes
 */
void bridgesDFS(Graph& graph, vector<pair<int, int>>& bridges);

/**
 * @brief Função auxiliar da DFS, que executa o algoritmo
 *        normal e encontra as arestas que são pontes.
 * 
 * @param graph Grafo a ser analisado
 * @param u Vértice atual
 * @param colors Cores de todos os vértices do grafo
 * @param parents Pais de todos os vértices do grafo
 * @param discoveryTimes Tempos de descoberta de todos os vértices do grafo
 * @param lowTimes Menor tempo de descoberta de todos os vértices do grafo
 * @param time Tempo atual
 * @param bridges Lista de arestas que são pontes
 */
void bridgesDFSVisit(Graph& graph, int u, vector<string>& colors, 
              vector<int>& parents, vector<int>& discoveryTimes, 
              vector<int>& lowTimes, int& time, vector<pair<int, int>>& bridges);

/**
 * @brief Faz uma DFS modificada no grafo,
 *        fortemente direcionando todas as arestas
 *        que não são pontes.
 * 
 * @param graph Grafo a ser analisado
 */

void directedDFS(Graph& graph);

/**
 * @brief Função auxiliar da DFS, que executa o algoritmo
 *        normal e fortemente direcionando todas as arestas
 *        que não são pontes.
 * 
 * @param graph Grafo a ser analisado
 * @param u Vértice atual
 * @param colors Cores de todos os vértices do grafo
 * @param discoveryTimes Tempos de descoberta de todos os vértices do grafo
 * @param time Tempo atual
 */
void directedDFSVisit(Graph& graph, int u, vector<string>& colors, vector<int>& discoveryTimes, int& time);

/**
 * @brief Transpõe um grafo, ou seja, inverte a direção de todas as arestas
 * 
 * @param graph Grafo a ser transposto
 */
void transposeGraph(Graph& graph);

int main() {
    Graph graph;
    vector<pair<int, int>> bridges;

    string graphFilename = "grafo3.txt";
    string filePath = "./tests/q3/" + graphFilename;

    readGraph(filePath, graph);

    bridgesDFS(graph, bridges);
    directedDFS(graph);

    // Adiciona as arestas que são pontes novamente
    for (auto [u, v] : bridges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Ordena as listas de adjacência
    for (auto& list : graph) {
        list.sort();
    }

    printEdges(graph);

    return 0;
}

void bridgesDFS(Graph& graph, vector<pair<int, int>>& bridges) {
    // Inicializa as variáveis referentes à DFS
    int time { 0 };
    size_t verticesNum = graph.size();
    vector<string> colors;
    vector<int> discoveryTimes(verticesNum), 
    lowTimes(verticesNum), 
    parents(verticesNum);

    colors.resize(verticesNum, "White");
    parents[0] = 0;

    // Realiza a DFS
    for (size_t u = 0; u < verticesNum; ++u)
        if (colors[u] == "White")
            bridgesDFSVisit(graph, u, colors, parents, discoveryTimes, lowTimes, time, bridges);

    // Remove todas as arestas que são pontes
    for (auto [u, v] : bridges) {
        graph[u].remove(v);
        graph[v].remove(u);
    }
}

void bridgesDFSVisit(Graph& graph, int u, vector<string>& colors, 
              vector<int>& parents, vector<int>& discoveryTimes, 
              vector<int>& lowTimes, int& time, vector<pair<int, int>>& bridges) {
    colors[u] = "Gray";
    // Incrementa o tempo 
    time += 1;
    // e atribui o tempo de descoberta e o menor tempo de descoberta
    lowTimes[u] = discoveryTimes[u] = time;

    for (int v : graph.at(u)) {
        if (colors[v] == "White") {
            parents[v] = u;
            bridgesDFSVisit(graph, v, colors, parents, discoveryTimes, lowTimes, time, bridges);
            // Atualiza o menor tempo de descoberta
            if (lowTimes[v] < lowTimes[u])
                lowTimes[u] = lowTimes[v];
            // Se o menor tempo de descoberta de v for maior que o tempo de descoberta de u,
            // então a aresta (u, v) é uma ponte.
            if (discoveryTimes[u] < lowTimes[v]) {
                bridges.push_back({u, v});
            }
        }
    }

    colors[u] = "Black";

    /* Atualiza o menor tempo de descoberta de u
     * com base nos menores tempos de descoberta
     * de seus vértices adjacentes (exceto do pai) */
    for (int v : graph.at(u)) {
        if (v != parents[u]) {
            lowTimes[u] = min(lowTimes[u], lowTimes[v]);
        }
    }
}

void directedDFS(Graph& graph) {
    // Inicializa as variáveis referentes à DFS
    int time { 0 };
    size_t verticesNum = graph.size();
    vector<string> colors;
    vector<int> discoveryTimes(verticesNum);

    colors.resize(verticesNum, "White");

    // Realiza a DFS
    for (size_t u = 0; u < verticesNum; ++u) {
        if (colors[u] == "White") {
            directedDFSVisit(graph, u, colors, discoveryTimes, time);
        }
    }
}

void directedDFSVisit(Graph& graph, int u, vector<string>& colors, vector<int>& discoveryTimes, int& time) {
    colors[u] = "Gray";
    time += 1;
    discoveryTimes[u] = time;

    for (int v : graph.at(u)) {
        if (colors[v] == "White") {
            // Remove a aresta (v, u) antes de visitar v
            // a fim de eliminar a mão dupla
            graph[v].remove(u);
            directedDFSVisit(graph, v, colors, discoveryTimes, time);
        }

        // Remove a mão dupla do vizinho v,
        // já descoberto, para u, se o tempo de descoberta
        // de u for maior que o de v
        if (colors[v] != "White") {
            if (discoveryTimes[u] > discoveryTimes[v]) {
                graph[v].remove(u);
            }
        }
    }

    colors[u] = "Black";
}

void readGraph(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        exit(1);
    }

    int edgesNum, verticesNum;
    file >> verticesNum >> edgesNum;

    graph.resize(verticesNum);

    for (int i = 0; i < edgesNum; ++i) {
        int u, v;
        file >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    file.close();
}

void printEdges(Graph& graph) {
    for (size_t u = 0; u < graph.size(); ++u) {
        for (int v : graph[u])
            cout << "(" << u << "," << v << ")" << endl;
    }
    cout << "#" << endl;
}
