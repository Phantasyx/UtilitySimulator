/**
* \file TilePowerStation.cpp
*
* \author Junshan Luo
*
*/
#include "stdafx.h"
#include "TilePowerStation.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param city The city this is a member of
*/
CTilePowerStation::CTilePowerStation(CCity *city) : CTile(city)
{
}

/**
* \brief Destructor
*/
CTilePowerStation::~CTilePowerStation()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTilePowerStation::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"building");
	itemNode->SetAttribute(L"file", GetFile());

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTilePowerStation::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L""));
}


