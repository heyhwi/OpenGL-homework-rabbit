#include "Loader.h"

CPLYLoader::CPLYLoader()
{
	this->m_loaderPointNums = 0;
	this->m_loaderFacesNums = 0;
	this->m_ModelData.modelPointNums = 0;
	this->m_ModelData.modelFaceNums = 0;
}

CPLYLoader::~CPLYLoader()
{
}

bool CPLYLoader::LoadModel(char *filename)
{
	cout << "Loading" << filename << "..." << endl;
	char *pch = strstr(filename, ".ply2");
	if (pch == NULL) {	
		//check file type
		cout << filename << " does not have a ply2 extension." << endl;
		return false;
	}
	else {
		ifstream fin(filename);
		fin >> m_loaderPointNums >> m_loaderFacesNums;
		m_ModelData.modelPointNums = m_loaderPointNums;
		m_ModelData.modelFaceNums = m_loaderFacesNums;

		//Load points info to m_ModelData
		float px, py, pz;
		for (int i = 0; i < m_loaderPointNums; i++) {
			fin >> px >> py >> pz;
			m_ModelData.vecPointsInfo.push_back(px);
			m_ModelData.vecPointsInfo.push_back(py);
			m_ModelData.vecPointsInfo.push_back(pz);
		}

		//Load faces info to m_ModelData
		int curFaceVertexs;
		for (int i = 0; i < m_loaderFacesNums; i++) {
			fin >> curFaceVertexs;
			int tempPointIndex;
			for (int j = 0; j < curFaceVertexs; j++) {
				fin >> tempPointIndex;
				m_ModelData.vecFaceInfo.push_back(m_ModelData.vecPointsInfo[curFaceVertexs*tempPointIndex]);
				m_ModelData.vecFaceInfo.push_back(m_ModelData.vecPointsInfo[curFaceVertexs*tempPointIndex + 1]);
				m_ModelData.vecFaceInfo.push_back(m_ModelData.vecPointsInfo[curFaceVertexs*tempPointIndex + 2]);
			}
		}

		fin.close();
		cout << filename << " Loaded Succesfully" << endl;
		return true;
	}
}

void CPLYLoader::Draw()
{
	glVertexPointer(3, GL_FLOAT, 0, m_ModelData.vecFaceInfo.data());
	//glDrawArrays(GL_TRIANGLES, 0, m_ModelData.modelFaceNums);
	glDrawArrays(GL_POINTS, 0, 69451*3);

}

void CPLYLoader::myDraw()
{
}

void CPLYLoader::DrawPoints()
{
	glVertexPointer(3, GL_FLOAT, 0, m_ModelData.vecFaceInfo.data());
	glDrawArrays(GL_POINTS, 0, m_ModelData.modelFaceNums * 3);
}

void CPLYLoader::DrawTriangles()
{
	glVertexPointer(3, GL_FLOAT, 0, m_ModelData.vecFaceInfo.data());
	glDrawArrays(GL_TRIANGLES, 0, m_ModelData.modelFaceNums*3);
}


void CPLYLoader::DrawGrids()
{
	//for (int i = 0; i < m_ModelData.modelFaceNums; i++) {
	//	glVertexPointer(3, GL_FLOAT, 0, &m_ModelData.vecFaceInfo[i*3]);
	//	glDrawArrays(GL_LINE_LOOP, i, 3);
	//}
	for (int i = 0; i < m_ModelData.modelFaceNums*9; i+=9) {
		glBegin(GL_LINE_LOOP);	
		glVertex3f(m_ModelData.vecFaceInfo[i + 0], m_ModelData.vecFaceInfo[i + 1], m_ModelData.vecFaceInfo[i + 2]);
		glVertex3f(m_ModelData.vecFaceInfo[i + 3], m_ModelData.vecFaceInfo[i + 4], m_ModelData.vecFaceInfo[i + 5]);
		glVertex3f(m_ModelData.vecFaceInfo[i + 6], m_ModelData.vecFaceInfo[i + 7], m_ModelData.vecFaceInfo[i + 8]);
		glEnd();
	}
}

void CPLYLoader::DebugOutput()
{
	freopen("DebugOutput.txt", "w", stdout);
	cout << "This is the DebugOutput: " << endl;
	cout << "Points: " << endl;
	for (int i = 0; i < m_loaderPointNums * 3; i += 3) {
		cout << m_ModelData.vecPointsInfo[i] << " " << m_ModelData.vecPointsInfo[i + 1] << " " << m_ModelData.vecPointsInfo[i + 2] << endl;
	}
	cout << "Faces: " << endl;
	for (int i = 0; i < m_loaderFacesNums * 9; i += 9) {
		cout << m_ModelData.vecFaceInfo[i] <<'\t'<< m_ModelData.vecFaceInfo[i + 1] << '\t' << m_ModelData.vecFaceInfo[i + 2] << '\t\t';
		cout << m_ModelData.vecFaceInfo[i + 3] << '\t' << m_ModelData.vecFaceInfo[i + 4] << '\t' << m_ModelData.vecFaceInfo[i + 5] << '\t\t';
		cout << m_ModelData.vecFaceInfo[i + 6] << '\t' << m_ModelData.vecFaceInfo[i + 7] << '\t' << m_ModelData.vecFaceInfo[i + 8] << endl;
	}
}
