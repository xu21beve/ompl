/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2010, Rice University
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Rice University nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Ioan Sucan */

#ifndef OMPL_EXTENSION_ODE_SIMPLE_SETUP_
#define OMPL_EXTENSION_ODE_SIMPLE_SETUP_

#include "ompl/control/SimpleSetup.h"
#include "ompl/extensions/ode/ODEStateValidityChecker.h"
#include "ompl/extensions/ode/ODEControlManifold.h"

namespace ompl
{

    namespace control
    {

        /** \brief Create the set of classes typically needed to solve a
            control problem when forward propagation is computed with ODE. */
        class ODESimpleSetup : public SimpleSetup
        {
        public:

            /** \brief Constructor needs the control manifold needed for planning. */
            explicit
            ODESimpleSetup(const ControlManifoldPtr &manifold);

            /** \brief The control manifold is assumed to be ODEControlManifold. Constructor only needs the state manifold. */
            explicit
            ODESimpleSetup(const base::StateManifoldPtr &manifold);

            /** \brief The control manifold is assumed to be
                ODEControlManifold. The state manifold is assumed to
                be ODEStateManifold. Constructor only needs the ODE
                environment. */
            explicit
            ODESimpleSetup(const ODEEnvironmentPtr &env);

            virtual ~ODESimpleSetup(void)
            {
            }

            /** \brief Get the ODE environment associated to the state and control manifolds */
            const ODEEnvironmentPtr& getEnvironment(void) const
            {
                return getStateManifold()->as<ODEStateManifold>()->getEnvironment();
            }

            /** \brief Get the current ODE state (read parameters from ODE bodies) */
            base::ScopedState<ODEStateManifold> getCurrentState(void) const;

            /** \brief Set the current ODE state (set parameters for ODE bodies) */
            void setCurrentState(const base::ScopedState<> &state);

            /** \brief Set the current ODE state (set parameters for ODE bodies) */
            void setCurrentState(const base::State *state);

            /** \brief Set the bounds for the planning volume */
            void setVolumeBounds(const base::RealVectorBounds &bounds)
            {
                getStateManifold()->as<ODEStateManifold>()->setVolumeBounds(bounds);
            }

            /** \brief Set the bounds for the linear velocity */
            void setLinearVelocityBounds(const base::RealVectorBounds &bounds)
            {
                getStateManifold()->as<ODEStateManifold>()->setLinearVelocityBounds(bounds);
            }

            /** \brief Set the bounds for the angular velocity */
            void setAngularVelocityBounds(const base::RealVectorBounds &bounds)
            {
                getStateManifold()->as<ODEStateManifold>()->setAngularVelocityBounds(bounds);
            }

            /** \brief Set the ODE world to the states that are
                contained in a given path, sequentially. Using \e
                timeFactor, the speed at which this sequence is
                iterated through is altered. */
            void playPath(const base::PathPtr &path, double timeFactor = 1.0) const;

            /** \brief Call playPath() on the solution path, if one is available */
            void playSolutionPath(double timeFactor = 1.0) const;

            /** \brief Simulate the ODE environment forward for \e steps simulation steps, using the control \e control.
                Construct a path representing this action. */
            base::PathPtr simulateControl(const double* control, unsigned int steps) const;

            /** \brief Simulate the ODE environment forward for \e steps simulation steps, using the control \e control.
                Construct a path representing this action. */
            base::PathPtr simulateControl(const Control* control, unsigned int steps) const;

            /** \brief Simulate the ODE environment forward for \e
                steps simulation steps, using the null control
                (ompl::control::ControlManifold::nullControl()).
                Construct a path representing this action. */
            base::PathPtr simulate(unsigned int steps) const;

            virtual void setup(void);

        private:

            void useEnvParams(void);

        };
    }

}
#endif