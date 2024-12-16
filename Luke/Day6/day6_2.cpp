#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../helper.h"

typedef std::vector<std::vector<char>> Graph;

struct Point{ 
    int x, y;
    Point operator+(const Point& p) {return {x + p.x, y + p.y};}
    Point operator+=(const Point& p) {y += p.y; x+=p.x; return *this;}
    Point operator-=(const Point& p) {y -= p.y; x-=p.x; return *this;}
};
typedef Point Vec;

static constexpr char WALL_KEY = '#';
static std::vector<char> GAURD_DIR = {'^', '>', 'v', '<'};
static std::unordered_map<char, Vec> GAURD_KEY = {{'^', {0,-1}}, {'>', {1,0}}, {'v', {0, 1}}, {'<', {-1,0}}};
std::unordered_set<int> seen;

void print_graph(Graph& graph) {
    for(auto thing : graph) {
        print_vector(thing);
        printf("\n");
    }
}

bool inBounds(Graph& graph, Point position) {
    const auto res = position.y >= 0 && position.x >= 0 && position.y < graph.size() && position.x < graph[position.y].size();
    return res;
}

std::vector<Point> turns;
int currIndex = 0;
int numBlockers = 0;

// Walk and turn. Return if there are more steps to take.
bool step(Graph& graph, Point gaurdPos, int& sum) {
    if(!inBounds(graph, gaurdPos)) return false;
    auto gaurdChar = graph[gaurdPos.y][gaurdPos.x];
    Vec direction = GAURD_KEY[gaurdChar];

    turns.push_back(gaurdPos);

    // Find rectangle
    if (turns.size() >= 3) {
        auto tmpGaurdPos = gaurdPos;
        printf("3 points: (%d, %d), (%d, %d), (%d, %d) finding fourth going (%d, %d)", turns[turns.size() - 3].x, turns[turns.size() - 3].y,turns[turns.size() - 2].x,turns[turns.size() - 2].y, turns[turns.size() - 1].x,turns[turns.size() - 1].y, direction.x,direction.y);
        while(inBounds(graph, tmpGaurdPos) && graph[tmpGaurdPos.y][tmpGaurdPos.x] != '#' && tmpGaurdPos.y != turns[turns.size() - 3].y && tmpGaurdPos.x != turns[turns.size() - 3].x) {
            char currentCell = graph[tmpGaurdPos.y][tmpGaurdPos.x];
            tmpGaurdPos += direction;
        }
        if(inBounds(graph, tmpGaurdPos) && graph[tmpGaurdPos.y][tmpGaurdPos.x] != '#'){
            tmpGaurdPos += direction;
            if(inBounds(graph, tmpGaurdPos) && graph[tmpGaurdPos.y][tmpGaurdPos.x] != '#'){
                printf("\t Fourth at (%d, %d)\n", tmpGaurdPos.x, tmpGaurdPos.y);
                numBlockers++;
            }
        }
        printf("\n");
    }

    while(inBounds(graph, gaurdPos) && graph[gaurdPos.y][gaurdPos.x] != '#') {
        char currentCell = graph[gaurdPos.y][gaurdPos.x];
        seen.insert(gaurdPos.y * graph.front().size() + gaurdPos.x);
        if(currentCell != 'x') sum++;
        graph[gaurdPos.y][gaurdPos.x] = 'x';
        gaurdPos += direction;
    }

    // Update direction
    if(inBounds(graph, gaurdPos)) {
        auto pos = std::find(GAURD_DIR.begin(), GAURD_DIR.end(), gaurdChar);
        int newIndex = (std::distance(GAURD_DIR.begin(), pos) + 1) % GAURD_DIR.size();
        gaurdPos -= direction;
        if(inBounds(graph, gaurdPos)){
            graph[gaurdPos.y][gaurdPos.x] = GAURD_DIR[newIndex];
            step(graph, gaurdPos, sum);
            return true;
        }
    }
    gaurdPos -= direction;
    return false;
}

int main() {

    std::ifstream file("puzzle_input.txt");

    // Build graph
    Graph graph;
    std::string row;
    Vec startingPosition;
    while(std::getline(file, row)) {
        graph.push_back({});
        for(auto cell : row) {
            auto guardIt = GAURD_KEY.find(cell);
            if(guardIt != GAURD_KEY.end()) startingPosition = {(int)graph.back().size(), (int)graph.size() - 1};
            graph.back().push_back(cell); 
        }
    }


    int sum = 0;

    step(graph, startingPosition, sum);

    printf("Num possible blockers: %d\n", numBlockers);

    return 0;
    

}
