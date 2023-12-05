#include <vector>
#include <string>
#include <limits.h>
#include "graph.h"

#define F 9999
using namespace std;

void Dijkstra(GraphAdjMatrix<string, string>* visGraph, Graph fGraph, int start) {

    fGraph.dijkstraAlgorithm(start);
    int* dist = fGraph.getDistD();

    string vertex;

    for(int i = 0; i < F - 1; i++) {
        vertex = fGraph.getFencer(i)->name + "\n" + fGraph.getFencer(i)->club;
        if(dist[i] != 0 && dist[i] != INT_MAX) {
            visGraph->getVisualizer(vertex)->setColor("red");
        }
    }



}

void BellmanFord(GraphAdjMatrix<string, string>* visGraph, Graph fGraph, int start) {
    fGraph.bfAlgorithm(start);
    int* dist = fGraph.getDistBF();
    string vertex;

    for(int i = 0; i < F - 1; i++) {
        vertex = fGraph.getFencer(i)->name + "\n" + fGraph.getFencer(i)->club;
        if(dist[i] != 0 && dist[i] != INT_MAX) {
            visGraph->getVisualizer(vertex)->setColor("red");
        }
    }
}

void Visualize(Graph* fGraph) {
    Bridges bridges(0, "armanchowdhury", "1068005597362");

    bridges.setTitle("Sample graph visualization");

    GraphAdjMatrix<string, string> visGraph;
    fGraph->copyToBridges(&visGraph);

    bridges.setDataStructure(visGraph);

    for(int i = 0; i < 100; i++) {
        BellmanFord(&visGraph, *fGraph, i);
    }

    bridges.visualize();

}

int main() {
    Graph* fGraph = new Graph();
    // pass csv file path as string
    fGraph->createMap("C:\\Users\\armma\\CLionProjects\\DSA\\COP3530-ProgrammingQuiz4-Bridges\\dataset.csv", false);

    // generates random edges between vertices, first param is # edges, second param is the seed for random generation
    fGraph->generateEdges(300, 1);

    Visualize(fGraph);

    return 0;
}

