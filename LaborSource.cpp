/**
* \author Robin Miller
* \file LaborSource.cpp
**/

#include "stdafx.h"
#include "LaborSource.h"
#include "City.h"

/** Constructor creates a new labor sink
* \param city the city this tile is is in.
*/
CLaborSource::CLaborSource(CCity* city) : CTileBuilding(city)
{
	SetZoning(CTile::Zonings::RESIDENTIAL);
}

/** Destructor **/
CLaborSource::~CLaborSource()
{
}

/** Saves to xml
* \param node the xml node to save to
*/
std::shared_ptr<xmlnode::CXmlNode> CLaborSource::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileBuilding::XmlSave(node);
	node->SetAttribute(L"type", L"labor-sink");
	node->SetAttribute(L"available-labor", mAvailableLabor);

	return node;
}

/** Loads from xml
* \param node the xml node to load from
*/
void CLaborSource::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileBuilding::XmlLoad(node);
	mAvailableLabor = node->GetAttributeIntValue(L"available-labor", mAvailableLabor);
}
