//
//  Entity.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include "EntityComposite.h"
#include "EntityManipulator.h"

/**
 Constructor for initializing composite Entities. Parent entity is set to null.
 @param n A name for the Entity.
 @param v The value for the entity.
 */
EntityComposite::EntityComposite(const std::string & n)
: Entity(n, "") {
}


/**
 Constructor for initializing composite Entities. Parent entity is set to null.
 @param n A name for the Entity.
 @param v The value for the entity.
 */
EntityComposite::EntityComposite(const std::string & n, const std::string & v)
: Entity(n, v) {
}

/**
 Constructs a composite entity as a copy of another composite entity.
 @param another The entity to copy to this newly created entity.
 */
EntityComposite::EntityComposite(const EntityComposite & another)
: Entity(another) {
	this->repeatingEntities = another.repeatingEntities;
	std::for_each(another.children.begin(), another.children.end(), [this](Entity * entity) { add(entity->clone()); });
}

/**
 A desctructor for the Entity. Destroys all it's children if there are any.
 */
EntityComposite::~EntityComposite() {
	while (!children.empty()) {
		delete children.front();
		children.pop_front();
	}
}

/**
 Clones the Entity, creating a deep copy of the composite Entity object.
 @return Returns a copy of the cloned object.
 */
Entity * EntityComposite::clone() {
	return new EntityComposite(*this);
}

/**
 Accepts an EntityManipulator to manipulate this entity.
 @param manipulator A manipulator to accept as a visitor.
 @param level The level where the manipulator is currently travelling in the object hierarchy.
 Initially zero.
 */
void EntityComposite::accept(EntityManipulator & manipulator, int level) {
	manipulator.manipulate(*this, level);
}


/**
 Check how many children the entity has.
 @return True if entity has children.
 */
int EntityComposite::childCount() const {
	return (int)children.size();
}

/**
 Passes a manipulator to the child entities of this entity.
 @param manipulator The manipulator to pass on
 @param level The level in hierarchy of objects in a Composite manipulator is now travelling.
 */
void EntityComposite::passToChildren(EntityManipulator & manipulator, int level) {
	std::for_each(children.begin(), children.end(), [&manipulator, level] (Entity * child) {child->accept(manipulator, level);});
}

/**
 Check if the provided entity is not the last of the children of this entity.
 @param entity The entity to check if it is the last one or not.
 @return Returns true if the Entity has other entities after this in the list.
 */
bool EntityComposite::hasElementsAfter(const Entity * entity) const {
	if (children.empty()) {
		return false;
	}
	if (entity == children.back()) {
		return false;
	}
	return true;
}

/**
 Adds a child entity to this Entity.
 @param child A child to add to this entity.
 */
void EntityComposite::add(Entity * child) {
	child->attach(this);
	children.push_back(child);
}

/**
 Removes and deletes a child entity from this Entity.
 If the child is not an immediate child
 of this entity, then it is given to the children to be removed from there, if it is found.
 If the child is a Composite, removes and deletes the children too.
 @param child A child to remove from this entity.
 @return Returns true if the entity was removed, otherwise false.
 */
bool EntityComposite::remove(Entity * child) {
	// Check if this entity holds the child as an immediate child object.
	bool returnValue = false;
	auto iter = std::find(children.begin(), children.end(), child);
	// Found it so destroy it.
	if (iter != children.end()) {
		children.remove(child);
		delete *iter;
		returnValue = true;
	} else {
		// child was not an immediate child. Check if one of the children (or their child) has the child.
		// Use a lambda function to go through the children to find and delete the child.
		// std::all_of can be stopped when the child is found by returning false from the lambda.
		std::ignore = std::all_of(children.begin(), children.end(), [child, &returnValue](Entity * entity) {
			if (entity->remove(child)) {
				returnValue = true;
				return false;
			} else {
				return true;
			}
		});
	}
	return returnValue;
}

/**
 A helper struct to assist in finding an Entity with a given name. Used
 in EntityComposite::remove(const std::string &) to find an Entity with a given name.
 */
struct ElementNameMatches {
	/**
	 Constructs the search element by providing a pair of strings to compare to Entity.name and Entity.value.
	 @param nameValue The name and value strings to compare an Entity to.
	 */
	ElementNameMatches(const std::pair<std::string,std::string> & nameValue) {
		searchNameValue = nameValue;
	}
	/**
	 Stores the name and value of the Entity to search for.
	 */
	std::pair<std::string,std::string> searchNameValue;
	/**
	 Does the actual comparison of the string pair to Entity object.
	 */
	bool operator() (const Entity * e) {
		return (e->getName() == searchNameValue.first && e->getValue() == searchNameValue.second);
	}
};

/**
 Removes and deletes a child entity from this Entity.
 If the child is not an immediate child of this entity, then it is given
 to the children to be removed from there, if it is found.
 If the child is a Composite, removes and deletes the children too.
 @param nameValue A child with the equal name and value properties to remove from this entity.
 @param removeParent Removes the parent node of the child, instead of the child node.
 @return Returns true if the entity was removed, otherwise false.
 */
bool EntityComposite::remove(const std::pair<std::string,std::string> & nameValue, bool removeParent) {
	bool returnValue = false;
	auto iter = std::find_if(children.begin(), children.end(), ElementNameMatches(nameValue));
	if (iter != children.end()) {
		if (removeParent) {
			getParent()->remove(this);
			return true;
		} else {
			Entity * entity = *iter;
			children.remove(*iter);
			delete entity;
			returnValue = false;
		}
	} else {
		// child was not an immediate child. Check if one of the children (or their child) has the child.
		// Use a lambda function to go through the children to find and delete the child.
		// std::all_of can be stopped when the child is found by returning false from the lambda.
		std::ignore = std::all_of(children.begin(), children.end(), [nameValue, removeParent, &returnValue](Entity * entity) {
			if (entity->childCount() > 0 && entity->remove(nameValue, removeParent)) {
				returnValue = true;
				return false;
			} else {
				return true;
			}
		});
	}
	return returnValue;
}

void EntityComposite::setEntitiesAreRepeating(bool repeating) {
	repeatingEntities = repeating;
}

bool EntityComposite::entitiesAreRepeating() {
	return repeatingEntities;
}
