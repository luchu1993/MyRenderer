//
// Created by luchu on 2022/3/16.
//

#pragma once

#include <vector>
#include "../Math/Vector.h"


struct Vertex
{
    Vector3 position_;
    Vector2 texcoord_;
    Vector3 normal_;
    Vector4 tangent_;
    Vector4 joint_;
    Vector4 weight_;
};


class Mesh
{
public:
    void Load(const char* filename);

    const std::vector<Vertex>& GetVertices() const { return vertices_; }

    unsigned GetNumFaces() const { return numFaces_; }

    Vector3 Center() const { return center_; }

private:
    unsigned numFaces_;
    std::vector<Vertex> vertices_;
    Vector3 center_;
};
