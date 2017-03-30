//
// Created by Chris on 17/3/25.
//

#ifndef STUDENT_MANAGE_SYSTEM_THREADSAFE_STACK_H
#define STUDENT_MANAGE_SYSTEM_THREADSAFE_STACK_H

#include <stack>
//#incldue <thread>
#include <exception>
#include <memory>
#include <mutex>

namespace NaiNa
{
    template <typename T>
    class threadsafe_stack
    {
    // data
    private:
        std::unique_ptr<std::stack<T>> data_ptr_;
        std::mutex m_;

    // function
    public:

        threadsafe_stack() noexcept;

        threadsafe_stack(const threadsafe_stack<T> &);

        threadsafe_stack(threadsafe_stack<T> &&);

        threadsafe_stack<T>& operator=(const threadsafe_stack<T> &);


        bool empty();

        std::shared_ptr<T> pop();

        //T pop();

        void pop(T &);

        void push(const T &);

        void push(T &&);

    };


    class stack_empty : public std::exception
    {
    public:
        const char* what() const noexcept
        {
            return "threadsafe_stack is empty!";
        }
    };


    template <typename T>
    threadsafe_stack<T>::threadsafe_stack() noexcept {
        data_ptr_.reset(new std::stack<T>);
    }

    template <typename T>
    threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack<T>& other) {
        *data_ptr_ = *other.data_ptr_;
    }


    template <typename T>
    threadsafe_stack<T>::threadsafe_stack(threadsafe_stack<T>&& other) {
        data_ptr_ = other.data_ptr_;
    }

    template <typename T>
    threadsafe_stack<T>& threadsafe_stack<T>::operator=(const threadsafe_stack<T> &other) {
        *data_ptr_ = *other.data_ptr_;
    }


    template <typename T>
    bool threadsafe_stack<T>::empty() {
        std::lock_guard<std::mutex> lock(m_);
        return data_ptr_->empty();
    }


    template <typename T>
    std::shared_ptr<T> threadsafe_stack<T>::pop() {
        std::lock_guard<std::mutex> lock(m_);
        if(data_ptr_->empty()) {
            throw stack_empty();
        }

        std::shared_ptr<T>const res(std::make_shared<T>(std::move(data_ptr_->top())));
        data_ptr_->pop();

        return res;
    }

//    template <typename T>
//    T threadsafe_stack<T>::pop() {
//        std::lock_guard<std::mutex> lock(m_);
//        if(data_ptr_->empty()) {
//            throw stack_empty();
//        }
//
//        T res(std::move(data_ptr_->top()));
//        data_ptr_->pop();
//
//        return res;
//    }

    template <typename T>
    void threadsafe_stack<T>::pop(T &other) {
        std::lock_guard<std::mutex> lock(m_);
        if(data_ptr_->empty()) {
            throw stack_empty();
        }

        other = data_ptr_->top();
        data_ptr_->pop();
    }




    template <typename T>
    void threadsafe_stack<T>::push(const T& other) {
        std::lock_guard<std::mutex> lock(m_);
        data_ptr_->push(other);
    }


    template <typename T>
    void threadsafe_stack<T>::push(T&& other) {
        std::lock_guard<std::mutex> lock(m_);
        data_ptr_->push(std::move(other));
    }


}

#endif //STUDENT_MANAGE_SYSTEM_THREADSAFE_STACK_H
