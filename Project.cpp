#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"

#define WIDTH 30
#define HEIGHT 15

using namespace std;

#define DELAY_CONST 100000

GameMechs *myGame = new GameMechs();
Player *myplayer = new Player(myGame); 
objPos playerElement{0, 0, 0};
objPosArrayList *playerPos;
objPos foodPos;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();
    while (!myGame->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = myGame->getExitFlagStatus();
    myGame->generateFood(foodPos);
    myGame->getFoodPos(foodPos);
}

void GetInput(void)
{
   myGame-> getInput();
}

void RunLogic(void)
{
    myplayer->updatePlayerDir();
    myplayer->movePlayer();   

    objPosArrayList *playerPosList = myplayer->getPlayerPos(); // get the playerPosList

    objPos headPos;
    playerPosList->getHeadElement(headPos);

    
    if (headPos.isPosEqual(&foodPos))
    {
        myGame->generateFood(foodPos);
        myGame->getFoodPos(foodPos);
        myGame->incrementScore(); 

    } 
}

void DrawScreen(void)
{
    // prints and updates score (for every loop)
    cout << "Current Score: " << myGame->getScore() << endl;

    //prints rest of screen elements
    cout << "==============================" << endl;
    cout << "jason & Cale's Final Project" << endl;
    cout << "Board Size: " << myGame->getBoardSizeX() << " X " << myGame->getBoardSizeY() << endl;

    
    MacUILib_clearScreen();

    
    objPosArrayList *drawBoardList = myplayer->getPlayerPos();
    objPos currentIndex;
    objPos drawBoard{0, 0, 0};

    
    bool hasRun = false;

    for (drawBoard.y = 0; drawBoard.y < HEIGHT; (drawBoard.y)++)
    {
        for (drawBoard.x = 0; drawBoard.x < WIDTH; (drawBoard.x)++)
        {
            hasRun = false;

            
            if (drawBoard.x == 0 || drawBoard.x == WIDTH - 1 || drawBoard.y == 0 || drawBoard.y == HEIGHT - 1 && hasRun == false)
            {
                MacUILib_printf("%c", '#');
               
                hasRun = true;
            }

            else if (drawBoard.isPosEqual(&foodPos) && hasRun == false)
            {
                MacUILib_printf("%c", foodPos.getSymbol());
                hasRun = true;
            }

            
            for (int i = 0; i < drawBoardList->getSize(); i++)
            {
                drawBoardList->getElement(currentIndex, i);
                if (drawBoard.isPosEqual(&currentIndex) && hasRun == false)
                {
                    MacUILib_printf("%c", currentIndex.getSymbol());
                    hasRun = true;
                }
            }

            
            if (drawBoard.x >= 1 && drawBoard.y < HEIGHT - 1 && hasRun == false)
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("%c", '\n');
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
  
    MacUILib_uninit();
    delete myGame;
    delete myplayer;
}
