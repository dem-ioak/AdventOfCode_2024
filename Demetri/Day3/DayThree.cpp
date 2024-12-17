#include <iostream>
#include <regex>
#include <string>
#include <fstream>


int part_one(const std::string& file_name) {

    std::ifstream file(file_name);
    std::string curr_line;
    const std::string mul_match = "mul\\({1}\\d+,{1}\\d+\\){1}";
    const std::string num_match = "\\d+";
    std::string curr_match;
    std::regex mul_pattern(mul_match);
    std::regex num_pattern(num_match);
    int total = 0, left, right;

    while (std::getline(file, curr_line)) {
        std::sregex_iterator mul_itr(curr_line.begin(), curr_line.end(), mul_pattern);
        std::sregex_iterator end;
        while (mul_itr != end) {
            curr_match = mul_itr->str();
            std::sregex_iterator num_itr(curr_match.begin(), curr_match.end(), num_pattern);
            left = std::stoi(num_itr++->str());
            right = std::stoi(num_itr++->str());
            total += left * right;
            mul_itr++;
        }
    }
    return total;
}

int part_two(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    const std::string mul_match = "(mul\\({1}\\d+,{1}\\d+\\){1})|(do\\(\\))|(don't\\(\\))";
    const std::string num_match = "\\d+";
    std::string curr_match;
    std::regex mul_pattern(mul_match);
    std::regex num_pattern(num_match);
    int total = 0, left, right;
    bool doing = true;

    while (std::getline(file, curr_line)) {
        std::sregex_iterator mul_itr(curr_line.begin(), curr_line.end(), mul_pattern);
        std::sregex_iterator end;
        while (mul_itr != end) {
            curr_match = mul_itr->str();
            if (curr_match == "do()") {
                doing = true;
            }
            else if (curr_match == "don't()") {
                doing = false;
            }
            else if (doing) {
                std::sregex_iterator num_itr(curr_match.begin(), curr_match.end(), num_pattern);
                left = std::stoi(num_itr++->str());
                right = std::stoi(num_itr++->str());
                total += left * right;
                std::cout << total << std::endl;
            }
            mul_itr++;
        }
    }
    return total;

}


int main() {
    const std::string& file_name = "day_three_input.txt";
    std::cout << part_one(file_name) << std::endl;
    std::cout << part_two(file_name) << std::endl;
}