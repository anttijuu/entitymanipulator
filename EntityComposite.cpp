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
EntityComposite::EntityComposite(const std::string & n, const std::string & v)
: Entity(n, v) {
}

EntityComposite::EntityComposite(const EntityComposite & another)
: Entity(another) {
   std::for_each(another.children.begin(), another.children.end(), [this](Entity * entity) { this->children.push_back(entity->clone()); });
}

/**
 A desctructor for the Entity. Destroys all it's children if there are any.
 */
EntityComposite::~EntityComposite() {
   while (!children.empty() > 0) {
      delete children.front();
      children.pop_front();
   }
}


Entity * EntityComposite::clone() {
   return new EntityComposite(*this);
}

/**
 Accepts an EntityManipulator to manipulate this entity.
 @param manipulator A manipulator to accept as a visitor.
 */
void EntityComposite::accept(EntityManipulator & manipulator, int level) {
   manipulator.manipulate(*this, level);
}


/**
 Check if entity has children.
 @return True if entity has children.
 */
bool EntityComposite::hasChildren() const {
   return !children.empty();
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
      delete *iter;
      children.remove(child);
      returnValue = true;
   } else {
      // child was not an immediate child. Check if one of the children (or their child) has the child.
      // Use a lambda function to go through the children to find and delete the child.
      // std::all_of can be stopped when the child is found by returning false from the lambda.
      std::all_of(children.begin(), children.end(), [child, &returnValue](Entity * entity) {
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
   ElementNameMatches(const std::string & name) {
      withName = name;
   }
   std::string withName;
   bool operator() (const Entity * e) {
      if (e->getName() == withName) {
         return true;
      }
      return false;
   }
};

/**
 Removes and deletes a child entity from this Entity.
 If the child is not an immediate child of this entity, then it is given
 to the children to be removed from there, if it is found.
 If the child is a Composite, removes and deletes the children too.
 @param withName A child with this name to remove from this entity.
 @return Returns true if the entity was removed, otherwise false.
 */
bool EntityComposite::remove(const std::string & withName) {
   bool returnValue = false;
   auto iter = std::find_if(children.begin(), children.end(), ElementNameMatches(withName));
   if (iter != children.end()) {
      Entity * entity = *iter;
      children.remove(*iter);
      delete entity;
      returnValue = true;
   } else {
      // child was not an immediate child. Check if one of the children (or their child) has the child.
      // Use a lambda function to go through the children to find and delete the child.
      // std::all_of can be stopped when the child is found by returning false from the lambda.
      std::all_of(children.begin(), children.end(), [withName, &returnValue](Entity * entity) {
         if (entity->remove(withName)) {
            returnValue = true;
            return false;
         } else {
            return true;
         }
      });
   }
   return returnValue;
}
