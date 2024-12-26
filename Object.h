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
	virtual Point fetchPosition() = 0;
	virtual bool emptyPosition() = 0;
public:
	virtual void updateKernel(Point position) = 0;
	virtual void updateKernel(Kernel newKernel) = 0;
};

// 玩家物体
class Player final : public Object {
public:
	Player(Point p);
	~Player() = default;
public:
	virtual Point getPosition() override;
	virtual Point fetchPosition() override;
	virtual bool emptyPosition() override;
	virtual void updateKernel(Point position) override;
	virtual void updateKernel(Kernel newKernel) override;
public:
	virtual void move();
private:
	Kernel kernel;
};

// 玩家物体
class AutoPilot final : public Object {
public:
	AutoPilot& operator=(const AutoPilot&) = delete;
	AutoPilot(Point p);
	~AutoPilot() = default;
public:
	virtual Point getPosition() override;
	virtual Point fetchPosition() override;
	virtual bool emptyPosition() override;
	virtual void updateKernel(Point position) override;
	virtual void updateKernel(Kernel newKernel) override;
public:
	virtual void move();
private:
	Kernel kernel;
};