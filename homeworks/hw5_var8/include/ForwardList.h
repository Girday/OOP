#pragma once

#include <memory_resource>
#include <iterator>
#include <stdexcept>

#include "ListIterator.h"

template <typename T>
class ForwardList {
    public:
        ForwardList(std::pmr::memory_resource* res) : alloc(res) {}

        ~ForwardList() {
            Node<T>* curr = head;
            
            while (curr) {
                Node<T>* tmp = curr->next;
                using Alloc = std::pmr::polymorphic_allocator<Node<T>>;
                std::allocator_traits<Alloc>::destroy(alloc, curr);
                alloc.deallocate(curr, 1);
                curr = tmp;
            }
            
            head = nullptr;
        }

        void push_back(const T& value) {
            Node<T>* new_node = alloc.allocate(1);
            alloc.construct(new_node, Node<T>{value, nullptr});

            if (!head) {
                head = new_node;
                return;
            }

            Node<T>* curr = head;
            while (curr->next)
                curr = curr->next;
            
            curr->next = new_node;
        }

        void push_front(const T& value) {
            Node<T>* new_node = alloc.allocate(1);
            alloc.construct(new_node, Node<T>{value, head});
            head = new_node;
        }

        Node<T>* get_head() const {
            return head;
        }

        ListIterator<T> begin() {
            return ListIterator<T>(head);
        }

        ListIterator<T> end() {
            return ListIterator<T>(nullptr);
        }

    private:
        Node<T>* head = nullptr;
        std::pmr::polymorphic_allocator<Node<T>> alloc;
};
