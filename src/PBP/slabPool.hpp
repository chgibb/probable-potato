#pragma once
#include <vector>
#include <list>

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
            std::list<int> emptySlots;

            bool add(Obj obj)
            {
                if(this->emptySlots.empty())
                {
                    this->cache.push_back(PBP::PooledObject<Obj>(obj));
                    return true;
                }
                else
                {
                    this->cache[this->emptySlots.back()] = PBP::PooledObject<Obj>(obj);
                    this->emptySlots.pop_back();
                    return true;
                }
                return false;
            }

            template<class CallBack = void(*)(PBP::PooledObject<Obj>&,bool&)>
            void forEach(CallBack&&cb)
            {
                bool abort = false;
                auto end = this->cache.end();
                int slot = 0;
                for(auto it = this->cache.begin(); it != end; ++it)
                {
                    if(it->live == true)
                    {
                        bool res = cb(*it,abort);
                        if(res)
                        {
                            it->live = false;
                            this->emptySlots.push_back(slot);
                        }

                        if(abort)
                            return;
                    }
                    slot++;
                }
            }
    };
}