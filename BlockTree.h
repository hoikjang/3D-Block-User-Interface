#pragma once

#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkMatrix4x4.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vtkMath.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>

using namespace std;

class Node
{
private:
    int BoxNum; 
    Node* Surf[7]; 
	int parentsurfnumber;
	bool onOff;
	vtkSmartPointer<vtkPolyDataReader> reader;
	vtkSmartPointer<vtkPolyData> polydata;
	
	
public:
    Node(int boxnum);
	void SetBoxType();//����
	void setSurf(Node* Block, int &num) { this->Surf[num]=Block;}//����
	Node* getSurf(int &k){return Surf[k];}//����
	void deleteSurf(int k){this->Surf[k]=NULL;}//����
	void setParent(Node* Parent, int &num) {this->parentsurfnumber=num; this->Surf[num]=Parent;}//����
	void deleteParent(){this->Surf[parentsurfnumber]=NULL; this->parentsurfnumber=0;}//����
	void deleteParentNum(){this->parentsurfnumber=0;}//����
    int getBoxNum() { return this->BoxNum;}//����
	int getParentNum() {return this->parentsurfnumber;}//����
	void setOnoff(bool onoff) { this->onOff=onoff;}//����
	bool getOnoff() { return this->onOff;}//����
	Node* getParentBlock() {return Surf[parentsurfnumber];}//����
	int SearchParent(Node* Parent);//����
	


public:
	vtkSmartPointer<vtkTransform> transform;
	vtkSmartPointer<vtkTransform> transform1;
	vtkSmartPointer<vtkPolyData> transformedbox;
	vtkSmartPointer<vtkTransformFilter> transformFilter;
	vtkSmartPointer<vtkTransform> Matrix;
	
public:
	void GetTransform(vtkSmartPointer<vtkTransform> TM);//����
	void SetTransform(vtkSmartPointer<vtkTransform> matrix);//����
	void SetIdentity(){this->transform=vtkSmartPointer<vtkTransform>::New();}//����
	void getTransformedBox(vtkSmartPointer<vtkPolyData> poly) 
	{poly->DeepCopy(this->transformedbox);}//�����۵�
	void Concatenation(vtkSmartPointer<vtkTransform> TR);//����
	void getConcatenatedTransform(vtkSmartPointer<vtkTransform> TR);//����
	~Node();
};
 

class Tree 
{
private:
    Node* Root;
    bool Onoff;
public:
    Tree() { Root = NULL;}//����
    Tree(Node* root) { this->Root = root; Onoff=false;}//����
	void setOnoff(bool onoff){this->Onoff=onoff;}//����
	bool getOnoff(){return this->Onoff;}//����
};



