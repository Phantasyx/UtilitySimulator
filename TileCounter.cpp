/**
* \file TileCounter.cpp
*
* \author Jordan Hill
*/

#include "stdafx.h"
#include "TileCounter.h"
#include <vector>
#include "Tile.h"
#include "City.h"


using namespace std;
/*
* Constructor
*/
CTileCounter::CTileCounter(CCity* city) : mCity(city)
{
	
}

/*
* deconstructor
*/
CTileCounter::~CTileCounter()
{
}
/*
* visits tile and accounts for 
*/
void CTileCounter::Visit(CTile* v)
{
	++mNumTiles;
	std::vector<std::shared_ptr<CTile> > mV, mV2;

	auto top    = mCity->GetAdjacent(v,  1,  0);
	auto bottom = mCity->GetAdjacent(v,  0, -1);
	auto left   = mCity->GetAdjacent(v, -1,  0);
	auto right  = mCity->GetAdjacent(v, -0, 1);

	
	if (top != nullptr || bottom != nullptr || left != nullptr || right != nullptr)
	{
		++mPartTiles; 
	}
	

	for (auto tile : *mCity)
	{
		mV.push_back(tile);
	}

	mV2 = mV;

	for (int i = 0,j=1; i < mV.size() - j; i++,j++)
	{
		if (mV[i]->GetX() == mV2[i + 1]->GetX() &&
			mV[i]->GetY() == mV2[i + 1]->GetY())
		{
			mFullTiles++;
		}
	}
	
}
