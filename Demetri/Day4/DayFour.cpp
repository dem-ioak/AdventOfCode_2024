#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>

bool search_util_a(std::vector<std::vector<char>>& matrix, int row, int col, std::pair<int, int>& direction, int xmas_idx) {
    static const char xmas[] = {'X', 'M', 'A', 'S'};
    if (row < 0 || row >= matrix.size() || col < 0 || col >= matrix[0].size() || matrix[row][col] != xmas[xmas_idx]) {
        return false;
    }
    if (xmas_idx == 3) {
        return true;
    }
    int dy = direction.first, dx = direction.second;
    return search_util_a(matrix, row + dy, col + dx, direction, xmas_idx + 1);
}

int part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    char curr_char;
    int idx = 0;
    int total = 0;
    std::vector<std::vector<char>> matrix; // Init 2D Matrix
    std::vector <std::pair<int, int>> offsets = {
        {0, 1},   // Right
        {0, -1},  // Left
        {1, 0},   // Down
        {-1, 0},  // Up
        {-1, -1}, // UpLeft
        {-1, 1}, // UpRight
        {1, -1}, // DownLeft
        {1, 1}   // DownRight
    };



    while (std::getline(file, curr_line)) {
        std::istringstream iss(curr_line);
        matrix.push_back(std::vector<char>()); // Add empty row
        while (iss >> curr_char) {
            matrix.back().push_back(curr_char); // Read in char by char, push to most recently added row
        }
    }
    int m = matrix.size(), n = matrix[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'X') {
                for (int k = 0; k < offsets.size(); k++) {
                    total += search_util_a(matrix, i, j, offsets[k], 0);
                }
            }
        }
    }

    return total;
}

bool search_util_b(std::vector<std::vector<char>>& matrix, int row, int col, std::pair<int, int>& direction, int mas_idx) {
    static const char mas[] = {'M', 'A', 'S'};
    int dy = direction.first, dx = direction.second;
    if (row < 0 || row >= matrix.size() || col < 0 || col >= matrix[0].size() || matrix[row][col] != mas[mas_idx]) {
        return false;
    }
    if (mas_idx == 2) {
        return true;
    }
    return search_util_b(matrix, row + dy, col + dx, direction, mas_idx + 1);
}

int part_two(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string curr_line;
    char curr_char;
    int idx = 0;
    int total = 0;
    std::vector<std::vector<char>> matrix; // Init 2D Matrix
    std::vector <std::pair<int, int>> offsets = {
        {-1, -1}, // UpLeft
        {-1, 1}, // UpRight
        {1, -1}, // DownLeft
        {1, 1}   // DownRight
    };

    while (std::getline(file, curr_line)) {
        std::istringstream iss(curr_line);
        matrix.push_back(std::vector<char>()); // Add empty row
        while (iss >> curr_char) {
            matrix.back().push_back(curr_char); // Read in char by char, push to most recently added row
        }
    }
    int m = matrix.size(), n = matrix[0].size();
    int intersections[m][n] = {};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'M') {
                for (int k = 0; k < 4; k++) {
                    if (search_util_b(matrix, i, j, offsets[k], 0)) {
                        intersections[i + offsets[k].first][j + offsets[k].second]++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            total += intersections[i][j] >= 2;
        }
    }

    return total;
}

int main() {
    const std::string& file_name = "day_four_input.txt";
    std::cout << part_one(file_name) << std::endl;
    std::cout << part_two(file_name) << std::endl;
}