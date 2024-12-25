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
    // �����ƶ�
    Point move = kernel.front();
    char ch = _getch();  // ��ȡһ���ַ�����
    if (ch == 'w' || ch == 'W') // ��
    {
        move += Point(0, -1);
        kernel.push(move);
    }
    else if (ch == 's' || ch == 'S') // ��
    {
        move += Point(0, 1);
        kernel.push(move);
    }
    else if (ch == 'a' || ch == 'A') // ��
    {
        move += Point(-1, 0);
        kernel.push(move);
    }
    else if (ch == 'd' || ch == 'D') // ��
    {
        move += Point(1, 0);
        kernel.push(move);
    }
}