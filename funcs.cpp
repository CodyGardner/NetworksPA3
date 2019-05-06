#include "funcs.h"

using namespace std;

//Function definitions
void printTable(const int n, int *distances, int *precs){
  printf("\n\n");
  printf("%-12s|%10s\n", "Destination", "Link");
  printf("_________________________\n");
  for(int i = 1; i <= n; ++i)
    if(distances[i])
      printf("%-7d%5s|%6d,%-5d\n", i, "", distances[i], precs[i]);
}

void printHeader(const int starter, const int n){
  //Prints the header of the chart, given the number of nodes and the starting node

  printf("----------------------------------------------------------------------------------------------------------\n");
  printf("%-8s%-20s", "Step", "N\'");

  for(int i = 1; i <= n; ++i)
    if(i != starter)
      printf("%-8d", i);

  printf("\n----------------------------------------------------------------------------------------------------------\n");
}

void printRow(const int n, int *distances, int *precs, bool *visited, vector<int> order){
  //Print step number and order
  printf("%-5d%-23s", order.size() - 1, orderStr(order).c_str());

  //For loop to print table entries
  for(int i = 1; i <= n; ++i){
    //Only print if distance to node greater than 0
    if(distances[i]){
      //Only print if node not previously visited
      if(!visited[i])
        printf("%-8s", columnStr(distances[i], precs[i]).c_str());
      else //Else leave column empty
        printf("%-8s", "");
    }
  }
  printf("\n");
}

string orderStr(const vector<int> order){
  string s = to_string(order[0]);
  for(int i = 1; i < order.size(); ++i)
    s += "," + to_string(order[i]);
  return s;
}

string columnStr(const int distance, const int preceding){
  string s;
  if(distance == BIG)
    s = "INF";
  else
    s = to_string(distance);

  s += "," + to_string(preceding);

  return s;
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

void lsr(const int nodei, const int n, int **graph, const bool flag){
  //Initialization
  int closestNode = 0;
  unsigned long start, end;
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
      precs[i] = nodei;
  }
  visited[nodei] = true;
  order.push_back(nodei);

  if(flag){
    printHeader(nodei, n);
    printRow(n, distances, precs, visited, order);
  }

  //Get starting time
  start = clock();
  //Perform calculations
  for(int i = 1; i < n; ++i){
    //Visit closest unvisited node
    closestNode = shortestPath(visited, n, distances);
    //Calculate new distance to connected paths

    if(closestNode)
      visit(n, closestNode, flag, visited, distances, precs, graph, order);
    else
      break;
  }
  //Get ending time
  end = clock() - start;
  printTable(n, distances, precs);
  printf("\nTime to perform calculations:  %d milliseconds\n", end);
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

void visit(const int n, const int node, const bool flag, bool *visited, int *distances, int *precs, int **graph, vector<int> &order){
  //Loops through to find connected nodes, then compares current cost of those nodes with the
  //cost of the current path plus the connection to them.  If lower, change routing table
  order.push_back(node);
  visited[node] = true;

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
  if(flag)
    printRow(n, distances, precs, visited, order);
}
