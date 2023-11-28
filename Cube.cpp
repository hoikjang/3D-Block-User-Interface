#include "Cube.h"
#include "header.h"

Cube::Cube() : rad(0), basenum(0), box1(0), box2(0), plane1(0), plane2(0), parent1(0), parent2(0), base1(0), base2(0), baseaxis1(0), baseaxis2(0), baserot1(0), baserot2(0)//정상 작동
{
	this->vec1[0]=0;
	this->vec1[1]=0;
	this->vec1[2]=0;
	this->vec2[0]=0;
	this->vec2[1]=0;
	this->vec2[2]=0;
	this->rot_vec[0]=0;
	this->rot_vec[1]=0;
	this->rot_vec[2]=0;
	this->normals = vtkSmartPointer<vtkPoints>::New();
	this->transform= vtkSmartPointer<vtkTransform>::New();
	this->transform->PostMultiply();
	this->TM1=vtkSmartPointer<vtkTransform>::New();
	this->TM1->PostMultiply();
	this->TM2=vtkSmartPointer<vtkTransform>::New();
	this->TM2->PostMultiply();
	this->TM3=vtkSmartPointer<vtkTransform>::New();
	this->TM3->PostMultiply();
	this->TM4=vtkSmartPointer<vtkTransform>::New();
	this->TM4->PostMultiply();
	this->TM5=vtkSmartPointer<vtkTransform>::New();
	this->TM5->PostMultiply();
	this->TM6=vtkSmartPointer<vtkTransform>::New();
	this->TM6->PostMultiply();
	this->transform->Update();
	this->TM1->Update();
	this->TM2->Update();
	this->TM3->Update();
	this->TM4->Update();
	this->TM5->Update();
	this->TM6->Update();
	SetNormals();
}

void Cube::SetNormals()//정상 작동 가능성 높음
{
	this->normals->InsertNextPoint(0,0,0);
	this->normals->InsertNextPoint(0,0,1);
	this->normals->InsertNextPoint(0,-1,0);
	this->normals->InsertNextPoint(0,0,-1);
	this->normals->InsertNextPoint(0,1,0);
	this->normals->InsertNextPoint(1,0,0);
	this->normals->InsertNextPoint(-1,0,0);
}

int Cube::BoxSeperation(int &blocknumber1, int &blocknumber2)//정상 작동 가능성
{
	BaseClear();
    int parent=ParentCheck(blocknumber1, blocknumber2);//정상
	if(parent==blocknumber1)//정상
	{BoxSeperationProcess(blocknumber1, blocknumber2);//정상
	return 1;}//정상
	else if(parent==blocknumber2)//정상
	{BoxSeperationProcess(blocknumber2, blocknumber1);//정상
	return 1;}//정상
	else//정상
	return 0;//정상
}

int Cube::ParentCheck(int &blocknumber1, int &blocknumber2)//정상
{
	this->box1=variables.boxdata.boxid.at(blocknumber1);//정상
	this->box2=variables.boxdata.boxid.at(blocknumber2);//정상
	//this->plane1=variables.boxdata.boxplanenum.at(blocknumber1);//정상
	//this->plane2=variables.boxdata.boxplanenum.at(blocknumber2);//정상
	//this->parent1=variables.Block[box1].getParentNum();//정상
	//this->parent2=variables.Block[box2].getParentNum();//정상
	if(&(variables.Block[box2])==variables.Block[box1].getParentBlock())//검증 필요
		return blocknumber2;
	else if(&(variables.Block[box1])==variables.Block[box2].getParentBlock())
		return blocknumber1;
	else //정상
		return -1;//정상
}

void Cube::BoxSeperationProcess(int &parent, int &child)
{
	    BaseClear();//정상
		this->box1=variables.boxdata.boxid.at(parent);//정상
		this->box2=variables.boxdata.boxid.at(child);//정상
		this->plane1=variables.boxdata.boxplanenum.at(parent);//정상
		this->boxdata1=atoi(variables.boxdata.boxdata.at(parent).c_str());
	    this->boxdata2=atoi(variables.boxdata.boxdata.at(child).c_str());
	    variables.Block[box2].deleteParent();//정상
		variables.Block[box1].deleteSurf(plane1);//정상
		BaseSearch(&(variables.Block[box2]));//정상
		int k=6;//정상
		if(this->basenum>0)//정상
		{
			for(unsigned int i=0; i<this->base.size(); ++i)//정상
			{
				if(k>base.at(i))
			    k=base.at(i);
			}
		variables.Block[box2].SetIdentity();//정상
		variables.Base[k].setOnoff(true);//정상
		baseid=k;
		baseonoff=1;
		SearchandTransformParent(&(variables.Block[k]));//정상
		variables.boxdata.DeleteBoxDataSep(this->boxdata1);//정상
	    variables.boxdata.DeleteBoxDataSep(this->boxdata2);//정상
		variables.boxdata.DeleteBoxData(this->boxdata1-10000);
		variables.boxdata.DeleteBoxData(this->boxdata2-10000);
		BaseClear();//정상
		}
		else//정상
		{
			variables.boxdata.DeleteBoxDataSep(this->boxdata1);//정상
	        variables.boxdata.DeleteBoxDataSep(this->boxdata2);//정상
		    variables.boxdata.DeleteBoxData(this->boxdata1-10000);
		    variables.boxdata.DeleteBoxData(this->boxdata2-10000);
			OtherBoxSearchandOFF(&(variables.Block[box2]));//정상
		}
}



void Cube::BaseSearch(Node* Leaf)//정상 작동 가능성 높음..
{
	  if(Leaf==NULL)//정상
	  return;//정상
	  int k=Leaf->getParentNum();//정상
	  for(int i=1; i<k;++i)//정상
	  {
	   BaseSearch(Leaf->getSurf(i));//정상
	  }
	  for(int i=k+1; i<7;++i)//정상
	  {
	   BaseSearch(Leaf->getSurf(i));//정상
	  }
	  int j=0;//정상
	  j=Leaf->getBoxNum();//정상
	  if(j<6)//정상
	  {
		  this->basenum+=1;//정상
		  this->base.push_back(j);//정상
	  }
}

void Cube::BaseSearchParent(Node* Leaf)//접촉 박스에서 시작하여 베이스 블록까지 검색하여 cube의 base 벡터에 차례로 저장함
{
	  if(Leaf==NULL)
	  return;
	  int j=0;
	  j=Leaf->getBoxNum();//현재 블록의 박스 ID를 추출함
	  if((j<6)&&(variables.Base[j].getOnoff()))//현재 블록의 박스 ID가 6보다 작고(베이스 여부) 켜져 있을 경우 실행함
	  {
	    this->basenum+=1;//베이스 블록 확인될 때마다 한 개씩 증가시킴
		this->base.push_back(j);//base 벡터에 각 숫자를 저장함
	  }
	  BaseSearchParent(Leaf->getParentBlock());//재귀함수로 검색해 나감
}


void Cube::SearchandTransformParent(Node* Current)
{ 
  if(Current==NULL)//정상
	  return;
  vtkSmartPointer<vtkTransform> TR1=vtkSmartPointer<vtkTransform>::New();//정상
  Current->GetTransform(TR1);//정상 작동 가능성, 입력된 Matrix가 변화 하는지 확인..
  SearchandTransformParent(Current->getParentBlock(), Current, TR1);
  Current->SetIdentity();//정상
  Current->deleteParentNum();//정상

}

void Cube::SearchandTransformParent(Node* Current, Node* NewParent, vtkSmartPointer<vtkTransform> TR)//정상
{ 
  
  if(Current==NULL)//정상
	  return;
  vtkSmartPointer<vtkTransform> TR2=vtkSmartPointer<vtkTransform>::New();//정상
  int newparentplane=0;//정상
  Current->GetTransform(TR2);//정상 작동 가능성, 입력된 Matrix가 변화 하는지 확인..
  SearchandTransformParent(Current->getParentBlock(), Current, TR2);//정상
  TR->Inverse();//정상
  Current->SetTransform(TR);//정상
  Current->deleteParentNum();//정상
  newparentplane=Current->SearchParent(NewParent);//정상
  Current->setParent(NewParent, newparentplane);//정상

}

void Cube::OtherBoxSearchandOFF(Node* Leaf)//정상
{
	  if(Leaf==NULL)//정상
	  return;//정상
	  int k=Leaf->getParentNum();//정상
	  for(int i=1; i<k;++i)//정상
	  {
	   OtherBoxSearchandOFF(Leaf->getSurf(i));//정상
	   Leaf->deleteSurf(i);//정상
	  }
	  for(int i=k+1; i<7;++i)//정상
	  {
	   OtherBoxSearchandOFF(Leaf->getSurf(i));//정상
	   Leaf->deleteSurf(i);//정상
	  }
	  int boxidnum=Leaf->getBoxNum();
	  variables.boxdata.DeleteBoxDataID(boxidnum);
	  Leaf->setOnoff(false);//정상
	  Leaf->SetIdentity();//정상
	  Leaf->deleteParent();//정상
}


void Cube::GroupConverge(int &blocknum1, int &blocknum2)
{
  BaseClear();
  this->box1=variables.boxdata.boxid.at(blocknum1);//정상 작동 가능성
  this->box2=variables.boxdata.boxid.at(blocknum2);//정상 작동 가능성
  this->plane1=variables.boxdata.boxplanenum.at(blocknum1);//정상 작동 가능성
  this->plane2=variables.boxdata.boxplanenum.at(blocknum2);//정상 작동 가능성
  Node *Parent=variables.Block[box2].getParentBlock();//정상 작동 가능성
  variables.Block[box2].GetTransform(this->TM1);//정상 작동 가능성, 입력 행렬이 변하는가?
  SearchandTransformParent(Parent, &(variables.Block[box2]), this->TM1);//정상 작동 가능성
  variables.Block[box1].setSurf(&(variables.Block[box2]), plane1);//정상 작동 가능성
  variables.Block[box2].setParent(&(variables.Block[box1]), plane2);//정상 작동 가능성
  this->TM2=GetMatrixTransform(plane1, plane2);
  variables.Block[box2].SetTransform(this->TM2);//정상 작동 가능성
}

void Cube::GroupConverge(int &blocknum1, int &blocknum2, int &base1, int &base2)
{
  BaseClear();//Cube 클래스에서 사용되는 변수 초기화
  this->box1=variables.boxdata.boxid.at(blocknum1);//Basegroup1에 속한 접촉 박스의 박스 ID 구하여 저장
  this->box2=variables.boxdata.boxid.at(blocknum2);//Basegroup2에 속한 접촉 박스의 박스 ID 구하여 저장
  this->plane1=variables.boxdata.boxplanenum.at(blocknum1);//Basegroup1에 속한 접촉 박스의 접촉면 구하여 저장
  this->plane2=variables.boxdata.boxplanenum.at(blocknum2);//Basegroup2에 속한 접촉 박스의 접촉면 구하여 저장
  this->base1=base1;//Base1의 박스 ID 저장
  this->base2=base2;//Base2의 박스 ID 저장
  GroupConvergeBoxRotationCal();//접촉된 두 박스 사이의 Base1과 Base2의 상대 회전이 구현된 TM을 구하여 this->transform에 저장한다.
  this->TM1=vtkSmartPointer<vtkTransform>::New();
  this->TM1->PostMultiply();
  Node *Parent=variables.Block[box2].getParentBlock();//ParentBlock 추출
  variables.Block[box2].GetTransform(this->TM1);//BaseGroup2에서의 접촉 박스의 TM을 구한다.
  SearchandTransformParent(Parent, &(variables.Block[box2]), this->TM1);//ParentBlock을 찾아 올라가며 Parent와 Child 블록의 TM을 교환하여 저장한다.
  variables.Block[box1].setSurf(&(variables.Block[box2]), plane1);//BaseGroup1의 접촉 박스에 BaseGroup2의 접촉 박스 연결 노드를 설정한다.
  variables.Block[box2].setParent(&(variables.Block[box1]), plane2);//BaseGroup2의 접촉 박스에 BaseGroup1의 접촉 박스를 ParentBlock으로 설정한다.
  variables.Block[box2].SetTransform(this->transform);//접촉된 두 박스 사이의 Base1과 Base2의 상대 회전이 구현된 TM을 BaseGroup2의 접촉 박스에 저장한다. 
}

void Cube::GroupConvergeBoxRotationCal()//접촉된 두 박스 사이의 Base1과 Base2의 상대 회전이 구현된 TM을 구한다.
{ 
  BaseRelRotCal();//base2의 base1에 대한 상대 회전 구하여 this->transform에 저장
  this->transform->Concatenate(TM5);//Base1과 Base2의 상대 회전을 BaseGroup2의 Base2부터 접촉 박스까지의 TM을 모두 곱한 것의 처음 부분에 곱한다. 
  this->TM1->SetInverse(this->TM4);//BaseGroup1의 Base1부터 접촉 박스까지의 TM을 모두 곱한 것의 역행렬을 구한다.
  this->TM2->DeepCopy(this->transform);//this->transform을 TM2에 복사한다.
  this->TM2->Concatenate(this->TM1);//TM2에 TM1의 값을 곱한다. 접촉박스 사이의 TM을 구하는 과정이다.
  GetMatrixTransform(this->plane1,this->plane2, this->TM2);//TM2에서 접촉 박스 사이의 상대 회전을 추출하고 Translation을 구하고 적용하여 Translation이 적용된 접촉 박스 사이의 TM을 구하여 this->transform에 저장한다. 
}


void Cube::BaseRelRotCal()
{
  this->TM4->DeepCopy(GroupConvergeRotatGet(&(variables.Block[this->box1])));//Basegroup1의 base1에서 접촉 블록까지의 TM의 곱을 저장//정상 작동
  this->TM6=vtkSmartPointer<vtkTransform>::New();//재사용을 위한 TM6의 초기화
  this->TM6->PostMultiply();
  this->TM5->DeepCopy(GroupConvergeRotatGet(&(variables.Block[this->box2])));//Basegroup2의 base2에서 접촉 블록까지의 TM의 곱을 저장//정상 작동
  this->normals->GetPoint(this->plane1, this->vec1);//Basegroup1에 속한 접촉 박스의 접촉면의 노멀 벡터 구함
  this->normals->GetPoint(this->plane2, this->vec2);//Basegroup2에 속한 접촉 박스의 접촉면의 노멀 벡터 구함
  this->TM4->TransformVector(this->vec1,this->vec1);//Basegroup1에 속한 접촉 박스의 접촉면의 노멀 벡터로 base1의 접촉 방향 벡터를 구함 
  this->TM5->TransformVector(this->vec2,this->vec2);//Basegroup2에 속한 접촉 박스의 접촉면의 노멀 벡터로 base2의 접촉 방향 벡터를 구함//이쪽 문제
  this->baseaxis1=NormalCal(this->vec1);//base1의 접촉 방향 벡터가 무슨 축인지 구함//정상 작동
  this->baseaxis2=NormalCal(this->vec2);//base2의 접촉 방향 벡터가 무슨 축인지 구함//정상 작동
  this->baserot1=this->BaseRelAxisRotCal(baseaxis1 ,this->base1);//base1의 접촉 방향축 회전각 구함
  this->baserot2=this->BaseRelAxisRotCal(baseaxis2 ,this->base2);//base2의 접촉 방향축 회전각 구함
  CalRot(baseaxis2, baserot1, baserot2);//base2의 base1에 대한 상대 회전을 구하여 this->transform에 저장
}

vtkSmartPointer<vtkTransform> Cube::GroupConvergeRotatGet(Node *Leaf)//베이스 블록에서 접촉박스까지의 TM의 곱을 구함 //정상 작동
{
if(Leaf==NULL)
return NULL;//Leaf가 없을시 반환
vtkSmartPointer<vtkTransform> Rot=vtkSmartPointer<vtkTransform>::New();
Leaf->GetTransform(Rot);//현재 블록의 TM을 구함
GroupConvergeRotatGet(Leaf->getParentBlock());//Parent블록에 대한 재귀 호출
this->TM6->Concatenate(Rot);//정상 작동 가능성, Node의 Concatenation에서 사용 검증됨, 다만 이 때 동적 할당이 아닌 DeepCopy된 값임, 최대 2회씩 사용함
return (this->TM6);
}

int Cube::NormalCal(double *vec)//베이스 블럭의 접촉 방향 벡터가 무슨 축인지 구함
{
	if((vec[0]>=-0.1)&&(vec[0]<=0.1))
	{
		if((vec[1]>=-0.1)&&(vec[1]<=0.1))
		{
			if((vec[2]>=0.9)&&(vec[2]<=1.1))
				return 1;
			else
				return 3;
		}
	  else if((vec[1]>=0.9)&&(vec[1]<=1.1))
		  return 2;
	  
	  else
		  return 4;
	}
  else if((vec[0]>=0.9)&&(vec[0]<=1.1))
	  return 5;
  else
	  return 6; 
  
}

double Cube::BaseRelAxisRotCal(int &num, int &box)//베이스 블록의 접촉 방향축 회전각 구함
{
	switch(num)
	{
		case 1:
			return variables.boxdata.z[box-1];
		case 3:
			return variables.boxdata.z[box-1]*-1;
		case 2:
			return variables.boxdata.y[box-1]*-1;
		case 4:
			return variables.boxdata.y[box-1];
		case 5:
			return variables.boxdata.x[box-1];
		case 6:
			return variables.boxdata.x[box-1]*-1;
	}
}

void Cube::CalRot(int &baseaxis2, double &x1, double &x2)//base2의 base1에 대한 상대 회전을 구하여 this->transform에 저장
{
	if(((x1-x2)<=110)&&((x1-x2)>=70))
		Rotate(90, baseaxis2);//회전축을 판별하고 그에 맞는 회전값 대입
	else if(((x1-x2)<=-250)&&((x1-x2)>=-270))
		Rotate(90, baseaxis2);
	else if(((x1-x2)<=200)&&((x1-x2)>=160))
		Rotate(180, baseaxis2);
	else if(((x1-x2)<=-160)&&((x1-x2)>=-200))
		Rotate(180, baseaxis2);
	else if(((x1-x2)<=290)&&((x1-x2)>=250))
		Rotate(-90, baseaxis2);
	else if(((x1-x2)<=-70)&&((x1-x2)>=-110))
		Rotate(-90, baseaxis2);
}

void Cube::Rotate(int rot, int &axis)//회전축을 판별하고 그에 맞는 회전값 대입
{
	switch(axis)
	{
		case 1:
		case 3:
			this->transform->RotateZ(rot);
			break;
		case 2:
		case 4:
			this->transform->RotateY(rot);
			break;
		case 5:
		case 6:
			this->transform->RotateX(rot);
			break;
	}
}


vtkSmartPointer<vtkTransform> Cube::GetMatrixTransform(int &planenum1, int &planenum2, vtkSmartPointer<vtkTransform> Rot)//Rot에서 접촉 박스 사이의 상대 회전을 추출하고 Translation을 구하고 적용하여 Translatoin이 적용된 접촉 박스 사이의 TM을 구한다.
{
        int num[2]={planenum1,planenum2};//가능한가?
        double size[2];
        double vec3[3];
        double scalar;
		double rotation[4];
	    this->normals->GetPoint(num[0], this->vec1);//정상 작동 가능성
        this->normals->GetPoint(num[1], this->vec2);//정상 작동 가능성
        vtkMath::Normalize(this->vec1);//정상 작동 가능성
        vtkMath::Normalize(this->vec2);//정상 작동 가능성
        vtkMath::Cross(vec1, vec2, this->rot_vec);//정상 작동 가능성
        vtkMath::Normalize(this->rot_vec);//정상 작동 가능성
        this->rad = vtkMath::DegreesFromRadians(acos((vtkMath::Dot(vec1, vec2))));//정상 작동 가능성
		
        for(int i=0; i<2; i++)//정상 작동 가능성
        {
        switch(num[i])
		{
		case 1:
		case 2:
		case 3:
		case 4:
		size[i]=24;
		break;
		
		case 5:
		case 6:
		size[i]=43;
		break;
		}
        
		}
        scalar=size[0]+size[1];//정상 작동 가능성
		vec3[0]=this->vec1[0];//정상 작동 가능성
		vec3[1]=this->vec1[1];//정상 작동 가능성
		vec3[2]=this->vec1[2];//정상 작동 가능성
        vtkMath::MultiplyScalar(vec3, scalar);//정상 작동 가능성
        
        //this->TM2->Translate(vec3);//정상 작동 가능성
		Rot->GetOrientationWXYZ(rotation);
		this->transform=vtkSmartPointer<vtkTransform>::New();
		this->transform->PostMultiply();
		this->transform->RotateWXYZ(this->rad, this->rot_vec);
		this->transform->RotateWXYZ(rotation[0],rotation[1],rotation[2],rotation[3]);
	    this->transform->Translate(vec3);
	    return this->transform;//정상 작동 가능성
} 

void Cube::BoxConverge(int &blocknum1, int &blocknum2)
{  
  BaseClear();
  this->box1=variables.boxdata.boxid.at(blocknum1);//정상
  this->box2=variables.boxdata.boxid.at(blocknum2);//정상
  this->plane1=variables.boxdata.boxplanenum.at(blocknum1);//정상
  this->plane2=variables.boxdata.boxplanenum.at(blocknum2);//정상
  this->TM1->DeepCopy(GetMatrixTransform(plane1, plane2));//정상 작동 가능성
  variables.Block[box1].setSurf(&(variables.Block[box2]), plane1);//정상    
  variables.Block[box2].setParent(&(variables.Block[box1]),plane2);//정상
  variables.Block[box2].SetTransform(TM1);//정상
}

vtkSmartPointer<vtkTransform> Cube::GetMatrixTransform(int &planenum1, int &planenum2)//회전이 반대인 경우 고려해야 함, 진원형 코드에 존재 하였음. 진원형 코드 그냥 사용 고려, 상대회전
{
        int num[2]={planenum1,planenum2};//가능한가?
		int area[2]={0};
		double size[2];
        double scalar;
		double vec3[3];
	    this->normals->GetPoint(num[0], this->vec1);//정상 작동 가능성
        this->normals->GetPoint(num[1], this->vec2);//정상 작동 가능성
        vtkMath::Normalize(this->vec1);//정상 작동 가능성
        vtkMath::Normalize(this->vec2);//정상 작동 가능성
        vtkMath::Cross(vec1, vec2, this->rot_vec);//정상 작동 가능성
        vtkMath::Normalize(this->rot_vec);//정상 작동 가능성
        this->rad = vtkMath::DegreesFromRadians(acos((vtkMath::Dot(vec1, vec2))));//정상 작동 가능성

        //this->TM1->RotateWXYZ(this->rad, this->rot_vec);//정상 작동 가능성
        for(int i=0; i<2; i++)//정상 작동 가능성
        {
        switch(num[i])
		{
		case 1:
		case 2:
		case 3:
		case 4:
		size[i]=24;
		break;
		
		case 5:
		case 6:
		size[i]=43;
		break;
		}
        
		}
        scalar=size[0]+size[1];//정상 작동 가능성
		vec3[0]=this->vec1[0];//정상 작동 가능성
		vec3[1]=this->vec1[1];//정상 작동 가능성
		vec3[2]=this->vec1[2];//정상 작동 가능성
        vtkMath::MultiplyScalar(vec3, scalar);//정상 작동 가능성
		for(int i=0; i<2;++i)
		{
			switch(num[0])
			{
		case 1:
		case 2:
	    case 3:
		case 4:
			area[i]=1;
			break;
		case 5:
		case 6:
			area[i]=2;
			break;
 		}
		}
		if(area[0]==area[1])
		{
			switch((int)rad)
			{
			case 180:
				break;
			case 90:
				this->transform->RotateWXYZ(this->rad, this->rot_vec);
				break;
			case 0:
				this->transform->RotateWXYZ(180,0,1,0);
				break;
			}
		}
		else
			this->transform->RotateWXYZ(this->rad, this->rot_vec);


		this->transform->Translate(vec3);
		return this->transform;//정상 작동 가능성
}


void Cube::BaseClear()//정상
{
	this->basenum=0;
	this->base.clear();
	this->parent1=0;
	this->parent2=0;
	this->box1=0;
	this->box2=0;
	this->plane1=0;
	this->plane2=0;
	this->baseaxis1=0;
    this->baseaxis2=0;
    this->baserot1=0;
    this->baserot2=0;
	this->vec1[0]=0;
	this->vec1[1]=0;
	this->vec1[2]=0;
	this->vec2[0]=0;
	this->vec2[1]=0;
	this->vec2[2]=0;
	this->rad=0;
	this->rot_vec[0]=0;
	this->rot_vec[1]=0;
	this->rot_vec[2]=0;
	this->transform=vtkSmartPointer<vtkTransform>::New();
	this->transform->PostMultiply();
	this->TM1=vtkSmartPointer<vtkTransform>::New();
	this->TM1->PostMultiply();
	this->TM2=vtkSmartPointer<vtkTransform>::New();
	this->TM2->PostMultiply();
	this->TM3=vtkSmartPointer<vtkTransform>::New();
	this->TM3->PostMultiply();
	this->TM4=vtkSmartPointer<vtkTransform>::New();
	this->TM4->PostMultiply();
	this->TM5=vtkSmartPointer<vtkTransform>::New();
	this->TM5->PostMultiply();
	this->TM6=vtkSmartPointer<vtkTransform>::New();
	this->TM6->PostMultiply();
}


Cube::~Cube()//정상 작동 가능성
{
	delete []&vec1;
	delete []&vec2;
	delete []&rot_vec;
	this->normals->Delete();
	this->transform->Delete();
	this->base.clear();
	this->TM1->Delete();
	this->TM2->Delete();
	this->TM3->Delete();
}