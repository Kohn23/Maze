#pragma once
#include<conio.h>

#include "Basic.h"

// �����ں��ɶ���ʵ��
using Kernel = std::queue<Point>;

// ����ӿ�
class Object {
public:
	Object& operator=(const Object&) = delete;
	virtual ~Object() = default;
public:
	virtual Point getPosition() = 0;
	virtual bool emptyPosition() = 0;
public:
	// �����ں˸��µķ�����һ����ȡ��λ�ã���һ����ѹ��λ��
	virtual Point updateKernel() = 0;
	virtual void updateKernel(Point position) = 0;
};

// �������
class Player final : public Object {
public:
	Player(Point p);
	~Player() = default;
public:
	virtual Point getPosition() override;
	virtual bool emptyPosition() override;
	virtual Point updateKernel() override;
	virtual void updateKernel(Point position) override;
public:
	virtual void move();
private:
	Kernel kernel;
};

