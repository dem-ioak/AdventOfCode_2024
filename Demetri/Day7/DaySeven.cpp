#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

std::vector<std::string> split_into_str_vec(std::string& line, char delimiter) {
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string curr_str;
    while (std::getline(iss, curr_str, delimiter)) {
        tokens.push_back(curr_str);
    }
    return tokens;
}

std::vector<int> split_into_int_vec(std::string& line, char delimiter) {
    std::istringstream iss(line);
    std::vector<int> tokens;
    std::string curr_str;
    while (std::getline(iss, curr_str, delimiter)) {
        if (curr_str.empty()) {
            continue;
        }
        tokens.push_back(std::stoi(curr_str));
    }
    return tokens;
}

void get_combinations(int n, std::string current, std::vector<std::string>& combinations, bool part_two) {
    if (current.size() == n - 1) {
        combinations.push_back(current);
        return;
    }
    get_combinations(n, current + "+", combinations, part_two);
    get_combinations(n, current + "*", combinations, part_two);
    if (part_two) {
        get_combinations(n, current + "|", combinations, part_two);
    }

}

bool valid_combination_a(long long target, std::string combination, std::vector<int>& operands) {
    long long result = operands[0];
    for (int i = 0; i < combination.size(); i++) {

        result = combination[i] == '+' ? result + operands[i + 1] : result * operands[i + 1];
        if (result > target) {
            return false;
        }
        
        if (result == target) {
            return true;
        }
    }
    return false;
}

bool valid_combination_b(long long target, std::string combination, std::vector<int>& operands) {
    long long result = operands[0];
    std::vector<long long> tokens;
    std::string result_str;
    for (int i = 0; i < combination.size(); i++) {
        if (combination[i] == '+') {
            result += operands[i + 1];
        }
        else if (combination[i] == '*') {
            result *= operands[i + 1];
        }
        else {
            result = std::stoll(std::to_string(result) + std::to_string(operands[i + 1]));

        }
    }
    return result == target;
}

long long part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    long long total = 0;
    while (std::getline(file, curr_line)) {
        bool is_valid = false;
        std::vector<std::string> tokens = split_into_str_vec(curr_line, ':');
        long long lhs = std::stoll(tokens[0]);
        std::vector<int> operands = split_into_int_vec(tokens[1], ' ');
        std::vector<std::string> combinations;
        get_combinations(operands.size(), "", combinations, false);
        for (auto& comb : combinations) {
            if (valid_combination_a(lhs, comb, operands)) {
                is_valid = true;
            }
        }
        total += is_valid ? lhs : 0;
    }
    return total;
}

long long part_two(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    long long total = 0;
    while (std::getline(file, curr_line)) {
        bool is_valid = false;
        std::vector<std::string> tokens = split_into_str_vec(curr_line, ':');
        long long lhs = std::stoll(tokens[0]);
        std::vector<int> operands = split_into_int_vec(tokens[1], ' ');
        std::vector<std::string> combinations;
        get_combinations(operands.size(), "", combinations, true);
        for (auto& comb : combinations) {
            //std::cout << comb << std::endl;
            if (valid_combination_b(lhs, comb, operands)) {
                is_valid = true;
            }
        }
        total += is_valid ? lhs : 0;
        //std::cout << std::endl;
    }
    return total;
}

int main() {
    const std::string file_name = "day_seven_input.txt";
    std::cout <<  "Part One Answer: " << part_one(file_name) << std::endl;
    std::cout << "Part Two Answer: " << part_two(file_name) << std::endl;
}