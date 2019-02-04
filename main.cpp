//
//  main.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <iostream>

#include "Entity.h"
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
         /    / \
       2.1   A.a  A.b
   */
   Entity rootEntity("root");
   Entity * thing1 = new Entity("numbers");
   rootEntity.add(thing1);
   Entity * thing2 = new Entity("1");
   thing1->add(thing2);
   thing2 = new Entity("2");
   thing1->add(thing2);
   thing1 = new Entity("21");
   thing2->add(thing1);
   
   thing1 = new Entity("letters");
   rootEntity.add(thing1);
   thing2 = new Entity("B");
   thing1->add(thing2);
   thing2 = new Entity("A");
   thing1->add(thing2);
   thing1 = new Entity("A.p");
   thing2->add(thing1);
   thing1 = new Entity("A.q");
   thing2->add(thing1);

   // ...and give the marshaller to the root entity.
   std::cout << "Marshal objects to XML..." << std::endl;
   // Create the marshaller..
   XMLMarshaller xmlMarshaller(std::cout);
   rootEntity.accept(xmlMarshaller);
   
   std::cout << std::endl << "Marshal objects to JSON..." << std::endl;
   JSONMarshaller jsonMarshaller(std::cout);
   rootEntity.accept(jsonMarshaller);
   
   return 0;
}

