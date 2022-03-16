//
// Created by luchu on 2022/3/16.
//
#include <cassert>
#include <cstring>
#include <cstdio>

#include "Mesh.h"

#define LINE_SIZE 256

static const char* GetFileExtension(const char* filename)
{
    const char *dotPos = strrchr(filename, '.');
    return dotPos == NULL ? "" : dotPos + 1;
}

void Mesh::Load(const char *filename)
{
    const char* extension = GetFileExtension(filename);
    assert(strcmp(extension, "obj") == 0);

    FILE* file = fopen(filename, "rb");
    assert(file != nullptr);

    std::vector<Vector3> positions;
    std::vector<Vector2> texcoords;
    std::vector<Vector3> normals;
    std::vector<Vector4> tangents;
    std::vector<Vector4> joints;
    std::vector<Vector4> weights;

    std::vector<int> positionIndices;
    std::vector<int> texcoordIndices;
    std::vector<int> normalIndices;

    char line[LINE_SIZE];
    while (true)
    {
        int items;
        if (fgets(line, LINE_SIZE, file) == nullptr)
            break;

        // position
        if (strncmp(line, "v ", 2) == 0)
        {
            Vector3 position;
            items = sscanf(line, "v %f %f %f", &position.x_, &position.y_, &position.z_);
            assert(items == 3);

            positions.push_back(position);
        }
        // texcoord
        else if (strncmp(line, "vt ", 3) == 0)
        {
            Vector2 texcoord;
            items = sscanf(line, "vt %f %f", &texcoord.x_, &texcoord.y_);
            assert(items == 2);

            texcoords.push_back(texcoord);
        }
        // normal
        else if (strncmp(line, "vn ", 3) == 0)
        {
            Vector3 normal;
            items = sscanf(line, "vn %f %f %f", &normal.x_, &normal.y_, &normal.z_);
            assert(items == 3);

            normals.push_back(normal);
        }
        // face
        else if (strncmp(line, "f ", 2) == 0)
        {
            int posIndex[3], uvIndex[3], normalIndex[3];
            items = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                           &posIndex[0], &uvIndex[0], &normalIndex[0],
                           &posIndex[1], &uvIndex[1], &normalIndex[1],
                           &posIndex[2], &uvIndex[2], &normalIndex[2]);
            assert(items == 9);
            for (int i = 0; i < 3; i++)
            {
                positionIndices.push_back(posIndex[i] - 1);
                texcoordIndices.push_back(uvIndex[i] - 1);
                normalIndices.push_back(normalIndex[i] - 1);
            }
        }
        // tangent
        else if (strncmp(line, "# ext.tangent ", 14) == 0)
        {
            Vector4 tangent;
            items = sscanf(line, "# ext.tangent %f %f %f %f",
                           &tangent.x_, &tangent.y_, &tangent.z_, &tangent.w_);
            assert(items == 4);

            tangents.push_back(tangent);
        }
        // joint
        else if (strncmp(line, "# ext.joint ", 12) == 0)
        {
            Vector4 joint;
            items = sscanf(line, "# ext.joint %f %f %f %f",
                           &joint.x_, &joint.y_, &joint.z_, &joint.w_);
            assert(items == 4);
            joints.push_back(joint);
        }
        // weight
        else if (strncmp(line, "# ext.weight ", 13) == 0)
        {
            Vector4 weight;
            items = sscanf(line, "# ext.weight %f %f %f %f",
                           &weight.x_, &weight.y_, &weight.z_, &weight.w_);
            assert(items == 4);

            weights.push_back(weight);
        }

        fclose(file);
    }

    unsigned numIndices = positionIndices.size();

    vertices_.clear();
    vertices_.resize(numIndices);

    Vector3 bboxMin = Vector3(+1e6, +1e6, +1e6);
    Vector3 bboxMax = Vector3(-1e6, -1e6, -1e6);

    for (int i = 0; i < numIndices; ++i)
    {
        int positionIndex = positionIndices[i];
        int texcoordIndex = texcoordIndices[i];
        int normalIndx = normalIndices[i];

        vertices_[i].position_ = positions[positionIndex];
        vertices_[i].texcoord_ = texcoords[texcoordIndex];
        vertices_[i].normal_ = normals[normalIndx];

        if (!tangents.empty())
        {
            int tangentIndex = positionIndex;
            assert(tangentIndex > 0 && tangentIndex < tangents.size());
            vertices_[i].tangent_ = tangents[tangentIndex];
        }
        else
        {
            vertices_[i].tangent_ = Vector4(1, 0, 0, 1);
        }

        if (!joints.empty())
        {
            int jointIndex = positionIndex;
            assert(jointIndex > 0 && jointIndex < joints.size());
            vertices_[i].joint_ = joints[jointIndex];
        }
        else
        {
            vertices_[i].joint_ = Vector4::Zero;
        }

        if (!weights.empty())
        {
            int weightIndex = positionIndex;
            assert(weightIndex > 0 && weightIndex < weights.size());
            vertices_[i].weight_ = weights[weightIndex];
        }
        else
        {
            vertices_[i].weight_ = Vector4::Zero;
        }

        bboxMax = Max(bboxMax, vertices_[i].position_);
        bboxMin = Min(bboxMin, vertices_[i].position_);
    }

    numFaces_ = numIndices / 3;
    center_ = (bboxMin + bboxMax) / 2;
}
