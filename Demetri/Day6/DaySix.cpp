#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <unordered_map>

const std::vector<std::vector<int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void traverse(const std::vector<std::vector<int>>& directions,
              std::unordered_set<std::tuple<int, int>>& visited,
              int curr_direction, 
              int row, 
              int col
              ) {
    


    return;
}

int part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    std::vector<std::vector<char>> mapped;
    char token;
    int curr_r, curr_c, curr_dir;
    int row_ptr = 0, col_ptr = 0;
    int total = 0;
    std::unordered_map<char, int> starting_chars = {
        {'^', 0}, 
        {'>', 1}, 
        {'v', 2}, 
        {'<', 3}
    };

    while (std::getline(file, curr_line)) {
        std::istringstream iss(curr_line);
        std::vector<char> curr_row;
        while (iss >> token) {
            curr_row.push_back(token);
            if (starting_chars.find(token) != starting_chars.end()) {
                curr_r = row_ptr;
                curr_c = col_ptr;
                curr_dir = starting_chars[token];
            }
            col_ptr++;
        }
        row_ptr++;
        col_ptr = 0;
        mapped.push_back(curr_row);
    }

    bool left_map = false;
    std::vector<std::vector<int>> visited(row_ptr, std::vector<int>(row_ptr));
    while (!left_map) {
        token = mapped[curr_r][curr_c];
        visited[curr_r][curr_c] = 1;
        int next_r = curr_r + directions[curr_dir][0];
        int next_c = curr_c + directions[curr_dir][1];
        if (next_r < 0 || next_r >= row_ptr || next_c < 0 || next_c >= row_ptr) {
            break;
        }
        if (mapped[next_r][next_c] == '#') {
            curr_dir = (curr_dir + 1) % 4;
        }
        else {
            curr_r = next_r;
            curr_c = next_c;
        }
    }

    for (int i = 0; i < row_ptr; i++) {
        for (int j = 0; j < row_ptr; j++) {
            total += visited[i][j];
        }
    }

    return total;
}

int main() {
    const std::string file_name = "day_six_input.txt";
    std::cout << part_one(file_name) << std::endl;
}