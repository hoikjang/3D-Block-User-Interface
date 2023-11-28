#pragma once


#include "BlockTree.h"
#include "BoxData.h"

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>


class Cube
{

private:
	double vec1[3];
	double vec2[3];
	double rad;
	double rot_vec[3];
	vtkSmartPointer<vtkPoints> normals;
	vtkSmartPointer<vtkTransform> transform;
	int box1;
	int box2;
	int plane1;
	int plane2;
	int parent1;
	int parent2;
	int boxdata1;
	int boxdata2;
	int base1;
	int base2;
	int baseaxis1;
    int baseaxis2;
    double baserot1;
    double baserot2;

public:
	int basenum;
	vector<int> base;
	vtkSmartPointer<vtkTransform> TM1;
	vtkSmartPointer<vtkTransform> TM2;
	vtkSmartPointer<vtkTransform> TM3;
	vtkSmartPointer<vtkTransform> TM4;
	vtkSmartPointer<vtkTransform> TM5;
	vtkSmartPointer<vtkTransform> TM6;
	

public:
	Cube();
	void SetNormals();
	void GroupConverge(int &blocknum1, int &blocknum2);
	void GroupConverge(int &blocknum1, int &blocknum2, int &base1, int &base2);
	void GroupConvergeBoxRotationCal();
	void BaseRelRotCal();
	int NormalCal(double *vec);
	double BaseRelAxisRotCal(int &num, int &box);
	void CalRot(int &baseaxis2, double &x1, double &x2);
	void Rotate(int rot, int &axis);
	vtkSmartPointer<vtkTransform> GroupConvergeRotatGet(Node *Leaf);
	void BoxConverge(int &blocknum1, int &blocknum2);
	void SearchandTransformParent(Node* Current);
	void SearchandTransformParent(Node *Current, Node* NewParent, vtkSmartPointer<vtkTransform> TR);
	int BoxSeperation(int &blocknumber1, int &blocknumber2);
	void BoxSeperationProcess(int &parent, int &child);
	int ParentCheck(int &blocknumber1, int &blocknumber2);
	void BaseSearch(Node* Leaf);
	void BaseSearchParent(Node* Leaf);
	void OtherBoxSearchandOFF(Node* Leaf);
	void BaseClear();
	vtkSmartPointer<vtkTransform> GetMatrixTransform(int &planenum1, int &planenum2,vtkSmartPointer<vtkTransform> Rot);
	vtkSmartPointer<vtkTransform> GetMatrixTransform(int &planenum1, int &planenum2);
	~Cube();
};

