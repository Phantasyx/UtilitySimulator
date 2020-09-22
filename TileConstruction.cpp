/**
 * \file TileConstruction.cpp
 *
 * \author Jordan Hill
 */

#include "stdafx.h"
#include "TileConstruction.h"


using namespace std;
using namespace Gdiplus;
/// Clearing sets 1-8
const wstring clearing0 = L"grass3.png";
/// Clearing sets 1-8
const wstring clearing1 = L"clearing1.png";
/// Clearing sets 1-8
const wstring clearing2 = L"clearing2.png";
/// Clearing sets 1-8
const wstring clearing3 = L"clearing3.png";
/// Clearing sets 1-8
const wstring clearing4 = L"clearing4.png";
/// Clearing sets 1-8
const wstring clearing5 = L"clearing5.png";
/// Clearing sets 1-8
const wstring clearing6 = L"clearing6.png";
/// Clearing sets 1-8
const wstring clearing7 = L"clearing7.png";
/// Clearing sets 1-8
const wstring clearing8 = L"clearing8.png";
/// Stadium
const wstring stadium1 = L"stadium.png";
/// Oremine sets 1-8
const wstring oremine1 = L"oremine1.png";
/// Oremine sets 1-8
const wstring oremine2 = L"oremine2.png";
/// Oremine sets 1-8
const wstring oremine3 = L"oremine3.png";
/// Oremine sets 1-8
const wstring oremine4 = L"oremine4.png";
/// Oremine sets 1-8
const wstring oremine5 = L"oremine5.png";
/// Oremine sets 1-8
const wstring oremine6 = L"oremine6.png";
/// Oremine sets 1-8
const wstring oremine7 = L"oremine7.png";
/// Oremine sets 1-8
const wstring oremine8 = L"oremine8.png";

/** Constructor
* \param city The city this is a member of
*/
CTileConstruction::CTileConstruction(CCity *city) : CTile(city)
{
	SetImage(clearing0);

}

/**
* \brief Destructor
*/
CTileConstruction::~CTileConstruction()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileConstruction::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"construction");
	itemNode->SetAttribute(L"file", GetFile());

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileConstruction::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L"construction"));
}
/*
* Updates construction images
*/
void CTileConstruction::Update(double elapsed)
{
	CTile::Update(elapsed);
	mDuration += elapsed;

	if (mDuration > 1)
	{
		++mSeconds;
		mDuration = 0;

		if (mBuilt == true)
		{
			SetClearing(mSeconds);
		}
	}

	else if (mStatus == stadium)
	{
		this->SetImage(stadium1);
	}

	else if (mStatus == oremine)
	{
		this->SetOremine();
	}
}

/**
* Construction clearing images
*/
void CTileConstruction::SetClearing(int mSeconds)
{

	switch (mSeconds)
	{
	case 1:
	{
		SetImage(clearing1);
		break;
	}
	case 2:
	{ SetImage(clearing2);
	++mTime;
	break;
	}
	case 3:
	{ SetImage(clearing3);
	++mTime;
	break;
	}
	case 4:
	{ SetImage(clearing4);
	++mTime;
	break;
	}
	case 5:
	{ SetImage(clearing5);
	++mTime;
	break;
	}
	case 6:
	{ SetImage(clearing6);
	++mTime;
	break;
	}
	case 7:
	{ SetImage(clearing7);
	++mTime;
	break;
	}
	case 8:
	{ SetImage(clearing8);

	srand((unsigned)time(NULL));
	mRandom = rand() % 10;
	if (mRandom > 4)
	{
		//stadium
		mStatus = stadium;
	}
	else
	{
		//oremine
		mStatus = oremine;

	}
	}
	}
}
/**
* Sets oremine images
*/
void CTileConstruction::SetOremine()
{
	
	if (mForward == false )
	{
		++mPosition;
	}
	else
	{
		--mPosition;
	}

	switch (mPosition)
	{
	case 1:
	{
		SetImage(oremine1);
		mForward = false;
		break;
	}
	case 2:
	{ SetImage(oremine2);
	
	break;
	}
	case 3:
	{ SetImage(oremine3);
	
	break;
	}
	case 4:
	{ SetImage(oremine4);
	
	break;
	}
	case 5:
	{ SetImage(oremine5);
	
	break;
	}
	case 6:
	{ SetImage(oremine6);
	
	break;
	}
	case 7:
	{ SetImage(oremine7);
	
	break;
	}
	case 8:
	{ 
		SetImage(oremine8);
		mForward = true;
		break;
	}
	}
}