/**
 * @file 01-vertex-coloring.cpp
 * @authors Antônio Joabe Alves Morais (539029)
 *          Iarley Natã Lopes Souza (535779)
 * @brief Nesta solução, verificamos se um grafo é bipartido, 
 *        verificando se o mesmo pode ser colorido com 2 cores 
 * @version 0.1
 * @date 2023-07-03
 * 
 */

#include "header.hpp"

/* Declaração do tipo do grafo:
 * hash de key int, valores representados 
 * por uma lista de ints */
using Graph = map<int, list<int>>;

/**
 * @brief Pinta vértices de um grafo com 1 de 2 cores,
 *        (vermelho e azul) de forma alternada e se em
 *        algum momento o algoritmo detectar uma aresta
 *        onde 2 vértices tem cores iguais, retorna false
 *        (o grafo não pode ter bipartido), senão retorna
 *        true (pode ser bipartido).
 * 
 * @param graph O grafo a ser analisado
 * @param colors As cores de todos os vértices de um grafo
 * @return true - Se o grafo for bipartido \\
 * @return false - Se o grafo não for (tiver uma aresta com 2 cores iguais)
 */
bool isBipartite(const Graph& graph, vector<char>& colors);

/**
 * @brief Adiciona uma aresta no grafo,
 *        ligando um vértice v a u,
 *        de forma não direcionada.
 * 
 * @param graph Grafo onde vai ser adicionado a aresta
 * @param u Vértice u
 * @param v Vértice v
 */
void addEdge(Graph& graph, int u, int v);

/**
 * @brief Lê um arquivo de nome filename e monta
 *        múltiplos grafos com base nos dados
 *        que o arquivo providencia.
 * 
 * @param filename Nome e caminho do arquivo
 * @param graphs Lista de grafos que vão ser gerados
 * @param numVertices Numeros de vértices de cada grafo
 * @return true - Se o arquivo puder ser lido \\
 * @return false - Se ocorrer algum erro na leitura
 */
bool readGraphs(const string& filename, vector<Graph>& graphs, vector<int>& numVertices);

int main() {
    vector<Graph> graphs; 
    vector<int> numVertices;

    /* Nome do arquivo que contém os grafos */
    string graphFilename = "snarks_24_vertices.txt";
    /* Nome da pasta que contém os grafos: (SIM / NAO)*/
    string YorN = "NAO";
    /* Caminho completo do arquivo */
    string filePath = "./tests/q1/" + YorN + "/" + graphFilename;

    /* Verifica se o arquivo pode ser lido e o lê, se for possível */
    if (!readGraphs(filePath, graphs, numVertices)) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    /* Roda o algoritmo para os vários grafos lidos anteriormente */
    for (size_t i = 0; i < graphs.size(); ++i) {
        const Graph& graph = graphs[i];
        int vertices = numVertices[i];

        // Inicializa as cores dos vértices de um grafo,
        // pintando-os de branco
        vector<char> colors(vertices, 'w');
        // E pinta o primeiro vértice de vermelho
        colors[0] = 'r';

        cout << "Graph " << i + 1 << ": ";
        // Printa o resultado da verificação da bipartibilidade
        cout << (isBipartite(graph, colors) ? "SIM" : "NAO") << endl;
    }

    return 0;
}

bool isBipartite(const Graph& graph, vector<char>& colors) {
    int numVertices = colors.size();

    for (int i = 0; i < numVertices; ++i) {
        /* Evita que um vértice isolado permaneça branco,
         * mesmo depois da finalização do algoritmo */
        if (colors[i] == 'w') {
            colors[i] = 'r';
        }

        for (int neighbor : graph.at(i)) {
            /* Se o vizinho for branco, */
            if (colors[neighbor] == 'w') {
                // Pinta o mesmo com a cor contrária ao vértice atual
                colors[neighbor] = (colors[i] == 'r') ? 'b' : 'r';
            } else { // Senão
                /* Retorna false se a cor do vizinho for igual
                 * (grafo não é bipartido) */
                if (colors[neighbor] == colors[i]) {
                    return false;
                }
            }
        }
    }

    return true;
}

void addEdge(Graph& graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

bool readGraphs(const string& filename, vector<Graph>& graphs, vector<int>& numVertices) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    int vertices, edges;
    while (file >> vertices >> edges) {
        Graph graph;
        for (int i = 0; i < edges; ++i) {
            int u, v;
            file >> u >> v;
            addEdge(graph, u, v);
        }

        graphs.push_back(graph);
        numVertices.push_back(vertices);
    }

    file.close();

    return true;
}
