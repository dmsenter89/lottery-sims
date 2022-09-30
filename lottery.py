#!/bin/env python

import numpy as np

def main():
    weights = np.array([1.0/302575351, 1.0/12607307, 1.0/931002,
                                1.0/38793, 1.0/14548, 1.0/694, 1.0/607,
                                1.0/90, 1.0/38, 24.0/25])
    weights = weights/np.sum(weights)  # normalize

    payout = np.array([750000000, 1000000, 10000, 500, 200, 10, 10, 4, 2, 0])

    num_of_sims = 50000
    no_of_games = 5218
    game_results = np.zeros(num_of_sims, dtype='int16')

    for i in range(num_of_sims):
        winnings = 0
        res = np.random.choice(payout, size=no_of_games, p=weights)
        for w in res:
            winnings = winnings + w - 2
        game_results[i] = winnings

    np.savetxt('py_result.txt', game_results)

if __name__=='__main__':
    main()
