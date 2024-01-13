default:
	rm -rf bin/*
	g++ ./src/01-vertex-coloring.cpp -Wall -Wextra -std=c++17 -pedantic-errors -o ./bin/run01
	g++ ./src/02-bacon-degrees.cpp -o ./bin/run02
# g++ ./src/03-two-way.cpp -o ./bin/run03

01: src/01-vertex-coloring.cpp
	rm -rf bin/run01
	g++ ./src/01-vertex-coloring.cpp -Wall -Wextra -std=c++17 -pedantic-errors -o ./bin/run01
	./bin/run01

02: src/02-bacon-degrees.cpp
	rm -rf bin/run02
	g++ ./src/02-bacon-degrees.cpp -Wall -Wextra -std=c++17 -pedantic-errors -o ./bin/run02
	./bin/run02

03: src/03-two-way.cpp
	rm -rf bin/run03
	g++ ./src/03-two-way.cpp -Wall -Wextra -std=c++17 -pedantic-errors -o ./bin/run03
	./bin/run03

clean:
	rm -rf bin/*