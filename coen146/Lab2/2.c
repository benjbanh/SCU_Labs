#include <stdio.h>

int main(){
    int RTT0 = 3;
    int RTT1 = 20;
    int RTT2 = 26;
    int RTTHTTP = 47;

    /** a. Assuming zero transmission time for the HTML object, how much time elapses from when the
        client clicks on the link until the client receives the object?*/ 
        int total_dns_time = RTT0 + RTT1 + RTT2;
        int total_http_time = total_dns_time + RTTHTTP * 2;
        printf("a) %d ms \n", total_http_time);


    /** b. Suppose the HTML object references six very small things on the same web server. Neglecting
        transmission times, how much time elapses from when the client clicks on the link until the base
        object and all six additional objects are received from the web server at the client, assuming
        non-persistent HTTP and no parallel TCP connections?*/
        int additional_objects_time = 6 * RTTHTTP;
        int total_additional_time = total_http_time + additional_objects_time;
        printf("b) %d ms \n", total_additional_time);

    /** c. Assume that the client is configured to support n parallel TCP connections and compute the
        response time in both persistent and non-persistent cases. */
        int n = 16;
        int total_nonpersistent = total_http_time + ((6/n) * (RTTHTTP *2));
        int total_persistent = total_http_time + (RTTHTTP * 2);
        printf("c) With %d parallel TCP connections: \n", n);
        printf("    Nonpersistent HTTP: %d ms\n", total_nonpersistent);
        printf("       Persistent HTTP: %d ms\n", total_persistent);
        

}