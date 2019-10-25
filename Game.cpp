//
// Created by nbhat on 9/15/2019.
//

#include "Game.h"
#include "Deck.h"
#include "Round.h"
#include "Human.h"
#include "Computer.h"
#include "DataLayer.h"
#include "Serialization.h"

/*
Function Name: Game
Purpose: Constructor for creating game class. game class represents five crowns game
		Initializes dataLayer member variable as null
		dataLayer is dependent on input of the user
Parameters: none
Return Value: Game object
Local Variables: none
Algorithm: none
Assistance Received: none

*/
Game::Game()
{
	dataLayer = NULL; // I feel this is unnecessary though
}

/*
Function Name: createPlayers
Purpose: Creates human and computer players
Parameters: startPlayerIndex, refrence to player who goes first
			default starting player is human player, toss function changes this value later on new game
			load game sets a different value
			
			humanPlayerIndex, index of human player on the collection of players returned by this function

			computerPlayerIndex, index of the computer player on the collection of players returned 
Return Value: vector of players, represents players in the game
Local Variables: human, object representing human player in the game
				computer, object representing computer player in the game
Algorithm: none
Assistance Received: none

*/
vector<Player*>* Game::createPlayers(int& startPlayerIndex, int&humanPlayerIndex, int&computerPlayerIndex) {
	
    Human* human = new Human();
    human->setName("Human");
	human->setSaveGameCallback(this);
    Computer* computer = new Computer();
    computer->setName("Computer");

    vector<Player*> * players = new vector<Player*>();
    players->insert(players->begin(), computer);
    players->insert(players->begin(), human);

	
	humanPlayerIndex = 0;
	computerPlayerIndex = 1;
	startPlayerIndex = humanPlayerIndex;
	return players;
}
/*
Function Name: execute
Purpose: Provides user with option to start a new game or load game
		
Parameters: none
Return Value: bool, returns false if loading the game fails
Local Variables: none
Algorithm: 1. calls startNew function if the user selects start new game
			2. calls load saved game function if the user selects load saved game
Assistance Received: none

*/
bool Game::execute() {
	cout << "------------Main Menu--------------------" << endl;
	cout << "1. Start new game" << endl;
	cout << "2. Load saved game" << endl;
	
	int option;
	do {
		cout << "Enter option : " ;
		
		cin >> option;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
	} while ((option <= 0) || (option >= 3) );


	
		
	
	switch (option) {
	case 1: {
		startNew();
		// Returning true denotes user completed the game
		return true;
	}
		  break;
	case 2: {
		cout << "-------------------------------" << endl;
		string filename;
		do {
			
			cout << "Enter file name: ";
			
			getline(cin, filename);
			cout << "File name entered was : " << filename << endl;
			
			

		} while (filename.empty());
		dataLayer = new DataLayer();
		if (!loadGame(filename, dataLayer)) return false;
	}
		  break;
	default:
		exit(EXIT_FAILURE);
	}
}
/*
Function Name: loadGame
Purpose: Loads the game stored in file
Parameters:  filename, used by ostream class to determine file's location
			dataLayer, object that stores the state of the game
Return Value: bool true if the loading game was successful
Local Variables: none
Algorithm: 1. if loading from file fails return false
			2. Call dataLayer's isLoadOn function so that round 
				knows that game is resumed from a previous state
Assistance Received: none

*/
bool Game::loadGame(string filename, DataLayer* dataLayer) {
	
	if (!Serialization::loadFromFile(filename, dataLayer)) return false;
	
	dataLayer->turnIsLoadOn(); 
	// not to forget to allow the user to save the loaded game
	dataLayer->getPlayers()->at(dataLayer->getHumanPlayerIndex())->setSaveGameCallback(this); 

	for (int i = dataLayer->getRound(); i <= numRounds; i++) {
		// do not forget to set subsequent rounds 
		dataLayer->setRound(i);
		Round* round = new Round( dataLayer);
		
		round->startGame();
	}
	return true;

}
/*
Function Name: startNew
Purpose: Start a new game
Parameters:  none
Return Value: bool, true if player plays until the end
Local Variables: none
Algorithm: Intialize dataLayer class with values. Loop until last round
Assistance Received: none

*/
bool Game::startNew() {
	// Game starts at round 1
	int startRound = 1;
	// Index of the player who starts first collection of player returned by createPlayers function
	int startPlayerIndex;
	// Index of human player
	int humanPlayerIndex;
	// Index of computer player
	int computerPlayerIndex;
	vector<Player*>* players = createPlayers(startPlayerIndex, humanPlayerIndex, computerPlayerIndex);
	int nextPlayer = toss(humanPlayerIndex, computerPlayerIndex);
	dataLayer = new DataLayer(players, nextPlayer, startRound, humanPlayerIndex, computerPlayerIndex);
	dataLayer->buildCardCollection(); // do not forget this
	for (int i = 1; i <= numRounds; i++) {
		dataLayer->setRound(i);
		Round* round = new Round( dataLayer);
		
		round->startGame();

	}
	return true;
}

/*
Function Name:  start
Purpose: Start game. Entry point for starting new game or loading game
Parameters: none
Return Value: none
Local Variables: none
Algorithm: Execute game in loop. If user plays until the end show winner and losers
Assistance Received: none

*/
void Game::start() {
    
	while (true) {
		// execute returns true if the user plays until the end
		if (execute()) break;
	}
	

	displayWinnerAndLoserScore();

}

/*
Function Name:  saveGame
Purpose: Saves the game state in a specific format
	Implementation of ISave.h class's pure virtual function so that player can callback the function
Parameters: filename, used by ostream class to determine file's location
Return Value: true if successfully saved
Local Variables: none
Algorithm: none
Assistance Received: none

*/
bool Game::saveGame(string filename)
{
	
	return Serialization::saveInFile(dataLayer, filename);
	
}

/*
	Function Name:  displayWinnerAndLoserScore
	Purpose: Displays winners and losers of the game and their final scores
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm:	1. Outputs draw if both the players have same score
				2. Outputs Human has won if the human player has lower score
				3. Outputs Computer has won if the computer player has lower score
	Assistance Received: none

*/
void Game::displayWinnerAndLoserScore() {

	cout << "\n-------------------------------Game Ended ----------------------------------\n";
	cout << "Final scores :- " << endl;
	string p1_name = dataLayer->getPlayers()->at(0)->getName();
	string p2_name = dataLayer->getPlayers()->at(1)->getName();
	int p1_score = dataLayer->getPlayers()->at(0)->getScore();
	int p2_score = dataLayer->getPlayers()->at(1)->getScore();
	cout << p1_name  << " 's score : " << p1_score << endl;
	cout << p2_name << " 's score : " << p2_score << endl;
	if (p1_score == p2_score) {
		cout << "Game Draw " << endl;
	}
	else if (p1_score < p2_score) {
		cout << p1_name << " won" << endl;
	}
	else {
		cout << p2_name << " won" << endl;
	}
	
}

/*
	Function Name:  toss
	Purpose: Determines who gets to play first in the starting round
	Parameters: humanPlayerIndex, index of the human player in collection of players stored in dataLayer
				computerPlayerIndex, index of the computer player in collection of players	stored in dataLayer	
	Return Value: index of the winner of the toss
	Local Variables: max =1, represents head before the toss
					min = 0, represent tail before the toss
	Algorithm: none
	Assistance Received: none

*/
int Game::toss(int humanPlayerIndex, int computerPlayerIndex) {
	cout << "--------Toss--------- " << endl;
	cout << " 0 for tail" << endl;
	cout << " 1 for head" << endl;

	int option;
	do {
		cout << "Enter option (e.g. 0) : ";
		cin >> option;
		if (cin.fail()) { // if user enter's chars option is set to 0
			option = -1;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
		};

	} while ((option <= -1) || (option >= 2));
	
	int	max = 1; // head
	int min = 0; // tail
	int toss = rand() % (max - min + 1) + min;
	if (toss == 0) cout << "It was a tail" << endl;
	if (toss == 1) cout << "It was a head" << endl;
	if (toss == option) {
		cout << "Human won the toss" << endl;
		return humanPlayerIndex;
	}
	cout << "Computer won the toss" << endl;
	return computerPlayerIndex ;
	


}

/*
	Function Name:  Destructor
	Purpose: Delete dataLayer object that was initialized
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

*/
Game::~Game()
{
	delete dataLayer;
}