#pragma once
#include "DataLayer.h"
#include "CardInterface.h"

/*
	Class that helps in serialization
	Dumps value from dataLayer
	Loads value in dataLayer
*/
class Serialization {
public:

	static bool saveInFile(DataLayer* dataLayer, string filename);
	static bool loadFromFile( string filename,  DataLayer* dataLayer);
	static void split(const string& str, vector<string>&tokens, char delim = ' '); // default is space
private:
	static void parseScoreAndHandLines(ifstream& inputFile, int&score, vector<string>&cards);
	static CardInterface* convertToCard(string crd);
	static vector<CardInterface*> convertToCollection(string cards);
};

