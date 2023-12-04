#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
int part1();
int part2();
int getCalibrationValue(std::unordered_map<std::string, std::string> &digitMap);

int main()
{
  std::cout<<part1()<<std::endl;
  std::cout<<part2()<<std::endl;
}

int part1() {
    std::unordered_map<std::string, std::string> digitMap = {
      {"1", "1"},
      {"2", "2"},
      {"3", "3"},
      {"4", "4"},
      {"5", "5"},
      {"6", "6"},
      {"7", "7"},
      {"8", "8"},
      {"9", "9"},
      {"0", "0"},
  };
  return getCalibrationValue(digitMap);
}

int part2() {

  std::unordered_map<std::string, std::string> digitMap = {
      {"1", "1"},
      {"2", "2"},
      {"3", "3"},
      {"4", "4"},
      {"5", "5"},
      {"6", "6"},
      {"7", "7"},
      {"8", "8"},
      {"9", "9"},
      {"0", "0"},
      {"zero", "0"},
      {"one", "1"},
      {"two", "2"},
      {"three", "3"},
      {"four", "4"},
      {"five", "5"},
      {"six", "6"},
      {"seven", "7"},
      {"eight", "8"},
      {"nine", "9"}
  };
  return getCalibrationValue(digitMap);
}

int getCalibrationValue(std::unordered_map<std::string, std::string> &digitMap) {
  int sum = 0;

  std::ifstream file("input.txt");
  std::string line;
  while (std::getline(file, line))
  {
    size_t first_pos = std::string::npos;
    std::string first_val = "";
    size_t last_pos = 0;
    std::string last_val = "";
    for (auto s : digitMap)
    {
      auto pos = line.find(s.first);
      if (pos < first_pos)
      {
        first_pos = pos;
        first_val = s.second;
      }
      pos = line.rfind(s.first);
      if (pos != std::string::npos && pos >= last_pos)
      {
        last_pos = pos;
        last_val = s.second;
      }
    }
    std::string tmp = first_val + last_val;
    sum += stoi(tmp);
  }
  return sum;
}
