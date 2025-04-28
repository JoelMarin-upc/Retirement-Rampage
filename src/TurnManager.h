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
	double secondsBetweenTurns = 2;
	double currentBetweenTurnsSeconds = 2;
	bool betweenTurns = false;

public:
	int turns = 1;
	int currentPlayer = 0;
	std::map<int,std::vector<Player*>> playerList;
	TurnManager(int playerNum) : GameObject(), playerNum(playerNum) { playerList = std::map<int, std::vector<Player*>>(playerNum); }
	void AddPlayer(Player* player, int playerNum);
	void Start();
	void End();
	void CheckTurn();
	bool TurnTimePassed();
	bool BetweenTurnTimePassed();
	void Update() override;
	void Draw() override;
	void CheckPlayerHit(Explosion exp);
};
#endif