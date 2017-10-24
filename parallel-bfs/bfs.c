/*
* Modified by: mbenlioglu, October 23, 2017
* 
* Following code includes sequential amd different parallel versions of breadth first
* traversal methods of a graph to find distances of vertices from a given source vertex.
*
* Graph is assumed to have no disjointed sub-graphs
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include "graphio.h"
#include "graph.h"

// #define DEBUG

char gfile[2048];

void usage(){
  printf("./bfs <filename> <sourceIndex>\n");
  exit(0);
}

int* sequential_bfs(etype* row_ptr, vtype* col_ind, vtype nov, vtype source){
  /*
   * Sequentially traverse the graph to find distances from source to all other vertices
   */
  int length = sizeof(int) * nov;

  // create distances array to store calculated distances
  int* distances = malloc(length);
  int i;
  for (i = 0; i < nov; ++i)
    distances[i] = -1;
  distances[source] = 0; // distance to itself

  // create frontier array to be traversed and set first item to the source vertex
  int* frontier = malloc(length);
  frontier[0] = source; //first element to be inspected
  
  int insert_ind = 1;
  int read_ind = 0;
  int distance = 1;

  int j, col_start, col_end, level_start, level_end, generated_cnt;

  level_start = 0;
  level_end = 1;
  while(level_end > level_start){
    generated_cnt = 0;
    for (i = 0; i < level_end - level_start; ++i)
    {
      col_start = row_ptr[frontier[read_ind]];
      col_end = row_ptr[frontier[read_ind] + 1];
      for (j = col_start; j < col_end; ++j)
      {
        #ifdef DEBUG
        printf("trying to add %d to %d relation ", frontier[read_ind], col_ind[j]);
        #endif
        if (distances[col_ind[j]] == -1)
        {
          #ifdef DEBUG
          printf("success\nchanging distance %d to %d",col_ind[j], distance);
          #endif
          frontier[insert_ind++] = col_ind[j];
          distances[col_ind[j]] = distance;
          generated_cnt++;
        }
        #ifdef DEBUG
        printf("\n");
        #endif
      }
      read_ind++;
    }
    #ifdef DEBUG
    printf("generated_cnt: %d\n", generated_cnt);
    #endif
    level_start = level_end;
    level_end += generated_cnt; //THSI IS WRONG
    distance++;
  }

  return distances;
}

int* parallel_bfs_v1(etype* row_ptr, vtype* col_ind, vtype nov, vtype source){
  
}

int* parallel_bfs_v2(etype* row_ptr, vtype* col_ind, vtype nov, vtype source){
  
}

int* parallel_bfs_v2_1(etype* row_ptr, vtype* col_ind, vtype nov, vtype source){
  
}

void preprocess_seq(etype* row_ptr, vtype* col_ind, vtype nov){

}

void preprocess_par(etype* row_ptr, vtype* col_ind, vtype nov){

}

int* parallel_bfs_v3(etype* row_ptr, vtype* col_ind, vtype nov, vtype source){

}

/*
  You can ignore the ewgths and vwghts. They are there as the read function expects those values
  row_ptr and col_ind are the CRS entities. nov is the Number of Vertices
*/
int main(int argc, char *argv[]) {
  etype *row_ptr;
  vtype *col_ind;
  ewtype *ewghts;
  vwtype *vwghts;
  vtype nov, source;

  if(argc != 3)
    usage();

  const char* fname = argv[1];
  strcpy(gfile, fname);
  source = atoi(argv[2]);
  
  if(read_graph(gfile, &row_ptr, &col_ind, &ewghts, &vwghts, &nov, 0) == -1) {
    printf("error in graph read\n");
    exit(1);
  }
  
  /****** YOUR CODE GOES HERE *******/
  int *result = sequential_bfs(row_ptr, col_ind, nov, source);
  int i;
  for (i = 0; i < nov; ++i)
    printf("%d ", result[i]);  
  printf("\n");
 
  
  free(row_ptr);
  free(col_ind);
    
  return 1;
}
