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
 Constructor for initializing Entities. Parent Entity is set to null.
 @param name A name for the Entity.
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
}

/**
 Attaches this Entity to a parent Entity. Parent may be null.
 @param parent New parent for this Entity.
 */
void Entity::attach(Entity * parent) {
   this->parent = parent;
}

/**
 Detaches this Entity from any parent. Sets the parent to null.
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
 Returns the name of the Entity.
 @returns The Entity's name.
 */
const std::string & Entity::getName() const {
   return name;
}

/**
 Returns the value of the Entity.
 @return The value of the Entity.
 */
const std::string & Entity::getValue() const {
   return value;
}
