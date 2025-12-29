#include "EntityManager.h"
#include "Worker.h"

EntityManager::~EntityManager()
{
	// Delete and clear entity list
	for (int i = 0, size = entities.size(); i < size; i++)
	{
		delete entities[i];
	}

	entities.clear();
}

void EntityManager::UpdateEntities(float dTime)
{
	// Regular update
	for (int i = 0, size = entities.size(); i < size; i++)
	{
		entities[i]->Update(dTime);
	}

	for (int i = 0, size = workers.size(); i < size; i++)
	{
		workers[i]->Update(dTime);
	}
}

void EntityManager::DrawEntities()
{
	// Regular update
	for (int i = 0, size = entities.size(); i < size; i++)
	{
		entities[i]->Draw();
	}

	for (int i = 0, size = workers.size(); i < size; i++)
	{
		workers[i]->Draw();
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	entity->SetId(idToAssign);
	idToAssign++;

	entities.insert(entities.end(), entity);
}

void EntityManager::AddEntities(std::initializer_list<Entity*> entitiesList)
{
	for (int i = 0; i < entitiesList.size(); i++)
	{
		AddEntity(entitiesList.begin()[i]);
	}
}

// Find selected entity and delete it
bool EntityManager::RemoveEntity(Entity* entity)
{
	for (int i = 0, size = entities.size(); i < size; i++)
	{
		// Remove found enetity from list and delete it
		if (entities[i] == entity)
		{
			entities.erase(entities.begin() + i);
			delete entity;
			return true; // Notify success
		}
	}

	// Entity couldn't be removed 
	return false;
}

// Type specific
void EntityManager::AddWorkers(std::initializer_list<Worker*> workersList)
{
	int start = workers.size();
	int end = workersList.size();

	int size = start + end;
	workers.resize(size);

	for (int i = start; i < end; i++)
	{
		workers[i] = workersList.begin()[i - start];
	}
}