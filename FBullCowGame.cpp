#include <iostream>
#include <time.h>
#include <algorithm>
#include <map>
#include <cmath>
#include "FBullCowGame.h"

//to make the syntax more Unreal like.
#define TMap std::map
using FString = std::string;
using int32 = int;

//constants
const FString GUESS_WORDS[] = { "strong", "human", "tech", "vector", "heart", "toe", "jacket", "fleasoup", "rocket", "space" };


//constructor, nothing to do here atm.
FBullCowGame::FBullCowGame() {
	
}

/*
 * Get maxguesses.
 * skipping the map structure for this and replacing it with a mathematical function
 */
int32 FBullCowGame::getMaxGuesses(FString word) const {
	int32 wl = word.length();
	int32 ret = round(wl * 2 + wl);

	return ret;
}

FString FBullCowGame::getNextWord() const {
	int32 numberOfWords = (sizeof(GUESS_WORDS) / sizeof(*GUESS_WORDS));
	srand(time(NULL));
	FString GuessingWord = GUESS_WORDS[rand() % numberOfWords];

	//could remove potential non isogram words by skipping over them and fetching the next word here.
	// to prevent bad userconfig input.

	return GuessingWord;
}

//the play loop
void FBullCowGame::playIt() const {
	bool moreGames = false;
	FString GuessingWord;

	do {
		
		GuessingWord = getNextWord();
		printintro(GuessingWord);

		doTheGuessing(GuessingWord);

		moreGames = playAgain();
	} while (moreGames);
}

//returns the number of bulls and cows in the bbc struct
BBC FBullCowGame::countBC(FString word, FString guess) const {
	BBC ret;

	ret.bulls = getBulls(word, guess);
	ret.cows = getCows(word, guess);

	return ret;
}
//returns the number of cows from the guessed word.
int32 FBullCowGame::getCows(FString word, FString guess) const {
	int32 ret = 0;
	int32 ctr = 0;
	int32 iCtr = 0;
	char wc = ' ';
	char gc = ' ';

	//for each letter in the word , get the cows for that letter, and add it to the total sum of cows.
	for (ctr = 0; ctr < word.length() && ctr < guess.length(); ctr++) {
		wc = word[ctr];
		ret = ret + getCowsForLetter(guess, wc, ctr);
	}
	
	return ret;
}

//returns the number of cows for this letter in this word.
int32 FBullCowGame::getCowsForLetter(FString word, char letter, int32 index) const {
	int32 ret = 0;

	for (int32 iCtr = 0; iCtr < word.length(); iCtr++) {
		
		if (word[iCtr] == letter && index != iCtr) {
			ret++;
		}
	}

	return ret;
}

// returns the number of bulls the guess contains
int32 FBullCowGame::getBulls(FString word, FString guess) const {
	int32 ret = 0;
	int32 ctr = 0;
	char wc = ' ';
	char gc = ' ';


	for (ctr = 0; ctr < word.length() && ctr < guess.length(); ctr++) {
		wc = word[ctr];
		gc = guess[ctr];

		if (wc == gc) {
			ret++;
		}
	}

	return ret;
}

//prompts the user to guess, and returns the guess made.
FString FBullCowGame::getGuess() const {
	FString guess;
	std::cout << "Guess the word!!!::: -->>>";
	std::getline(std::cin, guess);

	return guess;
}

//returns true if the guess was correct
bool FBullCowGame::isCorrect(FString guess, FString word) const {
	bool CorrectGuess = (guess.compare(word) == 0);

	return CorrectGuess;
}

//prints the feedback after a valid guess.
void FBullCowGame::printBullsAndCows(FString guess, FString word, bool CorrectGuess, int32 guesses, int32 maxGuesses) const {
	BBC counts = countBC(guess, word);

	if (!CorrectGuess) {
		std::cout << "nuhu.....\n.. you get " << counts.cows << " COWS, and " << counts.bulls << " bulls for it though ;)\n";
		std::cout << "(btw you have only " << maxGuesses - guesses << " guesses left...)";
	}
	std::cout << "\n\n\n";
}

//prints the ending of the game.
void FBullCowGame::printGameEnding(bool CorrectGuess, int32 Guesses, int32 maxGuesses) const {
	if (Guesses == maxGuesses && CorrectGuess) {
		std::cout << "TRALLALALAAAA YOU GOT IT ON THE LAST GUESSS!!!! EXCELLENT! :D\n";
	}
	else if (CorrectGuess) {
		std::cout << "Correct! Gratz! :D\n";
	}
	else {
		std::cout << "Bummer!!!!, you suck! (you guessed wrong)\n";
	}
}

//promts the user asking if it wants to play more games, and returns true if it does.
bool FBullCowGame::playAgain() const {
	FString resp = "";

	std::cout << "Play one more game? (y/n)";
	std::getline(std::cin, resp);

	return resp[0] == 'y';
}

//does the complete guessing loop for the given guessword
void FBullCowGame::doTheGuessing(FString word) const {
	int32 Guesses = 0;
	bool CorrectGuess = false;
	FString Guess = "";
	int32 maxGuesses = getMaxGuesses(word);
		
	while (Guesses < maxGuesses && !CorrectGuess) {

		Guess = getValidGuess(word);
		CorrectGuess = isCorrect(Guess, word);

		Guesses++;

		printBullsAndCows(Guess, word, CorrectGuess, Guesses, maxGuesses);
	}

	printGameEnding(CorrectGuess, Guesses, maxGuesses);
}


//prompts the user to guess until it has made a valid guess.
FString FBullCowGame::getValidGuess(FString word) const {
	
	FString guess = "";
	EWordStatus status;

	do {
		guess = getGuess();
		
		status = evaluateGuess(guess, word);
		
		printGuessStatus(status);
	} while (status != EWordStatus::OK);

	return guess;
}

//prints the status of the guess. Prints nothing if the guess was valid.
void FBullCowGame::printGuessStatus(EWordStatus status) const {
	switch (status) {
	case EWordStatus::Wrong_Length:
		std::cout << "Your guess didnt have the correct number of letters. We dont count that one.\n";
		break;
	case EWordStatus::Not_Isogram:
		std::cout << "The word is an ISOGRAM. It means no letter appears more than once. Now shape up and redo the guess!\n";
		break;
	case EWordStatus::Not_LowerCase:
		std::cout << "Your guess had some uppercase in it. Guess didnt count, REDO IT!\n";
		break;
	}
}

//returns the status of the guess supplied.
EWordStatus FBullCowGame::evaluateGuess(FString guess, FString word) const {
	EWordStatus ret;

	if (guess.length() != word.length()) {
		ret = EWordStatus::Wrong_Length;
	}
	else if (!isIsogram(guess)) {
		ret = EWordStatus::Not_Isogram;
	}
	else if (isCaps(guess)) {
		ret = EWordStatus::Not_LowerCase;
	}
	else {
		ret = EWordStatus::OK;
	}

	return ret;
}

//returns true if some letter in the guess is Capital (Caps)
bool FBullCowGame::isCaps(FString guess) const {
	bool ret = false;
	for (int32 i = 0; i < guess.length() && !ret; i++) {
		ret = isupper(guess[i]);
	}

	return ret;
}


// Makes all the letters in the string to lowercaps. Uses the Algorithm lib.
// NOT USED, but kept to try to understand it.
FString FBullCowGame::makeLower(FString in) const {
	
	std::transform(in.begin(), in.end(), in.begin(), ::tolower);

	return in;
}

//returns whether or not the word is an isogram (true) or not (false)
bool FBullCowGame::isIsogram(FString word) const {
	bool ret = true;
	TMap<char, int32> mapper;

	for (int32 i = 0; i < word.length() && ret; i++) {
		mapper[word[i]] ++;
		ret = !(mapper[word[i]] >= 2);
	}

	return ret;
}

//prints the intro to the game.
void FBullCowGame::printintro(FString word) const {
	//no Ascii art here, I'm not an artist. ;)
	std::cout << "Welcome to MR JIMPS BUILLS AND COWS!!!!\n\nThis is a superhard guessing game.\n\n";
	std::cout << "I have extracted a " << word.length() << " letter ISOGRAM word from my memory banks.\n\n";
}

