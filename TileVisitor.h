/**
* \file TileVisitor.h
*
* \author Robin Miller (based on template by Dr. Charles B. Owen)
*
* Tile visitor base class.
*/

#pragma once

// Forward references to all tile types
class CTileBuilding;
class CTileCoalmine;
class CTileLandscape;
class CTileRoad;
class CTileConstruction;

class CLaborSource;
class CLaborSink;
class CTileService;

class CTile;
class CTilePower;
class CTileSmallHousing;
class CTileBigHousing;
class CTilePowerStation;
/** Tile visitor base class */
class CTileVisitor
{
public:
	CTileVisitor();
	virtual ~CTileVisitor();

	/** Visit a CTile object
	* \param tile Tile we are visiting */
	virtual void Visit(CTile *tile) {}

	/** Visit a CTileBuilding object
	* \param building Building we are visiting */
	virtual void VisitBuilding(CTileBuilding *building);

	/** Visit a CTileCoalmine object
	* \param coalmine Coal mine we are visiting */
	virtual void VisitCoalmine(CTileCoalmine *coalmine);

	/** Visit a CTileLandscape object
	* \param landscape Landscape tile we are visiting */
	virtual void VisitLandscape(CTileLandscape *landscape);

	/** Visit a CTileRoad object
	* \param road Road we are visiting */
	virtual void VisitRoad(CTileRoad *road);

	/** Visit a CTileRoad object
	* \param road Road we are visiting */
	virtual void VisitPower(CTilePower *Power);

	/** Visit a CTileConstruction object
	* \param site we are visiting */
	virtual void VisitConstruction(CTileConstruction *site);

	/** Visit a CTileRoad object
	* \param road Road we are visiting */
	virtual void VisitPowerStation(CTilePowerStation *PowerStation);

	/** Visit a CLaborSink object
	* \param road sink we are visiting */
	virtual void VisitLaborSink(CLaborSink *road);

	/** Visit a CLaborSource object
	* \param road source we are visiting */
	virtual void VisitLaborSource(CLaborSource *road);

	/** Visit a CTileService object
	* \param road source we are visiting */
	virtual void VisitService(CTileService *service);
};

