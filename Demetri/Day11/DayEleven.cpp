#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

typedef unsigned long long ull;

std::vector<ull> split(std::string line, char delimiter) {
    std::vector<ull> tokens;
    std::istringstream iss(line);
    std::string curr_num;
    while (std::getline(iss, curr_num, delimiter)) {
        if (curr_num.empty()) {
            continue;
        }
        tokens.push_back(std::stoll(curr_num));
    }
    return tokens;

}

void print_vec(std::vector<int> arr) {
    for (auto& ele : arr) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
}

int part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string line;
    std::getline(file, line);
    std::vector<ull> stones = split(line, ' ');
    std::string num_str;

    // Bruteforce it :D
    for (int i = 0; i < 25; i++) {
        std::vector<ull> next_itr;
        for (ull num_int : stones) {
            num_str = std::to_string(num_int);
            num_int = std::stoll(num_str);
            int str_len = num_str.size();
            if (num_int == 0) {
                next_itr.push_back(1);
            }
            else if (str_len % 2 == 0) {
                next_itr.push_back(std::stoll(num_str.substr(0, str_len / 2)));
                next_itr.push_back(std::stoll(num_str.substr(str_len / 2, str_len / 2)));
            }
            else {
                next_itr.push_back(num_int * 2024);
            }
        }
        stones = next_itr;
    }
    return stones.size();
}

int main() {
    const std::string file_name = "day_eleven_input.txt";
    std::cout << part_one(file_name) << std::endl;
}