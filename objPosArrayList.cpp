#include "objPosArrayList.h"



objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];  
    Sizeoflist = 0;                       
    Sizeofarray = ARRAY_MAX_CAP;      
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; 
}

int objPosArrayList::getSize()
{
    return Sizeoflist;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    {
    for (int i = Sizeoflist; i >0; i--)
    {
        aList[i] = aList[i -1];
    }
    aList[0] = thisPos;
    aList[0].symbol = thisPos.symbol;
    Sizeoflist++;

}

}

void objPosArrayList::insertTail(objPos thisPos)
{
    
    aList[Sizeoflist] = thisPos; 
    Sizeoflist++;
}

void objPosArrayList::removeHead()
{
    if (Sizeoflist > 0) 
    {
        
        for (int i = 0; i < Sizeoflist - 1; ++i) 
        {
            aList[i] = aList[i + 1];
        }
        Sizeoflist++;
    }
}


void objPosArrayList::removeTail()
{
    if (Sizeoflist > 0) 
    {
        Sizeoflist--; 
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if (Sizeoflist > 0) 
    {
        returnPos = aList[0]; 
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (Sizeoflist > 0) 
    {returnPos = aList[Sizeoflist - 1]; }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < Sizeoflist) 
    {returnPos = aList[index]; }
}