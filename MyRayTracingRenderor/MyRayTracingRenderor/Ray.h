#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "Cube.h"
#include "CubicLight.h"
class Ray
{
public:
	Vector startPoint;
	Vector rayDirection;
	double t;
	Ray();
	Ray(Vector, Vector);
	//检测碰撞，若不发生碰撞则返回-1。同时用传递引用的方法得到法向量。
	double CollideSphere(Sphere,Vector&);
	double CollideCube(Cube,Vector&);
	//double CollideCubicLight(CubicLight, Vector&);
	// 
	//返回t时刻的光线位置。
	Vector Current(double);
	Vector RGB;
};