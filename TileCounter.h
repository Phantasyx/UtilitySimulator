/**
* \file TileCounter.h
*
* \author Jordan Hill
*
*
*/

#pragma once
#include "TileVisitor.h"

#include <vector>
#include <memory>
/*
*
* Calls instance of the city class
*/
class CCity;
/*
* Counts instances of tiles
*
*/
class CTileCounter : public CTileVisitor
{
public:
	/*
	* constructior
	*
	*/
	CTileCounter(CCity* city);
	/*
	* destructor
	*
	*/
	virtual ~CTileCounter();
	/** Get the number of tiles
	* \returns Number of tiles */
	int GetNumTiles() const { return mNumTiles; }
	
	/** Get the number of tiles
	* \returns Number of tiles */
	int GetPartTiles() const { return mPartTiles; }
	/** Get the number of tiles
	* \returns Number of tiles */
	int GetFullTiles() const { return mFullTiles; }



	/** Visit a CTileBuilding object
	* \param building Building we are visiting */
	virtual void Visit(CTile *tile);

	
private:
	/// tiles counter
	int mNumTiles = 0; /// total number of tiles
	int mPartTiles = 0;/// number of partial tiles 
	int mFullTiles = 0; /// number of fulling overlapping tiles
	CCity* mCity; /// city object

};