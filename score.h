/* score.h -- by lizhonglei 2008-05-24 */

#ifndef _SCORE_H
#define _SCORE_H

struct score{
        char name[256]; // player's name
        int lines; //score
};
void s_init(struct score* s,char* name);
char* s_getname(struct score* s);
int s_getscore(struct score* s);
void s_addscore(struct score* s,int l);
#endif
