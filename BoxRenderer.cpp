#include "BoxRenderer.h"
#include "header.h"

BoxRenderer::BoxRenderer(): base(0), stat(0)//정상 작동
{
	this->renWin=vtkSmartPointer<vtkRenderWindow>::New();
	this->ren[0]=vtkSmartPointer<vtkRenderer>::New();
	this->ren[1]=vtkSmartPointer<vtkRenderer>::New();
	this->ren[2]=vtkSmartPointer<vtkRenderer>::New();
	this->ren[3]=vtkSmartPointer<vtkRenderer>::New();
	this->ren[4]=vtkSmartPointer<vtkRenderer>::New();
	this->cam1=vtkSmartPointer<vtkCamera>::New();
	this->cam1->SetPosition(0,0,300);
	//this->cam1->Elevation(90);
	this->iren1=vtkSmartPointer<vtkRenderWindowInteractor>::New();
	this->writer = vtkSmartPointer<vtkPolyDataWriter>::New();
	this->appendFilter=vtkSmartPointer<vtkAppendPolyData>::New();
	this->cleanFilter =vtkSmartPointer<vtkCleanPolyData>::New();
    this->mapper[0]=vtkSmartPointer<vtkPolyDataMapper>::New();
    this->mapper[1]=vtkSmartPointer<vtkPolyDataMapper>::New();
	this->mapper[2]=vtkSmartPointer<vtkPolyDataMapper>::New();
	this->mapper[3]=vtkSmartPointer<vtkPolyDataMapper>::New();
	this->mapper[4]=vtkSmartPointer<vtkPolyDataMapper>::New();
	this->mapper[5]=vtkSmartPointer<vtkPolyDataMapper>::New();
	this->actor[0]=vtkSmartPointer<vtkActor>::New();
	this->actor[1]=vtkSmartPointer<vtkActor>::New();
	this->actor[2]=vtkSmartPointer<vtkActor>::New();
	this->actor[3]=vtkSmartPointer<vtkActor>::New();
	this->actor[4]=vtkSmartPointer<vtkActor>::New();
	this->lut=vtkSmartPointer<vtkLookupTable>::New();
	this->lut->SetNumberOfTableValues(9);
	this->lut->Build();
	this->lut->SetTableValue(0, 0,0,0,1);
	this->lut->SetTableValue(1, 1,0,0,1);
	this->lut->SetTableValue(2, 1,0.45,0,1);
	this->lut->SetTableValue(3, 1,1,0,1);
	this->lut->SetTableValue(4, 0,1,0,1);
	this->lut->SetTableValue(5, 0,0,1,1);
	this->lut->SetTableValue(6, 1,0,1,1);
	this->lut->SetTableValue(7, 0,1,1,1);
	this->lut->SetTableValue(8, 1,1,1,1);

	/*this->actor[0]->GetProperty()->LightingOn();
	this->actor[1]->GetProperty()->LightingOn();
	this->actor[2]->GetProperty()->LightingOn();
	this->actor[3]->GetProperty()->LightingOn();
	this->actor[4]->GetProperty()->LightingOn();*/
	this->IM=vtkSmartPointer<vtkTransform>::New();
	/*this->light = vtkSmartPointer<vtkLight>::New();
	this->light->SetColor(1,1,1);
	this->light->SetFocalPoint(0,0,0);
	this->light->SetPosition(1,0,0);
	this->light->SetIntensity(1.0);
	this->light->SetAmbientColor(1,1,1);
	this->light->SetLightTypeToHeadlight();
	this->lightActor = vtkSmartPointer<vtkLightActor>::New();
	this->lightActor->SetLight(light);*/
	this->reader = vtkSmartPointer<vtkPolyDataReader>::New();
	this->polydata=vtkSmartPointer<vtkPolyData>::New();
	//this->axes = vtkSmartPointer<vtkAxesActor>::New();
	//this->widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	this->xmins[0]=0;
	this->xmins[1]=0.5;
	this->xmins[2]=0;
	this->xmins[3]=0.5;
   	this->xmaxs[0]=0.5;
	this->xmaxs[1]=1;
	this->xmaxs[2]=0.5;
	this->xmaxs[3]=1;
	this->ymins[0]=0;
	this->ymins[1]=0;
	this->ymins[2]=0.5;
	this->ymins[3]=0.5;
	this->ymaxs[0]=0.5;
	this->ymaxs[1]=0.5;
	this->ymaxs[2]=1;
	this->ymaxs[3]=1;
	this->c1[0]=1;
	this->c1[1]=1;
	this->c1[2]=0;
	this->c1[3]=1;
	this->c1[4]=1;
	this->c2[0]=0;
	this->c2[1]=1;
	this->c2[2]=0;
	this->c2[3]=1;
	this->c2[4]=1;
	this->c3[0]=0;
	this->c3[1]=0;
	this->c3[2]=1;
	this->c3[3]=0;
	this->c3[4]=1;
}

void BoxRenderer::BaseGroupNumber()
{ 
  this->base=0;
  for(int i=1; i<6; ++i)
  {
	  bool onoff=variables.Base[i].getOnoff();
	  if(onoff==true)
	  base+=1;
  }
}

void BoxRenderer::Renderer()
{ 
	/*
  this->widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
  this->widget->SetOrientationMarker( this->axes );
  this->widget->SetInteractor( this->iren1 );
  this->widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
  this->widget->SetEnabled( 1 );
  this->widget->InteractiveOn();*/
	/*iren1->SetRenderWindow(renWin);
	renWin->SetSize(1600,800);
	vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    camera->SetPosition(0,0,-300);
	camera->SetFocalPoint(0,0,1);*/
	//this->renWin=vtkSmartPointer<vtkRenderWindow>::New();
	/*iren1->SetRenderWindow(renWin);
	this->renWin->SetSize(1600,1000);*/
	if(variables.boxdata.geteventonoff())
	{
		this->BaseGroupNumber();
		this->MergePolyData();
		this->ActorDistribution();
		//for(int j=this->base; j<4; ++j)
		//{
		//this->ren[j]=vtkSmartPointer<vtkRenderer>::New();
		//this->ren[j]->ResetCamera();
		////this->ren[j]->SetActiveCamera(camera);
		//this->ren[j]->SetBackground(0,0,0);
		//this->ren[j]->SetViewport(xmins[j], ymins[j], xmaxs[j], ymaxs[j]);
		////this->ren[j]->AddLight(this->light);
		//
		//this->ren[j]->AddActor(actor[j]);
		//this->renWin->AddRenderer(ren[j]);
		//this->renWin->Modified();
		//}
	if(this->stat!=this->base)
	{
	this->renWin=vtkSmartPointer<vtkRenderWindow>::New();
	this->renWin->SetSize(1600,1000);
	this->stat=this->base;
	}

	}
	//if(this->stat!=this->base)
	//{
	//this->renWin=vtkSmartPointer<vtkRenderWindow>::New();
	//this->renWin->SetSize(1600,1000);
	//this->stat=this->base;
	//}

	if(this->base==1)
	//for(int i=0; i<this->base; ++i)//정상 작동
	{
		this->ren[0]=vtkSmartPointer<vtkRenderer>::New();
		//this->ren[0]->SetViewport(xmins[0], ymins[0], xmaxs[0], ymaxs[0]);
		this->ren[0]->SetActiveCamera(cam1);
		
		
		this->ren[0]->ResetCamera();
		this->ren[0]->SetBackground(0,0,0);
		//this->ren[i]->AddLight(this->light);
		this->ren[0]->AddActor(actor[0]);
		
		this->actor[0]->SetUserTransform(variables.boxdata.TM[this->k[0]]);
		this->renWin->AddRenderer(ren[0]);
		renWin->Modified();
	
	}
		
	if(this->base==2)
	//for(int i=0; i<this->base; ++i)//정상 작동
	{
		
		this->ren[0]=vtkSmartPointer<vtkRenderer>::New();
		this->ren[1]=vtkSmartPointer<vtkRenderer>::New();
		this->ren[0]->SetViewport(0.0, 0.0, 0.5, 1.0);
		this->ren[1]->SetViewport(0.5, 0.0, 1.0, 1.0);
	
		//this->ren[1]->SetViewport(xmins[i], ymins[i], xmaxs[i], ymaxs[i]);
		//this->ren[i]->SetActiveCamera(camera);
		this->ren[0]->ResetCamera();
		this->ren[0]->SetActiveCamera(cam1);
		this->ren[0]->SetBackground(0,0,0);
		this->ren[1]->ResetCamera();
		this->ren[1]->SetActiveCamera(cam1);
		this->ren[1]->SetBackground(0,0,0);
		//this->ren[i]->AddLight(this->light);
		this->ren[0]->AddActor(actor[0]);
		this->ren[1]->AddActor(actor[1]);
		this->renWin->AddRenderer(ren[0]);
		this->renWin->AddRenderer(ren[1]);
		this->actor[0]->SetUserTransform(variables.boxdata.TM[this->k[0]]);
		this->actor[1]->SetUserTransform(variables.boxdata.TM[this->k[1]]);
		renWin->Modified();
		//renWin->Render();
	}
	   renWin->Render();
		
}


void BoxRenderer::MergePolyData()//정상 작동
{   
	  for(int i=0; i<5; ++i)
	  {
		  this->mapper[i]=vtkSmartPointer<vtkPolyDataMapper>::New();
		  this->mapper[i]->InterpolateScalarsBeforeMappingOn();
		  this->mapper[i]->SetScalarRange(0,1);
		  this->mapper[i]->SetLookupTable(lut);
	  }

	  for(int i=1; i<6; ++i)
	  {
	  
	  if(variables.Base[i].getOnoff())
	  {
	  this->IM->Identity();
	  this->appendFilter=vtkSmartPointer<vtkAppendPolyData>::New();
	  AppendFilter(&(variables.Block[i]), this->IM);
	  
	  /*this->cleanFilter=vtkSmartPointer<vtkCleanPolyData>::New();
	  this->cleanFilter->SetInputConnection(this->appendFilter->GetOutputPort());
      this->cleanFilter->Update();
	  */
	  switch(i)
	  {
	  case 1:
	
	 
	 
	  this->mapper[0]->SetInputConnection(appendFilter->GetOutputPort());  
	  this->writer->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetFileName("D:/polydata/mergedata/MergeData1.vtk");
	  this->writer->Write();
	  
	 /* reader->SetFileName("D:/polydata/MergeData1.vtk");	
	  reader->Update();
	  this->polydata = reader->GetOutput(); 
	  this->mapper[0]->SetInput(polydata);*/
	  break;

	  case 2:

	  
	  this->mapper[1]->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetFileName("D:/polydata/mergedata/MergeData2.vtk");
	  this->writer->Write();
	  /*reader->SetFileName("D:/polydata/MergeData2.vtk");	
	  reader->Update();
	  this->polydata = reader->GetOutput(); 
	  this->mapper[1]->SetInput(polydata);*/
	  break;

	  case 3:

	  
	  this->mapper[2]->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetFileName("D:/polydata/mergedata/MergeData3.vtk");
	  this->writer->Write();

	  /*reader->SetFileName("D:/polydata/MergeData3.vtk");	
	  reader->Update();
	  this->polydata = reader->GetOutput(); 
	  this->mapper[2]->SetInput(polydata);*/
	  break;

	  case 4:

	 
	  this->mapper[3]->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetFileName("D:/polydata/mergedata/MergeData4.vtk");
	  this->writer->Write();
	  
	  /*reader->SetFileName("D:/polydata/MergeData4.vtk");	
	  reader->Update();
	  this->polydata = reader->GetOutput(); 
	  this->mapper[3]->SetInput(polydata);*/
	  break;

	  case 5:
	  
	  
	  this->mapper[4]->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetInputConnection(appendFilter->GetOutputPort());
	  this->writer->SetFileName("D:/polydata/mergedata/MergeData5.vtk");
	  this->writer->Write();
	  
	 /* reader->SetFileName("D:/polydata/MergeData5.vtk");	
	  reader->Update();
	  this->polydata = reader->GetOutput(); 
	  this->mapper[4]->SetInput(polydata);*/
	  break;

	  }
	  
	  }
	  }
	
}

void BoxRenderer::AppendFilter(Node* Leaf, vtkSmartPointer<vtkTransform> TR)
{
	  
	  if(Leaf==NULL)
	  return;
	  vtkSmartPointer<vtkTransform> TR2=vtkSmartPointer<vtkTransform>::New();
	  int k=Leaf->getParentNum();
	  Leaf->Concatenation(TR);
	  Leaf->getConcatenatedTransform(TR2);
	  for(int i=1; i<k;i++)
	  {
	   AppendFilter(Leaf->getSurf(i), TR2);
	  }
	  for(int i=k+1; i<7;i++)
	  {
	   AppendFilter(Leaf->getSurf(i), TR2);
	  }
	  vtkSmartPointer<vtkPolyData> polydata2=vtkSmartPointer<vtkPolyData>::New();
	  Leaf->getTransformedBox(polydata2);
	  this->appendFilter->AddInputData(polydata2);
	  //this->appendFilter->AddInputConnection(polydata2->GetProducerPort());
	  this->appendFilter->Update();
}



void BoxRenderer::ActorDistribution()
{
	this->k[0]=5;
	this->k[1]=5;
	this->k[2]=5;
	this->k[3]=5;
	this->k[4]=5;
	int j=0;
	for(int i=0;i<5; ++i)
	{
		if(variables.Base[i+1].getOnoff())
		{
			this->k[j]=i;
			j+=1;
		}
	}
	
	this->actor[0]=vtkSmartPointer<vtkActor>::New();
	this->actor[1]=vtkSmartPointer<vtkActor>::New();
	this->actor[2]=vtkSmartPointer<vtkActor>::New();
	this->actor[3]=vtkSmartPointer<vtkActor>::New();
	this->actor[4]=vtkSmartPointer<vtkActor>::New();
	
	
	
	///*
	//this->actor[0]->GetProperty()->SetShading(1);
	//this->actor[1]->GetProperty()->SetShading(1);
	//this->actor[2]->GetProperty()->SetShading(1);
	//this->actor[3]->GetProperty()->SetShading(1);
	//this->actor[4]->GetProperty()->SetShading(1);
	//*/
	///*this->actor[0]->GetProperty()->SetSpecular(1);
	//this->actor[1]->GetProperty()->SetSpecular(1);
	//this->actor[2]->GetProperty()->SetSpecular(1);
	//this->actor[3]->GetProperty()->SetSpecular(1);
	//this->actor[4]->GetProperty()->SetSpecular(1);
	//*/
	//this->actor[0]->GetProperty()->SetDiffuse(0.7);
	//this->actor[1]->GetProperty()->SetDiffuse(0.7);
	//this->actor[2]->GetProperty()->SetDiffuse(0.7);
	//this->actor[3]->GetProperty()->SetDiffuse(0.7);
	//this->actor[4]->GetProperty()->SetDiffuse(0.7);
	//
	//this->actor[0]->GetProperty()->SetAmbient(0.1);
	//this->actor[1]->GetProperty()->SetAmbient(0.1);
	//this->actor[2]->GetProperty()->SetAmbient(0.1);
	//this->actor[3]->GetProperty()->SetAmbient(0.1);
	//this->actor[4]->GetProperty()->SetAmbient(0.1);
	//
	///*
	//this->actor[0]->GetProperty()->SetLighting(false);
	//this->actor[1]->GetProperty()->SetLighting(false);
	//this->actor[2]->GetProperty()->SetLighting(false);
	//this->actor[3]->GetProperty()->SetLighting(false);
	//this->actor[4]->GetProperty()->SetLighting(false);
	//*/
	//this->actor[0]->GetProperty()->EdgeVisibilityOn();
	//this->actor[1]->GetProperty()->EdgeVisibilityOn();
	//this->actor[2]->GetProperty()->EdgeVisibilityOn();
	//this->actor[3]->GetProperty()->EdgeVisibilityOn();
	//this->actor[4]->GetProperty()->EdgeVisibilityOn();
	//
	
	//this->actor[0]->GetProperty()->ShadingOn();
	//this->actor[1]->GetProperty()->ShadingOn();
	//this->actor[2]->GetProperty()->ShadingOn();
	//this->actor[3]->GetProperty()->ShadingOn();
	//this->actor[4]->GetProperty()->ShadingOn();

	//this->actor[0]->GetProperty()->LightingOff();
	//this->actor[1]->GetProperty()->LightingOff();
	//this->actor[2]->GetProperty()->LightingOff();
	//this->actor[3]->GetProperty()->LightingOff();
	//this->actor[4]->GetProperty()->LightingOff();
	
	this->actor[0]->SetMapper(mapper[k[0]]);
	this->actor[1]->SetMapper(mapper[k[1]]);
	this->actor[2]->SetMapper(mapper[k[2]]);
	this->actor[3]->SetMapper(mapper[k[3]]);
	this->actor[4]->SetMapper(mapper[k[4]]);
}

BoxRenderer::~BoxRenderer()
{
	this->renWin->Delete();
	this->ren[0]->Delete();
	this->ren[1]->Delete();
	this->ren[2]->Delete();
	this->ren[3]->Delete();
	this->ren[4]->Delete();
	this->iren1->Delete();
	this->writer ->Delete();
	this->appendFilter->Delete();
	this->cleanFilter ->Delete();
	this->mapper[0]->Delete();
	this->mapper[1]->Delete();
	this->mapper[2]->Delete();
    this->mapper[3]->Delete();
	this->mapper[4]->Delete();
	this->mapper[5]->Delete();
	this->actor[0]->Delete();
	this->actor[1]->Delete();
	this->actor[2]->Delete();
	this->actor[3]->Delete();
	this->actor[4]->Delete();
	delete []&k;
	delete []&xmins;
	delete []&ymins;
	delete []&xmaxs;
	delete []&ymaxs;
}

