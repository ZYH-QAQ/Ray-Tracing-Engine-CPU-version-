#include <iostream>
#include "Collider.h"
#include "Cube.h"
#include "Matrix.h"
#include "RandomDirection.h"
#include "Ray.h"
#include "RussianRoulette.h"
#include "Sphere.h"
#include "Vector.h"
#include <math.h>
#define INF 1000000
extern Collider* geometry[];
extern int num;
const char* tag;
Vector Trace(Ray ray)
{
	double tFirst =INF;
	Vector storeFirstNormalVector;
	int indexFirst;
	Vector now;
	double t;
	for (int i = 0;i < 100;i++)
	{
		//printf("%p\n", (geometry[i]));
		//printf("%s\n", (geometry[i])->Distinguish());

		if ((tag=(geometry[i]->Distinguish())) == "Cube")
		{
			t = ray.CollideCube(*(Cube*)geometry[i], now);
			if (t <= tFirst && t>0)
			{
				tFirst = t;
				storeFirstNormalVector = now;
				indexFirst = i;
			}
		}
		else if ((tag=geometry[i]->Distinguish()) == "Sphere")
		{
			t = ray.CollideSphere(*(Sphere*)geometry[i], now);
			if (t <= tFirst && t>0)
			{
				tFirst = t;
				storeFirstNormalVector = now;
				indexFirst = i;
			}
		}
		else if ((tag=geometry[i]->Distinguish()) == "CubicLight")
		{
			//((CubicLight*)geometry[i])->InitializeParent();
			t = ray.CollideCube(*(Cube*)geometry[i], now);
			if (t <= tFirst && t>0)
			{
				tFirst = t;
				storeFirstNormalVector = now;
				indexFirst = i;
			}
		}
		if (i == num - 1)
			break;

	}
	if (tFirst == INF)
		return Vector(0, 0, 0);
	if (!RussianRoulette::Decide())
		return Vector(0, 0, 0);
	else if((tag=geometry[indexFirst]->Distinguish()) == "CubicLight")
	{
		return Vector(255, 255, 255);
	}
	else
	{
		double phi;
		Vector next = RandomDirection::Decide(storeFirstNormalVector, phi);
		Ray rayNext = Ray(ray.Current(tFirst), next);
		ray.~Ray();
		return std::sin(phi) / (2 * 0.9/pi) * Trace(rayNext);
	}
}