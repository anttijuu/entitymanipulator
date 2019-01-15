# EntityManipulator demonstration project

This project is meant to demonstrate the relationships between class diagrams and C++ code.

See the included png file for the class diagram, and study the code to see how the class diagram and code relate to each other.

## Building and running the app

If you wish, you can build the app and run it to see how it works.

What you need is a C++ compiler and [CMake](https://cmake.org) build system.

After installing the tools, do this in the project directory:

1. mkdir build
2. cd build
3. cmake ..
4. make

After this, you should have a binary executable EntityManipulatorExe in the build directory.

You can then execute it and see the results:


```
Antti-iMac:build anttijuustila$ ./EntityManipulatorExe 
Marshal objects to XML...
<?xml version="1.0"?>
<entity name="Level 0">
 <entity name="Level 1">
  <entity name="Level 2">
  </entity>
 </entity>
</entity>

Marshal objects to JSON...
{
  "entity" : {
    "name : "Level 0"
    "entity" : {
      "name : "Level 1"
      "entity" : {
        "name : "Level 2"
      }
    }
  }
}
```

## Who made this

Originally developed by Toni Räisäinen, modified by Antti Juustila
Study Program of Information Processing Science, University of Oulu, Finland
