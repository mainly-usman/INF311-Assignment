CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

gradebook: src/main.cpp
	$(CXX) $(CXXFLAGS) -o gradebook src/main.cpp

run: gradebook
	./gradebook

clean:
	rm -f gradebook gradebook_report.txt
