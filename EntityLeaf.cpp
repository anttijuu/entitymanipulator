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
 A desctructor for the Entity.
 */
EntityLeaf::~EntityLeaf() {
}


Entity * EntityLeaf::clone() {
   return new EntityLeaf(*this);
}

/**
 Accepts an EntityManipulator to manipulate this entity.
 @param manipulator A manipulator to accept as a visitor.
 */
void EntityLeaf::accept(EntityManipulator & manipulator, int level) {
   manipulator.manipulate(*this, level);
}

/**
 Check the Entity's child count which is always zero for a Leaf entity.
 @returns Zero (0), since Leaf entity does not have children.
 */
int EntityLeaf::childCount() const {
   return 0;
}

/**
 Passes a manipulator to the child entities of this entity.
 @param manipulator The manipulator to pass on
 @param level The level in hierarchy of objects in a Composite manipulator is now travelling.
 */
void EntityLeaf::passToChildren(EntityManipulator & /*manipulator*/, int /*level*/) {
}

/**
 Check if the provided entity is not the last of the children of this entity.
 @param entity The entity to check if it is the last one or not.
 @return Returns always false since Leaf entities cannot have children.
 */
bool EntityLeaf::hasElementsAfter(const Entity * /*entity*/) const {
   return false;
}

/**
 Since leaf entities cannot have children will throw an exception if called.
 @param child A child to add to this entity.
 */
void EntityLeaf::add(Entity * /*child*/) {
   throw std::logic_error("Cannot add children to Leaf Entity");
}

/**
 Removes a child entity from this Entity, but leaf entity has no children so exception is thrown.
 @param child A child to remove from this entity. Since the operation is not possible, an exception
 is thrown to indicate a logic error in attempting to remove children from leaf Entity.
 */
bool EntityLeaf::remove(Entity * /*child*/) {
   throw std::logic_error("Cannot remove children from Leaf Entity");
   return false;
}

/**
 Leaf entity has no children so exception is thrown if called.
 @param child A child to remove from this entity. Since the operation is not possible, an exception
 is thrown to indicate a logic error in attempting to remove children from leaf Entity.
 */
bool EntityLeaf::remove(const std::pair<std::string,std::string> & /*nameValue*/) {
   throw std::logic_error("Cannot remove children from Leaf Entity");
   return false;
}
