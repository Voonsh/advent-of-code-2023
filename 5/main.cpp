#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_set>
#include <deque>

long long part1();
long long part2();

void prepareMaps(std::ifstream &file);
long long getLocationForSeed(long long seed);

std::vector<long long> getSeeds(std::ifstream &file);
std::vector<std::pair<long long, long long> > getSeedPairs(std::ifstream &file);
std::vector<std::vector<long long>> getMap(std::ifstream &file);
long long getNextValue(long long sourceValue, std::vector<std::vector<long long>> map);

std::vector<std::vector<long long>> seedToSoilMap;
std::vector<std::vector<long long>> soilToFertilizerMap;
std::vector<std::vector<long long>> fertilizerToWaterMap;
std::vector<std::vector<long long>> waterToLightMap;
std::vector<std::vector<long long>> lightToTemperatureMap;
std::vector<std::vector<long long>> temperatureToHumidityMap;
std::vector<std::vector<long long>> humidityToLocationMap;

int main()
{
  // std::cout << part1() << std::endl;
  std::cout <<"RESULT"<<part2() << std::endl;
}

long long part1()
{
  long long minLocation = LONG_LONG_MAX;
  std::ifstream file("input.txt");

  auto seeds = getSeeds(file);
  prepareMaps(file);

  for (auto seed : seeds)
  {
    minLocation = std::min(minLocation, getLocationForSeed(seed));
  }
  return minLocation;
}

long long part2() {
  long long minLocation = LONG_LONG_MAX;
  std::ifstream file("input.txt");

  auto seeds = getSeedPairs(file);
  prepareMaps(file);

  for (auto p : seeds) {
    for(int i=0; i <p.second; i++)
    {
      minLocation = std::min(minLocation, getLocationForSeed(p.first+i));
    }
    std::cout<<minLocation<<std::endl;
  }
  return minLocation;
}

void prepareMaps(std::ifstream &file)
{
  seedToSoilMap = getMap(file);
  soilToFertilizerMap = getMap(file);
  fertilizerToWaterMap = getMap(file);
  waterToLightMap = getMap(file);
  lightToTemperatureMap = getMap(file);
  temperatureToHumidityMap = getMap(file);
  humidityToLocationMap = getMap(file);
}

long long getLocationForSeed(long long seed)
{
  long long soil = getNextValue(seed, seedToSoilMap);
  long long fertilizer = getNextValue(soil, soilToFertilizerMap);
  long long water = getNextValue(fertilizer, fertilizerToWaterMap);
  long long light = getNextValue(water, waterToLightMap);
  long long temperature = getNextValue(light, lightToTemperatureMap);
  long long humidity = getNextValue(temperature, temperatureToHumidityMap);
  long long location = getNextValue(humidity, humidityToLocationMap);
  return location;
}

std::vector<long long> getSeeds(std::ifstream &file)
{
  std::string line;
  std::getline(file, line);
  std::stringstream s(line);
  std::vector<long long> seeds;
  std::string word;
  s >> word; //'seeds:' word
  while (s >> word)
  {
    seeds.push_back(stoll(word));
  }
  std::getline(file, line); // '\n' line

  return seeds;
}
std::vector<std::pair<long long, long long> > getSeedPairs(std::ifstream &file)
{
  std::string line;
  std::getline(file, line);
  std::stringstream s(line);
  std::vector<std::pair<long long, long long> > seeds;
  std::string word;
  s >> word; //'seeds:' word
  while (s >> word)
  {
    int first = stoll(word);
    s >> word;
    int second = stoll(word);
    seeds.push_back({first, second});
  }
  std::getline(file, line); // '\n' line

  return seeds;
}

std::vector<std::vector<long long>> getMap(std::ifstream &file)
{
  std::string line;
  std::string word;
  std::vector<std::vector<long long>> map;
  while (std::getline(file, line) && line.size() != 0)
  {
    if (line.back() == ':')
    {
      continue;
    }
    std::stringstream s(line);
    s >> word;
    long long destination = stoll(word);
    s >> word;
    long long source = stoll(word);
    s >> word;
    long long range = stoll(word);

    map.push_back({destination, source, range});
  }
  std::sort(map.begin(), map.end(),
            [](const std::vector<long long> &a, const std::vector<long long> &b)
            {
              return a[1] < b[1];
            });
  return map;
}

long long getNextValue(long long sourceValue, std::vector<std::vector<long long>> map)
{
  for (auto v : map)
  {
    if (sourceValue >= v[1] && sourceValue < (v[1] + v[2]))
    {
      return (v[0] + (sourceValue - v[1]));
    }
  }
  return sourceValue;
}
