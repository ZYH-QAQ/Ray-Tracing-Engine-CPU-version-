#include <iostream>
#include <random>
#include <fstream>
#include "Vector.h"
#include "Cube.h"
#include "Sphere.h"
#include "Ray.h"
#include "RandomDirection.h"
#include "RussianRoulette.h"
#include "Collider.h"
#include "PathTracing.h"
#include <stdlib.h>
#include <ctime>
using namespace std;
//用于生成俄罗斯轮盘的随机数和蒙特卡洛积分的随机采样。
std::default_random_engine e;
std::uniform_real_distribution<double> rand1(0, pi / 2);
std::uniform_real_distribution<double> rand2(0, 2 * pi);
std::uniform_int_distribution<unsigned> rand3(1,10);
//存储场景里的所有几何形体。
Collider* geometry[100];
int num;
void Create(int xLength, int yLength, int depth);
void DrawPixel();
long int* nowTimeP,*startTimeP;
int main()
{
	clock_t startTime,nowTime;
	nowTimeP = &nowTime;
	startTimeP = &startTime;
	startTime = clock();
	ifstream scene;
	scene.open("Scene.txt", ios::in);
	int cubeNum;
	scene >> cubeNum;
	int i = 0;
	for (;i < cubeNum;i++)
	{
		Cube* cubeP = new Cube();
		geometry[i] = cubeP;
		//double a, b, c,d,e,f;
		scene >>((Cube*)geometry[i])->xMax >>((Cube*)geometry[i])->xMin >>((Cube*)geometry[i])->yMax  >> ((Cube*)geometry[i])->yMin >> ((Cube*)geometry[i])->zMax >>((Cube*)geometry[i])->zMin;
		 //= a; 
		 //= b;
		 //= c;
		 //= d;
		 //= e;
		 //= f;
		//printf("%p\n", (geometry[i]));
	}
	int lightNum;
	scene >> lightNum;
	for (;i < cubeNum + lightNum;i++)
	{
		geometry[i] = new CubicLight();
		scene >> ((Cube*)geometry[i])->xMax >> ((Cube*)geometry[i])->xMin >> ((Cube*)geometry[i])->yMax >> ((Cube*)geometry[i])->yMin >> ((Cube*)geometry[i])->zMax >> ((Cube*)geometry[i])->zMin;
		//printf("%f\n", ((Cube*)geometry[i])->xMax);
		//printf("%f\n", ((CubicLight*)geometry[i])->Cube::xMax);

	}
	num = i;
	Vector test = Trace(Ray(Vector(0, 0, 0), Vector::Normalize(Vector(0, 200, -150))));
	DrawPixel();
	return 0;
}
void DrawPixel()
{
	ofstream image;
	image.open("image_1.ppm", ios::out | ios::trunc);
	image << "P3" << endl;
	image << 640 << " " << 360 << endl;
	image << 255 << endl;
	
	for (int j = 0;j < 360; j++)
	{
		for (int i = 0;i < 640;i++)
		{
			double centerX = -320 + i + 0.5;
			double centerY = 180 - j - 0.5;
			Vector NRGB(0, 0, 0);
			for (int k = -2;k <= 2;k++)
			{
				for (int l = -2;l <= 2;l++)
				{
					double eachX = centerX + k / 5.0;
					double eachY = centerY + l / 5.0;
					Ray ray = Ray(Vector(0, 0, 0), Vector::Normalize(Vector(eachX, eachY, -100)));
					NRGB = NRGB + Trace(ray);
				}
			}
			Vector RGB = NRGB / 25;
			image << (int)RGB.x << " " << (int)RGB.y << " " << (int)RGB.z << "	";
			system("cls");
			printf("Progress: %.4f%%\n", (j * 640 + i) / (360 * 640.0)*100);
			//*nowTimeP = clock();
			//printf("Estimated time left: %ld", (720 * 1280 - j * 1280 - i) * (*nowTimeP-*startTimeP)/ CLOCKS_PER_SEC / (j * 1280 + i + 1));
		}
		image << '\n';

	}
	image.close();

}
void Create(int xLength, int yLength, int depth)
{
	ofstream image;
	image.open("image_1.ppm", ios::out | ios::trunc);
	image << "P3" << endl;
	image << xLength << " " << yLength << endl;
	image << 255 << endl;
	image.close();

}