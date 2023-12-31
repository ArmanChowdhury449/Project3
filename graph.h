#ifndef P3TEST_GRAPH_H
#define P3TEST_GRAPH_H

#include <map>
#include <iostream>
#include "fencer.h"
#include "libraries/bridges/include/Bridges.h"
#include "libraries/bridges/include/GraphAdjMatrix.h"

using namespace std;
using namespace bridges;

class Graph {
private:
    vector<vector<int>> adjMatrix;
    map <int, Fencer*> fencers;
    int minEdge(int dist[], bool visited[]);
    void addEdge(int to, int from, int weight);
    int* distD;
    int* prevD;
    int* distBF;
    int* prevBF;
    int edges;

public:
    Graph();
    void createMap(string filename, bool trackerData);
    void generateEdges(int numEdges, int seed);
    void copyToBridges(GraphAdjMatrix<string, string>* graph);
    void dijkstraAlgorithm(int start);
    void bfAlgorithm(int start);
    void printMap();
    void printAdjMatrix();
    int* getDistD();
    int* getPrevD();
    int* getDistBF();
    int* getPrevBF();
    Fencer* getFencer(int key);
    int getNumVertices();
};

#endif //P3TEST_GRAPH_H
