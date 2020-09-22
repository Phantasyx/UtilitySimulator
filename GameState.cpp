/**
* \file: GameState.h
* \author: Robin Miller
*/


#include "stdafx.h"
#include "GameState.h"
using namespace Gdiplus;


const auto BaseScoreKey = L"game-state-base-score";
const auto MultiplierKey = L"game-state-multiplie";
const auto FontSize = 16;

/** Constructor */
CGameState::CGameState()
{
}

/** Destructor */
CGameState::~CGameState()
{
}

/** Saves this game state to the given node
*/
void CGameState::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) {
	node->SetAttribute(BaseScoreKey, mBaseScore);
	node->SetAttribute(MultiplierKey, mMultiplier);
}

/** Load from XML
* \parma node the node to load from
*/
void CGameState::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) {
	mBaseScore = node->GetAttributeDoubleValue(BaseScoreKey, 0);
	mMultiplier = node->GetAttributeDoubleValue(MultiplierKey, 1);
}

/** Draws the game state to the screen
* \param graphics the graphics context
* \param position Where to draw
*/
void CGameState::Draw(Gdiplus::Graphics *graphics, PointF position) {
	// Load the font
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, FontSize);
	// Setup the brush
	Color brushColor(0, 255, 0);
	SolidBrush brush(brushColor);
	// Display the message
	auto message = L"SCORE\n" + std::to_wstring((int) mBaseScore) + L" x " + std::to_wstring((int) mMultiplier) + L" = " + std::to_wstring((int) GetScore());
	graphics->DrawString(message.c_str(), -1, &font, position + PointF(0, FontSize / 2), &brush);
}