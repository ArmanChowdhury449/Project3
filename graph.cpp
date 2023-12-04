#include <string>
#include <vector>
#include <stdlib.h>
#include "graph.h"

#define F 1000

// finds next min weighted edge that hasn't been visited for dijkstra algorithm
int Graph::minEdge(int dist[], bool visited[])
{
    int min = INT_MAX;
    int index;
    for (int i = 0; i < F; i++) {
        if (visited[i] == false && dist[i] <= min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

Graph::Graph()
{
    adjMatrix = vector<vector<int>>(F, vector<int>(F, 0));

    distD = new int[F];
    prevD = new int[F];
    distBF = new int[F];
    prevBF = new int[F];
    edges = 0;
    for (int i = 0; i < F; i++) {
        distD[i] = INT_MAX;
        prevD[i] = 0;
        prevBF[i] = 0;
        distBF[i] = INT_MAX;
        for (int j = 0; j < F; j++) {
            adjMatrix[i][j] = 0;
        }
    }
}

// Insert new fencer into the map using data from CSV file
void Graph::createMap(string filename, bool trackerData)
{
    fstream file;
    file.open(filename, ios::in);

    if (!file.is_open()) {
        // Handle file opening failure
        cout << "Error opening file." << endl;
        return;
    }

    vector<string> row;
    string line, item, temp;
    int num = 0;
    int emptyCounter = 0;

    bool emptyRow = false;

    while (getline(file, line)) {
   		if (trackerData) {
			if (emptyRow && emptyCounter > 3) {
				row.clear();
				getline(file, line);
				stringstream s(line);
				// push each new item into vector
				while (std::getline(s, item, ',')) {
					row.push_back(item);
				}
				fencers[num] = new Fencer(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10]);
				num++;
				emptyRow = !emptyRow;
			}
			else {
				emptyRow = !emptyRow;
				emptyCounter++;
			}
		}
		else {
			row.clear();
			getline(file, line);
			stringstream s(line);
			// push each new item into vector
			while (std::getline(s, item, ',')) {
				row.push_back(item);
			}
			fencers[num] = new Fencer(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10]);
			num++;
		}
    }

    file.close();
}

void Graph::generateEdges(int numEdges, int seed)
{
    srand(seed);
    int randRow;
    int randCol;
    int randWeight;
    for (int i = 0; i < numEdges; i++) {
        // generate random nums for row, column, and weight
        // row and column are bound from 0 -> F-1
        // weight is bound from 1 -> 15;
        randRow = rand() % F;
        randCol = rand() % F;
        randWeight = 1 + (rand() % 15);

        addEdge(randRow, randCol, randWeight);
    }
}

// adds weighted edge to adjacency matrix
void Graph::addEdge(int to, int from, int weight)
{
    adjMatrix[from][to] = weight;
    edges++;
}

// prints the map of fencers: "int: name"
GraphAdjMatrix<string>* Graph::copyToBridges() {
    GraphAdjMatrix<string> out;

    // adjMatrix edges in bridges get added like so --> addEdge(from, to, weight)

    int weight = 0;
    Fencer* from;
    Fencer* to;

    for(int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[0].size(); j++) {

            weight = adjMatrix[i][j];

            if(weight == 0) {
                continue;
            }

            from = fencers[i];
            to = fencers[j];

            out.addVertex(from->name);
            out.addVertex(to->name);
            out.addEdge(from->name, to->name, weight);

        }
    }

}

// Goes through map and find shortest dist paths to each node with dijkstra's algorithm
// result stored in private distD and prevD variable
void Graph::dijkstraAlgorithm(int start)
{
    // initialize vars
    bool visit[F];

    for (int i = 0; i < F; i++) {
        visit[i] = false;
    }

    distD[start] = 0;

    // algorithm
    for (int i = 0; i < F - 1; i++) {
        int vert = minEdge(distD, visit);
        visit[vert] = true;
        for (int t = 0; t < F; t++) {
            if (!visit[t] &&
                adjMatrix[vert][t] &&
                distD[vert] != INT_MAX &&
                distD[vert] + adjMatrix[vert][t] < distD[t])
            {
                distD[t] = distD[vert] + adjMatrix[vert][t];
                prevD[t] = vert;
            }
        }
    }
    return;
}

// Goes through map and find shortest dist paths to each node with the Bellman Ford algorithm
// result stored in private distBF and prevBF variable
void Graph::bfAlgorithm(int start)
{
    distBF[start] = 0;

    for (int h = 0; h < F - 1; h++) {
        for (int i = 0; i < F; i++) {
            for (int j = 0; j < F; j++) {
                if (distBF[i] != INT_MAX &&
                    adjMatrix[i][j] &&
                    distBF[j] > (distBF[i] + adjMatrix[i][j]))
                {
                    distBF[j] = distBF[i] + adjMatrix[i][j];
                    prevBF[j] = i;
                }
            }
        }
    }
}
