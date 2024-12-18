#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

typedef unsigned long long ull;

ull part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string puzzle_input;

    // Only 1 line for this puzzle
    std::getline(file, puzzle_input);
    std::vector<int> memory_line;

    // Create linked list, specifying free nodes;
    int id_ = 0;
    for (int i = 0; i < puzzle_input.size(); i++) {
        int num_char = puzzle_input[i] - '0';
        bool is_free = i % 2 != 0;
        for (int j = 0; j < num_char; j++) {
            memory_line.push_back(is_free ? -1 : id_);
        }
        if (is_free) id_++;
    }

    int n = memory_line.size();
    int l = 0, r = n - 1;
    while (l < memory_line.size()) {

        // Move left to the next free, right to the next taken
        // Break out of loop if left exceeds right
        while (l < n && memory_line[l] != -1) {l++;}
        while (r >= 0  && memory_line[r] == -1) {r--;}
        if (l > r) {break;}

        // Free the val on the right, replace the val on the left;
        memory_line[l] = memory_line[r];
        memory_line[r] = -1;
    }   

    // Calculate checksum
    ull checksum = 0;
    for (int i = 0; i < memory_line.size(); i++) {
        std::cout << memory_line[i];
        if (memory_line[i] == -1) {
            continue;
        }
        checksum += memory_line[i] * i;
    }
    std::cout << std::endl;
    return checksum;

}

int part_two(const std::string& file_name) {
    return 1;
}

int main() {
    const std::string file_name = "day_nine_input.txt";
    std::cout << part_one(file_name) << std::endl;

}