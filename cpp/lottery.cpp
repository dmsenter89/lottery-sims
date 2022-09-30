#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#ifdef _OPENMP
    #include "omp.h"
#endif

std::discrete_distribution<int> game_distribution(){
    // define a distribution based on weights
    std::vector<double> weights {1.0/302'575'351, 1.0/12'607'307, 1.0/931'002,
                                1.0/38'793, 1.0/14'548, 1.0/694, 1.0/607,
                                1.0/90, 1.0/38, 24.0/25};
    // distribution that returns indices based on my weights
    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    return dist;
}

std::vector<int> mega_millions(){
    auto dist = game_distribution();

    // define the payouts; jackpot is set to 750 million
    std::vector<int> payout {750'000'000, 1'000'000, 10'000, 500, 200, 10, 10, 4, 2, 0};
    
    // set up random devices
    std::random_device rd;
    std::mt19937 gen(rd());

    // pre-allocate space for the number of games we wish to play
    std::vector<int> game_results{};
    game_results.reserve(50'000);

    #pragma omp parallel for
    for (int i=0; i<game_results.capacity(); ++i){
        int winnings = 0; 
        // we play 5'218 games each time
        for (int j=0; j<5'218; ++j){
            winnings += payout[dist(gen)] - 2;
        }
        #pragma omp critical
        game_results.push_back(winnings);
    }
    return game_results;
}

void save_results(const std::vector<int>& v){
    std::ofstream outFile("results.txt");

    for (const auto &e: v) {
        outFile << e << "\n";
    }
}

int main() {
    std::cout.imbue(std::locale("en_US.UTF-8")); // show commas when printing numbers

    std::cout << "Begin Mega Million simulation." << std::endl;
    std::vector<int> v = mega_millions();
    std::cout << "Finished simulation, saving result." << std::endl;

    save_results(v);
}
