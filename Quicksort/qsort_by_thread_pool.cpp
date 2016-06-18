// Author : Zheng Luo
// Modified by Zheng Luo on 03/26/14.

#include "thread_pool.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <thread>
#include <future>
#include <chrono>

template<typename T>
struct sorter
{
    thread_pool pool;

    std::list<T> do_sort(std::list<T>& chunk_data)
    {
        if(chunk_data.empty())
        {
            return chunk_data;
        }

        std::list<T> result;
        result.splice(result.begin(),chunk_data,chunk_data.begin());
        T const& partition_val=*result.begin();

        typename std::list<T>::iterator divide_point=
            std::partition(chunk_data.begin(),chunk_data.end(),
                [&](T const& val){return val<partition_val;});

        std::list<T> new_lower_chunk;
        new_lower_chunk.splice(new_lower_chunk.end(),
                               chunk_data,chunk_data.begin(),
                               divide_point);

        std::future<std::list<T> > new_lower=
            pool.submit(std::bind(&sorter::do_sort,this,
                                  std::move(new_lower_chunk)));

        std::list<T> new_higher(do_sort(chunk_data));

        result.splice(result.end(),new_higher);
        
        //while(!new_lower.wait_for(std::chrono::seconds(0)))
        {
            pool.run_pending_task();
        }

        result.splice(result.begin(),new_lower.get());
        return result;
    }
};


template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
        return input;
    }
    sorter<T> s;

    return s.do_sort(input);
}

int main ()
{
    std::list<int> mylist1, mylist2;
    std::list<int>::iterator it;

    // set some initial values:
    for (int i=1; i<=15; ++i)
        mylist1.push_back(i);

    for (int i=1; i<=8; ++i)
        mylist2.push_back(i*10);

    it = mylist1.begin();
    ++it;

    mylist1.splice (it, mylist2);

    for (it=mylist1.begin(); it!=mylist1.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    mylist2=parallel_quick_sort(mylist1);

    for (it=mylist2.begin(); it!=mylist2.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

  return 0;
}


