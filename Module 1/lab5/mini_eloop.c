#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>

int main(void)
{
    /* 1. Create a timer file descriptor */
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);

    if (timer_fd == -1)
    {
        perror("timerfd_create");
        return 1;
    }

    /* 2. Configure the timer */
    struct itimerspec timer;

    timer.it_value.tv_sec = 1;
    timer.it_value.tv_nsec = 0;

    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_nsec = 0;

    if (timerfd_settime(timer_fd, 0, &timer, NULL) == -1)
    {
        perror("timerfd_settime");
        close(timer_fd);
        return 1;
    }

    /* 3. Create epoll */
    int epoll_fd = epoll_create1(0);

    if (epoll_fd == -1)
    {
        perror("epoll_create1");
        close(timer_fd);
        return 1;
    }

    /* 4. Tell epoll to watch our timer */
    struct epoll_event event;

    event.events = EPOLLIN;
    event.data.fd = timer_fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &event) == -1)
    {
        perror("epoll_ctl");
        close(timer_fd);
        close(epoll_fd);
        return 1;
    }

    printf("Timer started...\n");

    int count = 0;

    /* 5. Event loop */
    while (count < 10)
    {
        struct epoll_event events[1];

        int number_of_events =
            epoll_wait(epoll_fd, events, 1, -1);

        if (number_of_events == -1)
        {
            perror("epoll_wait");
            break;
        }

        /* 6. Check whether our timer generated the event */
        if (events[0].data.fd == timer_fd)
        {
            uint64_t expirations;

            read(timer_fd, &expirations, sizeof(expirations));

            count += expirations;

            printf("Timer expired: count = %d\n", count);
        }
    }

    printf("Finished 10 timer expirations.\n");

    close(timer_fd);
    close(epoll_fd);

    return 0;
}
