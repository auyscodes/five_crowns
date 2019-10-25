#pragma once
#include <string>
class Save {
public:
	/*
	Function Name: saveGame
	Purpose: Save the game
	Parameters: filename, name of the file where serialized data is saved
	Return Value: bool, true if successful
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	virtual bool saveGame(std::string filename) = 0;
};