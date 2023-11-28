#include "BlockTree.h"


Node::Node(int boxnum) : BoxNum(boxnum), parentsurfnumber(0), onOff(false) //���� �۵�
{
    this->Surf[0]=NULL;
	this->Surf[1]=NULL;
	this->Surf[2]=NULL;
	this->Surf[3]=NULL;
	this->Surf[4]=NULL;
	this->Surf[5]=NULL;
	this->Surf[6]=NULL;
	this->reader =vtkSmartPointer<vtkPolyDataReader>::New();
	this->polydata =vtkSmartPointer<vtkPolyData>::New(); 
	this->transform=vtkSmartPointer<vtkTransform>::New(); 
	this->transform1=vtkSmartPointer<vtkTransform>::New();
	this->transform->PostMultiply();
	this->transform1->PostMultiply();
	this->transform->Update();
	this->transform1->Update();
	this->transformedbox=vtkSmartPointer<vtkPolyData>::New();
	this->transformFilter=vtkSmartPointer<vtkTransformFilter>::New();
	this->Matrix=vtkSmartPointer<vtkTransform>::New();
	
	SetBoxType();
	
	
}


void Node::SetBoxType() //���� �۵�
{
	  switch(this->BoxNum)
	  {
		case 1:
			this->reader->SetFileName("D:/polydata/base6.vtk");
			this->reader->Update();
			break;
		case 2:
			this->reader->SetFileName("D:/polydata/base2.vtk");
			this->reader->Update();
			break;
		case 3:
			this->reader->SetFileName("D:/polydata/base3.vtk");
			this->reader->Update();
			break;
		case 4:
			this->reader->SetFileName("D:/polydata/base4.vtk");
			this->reader->Update();
			break;
		case 5:
			this->reader->SetFileName("D:/polydata/base5.vtk");
			this->reader->Update();
			break;
		case 6:
			this->reader->SetFileName("D:/polydata/BuildingBlock6.vtk");
			this->reader->Update();
			break;
		case 7:
			this->reader->SetFileName("D:/polydata/BuildingBlock7.vtk");
			this->reader->Update();
			break;
		case 8:
			this->reader->SetFileName("D:/polydata/BuildingBlock8.vtk");
			this->reader->Update();
			break;
		case 9:
			this->reader->SetFileName("D:/polydata/BuildingBlock9.vtk");
			this->reader->Update();
			break;
		case 10:
			this->reader->SetFileName("D:/polydata/BuildingBlock10.vtk");
			this->reader->Update();
			break;
		case 11:
			this->reader->SetFileName("D:/polydata/BuildingBlock11.vtk");
			this->reader->Update();
			break;
		case 12:
			this->reader->SetFileName("D:/polydata/BuildingBlock12.vtk");
			this->reader->Update();
			break;
		case 13:
			this->reader->SetFileName("D:/polydata/BuildingBlock13.vtk");
			this->reader->Update();
			break;
		case 14:
			this->reader->SetFileName("D:/polydata/BuildingBlock14.vtk");
			this->reader->Update();
			break;
		case 15:
			this->reader->SetFileName("D:/polydata/BuildingBlock15.vtk");
			this->reader->Update();
			break;
	   }

	   //this->polydata->ShallowCopy(reader->GetOutput());//�´°�??
	   this->polydata=reader->GetOutput(); //������ ���
	  
}


void Node::GetTransform(vtkSmartPointer<vtkTransform> TM)//����
{ 
	TM->DeepCopy(this->transform);
}

void Node::SetTransform(vtkSmartPointer<vtkTransform> TR)//����
{
	this->transform=vtkSmartPointer<vtkTransform>::New();
	this->transform->DeepCopy(TR);
	this->transform->Update();
}

void Node::Concatenation(vtkSmartPointer<vtkTransform> TR)//�����۵�
{
	this->transform1->DeepCopy(this->transform);//����
	this->transform1->Concatenate(TR);//����
	this->transformFilter->SetInputData(this->polydata);//����
	this->transformFilter->SetTransform(this->transform1);//����
	this->transformFilter->Update();//����
	this->transformedbox=transformFilter->GetPolyDataOutput();//����
}

void Node::getConcatenatedTransform(vtkSmartPointer<vtkTransform> TR)//����??
{
	TR->DeepCopy(transform1);
}

int Node::SearchParent(Node* Parent)//����
{
	int k=0;
	for(int i=1; i<7; i++)
	{
		if((this->Surf[i])==Parent)
		k=i;
	}
	return k;
}



Node::~Node()
{ 
	Surf[0]->~Node();
	Surf[1]->~Node();
	Surf[2]->~Node();
	Surf[3]->~Node();
	Surf[4]->~Node();
	delete []&Surf;//delete ���μ��� �̰� �³�??
	this->Matrix->Delete();
	this->polydata->Delete();
	this->reader->Delete();
	this->transform->Delete();
	this->transform1->Delete();
	this->transformFilter->Delete();
	this->transformedbox->Delete();
}

