/*The MIT License (MIT)
 *
 * Copyright (c) 2016, Scanse LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <sweep/util.h>
#include <sweep/sweep.h>

struct scan_data
{
    sweep_response_scan_packet_t packets[2000];
    int count;
};

void *processCompleteScan(void *new_data);

SweepDriver *drv = NULL;
status result;

int main(void)
{

    drv = new SweepDriver();
    int p_stat;
    pthread_t t_attr;
    uint32_t startTs;
    uint32_t waitTime;

    //Create a new struct to store the data for processing
    struct scan_data *new_data;
    new_data = (struct scan_data *) malloc(sizeof(struct scan_data));

    if (!drv)
    {
        fprintf(stderr, "Create Driver fail, exit\n");
        return -2;
    }

    if (drv->connect("/dev/ttyUSB0", 115200, 1000))
    {
        fprintf(stderr, "Error, Serial Couldn't Connect\n");
        std::cout << "Could not connect" << std::endl;
        return -1;
    }

    if (drv->isConnected())
    {
        std::cout << "Connected" << std::endl;
    }
    else
    {
        std::cout << "Not Connected" << std::endl;
    }

    drv->printDeviceInfo();

    //Send command to start outputting scan data
    drv->startScan();

    while (1)
    {
        sweep_response_scan_packet_t packets[2000];
        size_t count = _countof(packets);
        memset(packets, 0, sizeof(packets));

        startTs = gettime_ms();

        result = drv->getCompleteScan(packets, count, 2000); //Returns when when a full scan has been received or times out
        if (result == S_OK)
        {
            //Copy scan data to be processed
            memcpy(new_data->packets, packets, sizeof(packets));
            new_data->count = count;

            waitTime = gettime_ms() - startTs;

            std::cout << "waitTime: " << waitTime << std::endl;

            std::cout << "Point Count: " << count << std::endl;

            //Start a thread to handle(print) the scan data
            p_stat = pthread_create(&t_attr, NULL, &processCompleteScan, new_data);
            if (p_stat)
            {
                std::cout << "Error: failure to create thread" << std::endl;
            }
        }
        else if (result == S_FAIL)
        {
            std::cout << "Failure" << std::endl;
        }
        else if (result == S_TIMEOUT)
        {
            std::cout << "Timeout" << std::endl;
        }
    }
}

void *processCompleteScan(void *new_data)
{
    struct scan_data *data;
    data = (struct scan_data *) new_data;

    std::cout << "********** New Scan **********" << std::endl;
    for (uint32_t i = 0; i < data->count; i++)
    {
        drv->printScanPacket(data->packets[i]);
    }

    pthread_exit(NULL);
}
