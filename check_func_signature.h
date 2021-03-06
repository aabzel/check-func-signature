// check_func_signature.h

#ifndef CHECK_FUNC_SIGNATURE_H
#define CHECK_FUNC_SIGNATURE_H

#include <string.h>
#include <stdio.h>
#include <string>



using namespace std;

string extract_file_name(string inputFileNameH);
int check_incule_file (string inputFileNameC, string inputFileNameH );
int is_proto(string codeSnippetIn);
int check_header(string inputFileNameH);
void print_list_of_functions_proto(void);
string  clean_fun_proto_right(string codeSnippetIn);
string clean_fun_proto_left (string codeSnippetIn);
string separate_func_prototype(string codeSnippetIn);
void parse_c_file(string inputFileNameC);
int func_name_extractor (string inStr, string* outStr);
string load_file_to_string (string inputFileName);
string discard_one_line_comments(string inputFileNameC);
string remove_preproc ( string codeSnippetOut);
void findAndReplaceAll(string & data, string toSearch, string replaceStr);



#endif /* CHECK_FUNC_SIGNATURE_H */
