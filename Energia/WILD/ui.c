#include <stdio.h>
static char *VIEW ="                    \n"
                "<  View Messages   >\n"
                "  unread:0 total:0  \n"
                "                    \n";
                
    char *SEND ="                    \n"
                "<   Send Message   >\n"
                "                    \n"
                "                    \n";
                
    char *OPT = "                    \n"
                "<     Options      >\n"
                "                    \n"
                "                    \n";
                
    char *SOS = "                    \n"
                "<    Send  SOS     >\n"
                "                    \n"
                "                    \n";
            
            
    
    
    char *pages[8][4]={
          {VIEW,       SEND,       OPT,            NULL}
        , {NULL,       NULL,       NULL,           NULL}
        , {NULL,       NULL,       NULL,           NULL}
        , {NULL,       NULL,       NULL,           NULL}
        , {NULL,       NULL,       NULL,           NULL}
        , {NULL,       NULL,       NULL,           NULL}
        , {NULL,       NULL,       NULL,           NULL}
        , {NULL,       NULL,       NULL,           NULL}
    };
    
