#include "../stdafx.h"

#include "MultiThreads.h"

#include "../execution/ProcessRegister.h"
#include "StreamProcessingDlg.h"
#include "../execution/ExecuteScheduler.h"

////////////////////////////////////////////////
ThreadOfEventFilter::ThreadOfEventFilter(bool isWithGUI) {
	this->isWithGUI = isWithGUI;
}

void ThreadOfEventFilter::run() {
	EventProcess * eventProcess = ProcessRegister::getProcessOfEventFiltering();
	EventPtr e;
	while (!isStop) {
		Sleep(900);
		//generate "movingObject_id_total_numble" events.
		for (int i = 0; i < Utils::movingObject_id_total_numble; i++) {
			e = EventGenerator::generateEvent();
			eventProcess->process(e);
		}
		//update the variable of "inputstream_to_display"
		CString cstr(e->toString().c_str());
		if (isWithGUI) {
			CStreamProcessingDlg::inputstream_to_display = cstr + "\r\n" + CStreamProcessingDlg::inputstream_to_display;
			if (CStreamProcessingDlg::inputstream_to_display.GetLength() > 5000)
				CStreamProcessingDlg::inputstream_to_display.Truncate(3000);
		}
	}
}

std::thread ThreadOfEventFilter::runThread() {
	return std::thread(&ThreadOfEventFilter::run, this);
}

void ThreadOfEventFilter::stop() {
	this->isStop = true;
}

/////////////////////////////////////////////////////


void ThreadOfProcessUnit::run() {
	ExecuteScheduler::runProcessQueue();
}

std::thread ThreadOfProcessUnit::runThread() {
	return std::thread(&ThreadOfProcessUnit::run, this);
}

///////////////////////////////////////////////////////


