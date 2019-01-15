//
//  Entity.h
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __EntityManipulatorExample__Entity__
#define __EntityManipulatorExample__Entity__

#include <string>

// Forward declaration of a class that does not need to be
// #include'd here.
class EntityManipulator;

/**
 The Entity class just describes some entity with a name. The entity can
 also have a parent entity. It may be null (0; there's no parent for the entity).
 */
class Entity {
public:
	Entity (const std::string & name);
	Entity (const std::string & name_p, Entity * parent_p);
	void accept(EntityManipulator & manipulator);
	void attach(Entity * parent);
	void detach();
	Entity * getParent();
	const std::string & getName() const;
	
private:
	/** The entity's name. */
	std::string name;
	
	/** The parent entity of this entity. May be null (0, zero) when there's no parent. */
	Entity * parent;
};

#endif /* defined(__EntityManipulatorExample__Entity__) */
