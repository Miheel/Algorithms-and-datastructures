import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize as opt

def func(x, a, b, c):
     return x ** 2 * a + b * x + c

def subplot_specs(file, search_funk_name):

    data = np.genfromtxt(file, delimiter=",")
    Tdata = np.transpose(data)
    xpoints = np.array(Tdata[0])
    ypoints = np.array(Tdata[1])

    #plt.plot(xpoints, ypoints, label="data")
    plt.errorbar(xpoints, ypoints, Tdata[2], label="data")

                        #pcov
    optimizedParameters, _ = opt.curve_fit(func, xpoints, ypoints)
    plt.plot(xpoints, func(xpoints, *optimizedParameters), label="fit")

    plt.title(search_funk_name)

    plt.xlabel("N elements")
    plt.ylabel("Time in sec")
    plt.xlim(left=0)
    plt.legend()
    plt.grid()

#insertion
plt.subplot(2,2,1)
subplot_specs("sorting_data_points\insertion_random.cvs", "insertion sort random")

plt.subplot(2,2,2)
subplot_specs("sorting_data_points\insertion_falling.cvs", "insertion sort falling")

plt.subplot(2,2,3)
subplot_specs("sorting_data_points\insertion_growing.cvs", "insertion sort growing")

plt.subplot(2,2,4)
subplot_specs("sorting_data_points\insertion_constant.cvs", "insertion sort constant")

# mng = plt.get_current_fig_manager()
# mng.window.showMaximized()
plt.show()

#selection
plt.subplot(2,2,1)
subplot_specs("sorting_data_points\selection_random.cvs", "selection sort random")

plt.subplot(2,2,2)
subplot_specs("sorting_data_points\selection_falling.cvs", "selection sort falling")

plt.subplot(2,2,3)
subplot_specs("sorting_data_points\selection_growing.cvs", "selection sort growing")

plt.subplot(2,2,4)
subplot_specs("sorting_data_points\selection_constant.cvs", "selection sort constant")

# mng = plt.get_current_fig_manager()
# mng.window.showMaximized()
plt.show()

#quicksort left
plt.subplot(2,2,1)
subplot_specs("sorting_data_points\quicksortL_random.cvs", "quicksort left pivot sort random")

plt.subplot(2,2,2)
subplot_specs("sorting_data_points\quicksortL_falling.cvs", "quicksort left pivot sort falling")

plt.subplot(2,2,3)
subplot_specs("sorting_data_points\quicksortL_growing.cvs", "quicksort left pivot sort growing")

plt.subplot(2,2,4)
subplot_specs("sorting_data_points\quicksortL_constant.cvs", "quicksort left pivot sort constant")

# mng = plt.get_current_fig_manager()
# mng.window.showMaximized()
plt.show()

#quicksort mediam
plt.subplot(2,2,1)
subplot_specs("sorting_data_points\quicksortm_random.cvs", "quicksort median pivot sort random")

plt.subplot(2,2,2)
subplot_specs("sorting_data_points\quicksortm_falling.cvs", "quicksort median pivot sort falling")

plt.subplot(2,2,3)
subplot_specs("sorting_data_points\quicksortm_growing.cvs", "quicksort median pivot sort growing")

plt.subplot(2,2,4)
subplot_specs("sorting_data_points\quicksortm_constant.cvs", "quicksort median pivot sort constant")

# mng = plt.get_current_fig_manager()
# mng.window.showMaximized()
plt.show()

#std::sort
plt.subplot(2,2,1)
subplot_specs("sorting_data_points\stdsort_random.cvs", "std::sort sort random")

plt.subplot(2,2,2)
subplot_specs("sorting_data_points\stdsort_falling.cvs", "std::sort sort falling")

plt.subplot(2,2,3)
subplot_specs("sorting_data_points\stdsort_growing.cvs", "std::sort sort growing")

plt.subplot(2,2,4)
subplot_specs("sorting_data_points\stdsort_constant.cvs", "std::sort sort constant")

# mng = plt.get_current_fig_manager()
# mng.window.showMaximized()
plt.show()