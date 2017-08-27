/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind
*/

#pragma once
#include <string>

//make the syntax unreal friendly
using FString = std::string;
using int32 = int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Input_Size,
	Not_Lowercase
};

enum class EResetStatus
{
	OK,
	No_Hidden_Word
};

class FBullCowGame
{
public:
	FBullCowGame();
	
	//game flow
	void ResetGame();
	void PrintIntro();
	bool AskToPlayAgain();
	
	//game processing
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	//counts bulls & cows and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);
	
	//getters & setters
	void SetMyCurrentTry(int32);
	int32 GetMyCurrentTry() const;
	int32 GetMyMaxTries() const;
	int32 GetHiddenWordLength() const;


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	bool isLowerCase(FString) const;
	bool isIsogram(FString) const;
};