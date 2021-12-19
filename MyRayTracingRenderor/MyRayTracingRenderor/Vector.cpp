#include<iostream>
//#include<cmath>
#include "Vector.h"
const Vector Vector::defaultVector = Vector(0, 0, 0);
Vector::Vector(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector::Vector()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
//������*��������������ˡ�
Vector operator*(const Vector& v1, double lambda)
{
	Vector vResult(v1.x * lambda, v1.y * lambda, v1.z * lambda);
	return vResult;
}
//������*��������������ˡ�
Vector operator*(double lambda, const Vector& v1)
{
	Vector vResult;
	vResult.x = v1.x * lambda;
	vResult.y = v1.y * lambda;
	vResult.z = v1.z * lambda;
	return vResult;
}
//������*����������ڵ�ˡ�
double operator*(const Vector& v1, const Vector& v2)
{
	return Vector::Dot(v1, v2);
}
//������/�����������������
Vector operator/(const Vector& v1, double lambda)
{
	Vector vResult;
	vResult.x = v1.x / lambda;
	vResult.y = v1.y / lambda;
	vResult.z = v1.z / lambda;
	return vResult;
}
//������+���������������ʸ����ӡ�
Vector operator+(const Vector& v1, const Vector v2)
{
	Vector vResult(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	return vResult;
}
//������-���������������ʸ�������
Vector operator-(const Vector& v1, const Vector v2)
{
	Vector vResult(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return vResult;
}

double Vector::Dot(const Vector& v1, const Vector& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector Vector::Cross(const Vector& v1, const Vector& v2)
{
	Vector vResult;
	vResult.x = v1.y * v2.z - v1.z * v2.y;
	vResult.y = v1.z * v2.x - v1.x * v2.z;
	vResult.z = v1.x * v2.y - v1.y * v2.x;
	return vResult;
}

double Vector::Module(const Vector& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector Vector::Normalize(const Vector& v)
{
	return v / Vector::Module(v);
}