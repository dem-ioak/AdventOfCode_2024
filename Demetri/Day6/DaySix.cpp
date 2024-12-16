#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <unordered_map>

struct Point {
    int x, y;
    Point(int row, int col) : x(row), y(col) {};

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "(" << x << ", " << y << ")";
        return oss.str();
    }
};

struct PointHash {
    int W;
    PointHash(int width) : W(width) {};

    std::size_t operator()(const Point& p) const {
        return p.x * W + p.y;
    }
};

// Useful globals
const std::vector<std::vector<int>> directions = {{-1, 0},   // Up
                                                  {0, 1},    // Right
                                                  {1, 0},    // Down
                                                  {0, -1}};  // Left

std::unordered_map<char, int> starting_chars = {
        {'^', 0}, 
        {'>', 1}, 
        {'v', 2}, 
        {'<', 3}
    };

void print_visited_from(std::unordered_map<Point, std::vector<int>, PointHash>& visited_from) {
    for (auto& [key, value] : visited_from) {
        std::cout << key.to_string() << " -> ";
        for (auto& ele : value) {
            std::cout << ele << ",";
        }
        std::cout << std::endl;
    }
}

void print_map(std::vector<std::vector<char>> mapped) {
    for (auto& row : mapped) {
        for (auto& ele : row) {
            std::cout << ele;
        }
        std::cout << std::endl;
    }
}

// Returns 2D MAP, START_R, START_C, START_DIRECTION
std::tuple<std::vector<std::vector<char>>, int, int, int> read_in_map(std::ifstream& file) {
    std::string curr_line;
    char token;
    int row_ptr = 0, col_ptr = 0;
    int start_r, start_c, start_dir;
    std::vector<std::vector<char>> mapped;
    while (std::getline(file, curr_line)) {
        std::istringstream iss(curr_line);
        std::vector<char> curr_row;
        while (iss >> token) {
            curr_row.push_back(token);
            if (starting_chars.find(token) != starting_chars.end()) {
                start_r = row_ptr;
                start_c = col_ptr;
                start_dir = starting_chars[token];
            }
            col_ptr++;
        }
        row_ptr++;
        col_ptr = 0;
        mapped.push_back(curr_row);
    }
    return std::tuple<std::vector<std::vector<char>>, int, int, int>(mapped, start_r, start_c, start_dir);
}

std::unordered_set<Point, PointHash> get_visited_nodes(std::vector<std::vector<char>>& mapped, int r, int c, int dir) {
    int W = mapped.size();
    int next_r, next_c;
    std::string token;
    std::unordered_set<Point, PointHash> visited(10, PointHash(W));
    while (true) {
        token = mapped[r][c];
        visited.insert(Point(r, c));
        int next_r = r + directions[dir][0];
        int next_c = c + directions[dir][1];
        if (next_r < 0 || next_r >= W || next_c < 0 || next_c >= W) {
            break;
        }
        if (mapped[next_r][next_c] == '#') {
            dir = (dir + 1) % 4;
        }
        else {
            r = next_r;
            c = next_c;
        }
    }
    return visited;
}

bool check_for_loop(std::vector<std::vector<char>> mapped, int r, int c, int dir, int test_r, int test_c) {
    int W = mapped.size();
    mapped[test_r][test_c] = '#';
    std::unordered_map<Point, std::unordered_set<int>, PointHash> obstacles_from(10, PointHash(W));
    std::string token;
    bool looped = false;
    while (true) {
        int next_r = r + directions[dir][0];
        int next_c = c + directions[dir][1];

        // Escaped
        if (next_r < 0 || next_r >= W || next_c < 0 || next_c >= W) {
            break;
        }

        // Running into an obstacle
        if (mapped[next_r][next_c] == '#') {
            Point p(next_r, next_c);

            // If this obstacle has already been hit from this direction, it's a loop
            if (obstacles_from[p].find(dir) != obstacles_from[p].end()) {
                looped = true;
                break;
            }
            obstacles_from[p].insert(dir);
            dir = (dir + 1) % 4;
        }
        else {
            r = next_r;
            c = next_c;
        }
    }
    return looped;
}

int part_one(const std::string& file_name) {
    std::ifstream file(file_name);
    auto [mapped, start_r, start_c, start_dir] = read_in_map(file);
    std::unordered_set<Point, PointHash> visited = get_visited_nodes(mapped, start_r, start_c, start_dir);
    return visited.size();
}

int part_two(const std::string& file_name) {
    std::ifstream file(file_name);
    auto [mapped, start_r, start_c, start_dir] = read_in_map(file);
    std::unordered_set<Point, PointHash> visited = get_visited_nodes(mapped, start_r, start_c, start_dir);
    int total = 0;

    for (auto& point : visited) {
        if (point == Point(start_r, start_c)) {
            continue;
        }
        total += check_for_loop(mapped, start_r, start_c, start_dir, point.x, point.y);
    }
    return total;
}

int main() {
    const std::string file_name = "day_six_input.txt";
    std::cout << "Part One Answer: " << part_one(file_name) << std::endl;
    std::cout << "Part Two Answer: " << part_two(file_name) << std::endl;
}