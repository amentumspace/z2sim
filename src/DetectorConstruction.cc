// USER //
#include "DetectorConstruction.hh"

// GEANT4 //
#include "G4NistManager.hh"
#include "G4TessellatedSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

#include "Randomize.hh"

// CADMESH //
#include "CADMesh.hh"


DetectorConstruction::DetectorConstruction() 
{
    // The input geometry filepath as an OBJ.
    filename = "./suit.obj";

    // Parts to load { name, material }. Before the _ is the name in blender.
    parts = {

    // BACKPACK //
    { "plss-seal_", "G4_WATER" },
    { "plss-cowling_", "G4_WATER" },
    //{ "plss-patch_", "G4_WATER" },

    // BODY //
    { "suit-body_", "G4_WATER" },
    { "suit-seat_", "G4_WATER" },

    // LEFT LEG //
    { "suit-left-thigh_", "G4_WATER" },
    { "suit-left-leg-seal_", "G4_WATER" },
    { "suit-left-leg_", "G4_WATER" },
    { "suit-left-ankle-seal_", "G4_WATER" },
    { "suit-left-boot_", "G4_WATER" },
    
    // LEFT ARM //
    { "suit-left-elbow_", "G4_WATER" },
    { "suit-left-glove_", "G4_WATER" },
    //{ "suit-left-arm-patch_", "G4_WATER" },
  
    // RIGHT LEG // 
    { "suit-right-thigh_", "G4_WATER" },
    { "suit-right-leg-seal_", "G4_WATER" },
    { "suit-right-leg_", "G4_WATER" },
    { "suit-right-ankle-seal_", "G4_WATER" },
    { "suit-right-boot_", "G4_WATER" },

    // RIGHT ARM // 
    { "suit-rigth-elbow_", "G4_WATER" },
    { "suit-right-glove_", "G4_WATER" },
    //{ "suit-right-arm-patch_", "G4_WATER" },

    // HElMET //
    { "helmet_", "G4_WATER" },
    { "helmet-upper_", "G4_WATER" },
    { "helmet-window_", "G4_WATER" },
    { "helmet-visor_", "G4_WATER" },
    { "helmet-hinge-left_", "G4_WATER" },
    { "helmet-hinge-right_", "G4_WATER" },
    //{ "helmet-lower-seal_", "G4_WATER" },
    //{ "helmet-lights_", "G4_WATER" },

    // CONTROL PANEL ON CHEST //
    { "device_", "G4_WATER" }
    //{ "device-patch_", "G4_WATER" },
    //{ "device-rail-3_", "G4_WATER" },
    //{ "device-rail-4_", "G4_WATER" },
    //{ "device-rail-2_", "G4_WATER" },
    //{ "device-rail-1_", "G4_WATER" },
    //{ "device-toggle-3-upper_", "G4_WATER" },
    //{ "device-toggle-3-base_", "G4_WATER" },
    //{ "device-toggle-4-upper_", "G4_WATER" },
    //{ "device-toggle-4-base_", "G4_WATER" },
    //{ "device-toggle-2-upper_", "G4_WATER" },
    //{ "device-toggle-2-base_", "G4_WATER" },
    //{ "device-toggle-1-upper_", "G4_WATER" },
    //{ "device-toggle-1-base_", "G4_WATER" },

    };
}



G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Materials //
    G4NistManager* nist_manager = G4NistManager::Instance();
    G4Material* air = nist_manager->FindOrBuildMaterial("G4_AIR");

    // World //
    auto world_solid = new G4Box("world_solid", 2*m, 2*m, 2*m);

    auto world_logical = new G4LogicalVolume( world_solid
                                            , air
                                            , "world_logical"
                                            , 0, 0, 0
    );

    world_logical->SetVisAttributes(G4VisAttributes::GetInvisible());
 
    auto world_physical = new G4PVPlacement( 0
                                           , G4ThreeVector()
                                           , world_logical
                                           , "world_physical"
                                           , 0, false, 0
    );

    // Load the OBJ file.
    auto mesh = CADMesh::TessellatedMesh::FromOBJ(filename);
    mesh->SetScale(m);

    // Place the volumes we have listed above.
    for (auto part : parts)
    { 
        auto material = nist_manager->FindOrBuildMaterial(part.second);
        auto solid = mesh->GetSolid(part.first, false);

        auto logical  = new G4LogicalVolume( solid
                                           , material
                                           , "logical"
                                           , 0, 0, 0
        );

        // Random colour.
        logical->SetVisAttributes(G4Colour( G4UniformRand()
                                          , G4UniformRand()
                                          , G4UniformRand()
                                          , 1.0 ));
        
        new G4PVPlacement( 0                           // Rotation.
                         , G4ThreeVector(0, -1.0*m, 0) // Position. 
                         , logical
                         , "physical"
                         , world_logical
                         , false, 0
        );
    }

    return world_physical;
}

