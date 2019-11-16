# Use for building, running and generating the graph file using GraphViz.
cd build
make
./EntityManipulatorExe
dot -Tpng graph.gv -ograph.png
open graph.png
cd ..

