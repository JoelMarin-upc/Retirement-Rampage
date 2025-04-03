#include "Game.h"

int Game::bottomY;

std::vector<std::unique_ptr<GameObject>> Game::gameObjects;

bool Game::ended = false;

Player* Game::winner;

void Game::CheckEndGame() {
	if (ended) return;
	TurnManager* turnManager = GetTurnManager();
	std::vector<Player*> alivePlayers;
	for (Player* player : turnManager->playerList)
		if (!player->dead)
			alivePlayers.push_back(player);
	if (alivePlayers.size() == 1) EndGame(alivePlayers[0]);
}

void Game::EndGame(Player* winner) {
	ended = true;
	Game::winner = winner;
	TurnManager* turnManager = GetTurnManager();
	turnManager->End();
	MapReader* map = GetMap();
	map->shouldDraw = false;
}

MapReader* Game::GetMap() { return dynamic_cast<MapReader*>(gameObjects[0].get()); }

TurnManager* Game::GetTurnManager() { return dynamic_cast<TurnManager*>(gameObjects[gameObjects.size()-1].get()); }