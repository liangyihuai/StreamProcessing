//
// Created by USER on 12/4/2018.
//

#include "stdafx.h"

#include <iostream>
#include "QueueReader.h"
#include "Utils.h"
#include "HashEvent.h"


using namespace std;

int main() {
	//     setup
	//1. set reader Id from 0.
	//2. set writer for each reader
	//3. set reader num for writer
	QueueWriter wr;

	QueueReader r1;
	QueueReader r2;
	r1.setWriter(&wr);
	r2.setWriter(&wr);

	QueueReader r3;
	r3.setWriter(&wr);

	Queue* reader1 = &r1;
	Queue* reader2 = &r2;
	Queue* reader3 = &r3;

	Queue* writer = &wr;

	EventPtr e1(new HashEvent(1, "test", Utils::getTime()));
	EventPtr e2(new HashEvent(2, "test", Utils::getTime()));
	EventPtr e3(new HashEvent(3, "test", Utils::getTime()));
	EventPtr e4(new HashEvent(4, "test", Utils::getTime()));
	EventPtr e5(new HashEvent(5, "test", Utils::getTime()));
	EventPtr e6(new HashEvent(6, "test", Utils::getTime()));
	EventPtr e7(new HashEvent(7, "test", Utils::getTime()));
	EventPtr e8(new HashEvent(8, "test", Utils::getTime()));
	EventPtr e9(new HashEvent(9, "test", Utils::getTime()));

	writer->enqueue(e1);
	writer->enqueue(e2);
	writer->enqueue(e3);

	while (!reader1->isEmpty()) {
		EventPtr result = reader1->dequeue();
		cout <<"reader 1 , "<<  *result << endl;
	}

	while (!reader2->isEmpty()) {
		cout << "reader 2, writer size: " << writer->size() << ", ";
		cout << "peek = " << reader2->peek()->getId() << ", ";
		EventPtr result = reader2->dequeue();
		cout << *result << endl;
	}

	writer->enqueue(e4);

	while (!reader2->isEmpty()) {
		cout << "reader 2, writer size: " << writer->size() << ", ";
		EventPtr result = reader2->dequeue();
		cout << *result << endl;
	}

	writer->enqueue(e5);

	while (!reader1->isEmpty()) {
		cout << "reader 1, writer size: " << writer->size() << ", ";
		EventPtr result = reader1->dequeue();
		cout << *result << endl;
	}
	writer->enqueue(e6);

	while (!reader1->isEmpty()) {
		cout << "reader 1, writer size: " << writer->size() << ", ";
		EventPtr result = reader1->dequeue();
		cout << *result << endl;
	}

	while (!reader2->isEmpty()) {
		cout << "reader 2, writer size: " << writer->size() << ", ";
		cout << "peek = " << reader2->peek()->getId() << ", ";
		EventPtr result = reader2->dequeue();
		cout << *result << endl;
	}

	cout << endl;
	while (!reader3->isEmpty()) {
		cout << "reader 3, writer size: " << writer->size() << ", ";
		cout << "peek = " << reader3->peek()->getId() << ", ";
		EventPtr result = reader3->dequeue();
		cout << *result << endl;
	}

	while (!writer->isFull()) {
		writer->enqueue(e3);
	}

	cout << endl;
	while (!reader1->isEmpty()) {
		cout << "reader 1, writer size: " << writer->size() << ", ";
		cout << "peek = " << reader1->peek()->getId() << ", ";
		EventPtr result = reader1->dequeue();
		cout << *result << endl;
	}

	cout << endl;
	while (!reader2->isEmpty()) {
		cout << "reader 2, writer size: " << writer->size() << ", ";
		cout << "peek = " << reader2->peek()->getId() << ", ";
		EventPtr result = reader2->dequeue();
		cout << *result << endl;
	}


	cout << endl;
	while (!reader3->isEmpty()) {
		cout << "reader 3, writer size: " << writer->size() << ", ";
		cout << "peek = " << reader3->peek()->getId() << ", ";
		EventPtr result = reader3->dequeue();
		cout << *result << endl;
	}



	system("pause");

	return 0;
}

