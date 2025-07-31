#include "iGraphics.h"
#include <iostream>
#include "iSound.h"
using namespace std;
Image bg;
Image sp, EnemyShip;
Image HP;
Image HP2;
Image storyBG;
Image bullet, enemybulleeet;
Image SforHealth;
Image Healthbar;
Image Stoneimg;
Image bg2;
Image instructionpage,ScorePage,Instruction2;
Image Enemyshipf2;
Image Enemybulletf2;
Image Healthitem;
Image missile;
Image missileitom;
Image gamepause ;
int speed = -10;
int shipX = 50;
int shipY = 200;
int gamestate = 0;
int shiphealth = 100;
int mx, my;
int bgSoundIdx = -1;
int battlethemeeee = -1;
int Storytheme = -1;
bool battlethemeplaying= false;
bool storythemeplaying= false;
int c = 1, score = 0,tempscore=0;
bool gameover = false;
//int gameovertimer = 0;
int battletheme2 = -1;
void spawnenemy();
bool arenalevel2 = false;
bool battletheme2play = false;
bool showarenamsg= false;
int arenamsgtimer = 0;
const int arenamsgdur = 200;
bool arenatranssitioned= false;
int gs5music = -1;
int flag=1;

bool Paused = false;  
int pausegamstate = -1;  

// int activeMissileCount=0;
int aavailablemissiles = 3;
#define MAX_SCORES 1000
typedef struct{
char name[100];
int score;
}HighScore;
HighScore highScores[MAX_SCORES];
int highScoreCount=0;
char playerName[100]="";
int nameInputIndex=0;
bool enteringName=false;
// bool showblaeff=false;
// int blaefftim=0;
// const int blaeffdur=5;
//  0 to 5
//  For timing each phase
int k = 0;
int p = 0;

struct Blast {
    int x, y;       
    int radius;     
    int maxradii;  
    int timer;      
    bool active;    
};

#define MAX_BLASTS 5
Blast blasts[MAX_BLASTS];

#define MAX_MISSILES 10
struct Missile
{
    bool active;
    int x, y;
    int speed;
    int targety;
};
Missile missiles[MAX_MISSILES];
//int missilecoll= 0;

struct Bullet
{
    int x, y;
    bool active;
};
struct Eenemybullet
{
    int x, y;
    bool active;
};
struct Enemy
{
    int x, y;
    int enemyhealth;
    bool exist;
    bool active;
};
struct hhealthiteem
{
    int x, y;
    bool visible;
};
hhealthiteem healthiitem;
struct missileitem
{
    int x, y;
    bool visible;
};
missileitem missileitm;

// Enemy enemies[2];
// int enemy_movement[2] = {-1, 1};
// int RevivingEnemyTimer[2] = {0};
#define MAX_ENEMIES 4
Enemy enemies[MAX_ENEMIES];
int enemy_movement[MAX_ENEMIES] = {-1, 1, 1, -1};
int revivinenemytime[MAX_ENEMIES] = {0};

const int MAX_BULLETS = 100;
Bullet bullets[MAX_BULLETS];
Eenemybullet enemybullets[MAX_BULLETS];
#define MAX_STONES 10
struct Stone
{
    int x;
    int y;
    int sx;
    int sy;
    bool stonevisible;
};
Stone stones[MAX_STONES];
bool stonespwned = false;
string storylines[] = {
    "2405100                                                                                                 2405099",
    "SECTION-B                                                                                         SECTION-B",
    "DEPARTMENT-CSE                        SUMAIYA SULTANA                 DEPARTMENT-CSE",
    "AJMAIN FAYEK DIGANTA                  SUPERVISOR                         PROTTOY BARUA",
    "",
    "",
    "",
    "",
    "                                                    ~ THE END ~",
    "",
    "",
    "",
    "This... is the Eclipse Protocol.",
    "To protect Earth. To save BUET. To survive extinction.",
    "Now, Prottoy and Diganta launch on a one-way mission.",
    "Built secretly by BUET's Mechanical and CSE wings.",
    "But one prototype remained — the B-71 Eclipse.",
    "Human fleets were ambushed. Hope nearly lost.",
    "An alien fleet known as The Null awakened from Titan’s shadows.",
    "\"The moons of Saturn are no longer yours.\"",
    "On January 1st, 3071, Earth intercepted a signal:",
    "Diganta — the youngest to pilot a quantum-class fighter.",
    "Prottoy — a hacker and tactical prodigy who rewrote battle systems.",
    "Among thousands of cadets, two names echoed through the cosmos:",
    "From the Infinity Dome, missions launched beyond stars.",
    "but as Earth's most powerful space defense agency: B.S.D.",
    "Decades after the Collapse Wars, BUET rose not just as a university,",
    "In the year 3071, Earth is no longer a cradle of humanity — it is a fortress.",
};
int totline = sizeof(storylines) / sizeof(storylines[0]);
float storyy = -30 * totline + 300;
float scrollspeed = .7;
bool scrolling = true;
void loadResources()
{
    iLoadImage(&sp, "assets/images/Ship6.png");
    iResizeImage(&sp, 80, 80);
    iLoadImage(&EnemyShip, "assets/images/Enemy.png");
    iResizeImage(&EnemyShip, 90, 90);
    iLoadImage(&bullet, "assets/images/bullet.png");
    iResizeImage(&bullet, 40, 15);
    iLoadImage(& enemybulleeet, "assets/images/EnemyBullet.png");
    iResizeImage(& enemybulleeet, 40, 20);
    iLoadImage(&bg, "assets/images/background2.png");
    iResizeImage(&bg, 1400, 700);
    iLoadImage(&HP, "assets/images/MainHomePage.png");
    iResizeImage(&HP, 1400, 700);
    iLoadImage(&storyBG, "assets/images/StoryPage.png");
    iResizeImage(&storyBG, 1400, 700);
    iLoadImage(&HP2, "assets/images/2ndPage.03.png");
    iResizeImage(&HP2, 1400, 700);
    iLoadImage(&SforHealth, "assets/images/Healthship.png");
    iResizeImage(&SforHealth, 80, 70);
    iLoadImage(&Healthbar, "assets/images/Healthbar.png");
    iResizeImage(&Healthbar, 280, 150);
    iLoadImage(&Stoneimg, "assets/images/Stone.png");
    iResizeImage(&Stoneimg, 70, 70);
    iLoadImage(&bg2, "assets/images/newbg1.png");
    iResizeImage(&bg2, 1400, 700);
    iLoadImage(&instructionpage, "assets/images/InstructionsPage.png");
    iResizeImage(&instructionpage, 1400, 700);
    iLoadImage(&Enemyshipf2, "assets/images/Enemyshipf2.png");
    iResizeImage(&Enemyshipf2, 80, 80);
    iLoadImage(&Enemybulletf2, "assets/images/Enemybulletf2.png");
    iResizeImage(&Enemybulletf2, 60, 20);
    iLoadImage(&Healthitem, "assets/images/Plus.png");
    iResizeImage(&Healthitem, 90, 90);
    iLoadImage(&missile, "assets/images/missile.png");
    iResizeImage(&missile, 175, 50);
    iLoadImage(&missileitom, "assets/images/missileitem.png");
    iResizeImage(&missileitom, 150, 80);

    iLoadImage(&ScorePage,"assets/images/HighScore.png");
iResizeImage(&ScorePage,1400,700);
iLoadImage(&gamepause, "assets/images/gamepause.png");
    iResizeImage(&gamepause, 1400, 700);
    iLoadImage(&Instruction2,"assets/images/INS.png");
iResizeImage(&Instruction2,1400,700);

}
void scrollStory()
{
    if (gamestate == 1 && scrolling)
    {
        storyy += scrollspeed;
        if (storyy >= 390)
        {
            scrolling = false;
        }
    }
}
void drawBlasts();

void iDraw()
{
    k++;
    iClear();

    if (gamestate == 1 || gamestate == 2 || gamestate == 7 || gamestate==8 || gamestate==9)
    {
        
    
        if (!storythemeplaying || Storytheme == -1)
        {
            Storytheme = iPlaySound("assets/sounds/Storytheme.wav", true, 150);
            storythemeplaying = (Storytheme != -1);
        }


    }
    else if (storythemeplaying)
    {
        iStopSound(Storytheme);
        Storytheme = -1;
        storythemeplaying = false;
    }

    if ((gamestate == 3 || gamestate == 4 || Paused ) && !battlethemeplaying && flag==1  ) //
    {
        battlethemeeee  = iPlaySound("assets/sounds/Battle.wav", true, 150);
       battlethemeplaying= (battlethemeeee  != -1);
        
        
       // flag=2;
    }
    else if ((gamestate != 3 && gamestate != 4 && !Paused) && battlethemeplaying)
    {
        iStopSound(battlethemeeee );
        battlethemeeee = -1;
       battlethemeplaying= false;

    }

    if ((gamestate == 6 ||Paused|| gamestate==4)  &&  !battletheme2play && flag==2) //flag==2
    {
        battletheme2 = iPlaySound("assets/sounds/battletheme2.wav", true, 150);
        battletheme2play = (battletheme2 != -1);


    }
    else if (gamestate != 6 && battletheme2play &&gamestate==2 )
    {
        iStopSound(battletheme2);
        battletheme2 = -1;
        battletheme2play = false;


    }
    /* else if(gamestate==3 && arenalevel2){
         iStopSound(BattleTheme);
 if(!battletheme2play){
 battletheme2= iPlaySound("assets/sounds/battletheme2.wav", true, 100);
 battletheme2play=true;
 }
     }*/

    /*  else if (gamestate == 3 && arenalevel2)
  {

      if (BattleThemePlaying) {
          iStopSound(BattleTheme);
          BattleTheme = -1;
          BattleThemePlaying = false;
      }

      if (!battletheme2play || battletheme2 == -1) {
          battletheme2 = iPlaySound("assets/sounds/battletheme2.wav", true, 100);
          battletheme2play = true;
      }
  }   */
    /* else
     {
         if (BattleThemePlaying)
         {
             iStopSound(BattleTheme);
             BattleTheme = -1;
             BattleThemePlaying = false;
         }
     }
 */

    if (gamestate != 0 && bgSoundIdx != -1)
    {
        iStopSound(bgSoundIdx);
        bgSoundIdx = -1;
    }

    if (gamestate == 0)
    {
        iShowLoadedImage(0, 0, &HP);
    }
    else if (gamestate == 1)
    {
        iShowLoadedImage(0, 0, &storyBG);

        int y = storyy;
        for (int i = 0; i < totline; i++)
        {
            if (y >= 220 && y <= 490)
            {
                iTextBold(350, y, storylines[i].c_str(), GLUT_BITMAP_HELVETICA_18);
            }
            y += 30;
        }
    }
    else if (gamestate == 2)
    {
        iShowLoadedImage(0, 0, &HP2);
        //flag=2;
    }
    else if (gamestate == 3)
    {flag =1;
        if (arenalevel2)
        {
            iShowLoadedImage(0, 0, &bg2);
            iWrapImage(&bg2, speed);
        }
        else
        {
            iShowLoadedImage(0, 0, &bg);
            iWrapImage(&bg, speed);
        }
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (enemies[i].active && enemies[i].exist)
            {
                iShowLoadedImage(enemies[i].x, enemies[i].y, &EnemyShip);
            }
        }
        if (shipX < 0)
            shipX = 0;
        if (shipX > 1320)
            shipX = 1320;
        if (shipY < 0)
            shipY = 0;
        if (shipY > 620)
            shipY = 620;
        iShowLoadedImage(shipX, shipY, &sp);
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].active)
            {
                iShowLoadedImage(bullets[i].x, bullets[i].y, &bullet);
            }
        }
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (enemybullets[i].active)
            {
                iShowLoadedImage(enemybullets[i].x, enemybullets[i].y, & enemybulleeet);
            }
        }
        for (int i = 0; i < MAX_STONES; i++)
            if (stones[i].stonevisible)
                iShowLoadedImage(stones[i].x, stones[i].y, &Stoneimg);

        iShowLoadedImage(560, 595, &Healthbar);
        int barWidth = 200;
        int barHeight = 18;
        int barX = 600;
        int barY = 659;
        float healthRatio = shiphealth / 150.0f;
        iShowLoadedImage(510, 630, &SforHealth);
        iSetColor(100, 100, 100);
        iFilledRectangle(barX, barY, barWidth, barHeight);
        iSetColor(255, 0, 0);
        iFilledRectangle(barX, barY, barWidth * healthRatio, barHeight);
        iSetColor(255, 255, 255);
        iRectangle(barX, barY, barWidth, barHeight);
        char HT[20];
        sprintf(HT, "HP: %d / 150", shiphealth);
        iSetColor(255, 255, 255);
        iText(barX + 57, barY + 25, HT, GLUT_BITMAP_HELVETICA_18);
        char scoreText[50];
        sprintf(scoreText, "Score: %d", score);
        iSetColor(255, 255, 255);
        iText(40, 650, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    /*if (showArenaMessage) {
        iSetColor(255, 255, 0);
        iText(600, 350, "Game Arena Changing...", GLUT_BITMAP_TIMES_ROMAN_24);
        return; }
    */
    /*if (showblaeff) {
        iSetTransparentColor(255,255,255,.9);
        iFilledRectangle(0, 0, 1400, 700);
    }
    */

    else if (gamestate == 4)
    {
        if (tempscore<= 200)
        {
            iShowLoadedImage(0, 0, &bg);
            iWrapImage(&bg, speed);
            iSetColor(255, 0, 0);
        }
        else
        {
            iShowLoadedImage(0, 0, &bg2);
            iWrapImage(&bg2, speed);
            iSetColor(255, 0, 0);
        }

       // iText(600, 350, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
       // char scoreText[50];
       // sprintf(scoreText, "Your Score: %d", score);
       // iText(600, 300, scoreText, GLUT_BITMAP_HELVETICA_18);
        // iText(600, 250, "Press Enter to Restart", GLUT_BITMAP_HELVETICA_18);


        if(enteringName){
iText(600,350,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
char scoreText[50];
sprintf(scoreText,"Your Score: %d",tempscore);
iSetColor(255,255,255);
iText(600,300,scoreText,GLUT_BITMAP_HELVETICA_18);
iText(600,400,"Enter your name:",GLUT_BITMAP_HELVETICA_18);
iText(750,400,playerName,GLUT_BITMAP_HELVETICA_18);
//return;
}
    }
    // iText(140, 180, "Hello World");
    else if (gamestate == 5)
    {
        p++;

        iShowLoadedImage(0, 0, &bg);
        iWrapImage(&bg, speed);
        iShowLoadedImage(shipX, shipY, &sp);

        /* if (showblaeff) {
          iSetTransparentColor(255,255,255,.9);
          iFilledRectangle(0, 0, 1400, 700);
      }
      */

        if (p >= 340)
        {
            iSetColor(255, 255, 255);
            iFilledRectangle(0, 0, 1400, 700);
        }

        if (k % 10 == 0)
        {
            iSetTransparentColor(255, 255, 255, 1);
            iFilledRectangle(0, 0, 1400, 700);
        }
        if (showarenamsg)
        {
            iSetColor(255, 255, 0);
            iText(600, 350, "Game Arena Changing...", GLUT_BITMAP_TIMES_ROMAN_24);
            return;
        }
    }

    else if (gamestate == 6)
    {flag =2;
        // iStopSound(gs5music);
        iShowLoadedImage(0, 0, &bg2);
        iWrapImage(&bg2, speed);
        iShowLoadedImage(shipX, shipY, &sp);
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].active)
            {
                iShowLoadedImage(bullets[i].x, bullets[i].y, &bullet);
            }
        }
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (enemies[i].active && enemies[i].exist)
            {
                iShowLoadedImage(enemies[i].x, enemies[i].y, &Enemyshipf2);
            }
        }

        if (healthiitem.visible)
        {
            iShowLoadedImage(healthiitem.x, healthiitem.y, &Healthitem);
        }
        if (missileitm.visible)
        {
            iShowLoadedImage(missileitm.x, missileitm.y, &missileitom);
        }

        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (enemybullets[i].active)
            {
                iShowLoadedImage(enemybullets[i].x, enemybullets[i].y, &Enemybulletf2);
            }
        }

        if (shipX < 0)
            shipX = 0;
        if (shipX > 1320)
            shipX = 1320;
        if (shipY < 0)
            shipY = 0;
        if (shipY > 620)
        {
            shipY = 620;
        }
        iShowLoadedImage(560, 595, &Healthbar);
        int barWidth = 200;
        int barHeight = 18;
        int barX = 600;
        int barY = 659;
        float healthRatio = shiphealth / 150.0f;
        iShowLoadedImage(510, 630, &SforHealth);
        iSetColor(100, 100, 100);
        iFilledRectangle(barX, barY, barWidth, barHeight);
        iSetColor(255, 0, 0);
        iFilledRectangle(barX, barY, barWidth * healthRatio, barHeight);
        iSetColor(255, 255, 255);
        iRectangle(barX, barY, barWidth, barHeight);
        char HT[20];
        sprintf(HT, "HP: %d / 150", shiphealth);
        iSetColor(255, 255, 255);
        iText(barX + 57, barY + 25, HT, GLUT_BITMAP_HELVETICA_18);
        char scoreText[50];
        sprintf(scoreText, "Score: %d", score);
        iSetColor(255, 255, 255);
        iText(40, 650, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);

        for (int i = 0; i < MAX_MISSILES; i++)
        {
            if (missiles[i].active)
            {
                iShowLoadedImage(missiles[i].x, missiles[i].y, &missile);
            }
        }
        if (gamestate == 6)
        {
            char missileInfo[20];
            sprintf(missileInfo, "Missiles: %d/3", aavailablemissiles);  //3 - availableMissiles
            iSetColor(0, 255, 255);
            iText(1150, 650, missileInfo, GLUT_BITMAP_HELVETICA_18);
        }

drawBlasts();

    }
    else if (gamestate == 7)
    {
        iShowLoadedImage(0, 0, &instructionpage);
    }

else if(gamestate==8){
iShowLoadedImage(0,0,&ScorePage);
iSetColor(255,255,255);
int shown=highScoreCount<7?highScoreCount:7;
for(int i=0;i<shown;i++){
char displayText[200];
sprintf(displayText,"%d. %s - %d",i+1,highScores[i].name,highScores[i].score);
iText(520,450-i*40,displayText,GLUT_BITMAP_HELVETICA_18);
}
}

else 
    if (Paused) {
      /*  iSetColor(255, 255, 255);
        iText(600, 350, "PAUSED", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(550, 300, "Press 'R' to Resume", GLUT_BITMAP_HELVETICA_18);

        */
       iShowLoadedImage(0,0,&gamepause);
    }

    else if(gamestate==9){
iShowLoadedImage(0,0,&Instruction2);}

}
int compareScores(const void*a,const void*b){
return((HighScore*)b)->score-((HighScore*)a)->score;
}
void sortScores(){
qsort(highScores,highScoreCount,sizeof(HighScore),compareScores);
}
void saveScoreToFile(const char*name,int score){
FILE*file=fopen("scores.txt","a");
if(file!=NULL){
fprintf(file,"%s %d\n",name,score);
fclose(file);
}
}
void loadScoresFromFile(){
FILE*file=fopen("scores.txt","r");
highScoreCount=0;
if(file!=NULL){
while(fscanf(file,"%s %d",highScores[highScoreCount].name,&highScores[highScoreCount].score)==2){
highScoreCount++;
if(highScoreCount>=MAX_SCORES)
break;
}
fclose(file);
}
}
void resetGame()
{
//flag =1;
       Paused = false;
   pausegamstate = -1;
   gameover=false;
   
    shipX = 50;
    shipY = 200;
    shiphealth = 150;
    score = 0;
    c = 0;
    p = 0;
    stonespwned = false;
    showarenamsg= false;
    arenamsgtimer = 0;
    arenatranssitioned= false;
    arenalevel2 = false;
    aavailablemissiles = 3;


    for (int i = 0; i < MAX_MISSILES; i++)
    {
        missiles[i].active = false;
        missiles[i].x = 0;
        missiles[i].y = 0;
        missiles[i].speed = 0;
        missiles[i].targety = 0;
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].active = false;
        enemybullets[i].active = false;
    }
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].active = false;
        enemies[i].exist = false;
        revivinenemytime[i] = 0;
    }
    for (int i = 0; i < MAX_STONES; i++)
    {
        stones[i].stonevisible = false;
    }

    for (int i = 0; i < MAX_BLASTS; i++) {
    blasts[i].active = false;
}

    healthiitem.visible = false;
    healthiitem.x = -100;
    healthiitem.y = -100;
    missileitm.visible = false;
    missileitm.x = -100;
    missileitm.y = -100;

    if (battlethemeplaying) iStopSound(battlethemeeee );
    if (battletheme2play) iStopSound(battletheme2);
    battlethemeplaying = false;
    battletheme2play = false;
}

void updateMissiles()
{
    for (int i = 0; i < MAX_MISSILES; i++)
    {
        if (missiles[i].active)
        {
            missiles[i].x += missiles[i].speed;
            
            if (missiles[i].y < missiles[i].targety)
                missiles[i].y += 3;
            else if (missiles[i].y > missiles[i].targety)
                missiles[i].y -= 3;
            
         
            for (int e = 0; e < MAX_ENEMIES; e++)
            {
                if (enemies[e].exist && enemies[e].active)
                {
                   
                    bool xCollide = (missiles[i].x < enemies[e].x + 80) && 
                                  (missiles[i].x + 175 > enemies[e].x);
                    bool yCollide = (missiles[i].y < enemies[e].y + 80) && 
                                  (missiles[i].y + 50 > enemies[e].y);
                    
                    if (xCollide && yCollide)
                    {
                         for (int b = 0; b < MAX_BLASTS; b++) {
                    if (!blasts[b].active) {
                        blasts[b].x = enemies[e].x + 40; 
                        blasts[b].y = enemies[e].y + 40;
                        blasts[b].radius = 10;
                        blasts[b].maxradii = 80; //70
                        blasts[b].timer = 30;  
                        blasts[b].active = true;
                        break;
                    }
                }
                        
                        const int R2 = 140 * 140;
                        for (int k = 0; k < MAX_ENEMIES; k++)
                        {
                            if (enemies[k].exist && enemies[k].active)
                            {
                                int dx = enemies[k].x - enemies[e].x;
                                int dy = enemies[k].y - enemies[e].y;
                                if (dx*dx + dy*dy <= R2)
                                {
                                    enemies[k].exist = false;
                                    enemies[k].active = false;
                                    revivinenemytime[k] = 100;
                                    score += 10;
                                }
                            }
                        }
                        missiles[i].active = false;
                        break;
                    }
                }
            }
            
           
            if (missiles[i].x > 1400)
            {
                missiles[i].active = false;
            }
        }
    }
}

void updateBlasts() {
    for (int i = 0; i < MAX_BLASTS; i++) {
        if (blasts[i].active) {
            blasts[i].radius += 10;  // Expand blast
            blasts[i].timer--;
            if (blasts[i].timer <= 0 || blasts[i].radius >= blasts[i].maxradii) {
                blasts[i].active = false;
            }
        }
    }
}

void drawBlasts() {
    for (int i = 0; i < MAX_BLASTS; i++) {
        if (blasts[i].active) {
           
            iSetTransparentColor(135, 206, 235, 1);  
            iFilledCircle(blasts[i].x, blasts[i].y, blasts[i].radius, 100);
        }
    }
}


/*
function iMouseMove() is called when the user moves the mouse.
cd "C:\Users\LENOVO\OneDrive\Desktop\Modern-iGraphics-main\Modern-iGraphics-main"
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
}
// /*
// function iMouseDrag() is called when the user presses and drags the mouse.
// (mx, my) is the position where the mouse pointer is.
// */
void iMouseDrag(int mx, int my)
{
    // place your codes here
}
/*
// function iMouse() is called when the user presses/releases the mouse.
// (mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if (gamestate == 0)
        {
            if (mx >= 570 && mx <= 810 && my >= 40 && my <= 145)
            {
                gamestate = 1;
                scrolling = true;
                storyy = -30 * totline + 300;
            }
        }
        else if (gamestate == 1)
        {
            if (mx >= 570 && mx <= 800 && my >= 30 && my <= 135)
            {
                gamestate = 2;
            }
        }
        else if (gamestate == 2)
        {
            if (mx >= 590 && mx <= 835 && my >= 525 && my <= 635)
            {
                resetGame();
                gamestate = 3;
                spawnenemy();
                shiphealth = 150;
tempscore=0;
                for (int i = 0; i < MAX_BULLETS; i++)
                {
                    bullets[i].active = false;
                    enemybullets[i].active = false;
                }
            }
            if (mx >= 1 && mx <= 91 && my >= 615 && my <= 700)
            {
                gamestate = 1;
                scrolling = true;
                storyy = -30 * totline + 300;
            }
            if (mx >= 385 && mx <= 825 && my >= 380 && my <= 485)
            {
                gamestate = 7;
            }


            if(mx>=585&&mx<=825&&my>=240&&my<=330){
gamestate=8;
loadScoresFromFile();
sortScores();
}
if(mx>=585&&mx<=825&&my>=90&&my<=200){
exit(1);
}
        }

        /* else if(gamestate==2){
         if (mx >= 385 && mx <= 825 && my >= 380 && my <= 485)
             {
                 gamestate = 7;
             }
         } */

        else if (gamestate == 7)
        {
            if (mx >= 1 && mx <= 91 && my >= 615 && my <= 700)
            {
                gamestate = 2;
            }

            if(mx>=1270&&mx<=1390&&my>=320&&my<=430)
gamestate=9;
        }
else if(gamestate==8){
if(mx>=1&&mx<=91&&my>=615&&my<=700){
gamestate=2;
}
}

else if(gamestate==9){
if(mx>=10&&mx<=130&&my>=310&&my<=425){
gamestate=7;}}

    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
}
/*
 function iMouseWheel() is called when the user scrolls the mouse wheel.
 dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}
// function iKeyboard() is called whenever the user hits a key in keyboard.
// key- holds the ASCII value of the key pressed.
void iKeyboard(unsigned char key)
{

   if (key == 'p' || key == 'P') {
        if (gamestate == 3 || gamestate == 6) {
            if (!Paused) {
                Paused = true;
                pausegamstate = gamestate;
                gamestate = -1;  
               // iPauseSound(BattleTheme);  
               // if (battletheme2play) iPauseSound(battletheme2);
            }
        }
    }
    else if (key == 'r' || key == 'R') {
        if (Paused) {
            Paused = false;
            gamestate = pausegamstate;
            //iResumeSound(BattleTheme); 
           // if (battletheme2play) iResumeSound(battletheme2);
        }

    }





   if(enteringName&&gamestate==4){
if(key=='\r'){
enteringName=false;
saveScoreToFile(playerName,tempscore);
enteringName=false;
score=0;
gamestate=2;
}else if(key=='\b'){
if(nameInputIndex>0){
nameInputIndex--;
playerName[nameInputIndex]='\0';
}
}else if(nameInputIndex<100-1&&key>=32&&key<=126){
playerName[nameInputIndex++]=key;
playerName[nameInputIndex]='\0';
}
return;
}
   
    if (key == 'm' && gamestate == 6)
    {
        if (aavailablemissiles > 0)
        { 
            for (int i = 0; i < MAX_MISSILES; i++)
            {
                if (!missiles[i].active)
                {
                    missiles[i].x = shipX + 70;
                    missiles[i].y = shipY + 33;
                    missiles[i].speed = 20;
                 
                    int closestEnemyY = shipY;
                    for (int j = 0; j < MAX_ENEMIES; j++)
                    {
                        if (enemies[j].active && enemies[j].exist)
                        {
                            closestEnemyY = enemies[j].y;
                            break;
                        }
                    }
                    missiles[i].targety = closestEnemyY;
                    missiles[i].active = true;
                    aavailablemissiles--; 
                    break;
                }
            }
        }
    }
}
/*
// function iSpecialKeyboard() is called whenver user hits special keys likefunction
// keys, home, end, pg up, pg down, arraows etc. you have to use
// appropriate constants to detect them. A list is:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
// GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
// GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
// GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
// GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    if (gamestate == 3)
    {
        if (key == GLUT_KEY_UP)
        {
            shipY += 15;
        }
        if (key == GLUT_KEY_DOWN)
        {
            shipY -= 15;
        }
        if (key == GLUT_KEY_RIGHT)
        {
            shipX += 15;
        }
        if (key == GLUT_KEY_LEFT)
        {
            shipX -= 15;
        }
    }

    else if (gamestate == 6)
    {
        if (key == GLUT_KEY_UP)
        {
            shipY += 15;
        }
        if (key == GLUT_KEY_DOWN)
        {
            shipY -= 15;
        }
        if (key == GLUT_KEY_RIGHT)
        {
            shipX += 15;
        }
        if (key == GLUT_KEY_LEFT)
        {
            shipX -= 15;
        }
    }
}
void shootBullet()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].x = shipX + 70;
            bullets[i].y = shipY + 33;
            bullets[i].active = true;
            break;
        }
    }
}
void updateBullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            bullets[i].x += 20;
            if (bullets[i].x > 1400)
            {
                bullets[i].active = false;
            }
        }
    }
}
void spawnenemy()
{
    int limit = (gamestate == 6) ? MAX_ENEMIES : 2;
    for (int i = 0; i < limit; i++)
    {
        if (gamestate == 6)
        {
            enemies[i].x = 1400 + rand() % 200;
            enemies[i].y = rand() % 600;
            enemies[i].enemyhealth = 6;
        }
        else
        {
            enemies[i].x = 1250;
            enemies[i].y = (i == 1) ? 20 : 600;
            enemies[i].enemyhealth = 3;
        }
        enemies[i].active = true;
        enemies[i].exist = true;
        enemy_movement[i] = (rand() % 2 == 0) ? -1 : 1;
    }
}
void moveStones()
{
    for (int i = 0; i < MAX_STONES; i++)
    {
        if (!stones[i].stonevisible)
            continue;
        stones[i].x += stones[i].sx * 3;
        stones[i].y += stones[i].sy * 2;
        if (stones[i].y <= 0 || stones[i].y >= 620)
            stones[i].sy *= -1;
        if (stones[i].x < -100 || stones[i].x > 1500)
            stones[i].stonevisible = false;
    }


}

void fireMissile()
{
    if (aavailablemissiles == 0) return;           
    for (int i = 0; i < MAX_MISSILES; ++i)
    {
        if (!missiles[i].active)
        {
            missiles[i].active   = true;
            missiles[i].speed    = 18;
            missiles[i].x        = shipX + 80;    
            missiles[i].y        = shipY + 40;    

           
            int bestDy = 10000;
            int bestY  = missiles[i].y;
            for (int e = 0; e < MAX_ENEMIES; ++e)
                if (enemies[e].exist && enemies[e].active)
                {
                    int dy = abs(enemies[e].y - missiles[i].y);
                    if (dy < bestDy) { bestDy = dy; bestY = enemies[e].y; }
                }
            missiles[i].targety = bestY;

            --aavailablemissiles;
           
            break;
        }
    }
}


void spawnStones()
{
    if (c % 400 == 0 && !stonespwned)
    {
        int spawned = 0;
        for (int i = 0; i < MAX_STONES && spawned < 2; i++)
        {
            if (!stones[i].stonevisible)
            {
                int X = 1400 + rand() % 100;
                int Y = rand() % 700;
                int DY;
                if (Y < 100)
                    DY = 1;
                else if (Y > 600)
                    DY = -1;
                else
                    DY = (rand() % 2 == 0) ? -1 : 1;
                stones[i] = {X, Y, -1, DY, true};
                spawned++;
            }
        }
        stonespwned = true;
    }
    if (c % 450 == 0)
        stonespwned = false;
}
void updateEnemy()
{
    if (gamestate == 3)
    {
        for (int i = 0; i < 2; i++)
        {
            if (enemies[i].active && enemies[i].exist)
            {
                enemies[i].y += enemy_movement[i] * 3;

                if (enemies[i].y >= 640)
                {
                    enemies[i].y = 640;
                    enemy_movement[i] = -1;
                }
                else if (enemies[i].y <= 1)
                {
                    enemies[i].y = 1;
                    enemy_movement[i] = 1;
                }
            }
        }
    }

    else if (gamestate == 6)
    {
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (enemies[i].active && enemies[i].exist)
            {

                enemies[i].x -= 4;

                if (enemies[i].y < shipY)
                    enemies[i].y += 2;
                else if (enemies[i].y > shipY)
                    enemies[i].y -= 2;

                if (enemies[i].x < -100)
                {
                    enemies[i].x = 1400 + rand() % 200;
                    enemies[i].y = rand() % 600;
                }
            }
        }
    }
}
void shootEnemybullet()
{
    if (gamestate == 3)
    {
        for (int j = 0; j < 2; j++)
        {
            if (enemies[j].active && enemies[j].exist)
            {
                for (int i = 0; i < MAX_BULLETS; i++)
                {
                    if (!enemybullets[i].active && enemies[j].exist && enemies[j].active)
                    {
                        enemybullets[i].x = enemies[j].x - 20;
                        enemybullets[i].y = enemies[j].y + 45;
                        enemybullets[i].active = true;
                        break;
                    }
                }
            }
        }
    }
    else if (gamestate == 6)
    {
        for (int j = 0; j < MAX_ENEMIES; j++)
        {
            if (enemies[j].active && enemies[j].exist)
            {
                if (abs(enemies[j].y - shipY) < 40)
                {
                    for (int i = 0; i < MAX_BULLETS; i++)
                    {
                        if (!enemybullets[i].active)
                        {
                            enemybullets[i].x = enemies[j].x;
                            enemybullets[i].y = enemies[j].y + 33;
                            enemybullets[i].active = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}
void updatingPositionOfEnemyBullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (enemybullets[i].active)
        {
            enemybullets[i].x -= 15;
            if (enemybullets[i].x < 0)
            {
                enemybullets[i].active = false;
            }
        }
    }
}
void ShipSurvival()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (enemybullets[i].active)
        {
            if (enemybullets[i].x + 40 >= shipX && enemybullets[i].x <= shipX + 80 && enemybullets[i].y + 20 >= shipY && enemybullets[i].y <= shipY + 80)
            {
                int damage = (gamestate == 6) ? 10 : 5;
                shiphealth -= damage;
                enemybullets[i].active = false;
                 if (shiphealth < 0) {
                    shiphealth = 0;
                }
                if (shiphealth <= 0 && !gameover)
                {  tempscore=score;
                    gameover = true;
                    //gameOverTimer = 10000;
                    enteringName=true;
strcpy(playerName,"");
nameInputIndex=0;
                  for (int i = 0; i <2; i++)
                    {
                        enemies[i].active = false;
                        enemies[i].exist = false;
                        revivinenemytime[i] = 0;
                    }
                    for (int i = 0; i < MAX_STONES; i++)
                        stones[i].stonevisible = false;
                    stonespwned = false;
                    for (int i = 0; i < MAX_BULLETS; i++)
                    {
                        bullets[i].active = false;
                        enemybullets[i].active = false;
                    }

                    gamestate = 4;
                }
            }
        }
    }
}
void StoneCollision()
{
    for (int i = 0; i < MAX_STONES; i++)
    {
        if (stones[i].stonevisible)
        {
            int sx = stones[i].x;
            int sy = stones[i].y;
            bool OX = (sx < shipX + 80) && (sx + 70 > shipX);
            bool OY = (sy < shipY + 80) && (sy + 70 > shipY);
            if (OX && OY)
            {
                shiphealth -= 15;
                if (shiphealth < 0)
                    shiphealth = 0;
                stones[i].stonevisible = false;
            }
        }
    }
}
void SurvivalOfEnemies()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            for (int j = 0; j < MAX_ENEMIES; j++)
            {
                if (enemies[j].active && enemies[j].exist)
                {
                    if (bullets[i].x + 40 >= enemies[j].x && bullets[i].x <= enemies[j].x + 90 && bullets[i].y >= enemies[j].y && bullets[i].y <= enemies[j].y + 90)
                    {
                        // Bullet hit
                        enemies[j].enemyhealth--;
                        bullets[i].active = false;
                        if (enemies[j].enemyhealth <= 0)
                        {
                            enemies[j].exist = false;
                            enemies[j].active = false;
                            revivinenemytime[j] = 50;
                            score += 10;
                        }
                    }
                }
            }
        }
    }
}
/*
void updateMissiles()
{
    for (int i = 0; i < MAX_MISSILES; i++)
    {
        if (!missiles[i].active) continue;

       
        int bestDy = 9999;
        for (int e = 0; e < MAX_ENEMIES; ++e)
            if (enemies[e].exist && enemies[e].active)
            {
                int dy = abs(enemies[e].y - missiles[i].y);
                if (dy < bestDy) { bestDy = dy; missiles[i].targetY = enemies[e].y; }
            }

        
        if      (missiles[i].y <  missiles[i].targetY) missiles[i].y += 4;
        else if (missiles[i].y >  missiles[i].targetY) missiles[i].y -= 4;

       

        
        if (missiles[i].x > 1400) missiles[i].active = false;
    }
}   */


void EnemyRevival()
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!enemies[i].exist && revivinenemytime[i] > 0)
        {
            revivinenemytime[i]--;
            if (revivinenemytime[i] == 0)
            {
                if (gamestate == 6)
                {
                    enemies[i].x = 1400 + rand() % 100;
                    enemies[i].y = rand() % 600;
                    enemies[i].enemyhealth = 12;
                }
                else
                {
                    enemies[i].x = 1250;
                    enemies[i].y = (i == 1) ? 20 : 600;
                    enemies[i].enemyhealth = 3;
                }

                enemies[i].exist = true;
                enemies[i].active = true;
            }
        }
    }
}
void calling_game_functions()
{  //if (isPaused) return;  
    scrollStory();
    if (gamestate == 3)
    {
        c++;

        updateEnemy();
        updateBullets();
        updatingPositionOfEnemyBullets();
        ShipSurvival();
        SurvivalOfEnemies();
        EnemyRevival();
        moveStones();
        spawnStones();
        StoneCollision();
    }
    else if (gamestate == 6)
    {

        updateBullets();
        updateEnemy();
        updatingPositionOfEnemyBullets();
        ShipSurvival();
        SurvivalOfEnemies();
        EnemyRevival();
        updateMissiles();
        updateBlasts();
        if (!healthiitem.visible && rand() % 500 == 0)
        {
            healthiitem.x = 1400;
            healthiitem.y = rand() % 600;
            healthiitem.visible = true;
        }

        if (healthiitem.visible)
        {
            healthiitem.x -= 4;
            if (healthiitem.x < -50)
            {
                healthiitem.visible = false;
            }
        }

        if (healthiitem.visible)
        {
            bool collideX = (healthiitem.x < shipX + 80) && (healthiitem.x + 40 > shipX);
            bool collideY = (healthiitem.y < shipY + 80) && (healthiitem.y + 40 > shipY);
            if (collideX && collideY)
            {
                shiphealth += 20;
                if (shiphealth > 150)
                    shiphealth = 150;
                healthiitem.visible = false;
            }
          

            
for (int m = 0; m < MAX_MISSILES; ++m)
if (missiles[m].active)
{
  
    for (int e = 0; e < MAX_ENEMIES; ++e)
        if (enemies[e].exist && enemies[e].active)
        {
           /* const int ew = 80, eh = 80;                // enemy size
            bool hit =
                missiles[m].x >= enemies[e].x &&
                missiles[m].x <= enemies[e].x + ew &&
                missiles[m].y >= enemies[e].y &&
                missiles[m].y <= enemies[e].y + eh;  */

               const int mw = 175, mh = 50;  // missile size
const int ew =  80, eh = 80;  // enemy size

int mxC = missiles[m].x + mw / 2;
int myC = missiles[m].y + mh / 2;
int exC = enemies[e].x + ew / 2;
int eyC = enemies[e].y + eh / 2;


bool xOverlap = abs(mxC - exC) <= (mw/2 + ew/2);
bool yOverlap = abs(myC - eyC) <= (mh/2 + eh/2);
bool hit = xOverlap && yOverlap;


            if (hit)
            {
                
                const int R2 = 140 * 140;
                for (int k = 0; k < MAX_ENEMIES; ++k)
                    if (enemies[k].exist && enemies[k].active)
                    {
                        int dx = enemies[k].x - enemies[e].x;
                        int dy = enemies[k].y - enemies[e].y;
                        if (dx*dx + dy*dy <= R2)
                        {
                            enemies[k].exist  = false;
                            enemies[k].active = false;
                            revivinenemytime[k] = 100;
                            score += 10;
                          //  printf("Enemy %d destroyed by mis sile %d\n", j, i);
                        }
                    }

                missiles[m].active = false;
              //  iPlaySound("assets/sounds/explosion.wav",0);
                break;  // missile consumed
            }
        }
}

        }


if (!missileitm.visible && rand() % 480 == 0)  
{
    missileitm.visible = true;
    missileitm.x = 1400;
    missileitm.y = rand() % 600;
}

if (missileitm.visible)
{
    missileitm.x -= 4;
    if (missileitm.x < -60)
        missileitm.visible = false;

    bool collideX = (missileitm.x < shipX + 80) && (missileitm.x + 40 > shipX);
    bool collideY = (missileitm.y < shipY + 80) && (missileitm.y + 40 > shipY);
    if (collideX && collideY)
    {
        aavailablemissiles = 3; 
        missileitm.visible = false;
    }
}




    }
    if (gamestate == 4)
    {
       // gameOverTimer--;
        if (gameover)
        {
            resetGame();
           // gamestate = 2;
           gameover = false;
            shiphealth = 150;
            score = 0;
            c = 0;
            stonespwned = false;
            showarenamsg = false;
           arenamsgtimer = 0;
           arenatranssitioned= false;
            arenalevel2 = false;
            // battletheme2play = false;
            // showblaeff=false;
            // blaefftim=0;

            if (battlethemeplaying)
            {
                iStopSound(battlethemeeee );
                battlethemeeee  = -1;
                battlethemeplaying = false;
            }
            if (battletheme2play)
            {
                iStopSound(battletheme2);
                battletheme2 = -1;
                battletheme2play = false;
            }
        }
    }
    if (!arenalevel2 && score >= 200 && !showarenamsg)
    {
        gamestate = 5;
        showarenamsg = true;
       arenamsgtimer = arenamsgdur;
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            enemies[i].active = false;
            enemies[i].exist = false;
        }
        for (int i = 0; i < MAX_STONES; i++)
        {
            stones[i].stonevisible = false;
        }
        stonespwned = false;
        if (battlethemeplaying)
        {
            iStopSound(battlethemeeee );
            battlethemeeee  = -1;
            battlethemeplaying = false;
        }
        iPlaySound("assets/sounds/blast.wav", false, 25);
        iPlaySound("assets/sounds/gs5music.wav", false, 500);
        // showblaeff=true;
        // blaefftim=blaeffdur;
    }
    if (showarenamsg)
    {
        arenamsgtimer--;
        if (arenamsgtimer<= 0 && !arenatranssitioned)
        {

            arenalevel2 = true;
            arenatranssitioned= true;
            showarenamsg = false;
            gamestate = 6;
            spawnenemy();

            /*battletheme2 = iPlaySound("assets/sounds/battletheme2.wav", true, 100);
            battletheme2play = true;
            */

            battlethemeplaying= false;
        }
        return;
    }
    /*if (showblaeff) {
        blaefftim--;
        if (blaefftim <= 0) {
            showblaeff = false;
        }
    }*/

    // if (gamestate == 5 ) {

    /*  if (arenaMessageTimer <= 0 && !arenaTransitioned) {


          arenalevel2 = true;
          arenaTransitioned = true;
          showArenaMessage = false;
          gamestate = 3;
          spawnEnemy();
      } */
    //}

    if (Paused) return;  
}
// void Calling_stones(){
// spawnStones();
// moveStones();
//}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    loadResources();
    iInitializeSound();
    bgSoundIdx = iPlaySound("assets/sounds/background.wav", true, 100);
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].active = false;
        enemies[i].exist = false;
        enemies[i].enemyhealth = 0;
        revivinenemytime[i] = 0;
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].active = false;
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        enemybullets[i].active = false;
    }
    healthiitem.visible = false;
    healthiitem.x = -100;
    healthiitem.y = -100;
    missileitm.visible = false;
    missileitm.x = -100;
    missileitm.y = -100;

    iSetTimer(20, calling_game_functions);
    iSetTimer(100, shootBullet);
    iSetTimer(450, shootEnemybullet);
    iInitialize(1400, 700, "SPACE SHOOTER");
    return 0;
}