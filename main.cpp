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
    // Create the marshaller..
    XMLMarshaller xmlMarshaller(std::cout);
    // Create the entity objects, second having the first as parent, third as second as a parent...
    Entity level0Entity("Level 0");
    Entity level1Entity("Level 1", &level0Entity);
    Entity level2Entity("Level 2", &level1Entity);
    // ...and give the marshaller to the level 2 entity.
    std::cout << "Marshal objects to XML..." << std::endl;
    level2Entity.accept(xmlMarshaller);
    
    std::cout << std::endl << "Marshal objects to JSON..." << std::endl;
    JSONMarshaller jsonMarshaller(std::cout);
    level2Entity.accept(jsonMarshaller);
    
    return 0;
}

