#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

int main() {

    std::ifstream file("puzzle_input.txt");

    if (!file.is_open()) {
        std::cerr << "Could not open puzzle input\n";
        return -1;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> leftQueue, rightQueue;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string word;

        lineStream >> word;
        leftQueue.push(std::stoi(word));

        lineStream >> word;
        rightQueue.push(std::stoi(word));
    }

    int distanceSum = 0;
    while (!leftQueue.empty()) {
        distanceSum += std::abs(leftQueue.top() - rightQueue.top());
        leftQueue.pop(); rightQueue.pop();
    }

    printf("Sum of distances: %d\n", distanceSum);
    return 0;
}
