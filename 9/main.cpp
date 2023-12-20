#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_set>

int part1();
int part2();

int getDiff(std::vector<int> &numbers);
int getDiff2(std::vector<int> &numbers);

int main()
{
    std::cout << part1() << std::endl;
    std::cout << part2() << std::endl;
}

int part1()
{
    std::ifstream file("input.txt");
    std::string line;
    int result = 0;
    while (std::getline(file, line))
    {
        std::vector<int> numbers;
        std::stringstream s(line);
        int number;

        while (s >> number)
        {
            numbers.push_back(number);
        }
        result += getDiff(numbers);
    }
    return result;
}

int getDiff(std::vector<int> &numbers) 
{
    bool allZeroes = true;
    std::vector<int> newNumbers;
    for(int i = 1; i<numbers.size(); i++) {
        if(numbers[i] != 0) {
            allZeroes = false;
        }
        newNumbers.push_back(numbers[i]-numbers[i-1]);
    }

    if(allZeroes) {
        return 0;
    }
    else {
        int diff = getDiff(newNumbers);
        return diff + numbers.back();
    }
}

int part2()
{
    std::ifstream file("input.txt");
    std::string line;
    int result = 0;
    while (std::getline(file, line))
    {
        std::vector<int> numbers;
        std::stringstream s(line);
        int number;

        while (s >> number)
        {
            numbers.push_back(number);
        }
        result += getDiff2(numbers);
    }
    return result;
}

int getDiff2(std::vector<int> &numbers) 
{
    bool allZeroes = true;
    std::vector<int> newNumbers;
    for(int i = 1; i<numbers.size(); i++) {
        if(numbers[i] != 0) {
            allZeroes = false;
        }
        newNumbers.push_back(numbers[i]-numbers[i-1]);
    }
    
    if(allZeroes) {
        return 0;
    }
    else {
        int diff = getDiff2(newNumbers);
        return numbers.front() - diff;
    }
}