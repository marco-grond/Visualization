import numpy as np
from scipy.interpolate import interp1d
from scipy.ndimage import sobel
from PIL import Image
import matplotlib.pyplot as plt
import time
import math
import sys

def interp(data_array, spacing_list, point, interp_type):
    '''
    Compute the interpolated value at the current point
    point - A 1D numpy array of the current point
    '''
    # Find the indices of numbers necesary for interpolation
    indices = [[], [], []]
    for i in xrange(3):
        for j in xrange(-2, 4):
            indices[i].append(int(math.floor(1.0*point[i]/spacing_list[i]) + j))

    #print indices

    # Save the number and spacing values necessary for interpolation
    interp_vals = np.zeros((len(indices[0]), len(indices[1]), len(indices[2])))
    for i in xrange(len(indices[0])):
        for j in xrange(len(indices[1])):
            for k in xrange(len(indices[2])):
                if (0 <= indices[0][i] < data_array.shape[0]) and (0 <= indices[1][j] < data_array.shape[1]) and (0 <= indices[2][k] < data_array.shape[2]):
                    interp_vals[i][j][k] = data_array[indices[0][i]][indices[1][j]][indices[2][k]]

    # Find the correct values in space of the sample points in interp_vals
    interp_spacing = [[], [], []]
    for i in xrange(len(indices[0])):
        interp_spacing[0].append(indices[0][i] * spacing_list[0])
        interp_spacing[1].append(indices[1][i] * spacing_list[1])
        interp_spacing[2].append(indices[2][i] * spacing_list[2])
    
    # Interpolate along the x-axis
    interp_vals = np.asarray(interp_vals)
    after_x = []
    for j in xrange(interp_vals.shape[1]):
        after_x.append([])
        for k in xrange(interp_vals.shape[2]):
            f = interp1d(interp_spacing[0], interp_vals[:, j, k], kind=interp_type)
            after_x[j].append(f(point[0]))

    # Interpolate along the y-axis
    after_x = np.asarray(after_x)
    after_y = []
    for k in xrange(after_x.shape[1]):
        f = interp1d(interp_spacing[1], after_x[:, k], kind=interp_type)
        after_y.append(f(point[1]))

    # Compute and return the final value
    after_y = np.asarray(after_y)
    f = interp1d(interp_spacing[2], after_y, kind=interp_type)
    after_z = f(point[2])

    return after_z

def norm_vector(vector):
    '''
    Normalize the given vector
    vector - A three dimensional vector
    '''
    return np.array(vector)/np.linalg.norm(vector)

def trace_ray(ray_vector, start_point, start_step, isovalue, data_dim, max_ray_len, data_array, sample_spacing, interp_type):
    '''
    Move along the ray and use the interval bisection method to determine the point in space along the ray that has the correct isovalue.
    '''

    # Normalize the ray vector, so that it can be used to move a certain distance along the ray
    direction = norm_vector(ray_vector)

    # Initialize a point at which to get the interpolated value
    current_point = np.array([start_point[0], start_point[1], start_point[2]])

    # Initialize variables to determine whether to stop running the interval bisection method
    stop = False
    halve_step = False
    step = start_step
    min_step = start_step/100.0
    prev_g = None
    first_pos = None

    # Compute the maximum x, y and z values that a point can have and still be in the volume
    max_x = ((data_dim[0]-1)*sample_spacing[0])
    max_y = ((data_dim[1]-1)*sample_spacing[1])
    max_z = ((data_dim[2]-1)*sample_spacing[2])

    # Run the interval bisection method
    while (not stop):

        # Check if the current point is further from the starting position than allowed
        ray_length = np.linalg.norm(current_point - start_point)
        if (ray_length > max_ray_len):
            return [-1, -1, -1]

        # Check if the ray has intersected the object
        if not ((0 <= current_point[0] <= max_x) and (0 <= current_point[1] <= max_y) and (0 <= current_point[2] <= max_z)):
            # Object are not intersected
            current_point += (direction * step)
            continue


        # Compute the function value g of the interpolated value at the current point minus the isovalue
        g = interp(data_array, sample_spacing, current_point, interp_type) - isovalue

        # Check if a zero crossing was made
        if (prev_g == None):
            prev_g = g
            first_pos = (g > 0)
        elif ((prev_g > 0) and (g < 0)) or ((prev_g < 0) and (g > 0)):
            halve_step = True

        # Check if the value of g is above or below 0
        if (g > 0):
            # Check if the step size should be made smaller
            if (halve_step):
                step /= 2.0

            if (first_pos):
                # Step forwards along the ray for step length
                current_point += (direction * step)
            else:
                # Step backwards along the ray for step length
                current_point -= (direction * step)

        elif (g < 0):
            # Change the value of the halve_step variable to be true and halve the step size
            if (halve_step):
                step /= 2.0

            if (not first_pos):
                # Step forwards along the ray for step length
                current_point += (direction * step)
            else:
                # Step backwards along the ray for step length
                current_point -= (direction * step)
            
        else:
            stop = True

        # Check if the step size has become too small
        if (step < min_step):
            stop = True

    # Return the point at which the isosurface is located
    return current_point

def image_plane_coords(camera_pos, camera_look_at, camera_view_angle, camera_up_vec, image_plane_distance, image_resolution):
    '''
    Compute the necessary data to represent the image plane.
    '''
    # Make sure that the vectors are numpy arrays
    camera_look_at = np.array(camera_look_at)
    camera_pos = np.array(camera_pos)

    # Compute the vector of where the camera is looking and normalize
    look_vec = norm_vector(camera_look_at - camera_pos)

    # Get the position of where the camera_look_at vector would cross the image plane
    image_center = camera_pos + (look_vec*image_plane_distance)#[]

    # Compute the vector along the x-axis of the image by taking the cross product of look-at vector and the up-vector at the intersection point
    camera_up_vec = norm_vector(camera_up_vec)
    camera_x = norm_vector(np.cross(look_vec, camera_up_vec))

    # Compute half the length of the x-axis in the image plane
    x_length = abs(math.tan(camera_view_angle/2.0)*image_plane_distance)
    y_length = x_length * (1.0*image_resolution[1]/image_resolution[0])

    return image_center, [camera_x, camera_up_vec], [x_length, y_length]
    
    
def compute_image(data_array, image_center, image_vectors, image_lengths, image_resolutions, camera_pos, sample_spacing, isoval, interp_type, light_source):
    '''
    Compute the image by tracing rays through the different pixels and applying phong shading to the end result.
    '''

    # Create an image with all zeros, that will be used to keep the spatial locations corresponding to pixels
    image_lookup = np.zeros((image_resolutions[0], image_resolutions[1])).tolist()

    # Determine the locations of the pixel values
    for j in xrange(image_resolutions[1]):
        for i in xrange(image_resolutions[0]):
            pixel_point = [0, 0, 0]

            # Move the pixel-point in the x-direction across the image plane
            x_step = image_lengths[0] * ((1.0*i-image_resolutions[0]/2)/(image_resolutions[0]/2.0))
            pixel_point = image_center + (image_vectors[0] * x_step)

            # Move the pixel-point in the y-direction across the image plane
            y_step = image_lengths[1] * ((1.0*j-image_resolutions[1]/2)/(image_resolutions[1]/2.0))
            pixel_point = pixel_point + (image_vectors[1] * y_step)

            # Add the pixel-point values to the correct pixel in the image lookup list
            image_lookup[i][j] = pixel_point

    # Trace rays from the camera postion through the pixel locations
    max_ray_length = get_furthest_point(camera_pos, [len(data_array)*sample_spacing[0], len(data_array[0])*sample_spacing[1], len(data_array[0][0])*sample_spacing[2]])*1.5
    step_size = math.sqrt(sample_spacing[0]**2 + sample_spacing[1]**2 + sample_spacing[2]**2)
    image_lookup = np.array(image_lookup)
    image_locs = np.zeros(image_lookup.shape)
    test_image = np.zeros((image_locs.shape[0], image_locs.shape[1]))
    num = -1
    print "Starting ray tracing..."
    total_ray = 0
    for i in xrange(image_lookup.shape[0]):

        # Print progress
        if (int(100.0*i/image_lookup.shape[0]) > num):
            num = int(100.0*i/image_lookup.shape[0])
            print str(num) + "% done."

        for j in xrange(image_lookup.shape[1]):
            # Get the vector from the camera origin to the point on the image
            vec_1 = norm_vector(image_lookup[i][j] - camera_pos)

            #  Trace the ray from the camera position through the pixel and store the 3D location where it hits the isosurface
            start = time.time()
            image_locs[i][j] = trace_ray(vec_1, image_lookup[i][j], step_size, isoval, [len(data_array), len(data_array[0]), len(data_array[0][0])], max_ray_length, data_array, sample_spacing, interp_type)
            end = time.time()
            total_ray += (end - start)

    print "**********************************\nAverage ray trace time:", (total_ray/(image_resolutions[0]*image_resolutions[1])),"\n*********************************"

    # Compute the colour value at any given location using phong shading
    final_image = np.zeros((image_locs.shape[0], image_locs.shape[1]))
    max_x = data_array.shape[0] * sample_spacing[0]
    max_y = data_array.shape[1] * sample_spacing[1]
    max_z = data_array.shape[2] * sample_spacing[2]
    I_i = 245
    I_a = 10
    x_deriv, y_deriv, z_deriv = compute_derivatives(data_array)
    print "Computing final image..."
    for i in xrange(len(final_image)):
        for j in xrange(len(final_image[0])):

            # Test if the returned point is inside of the volume.
            if ((image_locs[i][j][0] < 0) or (image_locs[i][j][1] < 0) or (image_locs[i][j][2] < 0) or
                (image_locs[i][j][0] > max_x) or (image_locs[i][j][1] > max_y) or (image_locs[i][j][2] > max_z)):
                final_image[i][j] = 0
            else:
                incoming_vector = get_vector(light_source, image_locs[i][j])
                normal_vector = [interp(x_deriv, sample_spacing, image_locs[i][j], interp_type), 
                                 interp(y_deriv, sample_spacing, image_locs[i][j], interp_type),
                                 interp(z_deriv, sample_spacing, image_locs[i][j], interp_type)]
                if (vector_magnitude(incoming_vector) == 0) or (vector_magnitude(normal_vector) == 0):
                    print "Invalid normal value at position:", image_locs[i][j]
                    final_image[i][j] = 0
                else:
                    cosine_angle = np.dot(incoming_vector, normal_vector)/(vector_magnitude(incoming_vector) * vector_magnitude(normal_vector))
                    if cosine_angle < 0:
                        final_image[i][j] = I_a
                    else:
                        final_image[i][j] = int(I_i*cosine_angle) + I_a

    return final_image
    


def get_vector(a, b):
    '''
    Compute the vector between the points a and b. The vector's direction is from a to b.
    '''

    return [b[0] - a[0], b[1] - a[1], b[2] - a[2]]

def vector_magnitude(vec):
    '''
    Computes the magnitude of a vector.
    '''

    total = 0.0
    for i in vec:
        total += i**2
    return math.sqrt(total)

def get_furthest_point(camera_point, image_shape):
    '''
    Find the furthest corner on the volume from the camera origin point.
    '''

    # Define the possible x, y and z values for the corners of the block
    max_dist = 0
    pos_x = [0, image_shape[0]]
    pos_y = [0, image_shape[1]]
    pos_z = [0, image_shape[2]]

    # Compute the distance between the camera and all corners and return the maximum distance
    for i in pos_x:
        for j in pos_y:
            for k in pos_z:
                max_dist = max(max_dist, math.sqrt((camera_point[0] - i)**2 + (camera_point[1] - j)**2 + (camera_point[2] - k)**2))

    return max_dist
        

def compute_derivatives(original_array):
    '''
    Computes arrays from the original_array by computing the derivative in the x, y and z direction.
    '''
    # Compute the x, y and z derivative filters
    x_deriv = sobel(original_array, 0)
    y_deriv = sobel(original_array, 1)
    z_deriv = sobel(original_array, 2)

    return x_deriv, y_deriv, z_deriv


def read_file(filename, data_res, data_spacing, datatype):
    '''
    Read the data from the file into a numpy array, and change the shape of the array to be correct. 
    '''
    # Read the data from the file into an array
    read_data = np.fromfile(filename, dtype=datatype)
    data_array = np.zeros((data_res[0], data_res[1], data_res[2]))
 
    # Reformat the data
    count = 0
    for k in xrange(data_res[2]):
        for j in xrange(data_res[1]):
            for i in xrange(data_res[0]):
                data_array[i][j][k] = read_data[count]
                count += 1

    return data_array


def toy_example():
    '''
    Computes a toy example to test the ray tracer.
    '''

    camera_position = [-50, 25, -50]
    image_resolution = [100, 100]

    # Create toy example of spheres
    test_array = np.zeros((50, 50, 50))
    camera_lookat = [len(test_array)/2, len(test_array[0])/2, len(test_array[0][0])/2]
    print camera_lookat
    for i in xrange(len(test_array)):
        for j in xrange(len(test_array)):
            for k in xrange(len(test_array[0][0])):
                test_array[i][j][k] = (i-len(test_array)/2)**2 + (j-len(test_array)/2)**2 + (k-len(test_array)/2)**2

    # Compute the x, y and z derivatives
    x_deriv, y_deriv, z_deriv = compute_derivatives(test_array)

    # Set up a camera and get the image plane coordinates
    im_center, im_vecs, im_lens = image_plane_coords(camera_pos = camera_position, 
                                                     camera_look_at = camera_lookat, 
                                                     camera_view_angle = math.pi/6.0, 
                                                     camera_up_vec = [0, 1, 0], 
                                                     image_plane_distance = 50, 
                                                     image_resolution = image_resolution)

    # Get the image
    start = time.time()
    im = compute_image(test_array, im_center, im_vecs, im_lens, image_resolution, camera_position, [1, 1, 1], 100, 'linear', [-100, 25, -100])
    end = time.time()
    print "Computed image in:", (end - start), "secs"
    image = Image.fromarray(im).convert('RGB')
    image.show()
    image.save('toy_example.png')
    print im_center, im_vecs, im_lens


def compute(camera_pos, resolution, image_plane_dist, im_res, file_name, spacing_list, isoval, interp_type, im_name, camera_up_vec, 
            camera_view_angle, input_type, camera_lookat, light_position):
    '''
    Attempts to compute an image from the given parameters.
    '''

    print "Computing image plane info..."
    im_center, im_vecs, im_lens = image_plane_coords(camera_pos = camera_pos, 
                                                     camera_look_at = camera_lookat,
                                                     camera_view_angle = camera_view_angle/2.0, 
                                                     camera_up_vec = camera_up_vec, 
                                                     image_plane_distance = image_plane_dist, 
                                                     image_resolution = im_res)
    print "Reading in data..."
    data_array = read_file(filename=file_name, 
                           data_res=resolution, 
                           data_spacing=spacing_list, 
                           datatype=input_type)

    print "Starting interpolation..."
    start = time.time()
    final_im = compute_image(data_array=data_array, 
                             image_center=im_center, 
                             image_vectors=im_vecs, 
                             image_lengths=im_lens, 
                             image_resolutions=im_res, 
                             camera_pos=camera_pos, 
                             sample_spacing=spacing_list, 
                             isoval=isoval, 
                             interp_type=interp_type,
                             light_source=light_position)
    end = time.time()

    print "Computed image in:", (end - start), "secs"
    im = Image.fromarray(final_im).convert('RGB')
    im.save(im_name)


def intersect_plane(origin, vector, plane_point, plane_normal, volume_dimensions):
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
        return denominator

    # Compute the distance between the original point and the plane point
    dist = np.dot(plane_point - origin, plane_normal)/denominator

    # Compute the intersection point between the vector and the plane and check if it would intersect the volume
    point = origin + (vector * dist)
    if (0 <= point[0] <= volume_dimensions[0]) and (0 <= point[1] <= volume_dimensions[1]) and (0 <= point[2] <= volume_dimensions[2]):
        return point
    else:
        print point, dist
        return [-1, -1, -1]

if __name__ == '__main__':
    # Try to read specification file
    file_list = []
    if len(sys.argv) > 1:
        for f in sys.argv[1:]:
            file_list.append(f)
    else:
        print "Computing toy example..."
        toy_example()
        exit()

    for f in file_list:
        try:
            options = {'-inputFile' : None,
                       '-inputType': None,
                       '-inputSpacing': None,
                       '-inputResolution': None,
                       '-cameraOrigin': None,
                       '-cameraUp': None,
                       '-cameraLookat': None,
                       '-cameraFov': None,
                       '-cameraResolution': None,
                       '-imagePlaneDistance': None,
                       '-isoValue': None,
                       '-outFile': None,
                       '-lightPosition': None,
                       '-interpType': None}

            with open(f, 'r') as file_name:
                for line in file_name:
                    lines = line.split()
                    if lines[0] == '-inputFile':
                        options[lines[0]] = lines[1]

                    elif lines[0] == '-inputType':
                        if lines[1] == 'uint8':
                            options[lines[0]] = np.uint8
                        elif lines[1] == 'uint16':
                            options[lines[0]] = np.uint16
                        else:
                            print 'Unknown option for -inputType.'
                            exit()

                    elif lines[0] == '-inputSpacing':
                        options[lines[0]] = [float(lines[1]), float(lines[2]), float(lines[3])]

                    elif lines[0] == '-inputResolution':
                        options[lines[0]] = [int(lines[1]), int(lines[2]), int(lines[3])]

                    elif lines[0] == '-cameraOrigin':
                        options[lines[0]] = [float(lines[1]), float(lines[2]), float(lines[3])]

                    elif lines[0] == '-cameraUp':
                        options[lines[0]] = [float(lines[1]), float(lines[2]), float(lines[3])]

                    elif lines[0] == '-cameraLookat':
                        options[lines[0]] = [float(lines[1]), float(lines[2]), float(lines[3])]

                    elif lines[0] == '-cameraFov':
                        options[lines[0]] = float(lines[1])/180.0 * math.pi

                    elif lines[0] == '-cameraResolution':
                        options[lines[0]] = [int(lines[1]), int(lines[2])]

                    elif lines[0] == '-isoValue':
                        options[lines[0]] = float(lines[1])

                    elif lines[0] == '-outFile':
                        options[lines[0]] = lines[1]

                    elif lines[0] == '-lightPosition':
                        options[lines[0]] = [float(lines[1]), float(lines[2]), float(lines[3])]

                    elif lines[0] == '-imagePlaneDistance':
                        options[lines[0]] = float(lines[1])

                    elif lines[0] == '-interpType':
                        if lines[1] == 'linear':
                            options[lines[0]] = lines[1]
                        elif lines[1] == 'cubic':
                            options[lines[0]] = lines[1]
                        else:
                            print "Unknown interpolation type. Quiting."
                            exit()

                    else:
                        print 'Unknown option:', lines[0]


            if options['-inputFile'] == None:
                print "No input file specified. Quiting."
                exit()

            if options['-inputType'] == None:
                print "No inputType specified. Quiting."
                exit()

            if options['-inputSpacing'] == None:
                print "No inputSpacing specified. Quiting."
                exit()

            if options['-inputResolution'] == None:
                print "No inputResolution specified. Quiting."
                exit()

            if options['-cameraOrigin'] == None:
                print "No cameraOrigin specified. Quiting."
                exit()

            if options['-cameraUp'] == None:
                print "No cameraUp specified. Quiting."
                exit()

            if options['-cameraLookat'] == None:
                print "No cameraLookat specified. Setting to center of object."
                options['-cameraLookat'] = [options['-inputResolution'][0]/2.0 * options['-inputSpacing'][0],
                                            options['-inputResolution'][1]/2.0 * options['-inputSpacing'][1],
                                            options['-inputResolution'][2]/2.0 * options['-inputSpacing'][2]]

            if options['-cameraFov'] == None:
                print "No cameraFov specified. Quiting."
                exit()

            if options['-cameraResolution'] == None:
                print "No cameraResolution specified. Quiting."
                exit()

            if options['-isoValue'] == None:
                print "No isoValue specified. Quiting."
                exit()

            if options['-outFile'] == None:
                print "No outFile specified. Quiting."
                exit()

            if options['-imagePlaneDistance'] == None:
                print "No imagePlaneDistance specified. Quiting."
                exit()

            if options['-lightPosition'] == None:
                print "No lightPosition specified. Setting to cameraOrigin."
                options['-lightPosition'] = [options['-cameraOrigin'][0], options['-cameraOrigin'][1], options['-cameraOrigin'][2]]

            if options['-interpType'] == None:
                print "No interpType specified. Quiting."
                exit()

            print "****************************************\nComputing image", options['-outFile']

            compute(camera_pos=options['-cameraOrigin'], 
                    resolution=options['-inputResolution'], 
                    image_plane_dist=options['-imagePlaneDistance'], 
                    im_res=options['-cameraResolution'], 
                    file_name=options['-inputFile'], 
                    spacing_list=options['-inputSpacing'], 
                    isoval=options['-isoValue'], 
                    interp_type=options['-interpType'], 
                    im_name=options['-outFile'], 
                    camera_up_vec=options['-cameraUp'], 
                    camera_view_angle=options['-cameraFov'],
                    input_type=options['-inputType'],
                    camera_lookat=options['-cameraLookat'],
                    light_position=options['-lightPosition'])

        except Exception as e:
            print "Unable to read file..."
            print e

