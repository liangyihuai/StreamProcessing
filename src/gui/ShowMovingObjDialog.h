#pragma once


// ShowMovingObjDialog dialog

class ShowMovingObjDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ShowMovingObjDialog)

public:
	ShowMovingObjDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ShowMovingObjDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOW_OBJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};


