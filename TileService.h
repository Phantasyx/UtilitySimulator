#pragma once
/**
* \file TileService.h
* \author Robin Miller
* Defines a service providing tile
**/
#include "TileBuilding.h"

/** Defines a service providing tile */
class CTileService : public CTileBuilding
{
public:
	CTileService(CCity* city);
	virtual ~CTileService();	

	std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** Apply this to the visitor
	* \param visitor the visitor to apply ourselves to
	**/
	void Accept(CTileVisitor* visitor) override { visitor->VisitService(this); }

	/** Gets the amount of labor serivced
	* \return the amount of service available
	**/
	int GetAvailableService() const { return mAvailableService; };

	/** Sets the amount of labor produced by this source
	* \param service the number of workers available.
	**/
	void SetAvailableService(int service){ mAvailableService = service; };
private:

	int mAvailableService;

};

