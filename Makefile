all: bin bin/cpp_lottery bin/omp_lottery bin/go_lottery rust/target/release/rust_lottery

bin:
	mkdir -p bin

bin/cpp_lottery: cpp/lottery.cpp
	g++ -O2 cpp/lottery.cpp -o bin/cpp_lottery

bin/omp_lottery: cpp/lottery.cpp
	g++ -O2 -fopenmp cpp/lottery.cpp -o bin/omp_lottery

bin/go_lottery: go/lottery.go
	go build -o bin/go_lottery go/lottery.go

rust/target/release/rust_lottery: rust/src/main.rs
	cargo build --release --manifest-path rust/Cargo.toml

benchmark:
	hyperfine --export-markdown benchmark_results.md './bin/cpp_lottery' './bin/omp_lottery' './bin/go_lottery' './rust/target/release/rust_lottery' 'julia lottery.jl' 'julia -t 4 ./lottery.jl' 'python3 ./lottery.py'