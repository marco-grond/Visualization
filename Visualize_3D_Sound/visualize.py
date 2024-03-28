from wavfile import read
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import numpy as np
import math
import triangle as tr
from matplotlib.colors import LightSource
import matplotlib.cm as cmx
import matplotlib
from mayavi import mlab
from scipy.interpolate import interp1d
import time

def intersect_plane(origin, vector, plane_point, plane_normal):
    '''
    Returns the point at which a plane and a vector intersect
    '''
    vector = norm_vector(vector)
    plane_normal = norm_vector(plane_normal)
    origin = np.array(origin)*1.0
    plane_point = np.array(plane_point)*1.0

    # Test if the vector and the plane are parallel
    denominator = np.dot(vector, plane_normal)
    if denominator < 1e-20:
        return None

    # Compute the distance between the original point and the plane point
    dist = np.dot(plane_point - origin, plane_normal)/denominator

    # Compute the intersection point between the vector and the plane and check if it would intersect the volume
    point = origin + (vector * dist)
    return point

def plot_wavfiles(file_list):
    for f_name in file_list:
        input_data = read(f_name)
        #print type(input_data), input_data[0], input_data[1].shape, input_data[2]
        plt.plot(input_data[1][:1024])
    plt.show()

def plot_one_file(filename):
    input_data = read(filename)
    data = input_data[1]
    fdata = np.fft.fftshift(np.fft.fft(data))
    fps = 1000
    secs = len(input_data[1])/input_data[0]
    #data = np.real(np.fft.ifft(fdata))
    data = np.real(np.fft.ifft(np.fft.ifftshift(fdata[len(fdata)/2-fps*secs/2:len(fdata)/2+fps*secs/2])))
    a = np.min(input_data[1])
    b = np.max(input_data[1])
    print a, b
    data = (b - a)*(data - np.min(data))/(np.max(data) - np.min(data)) - abs(a)
    spacing = np.arange(0, len(input_data[1]), 1.0*input_data[0]/fps).tolist()
    #data = []
    #for s in spacing:
    #    data.append(input_data[1][int(s)])
    print len(spacing), len(data)
    print np.min(data), np.max(data)
    plt.plot(input_data[1])
    plt.plot(spacing, data)
    plt.show()

def get_mic_locations(f_name='mic_locations.txt'):
    '''
    Compute the x, y and z coordinates of each microphone
    '''
    # Read elevation and azimuth from file
    mic_theta = [0]*32
    mic_phi = [0]*32
    ind = 0
    with open(f_name, 'r') as f:
        for l in f:
            line = l.split()
            mic_theta[ind] = float(line[1])/180.0 * math.pi
            mic_phi[ind] = float(line[2])/180.0 * math.pi
            ind += 1

    # Compute cartesian coordinates from elevation and azimuth
    x_coords = [0]*32
    y_coords = [0]*32
    z_coords = [0]*32
    for i in xrange(32):
        x_coords[i] = math.cos(mic_phi[i]) * math.sin(mic_theta[i])
        y_coords[i] = math.sin(mic_phi[i]) * math.sin(mic_theta[i])
        z_coords[i] = math.cos(mic_theta[i])

    return x_coords, y_coords, z_coords

def get_triangles(x_coords, y_coords, z_coords, vals):
    # Compute the connected microphones
    con_num = []
    for i in xrange(32):

        # Compute the distances between different microphones
        con_dist = []
        con_num.append([])
        for j in xrange(32):
            l = tr.geodesic_distance([x_coords[i], y_coords[i], z_coords[i]], [x_coords[j], y_coords[j], z_coords[j]])
            con_num[i].append(j)
            con_dist.append(l)
        con_dist, con_num[i] = sort_lengths(con_dist, con_num[i])

        # Find the microphones which are connected to the i'th one
        if con_dist[6] > 1:
            con_num[i] = con_num[i][1:6]
        else:
            con_num[i] = con_num[i][1:7]

    # Compute the triangles formed by the connected microphones
    triangle_list = []
    for i, c in enumerate(con_num):
        for j in xrange(len(c)):
            for k in xrange(j+1, len(c)):
                p1 = [x_coords[i], y_coords[i], z_coords[i]]
                p2 = [x_coords[c[j]], y_coords[c[j]], z_coords[c[j]]]
                p3 = [x_coords[c[k]], y_coords[c[k]], z_coords[c[k]]]
                v1 = vals[i]
                v2 = vals[c[j]]
                v3 = vals[c[k]]
                if (tr.geodesic_distance(p1, p2) < 1) and (tr.geodesic_distance(p1, p3) < 1) and (tr.geodesic_distance(p2, p3) < 1):
                    new_tr = tr.triangle(p1, p2, p3, v1, v2, v3)
                    if not new_tr in triangle_list:
                        triangle_list.append(new_tr)

    return triangle_list
    

def show_mic_locations(f_name='mic_locations.txt', interp=1, show_mic=0):
    x_coords, y_coords, z_coords = get_mic_locations(f_name)
    triangle_list = get_triangles(x_coords, y_coords, z_coords, [1]*len(x_coords))
    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    # Map microphones onto sphere
    x = []
    y = []
    z = []
    for i in xrange(len(x_coords)):
        x.append(x_coords[i]*r)
        y.append(y_coords[i]*r)
        z.append(z_coords[i]*r)

    #poly3d = []
    #all_points = []
    #for t in triangle_list:
    #    poly3d.append([np.array([t.p1[0], t.p1[1], t.p1[2]]), np.array([t.p2[0], t.p2[1], t.p2[2]]), np.array([t.p3[0], t.p3[1], t.p3[2]])])
    #    all_points += tr.split_triangle(t, 0, interp)
    #print poly3d
    #print len(all_points)
    #x = []
    #y = []
    #z = []
    #new_points = []
    #for a in all_points:
    #    n = tr.map_to_circle(a)
    #    if not n in new_points:
    #        new_points.append(n)

    #for a in new_points:
    #    x.append(a[0])
    #    y.append(a[1])
    #    z.append(a[2])

    # Plot the data
    print len(x_coords)
    print len(y_coords)
    print len(z_coords)
    mlab.clf()
    mlab.mesh(xx, yy, zz, color=(0.4,0.4,0.4))
    mlab.points3d(x[:show_mic], y[:show_mic], z[:show_mic], color=(0, 0, 0), scale_factor=0.5)
    mlab.points3d(x[show_mic+1:], y[show_mic+1:], z[show_mic+1:], color=(0, 0, 0), scale_factor=0.5)
    mlab.points3d(x[show_mic], y[show_mic], z[show_mic], color=(1, 0, 0), scale_factor=0.5)
    mlab.view(45, 60, 25)
    mlab.orientation_axes()
    mlab.savefig('vis_mics/mics_view_1.png')
    mlab.view(135, 60, 25)
    mlab.orientation_axes()
    mlab.savefig('vis_mics/mics_view_2.png')
    mlab.view(225, 60, 25)
    mlab.orientation_axes()
    mlab.savefig('vis_mics/mics_view_3.png')
    mlab.view(315, 60, 25)
    mlab.orientation_axes()
    mlab.savefig('vis_mics/mics_view_4.png')
    mlab.close()


    #fig = plt.figure()
    #ax = fig.add_subplot(111, projection='3d')
    #ax.add_collection3d(Poly3DCollection(np.array(poly3d), linewidths=1, edgecolors='black'))
    #ax.scatter(x, y, z, color='red', marker='.')
    #for t in triangle_list:
    #    x = [t.p1[0], t.p2[0], t.p3[0], t.p1[0]]
    #    y = [t.p1[1], t.p2[1], t.p3[1], t.p1[1]]
    #    z = [t.p1[2], t.p2[2], t.p3[2], t.p1[2]]
        #ax.plot(x, y, z, color='black')
    #ax.set_xlim(-1, 1)
    #ax.set_ylim(-1, 1)
    #ax.set_zlim(-1, 1)
    
    #ax.scatter(x_coords, y_coords, z_coords)
    #ax.plot_trisurf(x_coords, y_coords, z_coords)
    #plt.show()

    

def compute_arclength(p1, p2):
    '''
    Compute the arclength between two 3D-cartesian points, p1 and p2
    '''

    return np.arccos(np.dot(p1, p2))

def sort_lengths(lens, nums):
    s = [x for _, x in sorted(zip(lens, nums))]
    return sorted(lens), s

def downsample_wav(files, fps, interp_rate):

    # Sample the data at the specified fps
    total = []
    for f in files:
        input_data = read(f)
        data = input_data[1]
        new_data = [np.abs(data[0])]
        dmax = max(np.abs(data[0]), np.abs(data[-1]))
        dmin = min(np.abs(data[0]), np.abs(data[-1]))
        slice_size = input_data[0]/fps
        for i in xrange(len(data)/input_data[0]):
            second = np.abs(data[i*input_data[0]:(i+1)*input_data[0]])
            for j in xrange(fps):
                new_data.append(np.mean(second[j*slice_size:(j+1)*slice_size]))
        dmax = max(np.max(new_data), dmax)
        dmin = min(np.min(new_data), dmin)
        new_data.append(np.abs(data[-1]))
        total.append(new_data)

    # Compute the locations and values for interplating data
    locs = np.arange(interp_rate/2, (len(data)/input_data[0])*interp_rate*fps, interp_rate).tolist()
    locs = [0] + locs + [(len(data)/input_data[0])*interp_rate*fps]
    for i, t in enumerate(total):
        total[i] = (np.array(t) - dmin)/(dmax - dmin)
    #print len(locs), len(total[0])
    #print locs
    #print total[0]

    # Interpolate the data
    interp_vals = []
    n_max = None
    n_min = None
    for i, t in enumerate(total):
        f = interp1d(locs, t, kind='cubic')
        interp_vals.append([])
        for j in xrange((len(data)/input_data[0])*interp_rate*fps):
            #print j
            interp_vals[i].append(f(j))
            if n_max == None:
                n_max = np.max(interp_vals[i][-1])
                n_min = np.min(interp_vals[i])
            n_max = max(np.max(interp_vals[i]), n_max)
            n_min = min(np.min(interp_vals[i]), n_min)
    if (n_max > 1) or (n_min < 0):
        for i, t in enumerate(interp_vals):
            interp_vals[i] = (np.array(t) - n_min)/(n_max - n_min)

    # Plot the data
    for i in xrange(0,len(interp_vals[0])):
        for j in xrange(len(interp_vals)):
            plt.plot(interp_vals[j][0:i+1])
        plt.axis([0, len(interp_vals[0])-1, 0, 1])
        plt.savefig('vis_sound/sound_' + str(i) + '.png')
        plt.close()

    #for j in xrange(len(total)):
    #    plt.plot(total[j])
    #plt.axis([0, len(total[0])-1, 0, 1])
    #plt.show()
    #plt.close()

    #for j in xrange(len(interp_vals)):
    #    plt.plot(interp_vals[j])
    #plt.axis([0, len(interp_vals[0])-1, 0, 1])
    #plt.show()
    #plt.close()

    #exit()
    return interp_vals

def interpolate_density(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)

        # Compute the interpolated values at each point
        all_points = []
        point_vals = []
        for t in triangle_list:
            hold = tr.density_plot1(t, 0, interp, 20, 1)
            all_points += hold
            for h in hold:
                point_vals.append(t.lin_interp(h))

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for a in all_points:
            n = tr.map_to_circle(a, radius=r)
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing density:", i
        mlab.clf()
        mlab.mesh(xx, yy, zz, color=(0.4,0.4,0.4))
        mlab.points3d(x, y, z, point_vals, colormap='coolwarm', vmin=0, vmax=1, scale_mode='none', scale_factor=0.1)
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density/view_1/density_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density/view_2/density_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density/view_3/density_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density/view_4/density_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])
    
def interpolate_sphere(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)

        # Compute the interpolated values at each point
        all_points = []
        triangles = []
        point_vals = []
        for t in triangle_list:
            hold = tr.split_triangles(t, 0, interp)
            #all_points += hold
            for h in hold:
                if not (h.p1 in all_points):
                    all_points.append(h.p1)
                    point_vals.append(h.v1)
                if not (h.p2 in all_points):
                    all_points.append(h.p2)
                    point_vals.append(h.v2)
                if not (h.p3 in all_points):
                    all_points.append(h.p3)
                    point_vals.append(h.v3)
                triangles.append([all_points.index(h.p1), all_points.index(h.p2), all_points.index(h.p3)])

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for a in all_points:
            n = tr.map_to_circle(a, radius=r)
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing sphere:", i
        # Set up the data to be visualized
        mlab.clf()
        mlab.triangular_mesh(x, y, z, triangles, scalars=point_vals, colormap='coolwarm', vmin=0, vmax=1)

        # Visualize the data from 4 different angles
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere/view_1/sphere_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere/view_2/sphere_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere/view_3/sphere_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere/view_4/sphere_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])

def interpolate_height(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)

        # Compute the interpolated values at each point
        all_points = []
        triangles = []
        point_vals = []
        for t in triangle_list:
            hold = tr.split_triangles(t, 0, interp)
            #all_points += hold
            for h in hold:
                if not (h.p1 in all_points):
                    all_points.append(h.p1)
                    point_vals.append(h.v1)
                if not (h.p2 in all_points):
                    all_points.append(h.p2)
                    point_vals.append(h.v2)
                if not (h.p3 in all_points):
                    all_points.append(h.p3)
                    point_vals.append(h.v3)
                triangles.append([all_points.index(h.p1), all_points.index(h.p2), all_points.index(h.p3)])

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for j, a in enumerate(all_points):
            n = tr.map_to_circle(a, radius=r+(point_vals[j]**2))
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing height:", i

        # Set up the data to be visualized
        mlab.clf()
        mlab.triangular_mesh(x, y, z, triangles, scalars=point_vals, colormap='coolwarm', vmin=0, vmax=1)

        # Visualize the data from 4 different angles
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height/view_1/height_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height/view_2/height_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height/view_3/height_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height/view_4/height_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])

def interpolate_sphere2(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()
    locs = []
    for i in xrange(len(x_coords)):
        locs.append([x_coords[i], y_coords[i], z_coords[i]])

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)

        # Compute the interpolated values at each point
        all_points = []
        triangles = []
        point_vals = []
        for t in triangle_list:
            hold = tr.split_triangles(t, 0, interp)
            for h in hold:
                if not (h.p1 in all_points):
                    all_points.append(h.p1)
                    point_vals.append(tr.mod_shephard_interp(h.p1, locs, vals))
                if not (h.p2 in all_points):
                    all_points.append(h.p2)
                    point_vals.append(tr.mod_shephard_interp(h.p2, locs, vals))
                if not (h.p3 in all_points):
                    all_points.append(h.p3)
                    point_vals.append(tr.mod_shephard_interp(h.p3, locs, vals))
                triangles.append([all_points.index(h.p1), all_points.index(h.p2), all_points.index(h.p3)])

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for a in all_points:
            n = tr.map_to_circle(a, radius=r)
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing sphere2:", i

        # Set up the data to be visualized
        mlab.clf()
        mlab.triangular_mesh(x, y, z, triangles, scalars=point_vals, colormap='coolwarm', vmin=0, vmax=1)

        # Visualize the data from 4 different angles
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere2/view_1/sphere2_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere2/view_2/sphere2_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere2/view_3/sphere2_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere2/view_4/sphere2_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])

def interpolate_height2(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()
    locs = []
    for i in xrange(len(x_coords)):
        locs.append([x_coords[i], y_coords[i], z_coords[i]])

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)

        # Compute the interpolated values at each point
        all_points = []
        triangles = []
        point_vals = []
        for t in triangle_list:
            hold = tr.split_triangles(t, 0, interp)
            #all_points += hold
            for h in hold:
                if not (h.p1 in all_points):
                    all_points.append(h.p1)
                    point_vals.append(tr.mod_shephard_interp(h.p1, locs, vals))
                if not (h.p2 in all_points):
                    all_points.append(h.p2)
                    point_vals.append(tr.mod_shephard_interp(h.p2, locs, vals))
                if not (h.p3 in all_points):
                    all_points.append(h.p3)
                    point_vals.append(tr.mod_shephard_interp(h.p3, locs, vals))
                triangles.append([all_points.index(h.p1), all_points.index(h.p2), all_points.index(h.p3)])

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for j, a in enumerate(all_points):
            n = tr.map_to_circle(a, radius=r+(point_vals[j]**2))
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing height2:", i

        # Set up the data to be visualized
        mlab.clf()
        mlab.triangular_mesh(x, y, z, triangles, scalars=point_vals, colormap='coolwarm', vmin=0, vmax=1)

        # Visualize the data from 4 different angles
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height2/view_1/height2_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height2/view_2/height2_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height2/view_3/height2_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height2/view_4/height2_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])

def interpolate_density2(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()
    locs = []
    for i in xrange(len(x_coords)):
        locs.append([x_coords[i], y_coords[i], z_coords[i]])

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)

        # Compute the interpolated values at each point
        all_points = []
        point_vals = []
        for t in triangle_list:
            hold = tr.density_plot2(t, 0, interp, 20, 1, locs, vals)
            all_points += hold
            for h in hold:
                point_vals.append(tr.mod_shephard_interp(h, locs, vals))

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for a in all_points:
            n = tr.map_to_circle(a, radius=r)
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing density2:", i
        mlab.clf()
        mlab.mesh(xx, yy, zz, color=(0.4,0.4,0.4))
        mlab.points3d(x, y, z, point_vals, colormap='coolwarm', vmin=0, vmax=1, scale_mode='none', scale_factor=0.1)
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density2/view_1/density2_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density2/view_2/density2_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density2/view_3/density2_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density2/view_4/density2_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])

def interpolate_sphere3(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()
    locs = []
    for i in xrange(len(x_coords)):
        locs.append([x_coords[i], y_coords[i], z_coords[i]])

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)
        weights = tr.get_rbf_weigths(tr.rbf_gaussian, locs, vals)

        # Compute the interpolated values at each point
        all_points = []
        triangles = []
        point_vals = []
        for t in triangle_list:
            hold = tr.split_triangles(t, 0, interp)
            for h in hold:
                if not (h.p1 in all_points):
                    all_points.append(h.p1)
                    point_vals.append(tr.rbf_interp(weights, tr.rbf_gaussian, h.p1, locs))#mod_shephard_interp(h.p1, locs, vals))
                if not (h.p2 in all_points):
                    all_points.append(h.p2)
                    point_vals.append(tr.rbf_interp(weights, tr.rbf_gaussian, h.p2, locs))#mod_shephard_interp(h.p2, locs, vals))
                if not (h.p3 in all_points):
                    all_points.append(h.p3)
                    point_vals.append(tr.rbf_interp(weights, tr.rbf_gaussian, h.p3, locs))#mod_shephard_interp(h.p3, locs, vals))
                triangles.append([all_points.index(h.p1), all_points.index(h.p2), all_points.index(h.p3)])

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for a in all_points:
            n = tr.map_to_circle(a, radius=r)
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing sphere3:", i

        # Set up the data to be visualized
        mlab.clf()
        mlab.triangular_mesh(x, y, z, triangles, scalars=point_vals, colormap='coolwarm', vmin=0, vmax=1)

        # Visualize the data from 4 different angles
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere3/view_1/sphere3_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere3/view_2/sphere3_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere3/view_3/sphere3_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_sphere3/view_4/sphere3_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])

def interpolate_height3(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()
    locs = []
    for i in xrange(len(x_coords)):
        locs.append([x_coords[i], y_coords[i], z_coords[i]])

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)
        weights = tr.get_rbf_weigths(tr.rbf_gaussian, locs, vals)

        # Compute the interpolated values at each point
        all_points = []
        triangles = []
        point_vals = []
        for t in triangle_list:
            hold = tr.split_triangles(t, 0, interp)
            #all_points += hold
            for h in hold:
                if not (h.p1 in all_points):
                    all_points.append(h.p1)
                    point_vals.append(tr.rbf_interp(weights, tr.rbf_gaussian, h.p1, locs))#tr.mod_shephard_interp(h.p1, locs, vals))
                if not (h.p2 in all_points):
                    all_points.append(h.p2)
                    point_vals.append(tr.rbf_interp(weights, tr.rbf_gaussian, h.p2, locs))#tr.mod_shephard_interp(h.p2, locs, vals))
                if not (h.p3 in all_points):
                    all_points.append(h.p3)
                    point_vals.append(tr.rbf_interp(weights, tr.rbf_gaussian, h.p3, locs))#tr.mod_shephard_interp(h.p3, locs, vals))
                triangles.append([all_points.index(h.p1), all_points.index(h.p2), all_points.index(h.p3)])

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for j, a in enumerate(all_points):
            n = tr.map_to_circle(a, radius=r+(point_vals[j]**2))
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing height3:", i

        # Set up the data to be visualized
        mlab.clf()
        mlab.triangular_mesh(x, y, z, triangles, scalars=point_vals, colormap='coolwarm', vmin=0, vmax=1)

        # Visualize the data from 4 different angles
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height3/view_1/height3_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height3/view_2/height3_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height3/view_3/height3_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_height3/view_4/height3_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])

def interpolate_density3(data, interp=2):
    # Create a sphere
    r = 5.0
    phi, theta = np.mgrid[0:np.pi:101j, 0:2 * np.pi:101j]

    xx = r*np.sin(phi)*np.cos(theta)
    yy = r*np.sin(phi)*np.sin(theta)
    zz = r*np.cos(phi)

    mlab.figure(1, bgcolor=(1, 1, 1), fgcolor=(0, 0, 0), size=(800, 600))

    # Set up the microphone locations
    x_coords, y_coords, z_coords = get_mic_locations()
    locs = []
    for i in xrange(len(x_coords)):
        locs.append([x_coords[i], y_coords[i], z_coords[i]])

    # Compute a visualization for each time step in data
    avg_time = 0.0
    for i in xrange(data.shape[1]):
        start_t = time.time()
        vals = data[:, i]
        triangle_list = get_triangles(x_coords, y_coords, z_coords, vals)
        weights = tr.get_rbf_weigths(tr.rbf_gaussian, locs, vals)

        # Compute the interpolated values at each point
        all_points = []
        point_vals = []
        for t in triangle_list:
            hold = tr.density_plot3(t, 0, interp, 20, 1, locs, weights, tr.rbf_gaussian)
            all_points += hold
            for h in hold:
                point_vals.append(tr.rbf_interp(weights, tr.rbf_gaussian, h, locs))#tr.mod_shephard_interp(h, locs, vals))

        # Project all of the points onto a sphere
        x = []
        y = []
        z = []
        new_points = []
        for a in all_points:
            n = tr.map_to_circle(a, radius=r)
            if not n in new_points:
                new_points.append(n)

        for a in new_points:
            x.append(a[0])
            y.append(a[1])
            z.append(a[2])

        stop_t = time.time()
        avg_time += (stop_t - start_t)

        print "Visualizing density3:", i
        mlab.clf()
        mlab.mesh(xx, yy, zz, color=(0.4,0.4,0.4))
        mlab.points3d(x, y, z, point_vals, colormap='coolwarm', vmin=0, vmax=1, scale_mode='none', scale_factor=0.1)
        mlab.view(45, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density3/view_1/density3_time_" + str(i) + '.png')
        mlab.view(135, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density3/view_2/density3_time_" + str(i) + '.png')
        mlab.view(225, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density3/view_3/density3_time_" + str(i) + '.png')
        mlab.view(315, 60, 25)
        mlab.orientation_axes()
        mlab.savefig("vis_density3/view_4/density3_time_" + str(i) + '.png')
    mlab.close()
    return (avg_time/data.shape[1])


if __name__ == '__main__':
    file_list = ['sound_data/mic_1.wav', 'sound_data/mic_2.wav', 'sound_data/mic_3.wav',
                 'sound_data/mic_4.wav', 'sound_data/mic_5.wav', 'sound_data/mic_6.wav',
                 'sound_data/mic_7.wav', 'sound_data/mic_8.wav', 'sound_data/mic_9.wav',
                 'sound_data/mic_10.wav', 'sound_data/mic_11.wav', 'sound_data/mic_12.wav',
                 'sound_data/mic_13.wav', 'sound_data/mic_14.wav', 'sound_data/mic_15.wav',
                 'sound_data/mic_16.wav', 'sound_data/mic_17.wav', 'sound_data/mic_18.wav',
                 'sound_data/mic_19.wav', 'sound_data/mic_20.wav', 'sound_data/mic_21.wav',
                 'sound_data/mic_22.wav', 'sound_data/mic_23.wav', 'sound_data/mic_24.wav',
                 'sound_data/mic_25.wav', 'sound_data/mic_26.wav', 'sound_data/mic_27.wav',
                 'sound_data/mic_28.wav', 'sound_data/mic_29.wav', 'sound_data/mic_30.wav',
                 'sound_data/mic_31.wav', 'sound_data/mic_32.wav']
    #plot_wavfiles(file_list)
    #plot_one_file('sound_data/mic_1.wav')
    #show_mic_locations()

    #x_coords, y_coords, z_coords = get_mic_locations()
    #triangles = get_triangles(x_coords, y_coords, z_coords, [0.5]*len(x_coords))
    #print len(x_coords), len(y_coords), len(z_coords), len(triangles)

    data = downsample_wav(file_list, 5, 20)#['sound_data/mic_1.wav', 'sound_data/mic_16.wav', 'sound_data/mic_32.wav'], 60)

    # Linear interpolation
    s1 = interpolate_sphere(np.array(data), 2)
    h1 = interpolate_height(np.array(data), 2)
    d1 = interpolate_density(np.array(data), 1)

    # Modified Shepard's interpolation
    s2 = interpolate_sphere2(np.array(data), 2)
    h2 = interpolate_height2(np.array(data), 2)
    d2 = interpolate_density2(np.array(data), 1)

    # RBF interpolation
    s3 = interpolate_sphere3(np.array(data), 2)
    h3 = interpolate_height3(np.array(data), 2)
    d3 = interpolate_density3(np.array(data), 1)

    print s1, h1, d1
    print s2, h2, d2
    print s3, h3, d3

    #downsample_wav('sound_data/mic_16.wav', 100)
    #downsample_wav('sound_data/mic_32.wav', 100)
    #downsample_wav('sound_data/mic_4.wav')
    #downsample_wav('sound_data/mic_5.wav')
