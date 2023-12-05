#include "Player.h"
#include <iostream>

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,
                    mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    
    char input = mainGameMechsRef->getInput();
    bool exitFlag = mainGameMechsRef->getExitFlagStatus();

    if (input != 0) // if not null character
    {
        switch(input)
        {                      
        
            case ' ':  // exit
                mainGameMechsRef->setExitTrue();  
                break;

            //Movement inputs:
            case 'w':
            case 'W':
                if(myDir != UP && myDir != DOWN) {
                    myDir = UP;
                }
                break;

            case 's':
            case 'S':
                if(myDir != UP && myDir != DOWN) {
                    myDir = DOWN;
                }
                break;


            case 'a':
            case 'A':
                if(myDir != LEFT && myDir != RIGHT) {
                    myDir = LEFT;
                }
                break;

            case 'd':
            case 'D':
                if(myDir != LEFT && myDir != RIGHT) {
                    myDir = RIGHT;
                }
                break;
            
            default:
                break;
        }
        input = 0;
        }

}

void Player::movePlayer()
{
    
    objPos currentHead;        
    playerPosList->getHeadElement(currentHead);            

    switch(myDir) {

        case UP:
            currentHead.y--;               
            if (currentHead.y < 1) {                                               
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case DOWN:
            currentHead.y++;               
            if (currentHead.y >= mainGameMechsRef->getBoardSizeY()) {
                currentHead.y = 1;
            }
            break;

        case LEFT:
            currentHead.x--;               
            if (currentHead.x < 1) {
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;

        case RIGHT:
            currentHead.x++;               
            if (currentHead.x >= mainGameMechsRef->getBoardSizeX()) {
                currentHead.x = 1;
            }
            break;

        case STOP:
        default:
            break;
    }
    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}
