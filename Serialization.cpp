#include "Serialization.h"
#include "Computer.h"
#include "Human.h"
#include "Card.h"
#include "Joker.h"
#include "DrawPile.h"
#include "DiscardPile.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

/*
Function Name: saveInFile
Purpose: Save game state in a file
Parameters:
			dataLayer, pointer to DataLayer class. dataLayer is the model in MVC
			of the game.
			filename, name of the file where serialization is saved
Return Value: bool, true if saving in file was successful. otherwise false.
Local Variables:
			outputFile, an instance of ofstream object used for saving in a file.
Algorithm: none
Assistance Received: none

*/

bool Serialization::saveInFile(DataLayer* dataLayer, string filename)
{
	ofstream outputFile;
	outputFile.open(filename);
	if (!outputFile) {
		cerr << "Error while saving file" << endl;
		return false;
	}
	outputFile << "Round: " << dataLayer->getRound() << endl;
	outputFile << endl;
	outputFile << "Computer: " << endl;
	outputFile << "\tScore: " << dataLayer->getPlayers()->at(dataLayer->getComputerPlayerIndex())->getScore() << endl;
	outputFile << "\tHand: " << dataLayer->getPlayers()->at(dataLayer->getComputerPlayerIndex())->getHand()->toString() << endl;
	outputFile << endl;
	outputFile << "Human: " << endl;
	outputFile << "\tScore: " << dataLayer->getPlayers()->at(dataLayer->getHumanPlayerIndex())->getScore() << endl;
	outputFile << "\tHand: " << dataLayer->getPlayers()->at(dataLayer->getHumanPlayerIndex())->getHand()->toString() << endl;
	outputFile << endl;
	outputFile << "Draw Pile: " << dataLayer->getDrawPile()->toString() << endl;
	outputFile << endl;
	outputFile << "Discard Pile: " << dataLayer->getDisCardPile()->toString() << endl;
	outputFile << endl;
	outputFile << "Next Player: " << dataLayer->getNextPlayer() << endl;
	return true;
}

/*
Function Name: loadFromFile
Purpose: Load game state from serialization file
Parameters:
			dataLayer, pointer to DataLayer class. dataLayer is the model in MVC
			of the game.
			filename, name of the file where serialization is saved
Return Value: bool, true if loading from file was successful. otherwise false.
Local Variables:
			outputFile, an instance of ifstream object used for loading data from file.
			line, string representing each line in the serialization file
			tokens, vector of string token. a token is a value present in each line in
			serialization file that is separated by ":" delimiter.
Algorithm: 
		Splits each line with ":" delimiter in a vector using split function.
		If the first half of the delimeter matches keywords Round, Computer, Human, etc. , 
		then parases the second half accordingly.
		
Assistance Received: none

*/
bool Serialization::loadFromFile( string filename,  DataLayer* dataLayer) {

	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile) {
		cerr << "!!!!!!!!!!Unable to open file!!!!!!!!!!!!!!!!" << endl;
		while (!inputFile) {
			cout << "1. Enter file name again " << endl;
			cout << "2. Go back to main menu" << endl;
			
			// used for validating input
			int option;
			do {
				cout << "Enter option (eg. 1) : ";
				cin >> option;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			} while ((option <= 0) || (option >= 3));
			
			if (option == 1) {
				cout << "Enter file name: ";
				getline(cin, filename);
				inputFile.open(filename);
			}
			else {
				return false;
			}
		




		}
		
	}
	// stores each line in the serialization file
	string line;
	
	while (getline(inputFile, line)) {
		
		vector<string> tokens;
		split(line, tokens, ':');
		
		if (tokens.front() == "Round") {
			dataLayer->setRound(stoi(tokens.back()));
		}
		if (tokens.front() == "Computer") {
			int score;
			vector<string> cards;
			parseScoreAndHandLines(inputFile,score,cards);
			
			Computer* computer = new Computer();
			for (auto card : cards) {
				CardInterface* elem = convertToCard(card);
				computer->setCard(elem);
			}
			
			
			computer->setScore(score);
			computer->setName(tokens.front());
			dataLayer->getPlayers()->push_back(computer);
			dataLayer->setComputerPlayerIndex(dataLayer->getPlayers()->size() - 1);
			
			
		}
		if (tokens.front() == "Human") {
			int score;
			vector<string> cards;
			parseScoreAndHandLines(inputFile, score, cards);
			
			Human* human = new Human();
			for (auto card : cards) {
				CardInterface* elem = convertToCard(card);
				
				human->setCard(elem);
			}
			human->setScore(score);
			human->setName(tokens.front());
			dataLayer->getPlayers()->push_back(human);
			dataLayer->setHumanPlayerIndex(dataLayer->getPlayers()->size() - 1) ;
		}

		if (tokens.front() == "Draw Pile") {
			dataLayer->getDrawPile()->setCollectionVector(convertToCollection(tokens.back()));
		}
		if (tokens.front() == "Discard Pile") {
			dataLayer->getDisCardPile()->setCollectionVector(convertToCollection(tokens.back()));
		}
		if (tokens.front() == "Next Player") {
			
			istringstream iss(tokens.back());
			string token;
			while (iss >> token) {
				if (token == "Human") {
					dataLayer->setNextPlayerIndex(dataLayer->getHumanPlayerIndex());
				}
				if (token == "Computer") {
					dataLayer->setNextPlayerIndex(dataLayer->getComputerPlayerIndex());
				}
			}
			
		}
	}
	
	return true;
}


/*
Function Name: split
Purpose: splitting a string to tokens using delim
Parameters:
			str, string to be splitted
			tokens, reference to vector where tokens are saved
			delim, character that separates str into tokens
Return Value: none
Local Variables:
			none
Algorithm:
			1. Find the position of  delim.
			2. Make a substring using that delim
			3. Repeat the process.
Assistance Received: Stack Overflow

*/
void Serialization::split(const string& str, vector<string>& tokens, char delim)
{
	int current, previous = 0;
	
	current = str.find(delim);
	while (current != std::string::npos) {
		tokens.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	tokens.push_back(str.substr(previous, current - previous));
}

/*
Function Name: parseScoreAndHandLines
Purpose: 
		Parses the score and hand lines of human and computer stored in serialization file
		Note: This is just a helper function.
Parameters:
			inputFile, reference to inputStream Object 
			score, score of player or computer stored in file
			cards, string representation of cards stored in file
Return Value: none
Local Variables:
			none
Algorithm:
			None
Assistance Received: Stack Overflow

*/
void Serialization::parseScoreAndHandLines(ifstream&inputFile, int& score, vector<string>&cards)
{
	
	string score_line;
	
	
	if (getline(inputFile, score_line)) {
		
		vector<string> score_tokens;
		split(score_line, score_tokens, ':');
		score = stoi(score_tokens.back());

	}

	string hand_line;
	if (getline(inputFile, hand_line)) {
		
		
		vector<string> hand_tokens;
		
		split(hand_line, hand_tokens, ':');
		
		
		istringstream iss(hand_tokens.back());
		string card;
		while (iss >> card) {
			cards.insert(cards.begin(), card);
		}
		
	}
}
/*
Function Name: convertToCard
Purpose: Converts a card represented as string to Object of type Card Or Joker. Desirializes a card to joker or normal card
Parameters:
			_card, string representation of card stored in serialization file
Return Value: pointer to abstract class CardInterface. Since cards can be joker or normal card
Local Variables:
			elem, Pointer to CardInterface. A new Card Or Joker is stored
Algorithm:
			Uses CardInterface's static isJoker function to check if card 
			is a joker. If it is a joker creates a new
			create a new Joker object. otherwise create a new Card object.
			Extract the suit and face information from _card string and set face and suit.
Assistance Received: none

*/

CardInterface* Serialization::convertToCard( string _card)
{
	if (!CardInterface::isJoker(_card)) {
		CardInterface* elem = new Card();
		string suit = string(1, _card.back());
		elem->setSuit(suit);
		_card.pop_back();
		elem->setFace(_card);
		return elem;
	}
	else {
		CardInterface* elem = new Joker();
		string face = string(1, _card.back());
		elem->setFace(face);
		_card.pop_back();
		elem->setSuit(_card);
		return elem;
	}
	
}
/*
Function Name: convertToCollection
Purpose: Deserializes a string of cards separated by space to Joker or Normal Card objects
Parameters:
			cards, string representation of cards stored in serialization file
Return Value: vector of CardInterface pointers. CardInterface is an abstract class which represents a card in a deck
Local Variables:
			collection, vector of CardInterface pointers that is returned
			iss, istringstream object of STL library
Algorithm:	Use iss to get string representation of card from cards parameter
			that was passed in this function. Use convertToCard function
			to convert string of card to get a pointer to base class of Card object or Joker
			
Assistance Received: none

*/
vector<CardInterface*> Serialization::convertToCollection(string cards)
{
	istringstream iss(cards);
	string card;
	vector<CardInterface*> collection;
	while (iss >> card) {
		CardInterface* elem = convertToCard(card);
		collection.push_back(elem);
	}
	return collection;
}


