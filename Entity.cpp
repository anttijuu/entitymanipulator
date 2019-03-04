//
//  Entity.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include "Entity.h"
#include "EntityManipulator.h"

/**
 Constructor for initializing Entities. Parent entity is set to null.
 @param name A name for the entity.
 */
Entity::Entity (const std::string & n, const std::string & v)
  : name(n), value(v), parent(nullptr) {
}

Entity::Entity(const Entity & another)
 : name(another.name), value(another.value) {
   
}

/**
 A desctructor for the Entity. Destroys all it's children if there are any.
 */
Entity::~Entity() {
   while (!children.empty() > 0) {
      delete children.front();
      children.pop_front();
   }
}
/**
 Accepts an EntityManipulator to manipulate this entity.
 @param manipulator A manipulator to accept as a visitor.
 */
void Entity::accept(EntityManipulator & manipulator, int level) {
   manipulator.manipulate(*this, level);
}

/**
 Attaches this entity to a parent entity. Parent may be null.
 @param parent New parent for this entity.
 */
void Entity::attach(Entity * parent) {
   this->parent = parent;
}

/**
 Detaches this entity from any parent. Sets the parent to null.
 */
void Entity::detach() {
   this->parent = 0;
}

/**
 Returns the parent of this object. Note that the returned pointer may be null.
 @returns The parent pointer, may be null.
 */
Entity * Entity::getParent() {
   return this->parent;
}

/**
 Check if entity has children.
 @returns True if entity has children.
 */
bool Entity::hasChildren() const {
   return !children.empty();
}

/**
 Passes a manipulator to the child entities of this entity.
 @param manipulator The manipulator to pass on
 @param level The level in hierarchy of objects in a Composite manipulator is now travelling.
 */
void Entity::passToChildren(EntityManipulator & manipulator, int level) {
   std::for_each(children.begin(), children.end(), [&manipulator, level] (Entity * child) {child->accept(manipulator, level);});
}

/**
 Check if the provided entity is not the last of the children of this entity.
 @param entity The entity to check if it is the last one or not.
 @return Returns true if the Entity has other entities after this in the list.
 */
bool Entity::hasElementsAfter(const Entity * entity) const {
   if (children.empty()) {
      return false;
   }
   if (entity == children.back()) {
      return false;
   }
   return true;
}

/**
 Returns the name of the entity.
 @returns The entity's name.
 */
const std::string & Entity::getName() const {
   return name;
}

/**
 Returns the value of the entity.
 @return The value of the entity.
 */
const std::string & Entity::getValue() const {
   return value;
}

/**
 Adds a child entity to this Entity.
 @param child A child to add to this entity.
 */
void Entity::add(Entity * child) {
   child->attach(this);
   children.push_back(child);
}

/**
 Removes a child entity from this Entity.
 @param child A child to remove from this entity. If the child is not an immediate child
 of this entity, then it is given to the children to be removed from there, if it is found.
 */
bool Entity::remove(Entity * child) {
   // Check if this entity holds the child as an immediate child object.
   bool returnValue = false;
   auto iter = std::find(children.begin(), children.end(), child);
   // Found it so destroy it.
   if (iter != children.end()) {
      delete *iter;
      children.remove(child);
      returnValue = true;
   } else {
      // child was not an immediate child. Check if one of the children (or their child) has the child.
      // Use a lambda function to go through the children to find and delete the child.
      // std::all_of can be stopped when the child is found by returning false from the lambda.
      std::all_of(children.begin(), children.end(), [child, &returnValue](Entity * x) {
         if (x->remove(child)) {
            returnValue = true;
            return false;
         } else {
            return true;
         }
      });
   }
   return returnValue;
}
