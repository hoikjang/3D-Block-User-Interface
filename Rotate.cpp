#include "Rotate.h"
#include "header.h"

void EulerAngle::SetQuatRotation(int &box)
{
	this->transform->RotateWXYZ(variables.boxdata.w[box],variables.boxdata.x[box],variables.boxdata.y[box],variables.boxdata.z[box]);
}

void EulerAngle::SetRotation(int &box)//정상 작동
{
	this->transform=vtkSmartPointer<vtkTransform>::New();
	this->transform->RotateX(-90);
	//this->transform->RotateX(variables.boxdata.z[box]);
	//this->transform->RotateY(variables.boxdata.y[box]);
	//this->transform->RotateZ(variables.boxdata.x[box]);
	
}


void EulerAngle::GetOrientation(int &box)//정상 작동
{
	//double rot[3]={0};
	//this->transform->GetOrientation(rot);//맞나?? 데이터 분배 가장 중요한 부분
	variables.boxdata.TM[box]->DeepCopy(transform);
	//variables.boxdata.xr[box]=rot[0];
	//variables.boxdata.yr[box]=rot[1];
	//variables.boxdata.zr[box]=rot[2];
}

double cal_align(double vec1[3], double vec2[3], double vec_result[3])
{
	double rad = 0;
	
	vtkMath::Normalize(vec1);
	vtkMath::Normalize(vec2);

	vtkMath::Cross(vec1, vec2, vec_result);
	vtkMath::Normalize(vec_result);

	printf("%lf %lf %lf\n", vec_result[0], vec_result[1], vec_result[2]);

	rad = acos(-(vtkMath::Dot(vec1, vec2)));

	return vtkMath::DegreesFromRadians(rad);
}
	

void cal_translation(double pt1[3], double pt2[3], double trans[3]){
	for(int i=0; i<3; i++){
		trans[i] = pt1[i]-pt2[i];
	}
}