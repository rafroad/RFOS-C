#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include "helper.h"
#include <termfunc.h>
#include <string.h>
#define OS "RFOS-V1.0-ALPHA"
#define KERNELVER "KERNEL VERSION 1.0-A"
#define COPYRIGHTTEXT "COPYRIGHT Rafroad 2024"
#define BORDER "="

//MADE BY RAFROAD

char stringlong(char string1[],char string2[]){
    if(strlen(string1)>strlen(string2)){
        return string1[];
    }
    else{
        return string2[];
    }
}

char stringlongstrlen(char string1[],char string2[]){
    if(strlen(string1)>strlen(string2)){
        return strlen(string1);
    }
    else{
        return strlen(string2);
    }
}

void drawmultext(char input[][1000], int x){
    for(int i=0; i<x; i++){
        printf_("%s",input[i]);
    }
}

void drawline(int am){
   for(int i=0; i<am; i++){
         printf_("%s",BORDER);
   }
   printf_("\n");
}


void copyrighttextlegacy(bool isborder, int spaceam,bool splitspace, int spaceam2){
   char space[]=" ";
   if(isborder){
      printf_("%s",BORDER);
      for(int i=0; i<spaceam; i++){
         printf_("%s",space);
      }
      printf_("%s",COPYRIGHTTEXT);
   if(splitspace){
         for(int i=0; i<spaceam2; i++){
         printf_("%s",space);
      }
      }
   else {
         for(int i=0; i<spaceam; i++){
         printf_("%s",space);
      }
      }
      printf_("%s",BORDER);
      printf_("\n");
   }
   else{
      printf_("%s\n",COPYRIGHTTEXT);
   }
}

void titlescreen(char title[], bool includecopyright){
   int copylen=strlen(COPYRIGHTTEXT);
   int titlelen=strlen(title);
   if(includecopyright){
      if(copylen>titlelen){
         printf_("%s\n",title);
         printf_("%s\n",COPYRIGHTTEXT);
         drawline(copylen);
      }
      else{
         printf_("%s\n",title);
         printf_("%s\n",COPYRIGHTTEXT);
         drawline(titlelen);
      }
   }
   else{
      printf_("%s\n",title);
      drawline(titlelen);
   }
}

void copyrighttextwitbox(){
   drawline(45);
   char copyright[100]="";
   copyrighttextlegacy(copyright,5,false,5);
   printf_("%s",copyright);
   drawline(45);
}

void milderror(char errormessage[]){
   printf_("a error has occured: %s\n",errormessage);
}

void criterror(char errormessage[]){
   printf_("a critical error has occured: %s \nplease contact your system administrator and restart the application\n",errormessage);
}

void drawmulmultext(char input1[][1000],char input2[][1000], int x){
    for(int i=0; i<x; i++){
        printf_("%s\t%s\n",input1[i],input2[i]);
    }
}
void newdrawmultext(char input[][1000], int x){
    for(int i=0; i<x; i++){
        printf_("%s\n",input[i]);
    }
}

void newdrawmultextfloat(float input[], int x){
    for(int i=0; i<x; i++){
        printf_("%f\n",input[i]);
    }
}
void delarray(char input[][1000],int pos,int x){
    for(int i=pos-1;i<x-1;i++){
        strcpy(input[i],input[i+1]);
    }
}
void cleararray(char input[][1000],int x){
   char empty[x][1000];
   for(int i=0;i<x;i++){
      strcpy(input[i],empty[i]);
   }
}
void drawmulmultextnum(char input1[][1000],char input2[][1000], int x){
    int pos=0;
    for(int i=0; i<x; i++){
      pos++;
      printf("%i\t%s\t%s\n",pos,input1[i],input2[i]);
    }
}
void drawmultextnum(char input1[][1000], int x){
    int pos=0;
    for(int i=0; i<x; i++){
      pos++;
      printf("%i\t%s\n",pos,input1[i]);
    }
}

void drawostitle(void){
   printf_("%s\n",OS);
   printf("%s\n",KERNELVER);
   drawline(stringlongstrlen(OS, KERNELVER));
}
