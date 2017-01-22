/*
* Class to represent the BullCowGame of section of the unreal programming course at Udemy.
* Author: Jimmi Wimmersjö
*
* Unlike the game made in the vid, this class also contains the mainloop of the game,
* as I see no reason for it to be in the actual main function.
* theGame.run() or theGame.play() looks so much better at the level I think.
*
* Hence, the Public interface is very limited. It might get bigger if there are reasons to.
*/

#pragma once
#include <string>


//to make syntax unreal like.
using FString = std::string;
using int32 = int;

struct BBC {
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EWordStatus {
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase
};

class FBullCowGame {

public:
	FBullCowGame() ; // contructor
	bool playAgain() const;
	void playIt() const;

private:
	void doTheGuessing(FString word) const;
	void printintro(FString word) const;
	int32 getCows(FString word, FString guess) const;
	int32 getBulls(FString word, FString guess) const;
	FString getGuess() const;
	bool isCorrect(FString guess, FString word) const;
	void FBullCowGame::printBullsAndCows(FString guess, FString word, bool CorrectGuess, int32 guesses, int32 maxGuesses) const;
	void FBullCowGame::printGameEnding(bool CorrectGuess, int32 Guesses, int32 maxGuesses) const;
	FString FBullCowGame::getValidGuess(FString word) const;
	bool FBullCowGame::isIsogram(FString word) const;
	int32 FBullCowGame::getCowsForLetter(FString word, char letter, int32 index) const;
	BBC FBullCowGame::countBC(FString word, FString guess) const;
	EWordStatus evaluateGuess(FString guess, FString word) const;
	void FBullCowGame::printGuessStatus(EWordStatus status) const;
	FString FBullCowGame::makeLower(FString in) const;
	bool FBullCowGame::isCaps(FString guess) const;
	FString FBullCowGame::getNextWord() const;
	int32 FBullCowGame::getMaxGuesses(FString word) const;
};