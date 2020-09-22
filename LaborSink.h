/**
* \author Robin Miller
* \file LaborSink.h
* Defines a sink for labor (production)
**/

#pragma once

#include "TileBuilding.h"

class CLaborSink : public CTileBuilding
{
public:
	CLaborSink(CCity* city);

	virtual ~CLaborSink();

	std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** Apply this to the visitor
	* \param visitor the visitor to apply ourselves to
	**/
	void Accept(CTileVisitor* visitor) override { visitor->VisitLaborSink(this); }

	/** Gets the amount of labor required to operate this labor sink 
	* \return the number of workers needed. 
	**/
	int GetRequiredLabor() const { return mRequiredLabor; };

	/** Gets the amount of labor required to operate this labor sink
	* \param requiredLabor the number of workers needed.
	**/
	void SetRequiredLabor(int requiredLabor) { mRequiredLabor = requiredLabor; };

private:
	int mRequiredLabor;
};

