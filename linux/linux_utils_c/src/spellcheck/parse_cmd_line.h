#ifndef PARSE_CMD_LINE_H_
#define PARSE_CMD_LINE_H_

/* Run example:
 * ./spellcheck_s --dict-file /usr/share/dict/american-english file1.txt
 * Return Value: 0 - success
 */
int parse_cmd_line(int argc,
                   char* argv[],
                   char** dict_filename_ptr,
                   char **filename_ptr);

#endif // ! PARSE_CMD_LINE_H_