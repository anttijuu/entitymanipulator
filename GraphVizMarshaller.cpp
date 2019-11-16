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
: out(outputStream) {
   out << "digraph EntityGraph {" << std::endl;
   out << " node [color=antiquewhite2,style=filled];" << std::endl;
}

void GraphVizMarshaller::manipulate(EntityComposite & entity, int level) {
   Entity * parent = entity.getParent();
   std::string shape;
   if (nullptr != parent) {
      out << " \"" << parent->getValue() << "\" -> \"" << entity.getValue() << "\";" << std::endl;
      shape = "box";
   } else {
      shape = "Mdiamond";
   }
   out << " \"" << entity.getValue() << "\" [shape=\"" << shape << "\"";
   out << ",label=\"" << entity.getName() << ":" << entity.getValue() << "\"];" << std::endl;
   entity.passToChildren(*this, level++);
   if (!parent) {
      out << "}" << std::endl;
   }
}

void GraphVizMarshaller::manipulate(EntityLeaf & entity, int level) {
   Entity * parent = entity.getParent();
   if (nullptr != parent) {
      out << " \"" << parent->getValue() << "\" -> \"" << entity.getValue() << "\"" << std::endl;
   }
   out << " \"" << entity.getValue() << "\" [label=\"" << entity.getName() << ":" << entity.getValue() << "\"];" << std::endl;
}

GraphVizMarshaller::~GraphVizMarshaller() {
   // Empty
}

