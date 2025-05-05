#include "GameObject.h"
#include "TurnManager.h"
#include "MapReader.h"
#include <vector>
#include <memory>

class Game {
public:
	static int screenWidth;
	static int screenHeight;
	static int bottomY;
	static int tileSize;
	static bool ended;
	static Player* winner;
	static std::vector<std::unique_ptr<GameObject>> gameObjects;
	static std::map<int, int> playerIndexes;
	static void AddPlayer(unique_ptr<GameObject>);
	static void CheckEndGame();
	static void EndGame(Player* winner);
	static MapReader* GetMap();
	static TurnManager* GetTurnManager();
};