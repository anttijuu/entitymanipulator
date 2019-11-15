//
//  GraphVizMarshaller.cpp
//  EntityManipulatorExe
//
//  Created by Antti Juustila on 15.11.2019.
//

#include "GraphVizMarshaller.h"
#include "EntityComposite.h"
#include "EntityLeaf.h"


GraphVizMarshaller::GraphVizMarshaller(std::ostream & outputStream)
: output(outputStream) {
   output << "digraph EntityGraph {" << std::endl;
}

void GraphVizMarshaller::manipulate(EntityComposite & entity, int level) {
   Entity * parent = entity.getParent();
   if (nullptr != parent) {
      output << " " << parent->getValue() << " -> " << entity.getValue() << std::endl;
   }
   entity.passToChildren(*this, level++);
   if (!parent) {
      output << "}" << std::endl;
   }
}

void GraphVizMarshaller::manipulate(EntityLeaf & entity, int level) {
   Entity * parent = entity.getParent();
   if (nullptr != parent) {
      output << " " << parent->getValue() << " -> " << entity.getValue() << std::endl;
   }
}

GraphVizMarshaller::~GraphVizMarshaller() {
}

