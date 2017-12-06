#!/usr/bin/python

'''
This simple script will parse 
detail time logs retrieved by grepping from the original log files which 
were very big (1-2GB per day).
Script is also applicable to whole syslog files - only the processing takes longer. 

Format:
2017-01-08T00:00:27+00:00 dlv016/172.27.48.48 [user.debug] ctbt.acquisition.CopySegData[233]: ## Interval, time 1483833627.9466, before upd_req 0.0003 , before q_req 0.0671, before reqloop 0.0184, before commit 6.0771, before sleep 0.0006, after sleep 60.0006, total 66.1641
2017-01-08T00:00:28+00:00 dlv016/172.27.48.48 [user.debug] ctbt.acquisition.CopySegData[233]: ### Request loop, time 1483833628.1888, before wfdisk loop 0.0043, after wfdisk loop 0.0000, before req update -inf, until end inf, total 0.0137
2017-01-08T00:00:28+00:00 dlv016/172.27.48.48 [user.debug] ctbt.acquisition.CopySegData[233]: ### Request loop, time 1483833628.1974, before wfdisk loop 0.0041, after wfdisk loop 0.0000, before req update -inf, until end inf, total 0.0080
...
2017-01-08T00:00:28+00:00 dlv016/172.27.48.48 [user.debug] ctbt.acquisition.CopySegData[233]: #### Wdfdisc loop, time 1483833628.5899, bef q_large 0.0022, bef q_small 0.0051, after q_small 0.0086, after q_time inf, total 0.0199
2017-01-08T00:00:28+00:00 dlv016/172.27.48.48 [user.debug] ctbt.acquisition.CopySegData[233]: #### Wdfdisc loop, time 1483833628.6095, bef q_large 0.0008, bef q_small 0.0080, after q_small 0.0057, after q_time inf, total 0.0193
2017-01-08T00:00:28+00:00 dlv016/172.27.48.48 [user.debug] ctbt.acquisition.CopySegData[233]: #### Wdfdisc loop, time 1483833628.6268, bef q_large 0.0008, bef q_small 0.0080, after q_small 0.0044, after q_time inf, total 0.0170

Synopsis:
- create array of all processing intervals in the day - record total time, before q_req, before commit
- for each interval count number of requests
- evaluate average total time for whole day
- evaluate average total time for interval with number of requests > threshold 
- evaluate also difference between before q_req, before commit - which is the significant measure for us
- be capable to open and processing big log files
- evaluate also average time of request verification and render max/min

Author: Jan Kianicka - 26.1.2017
'''

from optparse import OptionParser
import numpy
import datetime
import re
import matplotlib.pyplot as plt

INTERVAL_PATTERN = "## Interval,( time[0-9. ]*),( before upd_req[0-9. ]*),( before q_req[0-9. ]*),( before reqloop[0-9. ]*),( before commit[0-9. ]*),( before sleep[0-9. ]*),( after sleep[0-9. ]*),( total[0-9. ]*)"
REQUEST_PATTERN  = "### Request loop,([a-zA-Z0-9.\-, ]*),( total[0-9. ]*)"

if __name__ == "__main__":
    print("Script to evaluate figures of performance on CopySegData log file.")
    
    parser = OptionParser()
    parser.add_option("--syslog-file",  dest="syslog_file", help="Specify full path to CopySegData sysylog file containing detail time logging")
    
    (options, dummy) = parser.parse_args()
    
    if options.syslog_file == None:
        print("CopySegData sysylog file not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
        
    print "Log file:",options.syslog_file
    start = datetime.datetime.now()
    
    l_total_time = []
    l_before_reqloop = []
    l_before_commit = []
    
    l_request_counter = []
    l_request_time = []
    
    request_counter = 0
    
    with open( options.syslog_file, 'r') as f:
        for line_number, line in enumerate(f, start=1):
            matcher = re.search(INTERVAL_PATTERN, line)
            if matcher:
                # time
                curr_time_tuple = matcher.group(1).strip().split(" ")
                #print curr_time_tuple
                t_curr_time = float(curr_time_tuple[1])
                #print t_curr_time
                
                # before upd_req
                before_upd_req_tuple = matcher.group(2).strip().split(" ")
                #print before_upd_req_tuple
                t_before_upd_req = float(before_upd_req_tuple[2])
                #print t_before_upd_req
                
                # before q_req
                before_q_req_tuple = matcher.group(3).strip().split(" ")
                #print before_q_req_tuple
                t_before_q_req = float(before_upd_req_tuple[2])
                #print t_before_q_req
                
                # before reqloop
                before_reqloop_tuple = matcher.group(4).strip().split(" ")
                #print before_reqloop_tuple
                t_before_reqloop = float(before_reqloop_tuple[2])
                #print t_before_reqloop
                
                # before commit
                before_commit_tuple = matcher.group(5).strip().split(" ")
                #print before_commit_tuple
                t_before_commit = float(before_commit_tuple[2])
                #print t_before_commit
                
                # before sleep
                before_sleep_tuple = matcher.group(6).strip().split(" ")
                #print before_sleep_tuple
                t_before_sleep = float(before_sleep_tuple[2])
                #print t_before_sleep
                
                # after sleep
                after_sleep_tuple = matcher.group(7).strip().split(" ")
                #print after_sleep_tuple
                t_after_sleep = float(after_sleep_tuple[2])
                #print t_after_sleep
                
                # total
                total_tuple = matcher.group(8).strip().split(" ")
                #print total_tuple
                t_total = float(total_tuple[1])
                #print t_total
                
                l_total_time.append(t_total)
                l_before_reqloop.append(t_before_reqloop)
                l_before_commit.append(t_before_commit)
                
                # Add filled request_counter
                l_request_counter.append(request_counter)
                request_counter = 0
                
            matcher_request = re.search(REQUEST_PATTERN, line)
            if (matcher_request):
                request_counter += 1
                
                # total request time
                total_tuple_req = matcher_request.group(2).strip().split(" ")
                t_total_req = float(total_tuple_req[1])
                
                l_request_time.append(t_total_req)
                
          
        # for line in f
    # with open file - closing the file here
    
    n_total_time = numpy.array(l_total_time)
    n_before_reqloop = numpy.array(l_before_reqloop)
    n_before_commit = numpy.array(l_before_commit)
     
    n_request_loop_duration = n_before_commit - n_before_reqloop
    
    n_request_time = numpy.array(l_request_time)
    
    
    print '{0:45}   {1:1d}'.format("Number if intervals:", n_total_time.shape[0])
    print '{0:45}   {1:1s}'.format("average time[sec]:", "%.3f"%n_total_time.mean())
    print '{0:45}   {1:1s}'.format("average request loop duration time[sec]:","%.3f"%n_request_loop_duration.mean())
    n_request_counter = numpy.array(l_request_counter)
    n_request_counter = numpy.roll(n_request_counter,-1) # just to put 0-th element to the beginning, the last is lost
    
    # Evaluation of intervals which have more than 1000 requests
    wh = numpy.where(n_request_counter > 500)
    # Try yet exactly 500 - 600 intervals
    req_loop_aver_500 = n_request_loop_duration[wh].mean()
    print '{0:45}   {1:1s}'.format("average request loop duration > 500[sec]:", "%.3f"%req_loop_aver_500)
    
    
    print '{0:45}   {1:1d}'.format("Number of all requests:", n_request_time.shape[0])
    print '{0:45}   {1:1s}'.format("Average of request processing[sec]:", "%.3f"%n_request_time.mean())
    
    end = datetime.datetime.now()
    print ("Duration of logfile processing: %s"%(end-start))
    
    # Display number of requests in diagram
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(n_request_counter)
    ax.set_title('CopySegData syslog parsing - Number of requests per processing interval')
    ax.set_xlabel('Intervals')
    ax.set_ylabel('Number of verified requests per interval')
    ax.grid(which='both', axis='both')
    plt.show()

    # Display detail request times
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(n_request_time)
    ax.set_title('Request times for all requests in the day')
    ax.set_xlabel('Requests')
    ax.set_ylabel('Duration of request verification')
    ax.grid(which='both', axis='both')
    plt.show()

