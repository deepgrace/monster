#ifndef OBJECT_POOL_HPP
#define OBJECT_POOL_HPP

#include <queue>
#include <memory>

namespace monster
{
    template <typename T>
    class object_pool
    {
        public:
            using object = std::shared_ptr<T>;

            object_pool() = default;

            object_pool(const object_pool<T>&) = delete;
            object_pool<T>& operator=(const object_pool<T>&) = delete;

            object_pool(object_pool<T>&&) = delete;
            object_pool<T>& operator=(object_pool<T>&&) = delete;

            object allocate();

            virtual ~object_pool() = default;

        private:
            std::queue<std::unique_ptr<T>> objects;
    };

    template <typename T>
    typename object_pool<T>::object object_pool<T>::allocate()
    {
        if (objects.empty())
            objects.emplace(std::make_unique<T>());

        std::unique_ptr<T> obj(std::move(objects.front()));
        objects.pop();

        object dst(obj.release(), [this](T* t){
               objects.emplace(t);
        });

        return dst;
    }
}

#endif
