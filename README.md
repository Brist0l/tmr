🕒 tmr — A Feature-Rich Timer CLI Tool for Linux

tmr is a minimalist yet powerful command-line timer tool designed for Linux users who want precise control over time, logs, focus, and productivity.

With focus mode, activity logs, custom countdowns, and distraction control, tmr helps you not just track time — but command it.

⚙️ Features

    ⏱ Set Custom Timers
    Use --time or --clock to set durations or countdown to a specific time.

    ⏳ Pause / Resume with Spacebar
    No need to kill the process — just hit space to toggle pause/resume.

    📓 Activity Logging
    Log time spent on activities using --log and review later with --print.

    🚫 Focus Mode
    Kill distracting apps listed in focus.txt using --focus.

    🛡️ Distraction Prevention
    Automatically kill listed apps during the timer with --notopen.

    🔔 Notifications
    Sends a desktop notification when the timer ends

🚀 Installation

Make sure you're on Linux. Then clone the repo and build using make:
```
git clone https://github.com/Brist0l/tmr.git
cd tmr
make
```
You should now have the Timer binary ready to roll.

🛠 Usage

./Timer [options]
```
🔧 Options

Flag	Description
-t, --time	Time in minutes (or seconds with --second)
-s, --second	Interprets --time as seconds instead of minutes
-c, --clock	Set timer until a specific HH:MM format
-l, --log	Log time spent on a named activity
-p, --print	Print the activity log
-r, --reverse	Reverse the countdown display
-f, --focus	Kills distracting apps listed in focus.txt at start
-n, --notopen	Continuously kills distracting apps while timer runs
-o, --nonotification	Disable end-of-timer notification
-h, --help	Show help message

You can also press spacebar anytime to pause or resume the timer.
```

🧠 Customizing Focus Mode

You can configure which apps get killed during focus mode by editing focus.txt.
Add one process name per line (e.g., discord, firefox, spotify).

🔔 Notifications

Notifications are sent using notify-send. Ensure you have it installed.

📌 Example Commands
```
# Run a 25-minute Pomodoro timer with focus mode
./Timer --time 25 --focus

# Set a timer until 10:30 AM
./Timer --clock 10:30

# Log a 30-minute study session
./Timer --time 30 --log "Studied Stats110"

# Kill distracting apps if opened mid-session
./Timer --time 20 --notopen
```
🧠 Why Use tmr?

Most timers track time. tmr shapes your focus.
You get the hardcore utility of a productivity tool without bloat or GUI clutter — just raw, keyboard-driven flow.

