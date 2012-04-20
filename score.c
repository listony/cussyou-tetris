/* score.c -- by lizhonglei 2008-05-24 */

#include "score.h"
void s_init(struct score* s,char* name)
{
        strcpy(s->name,name);
		s->lines=0;
}
char* s_getname(struct score* s)
{
        return s->name;
}
int s_getscore(struct score* s)
{
        return s->lines;
}
void s_addscore(struct score* s,int l)
{
        s->lines=s->lines+l;
}

