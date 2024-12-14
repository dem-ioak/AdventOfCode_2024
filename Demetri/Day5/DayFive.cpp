#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::vector<int> split(std::string& line, char delimiter) {
    std::istringstream iss(line);
    std::vector<int> tokens;
    std::string curr_token;
    while (std::getline(iss, curr_token, delimiter)) {
        tokens.push_back(std::stoi(curr_token));
    }
    return tokens;
}

void print_map(std::unordered_map<int, std::unordered_set<int>>& hmap) {
    for (const auto& [key, lst] : hmap) {
        std::cout << key << " -> [";
        for (const auto& value : lst) {
            std::cout << value << ',';
        }
        std::cout << ']' << std::endl;
    }
}

int part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    bool is_rule;
    std::unordered_map<int, std::unordered_set<int>> ruleset;
    std::vector<int> tokens;
    int left, right;
    int total = 0;
    while (std::getline(file, curr_line)) {
        if (curr_line.empty()) {
            continue;
        }
        
        std::istringstream iss(curr_line);
        is_rule = curr_line.find('|') != std::string::npos;
        // Create map linking N to NUMBERS THAT MUST COME BEFORE N
        if (is_rule) {
            tokens = split(curr_line, '|');
            left = tokens[0];
            right = tokens[1];
            ruleset[left].insert(right);
        }

        // Validate input
        else {
            std::unordered_set<int> seen;
            bool correct = true;
            tokens = split(curr_line, ',');
            for (auto& ele : tokens) {
                seen.insert(ele);
                if (ruleset.find(ele) != ruleset.end()) {
                    for (auto& dependency : ruleset[ele]) {
                        if (seen.find(dependency) != seen.end()) {
                            correct = false;
                            break;
                        }
                    }
                    if (!correct) {
                        break;
                    }
                }
            }   
            total += correct ? tokens[tokens.size() / 2] : 0;
        }
    }
    return total;
}

int part_two(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    bool is_rule;
    std::unordered_map<int, std::vector<int>> ruleset;
    std::unordered_set<int> uniques;
    std::vector<int> tokens;
    int left, right;
    int total = 0;
    while (std::getline(file, curr_line)) {
        if (curr_line.empty()) {
            continue;
        }
        
        std::istringstream iss(curr_line);
        is_rule = curr_line.find('|') != std::string::npos;
        // Create map linking N to NUMBERS THAT MUST COME BEFORE N
        if (is_rule) {
            tokens = split(curr_line, '|');
            left = tokens[0];
            right = tokens[1];
            ruleset[left].push_back(right);
            uniques.insert(left);
            uniques.insert(right);
        }

        // Validate input
        else {
            tokens = split(curr_line, ',');
            // I'll figure this out eventually
        }
    }
    return 1;
}

int main() {
    const std::string file_name = "day_five_input.txt";
    std::cout << part_one(file_name) << std::endl;
    // std::cout << part_two(file_name) << std::endl;

}