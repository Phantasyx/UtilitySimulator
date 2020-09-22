#include "stdafx.h"
#include <algorithm>

#include "City.h"
#include "Tile.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "TileRoad.h"
#include "TileCoalmine.h"
#include "TileConstruction.h"
#include "LaborSink.h"
#include "LaborSource.h"
#include "TileService.h"

using namespace std;
using namespace xmlnode;
using namespace Gdiplus;

/// The x offset to draw the game state at
const auto GameStateOffsetX = 950;
/// The y offset to draw the game state at
const auto GameStateOffsetY = 395;
/// the timer location for x
const auto TimerSetX = 700;
/// the timer location for y
const auto TimerSetY = 0;

CCity::CCity()
{
}


CCity::~CCity()
{
}


/** \brief Draw the city
* \param graphics The GDI+ graphics context to draw on
*/
void CCity::OnDraw(Gdiplus::Graphics *graphics, CPoint translation, double scale)
{
    for (auto item : mTiles)
    {
        item->Draw(graphics, translation, scale);
    }

	mStats.OnDraw(graphics, PointF(0, 0));
	mGameState.Draw(graphics, PointF(GameStateOffsetX, GameStateOffsetY));
	mTimer.OnDraw(graphics, PointF(TimerSetX, TimerSetY));
	
	
}


/** \brief Add a tile to the city
* \param tile New tile to add
*/
void CCity::Add(std::shared_ptr<CTile> tile)
{
    mTiles.push_back(tile);
	// Update the population statitics
	Accept(mStats.GetVisitor());
	auto multiplier = 1;
	auto demandballance = mStats.GetDemandBallance();
	auto laborBallance = mStats.GetLaborBallance();
	if (demandballance == CPopulationStatistics::Market::BALLANCED) 
	{
		multiplier = 2;
	}

	if (laborBallance == CPopulationStatistics::Market::BALLANCED)
	{
		multiplier *= 2;
	}

	mGameState.SetMultiplier(multiplier);
}



/** \brief Test an x,y click location to see if it clicked
* on some item in the city.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CTile> CCity::HitTest(int x, int y)
{
    for (auto i = mTiles.rbegin(); i != mTiles.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/** \brief Move an item to the front of the list of items.
*
* Removes item from the list and adds it to the end so it
* will display last.
* \param item The item to move
*/
void CCity::MoveToFront(std::shared_ptr<CTile> item)
{
    auto loc = find(::begin(mTiles), ::end(mTiles), item);
    if (loc != ::end(mTiles))
    {
        mTiles.erase(loc);
    }

    mTiles.push_back(item);
}


/** \brief Delete an item from the aquarium
*
* \param item The item to delete.
*/
void CCity::DeleteItem(std::shared_ptr<CTile> item)
{
    auto loc = find(::begin(mTiles), ::end(mTiles), item);
    if (loc != ::end(mTiles))
    {
        mTiles.erase(loc);
    }

	// Update the population statitics
	Accept(mStats.GetVisitor());
}


/** \brief Handle updates for animation
* \param elapsed The time since the last update
*/
void CCity::Update(double elapsed)
{
    for (auto item : mTiles)
    {
        item->Update(elapsed);
    }
}

/** \brief Save the city as a .city XML file.
*
* Open an XML file and stream the city data to it.
*
* \param filename The filename of the file to save the city to
*/
void CCity::Save(const std::wstring &filename)
{
    //
    // Create an XML document
    //
    auto root = CXmlNode::CreateDocument(L"city");

	mGameState.XmlSave(root);

    // Iterate over all items and save them
    for (auto item : mTiles)
    {
        item->XmlSave(root);
    }

    try
    {
        root->Save(filename);
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
}


/** \brief Load the city from a .city XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* \param filename The filename of the file to load the city from.
*/
void CCity::Load(const std::wstring &filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		mGameState.XmlLoad(root);

        // Once we know it is open, clear the existing data
        Clear();

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"tile")
            {
                XmlTile(node);
            }
        }

        //
        // All loaded, ensure all sorted
        //
        SortTiles();
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

}



/**
* \brief Handle a tile node.
* \param node Pointer to XML node we are handling
*/
void CCity::XmlTile(const std::shared_ptr<CXmlNode> &node)
{
    // A pointer for the item we are loading
    shared_ptr<CTile> tile;

    // We have an item. What type?
    wstring type = node->GetAttributeValue(L"type", L"");
    if (type == L"landscape")
    {
        tile = make_shared<CTileLandscape>(this);
    }
    else if (type == L"building")
    {
        tile = make_shared<CTileBuilding>(this);
    }
    else if (type == L"road")
    {
        tile = make_shared<CTileRoad>(this);
    }
    else if (type == L"coalmine")
    {
        tile = make_shared<CTileCoalmine>(this);
    }
	else if (type == L"construction")
	{
		tile = make_shared<CTileConstruction>(this);
	}
	else if (type == L"labor-source")
	{
		tile = make_shared<CLaborSource>(this);
	}
	else if (type == L"labor-sink")
	{
		tile = make_shared<CLaborSink>(this);
	}
	else if (type == L"service")
	{
		tile = make_shared<CTileService>(this);
	}

    if (tile != nullptr)
    {
        tile->XmlLoad(node);
        Add(tile);
    }
}




/**
* \brief Clear the city data.
*
* Deletes all known items in the city.
*/
void CCity::Clear()
{
    mTiles.clear();

	// Update the population statitics
	Accept(mStats.GetVisitor());
}




/**
 * \brief Ensure the tiles are in the correct drawing order.
 *
 * This draws bottom to top so the tiles can overlapp.
 * Also builds the adjacency support since this is called whenever
 * the city is reorganized.
 */
void CCity::SortTiles()
{
    // sort using a lambda expression 
    sort(::begin(mTiles), ::end(mTiles), 
        [](const shared_ptr<CTile> &a, const shared_ptr<CTile> &b) {
        if (a->GetY() < b->GetY())
            return true;

        if (a->GetY() > b->GetY())
            return false;

        return a->GetX() > b->GetX();
    });

    BuildAdjacencies();
}


/**
 * \brief Build support for fast adjacency testing.
 *
 * This builds a map of the grid locations of every tile, so we can
 * just look them up.
 */
void CCity::BuildAdjacencies()
{
    mAdjacency.clear();
    for (auto tile : mTiles)
    {
        mAdjacency[pair<int, int>(tile->GetX() / GridSpacing, 
            tile->GetY() / GridSpacing)] = tile;
    }
}



/**
 * \brief Get any adjacent tile.
 * 
 * Given a tile in the city, this determines if there is another
 * tile adjacent to it. The parameters dx, dy determine which direction
 * to look. 
 *
 * The values for specific adjacencies (dx, dy, and direction):
 *    - -1 -1 Upper left
 *    - 1 -1 Upper right
 *    - -1 1 Lower left
 *    - 1 1 Lower right
 * 
 * \param tile Tile to test
 * \param dx Left/right determination, -1=left, 1=right
 * \param dy Up/Down determination, -1=up, 1=down
 * \returns Adjacent tile or nullptr if none.
 */
std::shared_ptr<CTile> CCity::GetAdjacent(std::shared_ptr<CTile> tile, int dx, int dy)
{
    return GetAdjacent(tile.get(), dx, dy);
}

/**
 * \brief Get any adjacent tile.
 * 
 * Identical to the other version, except this version accepts a
 * regular pointer instead of a shared_ptr. This allows the function
 * to be called from CTile, which only knows itself as a pointer.
 * 
 * \param tile Tile to test
 * \param dx Left/right determination, -1=left, 1=right
 * \param dy Up/Down determination, -1=up, 1=down
 * \returns Adjacent tile or nullptr if none.
 */
std::shared_ptr<CTile> CCity::GetAdjacent(CTile *tile, int dx, int dy)
{
    int atX = tile->GetX() / GridSpacing + dx * 2;
    int atY = tile->GetY() / GridSpacing + dy;

    auto adj = mAdjacency.find(pair<int, int>(atX, atY));
    if (adj != mAdjacency.end())
    {
        // We found it
        return adj->second;
    }

    //int atX = tile->GetX() + dx * GridSpacing * 2;
    //int atY = tile->GetY() + dy * GridSpacing;

    //for (auto testTile : mTiles)
    //{
    //    if (testTile->GetX() == atX &&
    //        testTile->GetY() == atY)
    //    {
    //        return testTile;
    //    }
    //}

    // If nothing found
    return nullptr;
}
