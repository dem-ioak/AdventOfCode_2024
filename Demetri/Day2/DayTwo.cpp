#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

bool distance_check(int a, int b) {
    int diff = std::abs(a - b);
    return diff > 0 && diff < 4;
}

void clear_and_populate_vec(std::vector<int>& tokens, std::istringstream& ss) {
    tokens.clear();
    std::string token;
    while(std::getline(ss, token, ' ')) {
        int value = std::stoi(token);
        tokens.push_back(value);
    }
}

int part_one(const std::string& file_name) {
    std::ifstream file(file_name);                                              
    std::string record;
    std::string element;
    int first, second, curr, prev;
    int total = 0;
    bool direction, safety;
    while (std::getline(file, record)) {
        std::istringstream ss(record);

        // Read first and second element in from inputstringstream
        ss >> element; 
        first = std::stoi(element);
        ss >> element;
        second = std::stoi(element);

        // Declare direction based on first 2
        direction = first < second;
        prev = second;

        safety = distance_check(first, second);
        while (ss >> element && safety) {
            curr = std::stoi(element);
            safety = (prev < curr == direction) && distance_check(curr, prev);
            prev = curr;
        }
        total += safety;
    }
    return total;
}

int part_two(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string record;
    std::string element;
    std::vector<int> vec;
    int first, second, curr, prev, prev_idx;
    int total = 0;
    bool direction, safety, record_safety;

    while (std::getline(file, record)) {
        std::istringstream ss(record);
        clear_and_populate_vec(vec, ss);
        record_safety = false;     
        for (int i = 0; i < vec.size(); i++) {

            // Delete the first
            if (i == 0) {
                direction = vec[1] < vec[2];
                safety = distance_check(vec[1], vec[2]);
                prev_idx = 2;
            }

            // Delete the second
            else if (i == 1) {
                direction = vec[0] < vec[2];
                safety = distance_check(vec[0], vec[2]);
                prev_idx = 2;
            }

            // Delete anything else
            else {
                direction = vec[0] < vec[1];
                safety = distance_check(vec[0], vec[1]);
                prev_idx = 1;
            }
            
            prev = vec[prev_idx];
            for (int j = prev_idx + 1; j < vec.size(); j++) {
                if (i == j) {
                    continue;
                }
                safety &= (prev < vec[j] == direction && distance_check(prev, vec[j]));
                prev = vec[j];
            }
            record_safety |= safety;
        }
        total += record_safety;

    }
    return total;
}

int main() {
    const std::string file_name = "day_two_input.txt";
    int part_one_ans = part_one(file_name);
    int part_two_ans = part_two(file_name);
    std::cout << part_one_ans << std::endl;
    std::cout << part_two_ans << std::endl;
}