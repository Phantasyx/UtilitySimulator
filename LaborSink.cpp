/**
* \author Robin Miller
* \file LaborSink.cpp
**/

#include "stdafx.h"
#include "LaborSink.h"

/** Constructor creates a new labor sink
* \param city the city this tile is is in. 
*/
CLaborSink::CLaborSink(CCity* city) : CTileBuilding(city) 
{
	SetZoning(CTile::Zonings::INDUSTRIAL);
}

/** Destructor **/
CLaborSink::~CLaborSink()
{
}

/** Saves to xml
* \param node the xml node to save to 
*/
std::shared_ptr<xmlnode::CXmlNode> CLaborSink::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) 
{
	CTileBuilding::XmlSave(node);
	node->SetAttribute(L"type", L"labor-sink");
	node->SetAttribute(L"required-labor", mRequiredLabor);

	return node;
}

/** Loads from xml
* \param node the xml node to load from
*/
void CLaborSink::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileBuilding::XmlLoad(node);
	mRequiredLabor = node->GetAttributeIntValue(L"required-labor", mRequiredLabor);
}