#pragma once


#include "BlockTree.h"
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPolyDataWriter.h>
#include <vtkLight.h>
#include <vtkLightActor.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkLookupTable.h>


class BoxRenderer
{
private:

	vtkSmartPointer<vtkRenderWindow> renWin;
	vtkSmartPointer<vtkRenderer> ren[5]; 
	vtkSmartPointer<vtkRenderWindowInteractor> iren1;
	vtkSmartPointer<vtkPolyDataWriter> writer;
	vtkSmartPointer<vtkAppendPolyData> appendFilter;
	vtkSmartPointer<vtkCleanPolyData> cleanFilter;
	vtkSmartPointer<vtkPolyDataMapper> mapper[6];
	vtkSmartPointer<vtkActor> actor[5];
	vtkSmartPointer<vtkTransform> IM;
	vtkSmartPointer<vtkLight> light;
	vtkSmartPointer<vtkLight> backLight;
	vtkSmartPointer<vtkLightActor> lightActor;
	vtkSmartPointer<vtkCamera> cam1;
	vtkSmartPointer<vtkPolyDataReader> reader;
	vtkSmartPointer<vtkPolyData> polydata;
	vtkSmartPointer<vtkAxesActor> axes;
	vtkSmartPointer<vtkOrientationMarkerWidget> widget;
	vtkSmartPointer<vtkLookupTable> lut;
	int k[5];//박스 렌더링 순서
	int c1[5];//rgb setting
	int c2[5];
	int c3[5];
	double xmins[4];
    double xmaxs[4];
    double ymins[4];
    double ymaxs[4];
	int base;
	int stat;

public:
	
	BoxRenderer(); 
	void Renderer();
	void BaseGroupNumber();
	void MergePolyData();
	void Renderer(bool &contact, int &size);
	void AppendFilter(Node* Leaf, vtkSmartPointer<vtkTransform> TR);
	void ActorDistribution();
	~BoxRenderer();
};

