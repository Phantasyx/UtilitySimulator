/**
* \file ChildView.h
*
* \author Charles B. Owen
*
* \brief Class that implements the child window our program draws in.
*
* The window is a child of the main frame, which holds this
* window, the menu bar, and the status bar.
*/

#pragma once

#include "City.h"

class CTile;

/** \brief The child window our program draws in. */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
    void AddBuilding(const std::wstring &file);///
    void AddLandscape(const std::wstring &file);///
	void AddPower(const std::wstring &file);///
	void AddPowerStation(const std::wstring &file); ///  

	void AddLaborSource(const std::wstring &imageFile, const int labor);///
	void AddLaborSink(const std::wstring &imageFile, const int labor);///
	void AddService(const std::wstring &imageFile, const int service);///
    /// The city
    CCity   mCity;
	/// timer for city
	CTimer mTimer;
	



    /// True until the first time we draw
    bool mFirstDraw = true;

    long long mLastTime;    ///< Last time we read the timer
    double mTimeFreq;       ///< Rate the timer updates

    /// Any item we are currently dragging
    std::shared_ptr<CTile> mGrabbedItem;

    std::unique_ptr<Gdiplus::Bitmap> mTrashcan; ///< Trashcan image to use
    int mTrashcanTop = 0;           ///< Top line of the trashcan in pixels
    int mTrashcanRight = 0;         ///< Right side of the trashcan in pixels

	/// The image to display when moving with the mouse
	std::shared_ptr<Gdiplus::Bitmap> mNavModeActive;
	/// The image to display when scrolling is disabled
	std::shared_ptr<Gdiplus::Bitmap> mNavModeInactive;
	/// The current image to display for the nav button
	std::shared_ptr<Gdiplus::Bitmap> mNavModeImage;
	/// Is scrolling enabled?
	bool mNavModeActiveFlag = false;

	/// Point to hold where the dragging started
	CPoint mStartDragging;

	int mNavImageX;
	int mNavImageY;
	int mNavImageWidth;
	int mNavImageHeight;

	/// The current zoning selected for viewing
	CTile::Zonings mZoning = CTile::Zonings::NONE;

	/// Keeps track of the trump state of this application
	bool mTrumping = false;

	/// The translation of the city
	CPoint mTranslation;
	
	/// The scale of the city
	double mScale = 1;

	///Check electricity power
	double electricity();

public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnFileOpen();
    afx_msg void OnFileSaveas();

    /** \cond */
    afx_msg void OnBuildingsFarmhouse();
    afx_msg void OnLandscapingGrass();
    afx_msg void OnLandscapingSpartystatue();
    afx_msg void OnBuildingsBlacksmithshop();
    afx_msg void OnLandscapingTallgrass();
    afx_msg void OnBuildingsBrownhouse();
    afx_msg void OnBuildingsYellowhouse();
    afx_msg void OnBuildingsF();
    afx_msg void OnBuildingsHospital();
    afx_msg void OnBuildingsMarket();
    afx_msg void OnBuildingsCondos();
    afx_msg void OnLandscapingTree();
    afx_msg void OnLandscapingTrees();
    afx_msg void OnLandscapingBigtrees();
    afx_msg void OnLandscapingRoad();
    afx_msg void OnBusinessesCoalmine();
   
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnViewNone();
	afx_msg void OnViewReseidential();
	afx_msg void OnViewIndustrial();
	afx_msg void OnViewAgricultural();
	afx_msg void OnUpdateViewNone(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewReseidential(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewAgricultural(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewIndustrial(CCmdUI *pCmdUI);
	afx_msg void OnBuildingsCount();
	afx_msg void OnBusinessesHaulcoal();
	afx_msg void OnBusinessesTrump();
	afx_msg void OnUpdateBusinessesTrump(CCmdUI *pCmdUI);

	afx_msg void OnCounterTilesincity();
	afx_msg void OnCounterPartiallyoverlapping();
	afx_msg void OnCounterFullyoverlapped();
	afx_msg void OnPowerstationSolar();
	afx_msg void OnPowerstationCoal();
	afx_msg void OnPowerstationP();
	afx_msg void OnTwowayTwoway1();
	afx_msg void OnTwowayTwoway2();
	afx_msg void OnTwowayTwoway3();
	afx_msg void OnTwowayTwoway4();
	afx_msg void OnTwowayLowertwoway1();
	afx_msg void OnTwowayLowertwoway2();
	afx_msg void OnThreewayThreeway1();
	afx_msg void OnThreewayThreeway2();
	afx_msg void OnPowerlineFourway();
	afx_msg void OnThreewayThreeway3();
	afx_msg void OnPowersystemHualcoalforcoalpowerstation();
	afx_msg void OnConstructionCreatesite();
	afx_msg void OnBuildingsTrailerpark();
	afx_msg void OnBuildingsApartment();
	afx_msg void OnBuildingsFactory32810();
	afx_msg void OnBuildingsMill();
	afx_msg void OnBuildingsWell();
	afx_msg void OnBuildingsRecyclingcenter();
	afx_msg void OnBuildingsTrailerpark32833();
	afx_msg void OnConstructionCreatetile();
	/** \endcond */
	afx_msg void OnFileGamestart();
};

