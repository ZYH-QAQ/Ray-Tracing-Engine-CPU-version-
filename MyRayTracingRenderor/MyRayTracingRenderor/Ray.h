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
	//�����ײ������������ײ�򷵻�-1��ͬʱ�ô������õķ����õ���������
	double CollideSphere(Sphere,Vector&);
	double CollideCube(Cube,Vector&);
	//double CollideCubicLight(CubicLight, Vector&);
	// 
	//����tʱ�̵Ĺ���λ�á�
	Vector Current(double);
	Vector RGB;
};