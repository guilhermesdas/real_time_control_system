#include "../includes/simulation.h"

#define MAX_MSG_SIZE            200

unsigned inputTimingSampling_ms = 10; /*!< Input timing sampling in ms */
unsigned outputTimingSampling_ms = 50; /*!< Output timing sampling in ms */
char * in_timing_txt = "output/in_timing.txt";
char * out_timing_txt = "output/out_timing.txt";
char * values_txt = "output/values.txt";

void * calculateInputV(void * arg)
{

    // Get args
    double * args = arg;
    double kf = args[0];
    double step = args[1];

    // Simulation: generate input v
    while ( k <= kf )
    {

        // Calculate input and increment k
        sem_wait(&_k_mutex);
        inputVector(k); // Calculate input vector
        k += step;
        sem_post(&_k_mutex);

        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);

        // Sleep
        int s = usleep(_MS_TO_US(inputTimingSampling_ms));

        clock_gettime(CLOCK_REALTIME, &end);
        long int delay = (end.tv_nsec - start.tv_nsec);
        if ( delay < 0 )
        {
            delay = end.tv_nsec + _MAX_TV_NSEC_VALUE - start.tv_nsec;
        }

        char message[MAX_MSG_SIZE];
        memset(message,MAX_MSG_SIZE,'\0');

        sprintf( message, "%d\t%ld\n",
           _MS_TO_NS(inputTimingSampling_ms), delay );
        save_values(message,in_timing_txt);

    }

    // Exit thread
    pthread_exit(EXIT_SUCCESS);

}

void * calculateOutputV(void * arg)
{
    // Get args
    double * args = arg;
    double kf = args[0];
    double step = args[1];

    // Yf sampling and saving
    while ( k <= kf )
    {
        sem_wait(&_k_mutex);
        outputfVector(k); // Calculate output vector
        sem_post(&_k_mutex);

        // Get current input and output to generate file
        Matrix output; output.rows = 3; output.columns = 1;
        outputV_get(&output);
        Matrix input; input.rows = 2; input.columns = 1;
        inputV_get(&input);
 
        // Write k, input and output vector in standart output
        char message[MAX_MSG_SIZE];
        memset(message,MAX_MSG_SIZE,'\0');
        sem_wait(&_k_mutex);
        sprintf(message,"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
                k, input.values[0][0],
                input.values[1][0],
                output.values[0][0],
                output.values[1][0],
                output.values[2][0] ); 
        sem_post(&_k_mutex);
        save_values(message,values_txt);
        
        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);

        // Sleep
        usleep(_MS_TO_US(outputTimingSampling_ms));

        clock_gettime(CLOCK_REALTIME, &end);

        long int delay = (end.tv_nsec - start.tv_nsec);
        if ( delay < 0 )
        {
            delay = end.tv_nsec + _MAX_TV_NSEC_VALUE - start.tv_nsec;
        }

        memset(message,MAX_MSG_SIZE,'\0');
        sprintf( message, "%d\t%ld\n",
           _MS_TO_NS(outputTimingSampling_ms),  delay);
        save_values(message,out_timing_txt);
    }

    pthread_exit(EXIT_SUCCESS);

}

void runSimulation(double k0, double kf, double step)
{
    // Init files
    init_values(in_timing_txt);
    init_values(out_timing_txt);
    init_values(values_txt);

    // Initialize vectors and semaphore
    inputV_init(2,1);
    outputV_init(3,1);
    sem_init(&_k_mutex,0,1);

    // Args
    double args[4];
    k = k0;
    args[0] = kf;
    args[1] = step;
    args[2] = 30;

    // Thread create possible erros
    int error0, error1;

    // Create threads
    error0 = pthread_create(&tinput,NULL,&calculateInputV,args);
    args[2] = 50;
    error1 = pthread_create(&toutput,NULL,&calculateOutputV,args);
    if ( error0 != 0 || error1 != 0 )
    {
        printf("\nError in thread creation: [input: %s] [output: %s]\n",
            strerror(error0),strerror(error1));
    }

    // Wait threads to finish
    pthread_join(toutput,NULL);
    pthread_join(tinput,NULL);

    // Destroy semaphores
    inputV_destroy();
    outputV_destroy();
    sem_destroy(&_k_mutex);

    // exit
    exit(EXIT_SUCCESS);

}