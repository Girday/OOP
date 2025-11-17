#include "FixedBlockResource.h"

FixedBlockResource::FixedBlockResource(size_t size) : buffer_size(size), offset(0) {
    buffer = static_cast<char*>(std::malloc(size));
    
    if (!buffer)
        throw std::bad_alloc();
    /*
        В конструкторе не нужно выделять память под каждый блок заранее. 
        Все блоки будут создаваться по мере allocate.
    */
}

FixedBlockResource::~FixedBlockResource() {
    if (buffer)
        std::free(buffer);
    /*
        blocks — это std::vector<BlockInfo>. 
        Его не нужно вручную очищать: при разрушении объекта 
        vector уничтожается автоматически.

        В деструкторе ты не должен пытаться освобождать 
        отдельные блоки через do_deallocate — это всё уже 
        «подчищается» через delete[] buffer.
    */
}

void* FixedBlockResource::do_allocate(size_t bytes, size_t alignment) {
    for (auto& block : blocks)
        if (block.free && block.size >= bytes) {
            block.free = false;
            return block.ptr;
        }
    
    size_t remainder = offset % alignment;
    if (remainder != 0)
        offset += (alignment - remainder);
    
    if (offset + bytes > buffer_size)
        throw std::bad_alloc();
    
    void* ptr = buffer + offset;
    blocks.push_back({ptr, bytes, false});
    offset += bytes;
    
    return ptr;
}

void FixedBlockResource::do_deallocate(void* ptr, size_t bytes, size_t alignment) {
    auto it = std::find_if(blocks.begin(), blocks.end(), [ptr](const BlockInfo& block) {
        return block.ptr == ptr;
    });
    
    if (it == blocks.end())
        throw std::logic_error("An attempt to release an unallocated block.");
    
    it->free = true;
}

bool FixedBlockResource::do_is_equal(const memory_resource& other) const noexcept {
    return this == &other;
}
