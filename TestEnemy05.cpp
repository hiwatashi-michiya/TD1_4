#include "TestEnemy05.h"
#include <Novice.h>

TestEnemy05::TestEnemy05(Vec2 pos, Vec2 speed, E5MOVEDIRECTION direction)
{
	mPosition = pos;
	mSpeed = speed;

	e5MoveDIrection = direction;

}




void TestEnemy05::Update(Map map, bool* redSwitch, bool* greenSwitch, bool* blueSwitch, bool* isHitredSwitch, bool* isHitgreenSwitch, bool* isHitblueSwitch) {

	if (e5MoveDIrection == UP) {

		mPosition.y -= mSpeed.y;

	}

	else if (e5MoveDIrection == DOWN) {

		mPosition.y += mSpeed.y;

	}

	else if (e5MoveDIrection == LEFT) {

		mPosition.x -= mSpeed.x;

	}

	else if (e5MoveDIrection == RIGHT) {

		mPosition.x += mSpeed.x;

	}

	int leftTopX = (mPosition.x - 16) / MAP_SIZE;
	int leftTopY = (mPosition.y - 16) / MAP_SIZE;
	int rightTopX = (mPosition.x + 16 - 1) / MAP_SIZE;
	int rightTopY = (mPosition.y - 16) / MAP_SIZE;
	int leftBottomX = (mPosition.x - 16) / MAP_SIZE;
	int leftBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;
	int rightBottomX = (mPosition.x + 16 - 1) / MAP_SIZE;
	int rightBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;

	if ((map.map[leftTopY][leftTopX] == map.RED_SWITCH || map.map[rightTopY][rightTopX] == map.RED_SWITCH ||
		map.map[leftBottomY][leftBottomX] == map.RED_SWITCH || map.map[rightBottomY][rightBottomX] == map.RED_SWITCH)) {

		if (*isHitredSwitch == false) {

			if (*redSwitch == false) {
				*redSwitch = true;
			}
			else {
				*redSwitch = false;
			}

		}

		*isHitredSwitch = true;

	}
	else {
		*isHitredSwitch = false;
	}

	if ((map.map[leftTopY][leftTopX] == map.GREEN_SWITCH || map.map[rightTopY][rightTopX] == map.GREEN_SWITCH ||
		map.map[leftBottomY][leftBottomX] == map.GREEN_SWITCH || map.map[rightBottomY][rightBottomX] == map.GREEN_SWITCH)) {

		if (*isHitgreenSwitch == false) {

			if (*greenSwitch == false) {
				*greenSwitch = true;
			}
			else {
				*greenSwitch = false;
			}

		}

		*isHitgreenSwitch = true;

	}
	else {
		*isHitgreenSwitch = false;
	}

	if ((map.map[leftTopY][leftTopX] == map.BLUE_SWITCH || map.map[rightTopY][rightTopX] == map.BLUE_SWITCH ||
		map.map[leftBottomY][leftBottomX] == map.BLUE_SWITCH || map.map[rightBottomY][rightBottomX] == map.BLUE_SWITCH)) {

		if (*isHitblueSwitch == false) {

			if (*blueSwitch == false) {
				*blueSwitch = true;
			}
			else {
				*blueSwitch = false;
			}

		}

		*isHitblueSwitch = true;

	}
	else {
		*isHitblueSwitch = false;
	}

	if ((map.AnyNone(map.map[leftTopY][leftTopX]) == false || map.AnyNone(map.map[leftBottomY][leftBottomX]) == false) &&
		e5MoveDIrection == LEFT) {

		mPosition.x = (leftTopX + 1) * 32 + 16;

		leftTopX = (mPosition.x - 16) / MAP_SIZE;
		leftTopY = (mPosition.y - 16) / MAP_SIZE;
		rightTopX = (mPosition.x + 16 - 1) / MAP_SIZE;
		rightTopY = (mPosition.y - 16) / MAP_SIZE;
		leftBottomX = (mPosition.x - 16) / MAP_SIZE;
		leftBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;
		rightBottomX = (mPosition.x + 16 - 1) / MAP_SIZE;
		rightBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;

		if (map.AnyNone(map.map[leftBottomY][leftBottomX]) == true && map.AnyNone(map.map[rightBottomY][rightBottomX]) == true) {

			e5MoveDIrection = DOWN;

		}
		else if (map.AnyNone(map.map[leftTopY][leftTopX]) == true && map.AnyNone(map.map[rightTopY][rightTopX]) == true) {

			e5MoveDIrection = UP;

		}
		else {
			e5MoveDIrection = RIGHT;
		}

	}

	if ((map.AnyNone(map.map[rightTopY][rightTopX]) == false || map.AnyNone(map.map[rightBottomY][rightBottomX]) == false) &&
		e5MoveDIrection == RIGHT) {

		mPosition.x = (rightTopX - 1) * 32 + 16;

		leftTopX = (mPosition.x - 16) / MAP_SIZE;
		leftTopY = (mPosition.y - 16) / MAP_SIZE;
		rightTopX = (mPosition.x + 16 - 1) / MAP_SIZE;
		rightTopY = (mPosition.y - 16) / MAP_SIZE;
		leftBottomX = (mPosition.x - 16) / MAP_SIZE;
		leftBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;
		rightBottomX = (mPosition.x + 16 - 1) / MAP_SIZE;
		rightBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;
		
		if (map.AnyNone(map.map[leftTopY][leftTopX]) == true && map.AnyNone(map.map[rightTopY][rightTopX]) == true) {

			e5MoveDIrection = UP;

		}
		else if (map.AnyNone(map.map[leftBottomY][leftBottomX]) == true && map.AnyNone(map.map[rightBottomY][rightBottomX]) == true) {

			e5MoveDIrection = DOWN;

		}
		else {
			e5MoveDIrection = LEFT;
		}

	}

	if ((map.AnyNone(map.map[leftTopY][leftTopX]) == false || map.AnyNone(map.map[rightTopY][rightTopX]) == false) &&
		e5MoveDIrection == UP) {

		mPosition.y = (leftTopY + 1) * 32 + 16;

		leftTopX = (mPosition.x - 16) / MAP_SIZE;
		leftTopY = (mPosition.y - 16) / MAP_SIZE;
		rightTopX = (mPosition.x + 16 - 1) / MAP_SIZE;
		rightTopY = (mPosition.y - 16) / MAP_SIZE;
		leftBottomX = (mPosition.x - 16) / MAP_SIZE;
		leftBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;
		rightBottomX = (mPosition.x + 16 - 1) / MAP_SIZE;
		rightBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;

		if (map.AnyNone(map.map[leftTopY][leftTopX]) == true && map.AnyNone(map.map[leftBottomY][leftBottomX]) == true) {

			e5MoveDIrection = LEFT;

		}
		else if (map.AnyNone(map.map[rightTopY][rightTopX]) == true && map.AnyNone(map.map[rightBottomY][rightBottomX]) == true) {

			e5MoveDIrection = RIGHT;

		}
		else {
			e5MoveDIrection = DOWN;
		}

	}

	if ((map.AnyNone(map.map[leftBottomY][leftBottomX]) == false || map.AnyNone(map.map[rightBottomY][rightBottomX]) == false) &&
		e5MoveDIrection == DOWN) {

		mPosition.y = (leftBottomY - 1) * 32 + 16;

		leftTopX = (mPosition.x - 16) / MAP_SIZE;
		leftTopY = (mPosition.y - 16) / MAP_SIZE;
		rightTopX = (mPosition.x + 16 - 1) / MAP_SIZE;
		rightTopY = (mPosition.y - 16) / MAP_SIZE;
		leftBottomX = (mPosition.x - 16) / MAP_SIZE;
		leftBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;
		rightBottomX = (mPosition.x + 16 - 1) / MAP_SIZE;
		rightBottomY = (mPosition.y + 16 - 1) / MAP_SIZE;
		
		if (map.AnyNone(map.map[rightTopY][rightTopX]) == true && map.AnyNone(map.map[rightBottomY][rightBottomX]) == true) {

			e5MoveDIrection = RIGHT;

		}
		else if (map.AnyNone(map.map[leftTopY][leftTopX]) == true && map.AnyNone(map.map[leftBottomY][leftBottomX]) == true) {

			e5MoveDIrection = LEFT;

		}
		else {
			e5MoveDIrection = UP;
		}

	}

}

void TestEnemy05::Draw(float* scrollX) {

	Novice::DrawQuad(mPosition.x - 16 - *scrollX, mPosition.y - 16, mPosition.x + 16 - *scrollX, mPosition.y - 16,
		mPosition.x - 16 - *scrollX, mPosition.y + 16, mPosition.x + 16 - *scrollX, mPosition.y + 16,
		0, 0, 1, 1, 0, 0xFF0000FF);

}
