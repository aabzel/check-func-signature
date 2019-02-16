// check_func_signature.h

#ifndef CHECK_FUNC_SIGNATURE_H
#define CHECK_FUNC_SIGNATURE_H

#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

#define CHAR_MAIN  4	/* number of characters in the function name, 'main' */

#define INIT_ARR  800	/* initial array size */
#define MULT_ARR   2	/* multiplication factor to increase array size */
#define COM_CHAR   2	/* characters required to initiate a comment */

#define COM_SINGLE 1	/* flag for a single line comment */
#define COM_MULTI  2	/* flag for a multi-line comment */

#define END	   1	/* return value for a function */

void skip_past_char(FILE *is, char c);
void mem_check(void *arr);
FILE *parse_comments(FILE *is, int c_type);
void parse_src_file(FILE *is);
void print_list_of_functions_proto(void);
bool check_word(string filename, string search);
void check_header(string inputFileNameH );
void parse(FILE *is);
FILE *skip_past_newline(FILE *is);
void parse_line(char *line);
int skip_past_whitespace(char *c_arr, int i);
char *check_alloc(char *items, int c_size, int *max_size);
int check_end_array(char *items, int pos);

#endif /* CHECK_FUNC_SIGNATURE_H */
