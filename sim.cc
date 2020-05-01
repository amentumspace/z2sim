// USER //
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "PhysicsList.hh"

// GEANT4 //
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"


int main(int argc, char** argv)
{
    auto run_manager = new G4RunManager();

    auto detector_construction = new DetectorConstruction();
    run_manager->SetUserInitialization(detector_construction);

    auto physics_list = new PhysicsList();
    run_manager->SetUserInitialization(physics_list);

    auto primary_generator_action = new PrimaryGeneratorAction();
    run_manager->SetUserAction(primary_generator_action);

    run_manager->Initialize();
  
    auto vis_manager = new G4VisExecutive();
    vis_manager->Initialize();

    auto session = G4UImanager::GetUIpointer();

    // Source //
    session->ApplyCommand("/gps/pos/type Volume");
    session->ApplyCommand("/gps/pos/shape Para");
    session->ApplyCommand("/gps/pos/confine world_physical");
    session->ApplyCommand("/gps/ang/type iso");
    session->ApplyCommand("/gps/pos/halfx 2 m");
    session->ApplyCommand("/gps/pos/halfy 2 m");
    session->ApplyCommand("/gps/pos/halfz 2 m");

    // Visualisation //
    session->ApplyCommand("/vis/open OGL 500x500-500-50");
    session->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 70 30");
    session->ApplyCommand("/vis/viewer/set/style surface");
    session->ApplyCommand("/vis/drawVolume");
    session->ApplyCommand("/vis/scene/add/trajectories");
    session->ApplyCommand("/vis/scene/endOfEventAction accumulate");

    // Run //
    auto ui = new G4UIExecutive(argc, argv);
    run_manager->BeamOn(1e6);
    ui->SessionStart();

    delete session;
    delete ui;
}

