/**
 Tracker.cxx

 \file
 Implementation of class Tracker.

 \author Thomas Burton 
 \date 5/8/12
 \copyright 2012 BNL. All rights reserved.
*/

#include "eicsmear/smear/Tracker.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <list>

#include <TMath.h>

namespace {
   // Functor for testing non-existent intersection points,
   struct NoIntersection {
      bool operator()(const TVector3& v) const {
         return TMath::IsNaN(v.z());
      }
   };
} // namespace

namespace Smear {

   Tracker::Tracker(double magneticField, double nRadiationLengths,
                    double resolution)
   : mMagField(magneticField)
   , mNRadLengths(nRadiationLengths)
   , mSigmaRPhi(resolution) {
   }

   Tracker::~Tracker() {
   }

   double Tracker::MultipleScatteringContribution(
                                       const erhic::VirtualParticle& p) const {
      // Technically should be a factor of particle charge in the numerator
      // but this is effectively always one.
      double val = 0.0136 / 0.3 * p.GetP() * sqrt(mNRadLengths) / L(p) /
             p.Get4Vector().Beta() / mMagField;
             if(TMath::IsNaN(val)) {
             std::cerr << "MS nan!" << std::endl;
             } // if
             return val;
   }

   double Tracker::IntrinsicContribution(
                      const erhic::VirtualParticle& p) const {
      double val = sqrt(720.) / 0.3 * pow(p.GetP(), 2.) * mSigmaRPhi /
             mMagField / pow(LPrime(p), 2.) / sqrt(NPoints(p) + 4.);
             if(TMath::IsNaN(val)) {
             std::cerr << "Intrinsic nan!" << std::endl;
             } // if
             return val;
   }

   double Tracker::Resolution(const erhic::VirtualParticle& p) const {
      // Don't compute resolution for very small path length
      // as L in the denominator causes it to blow up.
      if(not Accepts(p)) {
         return 0.;
      } // if
      return sqrt(pow(MultipleScatteringContribution(p), 2.) +
                  pow(IntrinsicContribution(p), 2.));
   }

   void Tracker::Smear(const erhic::VirtualParticle& pIn,
                       ParticleMCS& pOut) {
      if(Accepts(pIn) and Accept.Is(pIn)) {
         double y = GetVariable(pIn, kP);
         // Randomly generate a smeared value from the resolution
         // and set it in the smeared particle.
         SetVariable(pOut, Distribution.Generate(y, Resolution(pIn)), kP);
         // Ensure E, p are positive definite
         HandleBogusValues(pOut, kP);
         if(pOut.GetP() < 0.) {
            std::cerr << "p " << pOut.GetP() << std::endl;
         } // if
         if(TMath::IsNaN(pOut.GetP())) {
            std::cerr << "p nan" << std::endl;
         } // if
      } //if
   }
} // namespace Smear
