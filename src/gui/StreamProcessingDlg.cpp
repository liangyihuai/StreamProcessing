
// StreamProcessingDlg.cpp : implementation file
//

#include "../stdafx.h"
#include "StreamProcessing.h"
#include "StreamProcessingDlg.h"
#include "afxdialogex.h"

//#include "ExecuteScheduler.h"
#include "../util/SpecUtils.h"
#include <thread>
#include "ThreadOfInputStreamPrint.h"
#include "../execution/ExecuteScheduler.h"

#include <future>
#include "../spec/SpecRegister.h"
#include "../execution/ProcessRegister.h"
#include "MultiThreads.h"
#include "RuleRegisterUtils.h"
#include "MovingObjectDrawing.h"
#include "../test/performanceTest/DataSample1.h"
#include "../test/performanceTest/SampleEventGenerator.h"


//#include "../test/performanceTest/DataSample1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString CStreamProcessingDlg::inputstream_to_display;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStreamProcessingDlg dialog



CStreamProcessingDlg::CStreamProcessingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STREAMPROCESSING_DIALOG, pParent)
	, outputStreamNameForSearch(_T(""))
	, editBoxOfRule(_T(""))
	, outputStreamForUpdate(_T("")){

	//initialize name and value
	event_filter_rule = _T("If not duplicate(id) & not unusual(speed)\
		\r\nFrom rawData\
		\r\nThen targetData");
	event_capture_rule = _T("If target.iff = ally\
		\r\nFrom targetData\
		\r\nThen allytarget");
	cq_rule = _T("If speed > 500 & elevation > 200\
		\r\nFrom allytarget\
		\r\nThen flyingAllyTarget");
	cep_rule = _T("If exist(flyingAllyTarget)\
		\r\nFrom flyingAllyTarget\
		\r\nThen cepTarget1");

	//launch a console
	FILE* fp = NULL;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	cout << "start stream processing..." << endl;


	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CStreamProcessingDlg::~CStreamProcessingDlg() {
	delete threadOfInputStream;
}

void CStreamProcessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_EVENT_FILTER_RULE, event_filter_rule);
	DDX_Text(pDX, IDC_EDIT_CAPTURE_RULE, event_capture_rule);
	DDX_Text(pDX, IDC_EDIT_CQ_RULE, cq_rule);
	DDX_Text(pDX, IDC_EDIT_CEP_RULE, cep_rule);
	DDX_Text(pDX, IDC_EDIT_OUTSTREAM_NAME_SEARCH, outputStreamNameForSearch);
	DDX_Text(pDX, IDC_EDIT1, editBoxOfRule);
	DDX_Text(pDX, IDC_EDIT_OUTSTREAM_UPDATE, outputStreamForUpdate);
}

BEGIN_MESSAGE_MAP(CStreamProcessingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_CEP_RULE, &CStreamProcessingDlg::OnEnChangeEditCepRule)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_FILTER_ADD, &CStreamProcessingDlg::OnBnClickedButtonEventFilterAdd)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_ADD, &CStreamProcessingDlg::OnBnClickedButtonCaptureAdd)
	ON_BN_CLICKED(IDC_BUTTON_CQ_ADD, &CStreamProcessingDlg::OnBnClickedButtonCqAdd)
	ON_BN_CLICKED(IDC_BUTTON_CEP_ADD, &CStreamProcessingDlg::OnBnClickedButtonCepAdd)
	ON_BN_CLICKED(IDC_BUTTON_START, &CStreamProcessingDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CStreamProcessingDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_STREAM, &CStreamProcessingDlg::OnBnClickedButtonInputStream)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CStreamProcessingDlg::OnBnClickedButtonSearch)
	ON_EN_CHANGE(IDC_INPUT_STREAM, &CStreamProcessingDlg::OnEnChangeInputStream)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY_ALL_RULE, &CStreamProcessingDlg::OnBnClickedButtonDisplayAllRule)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_RULE, &CStreamProcessingDlg::OnBnClickedButtonDeleteRule)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_RULE, &CStreamProcessingDlg::OnBnClickedButtonUpdateRule)
	ON_BN_CLICKED(IDC_BUTTON1, &CStreamProcessingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_RefeshRule, &CStreamProcessingDlg::OnBnClickedButtonRefeshrule)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_MOVING_OBJ, &CStreamProcessingDlg::OnBnClickedButtonShowMovingObj)
END_MESSAGE_MAP()


// CStreamProcessingDlg message handlers

BOOL CStreamProcessingDlg::OnInitDialog(){

	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr){
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()){
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStreamProcessingDlg::OnSysCommand(UINT nID, LPARAM lParam){
	if ((nID & 0xFFF0) == IDM_ABOUTBOX){
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}else{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStreamProcessingDlg::OnPaint(){
	//gui::ProcessFlowDrawing drawing(this);

	
	if (this->startToDrawSampleData1) {
	/*	SampleEventGenerator sampleGenerator;
		vector<EventPtr> events = sampleGenerator.generateSampleEvent1();
		stringstream ss;
		for (EventPtr e : events) {
			ss << e->toString() << "\n";
			cout << "" << *e << "\\n\\" << endl;
		}
		string sample = ss.str();*/
		MovingObjDrawing drawing(this, sample1);
		drawing.doDraw();
	}

	if (IsIconic()){
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}else{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStreamProcessingDlg::OnQueryDragIcon(){
	return static_cast<HCURSOR>(m_hIcon);
}

void CStreamProcessingDlg::OnEnChangeEditCepRule(){
}


//add rule of event filter
void CStreamProcessingDlg::OnBnClickedButtonEventFilterAdd() {
	UpdateData(true);

	if (event_filter_rule.GetLength() == 0) {
		MessageBox(_T("fill the rule"), NULL, MB_OK);
		return;
	}
	string specLines;
	RuleRegisterUtils::specProcessWithCString(event_filter_rule, specLines);
	RuleRegisterUtils::registerEventFilter(specLines);

	MessageBox(_T("Add Event Filter rule successfully"), NULL, MB_OK);
}

//add rule specification of event capture
void CStreamProcessingDlg::OnBnClickedButtonCaptureAdd(){
	UpdateData(true);

	if (event_capture_rule.GetLength() == 0) {
		MessageBox(_T("fill the rule"), NULL, MB_OK);
		return;
	}

	string outputName;
	string ruleStrs;
	RuleRegisterUtils::specProcessWithCString(event_capture_rule, ruleStrs);
	RuleRegisterUtils::registerEventCapture(ruleStrs);

	MessageBox(_T("Add Event Capture rule successfully"), NULL, MB_OK);

	event_capture_rule = _T("");
	UpdateData(false);
}

//add rule specification of CQ
void CStreamProcessingDlg::OnBnClickedButtonCqAdd()
{
	UpdateData(true);

	if (cq_rule.GetLength() == 0) {
		MessageBox(_T("fill the rule"), NULL, MB_OK);
		return;
	}

	string outputName;
	string ruleStrs;
	RuleRegisterUtils::specProcessWithCString(cq_rule, ruleStrs);
	RuleRegisterUtils::registerCQ(ruleStrs);

	MessageBox(_T("Add CQ rule successfully"), NULL, MB_OK);
	cq_rule = _T("");
	UpdateData(false);
}


//add rule specification of CEP
void CStreamProcessingDlg::OnBnClickedButtonCepAdd()
{
	UpdateData(true);

	if (cep_rule.GetLength() == 0) {
		MessageBox(_T("fill the rule"), NULL, MB_OK);
		return;
	}

	string outputName;
	string ruleStrs;
	RuleRegisterUtils::specProcessWithCString(cep_rule, ruleStrs);
	RuleRegisterUtils::registerCEP(ruleStrs);

	MessageBox(_T("Add CEP rule successfully"), NULL, MB_OK);
	cep_rule = _T("");
	UpdateData(false);
}

bool isStarted = false;
ThreadOfEventFilter *threadOfEventFilter = nullptr;//thread to run stream processing

void CStreamProcessingDlg::OnBnClickedButtonStart(){
	if (!isStarted) {
		//thread for event filtering.
		threadOfEventFilter = new ThreadOfEventFilter();
		threadOfEventFilter->runThread().detach();

		ExecuteScheduler::initialize();
		
		//thread for EventCapture, CQ and CEP.
		ThreadOfProcessUnit * threadOfProcessUnit = new ThreadOfProcessUnit();
		threadOfProcessUnit->runThread().detach();

		//thread for getting the results of CEP.
		//ThreadOfTimerToPerformCEP * threadOfTimerToPerformCEP = new ThreadOfTimerToPerformCEP();
		//threadOfTimerToPerformCEP->runThread().detach();

		isStarted = true;
	}else {
		MessageBox(_T("The processing has already started."), NULL, MB_OK);
	}
}


void CStreamProcessingDlg::OnBnClickedButtonStop(){
	if (isStarted) {
		threadOfEventFilter->stop();
		isStarted = false;
		delete threadOfEventFilter;
		threadOfEventFilter = nullptr;
	}
}

int length = 0;//store the history length of "inputstream_to_display"
void CStreamProcessingDlg::updataPrintInputStream() {
	if (length != inputstream_to_display.GetLength()) {
		//change the content of edit control
		GetDlgItem(IDC_INPUT_STREAM)->SetWindowText(inputstream_to_display);
		length = inputstream_to_display.GetLength();
	}
}


//button for displaying input stream
void CStreamProcessingDlg::OnBnClickedButtonInputStream(){
	if (threadOfInputStream == nullptr) {
		//start a new thread
		threadOfInputStream = AfxBeginThread(ThreadOfInputStreamPrint::runThread, this);
	}
}


void CStreamProcessingDlg::OnBnClickedButtonSearch(){
	// TODO: Add your control notification handler code here
	UpdateData(true);
	string outputStreamName(CW2A(outputStreamNameForSearch.GetString()));
	outputStreamName = Utils::toLower(outputStreamName);
	string ruleSpecification = SpecRegister::query(outputStreamName);

	CString cRule(ruleSpecification.c_str());
	editBoxOfRule = cRule;
	outputStreamForUpdate = outputStreamNameForSearch;
	UpdateData(false);
}


void CStreamProcessingDlg::OnEnChangeInputStream(){
}


void CStreamProcessingDlg::OnBnClickedButtonDisplayAllRule(){
	stringstream ss;
	list<string> allSpecs = SpecRegister::queryAll();
	
	auto iter = allSpecs.begin();
	for (; iter != allSpecs.end(); iter++) {
		string outputStreamName = *iter;
		iter++;
		string rule = *iter;
		ss << rule << "\r\n\r\n" 
			<< "output stream: " <<outputStreamName 
			<< "\r\n--------------------------------\r\n";
	}
	CString cRules(ss.str().c_str());
	editBoxOfRule = cRules;
	UpdateData(false);
}


void CStreamProcessingDlg::OnBnClickedButtonDeleteRule(){
	UpdateData(true);
	string outputStreamName(CW2A(outputStreamNameForSearch.GetString()));
	outputStreamName = Utils::toLower(outputStreamName);

	bool delete_result = SpecRegister::delete_rule(outputStreamName);
	if (delete_result) {
		ProcessRegister::removeProcess(outputStreamName);
		MessageBox(_T("delete successfully"), NULL, MB_OK);
	}else {
		MessageBox(_T("no such rule specification."), NULL, MB_OK);
	}
	editBoxOfRule = _T("");
	outputStreamNameForSearch = _T("");
	UpdateData(false);
}


void CStreamProcessingDlg::OnBnClickedButtonUpdateRule(){
	UpdateData(true);
	string outputStreamName(CW2A(outputStreamNameForSearch.GetString()));
	outputStreamName = Utils::toLower(outputStreamName);
	
	//delete history
	bool delete_result = SpecRegister::delete_rule(outputStreamName);
	if (delete_result) {
		Process * process = ProcessRegister::getProcess(outputStreamName);
		int processType = 0;//1:event capture, 2:cq, 3:cep
		if (EventCapture * ec = dynamic_cast<EventCapture*>(process)) {
			processType = 1;
		}else if (CQProcess * cq = dynamic_cast<CQProcess*>(process)) {
			processType = 2;
		}else if (CEPProcess * cep = dynamic_cast<CEPProcess*>(process)) {
			processType = 3;
		}
		ProcessRegister::removeProcess(outputStreamName);

		string outputName;
		string ruleStrs;
		RuleRegisterUtils::specProcessWithCString(editBoxOfRule, ruleStrs);

		if (processType == 1) {
			RuleRegisterUtils::registerEventCapture(ruleStrs);
		}
		else if (processType == 2) {
			RuleRegisterUtils::registerCQ(ruleStrs);
		}
		else if (processType == 3) {
			RuleRegisterUtils::registerCEP(ruleStrs);
		}
		
		outputStreamNameForSearch = outputStreamForUpdate;
		UpdateData(false);

		MessageBox(_T("update successfully"), NULL, MB_OK);
	}else {
		MessageBox(_T("no such name of output stream."), NULL, MB_OK);
	}
}


void CStreamProcessingDlg::OnBnClickedButton1(){
	// TODO: Add your control notification handler code here
}


void CStreamProcessingDlg::OnBnClickedButtonRefeshrule(){
	ExecuteScheduler::rebuildGraph();
	MessageBox(_T("Refresh all rules successfully"), NULL, MB_OK);
}


void CStreamProcessingDlg::OnBnClickedButtonShowMovingObj(){
	this->startToDrawSampleData1 = true;
	Invalidate();
	UpdateWindow();

}
