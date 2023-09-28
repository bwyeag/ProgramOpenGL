#ifndef COLLISION_HPP_FILE
#define COLLISION_HPP_FILE
#include "type_load.hpp"
#include "EnclosureBox.hpp"

namespace Engine
{
    inline bool IntersectTest(const axis_collision& a,const axis_collision& b)
    {
        return (a.min_pos.x <= b.max_pos.x &&
            a.max_pos.x >= b.min_pos.x &&
            a.min_pos.y <= b.max_pos.y &&
            a.max_pos.y >= b.min_pos.y &&
            a.min_pos.z <= b.max_pos.z &&
            a.max_pos.z >= b.min_pos.z);
    }
    inline bool IntersectTest(const axis_collision& box,const vec3& point)
    {
        return (point.x >= box.min_pos.x &&
            point.x <= box.max_pos.x &&
            point.y >= box.min_pos.y &&
            point.y <= box.max_pos.y &&
            point.z >= box.min_pos.z &&
            point.z <= box.max_pos.z);
    }
    inline bool IntersectTest(const vec3& point,const axis_collision& box)
    {
        return IntersectTest(box,point);
    }
    inline bool IntersectTest(const vec3& point,const shpere_collision& sphere)
    {
        float distance = (point.x - sphere.pos.x) * (point.x - sphere.pos.x) +
            (point.y - sphere.pos.y) * (point.y - sphere.pos.y) +
            (point.z - sphere.pos.z) * (point.z - sphere.pos.z);
        return distance <= (sphere.radius*sphere.radius);
    }
    inline bool IntersectTest(const shpere_collision& sphere,const vec3& point)
    {
        return IntersectTest(point,sphere);
    }
    inline bool IntersectTest(const shpere_collision& sphereA,const shpere_collision& sphereB)
    {
        float distance = (sphereA.pos.x - sphereB.pos.x) * (sphereA.pos.x - sphereB.pos.x) +
        (sphereA.pos.y - sphereB.pos.y) * (sphereA.pos.y - sphereB.pos.y) +
        (sphereA.pos.z - sphereB.pos.z) * (sphereA.pos.z - sphereB.pos.z);
        return distance <= (sphereA.radius + sphereB.radius)*(sphereA.radius + sphereB.radius);
    }

    inline bool IntersectTest(const axis_collision& box,const shpere_collision& sphere)
    {
        float x = max(box.min_pos.x, min(sphere.x, box.max_pos.x));
        float y = max(box.min_pos.y, min(sphere.y, box.max_pos.y));
        float z = max(box.min_pos.z, min(sphere.z, box.max_pos.z));

        float distance = (x - sphere.pos.x) * (x - sphere.pos.x) + (y - sphere.pos.y) * (y - sphere.pos.y) + (z - sphere.pos.z) * (z - sphere.pos.z);

        return distance < sphere.radius*sphere.radius;
    }
    inline bool IntersectTest(const shpere_collision& sphere,const axis_collision& box)
    {
        return IntersectTest(box,sphere);
    }
} // namespace Engine

#endif //!COLLISION_HPP_FILE