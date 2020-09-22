/**
 * \file Timer.h
 *
 * \author Jordan Hill
 *
 * 
 */

#pragma once
#include "Tile.h"
/*
* Class to display a count down timer
*/
class CTimer
{
public:
	/*
	* Constructor
	*/
	CTimer();
	/*
	* Deconstructor
	*/
	~CTimer();
	/* Update time function*/
	int UpdateTimer();
	/*Status setter*/
	void SetState() { mStart = true; }
	/// Gets timer value
	int GetState() { return mStartTime; }
	/// draws timer on screen
	void OnDraw(Gdiplus::Graphics *graphics, Gdiplus::PointF);


private :
	int mStartTime = -60;/// initial start time
	bool mStart = false;/// inital start status

};

