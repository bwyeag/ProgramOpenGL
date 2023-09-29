#ifndef COLLISION_HPP_FILE
#define COLLISION_HPP_FILE
#include "type_load.hpp"
#include "EnclosureBox.hpp"
#include <algorithm>
#include <array>

namespace Engine
{
    enum Octant
    {
        I=0,II=1,III=2,IV=3,V=4,VI=5,VII=6,VIII=7
    };

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
        float x = std::max(box.min_pos.x, std::min(sphere.pos.x, box.max_pos.x));
        float y = std::max(box.min_pos.y, std::min(sphere.pos.y, box.max_pos.y));
        float z = std::max(box.min_pos.z, std::min(sphere.pos.z, box.max_pos.z));

        float distance = (x - sphere.pos.x) * (x - sphere.pos.x) + (y - sphere.pos.y) * (y - sphere.pos.y) + (z - sphere.pos.z) * (z - sphere.pos.z);

        return distance < sphere.radius*sphere.radius;
    }
    inline bool IntersectTest(const shpere_collision& sphere,const axis_collision& box)
    {
        return IntersectTest(box,sphere);
    }
    inline void DivideBox(const axis_collision& from, Octant where, axis_collision& to)
    {
        switch (where)
        {
        case Octant::I:
            to.max_pos = from.max_pos;
            to.min_pos = (from.max_pos + from.min_pos)/2.0f;
            break;
        case Octant::II:
            to.min_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f + from.min_pos.x,
               (from.max_pos.y + from.min_pos.y)/2.0f,
               (from.max_pos.z + from.min_pos.z)/2.0f);
            to.max_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f,
                (from.max_pos.y + from.min_pos.y)/2.0f+from.max_pos.y,
                (from.max_pos.z + from.min_pos.z)/2.0f+from.max_pos.z);
            break;
        case Octant::III:
            to.min_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f+from.min_pos.x,
                (from.max_pos.y + from.min_pos.y)/2.0f+from.min_pos.y,
                (from.max_pos.z + from.min_pos.z)/2.0f);
            to.max_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f,
                (from.max_pos.y + from.min_pos.y)/2.0f,
                (from.max_pos.z + from.min_pos.z)/2.0f+from.max_pos.z);
            break;
        case Octant::IV:
            to.min_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f,
                (from.max_pos.y + from.min_pos.y)/2.0f+from.min_pos.y,
                (from.max_pos.z + from.min_pos.z)/2.0f);
            to.max_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f+from.max_pos.x,
                (from.max_pos.y + from.min_pos.y)/2.0f,
                (from.max_pos.z + from.min_pos.z)/2.0f+from.max_pos.z);
            break;
        case Octant::V:
            to.min_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f,
                (from.max_pos.y + from.min_pos.y)/2.0f,
                (from.max_pos.z + from.min_pos.z)/2.0f+from.min_pos.y);
            to.max_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f+from.max_pos.x,
                (from.max_pos.y + from.min_pos.y)/2.0f+from.max_pos.y,
                (from.max_pos.z + from.min_pos.z)/2.0f);
            break;
        case Octant::VI:
            to.min_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f+from.min_pos.x,
                (from.max_pos.y + from.min_pos.y)/2.0f,
                (from.max_pos.z + from.min_pos.z)/2.0f+from.min_pos.z);
            to.max_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f,
                (from.max_pos.y + from.min_pos.y)/2.0f+from.max_pos.y,
                (from.max_pos.z + from.min_pos.z)/2.0f);
            break;
        case Octant::VII:
            to.min_pos = from.min_pos;
            to.max_pos = (from.max_pos + from.min_pos)/2.0f;
            break;
        case Octant::VIII:
            to.min_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f,
                (from.max_pos.y + from.min_pos.y)/2.0f+from.min_pos.y,
                (from.max_pos.z + from.min_pos.z)/2.0f+from.min_pos.z);
            to.max_pos = vec3((from.max_pos.x + from.min_pos.x)/2.0f+from.max_pos.x,
                (from.max_pos.y + from.min_pos.y)/2.0f,
                (from.max_pos.z + from.min_pos.z)/2.0f);
            break;
        }
    }
    inline void PositionTest(const axis_collision& boxA,const axis_collision& boxB,std::array<bool,8>& result)
    {
        vec3 tmp = (boxA.min_pos+boxA.max_pos)/2.0f;
        vec3 dmin = boxB.min_pos-tmp, dmax = boxB.max_pos-tmp;
        if (dmax.x > 0.0f)
        {
            result[0]=true;result[3]=true;
            result[4]=true;result[7]=true;
        }
        else
        {
            result[1]=true;result[2]=true;
            result[5]=true;result[6]=true;
        }
        
        if (dmax.y > 0.0f)
        {

        }
            
    }
} // namespace Engine

#endif //!COLLISION_HPP_FILE