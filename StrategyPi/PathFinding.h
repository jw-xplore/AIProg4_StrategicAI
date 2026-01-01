#pragma once
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

struct Vector2;

struct Node;

struct Connection
{
	Node* fromNode;
	Node* node;
	float weight;
};

struct Node
{
	int x, y;
	bool walkable = true;
	std::vector<Connection*> connections;
};

struct NodeRecordAs
{
	Node* node;
	Connection* connection;
	float costSoFar;
	float costEstimated;

	bool operator==(const NodeRecordAs& other) const {
		return node == other.node && costSoFar == other.costSoFar && costEstimated == other.costEstimated;
	}
};

class PathFinding
{
public:
	std::vector<Node*> lastSearch;
	Node** nodes;
	int width, height;

	PathFinding(int w, int h);
	~PathFinding();

	//void UpdateGraph(MapEntity* mapEntity);
	void UpdateNode(int x, int y, bool walkable);
	void AddConnectionsToNode(Node* node, int x, int y);
	void DrawGraph();

	std::vector<Node*> AStar(Vector2 start, Vector2 end);

	inline int ManhattanHeuristic(const Node* start, const Node* end);
	NodeRecordAs SmallestAsRecord(std::vector<NodeRecordAs>& list);
	bool ContainsAsRecord(const std::vector<NodeRecordAs>& list, Node* node);
	NodeRecordAs* FindAsRecordFromNode(std::vector<NodeRecordAs>& list, Node* node);

};

