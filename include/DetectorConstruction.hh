#pragma once

// GEANT4 //
#include "G4VUserDetectorConstruction.hh"

// STL //
#include <map>


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
  
    G4VPhysicalVolume* Construct();

  protected:
    std::string filename;
    std::map<std::string, std::string> parts;
};

