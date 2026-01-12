#pragma once

class DecisionTreeNode
{
public:
	DecisionTreeNode() {}
	virtual DecisionTreeNode* makeDecision() { return this;  }
};

class Action : public DecisionTreeNode
{
public:
	Action* finalAction;

	virtual void execute() {}

	DecisionTreeNode* makeDecision() override
	{
		return this;
	}
};


class Decision : public DecisionTreeNode
{
public:
	DecisionTreeNode* positive;
	DecisionTreeNode* negative;

	~Decision()
	{
		if (positive)
			delete positive;

		if (negative)
			delete negative;
	}

	virtual bool pass() { return true; }

	DecisionTreeNode* makeDecision() override
	{
		if (pass())
			return positive->makeDecision();

		return negative->makeDecision();
	}
};