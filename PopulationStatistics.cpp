#include "stdafx.h"
#include "PopulationStatistics.h"
#include "LaborSink.h"
#include "LaborSource.h"
#include "TileService.h"

using namespace Gdiplus;


/// Min wokers to jobs ratio
const double UndersaturatedJobMarket = 0.9;
/// Min demand to suppy ratio
const double DemandSuppyRatio = 0.9;

/// the size of the font
const int FontSize = 12;

CPopulationStatistics::CPopulationStatistics() : mVisitor(this)
{
}


CPopulationStatistics::~CPopulationStatistics()
{
}

/** Calculates the ballance of the labor market
* \return the state of the labor market
*/
CPopulationStatistics::Market CPopulationStatistics::GetLaborBallance()
{
	// Calculate the ratio of workers to jobs
	double workersToJobs = ((double)mWorkers) / ((double)(mJobs + 1));
	if (workersToJobs < UndersaturatedJobMarket)
	{
		return Market::UNDER;
	}
	else if (workersToJobs > 1 / UndersaturatedJobMarket)
	{
		return Market::OVER;
	}
	return Market::BALLANCED;
}

/** Calculates the ballance of the demand market
* \return the state of the job market
*/
CPopulationStatistics::Market CPopulationStatistics::GetDemandBallance()
{	// Calculate the ratio of workers to demand
	double demandSupply = ((double)mWorkers) / ((double)1 + mService);
	if (demandSupply < DemandSuppyRatio)
	{
		return Market::UNDER;
	}
	else if (demandSupply > 1 / DemandSuppyRatio)
	{
		return Market::OVER;
	}
	return Market::BALLANCED;
}

void CPopulationStatistics::OnDraw(Gdiplus::Graphics *graphics, PointF position)
{
	// Load the font
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, FontSize);

	Color red(255, 0, 0);
	Color green(0, 255, 0);

	SolidBrush brush(green);
		
	auto laborBallance = GetLaborBallance();
	auto demandBallance = GetDemandBallance();

	// Build the message to display
	std::wstring message = L"The job market is";
	if (laborBallance == Market::UNDER)
	{
		message += L" undersaturated";
		brush.SetColor(red);
	} 
	else if (laborBallance == Market::OVER) 
	{
		message += L" oversaturated";
		brush.SetColor(red);
	}

	message += L" (workers):(jobs) = " + std::to_wstring(mWorkers) + L":" + std::to_wstring(mJobs);
	graphics->DrawString(message.c_str(), -1, &font, position, &brush);

	message = L"\nThe service market is ";
	brush.SetColor(green);

	double demandSupply = ((double) mWorkers) / ((double)1 + mService);
	if (demandBallance == Market::UNDER)
	{
		message += L" undersaturated";
		brush.SetColor(red);
	}
	else if (demandBallance == Market::OVER)
	{
		message += L" oversaturated";
		brush.SetColor(red);
	}
	message += L" (demand):(supply) = " + std::to_wstring(mWorkers) + L":" + std::to_wstring(mService);
	graphics->DrawString(message.c_str(), -1, &font, position + PointF(0, FontSize / 2), &brush);
}


/** Update the stats
* \param sink the sink to count 
**/
void CPopulationStatistics::Visitor::VisitLaborSink(CLaborSink* sink) 
{
	mStats->mJobs += sink->GetRequiredLabor();
}

/** Update the stats
* \param source the source to count
**/
void CPopulationStatistics::Visitor::VisitLaborSource(CLaborSource* source)
{
	mStats->mWorkers += source->GetAvailableLabor();
}

/** Update the stats
* \param service the service to count
**/
void CPopulationStatistics::Visitor::VisitService(CTileService* service)
{
	mStats->mService += service->GetAvailableService();
}