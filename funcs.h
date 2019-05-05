//Include libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib>

#define BIG 1073741824

//Function prototypes
void printTable();
void printHeader(int starter, int n);
void printRow();
void buildGraph(std::ifstream &ifs, int **graph);
void printMatrix(const int n, int **graph);
void lsr(const int nodei, const int n, int **graph);
int shortestPath(bool *visited, const int n, int *distances);
void visit(const int n, const int node, bool *visited, int *distances, int *precs, int **graph, std::vector<int> &order);
