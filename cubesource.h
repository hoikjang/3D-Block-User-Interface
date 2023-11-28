#ifndef __CubeSource_h
#define __CubeSource_h

#include "vtkCubeSource.h"
#include "vtkPoints.h"
#include "vtkPointData.h"
#include "vtkAppendPolyData.h"
#include <vtkCleanPolyData.h>
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkMath.h"
#include "vtkPolyData.h"
#include "vtkPolyDataWriter.h"
#include "vtkSmartPointer.h"
#include <vtkLookupTable.h>
#include <vtkPolyDataReader.h>
#include <vtkMatrix4x4.h>


using namespace std;

class CubeSource
{
private:
	class Box
	{
	private:
	vtkSmartPointer<vtkPolyDataReader> reader;
	vtkSmartPointer<vtkPolyData> polydata;
	vtkSmartPointer<vtkPolyData> final_cube;
	public:
		Box(string &ID)  //�ʱ�ȭ ���� �߻� ���� ����
		{};
	}; //���ο��� �ܺ�Ŭ���� �Լ� ��� �����Ѱ�??
	vector<Box> box; // �ʱ� �޸� ����

	vtkSmartPointer<vtkAppendPolyData> appendFilter;
	vtkSmartPointer<vtkAppendPolyData> appendFilter;
	vtkSmartPointer<vtkCleanPolyData> cleanFilter;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkPolyDataWriter> writer;
	void MergePolyData(vector<Box> &box);

public:

	vtkSmartPointer<vtkPolyDataReader> reader;
	vtkSmartPointer<vtkPolyData> polydatagroup[5]; //�����Ѱ�??
	vtkSmartPointer<vtkPoints> centers;
	vtkSmartPointer<vtkPoints> normals;
	vtkSmartPointer<vtkPolyData> final_cube;
	vtkSmartPointer<vtkPolyData> centers_poly;
	vtkSmartPointer<vtkPolyData> normals_poly;
	vtkSmartPointer<vtkPolyData> transformed_centers;
	vtkSmartPointer<vtkPolyData> transformed_normals;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkTransform> transform; 

	int Num_Sur;
	string ID;
	vector<string> BoxID;
	double center[3];
	double vec[3];
	double rad;
	double rot_vec[3];
	double trans[3];
	
	
	void initialization();
	void MergePolyData(); //�Լ��������� ����, Box�迭�� ���� ������, �迭 ���� ���� �ľ�
	void make_actor_Base();
	void make_actor();
	void del();

	void RotateActor(vtkSmartPointer<vtkMatrix4x4> rotat);
	void Move(double x1, double y1, double z1, double x2, double y2, double z2, int num_sur);
	void rotate(double x1, double y1, double z1, double x2, double y2, double z2, double vec[3], int num_sur);
	void rotate(int rx, int ry, int rz);
	void translate(double vec[3], int num_sur);

};


#endif
	