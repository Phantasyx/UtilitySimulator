/**
 * \file ChildView.cpp
 *
 * \author Charles B. Owen
 */

#include "stdafx.h"
#include <sstream>
#include "DoubleBufferDC.h"
#include "CityApp.h"
#include "ChildView.h"
#include "Tile.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "TileRoad.h"
#include "TileCoalmine.h"
#include "BuildingCounter.h"
#include "TileCounter.h"
#include "TilePower.h"
#include "TilePowerStation.h"
#include "LaborSink.h"
#include "LaborSource.h"
#include "TileService.h"
#include "TileConstruction.h"
#include <vector>
#include "GameState.h"
#include "Timer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 100;


/// Initial tile X location
const int InitialX = CCity::GridSpacing * 5;

/// Initial tile Y location
const int InitialY = CCity::GridSpacing * 3;

/// Margin of trashcan from side and bottom in pixels
const int TrashcanMargin = 5;

const int NavButtonMargin = 5;

const WCHAR* NavModeActiveImageName = L"images/nav2.png";
const WCHAR* NavModeInactiveImageName = L"images/nav1.png";

/// The number of workers in a house
const int HouseLabor = 5;
/// The number of workers in a yellow house
const int YellowHouseLabor = 6;
/// The number of workers in an apartment
const int ApartmentLabor = 300;
/// Trailer park labor
const int TrailerParkLabor = 200;
/// Factory workers
const int FactoryLabor = 100;
/// Mill workers
const int MillLabor = 100;

/// Market service
const int MarketService = 100;
/// Well service
const int WellService = 50;
/// Recycle Center service
const int RecycleCenterService = 100;

/**
 * Constructor
 */
CChildView::CChildView()
{
    srand((unsigned int)time(nullptr));

    // Load the trash can image
    mTrashcan = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/trashcan.png"));
    if (mTrashcan->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/trashcan.png");
    }

	mNavModeActive = unique_ptr<Bitmap>(Bitmap::FromFile(NavModeActiveImageName));
	if (mNavModeActive->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/nav2.png");
	}


	mNavModeInactive = unique_ptr<Bitmap>(Bitmap::FromFile(NavModeInactiveImageName));
	if (mNavModeInactive->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/nav1.png");
	}

	mNavModeImage = mNavModeInactive;

}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}

/// \cond
/// This doxygen switch tells it to ignore this block of code
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
    ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
    ON_COMMAND(ID_BUILDINGS_FARMHOUSE, &CChildView::OnBuildingsFarmhouse)
    ON_COMMAND(ID_LANDSCAPING_GRASS, &CChildView::OnLandscapingGrass)
    ON_COMMAND(ID_LANDSCAPING_SPARTYSTATUE, &CChildView::OnLandscapingSpartystatue)
    ON_COMMAND(ID_BUILDINGS_BLACKSMITHSHOP, &CChildView::OnBuildingsBlacksmithshop)
    ON_COMMAND(ID_LANDSCAPING_TALLGRASS, &CChildView::OnLandscapingTallgrass)
    ON_COMMAND(ID_BUILDINGS_BROWNHOUSE, &CChildView::OnBuildingsBrownhouse)
    ON_COMMAND(ID_BUILDINGS_YELLOWHOUSE, &CChildView::OnBuildingsYellowhouse)
    ON_COMMAND(ID_BUILDINGS_F, &CChildView::OnBuildingsF)
    ON_COMMAND(ID_BUILDINGS_HOSPITAL, &CChildView::OnBuildingsHospital)
    ON_COMMAND(ID_BUILDINGS_MARKET, &CChildView::OnBuildingsMarket)
    ON_COMMAND(ID_BUILDINGS_CONDOS, &CChildView::OnBuildingsCondos)
    ON_COMMAND(ID_LANDSCAPING_TREE, &CChildView::OnLandscapingTree)
    ON_COMMAND(ID_LANDSCAPING_TREES, &CChildView::OnLandscapingTrees)
    ON_COMMAND(ID_LANDSCAPING_BIGTREES, &CChildView::OnLandscapingBigtrees)
    ON_COMMAND(ID_LANDSCAPING_ROAD, &CChildView::OnLandscapingRoad)
    ON_COMMAND(ID_BUSINESSES_COALMINE, &CChildView::OnBusinessesCoalmine)
    ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_VIEW_NONE, &CChildView::OnViewNone)
	ON_COMMAND(ID_VIEW_RESEIDENTIAL, &CChildView::OnViewReseidential)
	ON_COMMAND(ID_VIEW_INDUSTRIAL, &CChildView::OnViewIndustrial)
	ON_COMMAND(ID_VIEW_AGRICULTURAL, &CChildView::OnViewAgricultural)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NONE, &CChildView::OnUpdateViewNone)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESEIDENTIAL, &CChildView::OnUpdateViewReseidential)
	ON_UPDATE_COMMAND_UI(ID_VIEW_AGRICULTURAL, &CChildView::OnUpdateViewAgricultural)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INDUSTRIAL, &CChildView::OnUpdateViewIndustrial)
	ON_COMMAND(ID_BUILDINGS_COUNT, &CChildView::OnBuildingsCount)
	ON_COMMAND(ID_BUSINESSES_HAULCOAL, &CChildView::OnBusinessesHaulcoal)
	ON_COMMAND(ID_BUSINESSES_TRUMP, &CChildView::OnBusinessesTrump)
	ON_UPDATE_COMMAND_UI(ID_BUSINESSES_TRUMP, &CChildView::OnUpdateBusinessesTrump)
	ON_COMMAND(ID_COUNTER_TILESINCITY, &CChildView::OnCounterTilesincity)
	ON_COMMAND(ID_COUNTER_PARTIALLYOVERLAPPING, &CChildView::OnCounterPartiallyoverlapping)
	ON_COMMAND(ID_COUNTER_FULLYOVERLAPPED, &CChildView::OnCounterFullyoverlapped)
	ON_COMMAND(ID_POWERSTATION_SOLAR, &CChildView::OnPowerstationSolar)
	ON_COMMAND(ID_POWERSTATION_COAL, &CChildView::OnPowerstationCoal)
	ON_COMMAND(ID_POWERSTATION_P, &CChildView::OnPowerstationP)
	ON_COMMAND(ID_TWOWAY_TWOWAY1, &CChildView::OnTwowayTwoway1)
	ON_COMMAND(ID_TWOWAY_TWOWAY2, &CChildView::OnTwowayTwoway2)
	ON_COMMAND(ID_TWOWAY_TWOWAY3, &CChildView::OnTwowayTwoway3)
	ON_COMMAND(ID_TWOWAY_TWOWAY4, &CChildView::OnTwowayTwoway4)
	ON_COMMAND(ID_TWOWAY_LOWERTWOWAY1, &CChildView::OnTwowayLowertwoway1)
	ON_COMMAND(ID_TWOWAY_LOWERTWOWAY2, &CChildView::OnTwowayLowertwoway2)
	ON_COMMAND(ID_THREEWAY_THREEWAY1, &CChildView::OnThreewayThreeway1)
	ON_COMMAND(ID_THREEWAY_THREEWAY2, &CChildView::OnThreewayThreeway2)
	ON_COMMAND(ID_POWERLINE_FOURWAY, &CChildView::OnPowerlineFourway)
	ON_COMMAND(ID_THREEWAY_THREEWAY3, &CChildView::OnThreewayThreeway3)
	ON_COMMAND(ID_POWERSYSTEM_HUALCOALFORCOALPOWERSTATION, &CChildView::OnPowersystemHualcoalforcoalpowerstation)
	ON_COMMAND(ID_BUILDINGS_TRAILERPARK, &CChildView::OnBuildingsTrailerpark)
	ON_COMMAND(ID_BUILDINGS_APAR, &CChildView::OnBuildingsApartment)
	ON_COMMAND(ID_BUILDINGS_FACTORY32810, &CChildView::OnBuildingsFactory32810)
	ON_COMMAND(ID_BUILDINGS_MILL, &CChildView::OnBuildingsMill)
	ON_COMMAND(ID_BUILDINGS_WELL, &CChildView::OnBuildingsWell)
	ON_COMMAND(ID_BUILDINGS_RECYCLINGCENTER, &CChildView::OnBuildingsRecyclingcenter)
	ON_COMMAND(ID_BUILDINGS_TRAILERPARK32833, &CChildView::OnBuildingsTrailerpark32833)
	ON_COMMAND(ID_CONSTRUCTION_CREATETILE, &CChildView::OnConstructionCreatetile)
	ON_COMMAND(ID_FILE_GAMESTART, &CChildView::OnFileGamestart)
END_MESSAGE_MAP()
/// \endcond


/** \cond */
/** 
* This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

/** 
* This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/void CChildView::OnPaint()
{
    CPaintDC paintDC(this);     // device context for painting
    CDoubleBufferDC dc(&paintDC); // device context for painting

    Graphics graphics(dc.m_hDC);
    graphics.Clear(Color(0, 0, 0));

    if (mFirstDraw)
    {
        mFirstDraw = false;
        SetTimer(1, FrameDuration, nullptr);

        /*
        * Initialize the elapsed time system
        */
        LARGE_INTEGER time, freq;
        QueryPerformanceCounter(&time);
        QueryPerformanceFrequency(&freq);

        mLastTime = time.QuadPart;
        mTimeFreq = double(freq.QuadPart);
    }

    /*
    * Compute the elapsed time since the last draw
    */
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    long long diff = time.QuadPart - mLastTime;
    double elapsed = double(diff) / mTimeFreq;
    mLastTime = time.QuadPart;

    mCity.Update(elapsed);

    // Get the size of the window
    CRect rect;
    GetClientRect(&rect);

    /*
     * Draw the trash can
     */
    
    // Bottom minus image size minus margin is top of the image
    mTrashcanTop = rect.Height() - mTrashcan->GetHeight() - TrashcanMargin;
    mTrashcanRight = TrashcanMargin + mTrashcan->GetWidth();

    graphics.DrawImage(mTrashcan.get(), TrashcanMargin, mTrashcanTop,
        mTrashcan->GetWidth(), mTrashcan->GetHeight());

	// Draw the nav image
	mNavImageWidth = mNavModeImage->GetWidth();
	mNavImageHeight = mNavModeImage->GetHeight();

	mNavImageX = rect.Width() - NavButtonMargin - mNavImageWidth;
	mNavImageY = NavButtonMargin;

	graphics.DrawImage(mNavModeImage.get(), mNavImageX, mNavImageY, mNavImageWidth, mNavImageHeight);
	

	// Scale the city
	graphics.SetPageUnit(UnitPixel);
	graphics.SetPageScale(mScale);

	CPoint scaledSpaceTranslation = mTranslation;
	scaledSpaceTranslation.x /= mScale;
	scaledSpaceTranslation.y /= mScale;

    /*
     * Actually Draw the city
     */
	mCity.OnDraw(&graphics, scaledSpaceTranslation, mScale);

	// Draw the zoning information
	Pen pen(Color::Green, 2);

	for (auto tile : mCity.GetZoning(mZoning))
	{
		tile->DrawBorder(&graphics, &pen, scaledSpaceTranslation, mScale);
	}
}


/**
* \brief Erase the background prior to drawing.
*
* We return true so this does nothing. This prevents the flicker
* of a repaint of white before actual drawing.
*
* \param pDC A device context to draw on
* \returns TRUE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    // This disabled the default background erase
    return TRUE;
}
/**
* Visitor for construction
*/
class CConstructionVisitor : public CTileVisitor {
public:
	void VisitConstruction(CTileConstruction *site) override { site->SetStatus(); }
};

/** \brief Handle a left button double-click on a tile
* \param nFlags Mouse flags
* \param point Where we clicked
*/
void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	auto tile = mCity.HitTest((point.x - mTranslation.x) / mScale, (point.y - mTranslation.y) / mScale);
    if (tile != nullptr) 
    {
		CConstructionVisitor visitor;
		tile->Accept(&visitor);

        tile->PropertiesDlg();
        Invalidate();
    }

}


/** Trumps coalmines **/
class Trumper : public CTileVisitor
{
public:
	/** Constructor */
	Trumper() {}

	/** Destructor */
	virtual ~Trumper() {}

	/** Empty out the coalmine
	* \param coalmine The coalmine to empty.
	*/
	virtual void VisitCoalmine(CTileCoalmine *coalmine)
	{
		coalmine->Trump();
	}
};

/** \brief Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x > (mNavImageX + mNavImageWidth / 2) && point.y > mNavImageY && point.x < (mNavImageX + mNavImageWidth) && point.y < (mNavImageY + mNavImageHeight))
	{
		mNavModeActiveFlag = !mNavModeActiveFlag;
		
		mNavModeImage = mNavModeActiveFlag ? mNavModeActive : mNavModeInactive;

		mStartDragging = point;

		Invalidate();
	} 
	// Zoom in
	else if (point.x > mNavImageX && point.y > mNavImageY + mNavImageHeight / 2 && point.x < (mNavImageX + mNavImageWidth / 2) && point.y < (mNavImageY + mNavImageHeight))
	{
		mScale /= 2;
	}
	// Zoom out
	else if (point.x > mNavImageX && point.y > mNavImageY && point.x < (mNavImageX + mNavImageWidth / 2) && point.y < (mNavImageY + mNavImageHeight / 2))
	{
		mScale *= 2;
	}
	else if (!mNavModeActiveFlag)
	{
		mGrabbedItem = mCity.HitTest((point.x - mTranslation.x) / mScale, (point.y - mTranslation.y) / mScale);

		if (mGrabbedItem != nullptr)
		{
			// We grabbed something
			// Move it to the front
			mCity.MoveToFront(mGrabbedItem);

			if (mTrumping)
			{
				Trumper trumper;
				mGrabbedItem->Accept(&trumper);
			}

			Invalidate();
		}
	}
}

/** \brief Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}



/** \brief Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{	
	// If the city should be translated
	if (mNavModeActiveFlag) 
	{
		// Are we dragging?
		if (nFlags & MK_LBUTTON) 
		{ 
			CPoint delta = point - mStartDragging;
			mTranslation += delta;
		}

		mStartDragging = point;

	}
	else if (mGrabbedItem != nullptr)    // See if an item is currently being moved by the mouse
    {

		CTilePowerStation n(&mCity);
		CTilePower m(&mCity);
		if (typeid(*mGrabbedItem).name() == typeid(n).name())
		{

			std::shared_ptr<CTile> upperleft = mGrabbedItem->GetAdjacent(-1, -1);
			if (upperleft != nullptr&&typeid(*upperleft).name() == typeid(m).name())
			{
				upperleft->changeelectric(1, 1);
			}
			std::shared_ptr<CTile> upperright = mGrabbedItem->GetAdjacent(1, -1);
			if (upperright != nullptr&&typeid(*upperright).name() == typeid(m).name())
			{
				upperright->changeelectric(-1, 1);
			}
			std::shared_ptr<CTile> lowerleft = mGrabbedItem->GetAdjacent(-1, 1);
			if (lowerleft != nullptr&&typeid(*lowerleft).name() == typeid(m).name())
			{
				lowerleft->changeelectric(1, -1);
			}
			std::shared_ptr<CTile> lowerright = mGrabbedItem->GetAdjacent(1, 1);
			if (lowerright != nullptr&&typeid(*lowerright).name() == typeid(m).name())
			{
				lowerright->changeelectric(-1, -1);
			}
		}
        // If an item is being moved, we only continue to 
        // move it while the left button is down.
        if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x / mScale - mTranslation.x, point.y / mScale - mTranslation.y);
        }
        else
        {
            // When the left button is released we release
            // the item. If we release it on the trashcan,
            // delete it.
            if (point.x < mTrashcanRight && point.y > mTrashcanTop)
            {
                // We have clicked on the trash can
                mCity.DeleteItem(mGrabbedItem);
            }
            else
            {
                mGrabbedItem->QuantizeLocation();
				CTilePowerStation n(&mCity);
				CTilePower m(&mCity);
				if (typeid(*mGrabbedItem).name() == typeid(n).name())
				{

					std::shared_ptr<CTile> upperleft = mGrabbedItem->GetAdjacent(-1, -1);
					if (upperleft != nullptr&&typeid(*upperleft).name() == typeid(m).name())
					{
						upperleft->changeelectric(1, 1);
					}
					std::shared_ptr<CTile> upperright = mGrabbedItem->GetAdjacent(1, -1);
					if (upperright != nullptr&&typeid(*upperright).name() == typeid(m).name())
					{
						upperright->changeelectric(-1, 1);
					}
					std::shared_ptr<CTile> lowerleft = mGrabbedItem->GetAdjacent(-1, 1);
					if (lowerleft != nullptr&&typeid(*lowerleft).name() == typeid(m).name())
					{
						lowerleft->changeelectric(1, -1);
					}
					std::shared_ptr<CTile> lowerright = mGrabbedItem->GetAdjacent(1, 1);
					if (lowerright != nullptr&&typeid(*lowerright).name() == typeid(m).name())
					{
						lowerright->changeelectric(-1, -1);
					}
				}
            }

            mCity.SortTiles();
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Invalidate();
    }
}

/**
* \brief Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    Invalidate();
    CWnd::OnTimer(nIDEvent);
}



/**
* \brief Handler for the File/Save As menu option
*/
void CChildView::OnFileSaveas()
{
    CFileDialog dlg(false,  // false = Save dialog box
        L".city",           // Default file extension
        nullptr,            // Default file name (none)
        OFN_OVERWRITEPROMPT,    // Flags
        L"City Files (*.city)|*.city|All Files (*.*)|*.*||");    // Filter
    if (dlg.DoModal() != IDOK)
        return;

    wstring filename = dlg.GetPathName();

    mCity.Save(filename);
}


/** \brief This function is called when an File Open menu item is selected.
*
* It loads the city from a file.
*/
void CChildView::OnFileOpen()
{
    CFileDialog dlg(true,  // true = Open dialog box
        L".city",           // Default file extension
        nullptr,            // Default file name (none)
        0,    // Flags
        L"City Files (*.city)|*.city|All Files (*.*)|*.*||");    // Filter
    if (dlg.DoModal() != IDOK)
        return;

    wstring filename = dlg.GetPathName();
    mCity.Load(filename);
    Invalidate();
}



/**
 * \brief Add a CTileBuilding tile to the drawing.
 * \param file The file for the building image
 */
void CChildView::AddBuilding(const std::wstring &file)
{
	CTileBuilding n(&mCity);
    auto tile = make_shared<CTileBuilding>(&mCity);
    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}

/**
* \brief Add a CTileBuilding tile to the drawing.
* \param file The file for the building image
*/
void CChildView::AddPower(const std::wstring &file)
{
	auto tile = make_shared<CTilePower>(&mCity);
	tile->SetImage(file);
	tile->SetLocation(InitialX, InitialY);
	tile->setfile(file);
	mCity.Add(tile);
	Invalidate();
}
/**
* adding power station
*/
void CChildView::AddPowerStation(const std::wstring &file)
{
	auto tile = make_shared<CTilePowerStation>(&mCity);
	tile->SetImage(file);
	tile->SetLocation(InitialX, InitialY);
	mCity.Add(tile);
	Invalidate();
}

/**
* \brief Add a CTileLandscaping tile to the drawing.
* \param file The file for the landscape image
*/
void CChildView::AddLandscape(const std::wstring &file)
{
    auto tile = make_shared<CTileLandscape>(&mCity);
    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}

/**
* \brief Adds a LaborSource to the city
* \param imageFile the image file to use 
* \param labor the number of laborers that this tile can support
*/
void CChildView::AddLaborSource(const std::wstring &file, const int labor)
{
	auto tile = make_shared<CLaborSource>(&mCity);
	tile->SetImage(file);
	tile->SetAvailableLabor(labor);
	tile->SetLocation(InitialX, InitialY);
	mCity.Add(tile);
	Invalidate();
}

/**
* \brief Adds a LaborSink to the city
* \param imageFile the image file to use
* \param labor the number of laborers that this tile can support
*/
void CChildView::AddLaborSink(const std::wstring &file, const int labor)
{
	auto tile = make_shared<CLaborSink>(&mCity);
	tile->SetImage(file);
	tile->SetRequiredLabor(labor);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}

/**
* \brief Adds a Service to the city
* \param imageFile the image file to use
* \param service the amount of service that this tile can support
*/
void CChildView::AddService(const std::wstring &file, const int service)
{
	auto tile = make_shared<CTileService>(&mCity);
	tile->SetImage(file);
	tile->SetAvailableService(service);
	tile->SetLocation(InitialX, InitialY);
	mCity.Add(tile);
	Invalidate();
}

/**
 * \cond
 *
 * I'm not going to document these menu handlers, since what they 
 * so is obvious. I'm using a Doxygen feature to ignore the functions
 */

/**
* Landscape image
*/
void CChildView::OnBuildingsFarmhouse()
{
    AddBuilding(L"farm0.png");
	mCity.GameSetScore(15);
}

/**
* Landscape image
*/
void CChildView::OnLandscapingGrass()
{
    AddLandscape(L"grass.png");
}

/**
* Landscape image
*/
void CChildView::OnLandscapingSpartystatue()
{
    AddLandscape(L"sparty.png");
}

/**
* Landscape image
*/
void CChildView::OnBuildingsBlacksmithshop()
{
    AddBuilding(L"blacksmith.png");
	mCity.GameSetScore(15);
}

/**
* Landscape image
*/
void CChildView::OnBuildingsTrailerpark()
{

}

/**
* Landscape image
*/
void CChildView::OnBuildingsTrailerpark32833()
{
	AddLaborSource(L"housing2.png", TrailerParkLabor);
	mCity.GameSetScore(15);
}
/**
* Landscape image
*/
void CChildView::OnBuildingsApartment()
{
	AddLaborSource(L"reshihi.png", ApartmentLabor);
	mCity.GameSetScore(15);
}
/**
* Landscape image
*/
void CChildView::OnLandscapingTallgrass()
{
    AddLandscape(L"tallgrass.png");
}

/**
* Landscape image
*/
void CChildView::OnBuildingsBrownhouse()
{
	AddLaborSource(L"house.png", HouseLabor);
	mCity.GameSetScore(15);
}

/**
* Landscape image
*/
void CChildView::OnBuildingsYellowhouse()
{
	AddLaborSource(L"yellowhouse.png", YellowHouseLabor);
	mCity.GameSetScore(15);
}

/**
* Landscape image
*/
void CChildView::OnBuildingsF()
{
    AddBuilding(L"firestation.png");
	mCity.GameSetScore(15);
}

/**
* Landscape image
*/
void CChildView::OnBuildingsHospital()
{
    AddBuilding(L"hospital.png");
	mCity.GameSetScore(15);
}

/**
* Landscape image
*/
void CChildView::OnBuildingsMarket()
{
    AddService(L"market.png", MarketService);
	mCity.GameSetScore(10);
}
/**
* Landscape image
*/
void CChildView::OnBuildingsWell()
{
	AddService(L"waterwell.png", WellService);
	mCity.GameSetScore(10);
}
/**
* Landscape image
*/
void CChildView::OnBuildingsRecyclingcenter()
{
	AddService(L"recyclecentre.png", RecycleCenterService);
	mCity.GameSetScore(10);
}
/**
* Landscape image
*/
void CChildView::OnBuildingsCondos()
{
    AddLaborSource(L"condos.png", ApartmentLabor);
	mCity.GameSetScore(10);
}

/**
* Landscape image
*/
void CChildView::OnLandscapingTree()
{
    AddLandscape(L"tree.png");
}

/**
* Landscape image
*/
void CChildView::OnLandscapingTrees()
{
    AddLandscape(L"tree2.png");
}

/**
* Landscape image
*/
void CChildView::OnLandscapingBigtrees()
{
    AddLandscape(L"tree3.png");
}

/*
* Landscaping tile
*/
void CChildView::OnLandscapingRoad()
{
    auto tile = make_shared<CTileRoad>(&mCity);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}

/**
* coalmine
*/
void CChildView::OnBusinessesCoalmine()
{
    auto tile = make_shared<CTileCoalmine>(&mCity);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
	mCity.GameSetScore(12);
    Invalidate();
}
/**
* Commerce image
*/
void CChildView::OnBuildingsFactory32810()
{
	AddLaborSink(L"industry0.png", FactoryLabor);
	mCity.GameSetScore(15);
}
/**
* Commerce image
*/
void CChildView::OnBuildingsMill()
{
	AddLaborSink(L"mill0.png", MillLabor);
	mCity.GameSetScore(15);
}


/** \endcond */

/** \cond 
* These functions handle click events from the view menu 
*/
void CChildView::OnViewNone()
{
	mZoning = CTile::Zonings::NONE;
}

/*
* Checkmark
*/
void CChildView::OnViewReseidential()
{
	mZoning = CTile::Zonings::RESIDENTIAL;
}

/*
* Checkmark
*/
void CChildView::OnViewIndustrial()
{
	mZoning = CTile::Zonings::INDUSTRIAL;
}

/*
* Checkmark
*/
void CChildView::OnViewAgricultural()
{
	mZoning = CTile::Zonings::AGRICULTURAL;
}

/** \endcond */

/** \cond
* These functions provide update functions so that the view menu state matches 
* the mZoning state of the child view 
*/
void CChildView::OnUpdateViewNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::Zonings::NONE);
}
/*
* Checkmark
*/
void CChildView::OnUpdateViewReseidential(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::Zonings::RESIDENTIAL);
}

/*
* Checkmark
*/
void CChildView::OnUpdateViewAgricultural(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::Zonings::AGRICULTURAL);
}
/*
* Checkmark
*/
void CChildView::OnUpdateViewIndustrial(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::Zonings::INDUSTRIAL);
}
/** \endcond */

/** Menu handler that counts the number of builds */
void CChildView::OnBuildingsCount()
{
	CBuildingCounter visitor;
	mCity.Accept(&visitor);
	int cnt = visitor.GetNumBuildings();

	wstringstream str;
	str << L"There are " << cnt << L" buildings.";
	AfxMessageBox(str.str().c_str());
}

// Note, this really should be done using lambdas + template<class Func>. That way, we can hold state 
// by overriding operator() if we really need to, but other stuff is kept short, and we don't 
// have overhead from vtables. Esp. nice in C++14, where we have generic lambdas, otherwise, we 
// have to use dynamic_cast<CTileCloalmine*>(tile) != nullptr, but that is more extensible anyway, as 
// more types of tiles are added.

/** This is a small visitor class for hauling coal, defined here since it is not used elsewhere, and is not very generalizable/generic. **/
class CHaulCoalVisitor : public CTileVisitor
{
public:
	/** Constructor */
	CHaulCoalVisitor() {}

	/** Destructor */
	virtual ~CHaulCoalVisitor() {}

	/** Empty out the coalmine
	* \param coalmine The coalmine to empty. 
	*/
	virtual void VisitCoalmine(CTileCoalmine *coalmine)
	{
		mCoalHauled += coalmine->GetProduction();
		double temp = mCoalHauled;
		coalmine->SetProduction(0);
	}

	// Not really any point in making this private, as this class will only every be used inside this function
	double mCoalHauled = 0; //< Remembers the amount of coal that has been hauled
};

/** Menu handler that hauls coal **/
void CChildView::OnBusinessesHaulcoal()
{
	// Haul the coal
	CHaulCoalVisitor visitor;
	mCity.Accept(&visitor);

	// Show the results
	wstringstream str;
	str << L"The total production is " << visitor.mCoalHauled << L" tons";
	AfxMessageBox(str.str().c_str());
}

/** Menu handler for trumping **/
void CChildView::OnBusinessesTrump()
{
	mTrumping = !mTrumping;
}

/** Updates the checked state of this check box. **/
void CChildView::OnUpdateBusinessesTrump(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mTrumping);
}



/**
* Counts number of tiles on the city
*
*/
void CChildView::OnCounterTilesincity()
{
	CTileCounter visitor(&mCity);
	mCity.Accept(&visitor);
	int cnt = visitor.GetNumTiles();

	wstringstream str;
	str << L"There are " << cnt << L" tiles.";
	AfxMessageBox(str.str().c_str());
}

/**
* counts tiles that are partually overlapped
*
*/
void CChildView::OnCounterPartiallyoverlapping()
{
	CTileCounter visitor(&mCity);
	
	mCity.Accept(&visitor);

	int cnt = visitor.GetPartTiles();
	wstringstream str;
	str << L"There are " << cnt << L" tiles.";
	AfxMessageBox(str.str().c_str());

}

/**
*
* counts tiles that are fully overlapped
*/
void CChildView::OnCounterFullyoverlapped()
{
	CTileCounter visitor(&mCity);
	mCity.Accept(&visitor);
	int cnt = visitor.GetFullTiles();

	wstringstream str;
	str << L"There are " << cnt << L" tiles.";
	AfxMessageBox(str.str().c_str());
}



/*
* Power Object
*/
bool eletricity()
{
	CTile *temp;
	//*temp = CCity.GetAdjacent(std::shared_ptr<CTile> tile, int dx, int dy)
	return false;
}
/*
* Power Object
*/
void CChildView::OnPowerstationSolar()
{
	AddPowerStation(L"powerssolar.png");
	mCity.GameSetScore(20);
}

/*
* Power Object
*/
void CChildView::OnPowerstationCoal()
{
	AddPowerStation(L"Powercoal0.png");
	mCity.GameSetScore(20);
}

/*
* Power Object
*/
void CChildView::OnPowerstationP()
{
	AddPowerStation(L"substation.png");
	mCity.GameSetScore(20);
}

/*
* Power Object
*/
void CChildView::OnTwowayTwoway1()
{
	AddPower(L"power_ab.png");
	mCity.GameSetScore(10);
}

/*
* Power Object
*/
void CChildView::OnTwowayTwoway2()
{
	AddPower(L"power_ac.png");
	mCity.GameSetScore(10);
}

/*
* Power Object
*/
void CChildView::OnTwowayTwoway3()
{
	AddPower(L"power_bd.png");
	mCity.GameSetScore(10);
}

/*
* Power Object
*/
void CChildView::OnTwowayTwoway4()
{
	AddPower(L"power_cd.png");
	mCity.GameSetScore(10);
}

/*
* Power Object
*/
void CChildView::OnTwowayLowertwoway1()
{
	AddPower(L"power_ad.png");
	mCity.GameSetScore(10);
}

/*
* Power Object
*/
void CChildView::OnTwowayLowertwoway2()
{
	AddPower(L"power_bc.png");
	mCity.GameSetScore(10);
}

/*
* Power Object
*/
void CChildView::OnThreewayThreeway1()
{
	AddPower(L"power_abd.png");
	mCity.GameSetScore(10);
}

/*
* Power Object
*/
void CChildView::OnThreewayThreeway2()
{
	AddPower(L"power_acd.png");
	mCity.GameSetScore(10);
}
/*
* Power Object
*/
void CChildView::OnThreewayThreeway3()
{
	AddPower(L"power_bcd.png");
	mCity.GameSetScore(10);

}
/*
* Power Object
*/
void CChildView::OnPowerlineFourway()
{
	AddPower(L"power_abcd.png");
	mCity.GameSetScore(10);
}



/** \endcond */
/*
* Power Object
*/
void CChildView::OnPowersystemHualcoalforcoalpowerstation()
{
	// Haul the coal
	CHaulCoalVisitor visitor;
	mCity.Accept(&visitor);

	// Show the results
	wstringstream str;
	str << L"The total production is " << visitor.mCoalHauled << L" tons";
	AfxMessageBox(str.str().c_str());
}



/*
* Creates a construction tile object
*/
void CChildView::OnConstructionCreatetile()
{
	auto tile = make_shared<CTileConstruction>(&mCity);
	tile->SetLocation(InitialX, InitialY);
	mCity.Add(tile);
	mCity.GameSetScore(17);
	Invalidate();
}
/**
* Starts the game timer and score counter
*/
void CChildView::OnFileGamestart()
{
	mCity.SetState();
}
