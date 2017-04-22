#!/usr/bin/env python

# Visualize the scatter of photon transmission/absorption/reflection events
# in different planes. The input file and user selection determines the
# representation that is produced by the script.

import numpy as np
import matplotlib.pyplot as plt
import sys
import os
import time

# define input file name and data type (transmission, absorption, or reflection)
filename = sys.argv[1]
datatype = sys.argv[2]

if datatype == 'trans':
    plot_label = "Transmission"
elif datatype == 'abs':
    plot_label = "Absorption"
elif datatype == 'refl':
    plot_label = "Reflection"
else:
    print("Invalid data type. Valid data types are \"trans\", \"abs\", and \"refl\"")
    sys.exit()

# request input for plot label & modify for output file name
label = raw_input("Plot label: ")
file_label = label.replace(" ", "_")

# if the directory the plot will be sent to does not exist, create it
script_dir = os.path.dirname(__file__)
output_dir = os.path.join(script_dir, 'output/{0}'.format(file_label))

if not os.path.isdir(output_dir):
    os.makedirs(output_dir)

# read data from file
data = np.genfromtxt(filename, dtype = None, usecols = (0, 1, 2))
x = data[:,][:,0]
y = data[:,][:,1]
z = data[:,][:,2]

# determine plane of interest
plane = raw_input("Select plane of interest:\n\n\txy\tyz\txz\n\n\t")

if plane == 'xy':
    ax_a = x
    ax_b = y
    ax_a_lab = 'x'
    ax_b_lab = 'y'
elif plane == 'yz':
    ax_a = y
    ax_b = z
    ax_a_lab_lab = 'y'
    ax_b_lab = 'z'
elif plane == 'xz':
    ax_a = x
    ax_b = z
    ax_a_lab = 'x'
    ax_b_lab = 'z'
else:
    print("Invalid input. Defaulting to xy.")
    ax_a_lab = 'x'
    ax_b_lab = 'y'

heatmap, xedges, yedges = np.histogram2d(x, y, bins = 25)
extent = [xedges[0], xedges[-1], yedges[0], yedges[-1]]
extent = [-5, 5, -5, 5]

print(xedges[0])
print(xedges[-1])
print(yedges[0])
print(yedges[-1])

#plt.clf()
#plt.imshow(heatmap.T, extent = extent, origin = [0,0])


from matplotlib import cm

gridsize = 80
plt.hexbin(x, y, gridsize=gridsize, cmap=cm.jet, bins=None)
plt.axis([-20, 20, -20, 20])

cb = plt.colorbar()
cb.set_label('Number of Photons Transmitted')

# plot data
# plt.figure(1)
# plt.scatter(ax_a, ax_b)
plt.title("MCSTIL Photon Transmission Results\n{0}".format(label))
plt.xlabel('{0} [cm]'.format(ax_a_lab))
plt.ylabel('{0} [cm]'.format(ax_b_lab))
plt.savefig('{0}/{1}.png'.format(output_dir, file_label))
plt.show()
