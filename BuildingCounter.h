/** 
* \file: BuildingCounter.h
*
* \author: Robin Miller
* 
* Defines a small visitor class for counting buildings. 
**/

#pragma once

#include "TileVisitor.h"

class CBuildingCounter : public CTileVisitor
{
public:
	CBuildingCounter();

	virtual ~CBuildingCounter();

	/** Get the number of buildings
	* \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }


	/** Visit a CTileBuilding object
	* \param building Building we are visiting */
	void CBuildingCounter::VisitBuilding(CTileBuilding *building)
	{
		mNumBuildings++;
	}

private:
	/// Buildings counter
	int mNumBuildings = 0;
};

