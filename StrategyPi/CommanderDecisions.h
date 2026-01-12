#pragma once
#include "DecisionTree.h"

/*
Defines all decisions and actions blocks used for commander
*/

class Commander;
class Task;
enum EMaterialResourceType;

namespace CommanderDecisions
{

	//---------------------------------------------------------------
	// Decisions
	//---------------------------------------------------------------

	class BuildingExists : public Decision
	{
	public:
		Commander* commander;
		EMaterialResourceType buildingType;

		BuildingExists(Commander* cmd, EMaterialResourceType type) { commander = cmd; buildingType = type; }
		virtual bool pass() override;
	};

	class HasEnoughResources : public Decision
	{
	public:
		Commander* commander;
		EMaterialResourceType goal;
		EMaterialResourceType type;

		HasEnoughResources(Commander* cmd, EMaterialResourceType goal, EMaterialResourceType type)
		{ 
			commander = cmd;
			this->goal = goal;
			this->type = type;
		}

		virtual bool pass() override;
	};

	//---------------------------------------------------------------
	// Actions
	//---------------------------------------------------------------

	class AssignTask : public Action
	{
	public:
		Commander* commander;
		Task* task;

		AssignTask(Commander* cmd, Task* task) { commander = cmd; this->task = task; }
		virtual void execute() override;
	};
	
	//---------------------------------------------------------------
	// Custom
	//---------------------------------------------------------------

	class HasRequiredResources : public DecisionTreeNode
	{
	public:
		Commander* commander;
		EMaterialResourceType goal;

		DecisionTreeNode* woodNode;
		DecisionTreeNode* coalNode;
		DecisionTreeNode* ironNode;
		DecisionTreeNode* swordsNode;
		DecisionTreeNode* continueNode;

		HasRequiredResources(Commander* cmd, EMaterialResourceType goal) { commander = cmd; this->goal = goal; }
		void SetupNodes(DecisionTreeNode* wood, DecisionTreeNode* coal, DecisionTreeNode* iron, DecisionTreeNode* swords)
		{
			woodNode = wood;
			coalNode = coal;
			ironNode = iron;
			swordsNode = swords;
		}

		virtual DecisionTreeNode* makeDecision() override;
	};

}