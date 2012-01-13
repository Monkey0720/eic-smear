#ifndef _ERHIC_Particle_H_
#define _ERHIC_Particle_H_

// erhic_Particle.h
// BuildTree
//
// Created by TB on 8/19/11.
// Copyright 2011 BNL. All rights reserved.

#include <TLorentzVector.h>
#include <TVector3.h>

#include "Pid.h"

namespace erhic {
   
   /**
    Abstract base class for a general particle.
    */
   class VirtualParticle : public TObject {
      
   public:
      
      virtual ~VirtualParticle() { }
      
      /**
       Returns the PDG code identifying the Particle species.
       */
      virtual Pid Id() const = 0;
      
      /**
       Returns the momentum-energy four-vector (px, py, pz, E).
       */
      virtual TLorentzVector PxPyPzE() const = 0;
      
      /**
       Returns the x component of 3-momentum.
       */
      virtual Double_t Px() const = 0;
      
      /**
       Returns the y component of 3-momentum.
       */
      virtual Double_t Py() const = 0;
      
      /**
       Returns the z component of 3-momentum.
       */
      virtual Double_t Pz() const = 0;
      
      /**
       Returns total energy.
       */
      virtual Double_t GetE() const = 0;
      
      /**
       Returns the magnitude of 3-momentum (GeV).
       */
      virtual Double_t P() const = 0;
      
      /**
       Returns invariant mass (GeV/c<sup>2</sup>).
       */
      virtual Double_t M() const = 0;
      
      /**
       Returns momentum transverse to the beam direction.
       */
      virtual Double_t Pt() const = 0;
      
      /**
       Returns the polar angle in the range [0,pi] radians.
       */
      virtual Double_t Theta() const = 0;
      
      /**
       Returns the polar angle in the range [0,2pi] radians.
       */
      virtual Double_t Phi() const = 0;
      
      /**
       Returns the rapidity.
       */
      virtual Double_t Y() const = 0;
      
      /**
       Returns the pseudorapidity.
       */
      virtual Double_t Eta() const = 0;
      
      /**
       Returns the origin point of the Particle (cm).
       (0,0,0) indicates a Particle originating in the collision.
       */
      virtual TVector3 Vertex() const = 0;
      
//      virtual void SetE(Double_t) = 0;
      
//      virtual void SetP(Double_t) = 0;
      
//      virtual void SetPt(Double_t) = 0;
      
//      virtual void SetPz(Double_t) = 0;
      
//      virtual void SetPhi(Double_t) = 0;
      
//      virtual void SetTheta(Double_t) = 0;
      
      ClassDef(VirtualParticle, 1)
   };
   
} // namespace erhic

#endif