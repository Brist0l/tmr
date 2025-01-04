import argparse

parser = argparse.ArgumentParser(
                    prog = "Timer",
                    description = "Sets timers")
parser.add_argument("time",help = "time for which the timer needs to be set")
parser.add_argument("-s","--second",help = "convert time into seconds",action="store_true")

args = parser.parse_args()

print(args.time,args.second,end="\0")
