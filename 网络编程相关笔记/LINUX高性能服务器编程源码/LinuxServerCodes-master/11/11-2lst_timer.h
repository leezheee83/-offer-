#ifndef LST_TIMER
#define LST_TIMER

#include <time.h>
#include<stdio.h>
#define BUFFER_SIZE 64
class util_timer;
struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[ BUFFER_SIZE ];
    util_timer* timer;
};

class util_timer
{
public:
    util_timer() : prev( NULL ), next( NULL ){}

public:
   time_t expire; //任务超时时间
   void (*cb_func)( client_data* );//任务回调函数
   //回调函数处理的客户数据，由定时器执行者回递给回调函数。
   client_data* user_data;
   util_timer* prev;//上一个定时器
   util_timer* next;//下一个
};

class sort_timer_lst
{
public:
    sort_timer_lst() : head( NULL ), tail( NULL ) {}
    ~sort_timer_lst()
    {
        //销毁所有定时器
        util_timer* tmp = head;
        while( tmp )
        {
            head = tmp->next;
            delete tmp;
            tmp = head;
        }
    }
    //添加定时器
    void add_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        if( !head )
        {
            head = tail = timer;
            return; 
        }
        //小于排前面
        if( timer->expire < head->expire )
        {
            timer->next = head;
            head->prev = timer;
            head = timer;
            return;
        }
        //重载函数add_timer（timer，head）是私有类。
        add_timer( timer, head );
    }
    //调整定时器
    void adjust_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        util_timer* tmp = timer->next;
        //时间小于0
        if( !tmp || ( timer->expire < tmp->expire ) )
        {
            return;
        }
        if( timer == head )
        {
            head = head->next;
            head->prev = NULL;
            timer->next = NULL;
            add_timer( timer, head );
        }
        else
        {
            //定时器通过重载函数，重排序。
            //往前跳一位
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            add_timer( timer, timer->next );
        }
    }
    void del_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        //只有一个定时器
        if( ( timer == head ) && ( timer == tail ) )
        {
            delete timer;
            head = NULL;
            tail = NULL;
            return;
        }
        //定时器是头部
        if( timer == head )
        {
            head = head->next;
            head->prev = NULL;
            delete timer;
            return;
        }
        //定时器是尾部
        if( timer == tail )
        {
            tail = tail->prev;
            tail->next = NULL;
            delete timer;
            return;
        }
        //其余情况/
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        delete timer;
    }
    //处理定时器/
    void tick()
    {
        if( !head )
        {
            return;
        }
        printf( "timer tick\n" );
        time_t cur = time( NULL );
        util_timer* tmp = head;
        while( tmp )
        {
            if( cur < tmp->expire )
            {
                break;
            }
            tmp->cb_func( tmp->user_data );
            head = tmp->next;
            if( head )
            {
                head->prev = NULL;
            }
            delete tmp;
            tmp = head;
        }
    }

private:
    void add_timer( util_timer* timer, util_timer* lst_head )
    {
        util_timer* prev = lst_head;
        util_timer* tmp = prev->next;
        while( tmp )
        {
            if( timer->expire < tmp->expire )
            {
                prev->next = timer;
                timer->next = tmp;
                tmp->prev = timer;
                timer->prev = prev;
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if( !tmp )
        {
            prev->next = timer;
            timer->prev = prev;
            timer->next = NULL;
            tail = timer;
        }
        
    }

private:
    util_timer* head;
    util_timer* tail;
};

#endif
