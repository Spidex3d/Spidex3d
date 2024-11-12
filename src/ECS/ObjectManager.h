#pragma once
#include <iostream>
#include "Components.h"

bool AddDefaultCube = false;
int cubeIndex = 0;


class ObjectManager
{
public:
	static ObjectManager* Instance() {
		static ObjectManager* component = new ObjectManager;

		return component;
	}

	void Initialize() {

		std::cout << "Testing Object Manager " << std::endl;

	}

    template<typename T>
    void Print(T value) {
        std::cout << value << std::endl;
    }
    template<typename T1, typename T2>
    void print(const T1& val1, const T2& val2) {
        std::cout << val1 << ' ' << val2 << '\n';
    }  
    
    template<typename T1, typename T2, typename T3>
    void Transforms(const T1& val1, const T2& val2, const T3& val3) {
        position(val1, val2, val3);

    }

    void AddObjectCube() {

        

        Print("My Button to add a cube from a class ");
        print(dc, cubeIndex);
        std::cout << "Index " << cubeIndex << std::endl;
        print(idxTx, cubeIndex);
        std::cout << "Transform " << std::endl;
        std::cout << "Scale " << std::endl;
        

        AddDefaultCube = true;
        cubeIndex++;

    }
    void RemoveObject() {

    }

private:
    std::string dc{ "DefaultCube_" };
    std::string idxTx{ "Index_" };
   
	int m_defaultCube = 1;  // type of object
	int m_defaultCubeIndex; // index of object
};
/*
Entity component system;
Entity id = 1 to 32; or more this is just a starting point
  |__ if EntityID is 1 then its a cube
   cube Has
    | __ CubeIdName = "DefaultCube"					  string
    | __ CubeIdIndex = 0							  int
    | __ CubeData = vertices & indices & normals	  float
    | __ CubeTexID = "crate.jpg"					  string
    | __ ComponentType has transform id = TransID     float Always starts at 0, 0, 0
    | __ ComponentType has Scale     id = ScaleID     float Always starts at 1, 1, 1
    | __ ComponentType has rotation  id = RotationID  float Always starts at 0, 0, 0
    | __ entities.push_back all the above
    | __ Render entities on screen
    | __ Make ajustment to the settings:- pos, scale, rotation, texture, cube name
    | __ Render entities on screen
    | __ entities.push_back all the above changes
        | __ Save this Data to the Scean File
            | __ Retrive the Data of the Scean File
                | __ Render it all
                // All we are interested in at the moment is the default cube nothing else
Entity 1 = defaultcube has Name Trasform Scale Rotation Texture
Entity 2 = HybridCube has trasform scale rotation colition gravaty texture
Entity 3 = Sphere
Entity 3 = Ico Sphere
Entity 4 = Cylinder
Entity 5 = Plane
Entity 6 = Cone
Entity 7 = Torus
Entity 8 = pyromid
Entity 9 = Capsule
Entity 10 = Spider obj
Entity 11 = Line
Entity 12 = Circle
Entity 13 = Text
Entity 14 + = import obj

Light 1 = Point
Light 2 = Area
Light 3 = Spot
Light 4 = Sun

Camera 1 = main

Sky 1 = Main
Terrain 1 = Main
*/


