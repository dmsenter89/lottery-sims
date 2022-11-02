#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double runiform(void);
size_t weighted_random(const double weights[], const int length);
void mega_millions(int winnings[], const int numOfSims);
void save_results(const int winnings[], const int length );


int main() {
  const int NumberOfSims = 50000;
  int winnings[NumberOfSims];
  
  srand(time(NULL)); // random seed

  printf("Begin Mega Million simulation.\n");
  mega_millions(winnings, NumberOfSims);

  printf("Finished simulation, saving result.\n");
  save_results(winnings, NumberOfSims);

  return EXIT_SUCCESS;
}

// Returns uniform random var in [0,1].
// Used as a helper function in weighted_random.
double runiform(void) {
  double r = (double)rand() / RAND_MAX;
  return r;
}

// Returns an index based on the array weights.
// Assumes the weights sum to one.
size_t weighted_random(const double weights[], const int length) {
  double rnd = runiform();
  for (size_t i = 0; i < length; i++) {
    rnd -= weights[i];
    if (rnd < 0) {
      return i;
    }
  }
  return length+1; // outside of bounds when not matching
}

// playing the mega-millions
void mega_millions(int winnings[], const int numOfSims){
  double weights[10] = {1.0/302575351, 1.0/12607307, 1.0/931002,
                      1.0/38793, 1.0/14548, 1.0/694, 1.0/607,
                      1.0/90, 1.0/38, 24.0/25};

  int payout[10] = {750000000, 1000000, 10000, 500, 200, 10, 10, 4, 2, 0};
  
  int numOfGames = 5218;
  
  int wins;
  
  for (size_t i = 0; i < numOfSims; i++) {
    winnings[i] = 0; wins = 0;
    for (size_t j=0; j<numOfGames; j++){
      wins += payout[weighted_random(weights,10)] - 2;
    }
    winnings[i] = wins;
  } 
}

void save_results(const int winnings[], const int length ){
  FILE *fp = fopen("results.txt", "w");
  for (int i=0; i<length; i++){
    fprintf(fp, "%d\n", winnings[i]);
  }
  fclose(fp);
}