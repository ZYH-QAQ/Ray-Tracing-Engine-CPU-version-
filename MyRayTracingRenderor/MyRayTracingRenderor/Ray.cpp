#include "Ray.h"
#include "Sphere.h"
#include <iostream>
#include <algorithm>
//Ray���������캯����
Ray::Ray()
{
	t = 0;
}

Ray::Ray(Vector startPoint, Vector rayDirection)
{
	t = 0;
	this->rayDirection = rayDirection;
	this->startPoint = startPoint;
}
//���Ray�����Ƿ���ײ��������ײ����ײʱ��Ϊ�������򷵻�-1��ͬʱ����������Ϊdefault��
double Ray::CollideSphere(Sphere sphere, Vector& normalVector)
{
	double x0 = this->startPoint.x;
	double y0 = this->startPoint.y;
	double z0 = this->startPoint.z;
	double x1 = this->rayDirection.x;
	double y1 = this->rayDirection.y;
	double z1 = this->rayDirection.z;

	double Delta = 4 * (x1 * x0 + y1 * y0 + z1 * z0) * (x1 * x0 + y1 * y0 + z1 * z0) - 4 * (x1 * x1 + y1 * y1 + z1 * z1) * (x0 * x0 + y0 * y0 + z0 * z0 - sphere.radius * sphere.radius);
	if (Delta < 0)
	{
		normalVector = Vector::defaultVector;
		return -1;
	}
	else
	{
		double result1 = (sqrt(Delta) - 2 * (x1 * x0 + y1 * y0 + z1 * z0)) / (2 * (x1 * x1 + y1 * y1 + z1 * z1));
		double result2 = (-sqrt(Delta) - 2 * (x1 * x0 + y1 * y0 + z1 * z0)) / (2 * (x1 * x1 + y1 * y1 + z1 * z1));
		if (result1 > 0 && result2 > 0)
		{
			normalVector = Vector::Normalize(this->Current(result1 > result2 ? result2 : result1)-sphere.center);
			return result1 > result2 ? result2 : result1;
		}
		if (result1 * result2 < 0)
		{
			normalVector = Vector::Normalize(this->Current(result1 > result2 ? result1 : result2) - sphere.center);
			return result1 > result2 ? result1 : result2;
		}
		if (result1 < 0 && result2 < 0)
		{
			normalVector = Vector::defaultVector;
			return -1;
		}
	}

}
//���Ray�Ƿ�����������ײ����δ��ײ������ײʱ��Ϊ�������򷵻�-1����������Ϊdefault��
double Select(double x, double y, double z)
{
	double max=x;
	if (max < y)
	{
		max = y;
	}
	if (max < z)
	{
		max = z;
	}
	return max;
}
double Ray::CollideCube(Cube cube, Vector& normalVector)
{
	double x0 = this->startPoint.x;
	double y0 = this->startPoint.y;
	double z0 = this->startPoint.z;
	double x1 = this->rayDirection.x;
	double y1 = this->rayDirection.y;
	double z1 = this->rayDirection.z;

	double txMin = (cube.xMin - x0) / x1 > (cube.xMax - x0) / x1 ? (cube.xMax - x0) / x1 : (cube.xMin - x0) / x1;
	double txMax = (cube.xMin - x0) / x1 < (cube.xMax - x0) / x1 ? (cube.xMax - x0) / x1 : (cube.xMin - x0) / x1;

	double tyMin = (cube.yMin - y0) / y1 > (cube.yMax - y0) / y1 ? (cube.yMax - y0) / y1 : (cube.yMin - y0) / y1;
	double tyMax = (cube.yMin - y0) / y1 < (cube.yMax - y0) / y1 ? (cube.yMax - y0) / y1 : (cube.yMin - y0) / y1;

	double tzMin = (cube.zMin - z0) / z1 > (cube.zMax - z0) / z1 ? (cube.zMax - z0) / z1 : (cube.zMin - z0) / z1;
	double tzMax = (cube.zMin - z0) / z1 < (cube.zMax - z0) / z1 ? (cube.zMax - z0) / z1 : (cube.zMin - z0) / z1;

	if (txMin < 0 && tyMin < 0 && tzMin < 0)
	{
		normalVector = Vector::defaultVector;
		return -1;
	}
	if (txMax > tyMin && tyMax > txMin && txMax > tzMin && tzMax > txMin && tyMax > tzMin && tzMax > tyMin)
	{
		double tMin = Select(txMin, tyMin, tzMin);
		if (tMin == txMin)
		{
			normalVector = Vector(1, 0, 0) * rayDirection > 0 ? Vector(-1, 0, 0) : Vector(1, 0, 0);
			return tMin;
		}
		if (tMin == tyMin)
		{
			normalVector = Vector(0, 1, 0) * rayDirection > 0 ? Vector(0, -1, 0) : Vector(0, 1, 0);
			return tMin;
		}
		if (tMin == tzMin)
		{
			normalVector = Vector(0, 0, 1) * rayDirection > 0 ? Vector(0, 0, -1) : Vector(0, 0, 1);
			return tMin;
		}
	}
	else
	{
		normalVector = Vector::defaultVector;
		return -1;
	}

}
//��ȡ����tʱ�̵����ꡣ
Vector Ray::Current(double t)
{
	return this->startPoint + t * this->rayDirection;
}