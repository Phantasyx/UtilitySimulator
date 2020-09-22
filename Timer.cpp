/**
 * \file Timer.cpp
 *
 * \author Jordan Hill
 */

#include "stdafx.h"
#include "Timer.h"
#include <time.h>

using namespace Gdiplus;
/// initial font size
const auto fontSize = 14;
/// timer initial start, may depend on the processor
const int timer = 63;
/*Constructor*/
CTimer::CTimer()
{
}
/*Deconstructor*/
CTimer::~CTimer()
{
}
/*
* When started counts down timer variable
*/
int CTimer::UpdateTimer()
{
	if (mStart == true && mStartTime < 0)
	{
		mStartTime = clock()/1000 - timer;
	}
	else
	{ 
		return mStartTime; 
		mStart == false;
	}
}
/**
* Draws the timer and current number
*/
void CTimer::OnDraw(Gdiplus::Graphics *graphics, PointF position)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, fontSize);
	Color RedColor(200, 0, 0);
	SolidBrush brush(RedColor);
	auto message = L"Timer: \n" + std::to_wstring((int)UpdateTimer());
	graphics->DrawString(message.c_str(), -1, &font, position + PointF(0, fontSize/2), &brush);



}