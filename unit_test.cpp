// check_func_signature.cpp : Defines the entry point for the console application.
// Extracting C / C++ function prototypes
// https://stackoverflow.com/questions/1570917/extracting-c-c-function-prototypes

#include "stdafx.h"

#include "unit_test.h"
#include "check_func_signature.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#include <fstream>   
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>

#include <iterator>


int test_preproc_cleaner(void){
	string outStr;
    outStr = remove_preproc ("");
	return 1;
}




int test_func_name_extractor(void){
	int ret = 0;
	string funcName;
	ret = func_name_extractor ("int func_name (int a, int b)", &funcName);
	
	if(funcName!="func_name"){
		return UT_FUNC_NAME_SEPARATOR_ERROR;
	}
	ret = func_name_extractor ("int func_name1  (int a )", &funcName);
	
	if(funcName!="func_name1"){
		return UT_FUNC_NAME_SEPARATOR_ERROR;
	}
	
	return UT_FINE;
}

int run_unit_tests(void) {
	int ret=0;
	ret = test_func_name_extractor();
	if(ret){
		return ret;
	}
    return 0;
}