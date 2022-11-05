#pragma once
#include <memory>

template<typename T>
struct Node {
    T value;
    Node* next;
    Node(T value) : value{value}, next{nullptr} {
        std::cout << "Node ctr" << std::endl;
    }
    ~Node() {
        std::cout << "Node dctr" << std::endl;
    }
};

template<typename T, typename A=std::allocator<T>>
class MyContainer {
    using value_type = T;
    using allocator_type = A;

    using node_alloc_t = typename std::allocator_traits<allocator_type>::template rebind_alloc<Node<T>>;

    Node<T>* root;
    Node<T>* head;
    allocator_type allocator;
    node_alloc_t node_allocator;
public:
    MyContainer(const allocator_type& a = allocator_type()) : allocator{a}, head{nullptr}, root{nullptr} {
        std::cout << "MyContainer ctr" << std::endl;
        auto node_allocator = allocator_type::rebind<Node<T>>::other(allocator);
        std::cout << "OLOLO" << std::endl;
    }
    ~MyContainer() {
        std::cout << "MyContainer dctr" << std::endl;
        auto it = root;
        while (it) {
            auto t = it;
            it = it->next;
            std::allocator_traits<node_alloc_t>::destroy(node_allocator, t);
            node_allocator.deallocate(t, 1);
        }
    }
    void push_back(T value) {
        auto node = node_allocator.allocate(1);
        std::allocator_traits<node_alloc_t>::construct(node_allocator, node, value);
        if (head != nullptr) {
            //node->prev = head;
            head->next = node;
        } else {
            root = node;
        }
        head = node;
    }
    void print_nodes() {
        auto it = root;
        while (it != nullptr) {
            std::cout << it->value << std::endl;
            it = it->next;
        } 
    }
};