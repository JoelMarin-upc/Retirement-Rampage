#include "GameObject.h"
#include "SoundEffects.h"
#include <vector>
#include <memory>

class Game {
public:
	static std::vector<std::unique_ptr<GameObject>> gameObjects;
};