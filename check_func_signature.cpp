/* check_func_signature.cpp : Defines the entry point for the console application.
 Extracting C / C++ function prototypes
 https://stackoverflow.com/questions/1570917/extracting-c-c-function-prototypes
*/


#include "stdafx.h"
#include "unit_test.h"
#include "preprocSettings.h"
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

vector<string>  functionsPrototypesListInC;


string remove_preproc ( string codeSnippetOut) {
	//return codeSnippetOut;
	string result;
	string strT = codeSnippetOut;
	string inputFileNameCLackComments = codeSnippetOut;
	regex  pattern("(#([^\r\n]*))");
	smatch matches;
    while(regex_search(strT, matches, pattern)) {
		    if(matches.size()) {
				findAndReplaceAll(inputFileNameCLackComments, matches.str(0), "");
		    }
			strT = matches.suffix().str();
	}
    return inputFileNameCLackComments;
}

string discard_one_line_comments(string inputFileNameC)
{
	string result;
	string strT = inputFileNameC;
	string inputFileNameCLackComments = inputFileNameC;
	regex  pattern("(\/{2}([^\r\n]*))");
	smatch matches;
    while(regex_search(strT, matches, pattern)) {
		    if(matches.size()) {
				findAndReplaceAll(inputFileNameCLackComments, matches.str(0), "");
		    }
			strT = matches.suffix().str();
	}
    return inputFileNameCLackComments;
}


int func_name_extractor (string inStr, string* outStr)
{
    int sizeOfinStr=0;
	int writeFlag =0;
	int nameWasFlag = 0;
	string temStr="";
	sizeOfinStr = inStr.length();
	for(int i=(sizeOfinStr-1); 0<i; i--){
		if(writeFlag){
			if(inStr[i]!=' '){
				temStr=inStr[i]+temStr;
				nameWasFlag=1;
			}else{
				if(nameWasFlag){
					writeFlag=0;
				}
			}
		}
		if('('==inStr[i]){
			writeFlag=1;
		}
	}
	if(!nameWasFlag){
		return 1;
	}
#if DEPLOY_UT_DEBUG
	cout <<"\n" << inStr;
	cout <<"\n" << temStr;
#endif

	*outStr=temStr;
	return 0;
}

void print_list_of_functions_proto(void) {
	cout << "\n\nresult of search: " << functionsPrototypesListInC.size() << " functions: \n" << endl;
	for (int i = 0; i < functionsPrototypesListInC.size(); i++) {
		cout << functionsPrototypesListInC[i] << endl;
	}
}

int check_header(string inputFileNameH) {
	//cout << "inputFileNameH "<<inputFileNameH << endl;
	string strHfileContent;
	strHfileContent = load_file_to_string (inputFileNameH);
	strHfileContent = discard_one_line_comments (strHfileContent);
	if(strHfileContent.length() < 1 ){
		return 3;
	}
	int errorCnt = 0, ret=0;
	string functionName;
	for (int i = 0; i < functionsPrototypesListInC.size(); i++) {
		//cout << functionsPrototypesListInC[i] << endl;
        ret = func_name_extractor(functionsPrototypesListInC[i], &functionName);
		//cout << "functionName "<<functionName << endl;
		if(ret){
			return 1;
		}
		if (strHfileContent.find(functionName) != string::npos) {
		}
		else {
			errorCnt++;
			cout << "Error: " << errorCnt << ". file " << inputFileNameH <<
				" does not contain prototype:\n" <<
				functionsPrototypesListInC[i] << endl;
		}
	}
	if(!errorCnt){
		cout <<"file\: " << inputFileNameH <<" prototypes fine!";
	} else {
		cout << "\nAmount of errors: " << errorCnt;
	}
	return 0;
}

string  clean_fun_proto_right (string codeSnippetIn)
{
#if DEBUG_CLEAN_FUN_PROTO_RIGHT
	cout << "\n clean_fun_proto_right " << "\n";
	cout << "\n codeSnippetIn {" << codeSnippetIn << "}\n";
#endif
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
#if DEBUG_CLEAN_FUN_PROTO_RIGHT
	cout << "\n codeSnippetOut {" << codeSnippetOut << "}\n";
#endif
	return codeSnippetOut;
}


string clean_fun_proto_left(string codeSnippetIn) {
#if DEBUG_CLEAN_FUN_PROTO_LEFT_IN
	cout << "\n clean_fun_proto_left " << "\n";
	cout << "\n codeSnippetIn [" << codeSnippetIn << "]\n";
#endif
	string codeSnippetOut;
	codeSnippetOut = codeSnippetIn;
	codeSnippetOut = remove_preproc(codeSnippetOut);
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
	codeSnippetOut = remove_preproc(codeSnippetOut);
#if DEBUG_CLEAN_FUN_PROTO_LEFT_OUT
	cout << "\n codeSnippetOut [" << codeSnippetOut << "]\n";
#endif
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
#if DEBUG_SEP_FUN_PROTO_IN
	cout << "\n clean_fun_proto_left " << "\n";
	cout << "\n codeSnippetIn <" << codeSnippetIn << ">\n";
#endif
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
#if DEBUG_SEP_FUN_PROTO_IN
	cout << "\n codeSnippetOut <" << codeSnippetOut << ">\n";
#endif
	return codeSnippetOut;
}

void findAndReplaceAll(string & data, string toSearch, string replaceStr)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while( pos != std::string::npos) {
	    // Replace this occurrence of Sub String
	    data.replace(pos, toSearch.size(), replaceStr);
	    // Get the next occurrence from the current position
	    pos =data.find(toSearch, pos + toSearch.size());
    }
}


string load_file_to_string (string inputFileName) {
    ifstream cFileIn(inputFileName);
	if (cFileIn.is_open()) {
		//cout << "file is open" << endl;
	}
	else {
		cout << "\nCan not open file " << inputFileName << endl;
		return "";
	}

	string strCfileContent="";

	cFileIn.seekg(0, ios::end);
	strCfileContent.reserve(cFileIn.tellg());
	cFileIn.seekg(0, ios::beg);

	strCfileContent.assign( istreambuf_iterator<char>(cFileIn),
		                    istreambuf_iterator<char>());
	cFileIn.close();

	return strCfileContent;
}

int check_incule_file (string inputFileNameC, string inputFileNameH ){
   string cFile; 
   cFile = load_file_to_string (inputFileNameC);

   if (cFile.find(inputFileNameH) != string::npos) {
   } else {
	   cout << "Error: File " << inputFileNameC << " does not contain include for header " << inputFileNameH << endl;
	   return 1;
   }

   return 0;
}


void parse_c_file(string inputFileNameC)
{
	string strCfileContent; 
	strCfileContent = load_file_to_string (inputFileNameC);

	strCfileContent = discard_one_line_comments (strCfileContent);
	//cout << "size of " << inputFileNameC << " file: " << strCfileContent.size() << endl;

	int bracketCount = 0;
	int functionCounter = 0;
	functionsPrototypesListInC.clear();
	string codeSnippet = "";

	int cnt =0;
	int line =0;
	for (int i = 0; i < strCfileContent.size(); i++) {
		cnt++;
		codeSnippet = codeSnippet + strCfileContent[i];
		if ('\n'==strCfileContent[i] ){
			line++;
		}
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
				cout << "cnt " << cnt << endl;
				cout << "line " << line << endl;
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

	int ret= 0;
	ret = run_unit_tests();
	if(ret){
		cout << "\n Unit test error: [" << ret << "]\n";
	}
	string inputFileNameC;
	string inputFileNameH;
	if (argc < 3) {
		cout << "Usage: check_func_signature.exe file.c file.h" << endl;

		return 1;
	}
#if DEBUG_MAIN_ARGS
	cout << "argc: " << argc << endl;
	cout << "argv[0]: " << argv[0] << endl;
	cout << "argv[1]: " << argv[1] << endl;
	cout << "argv[2]: " << argv[2] << endl;
#endif
	inputFileNameC = argv[1];
	inputFileNameH = argv[2];

#if DEBUG_MAIN_ARGS
	cout << "input File Name C: " << inputFileNameC << endl;
	cout << "input File Name h: " << inputFileNameH << endl;
#endif

	ret = check_incule_file (inputFileNameC, inputFileNameH );
	if(ret){
#if DEBUG_WAIT_KEY
	    getchar();
#endif
		return ret;
	}
	parse_c_file(inputFileNameC);
#if DEBUG_RESULTS
	print_list_of_functions_proto();
#endif 
	check_header(inputFileNameH);

#if DEBUG_WAIT_KEY
	getchar();
#endif

	return 0;
}

