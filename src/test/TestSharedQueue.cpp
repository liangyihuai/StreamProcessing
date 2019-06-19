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
    QueueWriter writer;
   

    QueueReader reader1;
    QueueReader reader2;

    reader1.setWriter(&writer);
    reader2.setWriter(&writer);
   


    EventPtr e1(new HashEvent(1, "test", Utils::getTime()));
    EventPtr e2(new HashEvent(2, "test", Utils::getTime()));
    EventPtr e3(new HashEvent(3, "test", Utils::getTime()));
    EventPtr e4(new HashEvent(4, "test", Utils::getTime()));
    EventPtr e5(new HashEvent(5, "test", Utils::getTime()));
    EventPtr e6(new HashEvent(6, "test", Utils::getTime()));
    EventPtr e7(new HashEvent(7, "test", Utils::getTime()));
    EventPtr e8(new HashEvent(8, "test", Utils::getTime()));
    EventPtr e9(new HashEvent(9, "test", Utils::getTime()));

    writer.enqueue(e1);
    writer.enqueue(e2);
    writer.enqueue(e3);

    cout << "reader 1"<< endl;
    while(!reader1.isEmpty()) {
        EventPtr result = reader1.dequeue();
        cout << *result << endl;
    }

    cout << "reader 2"<< endl;
    while(!reader2.isEmpty()) {
        cout <<"writer size: " << writer.size() << endl;
        EventPtr result = reader2.dequeue();
        cout << *result << endl;
    }


    writer.enqueue(e4);

    cout << "reader 2"<< endl;
    while(!reader2.isEmpty()) {
        cout <<"writer size: " << writer.size() << endl;
        EventPtr result = reader2.dequeue();
        cout << *result << endl;
    }

    writer.enqueue(e5);

    cout << "reader 1"<< endl;
    while(!reader1.isEmpty()) {
        cout <<"writer size: " << writer.size() << endl;
        EventPtr result = reader1.dequeue();
        cout << *result << endl;
    }
    writer.enqueue(e6);

    cout << "reader 1"<< endl;
    while(!reader1.isEmpty()) {
        cout <<"writer size: " << writer.size() << endl;
        EventPtr result = reader1.dequeue();
        cout << *result << endl;
    }

    cout << "reader 2"<< endl;
    while(!reader2.isEmpty()) {
        cout <<"writer size: " << writer.size() << endl;
        EventPtr result = reader2.dequeue();
        cout << *result << endl;
    }

	system("pause");

    return 0;
}

