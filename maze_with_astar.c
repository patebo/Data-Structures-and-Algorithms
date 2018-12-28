#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//!
#include "IntPriorityQueue.h"

#define MAXSIZE 100

struct MazeData {
  char maze[MAXSIZE*MAXSIZE];           // to store the maze
  int from[MAXSIZE*MAXSIZE];            // to reconstruct path
  int dist[MAXSIZE*MAXSIZE];            // for Dijkstra and A*
  int spos;                             // starting position
  int fpos;                             // finish position
};

typedef struct MazeData* Maze;


// In: coordinates in the maze.
// Out: the coordinates combined into a single int.
int pack(int x, int y) { return x+MAXSIZE*y; }

// In: a position in the maze, as a single integer
// Side effect: the position is unpacked into its components,
//              which are stored in x and y respectively.
void unpack(int pos, int* x, int* y) {
  *x = pos%MAXSIZE; *y=pos/MAXSIZE;
}

// Reads a maze from standard input, and initialises the Maze data
// structure accordingly.
Maze maze_load(char *fn) {
  FILE* fh = fopen(fn, "r");
  if (fh==NULL) { perror("maze_load"); exit(1); }
  Maze M = (Maze)malloc(sizeof(struct MazeData));
  if (M==NULL) { perror("maze_load");  exit(1); }
  M->spos = M->fpos = -1;
  int y;
  for (y=0; y<MAXSIZE-1; y++) {
    int pos = pack(0,y);
    char* maze_line = &M->maze[pos];
    if (fgets(maze_line, MAXSIZE-1, fh) == NULL) {
      break; // end of input
    }
    for (int x=0; maze_line[x]!='\0'; x++) {
      if (maze_line[x]=='S') { M->spos = pack(x,y); }
      if (maze_line[x]=='F') { M->fpos = pack(x,y); }
    }
  }
  M->maze[pack(0,y)] = '\0';
  if (M->spos==-1 || M->fpos==-1) {
    fprintf(stderr, "Failed to find starting position or finish.\n");
    exit(1);
  }

  // mark all positions as undiscovered, and their distance undefined
  for (int pos=0; pos<MAXSIZE*MAXSIZE; pos++) {
    M->from[pos] = -1;
    M->dist[pos] = -1;
  }

  fclose(fh);
  return M;
}

// In: a Maze M
// Side effect: frees all memory used to store the maze data.
void maze_destroy(Maze M) {
  free(M);
}

// In: a Maze M
// Side effect: prints out the maze, marking discovered places with "."
//              and the path with '*' (if it's found)
void maze_print(Maze M) {
  char maze_copy[MAXSIZE*MAXSIZE];
  memcpy(maze_copy, M->maze, MAXSIZE*MAXSIZE*sizeof(char));

  // mark all discovered positions with '.'
  int ndiscovered = 0;
  for (int pos=0; pos<MAXSIZE*MAXSIZE; pos++) {
    if (M->from[pos]!=-1 && maze_copy[pos]==' ') {
      maze_copy[pos] = '.';
      ndiscovered++;
    }
  }

  // then mark the path from the finish to the start with '*'
  int pos = M->from[M->fpos];
  int path_len=1;
  while (pos!=-1 && pos!=M->spos) {
    maze_copy[pos] = '*';
    pos = M->from[pos];
    path_len++;
  }

  printf("Discovered nodes: %d. Longest path: %d\n", ndiscovered, path_len);

  // then print the maze
  for (int y=0; maze_copy[pack(0,y)]!='\0'; y++) {
    printf("%s", &maze_copy[pack(0,y)]);
  }
}


float heuristic3(int pos1, int pos2) { return 0; }

float heuristic1(int pos1, int pos2) {
  int x1, y1, x2, y2;
  unpack(pos1, &x1, &y1);
  unpack(pos2, &x2, &y2);
  return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

float heuristic2(int pos1, int pos2) {
  int x1, y1, x2, y2;
  unpack(pos1, &x1, &y1);
  unpack(pos2, &x2, &y2);
  return (float)(abs(x2-x1)+abs(y2-y1));
}

float heuristic(int pos1, int pos2) {
  int x1, y1, x2, y2;
  unpack(pos1, &x1, &y1);
  unpack(pos2, &x2, &y2);
  return (float)(abs(x2-x1));
}



//!
void maze_Astar(Maze M) {
  int x;
  int y;
  IPQ frontier = ipq_create();
  ipq_enqueue(frontier, M->spos, 0.0);
  while (ipq_size(frontier)>0) {
    // there are still unexplored places
    int n = ipq_dequeue(frontier);
    if (n==M->fpos) { return; }

    unpack(n, &x, &y);
    int dist_m = M->dist[n]+1;
    for (int dir=0; dir<4; dir++) {
      int dx = dir==0 ? -1 : dir==1 ? 1 : 0;
      int dy = dir==2 ? -1 : dir==3 ? 1 : 0;
      int m = pack(x+dx, y+dy);
      char c = M->maze[m];
      if (c!='#' && (M->dist[m]==-1 || M->dist[m] > dist_m)) {
        M->from[m] = n;
        M->dist[m] = dist_m;
        ipq_enqueue(frontier, m, (float)dist_m + heuristic(m, M->fpos));
      }
    }
  }
  ipq_destroy(frontier);
}

int main(int argc, char* argv[]) {
  if (argc!=2) { printf("usage: maze_with_astar mazefile\n"); exit(1); }
  Maze M = maze_load(argv[1]);
  maze_Astar(M); //!
  maze_print(M);
  maze_destroy(M);
  return 0;
}
