#include "GameObject.h"
#include "TurnManager.h"
#include "MapReader.h"
#include <vector>
#include <memory>

class Game {
public:
	static int bottomY;
	static std::vector<std::unique_ptr<GameObject>> gameObjects;
	static void EndGame(int winner);
	static MapReader* GetMap();
	static TurnManager* GetTurnManager();
};