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
Entity::Entity (const std::string & name) : Entity(name, 0) {
}

/**
 Constructor for initializing Entities.
 @param name A name for the entity.
 @param parent The parent for this entity, may be null.
 */
Entity::Entity (const std::string & name_p, Entity * parent_p)
: name(name_p), parent(parent_p) {
}

/**
 Accepts an EntityManipulator to manipulate this entity.
 @param manipulator A manipulator to accept.
 */
void Entity::accept(EntityManipulator & manipulator) {
	manipulator.manipulate(*this);
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
 Returns the name of the entity.
 @returns The entity's name.
 */
const std::string & Entity::getName() const {
	return this->name;
}
