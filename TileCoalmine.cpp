#include "stdafx.h"
#include "TileCoalmine.h"
#include <iostream>

using namespace std;
using namespace Gdiplus;

/// Image when the coalmine production is empty
const wstring EmptyImage = L"coalmine-empty.png";

/// Image when the coalmine production is low
const wstring LowProductionImage = L"coalmine-low.png";

/// Time to reach low production level in seconds
const double LowProductionTime = 5;

/// Tons of coal at low production level
const double LowProduction = 1;

/// Image when the coalmine production is Medium
const wstring MediumProductionImage = L"coalmine-med.png";

/// Time to reach Medium production level in seconds
const double MediumProductionTime = 6;

/// Tons of coal at Medium production level
const double MediumProduction = 2.5;

/// Image when the coalmine production is Full
const wstring FullProductionImage = L"coalmine-full.png";

/// Time to reach Full production level in seconds
const double FullProductionTime = 4;

/// Tons of coal at Full production level
const double FullProduction = 4;

/// Image when the coalmine is destroyed
const wstring DestroyedImage = L"burnt_land.png";

/// The factor by which trumping speed production
const double TrumpBoost = 2;

/// The trumped image
const auto BurntLand = L"burnt_land.png";

/// The amount of labor required
const int LaborReqiuired = 20;

/** Constructor
* \param city The city this is a member of
*/
CTileCoalmine::CTileCoalmine(CCity *city) : CTile(city)
{
    SetImage(EmptyImage);
}

/**
* \brief Destructor
*/
CTileCoalmine::~CTileCoalmine()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileCoalmine::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
    auto itemNode = CTile::XmlSave(node);

    itemNode->SetAttribute(L"type", L"coalmine");

    return itemNode;
}

/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileCoalmine::Update(double elapsed)
{
	CTile::Update(elapsed);

	mDuration += elapsed * mTrumpFactor;

	// If we are not over trumped, we can keep producing
	if (mTrumpFactor <= TrumpBoost)
	{
		// If tree for the image/production timer
		if (mProduction == 0 && mDuration >= LowProductionTime)
		{
			SetProduction(LowProduction);
		}

		if (mProduction == LowProduction && mDuration >= MediumProductionTime)
		{
			SetProduction(MediumProduction);
		}

		if (mProduction == MediumProduction && mDuration >= FullProduction)
		{
			SetProduction(FullProduction);
		}
	}
}


/** Sets the amount of coal in the coalmine 
* \param production the new amount of coal in the coalmine
**/
void CTileCoalmine::SetProduction(double production)
{
	mDuration = 0;
	if (mTrumpFactor <= TrumpBoost)
	{
		mProduction = production;
		// Handles updating the image
		if (mProduction == LowProduction) {
			SetImage(LowProductionImage);
		}
		if (mProduction == MediumProduction) {
			SetImage(MediumProductionImage);
		}
		if (mProduction == FullProduction) {
			SetImage(FullProductionImage);
		}
		if (mProduction == 0) {
			SetImage(EmptyImage);
		}
	}
}

/** Trumps the coalmine */
void CTileCoalmine::Trump() 
{
	mTrumpFactor *= TrumpBoost;
	if (mTrumpFactor > TrumpBoost) 
	{
		SetImage(BurntLand);
	}
}

///** Inherit docs from CLaborSink **/
//int CTileCoalmine::GetRequiredLabor() const
//{
//	return LaborReqiuired;
//}