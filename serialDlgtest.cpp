
// serialDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "serial.h"
#include "serialDlg.h"

#include "myheader.h"
#include "vtkMath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 CStatic *pclStatic = new CStatic;
LPRECT rect = new CRect;










// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CserialDlg 대화 상자




CserialDlg::CserialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CserialDlg::IDD, pParent)
	, m_str_comport(_T(""))
	, m_str_baudrate(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CserialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_comport_list);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_str_comport);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_str_baudrate);
	DDX_Control(pDX, IDC_EDIT_RCV_VIEW, m_edit_rcv_view);
	DDX_Control(pDX, IDC_EDIT_SEND_DATA, m_edit_send_data);
}

BEGIN_MESSAGE_MAP(CserialDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
       ON_MESSAGE(WM_MYCLOSE, &CserialDlg::OnThreadClosed)
       ON_MESSAGE(WM_MYRECEIVE,&CserialDlg::OnReceive)

	   ON_BN_CLICKED(IDC_BT_CONNECT, &CserialDlg::OnBnClickedBtConnect)
	   ON_CBN_SELCHANGE(IDC_COMBO_COMPORT, &CserialDlg::OnCbnSelchangeComboComport)
	   ON_BN_CLICKED(IDC_BT_CLEAR, &CserialDlg::OnBnClickedBtClear)
	   ON_BN_CLICKED(IDC_BT_SEND, &CserialDlg::OnBnClickedBtSend)
END_MESSAGE_MAP()


// CserialDlg 메시지 처리기
LRESULT CserialDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
        //overlapped i/o 핸들을닫는다.
        ((CMycomm*)lpara)->HandleClose();
        delete ((CMycomm*)lpara);
 
        return 0;
}

vtkSmartPointer<vtkTransform> tf1 = vtkSmartPointer<vtkTransform>::New();
vtkSmartPointer<vtkTransform> tf2 = vtkSmartPointer<vtkTransform>::New();

//vtkSmartPointer<vtkTransformFilter> tf = vtkSmartPointer<vtkTransformFilter>::New();
//vtkSmartPointer<vtkTransformFilter> tf2 = vtkSmartPointer<vtkTransformFilter>::New();
 
vtkSmartPointer<vtkTransformPolyDataFilter> tff1 = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
vtkSmartPointer<vtkTransformPolyDataFilter> tff2 = vtkSmartPointer<vtkTransformPolyDataFilter>::New();


vtkSmartPointer<vtkCamera> cam = vtkSmartPointer<vtkCamera>::New();
vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
vtkSmartPointer<vtkPoints> cam_position = vtkSmartPointer<vtkPoints>::New();

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

vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();


LRESULT CserialDlg::OnReceive(WPARAM length, LPARAM lpara)
{
        CString str;
		char data[10000] = {0}; 
	
        vector<int> flag;
		int flag2 = 0;
		
		CString boxid,xr,yr,zr,boxids;
		CString boxid2,xr2,yr2,zr2;
		CString f1,f2;

		string str1;
		 

		if(m_comm)
		{       
			  
			m_comm->Receive(data,length); //length 길이만큼데이터를받는다.
               data[100] = '\0';
			   
			   
			   
			   for(int i = 0;i<(int)length;i++)
               {
                       str += data[i];	
			   }
			   Sleep(100);
	
	int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
	int val1=0;
	int val2=0;
	int val3=0;
	int val4=0;

	a=str;

    b=0x80000000;
	c=a&b;

	if (c==0x80000000)
	{
     d=0x7f800000;
	 e=a&d;
	 e>>=23;
	 e=~e+1;
	 val1 +=e;

	}

	else
	{

	 d=0x7fc00000;
	 e=a&d;
	 e>>=23;
	 val1 +=e;
	}

	f=0x00400000;
	g=a&f;
	g<<=9;

	if (g==0x80000000)
	{
     h=0x003fc000;
	 i=a&h;
	 i>>=14;
	 i=~i+1;
	 val2 +=i;
	}

	else
	{
	 h=0x003fc000;
	 i=a&h;
	 i>>=14;
	 val2 +=i;
	}

	j=0x00002000;
	k=a&j;
	k<<=18;

	if(k==0x80000000)
	{

    l=0x00001fe0;
	m=a&l;
	m>>=5;
	m=~m+1;
	val3 +=m;

	else
	{
	val2 +=k;
	l=0x00001fe0;
	m=a&l;
	m>>=5;
	val3 +=m;
	}

	n=0x0000001f;
	o=a&n;
	val4 +=o;
	
	switch(val4)
	{
	case 1:


	boxid = 15001;
	xr = val1;
	yr = val2;
	zr = val3;

    case 2:

	boxid2 = 16002;
	xr2 = val1;
	yr2 = val2;
	zr2 = val3;

	}

	/*
	val = str.Find('@');
    
	f1 = str.Left(val);
	f2 = str.Mid(val+1);

	a = f1.Find('{');
	b = f1.Find('}');
	c = f2.Find('{');
	d = f2.Find('}');
	
	
	
	
	CString app = f1.Mid(a+1,b-(a+1));
	CString bpp = f2.Mid(c+1,d-(c+1));

	f = app.Find('b');
	g = app.Find('x');
	h = app.Find('y');
	i = app.Find('z');
	j = app.Find('#');
	*/

	/*
	boxid = app.Mid(f+1,g-(f+1));
	xr = app.Mid(g+1,h-(g+1));
	yr = app.Mid(h+1,i-(h+1));
	zr = app.Mid(i+1,j-(i+1));
	
	k = bpp.Find('b');
	l = bpp.Find('x');
	m = bpp.Find('y');
	n = bpp.Find('z');
	o = bpp.Find('#');

	
	boxid2 = bpp.Mid(k+1,l-(k+1));
	xr2 = bpp.Mid(l+1,m-(l+1));
	yr2 = bpp.Mid(m+1,n-(m+1));
	zr2 = bpp.Mid(n+1,o-(n+1));

	*/

	/*
	if((xr = '\0')||(yr = '\0')||(zr = '\0')){
		xr = xr2;
	    yr = yr2;
		zr = zr2;
		
	}
	*/
	if((xr = '\0')||(xr2 = '\0')){
		
	    xr = xr2;
		
	}
	if((yr = '\0')||(yr2 = '\0')){
		
	    yr = yr2;
		
	}
	if((zr = '\0')||(zr2 = '\0')){
		
		zr = zr2;
	}
	
	int str_int = _ttoi(boxid2);
	str1 = std::string(CT2CA(boxid2.operator LPCWSTR()));
	
	xrr2 = _wtof(xr);
	yrr2 = _wtof(yr);
	zrr2 = _wtof(zr);
	xrr3 = _wtof(xr2);
	yrr3 = _wtof(yr2);
	zrr3 = _wtof(zr2);
	
	if ((xrr3 > xrr2+1)||(xrr3 < xrr2-1)){
		xrr3=xrr2;
	}
	if ((yrr3 > yrr2+1)||(yrr3 < yrr2-1)){
		yrr3=yrr2;
	}
	if ((zrr3 > zrr2+1)||(zrr3 < zrr2-1)){
		zrr3=zrr2;
	}

	
	//xrr4 = (xrr3 + xrr2)/2;
	//yrr4 = (yrr3 + yrr2)/2;
	//zrr4 = (zrr3 + zrr2)/2;
	
zrr4 = zrr3 +180;
	
	
	

			//  for(int i=0; i<6; i++){
			//	   str1.push_back(data[i]);
			 // }

			
			   m_edit_rcv_view.ReplaceSel(str); //에디트박스에표시하기위함
			   m_edit_rcv_view.LineScroll(m_edit_rcv_view.GetLineCount());
     
			   //str = "";

			  
			  // int str_int = atoi(str1.c_str());
			   if(str_int>10000){
			   if(str_arr.size() == 0){
					   str_arr.push_back(str1);
				   
				//   str_arr.push_back(string_boxid);
			   }
			   else{
				   

				   for(int i=0; i<str_arr.size(); i++){
						   flag.push_back(abs(str1.compare(str_arr[i])));
				   }
				   for(int i=0; i<flag.size(); i++){
						   flag2 += flag[i];
				   }
				   if(flag2 == flag.size()){
						   str_arr.push_back(str1);
					 
					//	    str_arr.push_back(string_boxid);
				   }
			   }
			   }
			   int size = str_arr.size();
				
			
			   
			   
			   
			  
			  
			  // pclStatic = (CStatic *)GetDlgItem(IDC_SCREEN);
			   //renWin->SetParentId(pclStatic->m_hWnd);
			   //pclStatic->GetWindowRect(rect);
			   //renWin->SetSize(rect->right-rect->left,rect->bottom-rect->top);
			   

			    
	         //  renWin->SetPosition(0,0);
	           renWin->SetSize(750,550);
			   iren->SetRenderWindow(renWin);
					
					
						
				if(size == 2){
				 	
					
					int num_sur1 = str_arr[0][1] - '0';
					int num_sur2 = str_arr[1][1] - '0';

					string ID_1;
					string ID_2;

					for(int i=0; i<3; i++){
				            ID_1.push_back(str_arr[0][i+2]);
							ID_2.push_back(str_arr[1][i+2]);
					}
					double vec[3] = {0};
					double pt1[3] = {0};

					CubeSource cube1;
					CubeSource cube2;
					
					cube1.initialization();
					cube2.initialization();

					cube1.ID = ID_1;
					cube2.ID = ID_2;

					cube1.normals->GetPoint(num_sur1, vec);
					cube1.centers->GetPoint(num_sur1, pt1);

					cube2.rotate(vec, num_sur2);
					cube2.translate(pt1, num_sur2);

					
				//	cube1.make_actor();
					cube1.make_actor_Base();		
					cube2.make_actor();

					if(Cube_data.size() == (size-2)){
						Cube_data.push_back(cube1);
						Cube_data.push_back(cube2);
					}

				       
						
					
				//	lut->SetTableRange(0,10);

//					cube1.mapper->SetLookupTable(lut);
	//				cube1.actor->SetMapper(cube1.mapper);
					//tf1->RotateWXYZ(360,xrr2,yrr2,zrr2);
					//tf2->RotateZ(zrr4);
					//tf2->RotateY(yrr4);
					//tf2->RotateX(xrr4);
					//tf2->Update();
					
					
									

				//	vtkSmartPointer<vtkPolyData> pd = vtkSmartPointer<vtkPolyData>::New();
				//	pd->SetPoints(cam_position);
				//	pd->Update();
							
				//	vtkSmartPointer<vtkTransformFilter> tff = vtkSmartPointer<vtkTransformFilter>::New();
				//	tff->SetTransform(tf2);
				//	tff->SetInput(pd);
				//	tff->Update();
					
					int ra = 90;
					int ra2 = 180;
					int ra3 = 270;
					int ra4 = 360;
				
					
					
					//	cube1.actor->SetUserTransform(tf2);
				//	cube2.actor->SetUserTransform(tf2);
					cube1.actor->RotateX(zrr3);
					cube1.actor->RotateY(yrr3-ra);
					cube1.actor->RotateZ(xrr3-ra2+20);
					cube2.actor->RotateX(zrr3);
					cube2.actor->RotateY(yrr3-ra);
					cube2.actor->RotateZ(xrr3-ra2+20);

					
					
					ren1 = vtkRenderer::New();
					ren1->ResetCamera();
					iren->SetRenderWindow(renWin);
					renWin->AddRenderer(ren1);
					ren1->AddActor(cube1.actor);
					ren1->AddActor(cube2.actor);
					ren1->SetBackground(0,0,0);
			       // ren1->SetActiveCamera(cam);
					
					
					/*
					cam->SetFocalPoint(0,0,0);
					//cam->SetDistance(100);
					cam->Roll(xrr4);
					cam->Pitch(yrr4);   
			  	    cam->Yaw(zrr4);
					//cam->Azimuth(zrr4);
				    cam->UpdateViewport(ren1);					
		            */

					renWin->Modified();
					renWin->Render();	
						
				
						
					
						
						
					

					
						
					
   }
			   
   
   
   /*
			   else if((size>2) && (size%2 == 0)){
			       		    
				       renWin->SetSize(750,550);
			            iren->SetRenderWindow(renWin);
				        
						int flag1 = 0;
						int flag2 = 0;
						int num_cube1 = 0;

						int num_sur1 = str_arr[size-2][1] - '0';
						int num_sur2 = str_arr[size-1][1] - '0';

						string ID_1, ID_2, ID_temp;

						for(int i=0; i<3; i++){
							ID_1.push_back(str_arr[size-2][i+2]);
							ID_2.push_back(str_arr[size-1][i+2]);
						}

						for(int i=0; i<size-2; i++){
							flag1 = ID_1.compare(Cube_data[i].ID);
							flag2 = ID_2.compare(Cube_data[i].ID);
							if(flag1 == 0){
								num_cube1 = i+1;
								num_sur1 = str_arr[size-2][1] - '0';
								num_sur2 = str_arr[size-1][1] - '0';
								break;
							}
							else if(flag2 == 0){
								num_cube1 = i+1;
								ID_temp = ID_1;
								ID_1 = ID_2;
								ID_2 = ID_temp;
								num_sur1 = str_arr[size-1][1] - '0';
								num_sur2 = str_arr[size-2][1] - '0';
								break;
							}
						}

						double vec[3] = {0};
						double pt1[3] = {0};

						CubeSource cube;

						cube.initialization();
						cube.ID = ID_2;

						Cube_data[num_cube1].normals->GetPoint(num_sur1, vec);
						Cube_data[num_cube1].centers->GetPoint(num_sur1, pt1);

						cube.rotate(vec, num_sur2);
						cube.translate(pt1, num_sur2);
						
						cube.make_actor();
						if(Cube_data.size() == size-2){
							Cube_data.push_back(cube);
						}
						

						
						
						
						
						ren1 = vtkRenderer::New();
						
					
						for(int i=0; i<Cube_data.size(); i++){
							if(i==0){
							//	Cube_data[i].make_actor_Base();
								ren1->AddActor(Cube_data[i].actor);
							}
							else{
							//	Cube_data[i].make_actor();
								ren1->AddActor(Cube_data[i].actor);
							}
							
						}

						ren1->SetBackground(0,0,0);							
						ren1->Modified();
					
						renWin = vtkRenderWindow::New();
						renWin->AddRenderer(ren1);
						renWin->SetInteractor(iren);
						renWin->Render();
						renWin->Modified();	
						  
						
						
						
			   }
		
			*/
		}
  
     
		
 return 0;
} 

BOOL CserialDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	       m_combo_comport_list.AddString(_T("COM1"));
           m_combo_comport_list.AddString(_T("COM2"));
           m_combo_comport_list.AddString(_T("COM3"));
           m_combo_comport_list.AddString(_T("COM4"));
 
           m_combo_baudrate_list.AddString(_T("9600"));
           m_combo_baudrate_list.AddString(_T("19200"));
           m_combo_baudrate_list.AddString(_T("115200"));

	 comport_state=false;
       GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
       m_str_comport = _T("COM2");
       m_str_baudrate = _T("9600");
       UpdateData(FALSE); 

	
	
	
	 
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CserialDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CserialDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CserialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CserialDlg::OnBnClickedBtConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(comport_state)
         {
                  if(m_comm)        //컴포트가존재하면
                  {
                           m_comm->Close();
                           m_comm = NULL;
                           AfxMessageBox(_T("COM 포트닫힘"));
                           comport_state=false;
                           GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
                           GetDlgItem(IDC_BT_SEND)->EnableWindow(false);
                  }
         }
         else
         {
                  m_comm= new CMycomm(_T("\\\\.\\")+m_str_comport,m_str_baudrate,_T("None"),_T("8 Bit"),_T("1 Bit"));         // initial Comm port
                  if(      m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
                  {
                           AfxMessageBox(_T("COM 포트열림"));
                           comport_state=true;
                           GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("CLOSE"));
                           GetDlgItem(IDC_BT_SEND)->EnableWindow(true);
                  }
                  else
                  {
                           AfxMessageBox(_T("ERROR!"));
                  }
 
         }
}

void CserialDlg::OnCbnSelchangeComboComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}

void CserialDlg::OnBnClickedBtClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	 GetDlgItem(IDC_EDIT_RCV_VIEW)->SetWindowText(_T(" "));
}

void CserialDlg::OnBnClickedBtSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
CString str;
        GetDlgItem(IDC_EDIT_SEND_DATA)->GetWindowText(str);
        str+= "\r\n";
        m_comm->Send(str,str.GetLength());
}
