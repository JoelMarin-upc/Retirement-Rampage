#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include <vector>
#include <Player.h>

class TurnManager : public GameObject {
private:
	int playerNum;
	bool ended = false;

public:
	int currentPlayer = 0;
	std::vector<Player*> playerList;
	TurnManager(int playerNum) : GameObject(), playerNum(playerNum) { playerList = std::vector<Player*>(playerNum); }
	void AddPlayer(Player* player);
	void Start();
	void End();
	void CheckTurn();
	void Update() override;
	void Draw() override;
};
#endif