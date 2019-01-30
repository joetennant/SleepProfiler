#include "sleepProfiler.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

const double US_IN_SECONDS = 1000000.0;
const int LOOP_WHILE_SECONDS = 2;
const unsigned long SLEEP_WAIT_TIME_US = 10000;

static inline double getTimestampInSecs(struct timeval tv){
    return tv.tv_sec + (tv.tv_usec / US_IN_SECONDS);
}

int timeLessThanSeconds(struct timeval startTime, double seconds) {
    struct timeval endTime;
    gettimeofday(&endTime, NULL);
    double diffTimeInSeconds = (getTimestampInSecs(endTime) - getTimestampInSecs(startTime));
    return (diffTimeInSeconds <= seconds);
}

/*
 Loop for some period of time, sleeping for 10 ms within the loop.
 Count the iterations of the loop to measure the timer variation
 */
unsigned long iterations1 = 0;
unsigned long profileSleep_usleep() {
    iterations1 = 0;
    struct timeval startTime;
    gettimeofday(&startTime, NULL);
    
    while (timeLessThanSeconds(startTime, LOOP_WHILE_SECONDS)) {
        useconds_t sleepTime = SLEEP_WAIT_TIME_US;
        usleep(sleepTime);
        iterations1++;
    }
    return iterations1;
}

/*
 Loop for some period of time, "selecting" with a 10 ms timout within the loop.
 Count the iterations of the loop to measure the timer variation
 */
unsigned long iterations2 = 0;
unsigned long profileSleep_select() {
    iterations2 = 0;
    struct timeval startTime;
    gettimeofday(&startTime, NULL);
    
    while (timeLessThanSeconds(startTime, LOOP_WHILE_SECONDS)) {
        struct timeval sleepTime;
        sleepTime.tv_sec = 0;
        sleepTime.tv_usec = SLEEP_WAIT_TIME_US;
        select(0, NULL, NULL, NULL, &sleepTime);
        iterations2++;
    }
    return iterations2;
}

/*
 Loop for some period of time, "hard-looping" with a 10 ms timout within the loop.
 Count the iterations of the loop to measure the timer variation
 */

static inline double getTimestampInMicroseconds(struct timeval tv){
    return (tv.tv_sec * US_IN_SECONDS) + (tv.tv_usec);
}

int hasTimeIntervalElapsed(struct timeval startTime, double desiredIntervalInMicrosecs) {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    double elapsedIntervalInMicroseconds = (getTimestampInMicroseconds(currentTime) - getTimestampInMicroseconds(startTime));
    return (elapsedIntervalInMicroseconds > desiredIntervalInMicrosecs);
}

const double SLEEP_IN_MICROSECONDS = 100;
const double SLEEP_IN_NANOSECONDS = SLEEP_IN_MICROSECONDS * 1000.0;

void usleepWorkAround(unsigned int sleepIntervalInMicrosecs) {
    
    struct timeval startTime;
    gettimeofday(&startTime, NULL);
    struct timespec subSleepInterval = {0, SLEEP_IN_NANOSECONDS};
    struct timespec subSleepRemaining;
    
    while (!hasTimeIntervalElapsed(startTime, sleepIntervalInMicrosecs)) {
//        usleep(SLEEP_IN_MICROSECONDS);
        nanosleep(&subSleepInterval, &subSleepRemaining);
    }
}

unsigned long iterations3 = 0;
unsigned long profileSleep_hardLoop() {
    iterations3 = 0;
    struct timeval startTime;
    gettimeofday(&startTime, NULL);
    
    while (timeLessThanSeconds(startTime, LOOP_WHILE_SECONDS)) {
        usleepWorkAround(SLEEP_WAIT_TIME_US);
        iterations3++;
    }
    return iterations3;
}

/*
 Loop for some period of time, "hard-looping" with a 10 ms timout within the loop.
 Count the iterations of the loop to measure the timer variation
 */
