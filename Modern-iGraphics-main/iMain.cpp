  
#include "iGraphics.h"
#include <iostream>
#include "iSound.h"
using namespace std;
Image bg;
Image sp, EnemyShip;
Image HP;
Image HP2;
Image storyBG;
Image bullet, enemyBullet;
Image SforHealth;
Image Healthbar;
Image Stoneimg;
Image bg2;
Image InstructionPage;
Image Enemyshipf2;
Image Enemybulletf2;
Image Healthitem;
int speed = -10;
int shipX = 50;
int shipY = 200;
int gamestate = 0;
int shiphealth = 100;
int mx, my;
int bgSoundIdx = -1;
int BattleTheme = -1;
int Storytheme = -1;
bool BattleThemePlaying = false;
bool StorythemePlaying = false;
int c = 1, score = 0;
bool gameOver = false;
int gameOverTimer = 0;
int battletheme2=-1;
void spawnEnemy();
bool arenalevel2=false;
bool battletheme2play=false;
bool showArenaMessage = false;
int arenaMessageTimer = 0;
const int arenaMessageDuration = 200; 
bool arenaTransitioned = false;
int gs5music=-1;
//bool showblaeff=false;
//int blaefftim=0;
//const int blaeffdur=5;
     // 0 to 5
     // For timing each phase

     int k=0;
     int p=0;


struct Bullet
{
    int x, y;
    bool active;
};
struct EnemyBullet
{
    int x, y;
    bool active;
};
struct Enemy
{
    int x, y;
    int enemyHealth;
    bool exist;
    bool active;
};
struct HealthItem {
    int x, y;
    bool visible;
};
HealthItem healthItem;

//Enemy enemies[2];
//int enemy_movement[2] = {-1, 1}; 

//int RevivingEnemyTimer[2] = {0};
#define MAX_ENEMIES 4
Enemy enemies[MAX_ENEMIES];
int enemy_movement[MAX_ENEMIES] = { -1, 1, 1, -1 };
int RevivingEnemyTimer[MAX_ENEMIES] = {0};


const int MAX_BULLETS = 100;
Bullet bullets[MAX_BULLETS];

EnemyBullet enemybullets[MAX_BULLETS];
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
string storyLines[] = {
    "2405100                                                                          2405099",
    "SECTION-B                                                                  SECTION-B",
    "DEPARTMENT-CSE                                                     DEPARTMENT-CSE",
    "AJMAIN FAYEK DIGANTA                                           PROTTOY BARUA",
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
int totalLines = sizeof(storyLines) / sizeof(storyLines[0]);
float storyY = -30 * totalLines + 300; 
float scrollSpeed = .5;
bool scrolling = true;
void loadResources()
{
    iLoadImage(&sp, "assets/images/Ship6.png");
    iResizeImage(&sp, 80, 80);
    iLoadImage(&EnemyShip, "assets/images/Enemy.png"); 
    iResizeImage(&EnemyShip, 90, 90);                  
    iLoadImage(&bullet, "assets/images/bullet.png"); 
    iResizeImage(&bullet, 40, 15);
    iLoadImage(&enemyBullet, "assets/images/EnemyBullet.png");
    iResizeImage(&enemyBullet, 40, 20); 
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
    iResizeImage(&bg2,1400,700);
     iLoadImage(&InstructionPage, "assets/images/InstructionsPage.png");
    iResizeImage(&InstructionPage, 1400, 700);
iLoadImage(&Enemyshipf2,"assets/images/Enemyshipf2.png");
 iResizeImage(&Enemyshipf2, 80, 80);

 iLoadImage(&Enemybulletf2,"assets/images/Enemybulletf2.png");
 iResizeImage(&Enemybulletf2, 60, 20);

 iLoadImage(&Healthitem,"assets/images/Healthitem.png");
 iResizeImage(&Healthitem, 150, 80);



    }
void scrollStory()
{
    if (gamestate == 1 && scrolling)
    {
        storyY += scrollSpeed;
        if (storyY >= 390)
        {
            scrolling = false;
        }
    }
}

void iDraw()
{
   k++;

    iClear();
    
  


if (gamestate == 1 || gamestate == 2 || gamestate ==7) {
    if (!StorythemePlaying || Storytheme == -1) {
        Storytheme = iPlaySound("assets/sounds/Storytheme.wav", true, 150);
        StorythemePlaying = (Storytheme != -1);
    }
} else if (StorythemePlaying) {
    iStopSound(Storytheme);
    Storytheme = -1;
    StorythemePlaying = false;
}


if ((gamestate == 3 || gamestate == 4) && !BattleThemePlaying) {
    BattleTheme = iPlaySound("assets/sounds/Battle.wav", true, 150);
    BattleThemePlaying = (BattleTheme != -1);
} else if ((gamestate != 3 && gamestate != 4) && BattleThemePlaying) {
    iStopSound(BattleTheme);
    BattleTheme = -1;
    BattleThemePlaying = false;
}


if (gamestate == 6 && !battletheme2play) {
    battletheme2 = iPlaySound("assets/sounds/battletheme2.wav", true, 150);
    battletheme2play = (battletheme2 != -1);
} else if (gamestate != 6 && battletheme2play) {
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
        
        int y = storyY;
        for (int i = 0; i < totalLines; i++)
        {
            if (y >= 220 && y <= 490)
            {
                iTextBold(350, y, storyLines[i].c_str(), GLUT_BITMAP_HELVETICA_18);
            }
            y += 30;
        }
    }
    else if (gamestate == 2)
    {
        iShowLoadedImage(0, 0, &HP2);
    }
    else if (gamestate == 3)
    {
        if(arenalevel2){
        iShowLoadedImage(0,0,&bg2);
iWrapImage(&bg2,speed);
    }
    else{
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
                iShowLoadedImage(enemybullets[i].x, enemybullets[i].y, &enemyBullet);
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
        iText(40, 650, scoreText,  GLUT_BITMAP_TIMES_ROMAN_24);
        
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
    {if(score<=200){
        iShowLoadedImage(0, 0, &bg);
        iWrapImage(&bg, speed);
        iSetColor(255, 0, 0);

    }

    else {
 iShowLoadedImage(0, 0, &bg2);
        iWrapImage(&bg2, speed);
        iSetColor(255, 0, 0);



    }
        
        iText(600, 350, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
        char scoreText[50];
        sprintf(scoreText, "Your Score: %d", score);
        iSetColor(255, 255, 255);
        iText(600, 300, scoreText, GLUT_BITMAP_HELVETICA_18);
        // iText(600, 250, "Press Enter to Restart", GLUT_BITMAP_HELVETICA_18);
    }
    // iText(140, 180, "Hello World");
else if(gamestate==5){

p++;



iShowLoadedImage(0,0,&bg);
iWrapImage(&bg,speed);
iShowLoadedImage(shipX, shipY, &sp);


  /* if (showblaeff) {
    iSetTransparentColor(255,255,255,.9); 
    iFilledRectangle(0, 0, 1400, 700); 
}

*/


if(p>=340) {
    iSetColor(255,255,255);
    iFilledRectangle(0, 0, 1400, 700); 
}
   
if(k%10==0){
iSetTransparentColor(255,255,255,1); 
    iFilledRectangle(0, 0, 1400, 700); 
}

if (showArenaMessage) {
    iSetColor(255, 255, 0);
    iText(600, 350, "Game Arena Changing...", GLUT_BITMAP_TIMES_ROMAN_24);
    return; }




}



else if(gamestate==6){
   // iStopSound(gs5music);
iShowLoadedImage(0,0,&bg2);
iWrapImage(&bg2,speed);

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
    if (enemies[i].active && enemies[i].exist) {
        iShowLoadedImage(enemies[i].x, enemies[i].y, &Enemyshipf2);
    }
}


if (healthItem.visible) {
    iShowLoadedImage(healthItem.x, healthItem.y, &Healthitem);
}



for (int i = 0; i < MAX_BULLETS; i++) {
    if (enemybullets[i].active) {
        iShowLoadedImage(enemybullets[i].x, enemybullets[i].y, &Enemybulletf2);
    }
}



        if (shipX < 0)
            shipX = 0;
        if (shipX > 1320)
            shipX = 1320;
        if (shipY < 0)
            shipY = 0;
        if (shipY > 620){
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
        iText(40, 650, scoreText,  GLUT_BITMAP_TIMES_ROMAN_24);


}

  else if (gamestate == 7)
    {
        iShowLoadedImage(0, 0, &InstructionPage);
    }



}

void resetGame() {
    shipX=50;
    shipY=200;
    shiphealth = 150;
    score = 0;
    c = 0;
    p=0;
    stonespwned = false;

    showArenaMessage = false;
    arenaMessageTimer = 0;
    arenaTransitioned = false;
    arenalevel2 = false;
    //showblaeff = false;
    //blaefftim = 0;

    // Stop sounds
    if (BattleThemePlaying) {
        iStopSound(BattleTheme);
        BattleTheme = -1;
        BattleThemePlaying = false;
    }
    if (battletheme2play) {
        iStopSound(battletheme2);
        battletheme2 = -1;
        battletheme2play = false;
    }

    // Reset bullets, enemies, stones
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
        enemybullets[i].active = false;
    }
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;
        enemies[i].exist = false;
        RevivingEnemyTimer[i] = 0;
    }
    for (int i = 0; i < MAX_STONES; i++) {
        stones[i].stonevisible = false;
    }
}



/*
function iMouseMove() is called when the user moves the mouse.
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
                storyY = -30 * totalLines + 300;
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
                spawnEnemy();
                shiphealth = 150;
                
                
                for (int i = 0; i < MAX_BULLETS; i++)
                {
                    bullets[i].active = false;
                    enemybullets[i].active = false;
                }
            } 
            if (mx >= 1 && mx <= 91 && my >= 615 && my <= 700) 
            {
                gamestate = 1;
                scrolling=true;
                 storyY = -30 * totalLines + 300;
            }

             if (mx >= 385 && mx <= 825 && my >= 380 && my <= 485)
            {
                gamestate = 7;
            }

        }


       /* else if(gamestate==2){
        if (mx >= 385 && mx <= 825 && my >= 380 && my <= 485)
            {
                gamestate = 7;
            }

        } */


        else if(gamestate ==7){
 if (mx >= 1 && mx <= 91 && my >= 615 && my <= 700) 
            {
                gamestate = 2;
            }



        }



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
    if (gamestate == 0)
    {
        if (key == '\r') 
        {
            gamestate = 1;
        }
    }
    if (gamestate == 2)
    {
        if (key == '\b') 
        {
            gamestate = 1;
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
void spawnEnemy()
{
     int limit = (gamestate == 6) ? MAX_ENEMIES : 2;
    for (int i = 0; i < limit; i++) {
        if (gamestate == 6) {
            enemies[i].x = 1400 + rand() % 200;
            enemies[i].y = rand() % 600;
            enemies[i].enemyHealth = 6;
        } else {
            enemies[i].x = 1250;
            enemies[i].y = (i == 1) ? 20 : 600;
            enemies[i].enemyHealth = 3;
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
void spawnStones()
{
    if (c % 550 == 0 && !stonespwned)
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
    if (c % 600 == 0)
        stonespwned = false;
}
void updateEnemy()
{
    if(gamestate==3)
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


else if (gamestate == 6) {
   for (int i = 0; i < MAX_ENEMIES; i++)
 {
        if (enemies[i].active && enemies[i].exist) {
          
            enemies[i].x -= 4;

           
            if (enemies[i].y < shipY) enemies[i].y += 2;
            else if (enemies[i].y > shipY) enemies[i].y -= 2;

     
            if (enemies[i].x < -100) {
                enemies[i].x = 1400 + rand() % 200;
                enemies[i].y = rand() % 600;
            }
        }
    }
}


}
void shootEnemybullet()
{
    if(gamestate==3){
    for (int j = 0; j < 2; j++)
    {
      if (enemies[j].active && enemies[j].exist)
        {
            for (int i = 0; i < MAX_BULLETS; i++)
       {
                if (!enemybullets[i].active && enemies[j].exist && enemies[j].active)
                {
               enemybullets[i].x = enemies[j].x-20;      
               enemybullets[i].y = enemies[j].y + 45; 
                    enemybullets[i].active = true;
             break;
                }
            }
        }
    }
}

else if (gamestate == 6) {
    for (int j= 0; j < MAX_ENEMIES; j++)
 {
    if (enemies[j].active && enemies[j].exist) {
            if (abs(enemies[j].y - shipY) < 40) {  
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!enemybullets[i].active) {
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
                if (shiphealth <= 1 && !gameOver)
                {
                    gameOver = true;
                    gameOverTimer = 250;
                    for (int i = 0; i < 2; i++)
                    {
                        enemies[i].active = false;
                        enemies[i].exist = false;
                        RevivingEnemyTimer[i] = 0;
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
                        enemies[j].enemyHealth--;
                        bullets[i].active = false;
                        if (enemies[j].enemyHealth <= 0)
                        {
                            enemies[j].exist = false;
                            enemies[j].active = false;
                            RevivingEnemyTimer[j] = 50; 
                            score += 10;                
                        }
                    }
                }
            }
        }
    }
}
void EnemyRevival()
{
    for (int i = 0; i < MAX_ENEMIES; i++)

    {
        if (!enemies[i].exist && RevivingEnemyTimer[i] > 0)
        {
            RevivingEnemyTimer[i]--;
            if (RevivingEnemyTimer[i] == 0)
            {
               if (gamestate == 6) {
    enemies[i].x = 1400 + rand() % 100;
    enemies[i].y = rand() % 600;
enemies[i].enemyHealth = 12;

} else {
    enemies[i].x = 1250;
    enemies[i].y = (i == 1) ? 20 : 600;
    enemies[i].enemyHealth = 3;

}

                
                enemies[i].exist = true;
                enemies[i].active = true;
            }
        }
    }
}
void calling_game_functions()

{
       scrollStory();
    if (gamestate == 3){
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

else if(gamestate==6){
    
 updateBullets();
  updateEnemy();
  updatingPositionOfEnemyBullets();
  ShipSurvival();
  SurvivalOfEnemies();
    EnemyRevival();

    if (!healthItem.visible && rand() % 500 == 0) {
        healthItem.x = 1400;
        healthItem.y = rand() % 600;
        healthItem.visible = true;
    }


    if (healthItem.visible) {
        healthItem.x -= 4;
        if (healthItem.x < -50) {
            healthItem.visible = false;
        }
    }


    if (healthItem.visible) {
        bool collideX = (healthItem.x < shipX + 80) && (healthItem.x + 40 > shipX);
        bool collideY = (healthItem.y < shipY + 80) && (healthItem.y + 40 > shipY);
        if (collideX && collideY) {
            shiphealth += 20;
            if (shiphealth > 150) shiphealth = 150;
            healthItem.visible = false;
        }
    }
    
}

    if (gamestate == 4)
    {
        gameOverTimer--;
        if (gameOverTimer <= 0)
        {
            resetGame();
            gamestate = 2;
            gameOver = false;
            shiphealth = 150;
            score = 0;
            c=0;
            stonespwned=false;
showArenaMessage = false;
    arenaMessageTimer = 0;
    arenaTransitioned = false;
    arenalevel2 = false;
   // battletheme2play = false;
   //showblaeff=false;
   //blaefftim=0;
           
if (BattleThemePlaying) {
    iStopSound(BattleTheme);
    BattleTheme = -1;
    BattleThemePlaying = false;
}

if (battletheme2play) {
    iStopSound(battletheme2);
    battletheme2 = -1;
    battletheme2play = false;
}
        }
    }
if (!arenalevel2 && score >= 200 && !showArenaMessage) {
   gamestate=5;
    showArenaMessage = true;
    arenaMessageTimer = arenaMessageDuration;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;
        enemies[i].exist = false;
    }
    for (int i = 0; i < MAX_STONES; i++) {
        stones[i].stonevisible = false;
    }
    stonespwned = false;

   if (BattleThemePlaying) {
        iStopSound(BattleTheme);
        BattleTheme=-1;
        BattleThemePlaying = false;
    }
iPlaySound("assets/sounds/blast.wav", false, 25) ;  
iPlaySound("assets/sounds/gs5music.wav", false, 500) ;  
 //showblaeff=true;
 //blaefftim=blaeffdur;

 
   
}
if (showArenaMessage) {
    arenaMessageTimer--;
    if (arenaMessageTimer <= 0 && !arenaTransitioned) {
      
        
        arenalevel2 = true;
        arenaTransitioned = true;
        showArenaMessage = false;
      gamestate=6;
        spawnEnemy();
      
        /*battletheme2 = iPlaySound("assets/sounds/battletheme2.wav", true, 100);
        battletheme2play = true;
        */
       
        BattleThemePlaying=false;
          
    }
    return;
}

/*if (showblaeff) {
    blaefftim--;
    if (blaefftim <= 0) {
        showblaeff = false;
    }
}*/




//if (gamestate == 5 ) {
  

    

 
  /*  if (arenaMessageTimer <= 0 && !arenaTransitioned) {
      
       
        arenalevel2 = true;
        arenaTransitioned = true;
        showArenaMessage = false;
        gamestate = 3;
        spawnEnemy();
    } */
//}





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
    enemies[i].enemyHealth = 0;
    RevivingEnemyTimer[i] = 0;
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].active = false;
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        enemybullets[i].active = false;
    }
    healthItem.visible = false;
healthItem.x = -100; 
healthItem.y = -100;

    iSetTimer(20, calling_game_functions);
    iSetTimer(100, shootBullet);
    iSetTimer(250, shootEnemybullet);
    iInitialize(1400, 700, "SPACE SHOOTER");
    return 0;
}
