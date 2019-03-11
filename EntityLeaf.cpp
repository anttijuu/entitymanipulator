//
//  EntityLeaf.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include "EntityLeaf.h"
#include "EntityManipulator.h"

/**
 Constructor for initializing Entities. Parent entity is set to null.
 @param name A name for the entity.
 */
EntityLeaf::EntityLeaf(const std::string & n, const std::string & v)
: Entity(n, v) {
}

EntityLeaf::EntityLeaf(const EntityLeaf & another)
: Entity(another) {
}

/**
 A desctructor for the Entity. Destroys all it's children if there are any.
 */
EntityLeaf::~EntityLeaf() {
}
/**
 Accepts an EntityManipulator to manipulate this entity.
 @param manipulator A manipulator to accept as a visitor.
 */
void EntityLeaf::accept(EntityManipulator & manipulator, int level) {
   manipulator.manipulate(*this, level);
}

/**
 Check if entity has children.
 @returns True if entity has children.
 */
bool EntityLeaf::hasChildren() const {
   return false;
}

/**
 Passes a manipulator to the child entities of this entity.
 @param manipulator The manipulator to pass on
 @param level The level in hierarchy of objects in a Composite manipulator is now travelling.
 */
void EntityLeaf::passToChildren(EntityManipulator & manipulator, int level) {
}

/**
 Check if the provided entity is not the last of the children of this entity.
 @param entity The entity to check if it is the last one or not.
 @return Returns true if the Entity has other entities after this in the list.
 */
bool EntityLeaf::hasElementsAfter(const Entity * entity) const {
   return false;
}

/**
 Adds a child entity to this Entity.
 @param child A child to add to this entity.
 */
void EntityLeaf::add(Entity * child) {
   throw std::logic_error("Cannot add children to Leaf Entity");
}

/**
 Removes a child entity from this Entity.
 @param child A child to remove from this entity. If the child is not an immediate child
 of this entity, then it is given to the children to be removed from there, if it is found.
 */
bool EntityLeaf::remove(Entity * child) {
   throw std::logic_error("Cannot remove children from Leaf Entity");
   return false;
}

bool EntityLeaf::remove(const std::string & withName) {
   throw std::logic_error("Cannot remove children from Leaf Entity");
   return false;
}
