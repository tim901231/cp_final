#include"enemy.h"

pii operator +(const pii& p1, const pii& p2) {
	return { p1.X + p2.X, p1.Y + p2.Y };
}

pii operator -(const pii& p1, const pii& p2) {
	return { p1.X - p2.X, p1.Y - p2.Y };
}

bool check(pii p) {
	return (p.X >= 0 && p.X < 18 && p.Y >= 0 && p.Y < 10);
}
ENEMY::ENEMY(int type) {
	TYPE = type;
	freeze = 0;
	rect.w = 90;
	rect.h = 90;
	rect.x = 0;
	rect.y = 70 + 5 * 90;
	nowx = rect.x;
	nowy = rect.y;
	CanFly = false;
	dir = RIGHT;
	current_phase = 0;
	pos = { 0,5 };
	switch (type) {
	case 0: {
		hp = 1000000;
		speed = 0;
		money = 1000000;
		break;
	}
	case 1: {  //Light_Soldier
		hp = 30;
		speed = 1;
		money = 1;
		period = 12;
		break;
	}
	case 2: {  //Heavy_Soldier
		hp = 120;
		speed = 0.75;
		money = 3;
		period = 16;
		break;
	}
	case 3: {  //Light_Tank
		hp = 700;
		speed = 0.5;
		money = 5;
		period = 3;
		break;
	}
	case 4: {  //Heavy_Tank
		hp = 2000;
		speed = 0.25;
		money = 10;
		period = 10;
		break;
	}
	case 5: {  //Titan
		hp = 6000;
		speed = 0.5;
		money = 50;
		period = 10;
	}
	case 6: {  //jet
		hp = 500;
		speed = 1.5;
		money = 10;
		period = 1;
		CanFly = true;
	}
	case 7: {  //Helicopter
		hp = 380;
		speed = 0.75;
		money = 8;
		period = 6;
		CanFly = true;
	}
	case 8: {  //Runner
		hp = 80;
		speed = 2;
		money = 2;
		period = 12;
	}
	case 9: {  //MotherShip
		hp = 1000;
		speed = 0.5;
		money = 30;
		period = 1;
		CanFly = true;
	}
	}
}
void ENEMY::calculate_hp() {
	green.w = hp / MAX_HEALTH[TYPE];
	green.h = 10;
	red.w = 90 - green.w;
	red.h = 10;
	green.x = rect.x;
	green.y = rect.y + 90;
	red.x = green.x + green.w;
	red.y = green.y;
}
