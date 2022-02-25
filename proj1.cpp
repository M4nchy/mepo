/* Name: Christian Walker
   Email: cwalker6@umbc.edu
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

void loadWords(string arr[2315]);
string displayCurrent(string previousGuesses[6], string hintGuesses[6]);
void resetGame(string userPrevGuesses[6], string userHintGuesses[6]);
string guessWord(string mysteryWord, string userGuess, string arr[2315]);
int checkWin(string userGuess, string hiddenWord);
int checkLetter(char userLetter, string hiddenWord);

const char INCORRECT = '_';
const char CORRECT_PLACE = '!';
const char CORRECT_LETTER_INCORRECT_PLACE = '&';


int main() {
  int Counter = 0;
  string wordList[2315];
  string mysteryWord;
  string userGuess;
  string pastGuesses[6];
  string hintGuesses[6];
  resetGame(pastGuesses, hintGuesses);
  cout << "Welcome to UMBC Wordle" << endl;
  loadWords(wordList);
  //cout << wordList << endl;
  cout << "Ok. I am thinking of a word with five letters." << endl;
  mysteryWord = wordList[rand()];
  cout << mysteryWord << endl;
  while (Counter < 6) {
    //guessWord(mysteryWord, userGuess, wordList);
    pastGuesses[Counter] = guessWord(mysteryWord, userGuess, wordList);
    if(checkWin(pastGuesses[Counter], mysteryWord) == 1){
        cout << "Congrats you won!" << endl;
        Counter = 6;
    }
    for(int i = 0; i < 5; i++){
        if(pastGuesses[Counter][i] == mysteryWord[i]){
            hintGuesses[Counter][i] = CORRECT_PLACE;
        }else if(checkLetter(pastGuesses[Counter][i], mysteryWord) == 1){
            hintGuesses[Counter][i] = CORRECT_LETTER_INCORRECT_PLACE;
        }else{
            hintGuesses[Counter][i] = INCORRECT;
        }
    }
    displayCurrent(pastGuesses, hintGuesses);
  }

    Counter++;

  cout << "Thank you!" << endl;
  return 0;
}


void loadWords(string arr[2315]) {
  string word;
  int Counter = 0;
  ifstream inputStream ("proj1_data.txt");
  if(inputStream.is_open()){
    while(inputStream >> word){
        arr[Counter] = word;
        //cout << Counter << word << endl; Used to test where the words were in the array.
        Counter++;
    }

    cout << "Your file was imported!" << endl;
  }else{
      cout << "Unable to open file" << endl;
  }
  inputStream.close();

}

string displayCurrent(string previousGuesses[6], string hintGuesses[6]) {
  for(int i = 0; i < 6; i++){
    if(previousGuesses[i] != ""){
        cout << previousGuesses[i] << endl;
    }
    cout << hintGuesses[i] << endl;
  }
  return "aaaaaatest";
}

string guessWord(string mysteryWord, string userGuess, string arr[2315]) {
  string userInput;
  string userReturn;
  string word;
  bool inList = false;
  char userHint[5];

  do{
      cout << "What word would you like to guess?" << endl;
      cin >> userInput;
      for(int i = 0; i < 2315; i++){
        word = arr[i];
        if(userInput == word){
            inList = true;
        }

      }
      if(inList == false){
        cout << "That word is not in the word list" << endl;
      }
  }while (inList == false);

  return userInput;
}

int checkLetter(char userLetter, string hiddenWord){

    for (int i = 0; i < 5; i++){
        if (userLetter == hiddenWord[i]){
            return 1;
        }
    }
    return 0;
}

int checkWin(string userGuess, string hiddenWord){
    if (userGuess == hiddenWord){
        return 1;
    }else{
        return 0;
    }
}

void resetGame(string userPrevGuesses[6], string userHintGuesses[6]) {
    for(int i = 0; i < 6; i++){
        userPrevGuesses[i] = "";
        userHintGuesses[i] = "-----";
    }
}
