/*this holds the methods for the game but isn't meant to interact with the user*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>

//to make the syntax unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

//constructor
FBullCowGame::FBullCowGame()
{
	ResetGame();
}

//game flow

void FBullCowGame::ResetGame()
{
	MyCurrentTry = 1;
	bGameWon = false;
	const FString HIDDEN_WORD = "planet"; //this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	return;
}

void FBullCowGame::PrintIntro()
{
	std::cout << "Welcome to BullsAndCows.\n";
	std::cout << "Can you guess the " << GetHiddenWordLength() << " letter isogram Im thinking of?\n";

	return;
}

bool FBullCowGame::AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FString Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

//game processing
bool FBullCowGame::IsGameWon() const
{
	return bGameWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!isIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!isLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Input_Size;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


//receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	//loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length();
	for (int32 HWChar=0; HWChar< WordLength; HWChar++)
	{
		//compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[HWChar])
			{
				if (HWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameWon = true;
	}

	return BullCowCount;
}




//getters & setters

void FBullCowGame::SetMyCurrentTry(int32 CurrentTry)
{
	MyCurrentTry = CurrentTry;
	return;
}


int32 FBullCowGame::GetMyCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetMyMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,5}, {5,6}, {6,7} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isLowerCase(FString Word) const
{
	if (Word.length() == 0)
	{
		return true;
	}
	for (auto Letter : Word)
	{
		if (Letter != '\0' && Letter != ' ' && Letter != '\t')
		{
			if (!islower(Letter))
			{
				return false;
			}
		}
	}
	return true;
}


bool FBullCowGame::isIsogram(FString Word) const
{
	TMap<char, bool> LetterSeen;
	if (Word.length() <= 1)
	{
		return true;
	}
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		LetterSeen[Letter] = true;
	}
	return true;
}


