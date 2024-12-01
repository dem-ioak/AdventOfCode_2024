#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>

int main() {

    std::ifstream file("puzzle_input.txt");

    if (!file.is_open()) {
        std::cerr << "Could not open puzzle input\n";
        return -1;
    }

    std::unordered_map<int, int> leftFreq, rightFreq;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string word;

        lineStream >> word;
        int leftId = (std::stoi(word));
        lineStream >> word;
        int rightId = (std::stoi(word));

        leftFreq [leftId]  += 1;
        rightFreq[rightId] += 1;
    }

    int similarityScore = 0;
    for(auto& [id, freq] : leftFreq) {
        auto rightPos = rightFreq.find(id);
        if (rightPos != rightFreq.end()) {
            similarityScore += id * rightPos->second;
        }
    }

    printf("Similarity score: %d\n", similarityScore);
    return 0;
}
