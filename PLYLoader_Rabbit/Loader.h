#pragma once
#include <GL\glut.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct PlyModelData
{
	vector<float> vecPointsInfo;
	vector<float> vecFaceInfo;
	vector<float> vecFaceColorInfo; 
	int modelPointNums;
	int modelFaceNums;
};

class CPLYLoader
{
public:
	CPLYLoader();
	~CPLYLoader();
	bool LoadModel(char *filename);
	void Draw();
	void myDraw();
	void DrawPoints();
	void DrawTriangles();
	void DrawGrids();
	void DebugOutput();
private:
	int m_loaderPointNums;
	int m_loaderFacesNums;
	PlyModelData m_ModelData;
};

