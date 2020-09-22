/**
 * \file Construction.h
 *
 * \author Jordan Hill
 *
 *
 */

#pragma once

#include "Tile.h"

/**
*
* Class for adding construction tiles
*/
class CTileConstruction : public CTile
{
public:
	/// Constructor
	CTileConstruction(CCity *city);
	//deleted constructor
	CTileConstruction() = delete;
	/// copy constructor
	CTileConstruction(const CTileConstruction &) = delete;
	//deconstructor
	~CTileConstruction();
	/// save
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	/// load
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);
	/// current state of construction
	enum status { unbuilt, stadium, oremine };
	/// returns the status of a build
	bool GetStatus(){ return mBuilt; }
	/// sets the state of build
	void SetStatus(){ mBuilt = true; }
	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Update(double elapsed) override;
	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitConstruction(this); }
	void SetClearing(int mSeconds);
	/// sets oremine
	void SetOremine();
private:
	double mDuration = 0;/// duration of passed time
	int mSeconds = 0; /// Passed time
	int mTime = 0; /// previous time
	bool mBuilt = false; /// if it is being built
	status mStatus = unbuilt;
	int mRandom = 0; /// number used for randomness
	bool mForward = false;/// direction
	int mPosition = 1; /// current position
};

