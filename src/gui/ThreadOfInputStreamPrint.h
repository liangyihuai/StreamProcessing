#pragma once



// ThreadOfInputStreamPrint
//this class is to update input stream in a individual thread.
//the main logic is in function "runThread"
class ThreadOfInputStreamPrint : public CWinThread
{
	DECLARE_DYNCREATE(ThreadOfInputStreamPrint)

protected:
	ThreadOfInputStreamPrint();           // protected constructor used by dynamic creation
	virtual ~ThreadOfInputStreamPrint();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	static UINT runThread(LPVOID param);
protected:
	DECLARE_MESSAGE_MAP()
};


