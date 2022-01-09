#ifndef WORDSTATLIB_WS_DICT_H_
#define WORDSTATLIB_WS_DICT_H_

#include <stddef.h>

typedef struct __ws_dict
{
  char** data;
  size_t size;
  size_t capacity;
} ws_dict;

void ws_dict_init(ws_dict* ws_dict_ptr);
void ws_dict_release(ws_dict* ws_dict_ptr);

// Return Value: 0 - success
int ws_dict_load_from_file(ws_dict* ws_dict_ptr, const char* filename);


int ws_dict_check_word(const ws_dict* ws_dict_ptr,
                       const char* word);

void ws_dict_check_line(const ws_dict* ws_dict_ptr,
                        const char* line,
                        size_t curr_line_num);

/* spellcheck procedure
 * parameters:
 * IN     ws_dict_ptr       - pointer to dictionary
 * IN     line              - current line
 * IN/OUT curr_len_ptr      - pointer to current pos in line
 *                            in the 1st call it MUST be pointer to line
 * IN/OUT word_buff_ptr     - pointer to word buffer
 *                            in the 1st call it MUsT be NULL
 *                            after the last call memory MUST be free
 * IN/OUT word_buff_size_ptr - pointer to size of word_buff
 * OUT    eol                - end of line
 */
int ws_dict_spellcheck(const ws_dict* ws_dict_ptr,
                       const char** curr_len_ptr,
                       char** word_buff_ptr,
                       size_t* word_buff_size_ptr,
                       int* eol);


#endif // ! WORDSTATLIB_WS_DICT_H_
