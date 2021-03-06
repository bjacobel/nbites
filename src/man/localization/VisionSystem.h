/**
 * @brief  Define a class responsible for updating particle swarm based on
 *         visual observations from the vision system
 *
 * @author EJ Googins <egoogins@bowdoin.edu>
 * @date   February 2013
 */

#pragma once

#include "SensorModel.h"
#include "NBMath.h"
#include "LineSystem.h"

#include "BallModel.pb.h"

#include "LocStructs.h"
#include "FieldConstants.h"

#include <vector>
#include <list>
#include <map>

#include <boost/math/distributions.hpp>

namespace man
{
namespace localization
{

static const float MIN_LINE_LENGTH = 100.f;

/**
 * @class Vision System
 * @brief Responsible for updating particles based on Visual Observations
 *        from the vision system.
 */
class VisionSystem// : public SensorModel
{
public:
    VisionSystem();
    ~VisionSystem();

    // updates give particleset by reference, returns true if observations was nonempty
    bool update(ParticleSet& particles,
                const messages::VisionField& obsv);

    // overloaded to use ball observations
    bool update(ParticleSet& particles,
                const messages::VisionField& obsv,
                const messages::FilteredBall& ballObsv);

    float scoreFromVisDetect(const Particle& particle,
                             const messages::VisualDetection& obsv);

    float scoreFromBallObsv(const Particle& particle,
                            const messages::FilteredBall& obsv);

    static Line prepareVisualLine(const messages::RobotLocation& loc,
                                  const messages::VisualLine& visualLine,
                                  bool stdLineLength = false);

    void setUpdated(bool val);
    float getLowestError(){return currentLowestError;};
    float getAvgError(){return avgError;};
    float getWeightedAvgError(){return weightedAvgError;};
    int getLastNumObsv(){return lastNumObsv;};

    float getConfidenceError(const messages::RobotLocation& loc,
                             const messages::VisionField& obsv);

    std::list<ReconstructedLocation> getReconstructedLocations(){return reconstructedLocations;};

    // Random number generator to be used throughout the system
    boost::mt19937 rng;

private:
    // Functions to calculate possible positions observation viewed from
    void addCornerReconstructionsToList(messages::VisualCorner corner);
    void addGoalPostReconstructionsToList(messages::VisualGoalPost leftPost,
                                          messages::VisualGoalPost rightPost);

    void optimizeReconstructions();

private:
    LineSystem* lineSystem;
    std::list<ReconstructedLocation> reconstructedLocations;
    float avgError;
    float weightedAvgError;
    float currentLowestError;

    int lastNumObsv;

    bool sawGoal;
};
} // namespace localization
} // namespace man
