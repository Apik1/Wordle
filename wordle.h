#pragma once
#include <vector>
#include <string>

std::string getWord(const std::vector<std::string>&);
void getWordList(std::vector <std::string>&);
void fillMapWithChar(int, char**);
void displayMap(char**, int);
void fillMap(int, char**);
double generateNumber(int, int);
bool placeWord(std::string, char**, int);
void copyWordIntoArray(std::string, int, int, int, char**);
bool checkLengthAndFit(std::string, int, int, int, char**, int);
bool checkForMatch(char**, std::string, int, int, int, int);
