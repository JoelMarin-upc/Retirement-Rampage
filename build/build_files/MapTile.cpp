#include <raylib.h>
#include "GameObject.cpp"

class MapTile : public GameObject {
public:
	Color color;
	bool hasTerrain;

	MapTile(Color c, bool hasTerrain, Vector2 position, Vector2 size) : GameObject(position, size)
	{
		color = c;
		this->hasTerrain = hasTerrain;
	}

	void Update() override {

	}

	void Draw() override {
		if (!hasTerrain) return;
		DrawRectangle(position.x, position.y, size.x, size.y, color);
	}

	void Destroy() {
		hasTerrain = false;
	}
};