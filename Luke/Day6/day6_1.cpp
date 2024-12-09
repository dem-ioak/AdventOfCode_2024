#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

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

bool inBounds(Graph& graph, Point position) {
    return position.y >= 0 && position.x >= 0 && position.y < graph.size() && position.x < graph[position.y].size();
}
// Walk and turn. Return if there are more steps to take.
bool step(Graph& graph, Point gaurdPos, int& sum) {
    if(!inBounds(graph, gaurdPos)) return false;
    auto gaurdChar = graph[gaurdPos.y][gaurdPos.x];
    Vec direction = GAURD_KEY[gaurdChar];

    while(inBounds(graph, gaurdPos) && graph[gaurdPos.y][gaurdPos.x] != '#') {
        char currentCell = graph[gaurdPos.y][gaurdPos.x];
        printf("Gaurd pos: (%d, %d) = %c\n", gaurdPos.x, gaurdPos.y, currentCell);
        if(currentCell != 'x') sum++;
        graph[gaurdPos.y][gaurdPos.x] = 'x';
        gaurdPos += direction;
    }

    printf("!Gaurd pos: (%d, %d) = %c\n", gaurdPos.x, gaurdPos.y, graph[gaurdPos.y][gaurdPos.x]);
    // Update direction
    if(inBounds(graph, gaurdPos)) {
        auto pos = std::find(GAURD_DIR.begin(), GAURD_DIR.end(), gaurdChar);
        int newIndex = (std::distance(GAURD_DIR.begin(), pos) + 1) % GAURD_DIR.size();
        gaurdPos -= direction;
        if(inBounds(graph, gaurdPos)){
            graph[gaurdPos.y][gaurdPos.x] = GAURD_DIR[newIndex];
            printf("Changing to %c\n", graph[gaurdPos.y][gaurdPos.x]);
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

    printf("Cells taken by gaurd: %d\n", sum);

    return 0;
    

}
