//
// Created by jxq on 20-4-7.
//

#include "time_heap.h"

time_heap::time_heap(int cap):capacity(cap),cur_size(0)
{
    //创建数组
    array = new heap_timer*[capacity];
    if(!array)
    {
        fprintf(stderr,"init heap faild");
        return ;
    }
    for(int i=0;i<capacity;i++)
    {
        array[i] = NULL;
    }
}

time_heap::time_heap(heap_timer **init_array, int size, int capacity):capacity(capacity),cur_size(size)
{
    if(capacity < size)
    {
        fprintf(stderr,"init ");
    }
    //创建堆数组
    array = new heap_timer*[capacity];
    if(!array)
    {
        fprintf(stderr,"init heap_timer failed");
        return ;
    }

    for(int i=0;i<capacity;i++)
    {
        array[i] = NULL;
    }
    //初始化堆数组
    if(size != 0)
    {
        for(int i=0;i<size;i++)
            array[i] = init_array[i];

        for(int i=(cur_size-1)/2;i>=0;--i)
        {
            percolate_down(i);
        }
    }
}


time_heap::~time_heap()
{
    for(int i=0;i<cur_size;i++)
    {
        delete array[i];
    }
    delete[] array;
}

int time_heap::add_timer(heap_timer *timer)
{
    if(!timer)
        return -1;

    //如果堆数组不够大，在扩充一倍
    if(cur_size >= capacity)
    {
        resize();
    }

    ////新插入一个元素，当前堆大小加1, hole是新建空穴的位置
    int hole = cur_size++;
    int parent = 0;
    //对从空穴到根节点的路径上的所有节点执行上虑操作
    for(;hole>0;hole=parent)
    {
        parent = (hole-1)/2;

        if(array[parent]->expire <= timer->expire)
        {
            break;
        }
        array[hole] = array[parent];
    }
    array[hole] = timer;
    return 0;
}

void time_heap::del_timer(heap_timer* timer)
{
    if(!timer)
        return ;
    timer->cb_func = NULL;
}

heap_timer* time_heap::top()const
{
    if(empty())
    {
        return NULL;
    }
    return array[0];
}

void time_heap::pop_timer()
{
    if(empty())
    {
        return ;
    }
    if(array[0])
    {
        delete array[0];
        //将原来的堆顶元素替换为堆数组中最后一个元素
        array[0] = array[--cur_size];

        //对新的堆顶元素执行以下操作
        percolate_down(0);
    }

}


void time_heap::tick()
{
    heap_timer *tmp = array[0];
    time_t cur = time(NULL);
    //循环处理定时器
    while(!empty())
    {
        if(!tmp)
        {
            break;
        }
        //如果堆顶定时没有到期，则退出循环
        if(tmp->expire > cur)
        {
            break;
        }
        //否则执行堆顶定时器中的回调函数
        if(array[0]->cb_func)
        {
            array[0]->cb_func(array[0]->user_data);
        }
        //删除堆顶元素，同时生成新的堆顶定时器
        pop_timer();
        tmp = array[0];
    }
}


void time_heap::percolate_down(int hole)
{
    heap_timer *tmp = array[hole];
    int child = 0;
    for(;((hole*2)+1) <= (cur_size-1);hole = child)
    {
        child = hole*2+1;   // 左子树
        if(child < (cur_size-1) && array[child+1]->expire < array[child]->expire)
        {
            ++child;
        }

        if(array[child]->expire < tmp->expire)
        {
            array[hole] = array[child];
        }
        else
        {
            /* code */
            break;
        }

    }
    array[hole] = tmp;
}


void time_heap::resize()
{
    heap_timer **tmp = new heap_timer*[2* capacity];
    for(int i=0;i<(2*capacity);i++)
    {
        tmp[i] = NULL;
    }

    if(!tmp)
    {
        fprintf(stderr,"resize() faild");
        return ;
    }

    capacity = 2*capacity;
    for(int i=0;i<cur_size;++i)
    {
        tmp[i] = array[i];
    }
    delete[] array;
    array = tmp;
}


bool time_heap::empty()const
{
    if (empty())
        return NULL;

    return array[0];
}


