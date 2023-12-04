#include "graph.h"

void Visualize(Graph* fGraph) {
    Bridges bridges(0, "armanchowdhury", "1068005597362");

    bridges.setTitle("Sample graph visualization");

    GraphAdjMatrix<string, string> visGraph;
    fGraph->copyToBridges(&visGraph);

    visGraph.addVertex("Arman_Chowdhury", "");
    visGraph.addVertex("Ru_Esteban", "");
    visGraph.addEdge("Arman_Chowdhury", "Ru_Esteban", 1);

    bridges.setDataStructure(visGraph);
    bridges.visualize();
}

int main() {
    Graph* fGraph = new Graph();
    // pass csv file path as string
    fGraph->createMap("C:\\Users\\armma\\CLionProjects\\DSA\\COP3530-ProgrammingQuiz4-Bridges\\dataset.csv", false);

    // generates random edges between vertices, first param is # edges, second param is the seed for random generation
    fGraph->generateEdges(1500, 1);

    // fGraph->printMap();
    // fGraph->printAdjMatrix();


    Visualize(fGraph);

    return 0;
}

