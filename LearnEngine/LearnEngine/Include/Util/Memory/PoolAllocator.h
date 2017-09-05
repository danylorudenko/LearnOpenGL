#ifndef __POOL_ALLOCATOR_H__
#define __POOL_ALLOCATOR_H__

#include <cstddef>
#include <cstdint>
#include <map>

template<typename T>
class ObjectPool
{
public:
    using type = T;
    using align_type = std::uint32_t;
    using aligned_ptr = align_type*;
    using byte = std::uint8_t;
    using pool_map = std::map<std::size_t, bool>
    
    // Each unit is aligned to the std::uint32_t for faster copying.
    static constexpr std::size_t POOL_UNIT_SIZE = alignof(type) + (alignof(type) % sizeof(std::uint32_t));

    ObjectPool                              (std::size_t initial_capacity = 20);

    T*                  Allocate            (std::size_t count = 1);
    void                Release             (T* first_obj_ptr, std::size_t count = 1);


protected:
    T*                  GetObjectPtr        (std::size_t object_ID);

    void                ReinitializePool    (std::size_t new_capacity);
    void                MovePool			(T* current_pool, T* target_pool, size_t count);

    std::size_t         GetFirstFreeID      () const;
    void                UpdateState         (std::size_t unit_ID, bool state);

protected:
    std::size_t         capacity_;
    std::size_t         count_;

    pool_map            state_map_;
    byte*               pool_;
};

#include "..\..\../Inl\PoolAllocator.inl"

#endif