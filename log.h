/* log.h -- by lizhonglei 2008-05-24 */

#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
/*
  0 don't print
  1 error
  2 warning
  3 info
  4
 */

struct log{
        FILE* fout;
        int level;
};
int l_init(struct log *l,char* file);
void l_info(struct log* l,char* str);
void l_warning(struct log* l,char* str);
void l_error(struct log* l,char* str);
void l_close(struct log* l);
#endif
