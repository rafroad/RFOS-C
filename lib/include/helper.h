#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>

#ifndef _HELPER_H_
#define _HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif

void drawmultext(char input[][1000], int x);
void drawline(int am);
void copyrighttextlegacy(bool isborder, int spaceam,bool splitspace, int spaceam2);
void titlescreen(char title[], bool includecopyright);
void copyrighttextwitbox();
void milderror(char errormessage[]);
void criterror(char errormessage[]);
void drawmulmultext(char input1[][1000],char input2[][1000], int x);
void newdrawmultext(char input[][1000], int x);
void newdrawmultextfloat(float input[], int x);
void delarray(char input[][1000],int pos,int x);
void cleararray(char input[][1000],int x);
void drawmulmultextnum(char input1[][1000],char input2[][1000], int x);
void drawmultextnum(char input1[][1000],int x);
void drawostitle(void);

#ifdef __cplusplus
}
#endif



#endif