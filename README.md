# EntityManipulator demonstration project

This project is meant to demonstrate the relationships between class diagrams and C++ code.

See the included png file for the class diagram, and study the code to see how the class diagram and code relate to each other.

In the main.cpp an object structure is created. Then code demonstrates two ways (JSON & XML) to externalize the object structure into a stream. The object structure looks like this:

```
            root
         /       \
      numbers   letters
     /     \    /      \
    1      2   A        B
         /    / \
       2.1   A.a  A.b
```


## Building and running the app

If you wish, you can build the app and run it to see how it works.

What you need is a C++ compiler and [CMake](https://cmake.org) build system.

After installing the tools, do this in the project root directory:

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
<entity name="root">
  <entity name="numbers">
    <entity name="1">
    </entity>
    <entity name="2">
      <entity name="21">
      </entity>
    </entity>
  </entity>
  <entity name="letters">
    <entity name="A">
      <entity name="A.p">
      </entity>
      <entity name="A.q">
      </entity>
    </entity>
  </entity>
</entity>

Marshal objects to JSON...
{
  "name" : "root",
  "children" : 
  [
    {
    "name" : "numbers",
    "children" : 
    [
      {
      "name" : "1"
      },
      {
      "name" : "2",
      "children" : 
      [
        {
        "name" : "21"
        }
      ]
      }
    ]
    },
    {
    "name" : "letters",
    "children" : 
    [
      {
      "name" : "A",
      "children" : 
      [
        {
        "name" : "A.p"
        },
        {
        "name" : "A.q"
        }
      ]
      }
    ]
    }
  ]
}
```

## Who made this

Originally developed by Toni Räisänen, modified by Antti Juustila (INTERACT Research Group)
Study Program of Information Processing Science, University of Oulu, Finland
