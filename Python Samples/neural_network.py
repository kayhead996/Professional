# Homework 2
# Neural Network
# Keyur Ved
# CS 559-A


import numpy as np
import math
import matplotlib.pyplot as pyplt
from sklearn.metrics import accuracy_score, log_loss
from mpl_toolkits.mplot3d import Axes3D
import sys

THRESHOLD = 10**(-15)

def sigmoid(x, deriv=False):
    """ Perform the sigmoid function or the sigmoid derivative 
    Parameters
    ----------
    x: ndarray
        Input matrix

    deriv (optional): boolean
        Flag to determine derivative calculation.

    Returns
    -------
    ndarray
        Input matrix run through sigmoid or sigmoid derivative
    """
    if deriv:
        return np.multiply(x, (1-x))
    return 1.0/(1 + np.exp(-x)) 

def relufn(x, deriv=False):
    """ Perform the relu function or the relu derivative 
    Parameters
    ----------
    x: ndarray
        Input matrix

    deriv (optional): boolean
        Flag to determine derivative calculation.

    Returns
    -------
    ndarray
        Input matrix run through relu or relu derivative
    """
    if deriv: 
        return np.vectorize(lambda x: 1 * (x > 0))(x)
    return np.vectorize(lambda x: x * (x > 0))(x)


def convert_to_binary(l):
    """ Perform binary classification on weighted values 
    
    Parameters
    ----------
    l: ndarray
        Output values

    Returns
    -------
    Values classified on a binary scale
    """
    def convert(x): return 1 if x > 0.5 else 0
    return np.vectorize(convert)(l)

def neural_net(X, Y, R, eta, lam, stop, test_X, test_Y, early_stop=False):
    """ Main neural network function 

    Parameters
    ----------
    X: ndarray
        Input training matrix of size N x D
    Y: ndarray
        Output training matrix of size N x 1
    R: int
        Hidden layer size
    eta: float
        Learning rate
    lam: float
        Regularizer
    stop: int
        Number of training epochs to run
    test_X: ndarray
        Input test matrix of size N x D
    test_Y: ndarray
        Output test matrix of size N x 1
    early_stop (optional): boolean
        Whether early stopping should be implemented

    Returns
    -------
    Multiple ndarrays of results to be used in plots
    """
    N, D = X.shape

    w0 = np.random.normal(size=(D, R))
    w1 = np.random.normal(size=(R, 1))

    bias1 = np.random.normal(size=(1, R))
    bias2 = np.random.normal(size=(1, 1))

    l1_error_list = []
    l2_error_list = []
    l2_test_error_list = []
    test_accuracy_list = []
    train_accuracy_list = []
    train_cross_entropy = []
    test_cross_entropy = []

    l2_delta_list = []
    l1_delta_list = []
    prev_i = 0
    i = 0
    run = False
    flag = False
    min_index = 0
    prev_min_index = 0

    w1_list = []
    w0_list = []


    while not flag:
        z1 = np.add(np.dot(X, w0), bias1)
        l1 = relufn(z1)
        z2 = np.add(np.dot(l1, w1), bias2)
        l2 = sigmoid(z2)

        z1_test = np.add(np.dot(test_X, w0), bias1)
        l1_test = relufn(z1_test)
        z2_test = np.add(np.dot(l1_test, w1), bias2)
        l2_test = sigmoid(z2_test)


        l2_test_converted = convert_to_binary(l2_test)
        l2_converted = convert_to_binary(l2)

        l2_test_error_list += [1 - accuracy_score(test_Y, l2_test_converted)]
        l2_error_list += [1 - accuracy_score(Y, l2_converted)]

        test_accuracy_list += [accuracy_score(test_Y, l2_test_converted)]
        train_accuracy_list += [accuracy_score(Y, l2_converted)]

        train_cross_entropy += [log_loss(Y.astype('str'), l2_converted)]
        test_cross_entropy += [log_loss(test_Y.astype('str'), l2_test_converted)]

        l2_test_error = l2_test - test_Y
        l2_error = l2 - Y
        deriv_sig = sigmoid(l2, True)
        # print(l2_error)

        l1_error = np.dot(np.multiply(l2_error, deriv_sig), w1.T)
        deriv_relu = relufn(l1, True)
        

        l2_delta = np.dot(l1.T, np.multiply(l2_error, deriv_sig))
        l1_delta = np.dot(X.T, np.multiply(l1_error, deriv_relu))

        l2_delta += lam * w1
        l1_delta += lam * w0

        w1 -= eta * l2_delta
        w0 -= eta * l1_delta


        
        # w1 = np.subtract(regularized_w1, (np.dot(l1.T, l2_delta)))
        # w0 = np.subtract(regularized_w0, (np.dot(X.T, l1_delta)))
        # print(l2_delta.shape)
        # print(bias1.shape)
        # print(l1_delta.shape)
        # print(l2_delta.shape)


        bias2 -= eta * np.sum(np.multiply(l2_error, deriv_sig))
        bias1 -= eta * np.sum(np.multiply(l1_error, deriv_relu))
        # w1 += np.dot(l1.T, l2_delta)
        # w0 += np.dot(X.T, l1_delta)
        # print("Type of l1: " + str(type(l1)))
        # print("Type of l2: " + str(type(l1)))
        # print("Type of l1_delta: " + str(type(l1_delta)))
        # print("Type of l2_delta: " + str(type(l2_delta)))
        # print("Type of l1_error: " + str(type(l1_error)))
        # print("Type of l2_error: " + str(type(l2_error)))
        # print("Type of w1: " + str(type(w1)))
        # print("Type of w0: " + str(type(w1)))
        # print("Type of bias1: " + str(type(bias1)))
        # print("Type of bias2: " + str(type(bias2)))

        w1_list += [np.mean(np.abs(w1))]
        w0_list += [np.mean(np.abs(w0))]

        if i - prev_i == 1000:
            print("Running... i = ", i, flush=True)
            # print(l1)
            # print(l2)
            # print(l2_converted)
            # print(bias1)
            # print(bias2)
            prev_i = i
            min_val = min(l2_test_error_list[(prev_min_index + 1):])
            prev_min_index = min_index
            min_index = l2_test_error_list.index(min_val)

            if abs(l2_test_error_list[prev_min_index] - min_val) < THRESHOLD:
                run = True 

        i += 1
        if not early_stop:
            flag = (i > stop)

        if early_stop and i - prev_i == 1000:
            flag = run
    print("Finished run with eta = ", eta, " and lam = ", lam, flush=True)

    return train_accuracy_list, test_accuracy_list, l2_delta_list, w1_list, w0_list, l2_error_list, l2_test_error_list, i, test_cross_entropy, train_cross_entropy

def create_io(size, bound):
    """ Create IO matrices using
    Parameters
    ----------
    size: int
        Size of input matrix
    bound:
        Upper bound of random calculation

    Returns
    -------
    Input ndarray of N x D and output ndarray of N x 1
    """
    X = bound * np.random.random((size, 3))

    Y = np.zeros((size, 1))
    for i in range(size):
        vals = X[i]
        sum_vals = 0
        for val in vals:
            sum_vals += math.floor(val)
        Y[i] = sum_vals % 2
    
    return X, Y

def create_data_plot(X, Y, dim_3=False):
    """ Create scatter plot in 2d or 3d """
    N, D = X.shape
    num_zeros = 0
    num_ones = 0
    ind0 = 0
    ind1 = 0
    y0 = []
    y1 = []

    if not dim_3:
        colors = "rb"
        for j in range(2):
            xval = [X[i, 0] for i in range(N)
                    if Y[i,0] == j]
            yval = [X[i, 1] for i in range(N)
                    if Y[i,0] == j]
            print(len(xval))
            print(len(yval))
            pyplt.plot(xval, yval, colors[j] + "o")
        pyplt.show()

        return
    else:
        for i in range(N):
            if Y[i, 0] == 0:
                y0 += [Y[i, 0]]
                num_zeros += 1
            elif Y[i, 0] == 1:
                y1 += [Y[i, 0]]
                num_ones += 1

        x0 = np.zeros((num_zeros, 3))
        x1 = np.zeros((num_ones, 3))

        for i in range(N):
            if Y[i, 0] == 0:
                x0[ind0] = X[i]
                ind0 += 1
            elif Y[i, 0] == 1:
                x1[ind1] = X[i]
                ind1 += 1
        
        fig = pyplt.figure(3)
        ax = fig.add_subplot(111, projection='3d')
        ax.scatter(x0[:,0], x0[:,1], x0[:,2], c='r', label="Even sum")
        ax.scatter(x1[:,0], x1[:,1], x1[:,2], c='g', label="Odd sum")
        pyplt.legend(loc="upper right")
        pyplt.show()

def create_plots(plot_list, stop, colors):
    """ Create graph results
    Parameters
    ----------
    plot_list: list
               List of plot values.
    stop: int
          Epochs ran
    colors: list
            List of graph colors
    """
    for i in range(len(plot_list)):
        eta, lam, train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy, R = plot_list[i]
        pyplt.figure(0)
        pyplt.plot(np.arange(0, stop, 1), test_accuracy, colors[i], label="Eta = " + str(eta) + ", Lam = " + str(lam) + ", R = " + str(R))
        pyplt.legend(loc="best")
        pyplt.figure(1)
        pyplt.plot(np.arange(0, stop, 1), train_accuracy, colors[i], label="Eta = " + str(eta) + ", Lam = " + str(lam) + ", R = " + str(R))
        pyplt.legend(loc="best")
        pyplt.figure(3)
        pyplt.plot(np.arange(0, stop, 1), w1, colors[i], label="Eta = " + str(eta) + ", Lam = " + str(lam) + ", R = " + str(R))
        pyplt.legend(loc="best")
        pyplt.figure(4)
        pyplt.plot(np.arange(0, stop, 1), w0, colors[i], label="Eta = " + str(eta) + ", Lam = " + str(lam) + ", R = " + str(R))
        pyplt.legend(loc="best")
        pyplt.figure(5)
        pyplt.plot(np.arange(0, stop, 1), l2_error, colors[i], label="Eta = " + str(eta) + ", Lam = " + str(lam) + ", R = " + str(R))
        pyplt.legend(loc="best")
        pyplt.figure(6)
        pyplt.plot(np.arange(0, stop, 1), l2_test_error, colors[i], label="Eta = " + str(eta) + ", Lam = " + str(lam) + ", R = " + str(R))
        pyplt.legend(loc="best")
        pyplt.figure(7)
        pyplt.plot(np.arange(0, stop, 1), test_cross_entropy, colors[i], label="Eta = " + str(eta) + ", Lam = " + str(lam) + ", R = " + str(R))
        pyplt.legend(loc="best")
        pyplt.figure(8)
        pyplt.plot(np.arange(0, stop, 1), train_cross_entropy, colors[i], label="Eta = " + str(eta) + ", Lam = " + str(lam) + ", R = " + str(R))
        pyplt.legend(loc="best")

    pyplt.figure(0)
    pyplt.title("Test Accuracy")
    pyplt.figure(1)
    pyplt.title("Train Accuracy")
    # pyplt.figure(2)
    # pyplt.title("Cross Entropy")
    pyplt.figure(3)
    pyplt.title("W1")
    pyplt.figure(4)
    pyplt.title("W0")
    pyplt.figure(5)
    pyplt.title("Train Error")
    pyplt.figure(6)
    pyplt.title("Test Error")
    pyplt.figure(7)
    pyplt.title("Train Cross Entropy")
    pyplt.figure(8)
    pyplt.title("Test Cross Entropy")
    pyplt.show()

def main():
    N = 600
    R = 50
    dataset = 2
    stop = 1000
    eta = 0.04
    lam = 0.1
    early_stop = False
    plot_list = []
    if len(sys.argv) <= 1 or sys.argv[1] != "--noinput":
        N = int(input("Enter size of input matrix: "))
        R = int(input("Enter the number of hidden neurons: "))
        dataset = int(input("Enter the dataset number: "))
        early_stop = int(input("Early stop (1/0): "))
        if not early_stop:
            stop = int(input("Enter the number of iterations: "))
        eta = float(input("Enter the learning rate: "))
        lam = float(input("Enter the regularizer: "))
    X = None
    Y = None
    testX = None
    testY = None
    # np.random.seed(5)
    if dataset == 1:
        print("Generating input...", flush=True)
        X, Y = create_io(N, 2)
        testX, testY = create_io(N, 2)
    elif dataset == 2:
        X, Y = create_io(N, 3)
        testX, testY = create_io(N, 3)
    else:
        print("Dataset number must be either a 1 or 2")
        exit(-1)

    

    print("Starting...", flush=True)
    colors = ['g-', 'r-', 'b-', 'y-']
    train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy = neural_net(X, Y, R, eta, lam, stop, testX, testY, early_stop)
    plot_list += [(eta, lam, train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy, R)]

    if len(sys.argv) > 1 and sys.argv[1] == "--noinput":
        eta = 0.0007
        lam = 0.1
        R = 20
        train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy = neural_net(X, Y, R, eta, lam, stop, testX, testY, early_stop)
        plot_list += [(eta, lam, train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy, R)]
        eta = 0.0005
        lam = 0.5
        R = 40
        train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy = neural_net(X, Y, R, eta, lam, stop, testX, testY, early_stop)
        plot_list += [(eta, lam, train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy, R)]
        eta = 0.0004
        lam = 0.1
        R = 10
        train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy = neural_net(X, Y, R, eta, lam, stop, testX, testY, early_stop)
        plot_list += [(eta, lam, train_accuracy, test_accuracy, l2_delta, w1, w0, l2_error, l2_test_error, stop, test_cross_entropy, train_cross_entropy, R)]


    create_plots(plot_list, stop, colors)

if __name__ == "__main__":
    main()
