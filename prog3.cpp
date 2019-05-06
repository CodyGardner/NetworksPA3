#include "funcs.h"

using namespace std;

int main(int argc, char *argv[]){
  //Arguments passed in the form "mylinkstate <input file> <node i> <flag>"
  if(argc < 4){
    printf("Error: Insufficient arguments\n");
    return -1;
  }

  //Declarations
  ifstream ifs(argv[1]);
  int n = 0, nodei = atoi(argv[2]);
  int **graph = NULL, *distances = NULL;
  bool flag = (argv[3][0] == '1'); //If argv[3][0] is 1, flag is on
  bool *visited = NULL;

  //Check argument values
  if (ifs.fail()){
    printf("Error: Input file failed to open\n");
    return -2;
  }

  if(nodei < 1){
    printf("Error: Target node must be at least 1\n");
    return -3;
  }

  //Get and check n value
  ifs >> n;
  if(n < 3 || n > 100){
    printf("Error: Node count from input file must be in range 3-100\n");
    return -4;
  }


  //Build graph - Graph will be of size n+1 x n+1 so that raw node values may be used as indices
  graph = new int*[n + 1];
  graph[0] = NULL;
  for(int i = 1; i <= n; ++i){
    graph[i] = new int[n + 1];
    graph[i][0] = -1; //There is no node 0
  }
  buildGraph(ifs, graph);

  //Build routing table
  lsr(nodei, n, graph, flag);



  return 0;
}
