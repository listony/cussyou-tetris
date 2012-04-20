/* log.c -- by lizhonglei 2008-05-24 */

#include "log.h"
#include "stdio.h"

int l_init(struct log* l,char* file)
{
        if(file==0){
                l->fout=stdout;
                return 0;
        }
        l->fout=fopen(file,"a");
        if(l->fout==NULL){//
                return -1;
        }
        l->level=4; // all print
        return 0;
}

void l_close(struct log* l)
{
        fclose(l->fout);
}
void l_info(struct log* l,char* str)
{
        if(l->level>=3){
                fprintf(l->fout,"%s\n",str);
        }
}
void l_warning(struct log* l,char* str)
{
}
void l_error(struct log* l,char* str)
{
}
