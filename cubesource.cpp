#include "cubesource.h"

CubeSource::Box::Box(string &ID)
{
	this->reader =vtkSmartPointer<vtkPolyDataReader>::New();
	this->polydata =vtkSmartPointer<vtkPolyData>::New(); 
	
	switch(atoi(ID.c_str()))
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			this->reader->SetFileName("C:/a/BaseBlockPart.vtk");
			break;
		case 6:
			this->reader->SetFileName("C:/a/CylinderPart.vtk");
			break;
		case 7:
			this->reader->SetFileName("C:/a/TriangularPart.vtk");
			break;
		case 8:
			this->reader->SetFileName("C:/a/HousePart.vtk");
			break;
		case 9:
			this->reader->SetFileName("C:/a/ConePart.vtk");
			break;
		case 10:
			this->reader->SetFileName("C:/a/ArchPart.vtk");
			break;
	}

	this->polydata=ShallowCopy(reader->GetOutput());

}



void CubeSource::MergePolyData(vector<Box> &box)
{
	this->writer = vtkSmartPointer<vtkPolyDataWriter>::New();
	this->appendFilter=vtkSmartPointer<vtkAppendPolyData>::New();
	this->cleanFilter =vtkSmartPointer<vtkCleanPolyData>::New();
	this->mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
	for(int i=0;i<box.size();i++)
		this->appendFilter->AddInputConnection(box[i].polydata->GetProducerPort());

	//appendFilter->AddInputData(input1);
	this->cleanFilter->SetInputConnection(this->appendFilter->GetOutputPort());
    this->cleanFilter->Update();
	this->mapper->SetInputConnection(cleanFilter->GetOutputPort());
	this->writer->SetInputConnection(cleanFilter->GetOutputPort());
	this->writer->SetFileName("C:/a/MergeData.vtk");
	this->writer->Write();
}//parent child 두 개씩 merge 해나가도록 for문 짜기

void CubeSource::initialization(){

	this->reader =vtkSmartPointer<vtkPolyDataReader>::New();
	this->polydatagroup[5] =vtkSmartPointer<vtkPolyData>::New(); 
	this->centers = vtkSmartPointer<vtkPoints>::New();
	this->normals = vtkSmartPointer<vtkPoints>::New();
	this->mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	this->actor = vtkSmartPointer<vtkActor>::New();
	this->final_cube = vtkSmartPointer<vtkPolyData>::New();
	this->centers_poly = vtkSmartPointer<vtkPolyData>::New();
	this->normals_poly = vtkSmartPointer<vtkPolyData>::New();
	this->transformed_centers = vtkSmartPointer<vtkPolyData>::New();
	this->transformed_normals = vtkSmartPointer<vtkPolyData>::New();

	/*
	if(this->ID == "001"){
	    //this->actor->GetProperty()->SetColor(1,0,0);
	     this->reader->SetFileName("C:/a/cube1.vtk");
		 this->reader->Update();
		 
	}
	else if(this->ID == "002"){
		//this->actor->GetProperty()->SetColor(1,1,0);
	     this->reader->SetFileName("C:/a/cube2.vtk");
	     this->reader->Update();
	}

	else if(this->ID == "003"){
		//this->actor->GetProperty()->SetColor(0,0,1);
		 this->reader->SetFileName("C:/a/cube3.vtk");
	     this->reader->Update();
	  
	}
	else if(this->ID == "004"){
		//this->actor->GetProperty()->SetColor(1,1,0);
		 this->reader->SetFileName("C:/a/cube4.vtk");
	     this->reader->Update();

	}
	else if(this->ID == "005")
		//this->actor->GetProperty()->SetColor(1,1,1);

	{
		 this->reader->SetFileName("C:/a/cube5.vtk");
	     this->reader->Update();
	}
	*/
	  //   this->polydata=reader->GetOutput();
	//	 this->polydata->GetCenter(this->center);
	/*
		 double a[3] = {0};
	     for(int i=0; i<3; i++)
		 {
		    a[i] = this->center[i];
		 }

		 */
	/*
    this->centers->InsertNextPoint(this->center[0], this->center[1], this->center[2]);
	this->centers->InsertNextPoint(this->center[0], this->center[1], this->center[2]+0.5);
	this->centers->InsertNextPoint(this->center[0], this->center[1]+0.5, this->center[2]);
	this->centers->InsertNextPoint(this->center[0], this->center[1], this->center[2]-0.5);
	this->centers->InsertNextPoint(this->center[0], this->center[1]-0.5, this->center[2]);
	this->centers->InsertNextPoint(this->center[0]-1, this->center[1], this->center[2]);
	this->centers->InsertNextPoint(this->center[0]+1, this->center[1], this->center[2]);
	*/
	/*
	this->normals->InsertNextPoint(-1,0,0);
	this->normals->InsertNextPoint(-1,0,0);
	this->normals->InsertNextPoint(-1,0,0);
	this->normals->InsertNextPoint(-1,0,0);
	this->normals->InsertNextPoint(1,0,0);
	this->normals->InsertNextPoint(1,0,0);
	this->normals->InsertNextPoint(1,0,0);
	this->normals->InsertNextPoint(1,0,0);
	this->normals->InsertNextPoint(0,-1,0);
	this->normals->InsertNextPoint(0,-1,0);
	this->normals->InsertNextPoint(0,-1,0);
	this->normals->InsertNextPoint(0,-1,0);
	this->normals->InsertNextPoint(0,1,0);
	this->normals->InsertNextPoint(0,1,0);
	this->normals->InsertNextPoint(0,1,0);
	this->normals->InsertNextPoint(0,1,0);
	this->normals->InsertNextPoint(0,0,-1);
	this->normals->InsertNextPoint(0,0,-1);
	this->normals->InsertNextPoint(0,0,-1);
	this->normals->InsertNextPoint(0,0,-1);
	this->normals->InsertNextPoint(0,0,1);
	this->normals->InsertNextPoint(0,0,1);
	this->normals->InsertNextPoint(0,0,1);
	this->normals->InsertNextPoint(0,0,1);
	*/

	/*
	this->cube->SetCenter(0,0,0);
	this->cube->SetXLength(2);
	this->cube->SetYLength(1);
	this->cube->SetZLength(1);
	
	this->cube->Update();
	
	this->cube->GetCenter(this->center);
	double a[3] = {0};
	for(int i=0; i<3; i++){
		a[i] = this->center[i];
	}

	this->centers->InsertNextPoint(this->center[0], this->center[1], this->center[2]);
	this->centers->InsertNextPoint(this->center[0], this->center[1]+0.5, this->center[2]);
	this->centers->InsertNextPoint(this->center[0], this->center[1], this->center[2]-0.5);
	this->centers->InsertNextPoint(this->center[0], this->center[1]-0.5, this->center[2]);
	this->centers->InsertNextPoint(this->center[0], this->center[1], this->center[2]+0.5);
	this->centers->InsertNextPoint(this->center[0]+1, this->center[1], this->center[2]);
	this->centers->InsertNextPoint(this->center[0]-1, this->center[1], this->center[2]);
	*/
	/*
	this->normals->InsertNextPoint(0,0,0);
	this->normals->InsertNextPoint(0,0,1);
	this->normals->InsertNextPoint(0,1,0);
	this->normals->InsertNextPoint(0,0,-1);
	this->normals->InsertNextPoint(0,-1,0);
	this->normals->InsertNextPoint(-1,0,0);
	this->normals->InsertNextPoint(1,0,0);
	*/
}
/*
void CubeSource::make_actor_Base(){

    this->mapper->SetInput(polydata);
    this->actor->SetMapper(mapper);
	this->actor->RotateX(-90);
	
	this->mapper->SetInput(this->cube->GetOutput());
	this->actor->SetMapper(this->mapper);
	
//	this->actor->GetProperty()->SetRepresentationToWireframe();
}


void CubeSource::make_actor(){
	this->mapper->SetInput(this->final_cube);
	//this->mapper->SetInput(polydata);
	this->actor->SetMapper(mapper);
	this->actor->RotateX(-90);
	
	*/
	/*
	this->actor->SetMapper(this->mapper);
	this->actor->GetProperty()->SetColor(0,0,0);
	if(this->ID == "001"){
		this->actor->GetProperty()->SetColor(1,0,0);
	}
	else if(this->ID == "002"){
		this->actor->GetProperty()->SetColor(1,1,0);
	}
	else if(this->ID == "003"){
		this->actor->GetProperty()->SetColor(0,0,1);
		
	}
	else if(this->ID == "004"){
		this->actor->GetProperty()->SetColor(1,0,0);
	}
	else if(this->ID == "005"){
		this->actor->GetProperty()->SetColor(1,1,1);
	}

		
}
	*/
/*
void CubeSource::RotateActor(vtkSmartPointer<vtkMatrix4x4> rotat)
{
	vtkSmartPointer<vtkTransform> tf1 = vtkSmartPointer<vtkTransform>::New();
	vtkSmartPointer<vtkTransformPolyDataFilter> tff1 = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	tf1->SetMatrix(rotat);
	tff1->SetTransform(tf1);
	tff1->SetInput(this->polydata);
	this->mapper->SetInput(tff1->GetOutput());
	this->actor->SetMapper(mapper);
}
*/
/*
void CubeSource::Move(double x1, double y1, double z1, double x2, double y2, double z2, int num_sur)
{
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformFilter> transformFilter_cube = vtkSmartPointer<vtkTransformFilter>::New();

	if((num_sur==2)&&(this->Num_Sur==6))
	{
		transform->Translate(0,1.5,0);
	    transform->RotateZ(-90);
	}
	if((num_sur==2)&&(this->Num_Sur==5))
	{
		transform->Translate(0,1.5,0);
		transform->RotateZ(90);
	}
	if((num_sur==2)&&(this->Num_Sur==2))
	{
		transform->Translate(0,0.5,0);
	}

	if((num_sur==6)&&(this->Num_Sur==2))
	{
		transform->Translate(1.5,0,0);
		transform->RotateZ(90);
	}

	if((num_sur==6)&&(this->Num_Sur==5))
	{
		transform->Translate(2,0,0);
		transform->RotateZ(-90);
	}

	if((num_sur==6)&&(this->Num_Sur==6))
	{
		transform->Translate(2,0,0);
		transform->RotateZ(180);
	}

	if((num_sur==5)&&(this->Num_Sur==2))

	{
		transform->Translate(0,1.5,0);
		transform->RotateZ(-90);

	}

	if((num_sur==5)&&(this->Num_Sur==5))
	{

		transform->Translate(-1.5,0,0);
		transform->RotateZ(-90);
	}
	if((num_sur==5)&&(this->Num_Sur==6))
	{
		transform->Translate(-2,0,0);
	}

	
	if(((x1-x2)<=110)&&((x1-x2)>=70))
	transform->RotateX(90);
	if(((x1-x2)<=-250)&&((x1-x2)>=-270))
	transform->RotateX(90);
	if(((x1-x2)<=200)&&((x1-x2)>=160))
	transform->RotateX(180);
	if(((x1-x2)<=-160)&&((x1-x2)>=-200))
	transform->RotateX(180);
	if(((x1-x2)<=290)&&((x1-x2)>=250))
	transform->RotateX(-90);
	if(((x1-x2)<=-70)&&((x1-x2)>=-110))
	transform->RotateX(-90);
	

	transformFilter_cube->SetInput(this->polydata);
	transformFilter_cube->SetTransform(transform);

	
	this->final_cube = transformFilter_cube->GetPolyDataOutput();
}
*/

	

void CubeSource::rotate(double x1, double y1, double z1, double x2, double y2, double z2, double vec[3], int num_sur)
{
	

	vtkMath::Normalize(vec);
	printf("%lf %lf %lf\n", vec[0], vec[1], vec[2]);
	this->normals->GetPoint(num_sur, this->vec);
	printf("%lf %lf %lf\n", this->vec[0], this->vec[1], this->vec[2]);
	
	vtkMath::Normalize(this->vec);
	vtkMath::Cross(vec, this->vec, this->rot_vec);
	vtkMath::Normalize(this->rot_vec);

	printf("%lf %lf %lf\n", this->rot_vec[0], this->rot_vec[1], this->rot_vec[2]);

	this->rad = vtkMath::DegreesFromRadians(acos((vtkMath::Dot(vec, this->vec))));
	
	printf("%lf\n", this->rad);
	
	
	this->centers_poly->SetPoints(this->centers);
	this->normals_poly->SetPoints(this->normals);

	
	//vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform= vtkSmartPointer<vtkTransform>::New();
	this->transform->RotateWXYZ(this->rad, this->rot_vec);
	
	/*
	if(((x1-x2)<=110)&&((x1-x2)>=70))
	transform->RotateX(90);
	if(((x1-x2)<=-250)&&((x1-x2)>=-270))
	transform->RotateX(90);
	if(((x1-x2)<=200)&&((x1-x2)>=160))
	transform->RotateX(180);
	if(((x1-x2)<=-160)&&((x1-x2)>=-200))
	transform->RotateX(180);
	if(((x1-x2)<=290)&&((x1-x2)>=250))
	transform->RotateX(-90);
	if(((x1-x2)<=-70)&&((x1-x2)>=-110))
	transform->RotateX(-90);
	*/
	/*
	vtkSmartPointer<vtkTransformFilter> transformFilter_cube = vtkSmartPointer<vtkTransformFilter>::New();
	vtkSmartPointer<vtkTransformFilter> transformFilter_centers = vtkSmartPointer<vtkTransformFilter>::New();
	vtkSmartPointer<vtkTransformFilter> transformFilter_normals = vtkSmartPointer<vtkTransformFilter>::New();

	transformFilter_cube->SetInput(this->polydata);
	transformFilter_cube->SetTransform(transform);

	
	this->final_cube = transformFilter_cube->GetPolyDataOutput();


	transformFilter_centers->SetInput(this->centers_poly);
	transformFilter_centers->SetTransform(transform);

	this->centers_poly = transformFilter_centers->GetPolyDataOutput();
	this->centers_poly->Update();
	

	transformFilter_normals->SetInput(this->normals_poly);
	transformFilter_normals->SetTransform(transform);

	
	this->normals_poly = transformFilter_normals->GetPolyDataOutput();
	this->normals_poly->Update();

	vtkSmartPointer<vtkPoints> trans_normal = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkPolyData> trans_poly = vtkSmartPointer<vtkPolyData>::New();

	
	for(int i=0; i<this->normals_poly->GetNumberOfPoints(); i++){
		double pt1[3], pt2[3], pt3[3];
		this->normals_poly->GetPoint(i, pt1);
		this->centers_poly->GetPoint(0, pt2);
		for(int j=0; j<3; j++){
			pt3[j] = pt1[j]-pt2[j];
			
		}
	//	printf("trans_normal : %lf %lf %lf\n", pt3[0], pt3[1], pt3[2]);
		trans_normal->InsertNextPoint(pt3);
		
	}

	double aaaa=0;
	aaaa = vtkMath::Dot(vec, this->normals_poly->GetPoint(num_sur));
	printf("dot : %lf\n", aaaa);

	trans_poly->SetPoints(trans_normal);


	this->normals_poly = trans_poly;

	this->normals_poly->Update();

	if(aaaa>0){
		vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
		vtkSmartPointer<vtkTransformFilter> transFilter1 = vtkSmartPointer<vtkTransformFilter>::New();
		vtkSmartPointer<vtkTransformFilter> transFilter2 = vtkSmartPointer<vtkTransformFilter>::New();
		vtkSmartPointer<vtkTransformFilter> transFilter3 = vtkSmartPointer<vtkTransformFilter>::New();

//		transform->RotateWXYZ(180, this->rot_vec);
		switch(num_sur){
			case 2:
			case 4: transform->RotateWXYZ(180, 1,0,0);
				break;
			case 1:
			case 3: transform->RotateWXYZ(180, 0,1,0);
				break;
			case 5:
			case 6: transform->RotateWXYZ(180, 0,0,1);
				break;
		}

//		transform->RotateWXYZ(180, 0,1,0);
//		transform->RotateWXYZ(180, 0,0,1);
		transFilter1->SetInput(this->final_cube);
		transFilter1->SetTransform(transform);

		this->final_cube = transFilter1->GetPolyDataOutput();
		this->final_cube->Update();

				
		transFilter2->SetInput(this->centers_poly);
		transFilter2->SetTransform(transform);

		this->centers_poly = transFilter2->GetPolyDataOutput();
		this->centers_poly->Update();

		this->centers_poly->GetPoint(0, this->center);

		transFilter3->SetInput(this->normals_poly);
		transFilter3->SetTransform(transform);

		this->normals_poly = transFilter3->GetPolyDataOutput();
		this->normals_poly->Update();
		

		double aaaa=0;
		aaaa = vtkMath::Dot(vec, this->normals_poly->GetPoint(num_sur));
		printf("dot : %lf\n", aaaa);
		
		*/
	}
	
//	transform->Delete();
//	transformFilter_cube->Delete();
//	transformFilter_centers->Delete();
//	transformFilter_normals->Delete();
//	trans_normal->Delete();
//	trans_poly->Delete();
	
}


/*
void CubeSource::rotate(int rx, int ry, int rz){
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform->RotateX(rx);
	transform->RotateY(ry);
	transform->RotateZ(rz);
	transform->Update();
	
	vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
	transformFilter->SetTransform(transform);
	transformFilter->SetInput(this->final_cube);
	transformFilter->Update();
	this->final_cube = transformFilter->GetPolyDataOutput();
	this->final_cube->Update();
}

*/

void CubeSource::translate(double pt1[3], int num_sur, int num_sur2){
	
	double size;


	switch(num_sur)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		size=24;
		break;
	case 5:
	case 6:
		size=46;
		break;
	}

	this->normals->GetPoint(num_sur, this->vec);

	vtkMath::MultiplyScalar(this->vec, size);

	this->transform->Translate(this->vec);

	/*
	double pt2[3] = {0};
	this->centers_poly->GetPoint(num_sur, pt2);


	for(int i=0; i<3; i++){
		this->trans[i] = pt1[i] - pt2[i];
	}

	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform->Translate(this->trans);



	vtkSmartPointer<vtkTransformFilter> transformFilter_cube = vtkSmartPointer<vtkTransformFilter>::New();
	vtkSmartPointer<vtkTransformFilter> transformFilter_centers = vtkSmartPointer<vtkTransformFilter>::New();
	vtkSmartPointer<vtkTransformFilter> transformFilter_normals = vtkSmartPointer<vtkTransformFilter>::New();


	transformFilter_cube->SetInput(this->final_cube);
	transformFilter_cube->SetTransform(transform);

	
	this->final_cube = transformFilter_cube->GetPolyDataOutput();
	this->final_cube->Update();


	transformFilter_centers->SetInput(this->centers_poly);
	transformFilter_centers->SetTransform(transform);

	this->centers_poly = transformFilter_centers->GetPolyDataOutput();
	this->centers_poly->Update();

	this->centers_poly->GetPoint(0, this->center);


	transformFilter_normals->SetInput(this->normals_poly);
	transformFilter_normals->SetTransform(transform);

	
	this->normals_poly = transformFilter_normals->GetPolyDataOutput();
	this->normals_poly->Update();
	
	vtkSmartPointer<vtkPoints> trans_normal1 = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkPolyData> trans_poly1 = vtkSmartPointer<vtkPolyData>::New();

	double vec1[3], vec2[3], vec3[3];

	for(int i=0; i<this->normals_poly->GetNumberOfPoints(); i++){
		this->normals_poly->GetPoint(i, vec1);
		this->centers_poly->GetPoint(0, vec2);
		for(int j=0; j<3; j++){
			vec3[j] = vec1[j]-vec2[j];
		}
		trans_normal1->InsertNextPoint(vec3);
	}
	trans_poly1->SetPoints(trans_normal1);
	

	this->normals_poly->SetPoints(trans_normal1);
	this->normals_poly->Modified();
//	this->normals_poly->Update();

//	transform->Delete();
//	transformFilter_cube->Delete();
//	transformFilter_centers->Delete();
//	transformFilter_normals->Delete();
//	trans_normal1->Delete();
//	trans_poly1->Delete();
*/
}


//delete should be added

void CubeSource::del(){
	this->actor->Delete();
	this->centers->Delete();
	this->centers_poly->Delete();
	this->final_cube->Delete();
	this->mapper->Delete();
	
	this->normals->Delete();
	this->normals_poly->Delete();
	this->transformed_centers->Delete();
	this->transformed_normals->Delete();
	
	this->reader->Delete();
	this->polydatagroup->Delete();

}

