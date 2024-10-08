//
//  EntityComposite.h
//  EntityCompositeManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#pragma once

#include <string>
#include <list>

#include "Entity.h"

// Forward declaration of a class that does not need to be
// #include'd here.
class EntityManipulator;

/**
 The EntityComposite class describes an Entity which is also a Composite.
 EntityComposite can have children.
 */
class EntityComposite : public Entity {
public:
	EntityComposite(const std::string & n);
	EntityComposite(const std::string & n, const std::string & v);
   EntityComposite(const EntityComposite & another);
   virtual ~EntityComposite();
   
   virtual Entity * clone() override;
   
   virtual void accept(EntityManipulator & manipulator, int level = 0) override;
   virtual void add(Entity * child) override;
   virtual bool remove(Entity * child) override;
   virtual bool remove(const std::pair<std::string,std::string> & nameValue, bool removeParent = false) override;
   
   virtual int childCount() const override;
   virtual void passToChildren(EntityManipulator & manipulator, int level) override;
   virtual bool hasElementsAfter(const Entity * entity) const override;
   
	bool entitiesAreRepeating();
	void setEntitiesAreRepeating(bool repeating);

private:
   EntityComposite() = delete;
   
   typedef std::list<Entity*> EntityCollection;
   /** The child Entities of the Composite Entity. */
   EntityCollection children;
   
	bool repeatingEntities;
};

// EOF
