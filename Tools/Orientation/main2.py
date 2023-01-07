import serial

import matplotlib.pyplot as plt


class lsmData:

    def __init__(self) -> None:
        self.pitch = 0
        self.roll = 0
        self.updated = [False, False]

parse_errors = 0

lsmdata = lsmData()

plt.ion()
plt.show()

pitch_array = [1.0, 2.0, 3.0]
roll_array = [1.0]


fig = plt.figure()
ax = fig.add_subplot(111)
line1, = ax.plot(pitch_array, label="Pitch")
line2, = ax.plot(roll_array, label="Roll")

plt.ylim(-20, 20)

def plot_euler2(euler):
    # Plot the Euler angles

    pitch_array.append(float(euler[0]))
    roll_array.append(float(euler[1]))

    line1.set_data( range(len(pitch_array)), pitch_array)


    line2.set_data(range(len(roll_array)), roll_array)

    plt.xlim(len(pitch_array)-100, len(pitch_array))
    fig.canvas.draw()
    fig.canvas.flush_events()



with serial.Serial('COM7', 115200, timeout=1) as ser:
    while True:

        line = ser.readline()   # read a '\n' terminated line
        # Decode the line
        try:
            decoded = line.decode("UTF-8").strip()
        except:
            print("parse error")
            parse_errors+=1
            continue

        #print(line.decode("UTF-8")) 
        try:
            if (decoded[0] == "P"):
                pitch = decoded.split(" ")[-1]
                lsmdata.pitch = pitch
                lsmdata.updated[0] = True
                #print("pitch: ", lsmdata.pitch )

            if (decoded[0] == "R"):
                
                roll = decoded.split(" ")[-1]
                lsmdata.roll = roll
                lsmdata.updated[1] = True
                #print("roll: ", lsmdata.roll)
        except ValueError:
            print("parse error")
            parse_errors+=1
            continue
        #print("-"*20)

        if all(lsmdata.updated):
            # Filter the data
            plot_euler2([lsmdata.pitch ,lsmdata.roll])
            lsmdata.updated = [False, False]

        

""" Old plotting function



def plot_euler(euler):
    # Plot the Euler angles
    #pitch_array.append(.8*(euler[0]* 57.2958) + .2*(pitch_array[-1]))
    #roll_array.append(.8*(euler[1]* 57.2958)+ .2*(roll_array[-1]))

    pitch_array.append(float(euler[0]))
    roll_array.append(float(euler[1]))

    plt.plot(pitch_array, label="Pitch")
    #print(euler)
    plt.plot(roll_array, label="Roll")

    plt.legend()
    plt.draw()
    plt.ylim(-100, 100)
    plt.xlim(len(pitch_array)-100, len(pitch_array))
    plt.pause(0.0001)
    plt.clf()
"""