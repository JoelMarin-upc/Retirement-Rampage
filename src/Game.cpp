#include "Game.h"

int Game::bottomY;

std::vector<std::unique_ptr<GameObject>> Game::gameObjects;

void Game::EndGame(int loser) {
	TurnManager* turnManager = GetTurnManager();
	turnManager->End();
	MapReader* map = GetMap();
	map->shouldDraw = false;

	// Mostrar pantalla final
}

MapReader* Game::GetMap() { return dynamic_cast<MapReader*>(gameObjects[0].get()); }
TurnManager* Game::GetTurnManager() { return dynamic_cast<TurnManager*>(gameObjects[gameObjects.size()-1].get()); }