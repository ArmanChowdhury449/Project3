#include "graph.h"

void Visualize(Graph* fGraph) {
    Bridges bridges("armanchowdhury", "964554411549");

    bridges.setTitle("Sample graph visualization");

    GraphAdjMatrix<string>* visGraph = fGraph->copyToBridges();

    bridges.setDataStructure(visGraph);
    bridges.visualize();
}

int main() {
    Graph* fGraph = new Graph();
    // pass csv file path as string
    fGraph->createMap("output.csv", false);

    // generates random edges between vertices, first param is # edges, second param is the seed for random generation
    fGraph->generateEdges(1000, 1);

    Visualize(fGraph);

    return 0;
}

