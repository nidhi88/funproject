#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <cerrno>
#include <stdexcept>

// Functor definitions. These functors binds a function pointer to
// its args

template <typename T, typename O> struct _functor0
{
    _functor0(O o) : o(o) {}
    T operator()() { return o(); }
    O o;
};

template <typename T, typename I0> struct _functor1
{
    _functor1(T(*f)(I0), I0 a0) : f(f), a0(a0) {}
    T operator()() { return f(a0); }
    T(*f)(I0);
    I0 a0;
};

template <typename T, typename I0, typename I1> struct _functor2
{
    _functor2(T(*f)(I0, I1), I0 a0, I1 a1) : f(f), a0(a0), a1(a1) {}
    T operator()() { return f(a0, a1); }
    T(*f)(I0, I1);
    I0 a0;
    I1 a1;
};

template <typename T, typename I0, typename I1, typename I2> struct _functor3
{
    _functor3(T(*f)(I0, I1, I2), I0 a0, I1 a1, I2) : f(f), a0(a0), a1(a1),
    a2(a2){}
    T operator()() { return f(a0, a1, a2); }
    T(*f)(I0, I1, I2);
    I0 a0;
    I1 a1;
    I2 a2;
};

template <typename T, typename I0, typename I1, typename I2,
          typename I3> struct _functor4
{
    _functor4(T(*f)(I0, I1, I2, I3), I0 a0, I1 a1, I2, I3 a3) : 
    f(f), a0(a0), a1(a1), a2(a2), a3(a3) {}
    T operator()() { return f(a0, a1, a2, a3); }
    T(*f)(I0, I1, I2, I3);
    I0 a0;
    I1 a1;
    I2 a2;
    I3 a3;
};

template <typename T, typename I0, typename I1, typename I2,
          typename I3, typename I4> struct _functor5
{
    _functor5(T(*f)(I0, I1, I2, I3, I4), I0 a0, I1 a1, I2, I3 a3, I4 a4) : 
    f(f), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4) {}
    T operator()() { return f(a0, a1, a2, a3, a4); }
    T(*f)(I0, I1, I2, I3, I4);
    I0 a0;
    I1 a1;
    I2 a2;
    I3 a3;
    I4 a4;
};

template <typename T, typename I0, typename I1, typename I2,
          typename I3, typename I4, typename I5> struct _functor6
{
    _functor6(T(*f)(I0, I1, I2, I3, I4, I5), 
        I0 a0, I1 a1, I2, I3 a3, I4 a4, I5 a5) : 
    f(f), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5) {}
    T operator()() { return f(a0, a1, a2, a3, a4, a5); }
    T(*f)(I0, I1, I2, I3, I4, I5);
    I0 a0;
    I1 a1;
    I2 a2;
    I3 a3;
    I4 a4;
    I5 a5;
};

template <typename T, typename I0, typename I1, typename I2,
          typename I3, typename I4, typename I5,
          typename I6> struct _functor7
{
    _functor7(T(*f)(I0, I1, I2, I3, I4, I5, I6), 
        I0 a0, I1 a1, I2, I3 a3, I4 a4, I5 a5, I6 a6) : 
    f(f), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6) {}
    T operator()() { return f(a0, a1, a2, a3, a4, a5, a6); }
    T(*f)(I0, I1, I2, I3, I4, I5, I6);
    I0 a0;
    I1 a1;
    I2 a2;
    I3 a3;
    I4 a4;
    I5 a5;
    I6 a6;
};

template <typename T, typename I0, typename I1, typename I2,
          typename I3, typename I4, typename I5,
          typename I6, typename I7> struct _functor8
{
    _functor8(T(*f)(I0, I1, I2, I3, I4, I5, I6, I7), 
        I0 a0, I1 a1, I2, I3 a3, I4 a4, I5 a5, I6 a6, I7 a7) : 
    f(f), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7) {}
    T operator()() { return f(a0, a1, a2, a3, a4, a5, a6, a7); }
    T(*f)(I0, I1, I2, I3, I4, I5, I6, I7);
    I0 a0;
    I1 a1;
    I2 a2;
    I3 a3;
    I4 a4;
    I5 a5;
    I6 a6;
    I7 a7;
};

// Class functor definitions: this functors binds class instance methods
template <typename T, typename C> struct _class_functor0
{
    _class_functor0(C* c, T(C::*m)()) : c(c), m(m) {}
    T operator()() { return (c->*m)(); }
    T(C::*m)();
    C* c;
};

template <typename T, typename C, typename I0> struct _class_functor1
{
    _class_functor1(C* c, T(C::*m)(I0), I0 a0) : c(c), m(m), a0(a0) {}
    T operator()() { return (c->*m)(a0); }
    T(C::*m)(I0);
    C* c;
    I0 a0;
};



template <typename T> struct _thread
{
    // This struct will hold the return value of the thread called func.
    
    _thread() : counter(0)
    {
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    }

    ~_thread() { pthread_detach(thd); }

    T result;
    pthread_t thd;
    pthread_attr_t attr;
    volatile int counter;

    int join() { return pthread_join(thd, NULL); }
    int start(void*(f)(void*), void* v)
    {
        return pthread_create(&thd, &attr, f, v);
    }
    
    // Atomic function for add and sub
    int inc() { return __sync_fetch_and_add(&counter, 1); }
    int dec() { if (__sync_fetch_and_sub(&counter, 1) == 0) delete this; }

    private:
    _thread(const _thread&);
    _thread& operator=(const _thread&);
};

template <typename S> void* _help_fn(void* v)
{
    // This function has a valid signature to be callen by
    // pthread_create func.
    S* st = (S*)v;
    st->exec();
    delete st;
};

template <typename T> struct Result
{

    Result(_thread<T>* thd) : thd(thd)
    {
        thd->inc();
    }

    Result(const Result<T>& o)
    {
        thd->inc();
        thd = o.thd;
    }

    Result<T>& operator=(const Result& o)
    {
        o.thd->inc();
        thd->dec();
        thd = o.thd;
        return *this;
    }

    T value()
    {
        switch (thd->join())
        {
            case 0:
              break;
            case EINVAL:
              throw std::runtime_error("EINVAL on pthread_join");
              break;
            case EDEADLK:
              throw std::runtime_error("EDEADLK on pthread_join");
              break;
            case ESRCH:
              // Thread already exited 
              break;
        }
        return thd->result;
    }

    ~Result()
    {
        thd->dec();
    }

    _thread<T>* thd;
};



template <typename T, typename I> struct _help_st
{
    _help_st(_thread<T>* t, I f) : thd(t), functor(f)
    {
        thd->inc();
    }

    ~_help_st()
    {
        thd->dec();
    }

    I functor;
    _thread<T>* thd;

    void exec()
    {
        thd->result = functor();
    }
};

class Thread
{

public:

    template <typename T, typename O> static Result<T>
    run(O obj)
    {
        _functor0<T, O> o(obj);
        return Result<T>(_start<T>(o));
    }

    template <typename T> static Result<T>
    run(T(*fun)())
    {
        _functor0<T, T(*)()> f(fun);
        return run<T, _functor0<T, T(*)()> >(f);
    }

    template <typename T, typename I0> static Result<T>
    run(T(*fun)(I0), I0 a0)
    {
        _functor1<T, I0> f(fun, a0);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename I0, typename I1> static Result<T>
    run(T(*fun)(I0, I1), I0 a0, I1 a1)
    {
        _functor2<T, I0, I1> f(fun, a0, a1);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename I0, typename I1,
              typename I2> static Result<T>
    run(T(*fun)(I0, I1, I2), I0 a0, I1 a1, I2 a2)
    {
        _functor3<T, I0, I1, I2> f(fun, a0, a1, a2);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename I0, typename I1,
              typename I2, typename I3> static Result<T>
    run(T(*fun)(I0, I1, I2, I3), I0 a0, I1 a1, I2 a2, I3 a3)
    {
        _functor4<T, I0, I1, I2, I3> f(fun, a0, a1, a2, a3);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename I0, typename I1,
              typename I2, typename I3, typename I4> static Result<T>
    run(T(*fun)(I0, I1, I2, I3, I4), I0 a0, I1 a1, I2 a2, I3 a3, I4 a4)
    {
        _functor5<T, I0, I1, I2, I3, I4> f(fun, a0, a1, a2, a3, a4);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename I0, typename I1,
              typename I2, typename I3, typename I4,
              typename I5> static Result<T>
    run(T(*fun)(I0, I1, I2, I3, I4, I5), I0 a0, I1 a1, I2 a2, I3 a3,
                                         I4 a4, I5 a5)
    {
        _functor6<T, I0, I1, I2, I3, I4, I5> f(fun, a0, a1, a2, a3, a4, a5);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename I0, typename I1,
              typename I2, typename I3, typename I4,
              typename I5, typename I6> static Result<T>
    run(T(*fun)(I0, I1, I2, I3, I4, I5, I6), I0 a0, I1 a1, I2 a2, I3 a3,
                                         I4 a4, I5 a5, I6 a6)
    {
        _functor7<T, I0, I1, I2, I3, I4, I5, I6>
                f(fun, a0, a1, a2, a3, a4, a5, a6);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename I0, typename I1,
              typename I2, typename I3, typename I4,
              typename I5, typename I6, typename I7> static Result<T>
    run(T(*fun)(I0, I1, I2, I3, I4, I5, I6, I7), I0 a0, I1 a1, I2 a2, I3 a3,
                                         I4 a4, I5 a5, I6 a6, I7 a7)
    {
        _functor8<T, I0, I1, I2, I3, I4, I5, I6, I7>
                f(fun, a0, a1, a2, a3, a4, a5, a6, a7);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename F> static _thread<T>*
    _start(const F& functor)
    {
        _thread<T>* mythread = new _thread<T>();
        _help_st<T, F >* h2 = new _help_st<T, F>(mythread, functor);
        mythread->start(_help_fn<_help_st<T, F> >, h2);
        return mythread;
    }


    template <typename T, typename C> static Result<T>
    run(C* c, T(C::*fun)())
    {
        _class_functor0<T, C> f(c, fun);
        return Result<T>(_start<T>(f));
    }

    template <typename T, typename C, typename I0> static Result<T>
    run(C* c, T(C::*fun)(I0), I0 a0)
    {
        _class_functor1<T, C, I0> f(c, fun, a0);
        return Result<T>(_start<T>(f));
    }


};


#endif
