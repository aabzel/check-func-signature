// check_func_signature.cpp : Defines the entry point for the console application.
// Extracting C / C++ function prototypes
// https://stackoverflow.com/questions/1570917/extracting-c-c-function-prototypes

#include "pch.h"
#include "stdafx.h"
#include "check_func_signature.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <fstream>  //Для файловых потоков
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

vector<string>  functionsPrototypesListInC;

void print_list_of_functions_proto(void) {
	cout << "\n\nresult of search: " << functionsPrototypesListInC.size() << " functions: \n" << endl;
	for (int i = 0; i < functionsPrototypesListInC.size(); i++) {
		cout << functionsPrototypesListInC[i] << endl;
	}
}

void check_header(string inputFileNameH) {
	int errorCnt = 0;

	ifstream headerFileIn(inputFileNameH);
	if (headerFileIn.is_open()) {
		//cout << "file is open" << endl;
	}
	else {
		cout << "\nCan not open file " << inputFileNameH << endl;
		return;
	}

	string strHfileContent;

	headerFileIn.seekg(0, ios::end);
	strHfileContent.reserve(headerFileIn.tellg());
	headerFileIn.seekg(0, ios::beg);

	strHfileContent.assign((istreambuf_iterator<char>(headerFileIn)),
		istreambuf_iterator<char>());

	//cout << "\n\n check prototypes in header... " << endl;
	for (int i = 0; i < functionsPrototypesListInC.size(); i++) {
		//cout << functionsPrototypesListInC[i] << endl;
		if (strHfileContent.find(functionsPrototypesListInC[i]) != string::npos) {
		}
		else {
			errorCnt++;
			cout << "Error: " << errorCnt << ". file " << inputFileNameH <<
				" does not contain prototype:\n" <<
				functionsPrototypesListInC[i] << endl;
		}
	}
	//cout << "verivication done!" << endl;
	//cout << "Amount of errors: " << errorCnt << endl;
}
string  clean_fun_proto_right(string codeSnippetIn)
{
	string codeSnippetOut;
	codeSnippetOut = codeSnippetIn;
	char LastChar;
	while (1) {
		LastChar = codeSnippetOut.back();
		if (')' != LastChar) {
			codeSnippetOut.pop_back();
		}
		else {
			break;
		}
	}
	return codeSnippetOut;
}


string clean_fun_proto_left(string codeSnippetIn) {
	string codeSnippetOut;
	codeSnippetOut = codeSnippetIn;
	char firstChar = '\0';
	while (1) {
		if (1 < codeSnippetOut.size()) {
			firstChar = codeSnippetOut[0];
			if (' ' == firstChar) {
				codeSnippetOut.erase(0, 1);
			}
			else if (0x0A == firstChar) {
				codeSnippetOut.erase(0, 1);
			}
			else if (0x0D == firstChar) {
				codeSnippetOut.erase(0, 1);
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	return codeSnippetOut;
}

int is_proto(string codeSnippetIn) {
	 
    if (codeSnippetIn.find("(") != string::npos) {
		if (codeSnippetIn.find(")") != string::npos) {
			return 0;
		}
		else {
			return 2;
		}
	} else {
		return 1;
	}
	return 5;
}

string separate_func_prototype(string codeSnippetIn)
{
	string codeSnippetOut = "";
	int size = 0;
	size = codeSnippetIn.size();
	for (int i = codeSnippetIn.size() - 1; 0 <= i; i--)
	{
		if (codeSnippetIn[i] == ';') {
			break;
		}
		if (codeSnippetIn[i] == '}') {
			break;
		}
		if (codeSnippetIn[i] == '/') {
			break;
		}
		if (codeSnippetIn[i] == '"') {
			break;
		}
		codeSnippetOut = codeSnippetIn[i] + codeSnippetOut;
	}
	if (is_proto(codeSnippetOut)) {
		return "";
	}
	codeSnippetOut = clean_fun_proto_left(codeSnippetOut);
	codeSnippetOut = clean_fun_proto_right(codeSnippetOut);
	return codeSnippetOut;
}

void parse_c_file(string inputFileNameC)
{
	ifstream cFileIn(inputFileNameC);
	if (cFileIn.is_open()) {
		//cout << "file is open" << endl;
	}
	else {
		cout << "\nCan not open file " << inputFileNameC << endl;
		return;
	}

	string strCfileContent;

	cFileIn.seekg(0, ios::end);
	strCfileContent.reserve(cFileIn.tellg());
	cFileIn.seekg(0, ios::beg);

	strCfileContent.assign((istreambuf_iterator<char>(cFileIn)),
		istreambuf_iterator<char>());

	//cout << "size of " << inputFileNameC << " file: " << strCfileContent.size() << endl;

	int bracketCount = 0;
	int functionCounter = 0;
	functionsPrototypesListInC.clear();
	string codeSnippet = "";

	for (int i = 0; i < strCfileContent.size(); i++) {
		codeSnippet = codeSnippet + strCfileContent[i];
		if (strCfileContent[i] == '{') {
			bracketCount++;
			if (1 == bracketCount) {
				functionCounter++;
				//cout << "\nFunction proto catch!" << endl;
				//cout << "\n<" << codeSnippet << ">";
				codeSnippet.pop_back();
				codeSnippet = separate_func_prototype(codeSnippet);
				if (3<codeSnippet.length()) {
					//cout << "\n{" << codeSnippet << "}";
					if (codeSnippet.find("static") == string::npos) {
						functionsPrototypesListInC.push_back(codeSnippet);
					}
					codeSnippet.clear();
				}
			}
		}
		if (strCfileContent[i] == '}') {
			if (bracketCount == 0) {
				cout << "} Error!" << endl;
			}
			else if (0 < bracketCount) {
				bracketCount--;
				if (!bracketCount) {
					//cout << "\nFunction body end" << endl;
					//codeSnippet.clear();
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	string inputFileNameC;
	string inputFileNameH;
	if (argc < 3) {
		cout << "Usage: check_func_signature <input code file name> " << endl;
		// no input file provided 
		return 1;
	}
	//cout << "argv[0] " << argv[0] << endl;
	//cout << "argv[1] " << argv[1] << endl;
	//cout << "argv[2] " << argv[2] << endl;

	inputFileNameC = argv[1];
	//cout << "input File Name C: " << inputFileNameC << endl;
	inputFileNameH = argv[2];

	//inputFileNameH.replace(inputFileNameH.find(".c"), sizeof(".h") - 1, ".h");
	//cout << "input File Name H: " << inputFileNameH << endl;

	parse_c_file(inputFileNameC);
	//print_list_of_functions_proto();
	check_header(inputFileNameH);
	//getchar();
	return 0;
}

