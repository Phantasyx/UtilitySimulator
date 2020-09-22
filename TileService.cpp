#include "stdafx.h"
#include "TileService.h"

/** Constructor **/
CTileService::CTileService(CCity* city) : CTileBuilding(city)
{
}

/** Destructor */
CTileService::~CTileService()
{
}

/** Saves to xml
* \param node the xml node to save to
*/
std::shared_ptr<xmlnode::CXmlNode> CTileService::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileBuilding::XmlSave(node);
	node->SetAttribute(L"type", L"service");
	node->SetAttribute(L"service", mAvailableService);

	return node;
}

/** Loads from xml
* \param node the xml node to load from
*/
void CTileService::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileBuilding::XmlLoad(node);
	mAvailableService = node->GetAttributeIntValue(L"service", mAvailableService);
}