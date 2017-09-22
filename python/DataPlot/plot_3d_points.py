import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

# matlab data extraction
import scipy.io

def show3DPoints(ptTuple, index):
    pts = np.array(ptTuple)
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1, projection='3d')
    surf = ax.scatter(pts[:, 0] * 1.2, pts[:, 1], pts[:, 2], c="cyan", alpha=1.0, edgecolor='b')
    ax.plot3D(pts[:17, 0] * 1.2, pts[:17, 1], pts[:17, 2], color='blue')
    ax.plot3D(pts[17:22, 0] * 1.2, pts[17:22, 1], pts[17:22, 2], color='blue')
    ax.plot3D(pts[22:27, 0] * 1.2, pts[22:27, 1], pts[22:27, 2], color='blue')
    ax.plot3D(pts[27:31, 0] * 1.2, pts[27:31, 1], pts[27:31, 2], color='blue')
    ax.plot3D(pts[31:36, 0] * 1.2, pts[31:36, 1], pts[31:36, 2], color='blue')
    ax.plot3D(pts[36:42, 0] * 1.2, pts[36:42, 1], pts[36:42, 2], color='blue')
    ax.plot3D(pts[42:48, 0] * 1.2, pts[42:48, 1], pts[42:48, 2], color='blue')
    ax.plot3D(pts[48:, 0] * 1.2, pts[48:, 1], pts[48:, 2], color='blue')
    ax.view_init(elev=90., azim=90.)
    ax.set_xlim(ax.get_xlim()[::-1])

    title = "Image " + str(index)
    plt.title(title)
    plt.show(block=True)


if __name__ == "__main__":
    mat = scipy.io.loadmat('../LoadMatlabFiles/test.mat')
    print("Data loaded!")
    data = mat['pt3d_68']

    pts = []
    for i in range(len(data[0])):
        pts.append([data[0, i], data[1, i], data[2, i]])

    show3DPoints(np.array(pts), 0)
    print("Finished!")
