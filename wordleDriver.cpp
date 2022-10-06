#include "wordle.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string words[5];
    int longestWord;
    vector<string> wordlist;
    getWordList(wordlist);
    for (int i = 0; i < 5; i++)
    {
        words[i] = getWord(wordlist);
        if (i == 0 || int(words[i].length()) > longestWord)
        {
            longestWord = int(words[i].length());
        }
    }
    int length = longestWord;
    string::size_type l = length;
    // declaration
    char* data = nullptr, ** arr2D = nullptr;
    // allocation
    data = new(nothrow) char[length * length];    // allocate linearized space
    if (data != nullptr)
    {
        arr2D = new(nothrow) char* [length];   // allocate row pointers
    }
    if (arr2D != nullptr)
    {
        for (size_t r = 0; r != l; r++)    // aim row pointers
        {
            arr2D[r] = data + r * length;
        }

        // access (in a pair of for loops)
        //arr2D[r][c]
    }
    fillMapWithChar(length, arr2D);
    for (int i = 0; i < 5; i++)
    {
        bool didWordPlace;
        didWordPlace = placeWord(words[i], arr2D, length);
        if (!didWordPlace) {
            i--;
        }
    }
    fillMap(length, arr2D);
    int points = 0;
    string matches[5];
    while (!(points == 5))
    {
        cout << "Words to find:\n";
        for (int i = 0; i < 5; i++)
        {
            if (!(words[i] == matches[0] || words[i] == matches[1] ||
                words[i] == matches[2] || words[i] == matches[3] ||
                words[i] == matches[4]))
                cout << words[i] << endl;
        }
        displayMap(arr2D, length);
        cout << "\nPoints: " << points << "\n";
        bool isMatch = false;
        while (!isMatch)
        {
            cout << "\nEnter found word: ";
            string responseFoundWord;
            cin >> responseFoundWord;
            cout << "Enter orientation(0 is N, 7 is NW): ";
            int foundO;
            cin >> foundO;
            cout << "Enter x cord(starts at 0): ";
            int foundX;
            cin >> foundX;
            cout << "Enter y cord(starts at 0): ";
            int foundY;
            cin >> foundY;
            isMatch = checkForMatch(arr2D, responseFoundWord, foundX, foundY, 
                foundO, length);
            if (isMatch) {
                matches[points] = responseFoundWord;
                for (int i = 0; i < int(responseFoundWord.size()); i++)
                {
                    responseFoundWord[i] = char(toupper(responseFoundWord[i]));
                }
                copyWordIntoArray(responseFoundWord, foundX, foundY,
                    foundO, arr2D);
                points++;
            }
            if (!isMatch)
                cout << "INCORRECT. Try Again. Points: " << points;
        }
        cout << "CORRECT. Points: " << points;

        cout << "\n_____________________________________________________________\n";
    }
    cout << "Congratulations!!! YOU WON!!!\n";
    delete[] arr2D;
    delete[] data;
    return 1;
}
