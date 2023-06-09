# https://www.youtube.com/watch?v=ECKA1Ojp_E0&list=PLejN69rU111NiOAX74MS7-nSAIY3uoXYo&index=12&t=3s
# https://www.flaticon.com/
# https://github.com/TkinterEP/ttkthemes

from tkinter import *
from tkinter import filedialog
import tkinter.messagebox
from tkinter import ttk
from ttkthemes import themed_tk as tk
import os
from mutagen.mp3 import MP3
from pygame import mixer
import time
import threading

root = tk.ThemedTk()

# Fonts: Arial, Courier, Comic Sans MS, Fixedsys
# Fonts: Sans Serif, MS Serif, Symbol, System, Times New Roman (Times), Verdana
# Styles: normal, bold, roman, italic, underline, overstrike
statusbar = ttk.Label(root, text='Welcome to Melody', relief=SUNKEN, anchor=W,
                      font='Times 10 italic')
statusbar.pack(side=BOTTOM, fill=X)

# Create the menubar.
menubar = Menu(root)
root.config(menu=menubar)
root.get_themes()
root.set_theme("radiance")

# playlist - contains full path and filename
# playlistbox - contains just the filename
playlist = []


def browse_file():
    global filename_path
    filename_path = filedialog.askopenfilename()
    print(filename_path)
    add_to_playlist(filename_path)


def add_to_playlist(filename):
    filename = os.path.basename(filename)
    index = 0
    playlistbox.insert(index, filename)
    playlist.insert(index, filename_path)
    index += 1


# Create the submenu.
subMenu = Menu(menubar, tearoff=0)
menubar.add_cascade(label='File', menu=subMenu)
subMenu.add_command(label="Open", command=browse_file)
subMenu.add_command(label="Exit", command=root.destroy)


def about_us():
    tkinter.messagebox.showinfo('About Melody',
                                'This is a music player built using Python and tkinter.')


subMenu = Menu(menubar, tearoff=0)
menubar.add_cascade(label='Help', menu=subMenu)
subMenu.add_command(label="About Us", command=about_us)

mixer.init()  # initializing the mixer

# root.geometry('500x500')
root.title("Melody")
root.iconphoto(True, PhotoImage(file='images/JVClickIcon.png'))

##filelabel = ttk.Label(root, text='Lets make some noise!')
##filelabel.pack(pady=10)

playPhoto = PhotoImage(file='images/play.png')

leftframe = Frame(root)
leftframe.pack(side=LEFT, padx=30, pady=30)

playlistbox = Listbox(leftframe)
playlistbox.pack()

addBtn = ttk.Button(leftframe, text='+ Add', command=browse_file)
addBtn.pack(side=LEFT)


def del_song():
    selected_song = playlistbox.curselection()
    selected_song = int(selected_song[0])
    playlistbox.delete(selected_song)
    playlist.pop(selected_song)
    print(playlist)


delBtn = ttk.Button(leftframe, text='- Del', command=del_song)
delBtn.pack(side=LEFT)

rightframe = Frame(root)
rightframe.pack(pady=30)

topframe = Frame(rightframe)
topframe.pack()

lengthlabel = ttk.Label(topframe, text='Total Length - --:--')
lengthlabel.pack(pady=5)

currenttimelabel = ttk.Label(topframe, text='Current Time - --:--',
                             relief=GROOVE)
currenttimelabel.pack()


def show_details(play_song):
    # global filename_path
    file_data = os.path.splitext(play_song)

    if file_data[1] == '.mp3':
        audio = MP3(play_song)
        total_length = audio.info.length
        print(total_length)
    else:
        a = mixer.Sound(play_song)
        total_length = a.get_length()

    mins, secs = divmod(total_length, 60)
    mins = round(mins)
    secs = round(secs)
    timeformat = '{:02d}:{:02d}'.format(mins, secs)
    lengthlabel['text'] = "Total length - " + timeformat

    tl = threading.Thread(target=start_count, args=(total_length,))
    tl.start()


def start_count(t):
    global paused
    # The get_busy() function returns false when we press the stop button, or music stop playing.
    current_time = 0
    while current_time <= t and mixer.music.get_busy():
        if paused:
            continue
        else:
            mins, secs = divmod(current_time, 60)
            mins = round(mins)
            secs = round(secs)
            timeformat = '{:02d}:{:02d}'.format(mins, secs)
            currenttimelabel['text'] = "Current time - " + timeformat
            time.sleep(1)
            current_time += 1


def play_music():
    global paused
    global filename_path
    if paused:
        mixer.music.unpause()
        statusbar['text'] = "Music Resumed"
        paused = FALSE
    else:
        try:
            stop_music()
            time.sleep(1)
            selected_song = playlistbox.curselection()
            selected_song = int(selected_song[0])
            play_it = playlist[selected_song]
            mixer.music.load(play_it)
            mixer.music.play()
            statusbar['text'] = "Playing music - " + os.path.basename(play_it)
            show_details(play_it)
        except:
            tkinter.messagebox.showerror('File not found',
                                         'Melody could not find the file. Please check again.')


def stop_music():
    mixer.music.stop()
    statusbar['text'] = "Music Stopped"


paused = FALSE


def pause_music():
    global paused
    paused = TRUE
    mixer.music.pause()
    statusbar['text'] = "Music Paused"


def rewind_music():
    play_music()
    statusbar['text'] = "Music Rewound"


def set_vol(val):
    volume = float(val) / 100
    mixer.music.set_volume(volume)


def mute_music():
    pass


muted = FALSE


def mute_music():
    global muted
    if muted:
        # Unmute the music.
        mixer.music.set_volume(0.7)
        volumeBtn.configure(image=volumePhoto)
        scale.set(70)
        muted = FALSE
    else:
        # Mute the music.
        mixer.music.set_volume(0)
        volumeBtn.configure(image=mutePhoto)
        scale.set(0)
        muted = TRUE


middleframe = Frame(rightframe)
middleframe.pack(padx=30, pady=30)

playBtn = ttk.Button(middleframe, image=playPhoto, command=play_music)
playBtn.grid(row=0, column=0, padx=10)

stopPhoto = PhotoImage(file='images/stop.png')
stopBtn = ttk.Button(middleframe, image=stopPhoto, command=stop_music)
stopBtn.grid(row=0, column=1, padx=10)

pausePhoto = PhotoImage(file='images/pause.png')
pauseBtn = ttk.Button(middleframe, image=pausePhoto, command=pause_music)
pauseBtn.grid(row=0, column=2, padx=10)

# Bottom Frame.

bottomframe = Frame(rightframe)
bottomframe.pack()

rewindPhoto = PhotoImage(file='images/rewind.png')
rewindBtn = ttk.Button(bottomframe, image=rewindPhoto, command=rewind_music)
rewindBtn.grid(row=0, column=0)

mutePhoto = PhotoImage(file='images/mute.png')
volumePhoto = PhotoImage(file='images/volume.png')
volumeBtn = ttk.Button(bottomframe, image=volumePhoto, command=mute_music)
volumeBtn.grid(row=0, column=1)

scale = ttk.Scale(bottomframe, from_=0, to=100, orient=HORIZONTAL,
                  command=set_vol)
scale.set(70)
mixer.music.set_volume(0.7)
scale.grid(row=0, column=2, pady=15, padx=30)


def on_closing():
    # tkinter.messagebox.showinfo('Prank', 'This window will not close.')
    stop_music()
    root.destroy()


root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()
