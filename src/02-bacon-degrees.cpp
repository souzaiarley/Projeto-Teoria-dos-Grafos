/**
 * @file 02-bacon-degrees.cpp
 * @authors Antônio Joabe Alves Morais (539029)
 *          Iarley Natã Lopes Souza (535779)
 * @brief Nesse arquivo, é implementado o algoritmo de busca
 *        em largura (BFS) para encontrar o número de Bacon
 *        de um ator, dado um grafo de filmes (arestas) e atores (vértices).
 * @version 0.1
 * @date 2023-07-03
 */

#include "header.hpp"

/* Declaração do tipo de grafo:
 * Uma hash de keys tipo T
 * e valores representados por uma lista de tipo Y
 * (nesse caso um par) */
template <typename T, typename Y>
using Graph = map<T, list<Y>>;

/* Declaração do tipo do vizinho:
 * Um par de strings. */
typedef pair<string, string> Neighbor;

/**
 * @brief Lê um arquivo CSV (Comma Separated Values) que tem
 *        como delimitador ";", dando push_backs em vizinhos
 *        no grafo, de forma não direcionada.
 * 
 * @param filename Nome e caminho do arquivo CSV
 * @param graph Grafo que irá ser gerado
 */
void readCSV(const string& filename, Graph<string, Neighbor>& graph);

/**
 * @brief Busca o grafo pelo método BFS (Breadth-First Search),
 *        uma busca em largura, que preenche (dentre outras coisas)
 *        um vetor de distâncias de todos os vértices do grafo,
 *        relativas a uma determinada origem.
 * 
 * @param graph Grafo que irá ser percorrido
 * @param start Origem da pesquisa
 */
void BFS(const Graph<string, Neighbor>& graph, const string& start);

int main() {
    Graph<string, Neighbor> graph;

    string graphFilename = "input.txt";
    string filePath = "./tests/q2/" + graphFilename;

    readCSV(filePath, graph);

    BFS(graph, "Kevin Bacon");

    return 0;
}

void readCSV(const string& filename, Graph<string, Neighbor>& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        /* Extrai os valores relavantes à montagem do grafo */
        istringstream iss(line);
        string leftName, movie, rightName;
        getline(iss, leftName, ';');
        getline(iss, movie, ';');
        getline(iss, rightName, ';');

        // Faz pares-vizinhos
        Neighbor neighbor1{rightName, movie};
        Neighbor neighbor2{leftName, movie};

        // E insere-os no grafo
        graph[leftName].push_back(neighbor1);
        graph[rightName].push_back(neighbor2);
    }

    file.close();
}

void BFS(const Graph<string, Neighbor>& graph, const string& start) {
    map<string, string> colors;
    map<string, int> distances; // Números de Bacon
    map<string, string> movies;

    /* Inicializa as cores e distâncias dos vértices */
    for (const auto& entry : graph) {
        const string& actor = entry.first;
        colors[actor] = "White";
        distances[actor] = -1;
    }

    queue<string> q; // Fila para controlar a busca
    q.push(start);
    colors[start] = "Gray"; // Inicializa a cor da origem
    distances[start] = 0; // E a distância (0)

    /* Percurso da busca */
    while (!q.empty()) {
        string current = q.front();
        q.pop();

        /* Visita os vizinhos do vértice atual */
        for (const auto& neighbor : graph.at(current)) {
            const string& neighborName = neighbor.first;
            const string& movie = neighbor.second;

            /* E atualiza os dados relevantes à busca */
            if (colors[neighborName] == "White") {
                colors[neighborName] = "Gray";
                distances[neighborName] = distances[current] + 1;
                movies[neighborName] = movie;
                q.push(neighborName);
            }
        }

        colors[current] = "Black";
    }

    /* Printa os resultados obtidos através da busca:
    Valor do vértice (ator), distância relativa à origem (Kevin Bacon)
    e valor da aresta (filme). */
    for (const auto& entry : distances) {
        const string& actorName = entry.first;
        const string& movie = movies[actorName];
        cout << "O numero de Bacon de " << actorName << " é " << distances[actorName];
        cout << " pelo filme " << movie << endl;
    }
}

