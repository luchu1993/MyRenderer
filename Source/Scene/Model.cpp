//
// Created by luchu on 2022/3/16.
//

#include "../Core/Mesh.h"
#include "Model.h"

void Model::Update()
{

}

void Model::Render(bool shadowPass)
{
    unsigned numFaces = mesh_->GetNumFaces();
    for (unsigned i = 0; i < numFaces; ++i)
    {
        for (unsigned j = 0; j < 3; ++j)
        {
            Vertex const& vertex = mesh_->GetVertices()[i *3 + j];
        }
    }
}

