/** 
* \file: GameState.h
* \author: Robin Miller, Jordan Hill
*
* Provides the definition of the game state.
*/

#pragma once
#include <memory>
#include "XmlNode.h"
#include "Timer.h"

/** The game state */
class CGameState
{
public:
	CGameState();
	virtual ~CGameState();

	/**
	* Sets the base score
	* \param baseScore the base score
	*/
	void SetBaseScore(double baseScore) 
	{ 
		if (mStart == true)
			mBaseScore = baseScore; 
	}
	/**
	* Gets the base score.
	* \return the base score.
	*/
	double GetBaseScore() { return mBaseScore; }

	/**
	* Sets the score multiplier
	* \param multiplier the score multiplier
	*/
	void SetMultiplier(double multiplier) { mMultiplier = multiplier; }
	/**
	* Gets the score multiplier.
	* \return the score multiplier.
	*/
	double GetMultipler() { return mMultiplier; }

	/**
	* Gets the score.
	* \return the score.
	*/
	double GetScore() { return mMultiplier * mBaseScore; }

	/**
	* Sets the game state
	*/
	void SetStatus() { mStart = true; }

	void XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);
	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	void Draw(Gdiplus::Graphics *graphics, Gdiplus::PointF);

private:
	/// The base score in the game
	double mBaseScore = 0;
	/// The score multipliler
	double mMultiplier = 1;
	/// flag for game state
	bool mStart = false;
};

