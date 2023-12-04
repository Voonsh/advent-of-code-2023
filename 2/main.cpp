#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
bool checkGameSet(std::string &line);
int getGameSetPower(std::string &line);
bool isNumber(std::string &word);

int part1();
int part2();

int main()
{
  std::cout<<part2();
}

int part1()
{
  std::ifstream file("input.txt");
  std::string line;

  int result = 0;
  int gameNumber = 1;
  while (std::getline(file, line))
  {
    if (checkGameSet(line))
    {
      result += gameNumber;
    }
    gameNumber++;
  }
  return result;
}

int part2() {
  std::ifstream file("input.txt");
  std::string line;

  int result = 0;
  while (std::getline(file, line))
  {
    result += getGameSetPower(line);;
  }
  return result;
}

bool checkGameSet(std::string &line)
{
  int max_red = 12;
  int max_green = 13;
  int max_blue = 14;
  std::unordered_map<char, int> colorMap = {
      {'r', 0}, {'g', 0}, {'b', 0}};

  std::stringstream s(line);
  std::string word;

  while (s >> word)
  {
    if (isNumber(word))
    {
      int number = stoi(word);

      s >> word;
      colorMap[word[0]] = number;

      if (word.back() != ',')
      {
        if (colorMap['r'] > max_red || colorMap['g'] > max_green || colorMap['b'] > max_blue)
        {
          return false;
        }
        colorMap = {
            {'r', 0}, {'g', 0}, {'b', 0}};
      }
    }
  }
  return true;
}

int getGameSetPower(std::string &line)
{
  std::unordered_map<char, int> colorMap = {
      {'r', 0}, {'g', 0}, {'b', 0}};

  std::stringstream s(line);
  std::string word;
  int maxPower = 0;
  while (s >> word)
  {
    if (isNumber(word))
    {
      int number = stoi(word);

      s >> word;
      colorMap[word[0]] = std::max(colorMap[word[0]], number);
    }
  }
  return colorMap['r'] * colorMap['g'] * colorMap['b'];
}

bool isNumber(std::string &word)
{
  if (word != "Game" && word.back() != ':')
    return true;
  return false;
}

