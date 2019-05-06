//Include libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <time.h>
#include <unistd.h>

#define BIG 1073741824

//Function prototypes
void printTable(const int n, int *distances, int *precs);
void printHeader(const int starter, const int n);
void printRow(const int n, int *distances, int *precs, bool *visited, std::vector<int> order);
void buildGraph(std::ifstream &ifs, int **graph);
void printMatrix(const int n, int **graph);
void lsr(const int nodei, const int n, int **graph, const bool flag);
int shortestPath(bool *visited, const int n, int *distances);
void visit(const int n, const int node, const bool flag, bool *visited, int *distances, int *precs, int **graph, std::vector<int> &order);
std::string orderStr(const std::vector<int> order);
std::string columnStr(const int distance, const int preceding);
