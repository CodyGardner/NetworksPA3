#include "funcs.h"

using namespace std;

//Function definitions
void printTable(){

}

void printHeader(int starter, int n){
  //Prints the header of the chart, given the number of nodes and the starting node

  printf("----------------------------------------------------------------------------------------------------------\n");
  printf("%-8s%-20s", "Step", "N\'");

  for(int i = 1; i < n; ++i)
    if(i != starter)
      printf("%-8d", i);

  printf("\n----------------------------------------------------------------------------------------------------------\n");
}

void printRow(){
}

void buildGraph(ifstream &ifs, int **graph){
  //Extracts data from input file and builds graph
  int x = 0, y = 0, cost = 0;
  while(ifs >> x >> y >> cost)
    graph[x][y] = cost;
}

void printMatrix(const int n, int **graph){
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= n; ++j)
      printf("%-15d", graph[i][j]);
    printf("\n");
  }
}
