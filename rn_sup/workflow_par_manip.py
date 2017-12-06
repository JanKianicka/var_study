'''
Auxiliary script to manipulate entries in workflow.par files:
label and action entries in WorkFlow_RN_FULL_reproc.par, WorkFlow_RN_PREL_reproc.par.
It will do the following:
1. collection stations.
2. Then per station retrieves entries.
3. Checks whether BG_ANA_ERR is present.
4. If yes, then add ABGAM_ERR just underneath of BG_ANA_ERR.
5. Put everything together and print it into the output file.

'''
import re

# assume station pattern is between -,- and does not contain "-"
STATION_PATTERN = "class-([a-zA-Z0-9\_]*)-"

if __name__ == "__main__":
    #in_file = 'WorkFlow_RN_FULL_input.txt'
    #out_file = "WorkFlow_RN_FULL_out.txt"
    in_file = "WorkFlow_RN_PREL_input.txt"
    out_file = "WorkFlow_RN_PREL_out.txt"
    
    f_in = open(in_file)
    in_lines = f_in.readlines()
    
    stations_list = []
    stations_ent_dict = {}
    
    # prepare list of stations and sort them
    for in_line in in_lines:
        print in_line
        Matcher = re.search(STATION_PATTERN, in_line)
        station = Matcher.group(1)
        stations_list.append(station)
        print station
    stations_set = set(stations_list)
    stations_list = list(stations_set)
    stations_list.sort()
    print stations_list
    
    for station in stations_list:
        stations_ent_dict[station] = []
    
    # prepare lists of entries per station
    for in_line in in_lines:
        for station in stations_ent_dict.keys():
            if (in_line.find(station) != -1):
                stations_ent_dict[station].append(in_line)
    
    # adding ABGAM entries into proper place
    index = 0
    for station, station_entries in stations_ent_dict.items():
        for line in station_entries:
            index += 1
            if (line.find("BG_ANA_ERR-action") != -1):
                label_in = "class-%s-ABGAM_ERR-label-1=\"Reprocess\"\n"%(station)
                station_entries.insert(index,label_in)
                action_in = "class-%s-ABGAM_ERR-action-1=\"$(process-SID) %s\"\n"%(station, "%s")
                station_entries.insert(index+1,action_in)
        index = 0
    
    f_in.close()
    
    f_o = open(out_file, "w")
    for station in stations_list:
        station_entries = stations_ent_dict[station]
        for line in station_entries:
            f_o.write(line)
    
    f_o.close()

    