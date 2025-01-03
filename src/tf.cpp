
class Go
{
public:
    template <typename Func>
    Go &operator>>(Func &&func)
    {
#pragma omp parallel
#pragma omp single
        {
#pragma omp task
            func();
        }
        return *this;
    }

    $ wait()
    {
#pragma omp taskwait
    }
};

Go go;
