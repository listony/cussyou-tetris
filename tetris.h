/* tetris.h -- by lizhonglei 2008-05-24 */
/*
  it's very eaty to implement OOP with "C" not "C++"
  this "Object" doesn't care timer, paint, message and etc.
  
 */
#ifndef _TETRIS_H
#define _TETRIS_H

#define WM_SCORE        1011 // delete some lines, wParam is number of 'lines' deleted

#define P_STOP 1102
#define P_PAUSE 1101
#define P_PLAY  1100
#define P_INIT  1109

struct tetris{
        int graphic[4][4]; //the following graphic
        int g_left,g_right,g_top,g_bottom; // the border limit of the graphic in the 4X4 matrics
        int g_x,g_y; // the left-top position of graphic in the matrics

        int *matrics; // the matrics 
        int m_x,m_y; // size

        int *out; // out to print, out=matrics+graphic, 
		int playing; // game state; play , stop, pause
};

// functions about matrics
int m_init(struct tetris* t,int x, int y);
int m_start(struct tetris* t);
void m_end(struct tetris* t);
int m_up(struct tetris* t);
int m_left(struct tetris* t);
int m_right(struct tetris* t);
int create_graphic(struct tetris* t);
// m_down() return the number of deleted lines
int m_down(struct tetris* t);
int m_ddown(struct tetris* t);
//
int m_rotate(struct tetris* t);
int m_get_x(struct tetris* t);
int m_get_y(struct tetris* t);
int m_get_state(struct tetris* t,int x,int y); 
void m_free(struct tetris* t);

#endif
