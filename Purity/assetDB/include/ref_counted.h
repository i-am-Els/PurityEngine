#pragma once

#include <atomic>
#include <iostream>

namespace purity::assetDB {

    // Base class that implements atomic reference counting
    class PURITY_API RefCounted {
    protected:
        mutable std::atomic<int> refCount{ 0 };

        virtual ~RefCounted() = default; // Ensure proper polymorphic destruction

    public:
        void addRef() const {
            refCount.fetch_add(1, std::memory_order_relaxed);
        }
        void release() const {
            if (refCount.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                delete this;
            }
        }
        int getRefCount() const {
            return refCount.load(std::memory_order_relaxed);
        }
    };

    // Templated smart pointer for reference counting
    template<typename T>
    class Ref {
    private:
        T* ptr{ nullptr };

    public:
        Ref() = default;
        explicit Ref(T* object) : ptr(object) {
            if (ptr) {
                ptr->addRef();
            }
        }
        Ref(const Ref& other) : ptr(other.ptr) {
            if (ptr) {
                ptr->addRef();
            }
        }
        Ref(Ref&& other) noexcept : ptr(other.ptr) {
            other.ptr = nullptr;
        }
        ~Ref() {
            if (ptr) {
                ptr->release();
            }
        }
        Ref& operator=(const Ref& other) {
            if (this != &other) {
                if (ptr) { ptr->release(); }
                ptr = other.ptr;
                if (ptr) { ptr->addRef(); }
            }
            return *this;
        }
        Ref& operator=(Ref&& other) noexcept {
            if (this != &other) {
                if (ptr) { ptr->release(); }
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }
        T* operator->() const { return ptr; }
        T& operator*() const { return *ptr; }
        T* get() const { return ptr; }
        explicit operator bool() const { return ptr != nullptr; }
    };
}
