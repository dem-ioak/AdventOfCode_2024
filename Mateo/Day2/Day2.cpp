#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::vector;
using std::string;

bool isSafe(vector<int> numbers){
    bool currSafe = true;
    string status = "";

    if (numbers[0] > numbers[1]){
        status = "increasing";
    }
    else if (numbers[0] < numbers[1]){
        status = "decreasing";
    }
    else{ // First two numbers arent increasing or decreasing so false
        currSafe = false;
    }
    for (int i = 0; i < numbers.size()-1;i++){
        if (!(abs(numbers[i] - numbers[i+1]) >= 1 && abs(numbers[i] - numbers[i+1]) <= 3)){ // If not between 1 n 3, then hahahaha
            currSafe = false;
        }
        if (numbers[i] > numbers[i+1] && status == "decreasing"){ // If two numbers arent decreasing while everything increasing, then hahaaha
            currSafe = false;
        }
        if (numbers[i] < numbers[i+1] && status == "increasing"){ // If two numbers arent increasing while everything decreasing, then hahaaha
            currSafe = false;
        }
    }
    return currSafe;
}

int partOne(string input){
    std::ifstream infile(input);
    if (!infile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    string line;
    vector<int> numbers;
    int safeReports = 0;
    
    while (getline(infile,line)){ // Reading in a line
        string strNum;
        std::istringstream splitStream(line);
        while (getline(splitStream, strNum, ' ')){ // Reading each number in a line and putting it in an array
            int num = std::stoi(strNum);
            numbers.push_back(num);
        }

        if (isSafe(numbers)){
            safeReports += 1;
        }
        numbers.clear();

    }
    return safeReports;
}

int partTwo(string input){
    std::ifstream infile(input);
    if (!infile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    string line;
    vector<int> numbers;
    int safeReports = 0;
    
    while (getline(infile,line)){ // Reading in a line
        string strNum;
        std::istringstream splitStream(line);
        while (getline(splitStream, strNum, ' ')){ // Reading each number in a line and putting it in an array
            int num = std::stoi(strNum);
            numbers.push_back(num);
        }

        if (isSafe(numbers)) safeReports += 1;
        else{
            vector<int> tempNumbers = numbers;
            for (int i = 0; i < numbers.size(); i++){
                tempNumbers.erase(tempNumbers.begin() + i);
                if (isSafe(tempNumbers)){
                    safeReports += 1;
                    break;
                }
                tempNumbers = numbers;
            }
        }
        numbers.clear();

    }
    return safeReports;
}

int main(){
    std::cout << "Part 1: " << partOne("Day2input.txt") << "\n";
    std::cout << "Part 2: " << partTwo("Day2input.txt");
    return 0;
}