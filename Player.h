//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_PLAYER_H
#define FIVECROWNS_PLAYER_H



#include "CardCollection.h"
#include "ISave.cpp"
#include <iostream>
#include <algorithm>
class Player {
public:
    Player();
	virtual bool playGame() = 0; 
    void setCard(CardInterface* card);
    void setName(string name);
	void setSaveGameCallback(Save* iSave);
	void setPlayerHand(CardCollection* hand);
	void setScore(int score); 
	void addToScore(int score);
    CardCollection* getHand() const;
    string getName();
	void playerGoOut(bool hasToGoOut); 
	void showDrawAndDiscardPile(); 
	void showHand();
	int getScore();
	~Player();
protected:
    CardCollection* hand;
	string name;
	Save* iSave;
    int score = 0;
	bool haveToGoOut = false;
};


#endif //FIVECROWNS_PLAYER_H
