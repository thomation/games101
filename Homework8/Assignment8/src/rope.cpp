#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.
//        Comment-in this part when you implement the constructor
        if(num_nodes < 2)
        {
            std::cerr << "nodes < 2" << std::endl;
            return;
        }
        auto step = (end - start) / (num_nodes - 1);
        for(int i = 0; i < num_nodes; i ++)
        {
            auto mass = new Mass(start + step * i, node_mass, false);
            std::cout << mass->velocity << std::endl;
            std::cout << mass->position << std::endl;
            masses.push_back(mass);
        }
        for (auto &i : pinned_nodes) {
            masses[i]->pinned = true;
        }
        for(int i = 0; i < num_nodes - 1; i ++)
        {
            springs.push_back(new Spring(masses[i], masses[i + 1], k));
        }
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            auto d = s->m2->position - s->m1->position;
            auto f21 = -s->k * d.unit() * (d.norm() - s->rest_length);
            s->m1->forces -= f21;
            s->m2->forces += f21;
        }

        const double kd = 0.005;
        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position
                m->forces += gravity * m->mass;
                m->forces += -kd * m->velocity;
                Vector2D a = m->forces / m->mass;
                // for explict
                // m->position += m->velocity * delta_t;
                // m->velocity += a * delta_t;
                // for semi-implict
                m->velocity += a * delta_t;
                m->position += m->velocity * delta_t;
                // TODO (Part 2): Add global damping
            }

            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet （solving constraints)
            auto d = s->m2->position - s->m1->position;
            auto f21 = -s->k * d.unit() * (d.norm() - s->rest_length);
            s->m1->forces -= f21;
            s->m2->forces += f21;
        }
        const double damping_factor = 0.00005;
        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                m->forces += gravity * m->mass;
                Vector2D a = m->forces / m->mass;
                Vector2D temp_position = m->position;
                // TODO (Part 3.1): Set the new position of the rope mass
                m->position = m->position + (1 - damping_factor) * (m->position - m->last_position) + a * delta_t * delta_t;
                m->last_position = temp_position;
                // TODO (Part 4): Add global Verlet damping
            }
            m->forces = Vector2D(0, 0);
        }
    }
}
