//
// Created by USER on 12/4/2018.
//
#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <stdexcept>


using namespace std;

void function() {
	
    throw runtime_error("i am an exception");
}

void test(){
    function();
}


