// ShowMovingObjDialog.cpp : implementation file
//

#include "../stdafx.h"
#include "../resource.h"
#include "ShowMovingObjDialog.h"
#include "afxdialogex.h"


// ShowMovingObjDialog dialog

IMPLEMENT_DYNAMIC(ShowMovingObjDialog, CDialogEx)

ShowMovingObjDialog::ShowMovingObjDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SHOW_OBJ, pParent){

	//new gui::MovingObjDrawing(this);
}

ShowMovingObjDialog::~ShowMovingObjDialog()
{
}

void ShowMovingObjDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShowMovingObjDialog, CDialogEx)
END_MESSAGE_MAP()


// ShowMovingObjDialog message handlers
