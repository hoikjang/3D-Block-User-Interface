
// serialDlg.h : ��� ����
//
#if !defined(AFX_VTK_MFCDLG_H__25D243A6_EEAC_4D74_9044_B13EF7E1CB33__INCLUDED_)
#define AFX_VTK_MFCDLG_H__25D243A6_EEAC_4D74_9044_B13EF7E1CB33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "afxwin.h"
#include "Mycomm.h"

// CserialDlg ��ȭ ����
class CserialDlg : public CDialog
{
// �����Դϴ�.
public:
	CMycomm* m_comm;
       LRESULT      OnThreadClosed(WPARAM length, LPARAM lpara);
       LRESULT      OnReceive(WPARAM length, LPARAM lpara);
	CserialDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

  
  
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SERIAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnZoomout();
	afx_msg void OnZoomin();
	afx_msg void OnBabout();
	DECLARE_MESSAGE_MAP()
	void BaseOnOff(int &baseid, int &baseonoff);//�߰�, ���̽� ����
public:
	BOOL comport_state;
	CComboBox m_combo_comport_list;
	CComboBox m_combo_baudrate_list;
	CString m_str_comport;
	CString m_str_baudrate;
	CEdit m_edit_rcv_view;
	CEdit m_edit_send_data;
	afx_msg void OnBnClickedBtConnect();
	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnBnClickedBtClear();
	afx_msg void OnBnClickedBtSend();
	afx_msg void OnStnClickedScreen();
	afx_msg void OnEnChangeEdit1();
};

#endif 