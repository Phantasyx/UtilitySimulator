/**
* \file TilePower.h
*
* \author Junshan Luo
*
* \brief Class that implements a poer grid
*/

#pragma once
#include "Tile.h"
#include "TileCoalmine.h"
#include "ChildView.h"
#include "GameState.h"

/**
* \brief A power grid tile
*/
class CTilePower : public CTile
{
public:
	//constructor
	CTilePower(CCity *city);

	/// \brief Default constructor (disabled)
	CTilePower() = delete;

	/// \brief Copy constructor (disabled)
	CTilePower(const CTilePower &) = delete;

	//destructor
	~CTilePower();
	//Xml save function
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	//xml load function
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitPower(this); }
	virtual void changeelectric(int x,int y)
	{
		if (electric)
		{
			std::wstring newfile = file.substr(0, 5) + file.substr(10);
			this->SetImage(newfile);
			file = newfile;
			electric = !electric;
			std::shared_ptr<CTile> upperleft = this->GetAdjacent(-1, -1);
			if (upperleft != nullptr && (x != -1 || y != -1))
			{

				upperleft->changeelectric(1, 1);
			}
			std::shared_ptr<CTile> upperright = this->GetAdjacent(1, -1);
			if (upperright != nullptr && (x != 1 || y != -1))
			{
				upperright->changeelectric(-1, 1);
			}
			std::shared_ptr<CTile> lowerleft = this->GetAdjacent(-1, 1);
			if (lowerleft != nullptr && (x != -1 || y != 1))
			{
				lowerleft->changeelectric(1, -1);
			}
			std::shared_ptr<CTile> lowerright = this->GetAdjacent(1, 1);
			if (lowerright != nullptr && (x != 1 || y != 1))
			{
				lowerright->changeelectric(-1, -1);
			}
		}
		else
		{
			std::wstring temp = L"spark";
			std::wstring newfile = file.substr(0, 5) + temp + file.substr(5);
			this->SetImage(newfile);
			file = newfile;
			electric = !electric;
			std::shared_ptr<CTile> upperleft = this->GetAdjacent(-1, -1);
			if (upperleft != nullptr && (x != -1 || y != -1))
			{

				upperleft->changeelectric(1, 1);
			}
			std::shared_ptr<CTile> upperright = this->GetAdjacent(1, -1);
			if (upperright != nullptr && (x != 1 || y != -1))
			{
				upperright->changeelectric(-1, 1);
			}
			std::shared_ptr<CTile> lowerleft = this->GetAdjacent(-1, 1);
			if (lowerleft != nullptr && (x != -1 || y != 1))
			{
				lowerleft->changeelectric(1, -1);
			}
			std::shared_ptr<CTile> lowerright = this->GetAdjacent(1, 1);
			if (lowerright != nullptr && (x != 1 || y != 1))
			{
				lowerright->changeelectric(-1, -1);
			}
		}
	}
	//a funtion that set file name
	void setfile(std::wstring mfile)
	{
		file = mfile;
	}
	//a function that sets score
	void PowerSetScore()
	{
		mGameState.SetBaseScore(10);
	}
private:
	//file name
	std::wstring file;
	// a bool to check electricity
	bool electric = false;
	CGameState mGameState;
};


