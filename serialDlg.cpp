
// serialDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "serial.h"
#include "serialDlg.h"
#include "vtkMath.h"
#include <stdlib.h>
#include "header.h"



int countnum=0;
int num=0;
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

////////////////////////////// 구현부
LRESULT CserialDlg::OnReceive(WPARAM length, LPARAM lpara)
{
        CString str;
		char data[10000] = {0}; 
		
		if(m_comm)
		{       
			m_comm->Receive(data,length); //length 길이만큼데이터를받는다.//여기서 문제..
            //data[100] = '\0';
			/*
			for(int i = 0;data[i];++i)
            {
                       str += data[i];	
		    }
			*/
			str=(LPSTR)data;
		    Sleep(100);
			//////////////////////// 문자열에서 데이터 추출
			variables.boxdata.DataExtract(str);
			////////////////////////////////////에디트박스에표시하기위함
			m_edit_rcv_view.ReplaceSel(str);
			m_edit_rcv_view.LineScroll(m_edit_rcv_view.GetLineCount());
			///////////////////////////////////////박스 데이터 분배
		
			variables.boxdata.seteventonoff(false);
			num=variables.boxdata.boxdata.size()-variables.boxdata.blocknum;
			if((num>0)&&(num<3))
			{
			variables.boxdata.BoxTreeMake(num);
			BaseOnOff(baseid,baseonoff);
			baseid=0;
			baseonoff=0;
			}
			else if(num>2)
		    variables.boxdata.EraseBox(num);
	        
		   
		    /////////////////////// 렌더링
			//variables.boxrenderer.BaseGroupNumber();
			variables.boxrenderer.Renderer();
			
		

        }//m_comm
		

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
	       m_combo_comport_list.AddString(_T("COM3"));
	       m_combo_comport_list.AddString(_T("COM45"));
           m_combo_comport_list.AddString(_T("COM46"));
           m_combo_comport_list.AddString(_T("COM49"));
           m_combo_comport_list.AddString(_T("COM50"));


           m_combo_baudrate_list.AddString(_T("4800"));
           m_combo_baudrate_list.AddString(_T("9600"));
           m_combo_baudrate_list.AddString(_T("19200"));
		   m_combo_baudrate_list.AddString(_T("38400"));
           m_combo_baudrate_list.AddString(_T("115200"));

	 comport_state=false;
       GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
       m_str_comport = _T("COM3");
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
void CserialDlg::BaseOnOff(int &baseid, int &baseonoff)
{
	if(baseid>0)
	{
	CString str;
	if(baseonoff==1)
	{
	switch(baseid)
	{
	case 1:
		str="QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ";
		break;
	case 2:
		str="EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
		break;
	case 3:
		str="TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT";
		break;
	case 4:
		str="UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
		break;
	case 5:
		str="OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
		break;
	}
	}
	else
	{
    switch(baseid)
	{
	case 1:
		str="WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
		break;
	case 2:
		str="RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR";
		break;
	case 3:
		str="YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY";
		break;
	case 4:
		str="IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII";
		break;
	case 5:
		str="PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP";
		break;
	}
	}
	for(int i=0; i<5; i++)
	m_comm->Send(str,str.GetLength());
	}
}