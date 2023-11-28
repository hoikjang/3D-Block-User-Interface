#include "myheader.h"
#include "Rotate.h"

//vtkSmartPointer<vtkTransform> tf1 = vtkSmartPointer<vtkTransform>::New();
//vtkSmartPointer<vtkTransform> tf2 = vtkSmartPointer<vtkTransform>::New();

//vtkSmartPointer<vtkTransformFilter> tf = vtkSmartPointer<vtkTransformFilter>::New();
//vtkSmartPointer<vtkTransformFilter> tf2 = vtkSmartPointer<vtkTransformFilter>::New();
 
//vtkSmartPointer<vtkTransformPolyDataFilter> tff1 = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
vtkSmartPointer<vtkTransformPolyDataFilter> tff2 = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
vtkSmartPointer<vtkCamera> cam = vtkSmartPointer<vtkCamera>::New();
vtkSmartPointer<vtkRenderWindow> renWin1 = vtkSmartPointer<vtkRenderWindow>::New();
vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderer> ren2 = vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindowInteractor> iren1 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
vtkSmartPointer<vtkPoints> cam_position = vtkSmartPointer<vtkPoints>::New();
//vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();

//vtkSmartPointer<vtkCamera> cam = vtkSmartPointer<vtkCamera>::New();      
                 
//vtkSmartPointer<vtkRenderWindow> renWin2 = vtkSmartPointer<vtkRenderWindow>::New();
vtkSmartPointer<vtkRenderer> ren3 = vtkSmartPointer<vtkRenderer>::New();
//vtkSmartPointer<vtkRenderWindowInteractor> iren2 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//vtkSmartPointer<vtkPoints> cam_position = vtkSmartPointer<vtkPoints>::New();
//vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();


vector<CubeSource> Cube_data;
CubeSource cube1;
CubeSource cube2;
CubeSource cube3;
CubeSource cube4;

double ww1, xx1, yy1, zz1, ww2, xx2, yy2, zz2, ww3, xx3, yy3, zz3, ww4, xx4, yy4, zz4;

double xrr;
double yrr;
double zrr;
double xrr1;
double yrr1;
double zrr1;
double xrr2;
double yrr2;
double zrr2;
double xrr3;
double yrr3;
double zrr3;
double xrr4;
double yrr4;
double zrr4;

double vec1[3] = {0};
double pt1[3] = {0};
double vec2[3] = {0};
double pt2[3] = {0};


vtkSmartPointer<vtkMatrix4x4> RotMat1=vtkSmartPointer<vtkMatrix4x4>::New();
vtkSmartPointer<vtkMatrix4x4> RotMat2=vtkSmartPointer<vtkMatrix4x4>::New();


void BoxRendering(int size, int boxid, double w, double x, double y, double z)
{
					renWin1->SetSize(800,400);
			        iren1->SetRenderWindow(renWin1);
					BoxData boxdata2(boxid,w,x,y,z);

					//RotatMatrix(ww1, xx1, yy1, zz1, RotMat1);
				    //RotatMatrix(ww2, xx2, yy2, zz2, RotMat2);
	
					

	if(size<=3)
	{

		          
			
					cube1.initialization();
					cube2.initialization();


				
					/*
				    cube1.normals->GetPoint(cube1.Num_Sur, vec1);
					cube1.centers->GetPoint(cube1.Num_Sur, pt1);

					cube2.normals->GetPoint(cube2.Num_Sur, vec1);
					cube2.centers->GetPoint(cube2.Num_Sur, pt1);
					
				    */

					cube1.make_actor_Base();		
					cube2.make_actor_Base();

					if(Cube_data.size() == 0){
						Cube_data.push_back(cube1);
						Cube_data.push_back(cube2);
					}
					//cube1.RotateActor(RotMat1);
					//cube2.RotateActor(RotMat2);
					
					//cube1.actor->RotateWXYZ(180*ww1, xx1, yy1, zz1);
					//cube2.actor->RotateWXYZ(180*ww2, xx2, yy2, zz2);

					
					ren1 = vtkRenderer::New();
					//ren1->ResetCamera();
					ren2 = vtkRenderer::New();
					//ren2->ResetCamera();
					cam->SetPosition(0, 0, 5);
                    cam->SetFocalPoint(0, 0, 0);
					cam->Elevation(-90);
					ren1->SetActiveCamera(cam);
					ren2->SetActiveCamera(cam);
					
					iren1->SetRenderWindow(renWin1);
					renWin1->AddRenderer(ren1);
					renWin1->AddRenderer(ren2);
					ren1->AddActor(cube1.actor);
					ren2->AddActor(cube2.actor);
					ren1->SetViewport(0.5,0,1,1);
					ren2->SetViewport(0,0,0.5,1);
					ren1->SetBackground(0,0,0);
					ren2->SetBackground(0,0,0);
			   
					renWin1->Modified();
					renWin1->Render();	
	}
	if(size==4)
	{

		           // iren1->GetRenderWindow()->Finalize();
                   // iren1->TerminateApp();


		         
		   
					cube3.initialization();
					cube4.initialization();

			

					cube3.normals->GetPoint(cube3.Num_Sur, vec2);
					cube3.centers->GetPoint(cube3.Num_Sur, pt2);
					cube4.rotate(xrr1, yrr1, zrr1, xrr2, yrr2, zrr2, vec2, cube3.Num_Sur);
					cube4.translate(pt2, cube3.Num_Sur);
					cube4.Move(xrr1, yrr1, zrr1, xrr2, yrr2, zrr2, cube3.Num_Sur);
					//cube3.make_actor_Base();
					//cube4.make_actor();

					
					if(Cube_data.size() == 0){
						Cube_data.push_back(cube3);
						Cube_data.push_back(cube4);
					}
					
					

						if(((xrr1-xrr2)<=110)&&((xrr1-xrr2)>=70))
						{
						//cube3.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
					    //cube4.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
						}
						
	                    if(((xrr1-xrr2)<=-250)&&((xrr1-xrr2)>=-270))
						{
						//cube3.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
					   // cube4.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
							
						cube3.actor->RotateX(xrr1);
					    cube3.actor->RotateY(-zrr1);
					    cube3.actor->RotateZ(yrr1);
					    cube4.actor->RotateX(xrr1);
					    cube4.actor->RotateY(-zrr1);
					    cube4.actor->RotateZ(yrr1);
						
						}

						if(((xrr1-xrr2)<=200)&&((xrr1-xrr2)>=160))
						{
						//cube3.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
					    //cube4.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
						
						cube3.actor->RotateX(xrr1);
					    cube3.actor->RotateY(yrr1);
					    cube3.actor->RotateZ(zrr1);
					    cube4.actor->RotateX(xrr1);
					    cube4.actor->RotateY(yrr1);
					    cube4.actor->RotateZ(zrr1);
						
						}
	                    if(((xrr1-xrr2)<=-160)&&((xrr1-xrr2)>=-200))
						{
						//cube3.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
					    //cube4.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
						
						cube3.actor->RotateX(xrr1);
					    cube3.actor->RotateY(yrr1);
					    cube3.actor->RotateZ(zrr1);
					    cube4.actor->RotateX(xrr1);
					    cube4.actor->RotateY(yrr1);
					    cube4.actor->RotateZ(zrr1);
						
						}
	                    if(((xrr1-xrr2)<=290)&&((xrr1-xrr2)>=250))
						{
						//cube3.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
					    //cube4.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
						
						cube3.actor->RotateX(xrr1);
					    cube3.actor->RotateY(-zrr1);
					    cube3.actor->RotateZ(yrr1);
					    cube4.actor->RotateX(xrr1);
					    cube4.actor->RotateY(-zrr1);
					    cube4.actor->RotateZ(yrr1);
						
						}
	                    if(((xrr1-xrr2)<=-70)&&((xrr1-xrr2)>=-110))
						{
						//cube3.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
					    //cube4.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
						
						cube3.actor->RotateX(xrr1);
					    cube3.actor->RotateY(-zrr1);
					    cube3.actor->RotateZ(yrr1);
					    cube4.actor->RotateX(xrr1);
					    cube4.actor->RotateY(-zrr1);
					    cube4.actor->RotateZ(yrr1);
						
						}
						else
						{
						//cube3.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
					   // cube4.actor->RotateWXYZ(ww1,xx1,yy1,zz1);
							
						cube3.actor->RotateX(xrr1);
					    cube3.actor->RotateY(yrr1);
					    cube3.actor->RotateZ(zrr1);
					    cube4.actor->RotateX(xrr1);
					    cube4.actor->RotateY(yrr1);
					    cube4.actor->RotateZ(zrr1);
						}
			
				
						
					

					ren3 = vtkRenderer::New();
					ren3->ResetCamera();
					iren1->SetRenderWindow(renWin1);
					renWin1->AddRenderer(ren3);
					ren3->AddActor(cube3.actor);
					ren3->AddActor(cube4.actor);
					ren3->SetBackground(0,0,0);
					renWin1->Modified();
					renWin1->Render();	
				//	iren2->Start();
	}
	if(size==6)
	{}
}