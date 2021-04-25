/************************************************************
 * AUTHOR        : Ellen Yim
 * ASSIGNMENT #5 : Queue Airport Simulation
 * CLASS         : CS8 Data Structures
 * SECTION       : MW 6:30 - 8:35p
 * DUE DATE      : 04/14/2021
*************************************************************/
#include <iostream>
using namespace std;
#include <iomanip>
#include <math.h>
#include "Plane.h"  // plane functions
#include "queue.h"  // my templated queue class

/**************************************************
 * airport_test()
 *
 * tests my templated queue class and my plane
 * functions. Gives a report with the
 * following inputs after each stimulated run.
***************************************************/
void airport_test();


/************************************************************
 *
 * Queue Airport Simulation
 *
 *  ----------------------------------------------------------------
 * This program is for a queue of planes waiting to take off or land.
 * 1 plane using the runway, only 1 takeoff and 1 landing at a time.
 * If a plane runs out of fuel, this simulation will not discover this
 * until the simulated plane is removed from the queue.
 *    - at that point, the fact that the plane crashed is recorded,
 *      the plane is discarded and the next plane is processed.
 *    - A crashed plane is not considered in waiting time.
 * ----------------------------------------------------------------
 *      INPUT:
 *      - amount of time needed for one plane to land,
 *      - amount of time needed for one plane to take off,
 *      - avg amount of time b/w arrival of planes to landing queue
 *      - avg amount of time b/w arrival of planes to takeoff queue
 *      - max amount of time that plane can stay in the landing queue
 *          without running out of fuel and crashing,
 *      - total length of time needed to be simulated
 *
 *      OUTPUT:
 *      - # of planes that took off in simulated time,
 *      - # of planes that landed in the simulated time,
 *      - # of planes crashed because they ran out of fuel
 *       before they could land,
 *      - avg time that a plane spent in takeoff queue,
 *      - avg time that plane spent in landing queue
*************************************************************/

int main()
{
    cout << "***************************************************" << endl;
    cout << "Programmed by : Ellen Yim \n";
    cout << "Student ID    : 10325759 \n";
    cout << "Class         : CS8 MW 6:30 - 8:35p \n";
    cout << "Assignment #5 : Airport Sim \n";
    cout << "***************************************************" << endl;

    char again;
    do
    {
        airport_test();
        cout << "\nAnother report? (y/n) " << endl;
        cin >> again;
    }while (again == 'y' || again == 'Y');

    system("pause");

    return 0;
}


void airport_test()
{
    int time_land;          // IN: time for a plane to land
    int time_takeoff;       // IN: time for a plane to takeoff
    int simulation_time;    // IN: total length of time needed to be stimulated
    int avg_land;           // IN: avg amount of time b/w arrival of planes to landing queue
    int avg_takeoff;        // IN: avg amount of time b/w arrival of planes to takeoff queue
    int max_time;           // IN: max amount of time that plane can stay in the landing queue without
                            //      running out of fuel and crashing

    cout << "Amount of time needed for 1 plane to land: " << endl;
    cin >> time_land;

    cout << "Amount of time needed for 1 plane to takeoff: " << endl;
    cin >> time_takeoff;

    cout << "Average amount of time b/w arrival of planes to landing queue: " << endl;
    cin >> avg_land;

    cout << "Avg amount of time b/w arrival of planes to takeoff queue: " << endl;
    cin >> avg_takeoff;

    cout << "max amount of time that plane can stay in landing queue without "
            "running out of fuel and crashing: " << endl;
    cin >> max_time;

    cout << "Total length of time to be stimulated: " << endl;
    cin >> simulation_time;

    int totalTimeInLandingQueue;
    totalTimeInLandingQueue = 0;
    int totalTimeInTakeoffQueue;
    totalTimeInTakeoffQueue = 0;

    int numPlanesLanded = 0;    // OUT: # of planes tookoff overall
    int numPlanesTookoff = 0;   // OUT: # of planes landed overall
    int numPlanesCrashed = 0;   // OUT: # of planes crashed overall

    int avgTimeInTakeoffQ = 0;  // OUT: avg time plane spent in takeoff queue
    int avgTimeInLandQ = 0;     // OUT: avg time plane spent in landing queue

    queue<int> landingQueue;
    queue<int> takeoffQueue;

    for (int i=0; i < simulation_time; i++)
    {
        cout << "Top of loop t=" << i << "\n";
        // 1. queue up planes that arrive in this minute.
        if (plane_coming_to_runway(avg_land)) {
            cout << "Plane arrives in landing queue. " << endl;
            landingQueue.enqueue(i);
        }
        if (plane_coming_to_runway(avg_takeoff)) {
            cout << "Plane arrives in takeoff queue. " << endl;
            takeoffQueue.enqueue(i);
        }
        // 2. if runway is occupied, they go to next minute
        // 3. process crashed planes
        while (true)
        {
            while (!landingQueue.isEmpty() && plane_crashed(landingQueue.Rear(), i, max_time)) {
                int next_plane = landingQueue.Front();
                landingQueue.dequeue();
                numPlanesCrashed++;
                cout << "Landing plane that arrives at: " << next_plane
                     << " has crashed. \n";
            }
            // 4. if a plane is in landing queue then land it and set
            if (!landingQueue.isEmpty()) {
                int next_plane = landingQueue.Front();
                landingQueue.dequeue();
                numPlanesLanded++;
                cout << "Landed plane that arrived at: " << next_plane << ". \n";
                totalTimeInLandingQueue += (i - next_plane);

                int j;
                for (j=i; j<time_land + i && j < simulation_time; ++j) {
                    if (plane_coming_to_runway(avg_land)) {
                        cout << j << ": plane arrives on landing queue. \n";
                        landingQueue.enqueue(i);
                    }
                    if (plane_coming_to_runway(avg_takeoff)) {
                        cout << j << ": plane arrives on takeoff queue. \n";
                        takeoffQueue.enqueue(i);
                    }
                }
                i = j;
                if (i >= simulation_time) {
                    break;
                }
            }
            else {
                break;
            }
        }
        // 5. else if a plane is in takeoff queue then launch it and update
        if (!takeoffQueue.isEmpty()) {
            int next_plane = takeoffQueue.Front();
            cout << "Departing plane that arrived at " << next_plane << "\n";
            takeoffQueue.dequeue();
            numPlanesTookoff++;
            totalTimeInTakeoffQueue += (i - next_plane);

            int j;
            for (j=i; j < time_takeoff + i && j < simulation_time; ++j)
            {
                if (plane_coming_to_runway(avg_land)) {
                    cout << j << ": plane arrives on landing queue. \n";
                    landingQueue.enqueue(j);
                }
                if (plane_coming_to_runway(avg_takeoff)) {
                    cout << j << ": plane arrives on takeoff queue. \n";
                    takeoffQueue.enqueue(j);
                }
            }
            i = j;
        }

    }
    // 6. process plane that crash after simulation ends

    cout << "End of simulation time... " << endl;
    while (!landingQueue.isEmpty() && plane_crashed(landingQueue.Rear(), simulation_time, max_time)) {
        int next = landingQueue.Front();
        cout << "Landing plane that arrives at: " << next << " has crashed. \n";
        landingQueue.dequeue();
        numPlanesCrashed++;
    }
    cout << "The number of planes that took off in the simulated time is: "
         << numPlanesTookoff << endl;

    cout << "The number of planes that landed in the simulated time is: "
         << numPlanesLanded << endl;

    cout << "The number of planes that crashed b/c they ran out of fuel before they could land: "
         << numPlanesCrashed << endl;

    avgTimeInTakeoffQ = totalTimeInTakeoffQueue / (double)numPlanesTookoff;
    cout << "The average time that a plane spent in the takeoff queue is: "
         << avgTimeInTakeoffQ << endl;

    avgTimeInLandQ = totalTimeInLandingQueue / (double)numPlanesLanded;
    cout << "The average time that a plane spent in the landing queue is: "
         << avgTimeInLandQ << endl;

}


