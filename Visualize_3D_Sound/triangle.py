import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import matplotlib.cm as cmx
import matplotlib
import numpy as np

class triangle:

    def __init__(self, point_1, point_2, point_3, val1=-1, val2=-1, val3=-1):
        points, vals = zip(*sorted(zip([point_1, point_2, point_3], [val1, val2, val3])))
        self.p1 = points[0]
        self.p2 = points[1]
        self.p3 = points[2]
        self.v1 = vals[0]
        self.v2 = vals[1]
        self.v3 = vals[2]
        self.center = self.get_center()

    def __eq__(self, other):
        return ((self.p1 == other.p1) and (self.p2 == other.p2) and (self.p3 == other.p3))

    def __repr__(self):
        return str(self.p1) + " - " + str(self.p1) + " - " + str(self.p3)

    def get_value(self):
        return self.lin_interp(self.center)

    def get_center(self):
        return [(self.p1[0] + self.p2[0] + self.p3[0])/3.0, (self.p1[1] + self.p2[1] + self.p3[1])/3.0, (self.p1[2] + self.p2[2] + self.p3[2])/3.0]

    def lin_interp(self, point):
        # Check if point is equal to one of the triangle corners
        if (point[0] == self.p1[0]) and (point[1] == self.p1[1]) and (point[2] == self.p1[2]):
            return self.v1

        if (point[0] == self.p2[0]) and (point[1] == self.p2[1]) and (point[2] == self.p2[2]):
            return self.v2

        if (point[0] == self.p3[0]) and (point[1] == self.p3[1]) and (point[2] == self.p3[2]):
            return self.v3

        # Compute the areas of the different triangles to use in the interpolation
        a = area_of_triangle(self)
        if a == 0:
            return -1.0
        r = area_of_triangle(triangle(self.p1, point, self.p3))/a
        s = area_of_triangle(triangle(self.p1, self.p2, point))/a

        # Compute interpolated result
        return (1 - r - s)*self.v1 + r*self.v2 + s*self.v3
        
def rbf_gaussian(p1, p2, c=1):
    '''
    Computes the values for the gaussian interpolation function used in the radial basis function interpolation.
    '''
    r = geodesic_distance(p1, p2)
    return np.exp(-1.0*(r/c)**2)
    

def get_rbf_weigths(function, points, values):
    '''
    Computes the weights for each interpolation kernel used in the radial basis function interpolation
    '''

    # Compute the function-point array
    O = np.zeros((len(points), len(points)))
    for i in xrange(len(points)):
        for j in xrange(len(points)):
            O[i][j] = function(points[i], points[j])

    # Find the solution to the linear system
    return np.linalg.solve(O, values)

def rbf_interp(weights, function, x, points):
    '''
    Interpolates the value at the point x using the radial basis function interpolation
    '''
    total = 0
    for i, p in enumerate(points):
        total += weights[i]*function(x, p)
    return total

def mod_shephard_interp(point, locations, values, r=1):
    '''
    Interpolates the value at the point using Modified Shapard's Method
    '''
    # Set up variables
    p = -2.0
    w = []
    total = 0.0
    w_sum = 0.0

    # Compute the distances between the point and all sample points on the sphere
    for i in xrange(len(locations)):
        w.append(geodesic_distance(point, locations[i]))
        if w[-1] != 0:
            w_sum += (w[-1]**p)

    # Interpolate the value at the point
    for i in xrange(len(w)):
        if w[i] != 0:
            total += ((w[i]**p)/w_sum) * values[i]
        else:
            return values[i]

    return total
        


def geodesic_distance(p1, p2, r=1):
    '''
    Compute the geodesic distance between two points
    '''
    # Compute the normals at the two points
    n1 = np.array(p1)/np.linalg.norm(p1)
    n2 = np.array(p2)/np.linalg.norm(p2)

    # Compute the angle between the points
    ang = np.arctan2(np.linalg.norm(np.cross(n1, n2)), np.dot(n1, n2))

    return r * ang

def area_of_triangle(t):
    '''
    Compute the area of a triangle defined by 3 points
    '''
    v1 = np.array([t.p1[0] - t.p2[0], t.p1[1] - t.p2[1], t.p1[2] - t.p2[2]])
    v2 = np.array([t.p3[0] - t.p2[0], t.p3[1] - t.p2[1], t.p3[2] - t.p2[2]])
    c = np.linalg.norm(np.cross(v1, v2))
    return c/2.0

def get_random_points(tr, num):
    '''
    Get the specified number of random points within the triangle
    '''

    # Compute the specified number of points
    points = []
    for i in xrange(num):

        # Get the random spacing values and ensure that they are inside the triangle
        a = np.random.uniform()
        b = np.random.uniform()
        if (a + b >= 1):
            a = 1 - a
            b = 1 - b

        # Compute a random point within the triangle
        v1 = np.array(tr.p1)
        v2 = np.array(tr.p2)
        v3 = np.array(tr.p3)
        x = v1 + a*(v2 - v1) + b*(v3 - v1)
        points.append(x.tolist())

    return points

def density_plot1(tr, d, md, num_bins, bin_inc):
    '''
    Compute a number of points within the triangle depending on the value around those points.
    The triangle is subdivided into 4 triangles recursively for the difference between d and md.
    '''
    # Test if stop condition has been reached
    if (d > md):
        val = int(np.ceil(tr.lin_interp(tr.center)/(1.0/num_bins)) * bin_inc)
        return get_random_points(tr, val)

    # Compute midpoints of triangle sides
    new_1 = [(tr.p2[0] + tr.p3[0])/2.0, (tr.p2[1] + tr.p3[1])/2.0, (tr.p2[2] + tr.p3[2])/2.0]
    new_2 = [(tr.p1[0] + tr.p3[0])/2.0, (tr.p1[1] + tr.p3[1])/2.0, (tr.p1[2] + tr.p3[2])/2.0]
    new_3 = [(tr.p2[0] + tr.p1[0])/2.0, (tr.p2[1] + tr.p1[1])/2.0, (tr.p2[2] + tr.p1[2])/2.0]

    # Compute 4 new triangles using midpoints
    ntr_1 = triangle(tr.p1, new_2, new_3, tr.v1, tr.lin_interp(new_2), tr.lin_interp(new_3))
    ntr_2 = triangle(tr.p2, new_1, new_3, tr.v2, tr.lin_interp(new_1), tr.lin_interp(new_3))
    ntr_3 = triangle(tr.p3, new_1, new_2, tr.v3, tr.lin_interp(new_1), tr.lin_interp(new_2))
    ntr_4 = triangle(new_1, new_2, new_3, tr.lin_interp(new_1), tr.lin_interp(new_2), tr.lin_interp(new_3))

    # Split the four triangles into smaller parts
    complete = []
    complete += density_plot1(ntr_1, d + 1, md, num_bins, bin_inc)
    complete += density_plot1(ntr_2, d + 1, md, num_bins, bin_inc)
    complete += density_plot1(ntr_3, d + 1, md, num_bins, bin_inc)
    complete += density_plot1(ntr_4, d + 1, md, num_bins, bin_inc)

    return complete

def density_plot2(tr, d, md, num_bins, bin_inc, locs, vals):
    '''
    Compute a number of points within the triangle depending on the value around those points.
    The triangle is subdivided into 4 triangles recursively for the difference between d and md.
    '''
    # Test if stop condition has been reached
    if (d > md):
        val = int(np.ceil(mod_shephard_interp(tr.center, locs, vals)/(1.0/num_bins)) * bin_inc)
        return get_random_points(tr, val)

    # Compute midpoints of triangle sides
    new_1 = [(tr.p2[0] + tr.p3[0])/2.0, (tr.p2[1] + tr.p3[1])/2.0, (tr.p2[2] + tr.p3[2])/2.0]
    new_2 = [(tr.p1[0] + tr.p3[0])/2.0, (tr.p1[1] + tr.p3[1])/2.0, (tr.p1[2] + tr.p3[2])/2.0]
    new_3 = [(tr.p2[0] + tr.p1[0])/2.0, (tr.p2[1] + tr.p1[1])/2.0, (tr.p2[2] + tr.p1[2])/2.0]

    # Compute 4 new triangles using midpoints
    ntr_1 = triangle(tr.p1, new_2, new_3, tr.v1, mod_shephard_interp(new_2, locs, vals), mod_shephard_interp(new_3, locs, vals))
    ntr_2 = triangle(tr.p2, new_1, new_3, tr.v2, mod_shephard_interp(new_1, locs, vals), mod_shephard_interp(new_3, locs, vals))
    ntr_3 = triangle(tr.p3, new_1, new_2, tr.v3, mod_shephard_interp(new_1, locs, vals), mod_shephard_interp(new_2, locs, vals))
    ntr_4 = triangle(new_1, new_2, new_3, mod_shephard_interp(new_1, locs, vals), mod_shephard_interp(new_2, locs, vals), mod_shephard_interp(new_3, locs, vals))

    # Split the four triangles into smaller parts
    complete = []
    complete += density_plot2(ntr_1, d + 1, md, num_bins, bin_inc, locs, vals)
    complete += density_plot2(ntr_2, d + 1, md, num_bins, bin_inc, locs, vals)
    complete += density_plot2(ntr_3, d + 1, md, num_bins, bin_inc, locs, vals)
    complete += density_plot2(ntr_4, d + 1, md, num_bins, bin_inc, locs, vals)

    return complete

def density_plot3(tr, d, md, num_bins, bin_inc, locs, weights, func):
    '''
    Compute a number of points within the triangle depending on the value around those points.
    The triangle is subdivided into 4 triangles recursively for the difference between d and md.
    '''
    # Test if stop condition has been reached
    if (d > md):
        val = int(np.ceil(rbf_interp(weights, func, tr.center, locs)/(1.0/num_bins)) * bin_inc)
        return get_random_points(tr, val)

    # Compute midpoints of triangle sides
    new_1 = [(tr.p2[0] + tr.p3[0])/2.0, (tr.p2[1] + tr.p3[1])/2.0, (tr.p2[2] + tr.p3[2])/2.0]
    new_2 = [(tr.p1[0] + tr.p3[0])/2.0, (tr.p1[1] + tr.p3[1])/2.0, (tr.p1[2] + tr.p3[2])/2.0]
    new_3 = [(tr.p2[0] + tr.p1[0])/2.0, (tr.p2[1] + tr.p1[1])/2.0, (tr.p2[2] + tr.p1[2])/2.0]

    # Compute 4 new triangles using midpoints
    ntr_1 = triangle(tr.p1, new_2, new_3, tr.v1, rbf_interp(weights, func, new_2, locs), rbf_interp(weights, func, new_3, locs))
    ntr_2 = triangle(tr.p2, new_1, new_3, tr.v2, rbf_interp(weights, func, new_1, locs), rbf_interp(weights, func, new_3, locs))
    ntr_3 = triangle(tr.p3, new_1, new_2, tr.v3, rbf_interp(weights, func, new_1, locs), rbf_interp(weights, func, new_2, locs))
    ntr_4 = triangle(new_1, new_2, new_3, rbf_interp(weights, func, new_1, locs), rbf_interp(weights, func, new_2, locs), rbf_interp(weights, func, new_3, locs))

    # Split the four triangles into smaller parts
    complete = []
    complete += density_plot3(ntr_1, d + 1, md, num_bins, bin_inc, locs, weights, func)
    complete += density_plot3(ntr_2, d + 1, md, num_bins, bin_inc, locs, weights, func)
    complete += density_plot3(ntr_3, d + 1, md, num_bins, bin_inc, locs, weights, func)
    complete += density_plot3(ntr_4, d + 1, md, num_bins, bin_inc, locs, weights, func)

    return complete


'''def split_triangle1(tr, d, md):
    # Test if stop condition has been reached
    if (d > md):
        return [tr.center]

    # Compute midpoints of triangle sides
    new_1 = [(tr.p2[0] + tr.p3[0])/2.0, (tr.p2[1] + tr.p3[1])/2.0, (tr.p2[2] + tr.p3[2])/2.0]
    new_2 = [(tr.p1[0] + tr.p3[0])/2.0, (tr.p1[1] + tr.p3[1])/2.0, (tr.p1[2] + tr.p3[2])/2.0]
    new_3 = [(tr.p2[0] + tr.p1[0])/2.0, (tr.p2[1] + tr.p1[1])/2.0, (tr.p2[2] + tr.p1[2])/2.0]

    # Compute 4 new triangles using midpoints
    ntr_1 = triangle(tr.p1, new_2, new_3)
    ntr_2 = triangle(tr.p2, new_1, new_3)
    ntr_3 = triangle(tr.p3, new_1, new_2)
    ntr_4 = triangle(new_1, new_2, new_3)

    # Split the four triangles into smaller parts
    complete = [tr.center]
    complete += split_triangle1(ntr_1, d + 1, md)
    complete += split_triangle1(ntr_2, d + 1, md)
    complete += split_triangle1(ntr_3, d + 1, md)
    complete += split_triangle1(ntr_4, d + 1, md)

    return complete'''

def split_triangles(tr, d, md):
    # Test if stop condition has been reached
    if (d > md):
        return [tr]

    # Compute midpoints of triangle sides
    new_1 = [(tr.p2[0] + tr.p3[0])/2.0, (tr.p2[1] + tr.p3[1])/2.0, (tr.p2[2] + tr.p3[2])/2.0]
    new_2 = [(tr.p1[0] + tr.p3[0])/2.0, (tr.p1[1] + tr.p3[1])/2.0, (tr.p1[2] + tr.p3[2])/2.0]
    new_3 = [(tr.p2[0] + tr.p1[0])/2.0, (tr.p2[1] + tr.p1[1])/2.0, (tr.p2[2] + tr.p1[2])/2.0]

    # Compute 4 new triangles using midpoints
    ntr_1 = triangle(tr.p1, new_2, new_3, tr.v1, tr.lin_interp(new_2), tr.lin_interp(new_3))
    ntr_2 = triangle(tr.p2, new_1, new_3, tr.v2, tr.lin_interp(new_1), tr.lin_interp(new_3))
    ntr_3 = triangle(tr.p3, new_1, new_2, tr.v3, tr.lin_interp(new_1), tr.lin_interp(new_2))
    ntr_4 = triangle(new_1, new_2, new_3, tr.lin_interp(new_1), tr.lin_interp(new_2), tr.lin_interp(new_3))

    # Split the four triangles into smaller parts
    complete = [tr]
    complete += split_triangles(ntr_1, d + 1, md)
    complete += split_triangles(ntr_2, d + 1, md)
    complete += split_triangles(ntr_3, d + 1, md)
    complete += split_triangles(ntr_4, d + 1, md)

    return complete

def map_to_circle(point, origin=[0.0, 0.0, 0.0], radius=1.0):
    '''
    Projects the given point to a point on a circle with the given radius and origin.
    '''
    v = np.array([point[0] - origin[0], point[1] - origin[1], point[2] - origin[2]])
    v_norm = v/np.linalg.norm(v)
    new_p = np.array(origin) + radius*v_norm
    return new_p.tolist()
    

if __name__ == '__main__':
    basic = triangle([0.1, 0.1, 0.1], [0.1, 0.6, 0.1], [0.6, 0.1, 0.1], 0.3, 0.2, 0.8)

    print(area_of_triangle(basic))

    #mids = split_triangle(basic, 0, 3)
    mids = density_plot(basic, 0, 2, 5, 2)
    new_mids = []
    for m in mids:
        new_mids.append(map_to_circle(m))
    print len(mids)
    x = []
    y = []
    z = []
    cs = []
    for i, m in enumerate(new_mids):
        x.append(m[0])
        y.append(m[1])
        z.append(m[2])
        cs.append(basic.lin_interp([mids[i][0], mids[i][1], mids[i][2]]))
    cm = plt.get_cmap('coolwarm')
    cNorm = matplotlib.colors.Normalize(vmin=0, vmax=1)
    scalarMap = cmx.ScalarMappable(norm=cNorm, cmap=cm)
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.scatter(x, y, z, marker='.', c=scalarMap.to_rgba(cs))
    scalarMap.set_array(cs)
    fig.colorbar(scalarMap)
    plt.show()
#    fig = plt.figure()
#    ax = fig.add_subplot(111, projection='3d')
#    ax.scatter(x, y, z)
#    plt.show()
