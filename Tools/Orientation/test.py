import numpy as np

from ahrs.filters import Madgwick

gyro_data = np.array([[2.1,1.0,1.0],[1.0,2.0,1.0],[1.0,2.0,1.0]])
acc_data = np.array([[1.1,1.2,1.0],[1.0,2.0,1.0],[1.0,2.0,1.0]])
mag_data = np.array([[1.3,1.0,1.0],[1.0,2.0,1.0],[2.0,1.0,3.0]])


gyro_data = np.array([[2.1,1.0,1.0]])
acc_data = np.array([[1.1,1.2,1.0]])
mag_data = np.array([[1.3,1.0,1.0]])

print(gyro_data)
print(gyro_data.shape)

madgwick = Madgwick(gyr=gyro_data, acc=acc_data, mag=mag_data)

print(madgwick.Q)