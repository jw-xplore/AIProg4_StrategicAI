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