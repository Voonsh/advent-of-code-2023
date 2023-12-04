#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_set>

int part1();
int part2();

std::unordered_set<std::string> getWinningNumbers(std::stringstream &s);
int getCardResultCount(std::stringstream &s, std::unordered_set<std::string> &winningNumbers);
void updateCardMultiplierMap(int cardNumber, int cardResultCount, std::unordered_map<int, int> &cardMultiplierMap);

int main()
{
  std::cout << part1() << std::endl;
  std::cout << part2() << std::endl;
}

int part1()
{
  std::ifstream file("input.txt");
  std::string line;
  std::vector<std::string> schema;
  int result = 0;

  while (std::getline(file, line))
  {
    std::stringstream s(line);
    std::string word; 
    s >> word; //"Card"
    s >> word; //card number

    auto winningNumbers = getWinningNumbers(s);
    int cardResultCount = getCardResultCount(s, winningNumbers);
    if(cardResultCount > 0)
    {
      result += 1 <<(cardResultCount - 1);
    }
  }
  return result;
}

int part2()
{
  std::ifstream file("input.txt");
  std::string line;
  std::vector<std::string> schema;
  std::unordered_map<int, int> cardMultiplierMap;
  int result = 0;

  while (std::getline(file, line))
  {
    std::stringstream s(line);
    std::string word; 
    s >> word; //"Card"
    s >> word; //card number
    int cardNumber = stoi(word);

    auto winningNumbers = getWinningNumbers(s);
    int cardResultCount = getCardResultCount(s, winningNumbers);
    if(cardResultCount > 0)
    {
      updateCardMultiplierMap(cardNumber, cardResultCount, cardMultiplierMap);
    }
    result += 1 + cardMultiplierMap[cardNumber];

  }
  return result;
}

std::unordered_set<std::string> getWinningNumbers(std::stringstream &s)
{
  std::unordered_set<std::string> winningNumbers;
  std::string word;
  while (s >> word)
  {
    if (word.back() == '|')
    {
      return winningNumbers;
    }
    winningNumbers.insert(word);
  }
  return winningNumbers;
}

int getCardResultCount(std::stringstream &s, std::unordered_set<std::string> &winningNumbers) 
{
    int resultCount = 0;
    std::string word;
    while (s >> word)
    {
      if(winningNumbers.count(word))
      {
        resultCount++;
      }
    }
    return resultCount;
}

void updateCardMultiplierMap(int cardNumber, int cardResultCount, std::unordered_map<int, int> &cardMultiplierMap)
{
  for(int i = 1; i<=cardResultCount; i++)
  {
    if(!cardMultiplierMap.contains(cardNumber + i))
    {
      cardMultiplierMap[cardNumber + i] = 0;
    }
    cardMultiplierMap[cardNumber + i] += (cardMultiplierMap[cardNumber] + 1);
  }
}
