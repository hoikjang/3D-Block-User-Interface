#include "Cube.h"
#include "header.h"

Cube::Cube() : rad(0), basenum(0), box1(0), box2(0), plane1(0), plane2(0), parent1(0), parent2(0), base1(0), base2(0), baseaxis1(0), baseaxis2(0), baserot1(0), baserot2(0)//���� �۵�
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

void Cube::SetNormals()//���� �۵� ���ɼ� ����
{
	this->normals->InsertNextPoint(0,0,0);
	this->normals->InsertNextPoint(0,0,1);
	this->normals->InsertNextPoint(0,-1,0);
	this->normals->InsertNextPoint(0,0,-1);
	this->normals->InsertNextPoint(0,1,0);
	this->normals->InsertNextPoint(1,0,0);
	this->normals->InsertNextPoint(-1,0,0);
}

int Cube::BoxSeperation(int &blocknumber1, int &blocknumber2)//���� �۵� ���ɼ�
{
	BaseClear();
    int parent=ParentCheck(blocknumber1, blocknumber2);//����
	if(parent==blocknumber1)//����
	{BoxSeperationProcess(blocknumber1, blocknumber2);//����
	return 1;}//����
	else if(parent==blocknumber2)//����
	{BoxSeperationProcess(blocknumber2, blocknumber1);//����
	return 1;}//����
	else//����
	return 0;//����
}

int Cube::ParentCheck(int &blocknumber1, int &blocknumber2)//����
{
	this->box1=variables.boxdata.boxid.at(blocknumber1);//����
	this->box2=variables.boxdata.boxid.at(blocknumber2);//����
	//this->plane1=variables.boxdata.boxplanenum.at(blocknumber1);//����
	//this->plane2=variables.boxdata.boxplanenum.at(blocknumber2);//����
	//this->parent1=variables.Block[box1].getParentNum();//����
	//this->parent2=variables.Block[box2].getParentNum();//����
	if(&(variables.Block[box2])==variables.Block[box1].getParentBlock())//���� �ʿ�
		return blocknumber2;
	else if(&(variables.Block[box1])==variables.Block[box2].getParentBlock())
		return blocknumber1;
	else //����
		return -1;//����
}

void Cube::BoxSeperationProcess(int &parent, int &child)
{
	    BaseClear();//����
		this->box1=variables.boxdata.boxid.at(parent);//����
		this->box2=variables.boxdata.boxid.at(child);//����
		this->plane1=variables.boxdata.boxplanenum.at(parent);//����
		this->boxdata1=atoi(variables.boxdata.boxdata.at(parent).c_str());
	    this->boxdata2=atoi(variables.boxdata.boxdata.at(child).c_str());
	    variables.Block[box2].deleteParent();//����
		variables.Block[box1].deleteSurf(plane1);//����
		BaseSearch(&(variables.Block[box2]));//����
		int k=6;//����
		if(this->basenum>0)//����
		{
			for(unsigned int i=0; i<this->base.size(); ++i)//����
			{
				if(k>base.at(i))
			    k=base.at(i);
			}
		variables.Block[box2].SetIdentity();//����
		variables.Base[k].setOnoff(true);//����
		baseid=k;
		baseonoff=1;
		SearchandTransformParent(&(variables.Block[k]));//����
		variables.boxdata.DeleteBoxDataSep(this->boxdata1);//����
	    variables.boxdata.DeleteBoxDataSep(this->boxdata2);//����
		variables.boxdata.DeleteBoxData(this->boxdata1-10000);
		variables.boxdata.DeleteBoxData(this->boxdata2-10000);
		BaseClear();//����
		}
		else//����
		{
			variables.boxdata.DeleteBoxDataSep(this->boxdata1);//����
	        variables.boxdata.DeleteBoxDataSep(this->boxdata2);//����
		    variables.boxdata.DeleteBoxData(this->boxdata1-10000);
		    variables.boxdata.DeleteBoxData(this->boxdata2-10000);
			OtherBoxSearchandOFF(&(variables.Block[box2]));//����
		}
}



void Cube::BaseSearch(Node* Leaf)//���� �۵� ���ɼ� ����..
{
	  if(Leaf==NULL)//����
	  return;//����
	  int k=Leaf->getParentNum();//����
	  for(int i=1; i<k;++i)//����
	  {
	   BaseSearch(Leaf->getSurf(i));//����
	  }
	  for(int i=k+1; i<7;++i)//����
	  {
	   BaseSearch(Leaf->getSurf(i));//����
	  }
	  int j=0;//����
	  j=Leaf->getBoxNum();//����
	  if(j<6)//����
	  {
		  this->basenum+=1;//����
		  this->base.push_back(j);//����
	  }
}

void Cube::BaseSearchParent(Node* Leaf)//���� �ڽ����� �����Ͽ� ���̽� ��ϱ��� �˻��Ͽ� cube�� base ���Ϳ� ���ʷ� ������
{
	  if(Leaf==NULL)
	  return;
	  int j=0;
	  j=Leaf->getBoxNum();//���� ����� �ڽ� ID�� ������
	  if((j<6)&&(variables.Base[j].getOnoff()))//���� ����� �ڽ� ID�� 6���� �۰�(���̽� ����) ���� ���� ��� ������
	  {
	    this->basenum+=1;//���̽� ��� Ȯ�ε� ������ �� ���� ������Ŵ
		this->base.push_back(j);//base ���Ϳ� �� ���ڸ� ������
	  }
	  BaseSearchParent(Leaf->getParentBlock());//����Լ��� �˻��� ����
}


void Cube::SearchandTransformParent(Node* Current)
{ 
  if(Current==NULL)//����
	  return;
  vtkSmartPointer<vtkTransform> TR1=vtkSmartPointer<vtkTransform>::New();//����
  Current->GetTransform(TR1);//���� �۵� ���ɼ�, �Էµ� Matrix�� ��ȭ �ϴ��� Ȯ��..
  SearchandTransformParent(Current->getParentBlock(), Current, TR1);
  Current->SetIdentity();//����
  Current->deleteParentNum();//����

}

void Cube::SearchandTransformParent(Node* Current, Node* NewParent, vtkSmartPointer<vtkTransform> TR)//����
{ 
  
  if(Current==NULL)//����
	  return;
  vtkSmartPointer<vtkTransform> TR2=vtkSmartPointer<vtkTransform>::New();//����
  int newparentplane=0;//����
  Current->GetTransform(TR2);//���� �۵� ���ɼ�, �Էµ� Matrix�� ��ȭ �ϴ��� Ȯ��..
  SearchandTransformParent(Current->getParentBlock(), Current, TR2);//����
  TR->Inverse();//����
  Current->SetTransform(TR);//����
  Current->deleteParentNum();//����
  newparentplane=Current->SearchParent(NewParent);//����
  Current->setParent(NewParent, newparentplane);//����

}

void Cube::OtherBoxSearchandOFF(Node* Leaf)//����
{
	  if(Leaf==NULL)//����
	  return;//����
	  int k=Leaf->getParentNum();//����
	  for(int i=1; i<k;++i)//����
	  {
	   OtherBoxSearchandOFF(Leaf->getSurf(i));//����
	   Leaf->deleteSurf(i);//����
	  }
	  for(int i=k+1; i<7;++i)//����
	  {
	   OtherBoxSearchandOFF(Leaf->getSurf(i));//����
	   Leaf->deleteSurf(i);//����
	  }
	  int boxidnum=Leaf->getBoxNum();
	  variables.boxdata.DeleteBoxDataID(boxidnum);
	  Leaf->setOnoff(false);//����
	  Leaf->SetIdentity();//����
	  Leaf->deleteParent();//����
}


void Cube::GroupConverge(int &blocknum1, int &blocknum2)
{
  BaseClear();
  this->box1=variables.boxdata.boxid.at(blocknum1);//���� �۵� ���ɼ�
  this->box2=variables.boxdata.boxid.at(blocknum2);//���� �۵� ���ɼ�
  this->plane1=variables.boxdata.boxplanenum.at(blocknum1);//���� �۵� ���ɼ�
  this->plane2=variables.boxdata.boxplanenum.at(blocknum2);//���� �۵� ���ɼ�
  Node *Parent=variables.Block[box2].getParentBlock();//���� �۵� ���ɼ�
  variables.Block[box2].GetTransform(this->TM1);//���� �۵� ���ɼ�, �Է� ����� ���ϴ°�?
  SearchandTransformParent(Parent, &(variables.Block[box2]), this->TM1);//���� �۵� ���ɼ�
  variables.Block[box1].setSurf(&(variables.Block[box2]), plane1);//���� �۵� ���ɼ�
  variables.Block[box2].setParent(&(variables.Block[box1]), plane2);//���� �۵� ���ɼ�
  this->TM2=GetMatrixTransform(plane1, plane2);
  variables.Block[box2].SetTransform(this->TM2);//���� �۵� ���ɼ�
}

void Cube::GroupConverge(int &blocknum1, int &blocknum2, int &base1, int &base2)
{
  BaseClear();//Cube Ŭ�������� ���Ǵ� ���� �ʱ�ȭ
  this->box1=variables.boxdata.boxid.at(blocknum1);//Basegroup1�� ���� ���� �ڽ��� �ڽ� ID ���Ͽ� ����
  this->box2=variables.boxdata.boxid.at(blocknum2);//Basegroup2�� ���� ���� �ڽ��� �ڽ� ID ���Ͽ� ����
  this->plane1=variables.boxdata.boxplanenum.at(blocknum1);//Basegroup1�� ���� ���� �ڽ��� ���˸� ���Ͽ� ����
  this->plane2=variables.boxdata.boxplanenum.at(blocknum2);//Basegroup2�� ���� ���� �ڽ��� ���˸� ���Ͽ� ����
  this->base1=base1;//Base1�� �ڽ� ID ����
  this->base2=base2;//Base2�� �ڽ� ID ����
  GroupConvergeBoxRotationCal();//���˵� �� �ڽ� ������ Base1�� Base2�� ��� ȸ���� ������ TM�� ���Ͽ� this->transform�� �����Ѵ�.
  this->TM1=vtkSmartPointer<vtkTransform>::New();
  this->TM1->PostMultiply();
  Node *Parent=variables.Block[box2].getParentBlock();//ParentBlock ����
  variables.Block[box2].GetTransform(this->TM1);//BaseGroup2������ ���� �ڽ��� TM�� ���Ѵ�.
  SearchandTransformParent(Parent, &(variables.Block[box2]), this->TM1);//ParentBlock�� ã�� �ö󰡸� Parent�� Child ����� TM�� ��ȯ�Ͽ� �����Ѵ�.
  variables.Block[box1].setSurf(&(variables.Block[box2]), plane1);//BaseGroup1�� ���� �ڽ��� BaseGroup2�� ���� �ڽ� ���� ��带 �����Ѵ�.
  variables.Block[box2].setParent(&(variables.Block[box1]), plane2);//BaseGroup2�� ���� �ڽ��� BaseGroup1�� ���� �ڽ��� ParentBlock���� �����Ѵ�.
  variables.Block[box2].SetTransform(this->transform);//���˵� �� �ڽ� ������ Base1�� Base2�� ��� ȸ���� ������ TM�� BaseGroup2�� ���� �ڽ��� �����Ѵ�. 
}

void Cube::GroupConvergeBoxRotationCal()//���˵� �� �ڽ� ������ Base1�� Base2�� ��� ȸ���� ������ TM�� ���Ѵ�.
{ 
  BaseRelRotCal();//base2�� base1�� ���� ��� ȸ�� ���Ͽ� this->transform�� ����
  this->transform->Concatenate(TM5);//Base1�� Base2�� ��� ȸ���� BaseGroup2�� Base2���� ���� �ڽ������� TM�� ��� ���� ���� ó�� �κп� ���Ѵ�. 
  this->TM1->SetInverse(this->TM4);//BaseGroup1�� Base1���� ���� �ڽ������� TM�� ��� ���� ���� ������� ���Ѵ�.
  this->TM2->DeepCopy(this->transform);//this->transform�� TM2�� �����Ѵ�.
  this->TM2->Concatenate(this->TM1);//TM2�� TM1�� ���� ���Ѵ�. ���˹ڽ� ������ TM�� ���ϴ� �����̴�.
  GetMatrixTransform(this->plane1,this->plane2, this->TM2);//TM2���� ���� �ڽ� ������ ��� ȸ���� �����ϰ� Translation�� ���ϰ� �����Ͽ� Translation�� ����� ���� �ڽ� ������ TM�� ���Ͽ� this->transform�� �����Ѵ�. 
}


void Cube::BaseRelRotCal()
{
  this->TM4->DeepCopy(GroupConvergeRotatGet(&(variables.Block[this->box1])));//Basegroup1�� base1���� ���� ��ϱ����� TM�� ���� ����//���� �۵�
  this->TM6=vtkSmartPointer<vtkTransform>::New();//������ ���� TM6�� �ʱ�ȭ
  this->TM6->PostMultiply();
  this->TM5->DeepCopy(GroupConvergeRotatGet(&(variables.Block[this->box2])));//Basegroup2�� base2���� ���� ��ϱ����� TM�� ���� ����//���� �۵�
  this->normals->GetPoint(this->plane1, this->vec1);//Basegroup1�� ���� ���� �ڽ��� ���˸��� ��� ���� ����
  this->normals->GetPoint(this->plane2, this->vec2);//Basegroup2�� ���� ���� �ڽ��� ���˸��� ��� ���� ����
  this->TM4->TransformVector(this->vec1,this->vec1);//Basegroup1�� ���� ���� �ڽ��� ���˸��� ��� ���ͷ� base1�� ���� ���� ���͸� ���� 
  this->TM5->TransformVector(this->vec2,this->vec2);//Basegroup2�� ���� ���� �ڽ��� ���˸��� ��� ���ͷ� base2�� ���� ���� ���͸� ����//���� ����
  this->baseaxis1=NormalCal(this->vec1);//base1�� ���� ���� ���Ͱ� ���� ������ ����//���� �۵�
  this->baseaxis2=NormalCal(this->vec2);//base2�� ���� ���� ���Ͱ� ���� ������ ����//���� �۵�
  this->baserot1=this->BaseRelAxisRotCal(baseaxis1 ,this->base1);//base1�� ���� ������ ȸ���� ����
  this->baserot2=this->BaseRelAxisRotCal(baseaxis2 ,this->base2);//base2�� ���� ������ ȸ���� ����
  CalRot(baseaxis2, baserot1, baserot2);//base2�� base1�� ���� ��� ȸ���� ���Ͽ� this->transform�� ����
}

vtkSmartPointer<vtkTransform> Cube::GroupConvergeRotatGet(Node *Leaf)//���̽� ��Ͽ��� ���˹ڽ������� TM�� ���� ���� //���� �۵�
{
if(Leaf==NULL)
return NULL;//Leaf�� ������ ��ȯ
vtkSmartPointer<vtkTransform> Rot=vtkSmartPointer<vtkTransform>::New();
Leaf->GetTransform(Rot);//���� ����� TM�� ����
GroupConvergeRotatGet(Leaf->getParentBlock());//Parent��Ͽ� ���� ��� ȣ��
this->TM6->Concatenate(Rot);//���� �۵� ���ɼ�, Node�� Concatenation���� ��� ������, �ٸ� �� �� ���� �Ҵ��� �ƴ� DeepCopy�� ����, �ִ� 2ȸ�� �����
return (this->TM6);
}

int Cube::NormalCal(double *vec)//���̽� ���� ���� ���� ���Ͱ� ���� ������ ����
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

double Cube::BaseRelAxisRotCal(int &num, int &box)//���̽� ����� ���� ������ ȸ���� ����
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

void Cube::CalRot(int &baseaxis2, double &x1, double &x2)//base2�� base1�� ���� ��� ȸ���� ���Ͽ� this->transform�� ����
{
	if(((x1-x2)<=110)&&((x1-x2)>=70))
		Rotate(90, baseaxis2);//ȸ������ �Ǻ��ϰ� �׿� �´� ȸ���� ����
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

void Cube::Rotate(int rot, int &axis)//ȸ������ �Ǻ��ϰ� �׿� �´� ȸ���� ����
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


vtkSmartPointer<vtkTransform> Cube::GetMatrixTransform(int &planenum1, int &planenum2, vtkSmartPointer<vtkTransform> Rot)//Rot���� ���� �ڽ� ������ ��� ȸ���� �����ϰ� Translation�� ���ϰ� �����Ͽ� Translatoin�� ����� ���� �ڽ� ������ TM�� ���Ѵ�.
{
        int num[2]={planenum1,planenum2};//�����Ѱ�?
        double size[2];
        double vec3[3];
        double scalar;
		double rotation[4];
	    this->normals->GetPoint(num[0], this->vec1);//���� �۵� ���ɼ�
        this->normals->GetPoint(num[1], this->vec2);//���� �۵� ���ɼ�
        vtkMath::Normalize(this->vec1);//���� �۵� ���ɼ�
        vtkMath::Normalize(this->vec2);//���� �۵� ���ɼ�
        vtkMath::Cross(vec1, vec2, this->rot_vec);//���� �۵� ���ɼ�
        vtkMath::Normalize(this->rot_vec);//���� �۵� ���ɼ�
        this->rad = vtkMath::DegreesFromRadians(acos((vtkMath::Dot(vec1, vec2))));//���� �۵� ���ɼ�
		
        for(int i=0; i<2; i++)//���� �۵� ���ɼ�
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
        scalar=size[0]+size[1];//���� �۵� ���ɼ�
		vec3[0]=this->vec1[0];//���� �۵� ���ɼ�
		vec3[1]=this->vec1[1];//���� �۵� ���ɼ�
		vec3[2]=this->vec1[2];//���� �۵� ���ɼ�
        vtkMath::MultiplyScalar(vec3, scalar);//���� �۵� ���ɼ�
        
        //this->TM2->Translate(vec3);//���� �۵� ���ɼ�
		Rot->GetOrientationWXYZ(rotation);
		this->transform=vtkSmartPointer<vtkTransform>::New();
		this->transform->PostMultiply();
		this->transform->RotateWXYZ(this->rad, this->rot_vec);
		this->transform->RotateWXYZ(rotation[0],rotation[1],rotation[2],rotation[3]);
	    this->transform->Translate(vec3);
	    return this->transform;//���� �۵� ���ɼ�
} 

void Cube::BoxConverge(int &blocknum1, int &blocknum2)
{  
  BaseClear();
  this->box1=variables.boxdata.boxid.at(blocknum1);//����
  this->box2=variables.boxdata.boxid.at(blocknum2);//����
  this->plane1=variables.boxdata.boxplanenum.at(blocknum1);//����
  this->plane2=variables.boxdata.boxplanenum.at(blocknum2);//����
  this->TM1->DeepCopy(GetMatrixTransform(plane1, plane2));//���� �۵� ���ɼ�
  variables.Block[box1].setSurf(&(variables.Block[box2]), plane1);//����    
  variables.Block[box2].setParent(&(variables.Block[box1]),plane2);//����
  variables.Block[box2].SetTransform(TM1);//����
}

vtkSmartPointer<vtkTransform> Cube::GetMatrixTransform(int &planenum1, int &planenum2)//ȸ���� �ݴ��� ��� ����ؾ� ��, ������ �ڵ忡 ���� �Ͽ���. ������ �ڵ� �׳� ��� ���, ���ȸ��
{
        int num[2]={planenum1,planenum2};//�����Ѱ�?
		int area[2]={0};
		double size[2];
        double scalar;
		double vec3[3];
	    this->normals->GetPoint(num[0], this->vec1);//���� �۵� ���ɼ�
        this->normals->GetPoint(num[1], this->vec2);//���� �۵� ���ɼ�
        vtkMath::Normalize(this->vec1);//���� �۵� ���ɼ�
        vtkMath::Normalize(this->vec2);//���� �۵� ���ɼ�
        vtkMath::Cross(vec1, vec2, this->rot_vec);//���� �۵� ���ɼ�
        vtkMath::Normalize(this->rot_vec);//���� �۵� ���ɼ�
        this->rad = vtkMath::DegreesFromRadians(acos((vtkMath::Dot(vec1, vec2))));//���� �۵� ���ɼ�

        //this->TM1->RotateWXYZ(this->rad, this->rot_vec);//���� �۵� ���ɼ�
        for(int i=0; i<2; i++)//���� �۵� ���ɼ�
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
        scalar=size[0]+size[1];//���� �۵� ���ɼ�
		vec3[0]=this->vec1[0];//���� �۵� ���ɼ�
		vec3[1]=this->vec1[1];//���� �۵� ���ɼ�
		vec3[2]=this->vec1[2];//���� �۵� ���ɼ�
        vtkMath::MultiplyScalar(vec3, scalar);//���� �۵� ���ɼ�
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
		return this->transform;//���� �۵� ���ɼ�
}


void Cube::BaseClear()//����
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


Cube::~Cube()//���� �۵� ���ɼ�
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