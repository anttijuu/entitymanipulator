//
//  main.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <iostream>

#include "EntityComposite.h"
#include "EntityLeaf.h"
#include "XMLMarshaller.h"
#include "JSONMarshaller.h"

int main(int argc, const char * argv[])
{
   // Create a following structure of objects...
   /*
    root
    /       \
    numbers   letters
    /     \    /      \
    1      2   A        B
    /   / \
    21 A.p  A.q
    */
   try {
      EntityComposite rootEntity("root", "The root object");
      Entity * thing1 = new EntityComposite("numbers", "All the numbers...");
      rootEntity.add(thing1);
      Entity * thing2 = new EntityLeaf("1", "The only one");
      thing1->add(thing2);
      thing2 = new EntityComposite("2", "Second after one");
      thing1->add(thing2);
      thing1 = new EntityLeaf("21", "Ventti");
      thing2->add(thing1);
      
      thing1 = new EntityComposite("letters", "a-b-c");
      rootEntity.add(thing1);
      thing2 = new EntityLeaf("B", "beta");
      thing1->add(thing2);
      thing2 = new EntityComposite("A", "alpha");
      thing1->add(thing2);
      thing1 = new EntityLeaf("A.p", "alpha pi");
      thing2->add(thing1);
      thing1 = new EntityLeaf("A.q", "alpha queue");
      thing2->add(thing1);
      
      // ...and give the marshaller to the root entity.
      std::cout << "Marshal objects to XML..." << std::endl << std::endl;
      // Create the marshaller..
      XMLMarshaller xmlMarshaller(std::cout);
      rootEntity.accept(xmlMarshaller);
      
      std::cout << std::endl << "Marshal objects to JSON..." << std::endl << std::endl;
      JSONMarshaller jsonMarshaller(std::cout);
      rootEntity.accept(jsonMarshaller);
      
      std::cout << "Cloning root entity and removing letters from clone..." << std::endl << std::endl;
      Entity * newComposite = rootEntity.clone();
      newComposite->remove("letters");
      std::cout << "Marshal objects to XML..." << std::endl << std::endl;
      newComposite->accept(xmlMarshaller);
      std::cout << std::endl << "Marshal objects to JSON..." << std::endl << std::endl;
      newComposite->accept(jsonMarshaller);
      delete newComposite;
      
   } catch (std::exception & e) {
      std::cout << "ERROR: " << e.what() << std::endl;
   }
   
   return 0;
}

