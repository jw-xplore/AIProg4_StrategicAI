/*
Entity manager handles creation, update, management and deleting of entities.
Each added entity is added to entities list and has assigned id.
Deleting entity manager handles deleting of registered entities.
*/

#pragma once
#include <raylib.h>
#include <vector>
#include "Entity.h"
#include <memory>

class Worker;

class EntityManager
{
private:
	int idToAssign = 0; // Last assigned id + 1
	
public:
	std::vector<Entity*> entities;
	std::vector<Worker*> workers;

	~EntityManager();

	void UpdateEntities(float dTime);
	void DrawEntities();
	void AddEntity(Entity* entity);
	void AddEntities(std::initializer_list<Entity*> entitiesList);
	bool RemoveEntity(Entity* entity);

	// Type specific
	//void AddWorkers(std::vector<std::weak_ptr<Worker>> workersList);
};