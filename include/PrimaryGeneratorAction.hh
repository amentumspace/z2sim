#pragma once

// GEANT4 //
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  private:
    G4GeneralParticleSource* particle_gun;

  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);
};

