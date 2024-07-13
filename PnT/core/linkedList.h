//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>


namespace pnt::ds{
    template<class T >
    class Node{
    public:
        T data;
        Node* next;
        explicit Node(T value) : data(value), next(nullptr){ }
    };

//    template<class T >
//    class LinkedList{
//        Node<T>* head;
//
//    public:
//        LinkedList() : head(nullptr){}
//
//        ~LinkedList() { clear(); }
//
//        void add(T n){
//            auto node = new Node(n);
//            if (head == nullptr) head = node;
//            else {
//                auto temp = head;
//                while (temp->next != nullptr) {
//                    temp = temp->next;
//                }
//                temp->next = node;
//            }
//        }
//
//        void remove(T n){
//
//        }
//
//        void clear(){
//            while (head != nullptr){
//                auto temp = head;
//                head = head->next;
//                delete temp;
//            }
//        }
//    };


    template<typename T>
    class LinkedList {
    public:
        LinkedList() : head(nullptr), tail(nullptr), size(0) {}

        ~LinkedList() {
            clear();
        }

        void add(const T& value) {
            auto newNode = std::make_unique<Node<T>>(value);
            Node<T>* newTail = newNode.get();

            if (!head) {
                head = std::move(newNode);
                tail = newTail;
            } else {
                tail->next = newNode.release();
                tail = tail->next;
            }
            ++size;
        }

        void remove(const T& value) {
            if (!head) return;

            if (head->data == value) {
                head = std::unique_ptr<Node<T>>(head->next);
                if (!head) {
                    tail = nullptr;
                }
                --size;
                return;
            }

            Node<T>* prev = head.get();
            while (prev->next && prev->next->data != value) {
                prev = prev->next;
            }

            if (prev->next) {
                std::unique_ptr<Node<T>> nodeToRemove(prev->next);
                prev->next = nodeToRemove->next;
                if (prev->next == nullptr) {
                    tail = prev;
                }
                --size;
            }
        }

        void display() const {
            Node<T>* current = head.get();
            while (current) {
                std::cout << current->data << " -> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }

        void clear() {
            while (head) {
                head = std::unique_ptr<Node<T>>(head->next);
            }
            tail = nullptr;
            size = 0;
        }

        [[nodiscard]] std::size_t getSize() const {
            return size;
        }

    private:
        std::unique_ptr<Node<T>> head;
        Node<T>* tail;
        std::size_t size;
    };

}
