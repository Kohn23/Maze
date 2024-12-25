#pragma once
#include<conio.h>

#include "Basic.h"

// 物体内核由队列实现
using Kernel = std::queue<Point>;

// 物体接口
class Object {
public:
	Object& operator=(const Object&) = delete;
	virtual ~Object() = default;
public:
	virtual Point getPosition() = 0;
	virtual bool emptyPosition() = 0;
public:
	// 重载内核更新的方法，一个是取出位置，另一个是压入位置
	virtual Point updateKernel() = 0;
	virtual void updateKernel(Point position) = 0;
};

// 玩家物体
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

