/* tetris.c -- by lizhonglei 2008-05-24 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "tetris.h"
#include "log.h"

#define GRAPHIC_MAX 
#define PI 3.1415926
//global

extern struct log mylog;

/*
  graphics
 */
// this way can add graphics quickly
// and if there are some graphics saved in a file, 
// then the program will be more configureable...

int graphics[][4][4]={
        {
                {0,0,0,0},
                {0,1,0,0},
                {1,1,1,0},
                {0,0,0,0}
        },
        {
                {0,0,1,0},
                {0,0,1,0},
                {0,0,1,0},
                {0,0,1,0}
        },
        {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
        },
        {
                {0,0,1,0},
                {0,0,1,0},
                {0,1,1,0},
                {0,0,0,0}
        },
        {
                {0,1,0,0},
                {0,1,0,0},
                {0,1,1,0},
                {0,0,0,0}
        },
        {
                {0,0,0,0},
                {0,0,1,0},
                {0,1,1,0},
                {0,1,0,0}
        },
        {
                {0,0,0,0},
                {0,1,0,0},
                {0,1,1,0},
                {0,0,1,0}
        },
        { // check the end
                {1,1,1,1},
                {1,1,1,1},
                {1,1,1,1},
                {1,1,1,1}
        }
};
int create_graphic(struct tetris* t)
{
        int size=0;
        int g;
        int i,j;
        int find;
		int *tmp_m;

        while(1){
                if(graphics[size][0][0]==1) break;
                size++;
        }
        g=rand()%size;
        for(i=0;i<4;i++)
                for(j=0;j<4;j++)
                        t->graphic[i][j]=graphics[g][i][j];
        // set bound
        find=0;
        j=0;
        while(!find&&j<4){
                for(i=0;i<4;i++){
                        if(t->graphic[i][j]==1){
                                t->g_left=j;
                                find=1;
                                break;
                        }
                }
                j++;
        }
        find=0;
        j=3;
        while(!find&&j>-1){
                for(i=0;i<4;i++){
                        if(t->graphic[i][j]==1){
                                t->g_right=j;
                                find=1;
                                break;
                        }

                }
                j--;
        }
        find=0;
        i=0;
        while(!find&&i<4){
                for(j=0;j<4;j++){
                        if(t->graphic[i][j]==1){
                                t->g_top=i;
                                find=1;
                                break;
                        }
                }
                i++;
        }
        find=0;
        i=3;
        while(!find&&i>-1){
                for(j=0;j<4;j++){
                        if(t->graphic[i][j]==1){
                                t->g_bottom=i;
                                find=1;
                                break;
                        }
                }
                i--;
        }
        // set grahic position in matrics
        t->g_x=t->m_x/2-2;
        t->g_y=0;
		//check space
		tmp_m=(int*)malloc(t->m_x*t->m_y*sizeof(int));
		memcpy(tmp_m,t->matrics,t->m_x*t->m_y*sizeof(int));
		for(i=0;i<4;i++){
					for(j=0;j<4;j++){
						*(tmp_m+(t->g_y+i)*t->m_x+t->g_x+j)=*(tmp_m+(t->g_y+i)*t->m_x+t->g_x+j)+t->graphic[i][j];
					}
				}
		for(i=0;i<t->m_y;i++)
					for(j=0;j<t->m_x;j++){
						if(*(tmp_m+i*t->m_x+j)>=2){
								free(tmp_m);
								t->playing=P_STOP;
								return -1;
                        }
                }
		free(tmp_m);
/*
        // log
        l_info(&mylog,"create graphic");
        for(i=0;i<4;i++){
                char tmp[256]={0};
                for(j=0;j<4;j++){
                        char ch[16]={0};
                        sprintf(ch,"%d ",t->graphic[i][j]);
                        strcat(tmp,ch);
                }
                l_info(&mylog,tmp);
        }
        {
                char tmp[256]={0};
                sprintf(tmp,"%d %d %d %d",t->g_left,t->g_top,t->g_right,t->g_bottom);
                l_info(&mylog,tmp);
        }
*/
        return 0;
}
int m_start(struct tetris* t)
{
        int lt;
        int i,j;
        lt=(int)time(NULL);
        srand(lt);
		t->playing=P_PLAY;
        create_graphic(t);
        // log
/*
        for(i=0;i<t->m_y;i++){
                char tmp[256]={0};
                for(j=0;j<t->m_x;j++){
                        char ch[16]={0};
                        sprintf(ch,"%d ",*(t->matrics+i*t->m_x+j));
                        strcat(tmp,ch);
                }
                l_info(&mylog,tmp);
        }
*/
        return 0;
}
int m_rotate(struct tetris* t)
{
        int i,j,k;
        int tmp[4][4];
        //int tmp2;
        int tmp_l,tmp_r,tmp_t,tmp_b; // tmp border
        tmp_l=t->g_top;
        tmp_t=3-t->g_right;
        tmp_r=t->g_bottom;
        tmp_b=3-t->g_left;
        if(t->g_x+tmp_l<0) return -1;
        if(t->g_x+tmp_r>t->m_x-1) return -1;
        if(t->g_y+tmp_t<0) return -1;
        //check if down to ...
		if(t->g_y+tmp_b>t->m_y-1) return -1;
        k=0;
        i=t->g_y+tmp_b; // bottom line
        j=t->g_x;
        while(k<4){
                if(*(t->matrics+i*t->m_x+j+k)==1) break;
                k++;
        }
        if(k<4) return -1;
        memset(tmp,0,16*sizeof(int));
        for(i=0;i<4;i++)
                for(j=0;j<4;j++){
                        tmp[3-j][i]=t->graphic[i][j];
                }
        for(i=0;i<4;i++)
                for(j=0;j<4;j++){
                        t->graphic[i][j]=tmp[i][j];
                }
        // border limit
        t->g_left=tmp_l;
        t->g_top=tmp_t;
        t->g_right=tmp_r;
        t->g_bottom=tmp_b;
        {
                char tmp[256]={0};
                sprintf(tmp,"%d %d %d %d",t->g_left,t->g_top,t->g_right,t->g_bottom);
                l_info(&mylog,tmp);
        }
        return 0;
}

int m_init(struct tetris* t, int x, int y)
{
        t->m_x=x;
        t->m_y=y;
        t->matrics=(int*)malloc(x*y*sizeof(int));
		t->playing=P_INIT;
        memset((void*)t->matrics,0,x*y*sizeof(int));
/*
        *(t->matrics)=1;
        *(t->matrics+13)=1;
        *(t->matrics+x*y-2)=1;
        *(t->matrics+x*y-14)=1;
        */
        return 0;
}

int m_left(struct tetris* t)
{
		if(t->playing!=P_PLAY) return -1;
        if(t->g_x+t->g_left>0){
				int tmp_gx=t->g_x-1;
				int tmp_gy=t->g_y;
				int *tmp_m;
				int i,j;
				tmp_m=(int*)malloc(t->m_x*t->m_y*sizeof(int));
				memcpy(tmp_m,t->matrics,t->m_x*t->m_y*sizeof(int));
				for(i=0;i<4;i++){
					for(j=0;j<4;j++){
                         *(tmp_m+(tmp_gy+i)*t->m_x+tmp_gx+j)=*(tmp_m+(tmp_gy+i)*t->m_x+tmp_gx+j)+t->graphic[i][j];
					}
				}
				for(i=0;i<t->m_y;i++)
					for(j=0;j<t->m_x;j++){
						if(*(tmp_m+i*t->m_x+j)==2){
								free(tmp_m);
								return -1;
                        }
                }
				free(tmp_m); // 
                t->g_x--; // left forward
        }
        return 0;
}
int m_right(struct tetris* t)
{
		if(t->playing!=P_PLAY) return -1;
        if(t->g_x+t->g_right<t->m_x-1){
				int tmp_gx=t->g_x+1;
				int tmp_gy=t->g_y;
				int *tmp_m;
				int i,j;
				tmp_m=(int*)malloc(t->m_x*t->m_y*sizeof(int));
				memcpy(tmp_m,t->matrics,t->m_x*t->m_y*sizeof(int));
				for(i=0;i<4;i++){
					for(j=0;j<4;j++){
                         *(tmp_m+(tmp_gy+i)*t->m_x+tmp_gx+j)=*(tmp_m+(tmp_gy+i)*t->m_x+tmp_gx+j)+t->graphic[i][j];
					}
				}
				for(i=0;i<t->m_y;i++)
					for(j=0;j<t->m_x;j++){
						if(*(tmp_m+i*t->m_x+j)==2){
								free(tmp_m);
								return -1;
                        }
                }
				free(tmp_m); // 
                t->g_x++;
        }
        return 0;
}
int m_down(struct tetris* t)
{
        int i,j,k;
        int tmp_gx,tmp_gy;
        int *tmp_m; //temp matrics
        int invalid;
		int tmp;
		if(t->playing!=P_PLAY) return -1;
		//
		tmp_m=(int*)malloc(t->m_x*t->m_y*sizeof(int));
        //check if down to ...
		tmp_gx=t->g_x;
        tmp_gy=t->g_y+1;
        invalid=0;
		if(t->g_y+t->g_bottom>=t->m_y-1) {
				invalid=1;
				goto is_down;
		}
		memcpy(tmp_m,t->matrics,t->m_x*t->m_y*sizeof(int));
		for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                         *(tmp_m+(tmp_gy+i)*t->m_x+tmp_gx+j)=*(tmp_m+(tmp_gy+i)*t->m_x+tmp_gx+j)+t->graphic[i][j];
                }
        }
        for(i=0;i<t->m_y;i++)
                for(j=0;j<t->m_x;j++){
						if(*(tmp_m+i*t->m_x+j)==2){
								invalid=1;
								goto is_down;
                        }
                }
 is_down:
        if(invalid==1){ // delete lines
				int lines=0;
                //memset(tmp_m,0,t->m_x*t->m_y*sizeof(int));
                memcpy(tmp_m,t->matrics,t->m_x*t->m_y*sizeof(int));
                for(i=0;i<4;i++){
                        for(j=0;j<4;j++){
                                *(tmp_m+(t->g_y+i)*t->m_x+t->g_x+j)=*(tmp_m+(t->g_y+i)*t->m_x+t->g_x+j)+t->graphic[i][j];
                        }
                }
                for(i=0;i<t->m_y;i++){
                        tmp=0;
                        for(j=0;j<t->m_x;j++) tmp=tmp+*(tmp_m+i*t->m_x+j);
                        if(tmp==t->m_x){// to delete this line
                                for(j=0;j<t->m_x;j++) *(tmp_m+i*t->m_x+j)=0;
								lines++;
                        }
                }
                // already deleted all lines that are full of blocks
         
				for(i=3;i<t->m_y;i++){// i record the tmp matrics line
						k=i;
						tmp=0;
                        for(j=0;j<t->m_x;j++) tmp=tmp+*(tmp_m+i*t->m_x+j);
                        if(tmp==0){ // spceline
							for(k=i;k>2;k--)
                                for(j=0;j<t->m_x;j++) *(tmp_m+k*t->m_x+j)=*(tmp_m+(k-1)*t->m_x+j); // copy up line
                        }                        
                }
				//copy to new matrics
				memcpy(t->matrics,tmp_m,t->m_x*t->m_y*sizeof(int));
				free(tmp_m);
				if(lines==0) return -1; 
				else return lines;
        }
		//down
        t->g_y++; 
		free(tmp_m);
        return 0;
}
int m_up(struct tetris *t)
{
		return 0;
}
int m_ddown(struct tetris *t)
{
		int i,ret;
		if(t->playing!=P_PLAY) return -1;
		while(1){
				ret=m_down(t);
				if(ret!=0) return ret;
		}
        return 0;
}
int m_get_x(struct tetris* t)
{
        return t->m_x;
}
int m_get_y(struct tetris* t)
{
        return t->m_y;
}
int m_get_state(struct tetris* t,int x,int y)
{
        int t1,t2;
        t1=*(t->matrics+(t->m_x)*y+x);
        if(t1==1) return 1;
        // check whethe this (x,y) in the graphic
		t2=0;
        if((t->g_x<=x)&&(t->g_x+4>x)&&(t->g_y<=y)&&(t->g_y+4>y)){
                t2=t->graphic[y-t->g_y][x-t->g_x];
                
        }
        return t2;
}
void m_free(struct tetris* t)
{
        free(t->matrics);
}
void m_end(struct tetris *t)
{
		t->playing=P_STOP;
		memset(t->matrics,0,t->m_x*t->m_y*sizeof(int));
		memset(t->graphic,0,16);
		t->g_bottom=t->g_left=t->g_right=t->g_top=t->g_x=t->g_y=0;
}