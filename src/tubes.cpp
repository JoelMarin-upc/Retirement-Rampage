

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

typedef struct Tubes {
	Rectangle rec;
	Color color;
	bool active;
} Tubes;


static Tubes tubes[MAX_TUBES * 2] = { 0 };
static Vector2 tubesPos[MAX_TUBES] = { 0 };
static int tubesSpeedX = 0;


void SpawnTubes ()
{
	tbuesSpeedX = 2;

	for (int i = 0; i < MAX_TUBES; i++)
	{
		tubesPos[i].x = 400 + 280 * i;
		tubesPos[i].y = -GetRandomValue(0, 120);
	}

	for (int i = 0; i < MAX_TUBES * 2; i += 2)
	{
		tubes[i].rec.x = tubesPos[i / 2].x;
		tubes[i].rec.y = tubesPos[i / 2].y;
		tubes[i].rec.width = TUBES_WIDTH;
		tubes[i].rec.height = 255;

		tubes[i + 1].rec.x = tubesPos[i / 2].x;
		tubes[i + 1].rec.y = 600 + tubesPos[i / 2].y - 255;
		tubes[i + 1].rec.width = TUBES_WIDTH;
		tubes[i + 1].rec.height = 255;

	//	tubes[i / 2].active = true;
	}
}

void MoveTubes() 
{
	for (int i = 0; i < MAX_TUBES; i++) tubesPos[i].x -= tubesSpeedX;

	for (int i = 0; i < MAX_TUBES * 2; i += 2)
	{
		tubes[i].rec.x = tubesPos[i / 2].x;
		tubes[i + 1].rec.x = tubesPos[i / 2].x;
	}
}