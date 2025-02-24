#include <raylib.h>

class GameObject {
public:
	Vector2 position, size;

	GameObject() {
		position = Vector2();
		position.x = 0;
		position.y = 0;

		size = Vector2();
		size.x = 0;
		size.y = 0;
	}

	GameObject(Vector2 &position, Vector2 &size) {
		this->position = Vector2(position);
		this->size = Vector2(size);
	}

	virtual void Init() {}

	virtual void Update() = 0;

	virtual void Draw() = 0;
};