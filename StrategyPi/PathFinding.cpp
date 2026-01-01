#include "PathFinding.h"
#include <raylib.h>
#include <raymath.h>

PathFinding::PathFinding(int w, int h)
{
	width = w;
	height = h;
	nodes = new Node*[h];

	// Define node graph
	for (int y = 0; y < h; y++)
	{
		nodes[y] = new Node[w];

		for (int x = 0; x < w; x++)
		{
			nodes[y][x].x = x;
			nodes[y][x].y = y;
		}
	}

	// Define connections
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			AddConnectionsToNode(&nodes[y][x], x, y);
		}
	}
}

PathFinding::~PathFinding()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int ns = nodes[y][x].connections.size();

			for (int n = 0; n < ns; n++)
			{
				delete nodes[y][x].connections[n];
			}

			nodes[y][x].connections.clear();
		}
	}

	for (int y = 0; y < height; y++)
	{
		delete[] nodes[y];
	}

	delete nodes;
}

/*
Add connections to all neightbouring nodes
*/
void PathFinding::AddConnectionsToNode(Node* node, int x, int y)
{
	int w = width;
	int h = height;

	// Top
	if (y < h - 1 && nodes[y+1][x].walkable != false)
	{
		Connection* link = new Connection();
		link->fromNode = node;
		link->node = &nodes[y + 1][x];
		link->weight = 1;

		node->connections.push_back(link);
	}

	if (y < h - 1 && x < w - 1 && nodes[y + 1][x + 1].walkable != false && nodes[y + 1][x].walkable != false && nodes[y][x + 1].walkable != false)
	{
		Connection* link = new Connection();
		link->fromNode = node;
		link->node = &nodes[y + 1][x + 1];
		link->weight = 1.4f;

		node->connections.push_back(link);
	}

	// Right
	if (x < w - 1 && nodes[y][x+1].walkable != false)
	{
		Connection* link = new Connection();
		link->fromNode = node;
		link->node = &nodes[y][x + 1];
		link->weight = 1;

		node->connections.push_back(link);
	}

	if (y > 0 && x < w - 1 && nodes[y - 1][x + 1].walkable != false && nodes[y - 1][x].walkable != false && nodes[y][x + 1].walkable != false)
	{
		Connection* link = new Connection();
		link->fromNode = node;
		link->node = &nodes[y - 1][x + 1];
		link->weight = 1.4f;

		node->connections.push_back(link);
	}

	// Bottom
	if (y > 0 && nodes[y - 1][x].walkable != false)
	{
		Connection* link = new Connection();
		link->fromNode = node;
		link->node = &nodes[y - 1][x];
		link->weight = 1;

		node->connections.push_back(link);
	}

	if (y > 0 && x > 0 && nodes[y - 1][x - 1].walkable != false && nodes[y - 1][x].walkable != false && nodes[y][x - 1].walkable != false)
	{
		Connection* link = new Connection();
		link->fromNode = node;
		link->node = &nodes[y - 1][x - 1];
		link->weight = 1.4f;

		node->connections.push_back(link);
	}

	// Left
	if (x > 0 && nodes[y][x - 1].walkable != false)
	{
		Connection* link = new Connection();
		link->fromNode = node;
		link->node = &nodes[y][x - 1];
		link->weight = 1;

		node->connections.push_back(link);
	}

	if (y < h - 1 && x > 0 && nodes[y + 1][x - 1].walkable != false && nodes[y][x - 1].walkable != false && nodes[y + 1][x].walkable != false)
	{
		Connection* link = new Connection();
		link->fromNode = node;
		link->node = &nodes[y + 1][x - 1];
		link->weight = 1.4f;

		node->connections.push_back(link);
	}
}

/*
Debug draw to display connectections in the graph
*/

void PathFinding::DrawGraph()
{
	int tileSize = 32;
	int halfSize = 16;

	std::vector<Connection*> cons;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Vector2 nodePos = { x * tileSize + halfSize, y * tileSize + halfSize };

			cons = nodes[y][x].connections;

			for (int n = 0; n < cons.size(); n++)
			{
				Node* xt = cons[n]->node;
				Vector2 pos = { cons[n]->node->x * tileSize + halfSize, cons[n]->node->y * tileSize + halfSize };
				DrawLine(nodePos.x, nodePos.y, pos.x, pos.y, RED);
			}
		}
	}
}

std::vector<Node*> PathFinding::AStar(Vector2 start, Vector2 end)
{
	// Find start and end
	Node startNode = nodes[(int)start.y][(int)start.x];
	Node endNode = nodes[(int)end.y][(int)end.x];

	// Initialize start node
	NodeRecordAs startRecord;
	startRecord.node = &startNode;
	startRecord.costSoFar = 0;
	startRecord.costEstimated = ManhattanHeuristic(&startNode, &endNode);

	// Setup open and closed list
	std::vector<NodeRecordAs> open;
	open.insert(open.end(), startRecord);

	std::vector<NodeRecordAs> closed;
	NodeRecordAs current;

	while (open.size() != 0)
	{
		// Find smallest record - smallest estimated cost
		current = SmallestAsRecord(open);
		lastSearch.push_back(current.node);

		// Is at the end?
		if (current.node == &endNode)
			break;

		// Loop through connections
		for (int i = 0; i < current.node->connections.size(); i++)
		{
			Connection* connection = current.node->connections[i];

			Node* currentNode = connection->node;
			NodeRecordAs* currentNodeRecord;
			float currentNodeCost = current.costSoFar + connection->weight;

			float currentNodeHeuristics;

			// Check node in closed list
			if (ContainsAsRecord(closed, currentNode))
			{
				// Check if there is shorter route
				currentNodeRecord = FindAsRecordFromNode(closed, currentNode);
				if (currentNodeRecord->costSoFar <= currentNodeCost)
					continue;

				// Remove from closed list if it is shortest path
				closed.erase(std::remove(closed.begin(), closed.end(), *currentNodeRecord), closed.end());

				currentNodeHeuristics = currentNodeRecord->costEstimated - currentNodeRecord->costSoFar;
			}
			else if (ContainsAsRecord(open, currentNode)) // Skip if the node is open and we ve not found a better route
			{
				currentNodeRecord = FindAsRecordFromNode(open, currentNode);

				// Skip if route is not better
				if (currentNodeRecord->costSoFar <= currentNodeCost)
					continue;

				currentNodeHeuristics = connection->weight - currentNodeRecord->costSoFar;
			}
			else // Record unvisited node
			{
				currentNodeRecord = new NodeRecordAs();
				currentNodeRecord->node = currentNode;

				currentNodeHeuristics = ManhattanHeuristic(&startNode, &endNode);
			}

			// Update node cost, estimate and connection
			currentNodeRecord->connection = connection;
			currentNodeRecord->costEstimated = currentNodeCost + currentNodeHeuristics;

			// Add to open list 
			if (!ContainsAsRecord(open, currentNode))
			{
				open.insert(open.end(), *currentNodeRecord);
			}
		}

		// Release current node when done with iterating through connections
		open.erase(std::remove(open.begin(), open.end(), current), open.end());
		closed.insert(closed.end(), current);
	}

	// Format path
	std::vector<Node*> path;

	// Failed to find end?
	if (current.node != &endNode)
		return path; // Empty path
	
	// Track path
	while (current.node != &startNode)
	{
		path.insert(path.end(), current.node);
		current = *FindAsRecordFromNode(closed, current.connection->fromNode);
	}

	return path;
}

inline int PathFinding::ManhattanHeuristic(const Node* start, const Node* end)
{
    return std::abs(end->x - start->x) + std::abs(end->y - start->y);
}

NodeRecordAs PathFinding::SmallestAsRecord(std::vector<NodeRecordAs>& list)
{
	NodeRecordAs record = list[0];

	for (int i = 1; i < list.size(); i++)
	{
		if (record.costEstimated > list[i].costEstimated)
			record = list[i];
	}

	return record;
}

bool PathFinding::ContainsAsRecord(const std::vector<NodeRecordAs>& list, Node* node)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].node == node)
			return true;
	}

	return false;
}

NodeRecordAs* PathFinding::FindAsRecordFromNode(std::vector<NodeRecordAs>& list, Node* node)
{
	for (auto& record : list)
	{
		if (record.node == node)
			return &record;
	}

	return nullptr; 
}