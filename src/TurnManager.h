#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include <vector>
#include <Player.h>

class TurnManager : public GameObject {
private:
	int playerNum;
	bool ended = false;
	double secondsPerTurn = 20;
	double currentTurnSeconds = 20;

public:
	int turns = 1;
	int currentPlayer = 0;
	std::vector<Player*> playerList;
	TurnManager(int playerNum) : GameObject(), playerNum(playerNum) { playerList = std::vector<Player*>(playerNum); }
	void AddPlayer(Player* player);
	void Start();
	void End();
	void CheckTurn();
	bool TurnTimePassed();
	void Update() override;
	void Draw() override;
};
#endif