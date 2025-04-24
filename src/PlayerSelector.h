#ifndef PLAYERSELECTOR_H
#define PLAYERSELECTOR_H

#include "raylib.h"  
#include <string> 
#include <vector> 
#include <iostream>
#include "Player.h"
#include "TurnManager.h"



class PlayerSelector : public GameObject {
public:
	int size = 5;
	std::vector<Player> wormsList;
	//PlayerSelector();

	void Update() override;
};

#endif