#include "stdafx.h"

#include "TileVisitor.h"

#include "TileBuilding.h"
#include "TileCoalmine.h"
#include "TileLandscape.h"
#include "TileRoad.h"
#include "LaborSource.h"
#include "LaborSink.h"
#include "TileService.h"
#include "TilePower.h"
#include "TileConstruction.h"
#include "TilePowerStation.h"

/**
* \file TileVisitor.h
*
* \author Robin Miller
* Tile visitor implementation.
*/

/** Empty Constuctor */
CTileVisitor::CTileVisitor()
{
}

/** Empty Destructor */
CTileVisitor::~CTileVisitor()
{
}
/** Visit a CTileBuilding object
* \param building Building we are visiting */
void CTileVisitor::VisitBuilding(CTileBuilding *building) 
{
	Visit(building);
}

/** Visit a CTileCoalmine object
* \param coalmine Coal mine we are visiting */
void CTileVisitor::VisitCoalmine(CTileCoalmine *coalmine)
{
	Visit(coalmine);
}

/** Visit a CTileLandscape object
* \param landscape Landscape tile we are visiting */
void CTileVisitor::VisitLandscape(CTileLandscape *landscape)
{
	Visit(landscape);
}

/** Visit a CTileRoad object
* \param road Road we are visiting */
void CTileVisitor::VisitRoad(CTileRoad *road)
{
	Visit(road);
}

/** Visit a CLaborSink object
* \param road sink we are visiting */
void CTileVisitor::VisitLaborSink(CLaborSink *road)
{
	Visit(road);
}

/** Visit a CLaborSource object
* \param road source we are visiting */
void CTileVisitor::VisitLaborSource(CLaborSource *road)
{
	Visit(road);
}

/** Visit a CTileService object
* \param road source we are visiting */
void CTileVisitor::VisitService(CTileService *service)
{
	Visit(service);
}

/** Visit a CTileRoad object
* \param road Road we are visiting */
void CTileVisitor::VisitPower(CTilePower *Power)
{
	Visit(Power);
}

/** Visit a CTileConstruction object
* \param site we are visiting */
void CTileVisitor::VisitConstruction(CTileConstruction *site)
{
	Visit(site);
}

/** Visit a CTileRoad object
* \param road Road we are visiting */
void CTileVisitor::VisitPowerStation(CTilePowerStation *PowerStation)
{
	Visit(PowerStation);
}