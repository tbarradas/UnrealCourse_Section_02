#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

/*
This is the console executable that makes use of the BullCowGame class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.

*/

//to make syntax unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes 
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText);
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game which we reuse across games

//the entrypoint for our app
int main()
{
	do
	{
		BCGame.PrintIntro();
		PlayGame();
	} while (BCGame.AskToPlayAgain());
	//repeat the guess back to them
	std::cout << std::endl;
	
	return 0;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.ResetGame();
	//get a defined number of guesses from the player
	int32 MaxTries = BCGame.GetMyMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetMyCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		PrintGuess(Guess);
		std::cout << std::endl;
	}
	PrintGameSummary();

	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "GRATS!!! You've won!" << std::endl << std::endl;
	}
	else
	{
		std::cout << "Nope. You lost." << std::endl << std::endl;
	}
	return;
}

//Prints the game introduction

//loop until the user inputs a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess;
	do
	{
		int32 CurrentTry = BCGame.GetMyCurrentTry();
		std::cout << "Try #" << CurrentTry << " of " << BCGame.GetMyMaxTries() << ". Enter your guess: ";
		Guess = "";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Input_Size:
			{
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word!\n";
				break;
			}
			case EGuessStatus::Not_Isogram:
			{
				std::cout << "Please enter a valid isogram! An isogram is a word with no repeating letters! \n";
				break;
			}
			case EGuessStatus::Not_Lowercase:
			{
				std::cout << "Please input the word fully in lowercase!\n";
				break;
			}
			default:
			{
				
			}
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintGuess(FText Guess)
{
	std::cout << std::endl << "Your guess was " << Guess << std::endl;
	
	return;
}

