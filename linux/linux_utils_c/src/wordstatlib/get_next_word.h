#ifndef GET_NEXT_WORD_H_
#define GET_NEXT_WORD_H_

#include <stddef.h>

/* IN/OUT curr_ptr     - current pointer
 * IN/OUT curr_pos_ptr - pointer to current position in line
 * Return value: word or NULL.
 * Return value MUST be free.
 */
char* get_next_word(const char** curr_ptr, size_t* curr_pos_ptr);

#endif // ! GET_NEXT_WORD_H_