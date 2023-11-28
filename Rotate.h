#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
#include <vtkMath.h>
#include <vtkTransform.h>

class EulerAngle
{
private:
	vtkSmartPointer<vtkMatrix4x4> TM;
    vtkSmartPointer<vtkTransform> transform;
public:
	EulerAngle()
	{
		this->TM=vtkSmartPointer<vtkMatrix4x4>::New();
		this->transform=vtkSmartPointer<vtkTransform>::New();
	}
	void SetQuatRotation(int &box);
	void SetRotation(int &box);//정상 작동
	void GetOrientation(int &box);//정상 작동
};


double cal_align(double vec1[3], double vec2[3], double vec_result[3]);
void cal_translation(double pt1[3], double pt2[3], double trans[3]);