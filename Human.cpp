//
// Created by nbhat on 9/15/2019.
//

#include "Human.h"
#include "DiscardPile.h"
#include "DrawPile.h"
#include "Computer.h"
#include "Round.h"
/*
Function Name: playGame
Purpose: Allows player's to play the game by displaying options and 
		executing functions. 
Parameters: face, number representing joker i.e 1 in joker J1
Return Value: bool, true if player clicks the option to go out.
Local Variables: none
Algorithm: none
Assistance Received: none

*/
bool Human::playGame() {
	cout << "--------------------Human Playing--------------" << endl;
	cout << " I am " << this->name << endl;
	showDrawAndDiscardPile();
	showHand();
	while (true) {
		cout << "-----------------Player Menu--------------------" << endl;
		cout << "1. Save the game" << endl;
		cout << "2. Make a move" << endl;
		cout << "3. Ask for help (go out/ keep discard pile card/ draw new) ?" << endl; // discard
		cout << "4. Quit the game" << endl;

		cout << "Enter option : ";
		int option;
		cin >> option;

		while (!cin || option < 1 || option>4) {
			cout << "Please enter valid integer option: ";
			cin.clear();
			cin.ignore();
			cin >> option;

		}
		

		switch (option) {
		case 1: {
			cin.clear();
			cin.ignore();
			string filename;
			do {
				cout << "Enter filename : ";
				getline(cin, filename);
			} while (filename.empty());
			if (iSave != NULL) {
				// iSave returns boolean
				// Currently does nothing if it fails
				iSave->saveGame(filename);
			}
			
			exit(EXIT_SUCCESS);
		}
			  break;
		case 2: {
			bool flag = moveHelper(); // flag true means user wants to go out
			if (flag) return true;
			return false;
		}
			  break;
		case 3: {
			cout << "Asking for help" << endl;
			Computer::helpPick(*this->hand); // change this hardcoded int
		}
			  break;
		case 4: {
			exit(EXIT_SUCCESS);
		}
			  break;
		default:
			exit(EXIT_FAILURE); // might need to change this later

		}
	}
	
}
/*
Function Name: moveHelper
Purpose: To allow the user the options to throw card, throw  card and go out
		or make a move
Parameters: none
Return Value: bool, returns true if the user wants to go out after throwing 
	the card
Local Variables: pickedCard, reference to pointer to the card picked by user
Algorithm: 
		1. if the user decides to go out without picking any card then return true
		2. Otherwise Provide the user option to throw card, throw card and go out
			and ask for help
Assistance Received: none

*/
bool Human::moveHelper() {
	
	showDrawAndDiscardPile();
	showHand();
	CardInterface* pickedCard;
	CardCollection hand_before_picking = *(this->hand); // copies curr hand

	bool _getCardOrGoOut = getCardOrGoOut(pickedCard);
	if (_getCardOrGoOut) return true;
	
	int option;
	while (true) {
		cout << "1. Throw card" << endl;
		cout << "2. Throw card and Go Out " << endl;
		cout << "3. Ask for help, which card to throw? " << endl;
		do {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Selection options (e.g 1 ) : ";
			cin >> option;

		} while ((option <= 0) || (option >= 4));

		switch (option) {
		case 1: {
			
			showHand();
			throwCardAtIndex();
			return false;
		}	
			break;
		case 2: {
			showHand();
			throwCardAtIndex();
			return true;
		}
			  break;
		case 3: {
			Computer::helpThrow(hand_before_picking, pickedCard); 
		}
			  break;
			   
		default:
			exit(EXIT_FAILURE);
		}
	}
	
}


/*
Function Name: throwCardAtIndex
Purpose: Ask the user which card they want to throw and throw that card
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Human::throwCardAtIndex() {
	int index;
	do {
		cout << "1. Enter the index of card that you want to throw: " << endl;
		
		// cout << "Enter option (e.g. 0) : ";
		cin >> index;
		if (cin.fail()) { // if user enter's chars option is set to 0
			index = -1;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (index<0 || index>hand->getSize()-1);
	cout << "card thrown: " << hand->getCardAt(index)->toString() << endl;
	DiscardPile::getInstance()->addFront(hand->popCardAt(index));
}
/*
Function Name: getCardOrGoOut
Purpose: Ask the user for option to get card from drawPile, discardPile or go out
	without picking any card
Parameters: pickedCard reference to pointer to the card that user picks
Return Value: bool, true if the user chooses to go out without picking
Local Variables: none
Algorithm: none
Assistance Received: none

*/
bool Human::getCardOrGoOut(CardInterface*& pickedCard)
{
	
	 

	int option;
	cout << "1. Get card from DrawPile" << endl;
	cout << "2. Get card from DiscardPile" << endl;
	cout << "3. Go out " << endl;

	do {
		cin.clear();
		cin.ignore(numeric_limits < streamsize>::max(), '\n');
		cout << "Enter option (e.g 1) : ";
		cin >> option;
	} while ((option <= 0) || (option >= 4));
	switch (option) {
	case 1: {
		hand->addFront(DrawPile::getInstance()->popFront());
		pickedCard = hand->getFront();
	}
		  

		  break;
	case 2: {
		hand->addFront(DiscardPile::getInstance()->popFront());
		pickedCard = hand->getFront();
	}
		  
		  break;
	case 3:
		return true;
	default:
		exit(EXIT_FAILURE);
		
	}
	return false;
}

