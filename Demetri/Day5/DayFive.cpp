#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int part_one(const std::string& file_name) {
    std::fstream file(file_name);
    std::string curr_line;
    std::string token;
    char delimiter;
    int left, right, curr, total = 0;
    std::unordered_map<int, std::vector<int>> ruleset;
    std::unordered_set<int> seen;
    std::vector<int> entries;
    bool correct;
    while (std::getline(file, curr_line)) {
        std::istringstream iss(curr_line);

        // Read in rules
        if (curr_line.find('|') != std::string::npos) {
            std::getline(iss, token, '|');
            left = std::stoi(token);
            std::getline(iss, token, '|');
            right = std::stoi(token);
            ruleset[left].push_back(right);
        }

        // Evaluate lines
        else {
            seen.clear();
            entries.clear();
            correct = true;
            while (std::getline(iss, token, ',')) {
                curr = std::stoi(token);
                seen.insert(curr);
                entries.push_back(curr);
                // If the current value needs to appear before some values
                if (ruleset.find(curr) != ruleset.end()) {
                    // Check if any of those values have already been seen
                    // If so, wrong order
                    for (auto& condition : ruleset[curr]) {
                        if (seen.find(condition) != seen.end()) {
                            correct = false;
                            break;
                        }
                    }
                }
            }
            total += (correct ? entries[entries.size() / 2] : 0);
        }
    }
    return total;
}

int part_two() {
    return 1;
}

int main() {
    const std::string file_name = "day_five_input.txt";
    std::cout << part_one(file_name) << std::endl;

}