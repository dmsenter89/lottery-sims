#!/usr/bin/julia
using DelimitedFiles
using StatsBase

weights = [1.0/302575351, 1.0/12607307, 1.0/931002,
           1.0/38793, 1.0/14548, 1.0/694, 1.0/607,
           1.0/90, 1.0/38, 24.0/25]

payout = [750000000, 1000000, 10000, 500, 200, 10, 10, 4, 2, 0]

num_of_sims = 50000
num_of_games = 5218

game_results = zeros(Int, num_of_sims)

Threads.@threads for i in 1:num_of_sims
    winnings = 0
    res = sample(payout, Weights(weights), num_of_games)
    for w in res
        winnings = winnings + w - 2
    end
    game_results[i]=winnings
end

open("jl_results.txt", "w") do file 
    writedlm(file, game_results)
end