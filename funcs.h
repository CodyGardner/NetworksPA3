//Include libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib>

//Object definitions
enum Color {white, grey, black};

//Function prototypes
void printTable();
void printHeader(int starter, int n);
void printRow();
void buildGraph(std::ifstream &ifs, int **graph);
void printMatrix(const int n, int **graph);
