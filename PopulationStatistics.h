/**
* \author: Robin Miller
* \file: PopulationStatistics.h
* Defines A visitor / stats file for quanitifing things about the population.
**/

#pragma once

#include "TileVisitor.h"

/**
* A visitor / stats file for quanitifing things about the population.
**/
class CPopulationStatistics
{
public:
	CPopulationStatistics();
	virtual ~CPopulationStatistics();

	void OnDraw(Gdiplus::Graphics *graphics, Gdiplus::PointF position);


	/** Collects the information **/
	class Visitor : public CTileVisitor
	{
	public:

		/** Destructor */
		virtual ~Visitor() {}

		void VisitLaborSink(CLaborSink* sink) override;

		void VisitLaborSource(CLaborSource* source) override;


		void VisitService(CTileService* source) override;
	private:
		/// The parent of this visitor
		CPopulationStatistics* mStats;

		Visitor(CPopulationStatistics* stats) : mStats(stats) {}

		friend CPopulationStatistics;
	};

	/** Get visitor for this popultion statistics to use.
	* \return the visitor.
	**/
	Visitor* GetVisitor() 
	{ 
		mWorkers = 0; 
		mJobs = 0; 
		mService = 0;
		return &mVisitor; 
	}

	/** Defines the state of a market. */
	enum Market
	{
		BALLANCED,
		UNDER,
		OVER
	};

	Market GetLaborBallance();
	Market GetDemandBallance();

private:
	/// The number of workers that we know about
	size_t mWorkers = 0;
	/// The number of jobs that we know about
	size_t mJobs = 0;
	/// The supply of serivce 
	size_t mService = 0;

	/// The visitor for counting things
	Visitor mVisitor;
};

