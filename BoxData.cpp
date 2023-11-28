#include "BoxData.h"
#include "header.h"



BoxData::BoxData():size1(0), blocknum(0),baseblocknum(0),eventonoff(false), blocknumber1(0), blocknumber2(0), existence(0), basenum(0), sep(0), box1(0), box2(0), plane1(0), plane2(0), baseblock1(0), baseblock2(0),boxdata1(0), boxdata2(0), a(0), b(0),c(0),d(0), e(0), val(0), basecont(0), boxcount2(0), boxid1(0), boxplanenum1(0), boxsep1(0) //���� �۵�
{ 
	//ȸ�� ����
	Q[0][0]=0;
	Q[0][1]=0;
	Q[0][2]=1;

	Q[1][0]=1;
	Q[1][1]=0;
	Q[1][2]=0;
	
	Q[2][0]=0;
	Q[2][1]=1;
	Q[2][2]=0;

	mat4[0]=0;
	mat4[1]=0;
	mat4[2]=1;
	mat4[3]=0;
	mat4[4]=1;
	mat4[5]=0;
	mat4[6]=0;
	mat4[7]=0;
	mat4[8]=0;
	mat4[9]=1;
	mat4[10]=0;
	mat4[11]=0;
	mat4[12]=0;
	mat4[13]=0;
	mat4[14]=0;
	mat4[15]=1;
	this->qw[0]=0;
	this->qw[1]=0;
	this->qw[2]=0;
	this->qw[3]=0;
	this->qw[4]=0;
	this->qx[0]=0;
	this->qx[1]=0;
	this->qx[2]=0;
	this->qx[3]=0;
	this->qx[4]=0;
	this->qy[0]=0;
	this->qy[1]=0;
	this->qy[2]=0;
	this->qy[3]=0;
	this->qy[4]=0;
	this->qz[0]=0;
	this->qz[1]=0;
	this->qz[2]=0;
	this->qz[3]=0;
	this->qz[4]=0;
	this->x[0]=0;
	this->x[1]=0;
	this->x[2]=0;
	this->x[3]=0;
	this->x[4]=0;
	this->y[0]=0;
	this->y[1]=0;
	this->y[2]=0;
	this->y[3]=0;
	this->y[4]=0;
	this->z[0]=0;
	this->z[1]=0;
	this->z[2]=0;
	this->z[3]=0;
	this->z[4]=0;
	this->TM[0]=vtkSmartPointer<vtkTransform>::New();
	this->TM[1]=vtkSmartPointer<vtkTransform>::New();
	this->TM[2]=vtkSmartPointer<vtkTransform>::New();
	this->TM[3]=vtkSmartPointer<vtkTransform>::New();
	this->TM[4]=vtkSmartPointer<vtkTransform>::New();
	this->TM[5]=vtkSmartPointer<vtkTransform>::New();
	this->TM[6]=vtkSmartPointer<vtkTransform>::New();
	this->matrix[0]=vtkSmartPointer<vtkMatrix4x4>::New();
	this->matrix[1]=vtkSmartPointer<vtkMatrix4x4>::New();
	this->matrix[2]=vtkSmartPointer<vtkMatrix4x4>::New();
	
	//������ ���� ����
	this->basechar[0]='a';
	this->basechar[1]='b';
	this->basechar[2]='c';
	this->basechar[3]='d';
	this->basechar[4]='e';
	epp[0]="10001";
	epp[1]="10002";
	epp[2]="10003";
	epp[3]="10004";
	epp[4]="10005";
	base[0]=false;
	base[1]=false;
	base[2]=false;
	base[3]=false;
	base[4]=false;
	
	this->boxidnum[0]=0;
	this->boxidnum[1]=0;
	this->myfile.open("D:/BlockData/Orientation.csv", ios::app);
	this->myfile<<"Block A,,,,,,,Block B"<<endl;
	this->myfile<<"qw,qx,qy,qz,x(roll),y(yaw),z(pitch),qw,qx,qy,qz,x(roll),y(yaw),z(pitch)"<<endl;

}
/*
Quaterniond BoxData::euler2Quaternion(const double roll, const double pitch, const double yaw)
{
	AngleAxisd rollAngle(roll, Vector3d::UnitZ());
    AngleAxisd yawAngle(yaw, Vector3d::UnitY());
    AngleAxisd pitchAngle(pitch, Vector3d::UnitX());

    Quaterniond q = rollAngle * yawAngle * pitchAngle;
    return q;
}
*/

void BoxData::DataExtract(CString &str)
{      
	
	    this->str5=str;
        for(int i=0; i<5;++i)
        {
		 this->val=str5.ReverseFind(this->basechar[i]);
		 

		 while(val>-1)
         {
		 if(!(this->base[i]))
		 {
				 BoxSize(epp[i]);
				 this->base[i]=true;
		 }
			 
		 this->e=str5.Find('^', val);
		 if((e-val)>=21&&(e-val)<=25)//anglevector
         //if((e-val)>=19&&(e-val)<=25)//������ ���ռ� ���� �Ǻ�, ���� ���� �´��� Ȯ��, euler 
         {
		 this->a=str.Find('w',val);
         this->b=str5.Find('x',val);
         this->c=str5.Find('y',val);
         this->d=str5.Find('z',val);
         this->app=str.Mid(a+1,b-(a+1));
         this->bpp=str5.Mid(b+1,c-(b+1));
         this->cpp=str5.Mid(c+1,d-(c+1));
		 this->dpp=str5.Mid(d+1,e-(d+1));
		 this->qw[i]=_wtof(app);
         this->qx[i]=_wtof(bpp);
         this->qy[i]=_wtof(cpp);
         this->qz[i]=_wtof(dpp);

         this->TM[i]=vtkSmartPointer<vtkTransform>::New();
		 //this->TM[6]->Rotate
		 
		 this->TM[i]->PostMultiply();
		 
		 this->q.Set(qw[i], qx[i], qy[i], qz[i]);
		 this->q.ToMatrix3x3(this->mat3);
		 this->TransitionMatrix3x3(mat3, Q, this->mat31);
		 this->mat3tomat4(this->mat31, this->mat4);
		 this->TM[i]->SetMatrix(mat4);
		 //this->TM[i]->RotateZ(180);
		 //this->TM[i]->RotateY(-180);

		 //this->TM[6]=vtkSmartPointer<vtkTransform>::New();
		 //this->TM[6]->PostMultiply();
		 /*double c1=cos(y[i]/2.0);
		 double c2=cos(z[i]/2.0);
		 double c3=cos(x[i]/2.0);
		 double s1=sin(y[i]/2.0);
		 double s2=sin(z[i]/2.0);
		 double s3=sin(x[i]/2.0);*/
		 /*this->qw[i]=sqrt(1.0+c1*c2+c1*c3-s1*s2*s3+c2*c3)/2.0;
		 double w4=(4.0*qw[i]);
		 this->qx[i]=(c2*s3+c1*s3+s1*s2*c3)/w4;
		 this->qy[i]=(s1*c2+s1*c3+c1*s2*s3)/w4;
		 this->qz[i]=(-s1*s3+c1*s2*c3+s2)/w4;*/
		 //double c1c2=c1*c2;
		 //double s1s2=s1*s2;
		 ///////////////////////////////////////////Original
		// this->q=euler2Quaternion(qx[i],qz[i],qy[i]);
		/* this->qw[i]=c1*c2*c3+s1*s2*s3;
		 this->qx[i]=c2*c3*s1-c1*s2*s3;
		 this->qy[i]=c1*s2*c3+s1*c2*s3;
		 this->qz[i]=c1*c2*c3-s1*c2*c3;
		 double len=sqrt(qw[i]*qw[i]+qx[i]*qx[i]+qy[i]*qy[i]+qz[i]*qz[i]);
		 this->qw[i]/=len;
		 this->qx[i]/=len;
		 this->qy[i]/=len;
		 this->qz[i]/=len;*/

		 //double w4=(4.0*qw[i]);
		 
		 //this->q.ToMatrix3x3(this->mat3);
		 //this->TransitionMatrix3x3(mat3, Q, this->mat31);
		 //this->mat3tomat4(this->mat3, this->mat4);
		 /*double axis[3];
		 double rad=this->q.GetRotationAngleAndAxis(axis);
		 rad*=180.0/3.14;
		 this->TM[i]->RotateWXYZ(rad, axis[0], axis[1], axis[2]);*/
		 //this->TM[i]->RotateZ(90);
		 //this->TM[i]->RotateX(90);
		 
		 
		 //this->TM[i]->RotateY(-90);
		 //this->TM[i]->RotateZ(90);
		 //this->TM[i]->RotateX(-90);
		/* this->TM[i]->RotateZ(z[i]);
		 this->TM[i]->RotateY(y[i]);
		 this->TM[i]->RotateX(x[i]);*/
		 stringstream ss[7];

		 ss[0]<<qw[i];
		 ss[1]<<qx[i];
		 ss[2]<<qy[i];
		 ss[3]<<qz[i];
		 ss[4]<<x[i];
		 ss[5]<<y[i];
		 ss[6]<<z[i];


		 switch(i)
		 {
		 case 0:
			 myfile<<ss[0].str()<<","<<ss[1].str()<<","<<ss[2].str()<<","<<ss[3].str()<<","<<ss[4].str()<<","<<ss[5].str()<<","<<ss[6].str()<<endl;
			 break;
	     case 1:
			 myfile<<",,,,,,,"<<ss[0].str()<<","<<ss[1].str()<<","<<ss[2].str()<<","<<ss[3].str()<<","<<ss[4].str()<<","<<ss[5].str()<<","<<ss[6].str()<<endl;
			 break;
		 }
		
		 //20170614Modified
		 /*this->TM[i]->RotateZ(qy[i]);
		 this->TM[i]->RotateY(qz[i]);
		 this->TM[i]->RotateX(qx[i]);*/

         //SJBaseV2
/*
		 this->TM[i]->RotateX(-90);
		 this->TM[i]->RotateY(-90);
		 this->TM[i]->RotateZ(qz[i]);
		 this->TM[i]->RotateY(qy[i]);
		 this->TM[i]->RotateX(qx[i]);*/
		 //KingTideIMU
		 /*this->TM[i]->RotateZ(qz[i]);
		 this->TM[i]->RotateY(qy[i]);
		 this->TM[i]->RotateX(qx[i]);*/


		 //this->TM[5]=vtkSmartPointer<vtkTransform>::New();
		 //this->TM[6]=vtkSmartPointer<vtkTransform>::New();

		 //this->TM[i]->PostMultiply();
		 //this->TM[5]->RotateWXYZ(qw[i],qx[i],qy[i],qz[i]);
		 //this->TM[5]->GetOrientation(this->rot[i]);

		 /*
		 this->x[i]=this->rot[i][0];
		 this->y[i]=this->rot[i][1];
		 this->z[i]=this->rot[i][2];
		 this->TM[5]->DeepCopy(this->TM[i]);
		 this->TM[6]->RotateX(this->y[i]);
		 this->TM[6]->RotateY(this->z[i]);
		 this->TM[6]->RotateZ(this->x[i]);
		 this->TM[5]->GetMatrix(this->matrix[0]);
		 this->TM[6]->GetMatrix(this->matrix[1]);
		 this->matrix[0]->Transpose();
		 vtkMatrix4x4::Multiply4x4(this->matrix[0],this->matrix[1],this->matrix[2]);
		 this->TM[i]->Concatenate(this->matrix[2]);
		 */

		 
		
		 //SJBASE2


		
		 /*this->TM[i]->RotateX(rot[i][2]);
         this->TM[i]->RotateY(rot[i][0]);
         this->TM[i]->RotateZ(rot[i][1]);*/
		 
		 

		 break;
         }
		 else
		 {
         this->str5=this->str5.Left(val);
	     val=this->str5.ReverseFind(this->basechar[i]);

         }
        }
		}

		this->val=str.Find('!');
        while(this->val>-1)//��û�� ������ ���� ���ɼ�..
		{
           this->a=str.Find('@',val);
           if((a-val)==6)
           {
		   this->bpp=str.Mid(val+1,a-(val+1));
		   if(this->app!=this->bpp)
		   {
           this->app=bpp;//BoxData CString
           BoxSize(app);
		   }
           }
		   this->val=str.Find('!',val+1);
        }

}

void BoxData::BoxSize(CString &BoxID)//������ �ױ� �� �� ����, blockID �и� �� ����, ���� �۵�
{
	
	this->str1=string(CT2CA(BoxID.operator LPCWSTR()));
	this->boxcount2=count(boxdata.begin(), boxdata.end(), str1);
	if(!boxcount2)
	{
	this->boxid1=0;
	this->boxplanenum1=0;
	this->boxsep1=0;
	this->str2=BoxID.Right(3);
	this->boxid1=_ttoi(this->str2);
	this->str3=BoxID.Mid(1,1);
	this->boxplanenum1=_ttoi(this->str3);
	this->str4=BoxID.Left(1);
	this->boxsep1=_ttoi(this->str4);
	
	////////////////////////////////////////
	this->boxdata.push_back(this->str1);
	this->boxid.push_back(this->boxid1);
	this->boxplanenum.push_back(this->boxplanenum1);
	this->boxsep.push_back(this->boxsep1);
	}

	
}



void BoxData::BoxTreeMake(int &num)//���� ����� ���� ���� �κ�.. ���� ���� �߸� �۵��Ͽ��� ����� ���� ����ؾ� ��..
{
	;//���� ���� �����Ϳ� ���� �������� ����->���� �νĵ� ��� ���� ����
	this->eventonoff=false;//����
	this->blocknumber1=this->blocknum;//����
	this->blocknumber2=this->blocknum+1;//���ο� ��� ���������� ���ο� ī���� �ù��� //����
	this->box1=boxid.at(blocknumber1);//����
	this->plane1=this->boxplanenum.at(blocknumber1);//����
	this->baseblocknum=0;//����
	this->existence=0;
	this->boxidnum[0]=0;
	this->boxidnum[1]=0;
	this->sep=0;
	this->boxdata1=atoi(this->boxdata.at(blocknumber1).c_str());
	this->boxdata2=0;

	if(num>1)
	{
	this->box2=boxid.at(blocknumber2);//����
	this->plane2=this->boxplanenum.at(blocknumber2);
	this->boxdata2=atoi(this->boxdata.at(blocknumber2).c_str());}//����
	//int plane1=boxplanenum[blocknumber1];
	
	this->size1=this->boxdata.size();
	for(signed int i=this->blocknumber1;i<this->size1;++i)
	{
	    if(this->boxsep.at(i)==2)
		this->sep+=1;
	}

	if((this->sep)==2)
	{
		int a=variables.cube.BoxSeperation(this->blocknumber1, this->blocknumber2);//��� �и� ��� ���� ��� ���� �ϴ� ����
		
		if(a)
		{
		this->eventonoff=true;//����
		return;
		}

		else
		{EraseBox(num);return;}//����
	}
	else
	{
	int k=0;//����
	for(signed int i=this->blocknumber1; i<this->size1;++i)//����
	{
	  bool onoff=variables.Block[boxid.at(i)].getOnoff();//����

	  if(onoff==false)//����
	  {
	   switch(boxid.at(i))//���� �۵� ���ɼ�
	   {
	    case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		variables.Base[this->boxid.at(i)].setOnoff(true);////����
		variables.Block[this->boxid.at(i)].setOnoff(true);////���� 
		this->baseblocknum+=1;//����
		this->eventonoff=true;
		//basenum=0;//����
		//basenum=i;//����
		break;
	   }
	  }
	  else if(onoff==true)//����
	  { existence+=1; boxidnum[k]=1;}
	  k+=1;
	}

	switch(existence)
	{

      case 2:
		  
		  BaseSearch();//����//�� ���̽� �׷��� ���̽� ��� ����
		  if((this->baseblock1)!=(this->baseblock2))//����//���̽� ����� ���� �ٸ� ��� ����, ���̽� ����� ���� �޶�� �� ���� ����� ���� �ٸ� ���̽� �׷쿡 ���� ���� Ȯ�� ������
		  {
		  if(baseblock1<baseblock2)//����//���̽� ��� ���ڰ� ���� ���� �������� ���̽� �׷� ���� ����
		  {
			  //variables.cube.GroupConverge(this->blocknumber1, this->blocknumber2);
			  variables.cube.GroupConverge(this->blocknumber1, this->blocknumber2, this->baseblock1, this->baseblock2);//���̽� ��� �׷��� ��� ȸ���� �ݿ��� ���� ����
			  variables.Base[this->baseblock2].setOnoff(false);//���̽� ��� ��ȣ�� ��������� ���� ����� OFF��Ŵ
			  baseid=baseblock2;
			  baseonoff=0;
			  this->blocknum+=num;//boxdata ���Ϳ� ����� ����� ������ blocknum�� ����� ����� ������ ��ġ��Ŵ, ���� ��� �����͸� ���� �����ͷ� �����Ѵٴ� �ǹ�
			  this->eventonoff=true;//�̺�Ʈ �߻��� �˸�, Renderer Ŭ������ Mergepolydata ���� �����ϴ� ���� ������ ���� ����
			  TurnOnBox(this->blocknumber1);//���˵ǰ� ����� ��ϵ��� On ��Ű�� ������.
			  return;
		  }

		  else if(baseblock1>baseblock2)//���̽� ��� ���ڰ� ���� ���� �������� ���̽� �׷� ���� ����
		  {
			  //variables.cube.GroupConverge(this->blocknumber2, this->blocknumber1);
			  variables.cube.GroupConverge(this->blocknumber2, this->blocknumber1, this->baseblock2, this->baseblock1);//���̽� ��� �׷��� ��� ȸ���� �ݿ��� ���� ����
			  variables.Base[this->baseblock1].setOnoff(false);//���̽� ��� ��ȣ�� ��������� ���� ����� OFF��Ŵ
			  baseid=baseblock1;
			  baseonoff=0;
			  this->blocknum+=num;//boxdata ���Ϳ� ����� ����� ������ blocknum�� ����� ����� ������ ��ġ��Ŵ, ���� ��� �����͸� ���� �����ͷ� �����Ѵٴ� �ǹ�
			  this->eventonoff=true;//�̺�Ʈ �߻��� �˸�, Renderer Ŭ������ Mergepolydata ���� �����ϴ� ���� ������ ���� ����
			  TurnOnBox(this->blocknumber1);//���˵ǰ� ����� ��ϵ��� On ��Ű�� ������.
			  return;
	      }
		  }
		  else
		  {
		  EraseBox(num);//���˵� �� ��� �����͸� ����, ���� �����ͷ� �������� ����
		  return;
		  }
		  variables.cube.BaseClear();//cube�� ���� ���� �ʱ�ȭ
		  
		  break;

	  case 1:
		  if(num>1)
		  {
			  if(this->boxidnum[0])//����
		      variables.cube.BoxConverge(this->blocknumber1, this->blocknumber2);//����
		      else if(this->boxidnum[1])//����
		      variables.cube.BoxConverge(this->blocknumber2, this->blocknumber1);//����
		      this->blocknum+=num;//����
			  this->eventonoff=true;//����
			  TurnOnBox(this->blocknumber1);//ó���� Ű�� ����� ����..����
			  return;
		  }
		  else
		  {EraseBox(num);//���� �۵�
		  return;
		  }
		  break;
		  /*else if(baseblocknum==1)//�ӽù���
		  {
			  this->blocknum+=num;
			  TurnOnBox(blocknumber1);
		  }*///�۵� ���ɼ� ���� ����
		 

	  case 0:

		if(this->baseblocknum>0)//���� �۵�
		{this->blocknum+=num;
		this->eventonoff=true;
		return;}
		else
		{EraseBox(num); return;}//���� �۵�
		break;
			/*if(num>1)//���ǿ��� �۵� ���ɼ� ���� ����
			{
			if(blocknumber1==basenum)
			variables.cube.BoxConverge(blocknumber1, blocknumber2);
			else if(blocknumber2==basenum)
			variables.cube.BoxConverge(blocknumber2, blocknumber1);
			}*/
			//TurnOnBox(blocknumber1);//����
		    //this->blocknum+=num;//����
			//this->eventonoff=true;//����
		//}
		//else if(baseblocknum==2)//���� �۵�
		//{
			//BaseSearch();//���� �۵�
			/*if((plane1>0)&&(plane2>0))//���ǿ��� �۵� ���ɼ� ���� ����
			{
				if(box1<box2)
				{variables.cube.BoxConverge(blocknumber1, blocknumber2);
			     variables.Base[box2].setOnoff(false);}
				else if(box1>box2)
				{variables.cube.BoxConverge(blocknumber2, blocknumber1);
			     variables.Base[box1].setOnoff(false);}
				this->blocknum+=num;
				this->eventonoff=true;
			}*/
		  
		  /*else*/ //if(this->baseblock1!=this->baseblock2)//���� �۵�
		  //{this->blocknum+=num;}//����
		  //else
			//{EraseBox(num);}//���� �۵�

		  //variables.cube.BaseClear();//���� �۵�
				
		  
		
	}
	}
	this->boxdata1=0;
	this->boxdata2=0;
	return;
}

void BoxData::BaseSearch()//���� �۵�
{
	this->baseblock1=0;//���̽� �ѹ� �ʱ�ȭ
	this->baseblock2=0;//���̽� �ѹ� �ʱ�ȭ
	variables.cube.BaseClear();//cube�� ���Ǵ� ���� �ʱ�ȭ
	variables.cube.BaseSearchParent(&(variables.Block[this->box1]));//���� �ڽ����� �����Ͽ� ���̽� ��ϱ��� �˻��Ͽ� cube�� base ���Ϳ� ���ʷ� ������
	variables.cube.BaseSearchParent(&(variables.Block[this->box2]));//���� �ڽ����� �����Ͽ� ���̽� ��ϱ��� �˻��Կ� cube�� base ���Ϳ� ���ʷ� ������   
	this->baseblock1=variables.cube.base.at(0);//base ���Ϳ� ����� ���� ù ��° ���̽� ��� ���ڸ� ������
	this->baseblock2=variables.cube.base.at(1);//base ���Ϳ� ����� ���� �� ��° ���̽� ��� ���ڸ� ������

}
void BoxData::TurnOnBox(int &num)//����
{
	this->size1=boxdata.size();
	for(unsigned int i=num;i<boxdata.size();++i)
	{
		variables.Block[boxid.at(i)].setOnoff(true);	
	}
}

void BoxData::EraseBox()//���� �۵�
{
     DeleteBoxData(this->boxdata1);
	 if(boxdata2!=0)
	 DeleteBoxData(this->boxdata2);
}

void BoxData::EraseBox(int num)//���� �۵�
{
     for(int i=0; i<num;++i)
	 {
		 this->boxdata.pop_back();
		 this->boxid.pop_back();
		 this->boxplanenum.pop_back();
		 this->boxsep.pop_back();
	 }
}

void BoxData::DeleteBoxDataSep(int boxdata)
{
	this->boxiter=this->boxdata.begin();
	this->iditer=this->boxid.begin();
	this->planeiter=this->boxplanenum.begin();
	this->sepiter=this->boxsep.begin();
	
	while((this->boxdata.end())!=boxiter)
	{
	if(boxdata==(atoi((*boxiter).c_str())))
	{
    boxiter=this->boxdata.erase(boxiter);
    iditer=this->boxid.erase(iditer);
    planeiter=this->boxplanenum.erase(planeiter);
	sepiter=this->boxsep.erase(sepiter);
	}
	else
	{
		++boxiter;
		++iditer;
		++planeiter;
		++sepiter;
	}
	}
}
/*
void BoxData::DeleteBoxDataSep(string boxdata)
{
	this->boxiter=find(this->boxdata.begin(), this->boxdata.end(), boxdata);
	int k=boxiter-(boxdata.begin());
	this->iditer=this->boxid.begin();
	this->planeiter=this->boxplanenum.begin();
	this->sepiter=this->boxsep.begin();
	iditer+=k;
	planeiter+=k;
	sepiter+=k;
	this->boxdata.erase(boxiter);
    this->boxid.erase(iditer);
    this->boxplanenum.erase(planeiter);
	this->boxsep.erase(sepiter);
}
*/
void BoxData::DeleteBoxData(int boxdata)
{
	this->boxiter=this->boxdata.begin();
	this->iditer=this->boxid.begin();
	this->planeiter=this->boxplanenum.begin();
	this->sepiter=this->boxsep.begin();


	while((this->boxdata.end())!=boxiter)
	{
	if(boxdata==(atoi((*boxiter).c_str())))
	{
    boxiter=this->boxdata.erase(boxiter);
    iditer=this->boxid.erase(iditer);
    planeiter=this->boxplanenum.erase(planeiter);
	sepiter=this->boxsep.erase(sepiter);
    --(this->blocknum);
	}
	else
	{
		++boxiter;
		++iditer;
		++planeiter;
		++sepiter;
	}
	}
}

void BoxData::mat3tomat4(double mat3[3][3], double mat4[16])
{
mat4[0]=mat3[0][0];
mat4[1]=mat3[0][1];
mat4[2]=mat3[0][2];
mat4[3]=0;
mat4[4]=mat3[1][0];
mat4[5]=mat3[1][1];
mat4[6]=mat3[1][2];
mat4[7]=0;
mat4[8]=mat3[2][0];
mat4[9]=mat3[2][1];
mat4[10]=mat3[2][2];
mat4[11]=0;
mat4[12]=0;
mat4[13]=0;
mat4[14]=0;
mat4[15]=1;
}

void BoxData::TransitionMatrix3x3(double T[3][3], double Q[3][3], double Result[3][3])
{
	
 double sum=0;
 int i,j,k;
  //Finding transpose of matrix a[][] and storing it in array trans[][].
for(i = 0; i < 3; ++i)
{
        for(j = 0; j < 3; ++j)
        {
            trans[j][i]=Q[i][j];
        }
}
//
for(i = 0; i < 3; ++i)
{
	for(j = 0; j < 3; ++j)
	{
		
		for(k = 0; k < 3; ++k)
		{
                 sum+= trans[i][k] * T[k][j];
		}
		QT[i][j]=sum;
		sum=0;
	}

}
for(i = 0; i < 3; ++i)
{
	for(j = 0; j < 3; ++j)
	{
		for(k = 0; k < 3; ++k)
		{
			sum+=QT[i][k] * Q[k][j];
		}
		Result[i][j]=sum; 
	    sum=0;
	}
}
}

void BoxData::DeleteBoxDataID(int boxidnum)
{
	
	this->boxiter=this->boxdata.begin();
	this->iditer=this->boxid.begin();
	this->planeiter=this->boxplanenum.begin();
	this->sepiter=this->boxsep.begin();
	
	while((this->boxid.end())!=iditer)
	{
	if(boxidnum==(*iditer))
	{
    boxiter=this->boxdata.erase(boxiter);
    iditer=this->boxid.erase(iditer);
    planeiter=this->boxplanenum.erase(planeiter);
	sepiter=this->boxsep.erase(sepiter);
    --(this->blocknum);
	}
	else
	{
		++boxiter;
		++iditer;
		++planeiter;
		++sepiter;
	}
	}
}

BoxData::~BoxData()
{
	/*delete []&xr;
	delete []&yr;
	delete []&zr;
	delete []&w;
	delete []&x;
	delete []&y;
	delete []&z;
	*/
	this->TM[0]->Delete();
	this->TM[1]->Delete();
	this->TM[2]->Delete();
	this->TM[3]->Delete();
	this->TM[4]->Delete();
	this->TM[5]->Delete();
	delete []&TM;
	this->matrix[0]->Delete();
	this->matrix[1]->Delete();
	this->matrix[2]->Delete();
	delete []&matrix;
	this->boxdata.clear();
	this->boxid.clear();
	this->boxplanenum.clear();
	this->boxsep.clear();
	delete []&boxidnum;
	this->myfile.close();
}

