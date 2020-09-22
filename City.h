/**
 * \file City.h
 *
 * \author Charles B. Owen
 *
 * \brief Class that implements a simple city with tiles we can manipulate
 */

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <utility>

#include "XmlNode.h"
#include "Tile.h"
#include "PopulationStatistics.h"
#include "GameState.h"
#include "Timer.h"

/**
 * \brief Implements a simple city with tiles we can manipulate
 */
class CCity
{
public:
    CCity();
    virtual ~CCity();

    /// The spacing between grid locations
    static const int GridSpacing = 32;


    void Add(std::shared_ptr<CTile> item);
	std::shared_ptr<CTile> HitTest(int x, int y);
    void MoveToFront(std::shared_ptr<CTile> item);
    void DeleteItem(std::shared_ptr<CTile> item);
	void GameSetScore(int score)
	{
		if (mTimer.GetState() != 0)
			mGameState.SetBaseScore(mGameState.GetBaseScore()+score);
	}
    void OnDraw(Gdiplus::Graphics *graphics, CPoint translation, double scale);

    void Save(const std::wstring &filename);
    void Load(const std::wstring &filename);
    void Clear();

    void Update(double elapsed);
    void SortTiles();

    std::shared_ptr<CTile> GetAdjacent(std::shared_ptr<CTile> tile, int dx, int dy);
    std::shared_ptr<CTile> GetAdjacent(CTile *tile, int dx, int dy);

	/** Iterator that iterates over the city tiles */
	class Iter
	{
	public:
		/** Constructor
		* \param city The city we are iterating over */
		Iter(CCity *city, int pos) : mCity(city), mPos(pos) {}

		/** Test for end of the iterator
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTile> operator *() const { return mCity->mTiles[mPos]; }

		/** Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}


	private:
		CCity *mCity;   ///< City we are iterating over
		int mPos;       ///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mTiles.size()); }

	/** An iterator to the tiles in a given zoning */
	class ZoningIter{
	public: 
		ZoningIter(CCity* city, CTile::Zonings zoning, int pos) : mCity(city), mZoning(zoning), mPos(pos){
			while (mPos < mCity->mTiles.size() && mCity->mTiles[mPos]->GetZoning() != mZoning) {
				++mPos;
			}
	}

		/** Tests iterator inequality *
		* \return True if this iterator is not equal to the other iterator. */
		bool operator!=(const ZoningIter& iter)
		{
			return mPos != iter.mPos;
		}

		/** Get the value of this iterator's position 
		* \return a pointer to a tile. */
		std::shared_ptr<CTile> operator*() { return mCity->mTiles[mPos]; }

		/** Advance this iterator to the next position in the list 
		* \return This iterator. */
		const ZoningIter& operator++() {
			// Loop until we reach the end of the tiles list or we get to a tile with the right zoning
			do{
				++mPos;
			} while (mPos < mCity->mTiles.size() && mCity->mTiles[mPos]->GetZoning() != mZoning);

			return *this;
		}
	private:
		/// The City we are searching
		CCity* mCity;
		/// Our position in the list of tiles
		int mPos;
		/// The filter we are searching for
		CTile::Zonings mZoning;
	};

	/** A class we return to support iterating over
	* only specific zonings in the collection */
	class ZoningIterSupport
	{
	public:
		/** Constructor
		* \param city The city we are iterating over
		* \param zoning The zoning we are interested in */
		ZoningIterSupport(CCity *city, CTile::Zonings zoning) : mCity(city), mZoning(zoning) {}

		/** Get an iterator for the beginning of the collection
		* \returns Iter object at position 0 */
		ZoningIter begin() { return ZoningIter(mCity, mZoning, 0); }

		/** Get an iterator for the end of the collection
		* \returns Iter object at position past the end */
		ZoningIter end() { return ZoningIter(mCity, mZoning, mCity->mTiles.size()); }

	private:
		CCity *mCity;
		CTile::Zonings mZoning;
	};

	/** Get a zoning iterator support object
	* \param zoning The zoning we are interested in
	* \returns ZoningIterSupport object
	*/
	ZoningIterSupport GetZoning(CTile::Zonings zoning) { return ZoningIterSupport(this, zoning); }

	/** Accept a visitor for the collection
	* \param visitor The visitor for the collection
	*/
	void CCity::Accept(CTileVisitor *visitor)
	{
		for (auto tile : mTiles)
		{
			tile->Accept(visitor);
		}
	}

	/**
	* Sets the state for the timer class
	*/
	void SetState()
	{ 
		mTimer.SetState();
		mGameState.SetStatus();
	}

private:
    void XmlTile(const std::shared_ptr<xmlnode::CXmlNode> &node);
    void BuildAdjacencies();

    /// All of the tiles that make up our city
    std::vector<std::shared_ptr<CTile> > mTiles;

    /// Adjacency lookup support
    std::map<std::pair<int, int>, std::shared_ptr<CTile> > mAdjacency;

	/// The population statitics for this city
	CPopulationStatistics mStats;

	/// The game state for the city
	CGameState mGameState;

	/// the timer for the game
	CTimer mTimer;
};

