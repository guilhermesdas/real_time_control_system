#include "../includes/space_state_mutex.h"

void inputV_init(int rows, int columns)
{
    pthread_mutex_lock(&_inputV_mutex);
    _inputV_k = (Matrix*) malloc(2000*sizeof(Matrix));
    _inputV_k->rows = rows;
    _inputV_k->columns = columns;
    matrix_zero(rows,columns,_inputV_k);
    pthread_mutex_unlock(&_inputV_mutex);

}

void outputV_init(int rows, int columns)
{
     pthread_mutex_lock(&_inputV_mutex);
    _outputV_k = (Matrix*) malloc(2000*sizeof(Matrix));
    _outputV_k->rows = rows;
    _outputV_k->columns = columns;
    matrix_zero(rows,columns,_outputV_k);
    pthread_mutex_unlock(&_inputV_mutex);
}

void inputV_set(Matrix inputV_k)
{
    pthread_mutex_lock(&_inputV_mutex);
    *_inputV_k = inputV_k;
    pthread_mutex_unlock(&_inputV_mutex);
}

void outputV_set(Matrix outputV_k)
{
    pthread_mutex_lock(&_outputV_mutex);
    *_outputV_k = outputV_k;
    pthread_mutex_unlock(&_outputV_mutex);
}

void inputV_get(Matrix * inputV_k)
{
    pthread_mutex_lock(&_inputV_mutex);
    *inputV_k = *_inputV_k;
/*     inputV_k->rows = _inputV_k->rows;
    inputV_k->columns = _inputV_k->columns;
    inputV_k->values = _inputV_k->values; */
    pthread_mutex_unlock(&_inputV_mutex);
}

void outputV_get(Matrix * outputV_k)
{
    pthread_mutex_lock(&_outputV_mutex);
    *outputV_k = *_outputV_k;
    pthread_mutex_unlock(&_outputV_mutex);
}

void inputV_wait(long ms)
{
/*     struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_nsec += _MS_TO_US(ms);
    usleep(1000000);
    sem_timedwait(&_inputV_mutex,&ts);
    while (( sem_timedwait(&_inputV_mutex,&ts) != -1 )) {}
    sem_post(&_inputV_mutex); */
}

void outputV_wait(long ms)
{
/*     struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long int start = ts.tv_sec;
    ts.tv_sec += 5;
    //pthread_mutex_lock(&_outputV_mutex);
    int result;
    while( result = pthread_mutex_timedlock(&_outputV_mutex,&ts) == 0 ) {};
    pthread_mutex_timedlock(&_outputV_mutex,&ts);
    pthread_mutex_unlock(&_outputV_mutex);
    clock_gettime(CLOCK_REALTIME, &ts);
    long int delay = ts.tv_sec - start;
    printf("result %d, real delay %ld\n",result, delay); */

}


void inputV_destroy()
{
    pthread_mutex_destroy(&_inputV_mutex);
    free(_inputV_k);
}

void outputV_destroy()
{
    pthread_mutex_destroy(&_outputV_mutex);
    free(_outputV_k);
}