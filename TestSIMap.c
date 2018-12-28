#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#include "SIMap.h"

struct WordListData {
  char*  raw_data;
  char** words;
  int    size;  // total size of data
  int    num;   // number of words
};

typedef struct WordListData* WordList;

// in: -
// out: the current time (since some fixed moment in the past) in milliseconds
float current_time() {
  return 1000*(float)clock()/CLOCKS_PER_SEC;
}

WordList wl_read(char* filename) {

  // allocate memory for the wordlistdata
  WordList W = (WordList)malloc(sizeof(struct WordListData));
  if (W==NULL) { printf("Can't allocate memory\n"); exit(1); }

    // open the file
  FILE *fh = fopen(filename, "rb");
  if (fh==NULL) { printf("Can't open the file\n"); exit(1); }

  // read the size of the file
  struct stat buf;
  fstat(fileno(fh), &buf);
  W->size = (int)buf.st_size;

  // allocate memory for the file
  W->raw_data = (char*)malloc(W->size*sizeof(char));

  // read the file
  int items_read = fread(W->raw_data, sizeof(char), W->size, fh);
  if (items_read != W->size) {
    printf("Something went wrong reading the file: %d!=%d\n", items_read, W->size);
    exit(1);
  }

  // count the number of distinct words, and terminate all of them with '\0'
  int in_word = 0;
  W->num = 0;
  for (int i=0; i<W->size; i++) {
    if (isalpha(W->raw_data[i])) {
      in_word = 1;
    } else {
      if (in_word) {
        in_word = 0;
        W->raw_data[i] = '\0';
        W->num++;
      }
    }
  }

  // allocate memory for the pointers to the individual words
  W->words = (char**)malloc(W->num * sizeof(char*));
  if (W->words==NULL) { printf("Allocation error\n"); exit(1); }

  // find the starting positions of all distinct words
  in_word = 0;
  int n=0;
  for (int i=0; i<W->size; i++) {
    if (isalpha(W->raw_data[i])) {
      if (!in_word) {
        in_word = 1;
        W->words[n] = &(W->raw_data[i]);
        n++;
      }
    } else {
      if (in_word) {
        in_word = 0;
      }
    }
  }

  fclose(fh);
  return W;
}

void wl_destroy(WordList W) {
  free(W->raw_data);
  free(W->words);
  free(W);
}

int cmp(const void* a, const void* b) {
  return strcmp(*((char**)a), *((char**)b));
}

void wl_sort(WordList W) {
  qsort(W->words, W->num, sizeof(char*), &cmp);
}

void wl_statistics(WordList W) {

  float t0 = current_time();
  SIMap M = sim_create();
  for (int i=0; i<W->num; i++) {
    int c = sim_lookup(M, W->words[i]);
    if (c==-1) {
      sim_set(M, W->words[i], 1);
    } else {
      sim_set(M, W->words[i], c+1);
    }
  }
  //test sim_remove
  //sim_remove(M, "the");
  float t1 = current_time();

  int best_freq = 0;
  char* best_word;
  for (int i=0; i<W->num; i++) {
    int c = sim_lookup(M, W->words[i]);
    if (c > best_freq) {
      best_freq = c;
      best_word = W->words[i];
    }
  }

  printf("%-40s: %d bytes\n", "File size", W->size);
  printf("%-40s: %d\n", "Total number of words", W->num);
  printf("%-40s: %d\n", "Number of distinct words", sim_size(M));
  printf("%-40s: %s (occurs %d times)\n", "Most frequent word",
         best_word, best_freq);
  printf("%-40s: %f ms\n", "Total time taken", t1-t0);
  sim_destroy(M);
}

void wl_timings(WordList W) {

  for (int nwords=100; nwords<W->num; nwords=(int)nwords*1.1) {
    float t0 = current_time();
    SIMap M = sim_create();
    for (int i=0; i<nwords; i++) {
        int c = sim_lookup(M, W->words[i]);
        if (c==-1) {
          sim_set(M, W->words[i], 1);
        } else {
          sim_set(M, W->words[i], c+1);
        }
    }
    float t1 = current_time();
    sim_destroy(M);

    printf("%d,%f\n", nwords, t1-t0);
  }
}

int main(int argc, char* argv[]) {

  if (argc!=2) {
    printf("usage: TestSIMap textfile\n");
    exit(1);
  }

  WordList W = wl_read(argv[1]);


  //Experiment 1:
  wl_statistics(W);

  // Experiment 2:
  //wl_timings(W);

  return 0;
}
