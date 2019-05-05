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

void lsr(const int nodei, const int n, int **graph){
  //Initialization
  int closestNode = 0;
  bool *visited = new bool[n+1];
  int *distances = new int[n+1], *precs = new int[n+1];
  vector<int> order;
  for(int i = 1; i <= n; ++i){
    distances[i] = graph[nodei][i];
    visited[i] = false;
    //If there's a connection to i
    if(distances[i] > 0 && distances[i] < BIG)
      precs[i] = i;
    else
      precs[i] = 0;
  }
  visited[nodei] = true;

  //Perform calculations
  for(int i = 1; i < n; ++i){
    //Visit closest unvisited node
    closestNode = shortestPath(visited, n, distances);
    //Calculate new distance to connected paths

    if(closestNode)
      visit(n, closestNode, visited, distances, precs, graph, order);
    else
      break;
  }
}

int shortestPath(bool *visited, const int n, int *distances){
  int nearest = 0, i = 1; //Arbitrary starting comparison
  for(i; i <= n; ++i)
    if(!visited[i]){
      nearest = i;
      break;
    }
  if(!nearest)
    return 0;

  for (++i; i <= n; ++i)
    if(!visited[i] && (distances[i] < distances[nearest]))
      nearest = i;

  if(visited[nearest])
    return 0;
  return nearest;
}

void visit(const int n, const int node, bool *visited, int *distances, int *precs, int **graph, vector<int> &order){
  //Loops through to find connected nodes, then compares current cost of those nodes with the
  //cost of the current path plus the connection to them.  If lower, change routing table
  visited[node] = true;
  order.push_back(node);

  //For all nodes in graph
  for(int i = 1; i <= n; ++i){
    //If directly connected
    if((graph[node][i] > 0) && (graph[node][i] < BIG))
      //If cost to node plus cost between node and i is less than current cost to i
      if((graph[node][i] + distances[node]) < distances[i]){
        //Change distance and predecessor node for i
        distances[i] = distances[node] + graph[node][i];
        precs[i] = precs[node];
    }
  }
  printRow();
  printf("Shortest path to node %d found to be %d forwarded through link to node %d\n", node, distances[node], precs[node]);
}
