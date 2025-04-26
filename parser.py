import argparse

parser = argparse.ArgumentParser(
                    prog = "Timer",
                    description = "Sets timers")
parser.add_argument("-t","--time",help = "time for which the timer needs to be set")
parser.add_argument("-s","--second",help = "convert time into seconds",action="store_true")
parser.add_argument("-c","--clock",help = "set timer till given time")
parser.add_argument("-l","--log",type = str,help = "log the time for a certain activity")
parser.add_argument("-p","--print",help = "log the time for a certain activity",action = "store_true")

args = parser.parse_args()

print(args.time,args.second,args.clock,args.log,end="\0")
