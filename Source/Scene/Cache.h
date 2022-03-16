//
// Created by luchu on 2022/3/16.
//

#pragma once

#include <unordered_map>

class Mesh;
class Texture;
class Skeleton;

template <typename Resource>
struct CachedItem
{
    Resource* resource_ {};
    unsigned refCount_ {};
};

class Cache
{
    typedef std::unordered_map<const char*, CachedItem<Mesh>> MeshPool;
    typedef std::unordered_map<const char*, CachedItem<Texture>> TexturePool;
    typedef std::unordered_map<const char*, CachedItem<Skeleton>> SkeletonPool;

public:
    static Cache& Get() { return instance_; }

    const Mesh& AcquireMesh(const char* filename);

    void ReleaseMesh(const Mesh& mesh);

private:
    MeshPool meshPool_;
    TexturePool texturePool_;
    SkeletonPool skeletonPool_;

    static Cache instance_;
};
