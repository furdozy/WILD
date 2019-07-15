#include <stdio.h>
#include "pages.h"


char* UI(int dir){  
    char *pages[8][4]={
        {VIEW,       SEND,       OPT,        SOS}
        ,{NULL,       NULL,       NULL,           NULL}
        ,{NULL,       NULL,       NULL,           NULL}
        ,{NULL,       NULL,       NULL,           NULL}
        ,{NULL,       NULL,       NULL,           NULL}
        ,{NULL,       NULL,       NULL,           NULL}
        ,{NULL,       NULL,       NULL,           NULL}
        ,{NULL,       NULL,       NULL,           NULL}
    };
        int col=0;
        int row=0;
        int input;
        
        while(1==1){
        ("%s",pages[row][col]);
        scanf("%d",&input);
        if(input==4){
            if(col==0)col=3;
            else col--;
        }else if(input==6){
            if(col==3)col=0;
            else col++;
        }
        }
    
        printf("\n");
    }
    
