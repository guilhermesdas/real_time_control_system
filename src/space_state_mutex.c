#include "../includes/space_state_mutex.h"

void inputV_init(int rows, int columns)
{
    sem_init(&_inputV_mutex,0,1);
    sem_wait(&_inputV_mutex);
    _inputV_k = (Matrix*) malloc(2000*sizeof(Matrix));
    _inputV_k->rows = rows;
    _inputV_k->columns = columns;
    //strncpy(_inputV_k->name,"Input",10);
    matrix_zero(rows,columns,_inputV_k);
    sem_post(&_inputV_mutex);

}

void outputV_init(int rows, int columns)
{
    sem_init(&_outputV_mutex,0,1);
    sem_wait(&_inputV_mutex);
    _outputV_k = (Matrix*) malloc(2000*sizeof(Matrix));
    _outputV_k->rows = rows;
    _outputV_k->columns = columns;
    //strncpy(_outputV_k->name,"Output",10);
    matrix_zero(rows,columns,_outputV_k);
    sem_post(&_inputV_mutex);
}

void inputV_set(Matrix inputV_k)
{
    sem_wait(&_inputV_mutex);
    *_inputV_k = inputV_k;
    sem_post(&_inputV_mutex);
}

void outputV_set(Matrix outputV_k)
{
    sem_wait(&_outputV_mutex);
    *_outputV_k = outputV_k;
    sem_post(&_outputV_mutex);
}

void inputV_get(Matrix * inputV_k)
{
    sem_wait(&_inputV_mutex);
    *inputV_k = *_inputV_k;
/*     inputV_k->rows = _inputV_k->rows;
    inputV_k->columns = _inputV_k->columns;
    inputV_k->values = _inputV_k->values; */
    sem_post(&_inputV_mutex);
}

void outputV_get(Matrix * outputV_k)
{
    sem_wait(&_outputV_mutex);
    *outputV_k = *_outputV_k;
    sem_post(&_outputV_mutex);
}

void inputV_wait(long ms)
{
    struct timespec ts;
    //clock_gettime(CLOCK_REALTIME, &ts);
    //ts.tv_nsec += _MS_TO_US(ms);
    //usleep(1000000);
    //sem_timedwait(&_inputV_mutex,&ts);
    //while (( sem_timedwait(&_inputV_mutex,&ts) != -1 )) {}
    //sem_post(&_inputV_mutex);
}

void outputV_wait(long ms)
{
    struct timespec ts;
    //clock_gettime(CLOCK_REALTIME, &ts);
    //ts.tv_nsec += _MS_TO_US(ms);
    //sem_timedwait(&_outputV_mutex,&ts);
    //usleep(1000000);
    //while (( sem_timedwait(&_outputV_mutex,&ts) != -1 )) {}
    //sem_post(&_outputV_mutex);
}


void inputV_destroy()
{
    sem_destroy(&_inputV_mutex);
    free(_inputV_k);
}

void outputV_destroy()
{
    sem_destroy(&_outputV_mutex);
    free(_outputV_k);
}