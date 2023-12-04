#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

int part1(std::vector<std::string> &schema);
int part2(std::vector<std::string> &schema);
bool isDigit(char c);
bool isSymbol(char c);
bool isOutOfBound(std::vector<std::string> &schema, int row, int col);
bool isAdjacentToSymbol(std::vector<std::string> &schema, int row, int col);
std::pair<int,int> getAdjacentGear(std::vector<std::string> &schema, int row, int col);

int main() {
  std::ifstream file("input.txt");
  std::string line;
  std::vector<std::string> schema;

  while (std::getline(file, line)) {
    schema.push_back(line);
  }
  std::cout<<part1(schema)<<std::endl;
  std::cout<<part2(schema)<<std::endl;
}

int part1(std::vector<std::string> &schema) {
  int result = 0;
  std::string numberStr = "";
  bool isAdjacent = false;
  for(int i=0; i<schema.size(); i++) 
  {
    for(int j=0; j<schema[0].size(); j++)
    {
      char c = schema[i][j];
      if(isDigit(c)) {
        numberStr += c;
        if(!isAdjacent) {
          isAdjacent = isAdjacentToSymbol(schema, i, j);
        }
      }
      else {
        if(isAdjacent) {
          result += stoi(numberStr);
        }
        numberStr = "";
        isAdjacent = false;
      }
    }
  }
  return result;
}

int part2(std::vector<std::string> &schema) {
  std::map<std::pair<int,int>, std::vector<int> > gearMap;
  int result = 0;
  std::string numberStr = "";
  std::pair<int,int> isAdjacent = {-1, -1};
  for(int i=0; i<schema.size(); i++) 
  {
    for(int j=0; j<schema[0].size(); j++)
    {
      char c = schema[i][j];
      if(isDigit(c)) {
        numberStr += c;
        if(isAdjacent.first == -1) {
          isAdjacent = getAdjacentGear(schema, i, j);
        }
      }
      else {
        if(isAdjacent.first != -1) {
          gearMap[isAdjacent].push_back(stoi(numberStr));
        }
        numberStr = "";
        isAdjacent = {-1, -1};
      }
    }
  }
  for(auto item: gearMap) {
    if(item.second.size() == 2) {
      result += item.second[0] * item.second[1];
    }
  }
  return result;
}
bool isAdjacentToSymbol(std::vector<std::string> &schema, int row, int col) {
  std::vector<std::pair<int,int> > coordsToCheck = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}, {1, 1}
  };

  for(std::pair<int,int> p : coordsToCheck) {
    int newRow = row + p.first;
    int newCol = col + p.second;
    if(!isOutOfBound(schema, newRow, newCol)) {
      if(isSymbol(schema[newRow][newCol])) {
        return true;
      }
    }
  }
  return false;
}

std::pair<int,int> getAdjacentGear(std::vector<std::string> &schema, int row, int col) {
  std::vector<std::pair<int,int> > coordsToCheck = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}, {1, 1}
  };

  for(std::pair<int,int> p : coordsToCheck) {
    int newRow = row + p.first;
    int newCol = col + p.second;
    if(!isOutOfBound(schema, newRow, newCol)) {
      if(schema[newRow][newCol] == '*') {
        return {newRow, newCol};
      }
    }
  }
  return {-1, -1};
}

bool isOutOfBound(std::vector<std::string> &schema, int row, int col) {
  return row < 0 || row >= schema.size() || col < 0 || col >= schema[0].size();
}

bool isDigit(char c) 
{
  return c >= '0' && c<= '9';
}

bool isSymbol(char c) 
{
  return !isDigit(c) && c != '.';
}