#define DOWN P4_2
#define RIGHT P4_0
#define UP P4_4
#define CENTER P4_1
#define LEFT P4_3
#define maxMsgs 10


void initCursor();

void initLCD();

void updateUI(int dir);

void doActions(int row, int col);

String getText(int maxSize);

void doSend();

void updateMsg(int messages);

void getMsg();

void lcdPage(String page);

void initialize_kb();
