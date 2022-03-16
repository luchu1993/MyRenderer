//
// Created by luchu on 2022/3/16.
//

#include <cassert>
#include "Cache.h"
#include "../Core/Mesh.h"


const Mesh& Cache::AcquireMesh(const char *filename)
{
    assert(filename != nullptr);

    auto iter = meshPool_.find(filename);
    if (iter != meshPool_.end())
    {
        CachedItem<Mesh>& item = iter->second;
        if (item.refCount_ > 0)
        {
            ++item.refCount_;
        }
        else
        {
            assert(item.refCount_ == 0);
            assert(item.resource_ == nullptr);

            item.resource_ = new Mesh();
            item.resource_->Load(filename);
            item.refCount_ = 1;
        }

        return *item.resource_;
    }

    CachedItem<Mesh> cachedItem;
    cachedItem.resource_ = new Mesh();
    cachedItem.resource_->Load(filename);
    cachedItem.refCount_ = 1;

    meshPool_[filename] = cachedItem;
    return *cachedItem.resource_;
}

void Cache::ReleaseMesh(const Mesh& mesh)
{
    for (auto& item : meshPool_)
    {
        auto& cachedItem = item.second;
        if (cachedItem.resource_ == &mesh)
        {
            assert(cachedItem.refCount_ > 0);
            --cachedItem.refCount_;
            if (cachedItem.refCount_ == 0)
            {
                delete cachedItem.resource_;
                cachedItem.resource_ = nullptr;
            }

            return;
        }
    }

    assert(false);
}