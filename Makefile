all: bin/cpp_lottery bin/omp_lottery bin/go_lottery

bin/cpp_lottery: cpp/lottery.cpp
	g++ -O2 cpp/lottery.cpp -o bin/cpp_lottery

bin/omp_lottery: cpp/lottery.cpp
	g++ -O2 -fopenmp cpp/lottery.cpp -o bin/omp_lottery

bin/go_lottery: go/lottery.go
	go build -o bin/go_lottery go/lottery.go

benchmark:
	hyperfine --export-markdown benchmark_results.md './bin/cpp_lottery' './bin/omp_lottery' './bin/go_lottery' 'julia lottery.jl' 'julia -t 4 ./lottery.jl' 'python3 ./lottery.py'