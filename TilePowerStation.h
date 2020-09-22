/**
* \file Tilepowerstation.h
*
* \author Junshan Luo
*
* \brief Class that implements a Power station tile
*/#pragma once
#include "Tile.h"
#include "TileCoalmine.h"
#include "ChildView.h"

/**
* \brief A Power station tile
*/
class CTilePowerStation : public CTile
{
public:
	//constructor
	CTilePowerStation(CCity *city);

	/// \brief Default constructor (disabled)
	CTilePowerStation() = delete;

	/// \brief Copy constructor (disabled)
	CTilePowerStation(const CTilePowerStation &) = delete;
	
	//destructor
	~CTilePowerStation();
	//xml save function
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	//xml load function
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitPowerStation(this); }

};

