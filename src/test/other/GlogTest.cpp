#include "stdafx.h"

#include "glog/logging.h"

void logTest() {
	LOG(WARNING) << "warning test";
}

int main(int argc, char* argv[]){
	LOG(INFO) << "hello glog!" << "number of argc" << argc;
	LOG(INFO) << "done...";

	logTest();


	system("pause");
	return 0;
}