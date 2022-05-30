import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize as opt

def func(x, a, b, c):
     return np.log(x) * a + b * x + c
     #return x ** 2 * a + b * x + c

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


#Searching
#Linear
plt.subplot(2,2,1)
subplot_specs("searching_data_points\\Lineas_search.csv", "Linear search")
#Binary
plt.subplot(2,2,2)
subplot_specs("searching_data_points\\binary_search.csv", "Binary search")
#Binary search tree
plt.subplot(2,2,3)
subplot_specs("searching_data_points\\bst_search.csv", "Binary search tree search")
#Hashtabel
plt.subplot(2,2,4)
subplot_specs("searching_data_points\\hashtable_search.csv", "Hashtabel search")

# mng = plt.get_current_fig_manager()
# mng.window.showMaximized()
plt.show()

# #Sorting
# #insertion
# plt.subplot(2,2,1)
# subplot_specs("sorting_data_points\insertion_random.csv", "insertion sort random")

# plt.subplot(2,2,2)
# subplot_specs("sorting_data_points\insertion_falling.csv", "insertion sort falling")

# plt.subplot(2,2,3)
# subplot_specs("sorting_data_points\insertion_growing.csv", "insertion sort growing")

# plt.subplot(2,2,4)
# subplot_specs("sorting_data_points\insertion_constant.csv", "insertion sort constant")

# # mng = plt.get_current_fig_manager()
# # mng.window.showMaximized()
# plt.show()

# #selection
# plt.subplot(2,2,1)
# subplot_specs("sorting_data_points\selection_random.csv", "selection sort random")

# plt.subplot(2,2,2)
# subplot_specs("sorting_data_points\selection_falling.csv", "selection sort falling")

# plt.subplot(2,2,3)
# subplot_specs("sorting_data_points\selection_growing.csv", "selection sort growing")

# plt.subplot(2,2,4)
# subplot_specs("sorting_data_points\selection_constant.csv", "selection sort constant")

# # mng = plt.get_current_fig_manager()
# # mng.window.showMaximized()
# plt.show()

# #quicksort left
# plt.subplot(2,2,1)
# subplot_specs("sorting_data_points\quicksortL_random.csv", "quicksort left pivot sort random")

# plt.subplot(2,2,2)
# subplot_specs("sorting_data_points\quicksortL_falling.csv", "quicksort left pivot sort falling")

# plt.subplot(2,2,3)
# subplot_specs("sorting_data_points\quicksortL_growing.csv", "quicksort left pivot sort growing")

# plt.subplot(2,2,4)
# subplot_specs("sorting_data_points\quicksortL_constant.csv", "quicksort left pivot sort constant")

# # mng = plt.get_current_fig_manager()
# # mng.window.showMaximized()
# plt.show()

# #quicksort mediam
# plt.subplot(2,2,1)
# subplot_specs("sorting_data_points\quicksortm_random.csv", "quicksort median pivot sort random")

# plt.subplot(2,2,2)
# subplot_specs("sorting_data_points\quicksortm_falling.csv", "quicksort median pivot sort falling")

# plt.subplot(2,2,3)
# subplot_specs("sorting_data_points\quicksortm_growing.csv", "quicksort median pivot sort growing")

# plt.subplot(2,2,4)
# subplot_specs("sorting_data_points\quicksortm_constant.csv", "quicksort median pivot sort constant")

# # mng = plt.get_current_fig_manager()
# # mng.window.showMaximized()
# plt.show()

# #std::sort
# plt.subplot(2,2,1)
# subplot_specs("sorting_data_points\stdsort_random.csv", "std::sort sort random")

# plt.subplot(2,2,2)
# subplot_specs("sorting_data_points\stdsort_falling.csv", "std::sort sort falling")

# plt.subplot(2,2,3)
# subplot_specs("sorting_data_points\stdsort_growing.csv", "std::sort sort growing")

# plt.subplot(2,2,4)
# subplot_specs("sorting_data_points\stdsort_constant.csv", "std::sort sort constant")

# # mng = plt.get_current_fig_manager()
# # mng.window.showMaximized()
# plt.show()