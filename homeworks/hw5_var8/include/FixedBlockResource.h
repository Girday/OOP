#pragma once

#include <memory_resource>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

class FixedBlockResource : public std::pmr::memory_resource {
    public:
        FixedBlockResource(size_t size);
        ~FixedBlockResource();
    
    protected:
        void* do_allocate(size_t bytes, size_t alignment) override;
        void do_deallocate(void* ptr, size_t bytes, size_t alignment) override;
        bool do_is_equal(const memory_resource& other) const noexcept override;
    
    private:
        struct BlockInfo {
            void* ptr;
            size_t size;
            bool free;
        };

        char* buffer;
        size_t buffer_size;
        size_t offset;
        std::vector<BlockInfo> blocks;
};
