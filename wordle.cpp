#include "wordle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>

using namespace std;

string getWord(const vector<string>& words)
{
    int random_number = int(generateNumber(0, int(words.size())));
    string word = words[random_number];
    return word;
}
void getWordList(vector <string>& words) {
    string line;
    ifstream file;
    file.open("word.list");
    file >> ws;
    bool goodword;
    while (!file.eof())
    {
        file >> line;
        goodword = true;
        if (islower(line[0]))
        {
            for (string::size_type i = 0; i < line.size(); i++)
            {
                if (!(islower(line[i])))
                {
                    goodword = false;
                }
            }
            if (goodword) {
                words.push_back(line);
            }
        }
        file >> ws;
    }
    file.close();
}
void fillMapWithChar(int size, char** arr2D)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr2D[i][j] = 63;
        }
    }
}
void displayMap(char** arr2D, int size)
{
    cout << "\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << arr2D[i][j];
        }
        cout << "\n";
    }
}
void fillMap(int length, char** arr2D)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (!((arr2D[i][j]) >= 97 && arr2D[i][j] <= 122))
            {
                arr2D[i][j] = char(generateNumber(97, 123));
            }
        }
    }
}
double generateNumber(int x, int y) //generates int (x, y-1)
{
    std::uniform_real_distribution<double> distribution(x, y);  // produces random number in range x <= # < y
    std::random_device rd;										//generates a sequence of uniformly distributed random numbers(not pseudo random)
    std::default_random_engine generator(rd());					//default random engine generates pseudo random numbers but since we combined them this is truly random
    return distribution(generator);
}
bool placeWord(string s, char** arr2D, int length)
{
    int x, y, orientation;
    int tries = 0;
    const int MAX_TRIES = 1000;
    do {
        x = int(generateNumber(0, length));
        y = int(generateNumber(0, length));
        orientation = int(generateNumber(0, 8));// 0 is up, 7 is up to right
        tries++;
    } while (checkLengthAndFit(s, x, y, orientation, arr2D, length) 
        == false && tries < MAX_TRIES);
    if (tries < MAX_TRIES)  //place word
    {

        copyWordIntoArray(s, x, y, orientation, arr2D);
        return true;
    }
    else
        return false;
}
void copyWordIntoArray(string s, int x, int y, int o, char** arr2D)
{
    for (int i = 0; i < int(s.size()); i++)
    {
        arr2D[y][x] = s[i];
        if (o == 0 || o == 1 || o == 7)
        {
            y--;
        }
        if (o == 3 || o == 4 || o == 5)
        {
            y++;
        }
        if (o == 1 || o == 2 || o == 3)
        {
            x++;
        }
        if (o == 5 || o == 6 || o == 7)
        {
            x--;
        }
    }
}
bool checkLengthAndFit(string s, int x, int y, int o, char** arr2D,
    int length)
{
    string::size_type spacesUntilBoundry = 0;
    if (o == 0)  //if pointing up
    {
        for (int i = y; i >= 0 && spacesUntilBoundry < s.size(); i--)
        {
            if (!(s[spacesUntilBoundry] == arr2D[i][x] || arr2D[i][x]
                == '?'))//if the space not is the same or is not empty
            {
                return false;
            }
            spacesUntilBoundry++;
        }
    }
    if (o == 4)  //if pointing down
    {
        for (int i = y; i < length && spacesUntilBoundry < s.size(); i++)
        {
            if (!(s[spacesUntilBoundry] == arr2D[i][x] || arr2D[i][x] ==
                '?'))//if the space not is the same or is not empty
            {
                return false;
            }
            spacesUntilBoundry++;
        }
    }
    if (o == 2)  //if pointing right
    {
        for (int i = x; i < length && spacesUntilBoundry < s.size(); i++)
        {
            if (!(s[spacesUntilBoundry] == arr2D[y][i] || arr2D[y][i] ==
                '?'))//if the space not is the same or is not empty
            {
                return false;
            }
            spacesUntilBoundry++;
        }
    }
    if (o == 6)  //if pointing left
    {
        for (int i = x; i >= 0 && spacesUntilBoundry < s.size(); i--)
        {
            if (!(s[spacesUntilBoundry] == arr2D[y][i] || arr2D[y][i] ==
                '?'))//if the space not is the same or is not empty
            {
                return false;
            }
            spacesUntilBoundry++;
        }
    }
    if (o == 1)  //if up&right
    {
        int i, j;
        for (i = x, j = y; i < length && j >= 0 && spacesUntilBoundry < 
            s.size(); i++, j--)
        {
            if (!(s[spacesUntilBoundry] == arr2D[j][i] || arr2D[j][i] ==
                '?'))//if the space not is the same or is not empty
            {
                return false;
            }
            spacesUntilBoundry++;
        }
    }
    if (o == 3)  //if down&right
    {
        int i, j;
        for (i = x, j = y; i < length && j <= 0 && spacesUntilBoundry <
            s.size(); i++, j++)
        {
            if (!(s[spacesUntilBoundry] == arr2D[j][i] || arr2D[j][i] == '?'))//if the space not is the same or is not empty
            {
                return false;
            }
            spacesUntilBoundry++;
        }
    }
    if (o == 5)  //if down&left
    {
        int i, j;
        for (i = x, j = y; i >= 0 && j < length && spacesUntilBoundry < 
            s.size(); i--, j++)
        {
            if (!(s[spacesUntilBoundry] == arr2D[j][i] || arr2D[j][i] ==
                '?'))//if the space not is the same or is not empty
            {
                return false;
            }
            spacesUntilBoundry++;
        }
    }
    if (o == 7)  //if up&Left
    {
        int i, j;
        for (i = x, j = y; i >= 0 && j >= 0 && spacesUntilBoundry < 
            s.size(); i--, j--)
        {
            if (!(s[spacesUntilBoundry] == arr2D[j][i] || arr2D[j][i]
                == '?'))//if the space not is the same or is not empty
            {
                return false;
            }
            spacesUntilBoundry++;
        }
    }
    if (spacesUntilBoundry == s.length())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool checkForMatch(char** arr2D, string word, int x, int y, int o, int length)
{
    //x--;
    //y--;
    if (x < 0 || x >= length || y < 0 || y >= length)
        return false;
    for (int i = 0; i < int(word.length()); i++)
    {
        if (!(toupper(word[i]) == toupper(arr2D[y][x])))
        {
            return false;
        }
        if (o == 0 || o == 1 || o == 7)
        {
            y--;
        }
        if (o == 3 || o == 4 || o == 5)
        {
            y++;
        }
        if (o == 1 || o == 2 || o == 3)
        {
            x++;
        }
        if (o == 5 || o == 6 || o == 7)
        {
            x--;
        }
    }
    return true;
}
