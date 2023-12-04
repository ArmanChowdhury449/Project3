#ifndef PROGRAMMINGQUIZ4_GRAPH_H
#define PROGRAMMINGQUIZ4_GRAPH_H

#include <map>
#include <fstream>
#include <sstream>
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
    void createMap(string filename);
    void generateEdges(int numEdges, int seed);
    GraphAdjMatrix<string>* copyToBridges();
    void dijkstraAlgorithm(int start);
    void bfAlgorithm(int start);

};

#endif //PROGRAMMINGQUIZ4_GRAPH_H
