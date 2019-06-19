//
// Created by USER on 12/4/2018.
//
#include "stdafx.h"

#include <unordered_set>
#include <cassert>
#include "EventProcess.h"
#include "HashEvent.h"

using namespace std;


int main() {

    HashEvent* he = new HashEvent(1, "test", Utils::getTime());
    he->addAttr("speed", (float)Utils::randomFloat(100, 800));
    EventPtr e(he);

    HashEvent* he2 = new HashEvent(1, "test", Utils::getTime());
    he2->addAttr("speed", (float)Utils::randomFloat(100, 800));
    EventPtr e2(he2);

    HashEvent* he3 = new HashEvent(2, "test", Utils::getTime());
    he3->addAttr("speed", (float)Utils::randomFloat(100, 800));
    EventPtr e3(he3);

    HashEvent* he4 = new HashEvent(2, "test", Utils::getTime());
    he4->addAttr("speed", (float)Utils::randomFloat(100, 800));
    EventPtr e4(he4);

    HashEvent* he5 = new HashEvent(3, "test", Utils::getTime());
    he5->addAttr("speed", "");
    EventPtr e5(he5);

    HashEvent* he6 = new HashEvent(3, "test", Utils::getTime());
    he6->addAttr("speed", (float)Utils::randomFloat(100, 800));
    EventPtr e6(he6);

    EventProcess * ep = new EventProcess();
    ep->setDeduplicationField("id");
    ep->addUnusualName("speed");

    if (ep->filter(e)) cout << "yes" << endl;
    if (!ep->filter(e2)) cout << "yes2" << endl;
    if (ep->filter(e3)) cout << "yes3" << endl;
    if (!ep->filter(e4)) cout << "yes4" << endl;
    if (!ep->filter(e5)) cout << "yes5" << endl;
    if (ep->filter(e6)) cout << "yes6" << endl;


    system("pause");
    return 0;
}