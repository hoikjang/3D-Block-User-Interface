#pragma once

#include "Cube.h"
#include "BlockTree.h"
//#include "Rotate.h"
#include <vtkSmartPointer.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <afxwin.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vtkMath.h>
#include <vtkProperty.h>
#include <algorithm>
#include <vtkMatrix4x4.h>
#include <vtkMatrix3x3.h>
#include <fstream>
#include <sstream>
#include <vtkQuaternion.h>
//#include <Eigen\Geometry>
//#include <Eigen\Dense>
#include <math.h>
//using namespace Eigen;
using namespace std;


class BoxData
{
private:
	
	//EulerAngle eulerangle;
	
	
	int baseblocknum;     //���̽���� ����
	bool eventonoff;     //�̺�Ʈ �߻� ����

	//blocktree
	int size1;
	int blocknumber1;
	int blocknumber2;
	int existence;
	int boxidnum[2];
	int basenum;
	int sep;
	int box1;
	int box2;
	int plane1;
	int plane2;
	int baseblock1;
	int baseblock2;
	int boxdata1;
	int boxdata2;

	//boxdata extract
	double rot[5][3];
	char basechar[5];
	int a,b,c,d,e;
	int val;
	CString app, bpp, cpp, dpp, epp[5];
	bool base[5];
	double qw[5];
	double qx[5];
    double qy[5];
	double qz[5];
	ofstream myfile;
	
	int decimal[6], sign[6];
	vtkSmartPointer<vtkMatrix4x4> matrix[3];
	//BoxSize
	int basecont;
	int boxcount2;
	string str1;
	CString str2;
	CString str3;
	CString str4;
	CString str5;
	int boxid1;
	int boxplanenum1;
	int boxsep1;

	//boxiterator
	vector<string>::iterator boxiter;
	vector<int>::iterator iditer;
	vector<int>::iterator planeiter;
	vector<int>::iterator sepiter;

public:
	int blocknum;         //���� ����� ��� ����Ÿ ���� 
	
	//ȸ�� ������
	//Quaterniond q;
	double x[5];
	double y[5];
	double z[5];
	vtkSmartPointer<vtkTransform> TM[7];
	vector<string> boxdata; //�ڽ� ������
	vector<int> boxid;      //�ڽ��� ID
	vector<int> boxplanenum;//�ڽ� �� ��ȣ      �� �� ������ �ϳ��� ����ü�� ����
	vector<int> boxsep;
	vtkQuaternion<double> q;
    double Q[3][3];
	double mat3[3][3];
	double mat31[3][3];
	double mat4[16];
	double trans[3][3];
	double QT[3][3];
public:
	BoxData();
	//Quaterniond euler2Quaternion(const double roll, const double pitch, const double yaw);
	void DataExtract(CString &str); //������ ����
	void BoxSize(CString &BoxID); //�ڽ� ������ �ױ�
	void BoxTreeMake(int &num); //��� ���� ����, �и� ���� Ȯ��
	void EraseBox();
	void EraseBox(int num);
	void DeleteBoxDataSep(int boxdata);
	//void DeleteBoxDataSep(string boxdata);
	void DeleteBoxData(int boxdata);
	void DeleteBoxDataID(int boxid);
	void mat3tomat4(double mat3[3][3], double mat4[16]);
	void TransitionMatrix3x3(double T[3][3], double Q[3][3], double Result[3][3]);
	void TurnOnBox(int &num);
	void BaseSearch();
	void seteventonoff(bool onoff){this->eventonoff=onoff;}
	bool geteventonoff(){ return this->eventonoff;}
	~BoxData();
};

