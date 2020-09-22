#pragma once
/**
* \author Robin Miller
* \file LaborSource.h
* Defines a source of labor (housing)
**/

#include "TileBuilding.h"

/**
* Abstract class defining the a source of workers. 
*/
class CLaborSource : public CTileBuilding
{
public:
	CLaborSource(CCity* city);
	virtual ~CLaborSource();

	std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) override;


	/** Apply this to the visitor
	* \param visitor the visitor to apply ourselves to
	**/
	void Accept(CTileVisitor* visitor) override { visitor->VisitLaborSource(this); }

	/** Gets the amount of labor produced by this source 
	* \return the number of workers available.
	**/
	int GetAvailableLabor() const { return mAvailableLabor; };

	/** Sets the amount of labor produced by this source
	* \param labor the number of workers available.
	**/
	void SetAvailableLabor(int labor){ mAvailableLabor = labor; };
private:

	int mAvailableLabor;
};

