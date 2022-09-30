package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func play_game() int {
	var winning int
	var weights = []float64{1.0 / 302575351, 1.0 / 12607307, 1.0 / 931002,
		1.0 / 38793, 1.0 / 14548, 1.0 / 694, 1.0 / 607,
		1.0 / 90, 1.0 / 38, 24.0 / 25}
	var prize = []int{750000000, 1000000, 10000, 500, 200, 10, 10, 4, 2, 0}

	rnd := rand.Float64()
	for i, w := range weights {
		rnd -= w
		if rnd < 0 {
			winning = prize[i]
			break
		}
	}
	return winning
}

func saveResults(result []int) {
	var p string
	for _, elem := range result {
		p += strconv.Itoa(elem) + "\n"
	}

	err := os.WriteFile("go_results.txt", []byte(p), 0755)
	if err != nil {
		panic(err)
	}
}

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	var numOfSims, numOfGames = 50000, 5218
	fmt.Printf("Sims: %d - Games: %d\n", numOfSims, numOfGames)

	var gameResults = make([]int, numOfSims)
	var wins int

	for i, _ := range gameResults {
		wins = 0
		for j := 0; j < numOfGames; j++ {
			wins += play_game() - 2
		}
		gameResults[i] = wins
	}

	saveResults(gameResults)
}
