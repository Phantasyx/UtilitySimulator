/**
* \file TileCoalmine.h
*
* \author Charles B. Owen
*
* \brief Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"
//#include "LaborSink.h"


/**
* \brief A Landscape tile
*/
class CTileCoalmine : public CTile
{
public:
    CTileCoalmine(CCity *city);

    /// \brief Default constructor (disabled)
    CTileCoalmine() = delete;

    /// \brief Copy constructor (disabled)
    CTileCoalmine(const CTileCoalmine &) = delete;

    ~CTileCoalmine();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitCoalmine(this); }

	virtual void Update(double elapsed);

	/** Get the current amount of coal at the coalmine.
	* \return The amount of coal in the coal mine. 
	*/
	double GetProduction() { return mProduction; }
	void SetProduction(double production);

	void Trump();

//	int GetRequiredLabor() const  override;

private:
	double mProduction = 0;
	double mDuration = 0;
	double mTrumpFactor = 1;
};

