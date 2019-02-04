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
#include <list>

// Forward declaration of a class that does not need to be
// #include'd here.
class EntityManipulator;

/**
 The Entity class just describes some entity with a name. The entity can
 also have a parent entity. It may be null (0; there's no parent for the entity).
 Entity can also have children.
 */
class Entity {
public:
	Entity (const std::string & n);
   virtual ~Entity();
   
	void accept(EntityManipulator & manipulator, int level = 0);
	void attach(Entity * parent);
	void detach();
	Entity * getParent();
	const std::string & getName() const;

   void add(Entity * child);
   bool remove(Entity * child);
   
   bool hasChildren() const;
   void passToChildren(EntityManipulator & manipulator, int level);
   bool hasElementsAfter(const Entity * entity) const;
   
private:
	/** The entity's name. */
	std::string name;
	
	/** The parent entity of this entity. May be null (0, zero) when there's no parent. */
	Entity * parent;
   
   typedef std::list<Entity*> EntityCollection;
   
   EntityCollection children;
   
};

#endif /* defined(__EntityManipulatorExample__Entity__) */
