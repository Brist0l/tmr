# Timer

A timer utility for linux. A notification would be sent after the given time has elapsed.

## Installation

You can either choose to compile it or download the executable 

### Compiling it
1)Clone the repo

2)`cd` into it

3)Run `make`

### Downloading the executable

1) Click and download the binary present on the right side of the github page under the heading `Releases`

## Usage

`./timer {time}`

This will start a timer for the given amount of time(note: time is calculated in minutes if no flag is given)

To set the timer for few seconds use the flag `-s`
eg:

`./timer -s {time}`

## Requirements

1) Any linux distro

2) dunst

3) notify-send

