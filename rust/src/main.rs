use rand::distributions::{Distribution,WeightedIndex};
use rand::thread_rng;
use std::fs;

fn game_distribution() -> rand::distributions::WeightedIndex<f64> {
    let weights = [1.0/302_575_351.0, 1.0/12_607_307.0, 
                    1.0/931_002.0, 1.0/38_793.0, 1.0/14_548.0,
                    1.0/694.0, 1.0/607.0, 1.0/90.0, 1.0/38.0, 24.0/25.0];
    
    
    // this distribution returns indices based on my weights
    let dist = WeightedIndex::new(&weights).unwrap();

    return dist;
}

fn mega_millions() -> Vec<i32> {
    // general settings
    let num_of_sims = 50_000;
    let num_games = 5_218;

    let dist = game_distribution();
    
    // define the payouts; jackpot is set to 750 million
    let payout = [750_000_000, 1_000_000, 10_000, 500, 200, 10, 10, 4, 2, 0];
    
    // set up random device
    let mut rng = thread_rng();
    

    // set up vector for results
    let mut game_results = Vec::with_capacity(num_of_sims);
    let mut winnings;  // will initialize in the for-loop

    for _i in 1..=num_of_sims {
        winnings = 0;

        for _j in 1..=num_games {
            winnings += payout[dist.sample(&mut rng)] - 2;
        }

        game_results.push(winnings)
    }
    
    return game_results;
}

fn save_results(vec : Vec<i32>) {
    
    let mut str_repr = String::new();
    
    for val in vec {
        str_repr.push_str(&(val.to_string() + "\n"))
    }
    
    fs::write("results.txt", str_repr).expect("Unable to write file");
}

fn main() {
    println!("Begin Mega Million simulation.");
    let res = mega_millions();

    println!("Finished simulation, saving result.");
    save_results(res);
}