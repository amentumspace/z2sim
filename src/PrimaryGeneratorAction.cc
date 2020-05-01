// USER //
#include "PrimaryGeneratorAction.hh"

// GEANT4 //
#include "G4Geantino.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particle_gun = new G4GeneralParticleSource();
    particle_gun->SetParticleDefinition(G4Geantino::Definition());
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particle_gun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    particle_gun->GeneratePrimaryVertex(event);
}

