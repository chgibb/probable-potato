#pragma once
#include <vector>

namespace PBP
{
    template<class T>
    class PooledObject
    {
        public:
            bool live;
            T obj;
            PooledObject(T obj) : live(true), obj(obj){}
    };

    template<class Obj,class Container = std::vector<PooledObject<Obj>>>
    class SlabPool
    {
        public:
            Container cache;
            std::vector<int> emptySlots;

            bool add(Obj obj)
            {
                if(this->emptySlots.empty())
                {
                    this->cache.push_back(PBP::PooledObject<Obj>(obj));
                    return true;
                }
                return false;
            }

            template<class CallBack>
            void forEach(CallBack cb)
            {
                bool abort = false;
                auto end = this->cache.end();
                for(auto it = this->cache.begin(); it != end; ++it)
                {
                    if(it->live)
                    {
                        bool res = cb(*it,abort);
                        if(res)
                        {
                            it->live = false;
                        }

                        if(abort)
                            return;
                    }
                }
            }
    };
}