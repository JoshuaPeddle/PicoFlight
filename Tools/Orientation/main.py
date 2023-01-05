import serial
import numpy as np
import matplotlib.pyplot as plt
from ahrs.filters import Madgwick

class lsmData:

    def __init__(self) -> None:
        self.accel = np.array([[1.0,1.0,1.0]])
        self.mag = np.array([[1.0,1.0,1.0]])
        self.gyro = np.array([[1.0,1.0,1.0]])
        self.updated = [False, False, False]
        print(self.accel)
        ...
    

parse_errors = 0

lsmdata = lsmData()

plt.ion()
plt.show()

pitch_array = [1]
roll_array = [1]
yaw_array = [1]

def plot_euler(euler):
    # Plot the Euler angles
    pitch_array.append(.8*(euler[1]* 57.2958) + .2*(pitch_array[-1]))
    roll_array.append(.8*(euler[0]* 57.2958)+ .2*(roll_array[-1]))
    yaw_array.append(euler[2]* 57.2958)
    plt.plot(pitch_array, label="Pitch")
    plt.plot(roll_array, label="Roll")
    #plt.plot(yaw_array, label="Yaw")
    plt.legend()
    plt.draw()
    plt.ylim(-100, 100)
    plt.pause(0.0001)
    plt.clf()


def toEuler(Q):
    # Convert the quaternion to Euler angles
    # https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    # https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
    # https://www.x-io.co.uk/res/doc/madgwick_internal_report.pdf
    # https://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
    # https://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
    #
    #print("Q: ",Q)
    w,x,y,z = Q[0]
    
    # roll (x-axis rotation)
    sinr_cosp = 2 * (w * x + y * z)
    cosr_cosp = 1 - 2 * (x * x + y * y)
    roll = np.arctan2(sinr_cosp, cosr_cosp)

    # pitch (y-axis rotation)
    sinp = 2 * (w * y - z * x)
    if np.abs(sinp) >= 1:
        pitch = np.copysign(np.pi / 2, sinp)
    else:
        pitch = np.arcsin(sinp)
    
    # yaw (z-axis rotation)
    siny_cosp = 2 * (w * z + x * y)
    cosy_cosp = 1 - 2 * (y * y + z * z)
    yaw = np.arctan2(siny_cosp, cosy_cosp)

    return np.array([roll, pitch, yaw])


def filterData():
    # Filter the data to compute the orientation
    # 1. Convert the data to a quaternion
    # 2. Convert the quaternion to Euler angles
    
    # implement madgwick filter
    #
    # Here is madgwick filter code

    # Create a Madgwick filter
    madgwick = Madgwick(gyr=lsmdata.gyro, acc=lsmdata.accel, mag=lsmdata.mag)
    #print(madgwick.Q)

    euler = toEuler(madgwick.Q)


    plot_euler(euler)
    # Get the Euler angles
    
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
            if (decoded[0] == "A"):
                x,y,z = [float(x) for x in decoded[1:-1].split("|")]
                lsmdata.accel = np.array([[x,y,z]])
                lsmdata.updated[0] = True
                #print("Accel: ", lsmdata.accel )
            if (decoded[0] == "M"):
                x,y,z = [float(x) for x in decoded[1:-1].split("|")]

                # convert from Gauss to micro Tesla

                lsmdata.mag = np.array([[x/10.0,y/10.0,z/10.0]])
                lsmdata.updated[1] = True

                #print("Mag:" , lsmdata.mag)
            if (decoded[0] == "G"):
                x,y,z = [float(x) for x in decoded[1:-1].split("|")]
                # convert from degrees per second to radians per second
                x * 0.0174533
                y * 0.0174533
                z * 0.0174533
                lsmdata.gyro = np.array([[x,y,z]])
                lsmdata.updated[2] = True
                #print("Gyro: ", lsmdata.gyro)
        except ValueError:
            print("parse error")
            parse_errors+=1
            continue
        #print("-"*20)

        if all(lsmdata.updated):
            # Filter the data
            filterData()
            lsmdata.updated = [False, False, False]

        