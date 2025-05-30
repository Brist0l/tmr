import argparse

parser = argparse.ArgumentParser(
                    prog = "Timer",
                    description = "Sets timers")
parser.add_argument("-t","--time",help = "time for which the timer needs to be set")
parser.add_argument("-s","--second",help = "convert time into seconds",action="store_true")
parser.add_argument("-c","--clock",help = "set timer till given time")
parser.add_argument("-l","--log",type = str,help = "log the time for a certain activity")
parser.add_argument("-p","--print",help = "show the log",action = "store_true")
parser.add_argument("-r","--reverse",help = "reverse the countdown",action = "store_true")
parser.add_argument("-f","--focus",help = "switches on focus mode which kills the distracting apps",action="store_true")
parser.add_argument("-n","--notopen",help = "kills the distracting apps while the timer is running",action="store_true")
parser.add_argument("-o","--nonotification",help = "doesn't send notifications after the time has elapsed",action="store_true")

args = parser.parse_args()

print(args.time,args.second,args.clock,args.log,args.print,args.reverse,args.focus,args.notopen,args.nonotification,end="\0")
