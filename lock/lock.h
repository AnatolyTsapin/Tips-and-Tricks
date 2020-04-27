#ifndef LOCK_LOCK_H_
#define LOCK_LOCK_H_

#include <utility>
#include <mutex>

template<typename T>
class Lock
{
    class Proxy
    {
    public:
        explicit Proxy(T& object) :
            object(object),
            lock(object)
        {}

        T* operator->()
        {
            return &object;
        }

    private:
        T& object;
        std::lock_guard<T> lock;
    };

public:
    template<typename... A>
    explicit Lock(A&&... args) :
        object(std::forward<A>(args)...)
    {}

    Proxy operator->()
    {
        return Proxy(object);
    }

private:
    T object;
};

#endif /* LOCK_LOCK_H_ */
