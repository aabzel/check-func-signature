// check_func_signature.h

#ifndef CHECK_FUNC_SIGNATURE_H
#define CHECK_FUNC_SIGNATURE_H

#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

void print_list_of_functions_proto(void);
void check_header(string inputFileNameH);
string  clean_fun_proto_right(string codeSnippetIn);
string clean_fun_proto_left (string codeSnippetIn);
string separate_func_prototype(string codeSnippetIn);
void parse_c_file(string inputFileNameC);
int main(int argc, char *argv[]);

#endif /* CHECK_FUNC_SIGNATURE_H */
