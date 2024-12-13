#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>

int part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    std::string token;
    std::priority_queue<int> left_vals;
    std::priority_queue<int> right_vals;
    int distance = 0;
    int left, right;
    while (std::getline(file, curr_line)) {
        std::istringstream iss(curr_line);
        iss >> token;
        left_vals.push(std::stoi(token));
        iss >> token;
        right_vals.push(std::stoi(token));
    }

    while (!left_vals.empty()) {
        left = left_vals.top();
        right = right_vals.top();
        distance += std::abs(left - right);
        left_vals.pop();
        right_vals.pop();
    }
    return distance;
}

int part_two(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line, token;
    std::unordered_set<int> unique_lefts;
    std::unordered_map<int, int> occurences;
    int left, right;
    int total = 0;
    while (std::getline(file, curr_line)) {
        std::istringstream iss(curr_line);
        iss >> token;
        left = std::stoi(token);
        unique_lefts.insert(left);
        iss >> token;
        right = std::stoi(token);
        occurences[right]++;
    }

    for (auto& val : unique_lefts) {
        total += occurences[val] * val;
    }
    return total;

}

int main() {
    const std::string& file_name = "day_one_input.txt";
    std::cout << part_one(file_name) << std::endl;
    std::cout << part_two(file_name) << std::endl;

}