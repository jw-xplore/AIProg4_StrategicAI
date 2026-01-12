#pragma once
#include "DecisionTree.h"

/*
Defines all decisions and actions blocks used for commander
*/

class Commander;

//---------------------------------------------------------------
// Decisions
//---------------------------------------------------------------

class BuildingExists : public Decision
{
	Commander* commander;
	BuildingExists(Commander* cmd) { commander = cmd; }

	virtual bool pass() override
	{
		return true;
	}
};

//---------------------------------------------------------------
// Actions
//---------------------------------------------------------------

/*
template <typename T>class BuildingExists : public Action<Commander>
{
	void execute(World& actor) override
	{

	}
};
*/