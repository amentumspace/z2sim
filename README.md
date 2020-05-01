# Geant4 Simulation With Space Suit

## Build Instructions
Assuming a working Geant4 installation is active in you user environment, in this directory:
```
mkdir build
cd build/
cmake ..
make
```
The macro commands present in `sim.cc` assume Geant4 has OpenGL visualisation capabilities enabled. 

## Run Instructions
To run the simulation, in the build directory:
```
./sim
```
The required geometry file is automatically copied to the build directory.

## Loading Parts
The detector construction loads all of the parts that make up the suit as contained in an OBJ file.
The parts to load are specified in `src/DetectorConstruction.cc` around like 25.
Comment in or out parts to load as desired, and specify the material name for each part to use as indicated.
```
parts = {

// BACKPACK //
{ "plss-seal_", "G4_WATER" },
{ "plss-cowling_", "G4_WATER" },
//{ "plss-patch_", "G4_WATER" },
...

```
The units in the geometry file are assumed to the meters, however this scale/value can be changed on line 116 of the `src/DetectorConstruction.cc` file:
```
mesh->SetScale(m);
```

## Editing Parts
All parts are assumed to be shells with a thickness where appropriate.
These shells are generated from the provided surfaces meshes using Blender.
Using the provided `suit.blend` file, these thicknesses can be modified by choosing the target part in "Object Mode", and editing the "Thickness" of the "Solidify" modifier that has been attached to the part.

To export the OBJ geometry file to load into the Geant4 simulation, use the "File > Export > Wavefront (.obj)" option.
On the export screen the "Objects as OBJ Objects" check box must be selected rather than the "Obects as OBJ Groups" checkbox.

If the names of parts are changed in Blender, or new parts of added, the parts list must be updated in the `DetectorConstruction.cc` file as appropriate.
Not that Blender adds extra characters after object names during export by appending `_stuff`.

## Updating CADMesh
CADMesh is used to load in the OBJ file into the detector construction.
If a new or updated version of CADMesh becomes available, simply overwrite `include/CADMesh.hh` with the new file as distributed.

