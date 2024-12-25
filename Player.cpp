#include "Object.h"

Player::Player(Point p) {
	kernel.push(p);
}

Point Player::getPosition() {
	return kernel.front();
}

Point Player::updateKernel() {
	Point temp = kernel.front();
	kernel.pop();
	return temp;
}

void Player::updateKernel(Point position) {
	kernel.push(position);
}

bool Player::emptyPosition() {
	return kernel.empty();
}

void Player::move() {
    // 进行移动
    Point move = kernel.front();
    char ch = _getch();  // 获取一个字符输入
    if (ch == 'w' || ch == 'W') // 上
    {
        move += Point(0, -1);
        kernel.push(move);
    }
    else if (ch == 's' || ch == 'S') // 下
    {
        move += Point(0, 1);
        kernel.push(move);
    }
    else if (ch == 'a' || ch == 'A') // 左
    {
        move += Point(-1, 0);
        kernel.push(move);
    }
    else if (ch == 'd' || ch == 'D') // 右
    {
        move += Point(1, 0);
        kernel.push(move);
    }
}