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
	void SetBoxType();//정상
	void setSurf(Node* Block, int &num) { this->Surf[num]=Block;}//정상
	Node* getSurf(int &k){return Surf[k];}//정상
	void deleteSurf(int k){this->Surf[k]=NULL;}//정상
	void setParent(Node* Parent, int &num) {this->parentsurfnumber=num; this->Surf[num]=Parent;}//정상
	void deleteParent(){this->Surf[parentsurfnumber]=NULL; this->parentsurfnumber=0;}//정상
	void deleteParentNum(){this->parentsurfnumber=0;}//정상
    int getBoxNum() { return this->BoxNum;}//정상
	int getParentNum() {return this->parentsurfnumber;}//정상
	void setOnoff(bool onoff) { this->onOff=onoff;}//정상
	bool getOnoff() { return this->onOff;}//정상
	Node* getParentBlock() {return Surf[parentsurfnumber];}//정상
	int SearchParent(Node* Parent);//정상
	


public:
	vtkSmartPointer<vtkTransform> transform;
	vtkSmartPointer<vtkTransform> transform1;
	vtkSmartPointer<vtkPolyData> transformedbox;
	vtkSmartPointer<vtkTransformFilter> transformFilter;
	vtkSmartPointer<vtkTransform> Matrix;
	
public:
	void GetTransform(vtkSmartPointer<vtkTransform> TM);//정상
	void SetTransform(vtkSmartPointer<vtkTransform> matrix);//정상
	void SetIdentity(){this->transform=vtkSmartPointer<vtkTransform>::New();}//정상
	void getTransformedBox(vtkSmartPointer<vtkPolyData> poly) 
	{poly->DeepCopy(this->transformedbox);}//정상작동
	void Concatenation(vtkSmartPointer<vtkTransform> TR);//정상
	void getConcatenatedTransform(vtkSmartPointer<vtkTransform> TR);//정상
	~Node();
};
 

class Tree 
{
private:
    Node* Root;
    bool Onoff;
public:
    Tree() { Root = NULL;}//정상
    Tree(Node* root) { this->Root = root; Onoff=false;}//정상
	void setOnoff(bool onoff){this->Onoff=onoff;}//정상
	bool getOnoff(){return this->Onoff;}//정상
};



