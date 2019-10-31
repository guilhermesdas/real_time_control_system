
# importing the required module 
import matplotlib.pyplot as plt 

###########################################################

# init list of values and index's
k_index = 0
v_index = 1
w_index = 2
x_index = 3
y_index = 4
o_index = 5

# get values from file
def getValues(filename):
    values = [ [], [], [], [], [], [] ]
    f = open(filename,"r")
    lines = f.readlines()
    for line in lines:
        line_list = list(map(float,line.split("\t")))
        for i in range(len(line_list)):
            values[i].append(line_list[i])
    return values

###################### SCRIPT ############################

values = getValues("values.txt")

# plotting X Y
plt.subplot(2,2,1)
plt.plot(values[x_index], values[y_index]) 
plt.xlabel('x') # naming the x axis
plt.ylabel('y ') # naming the y axis    
#plt.title('X Y Trajetory') # giving a title to my graph 

# plotting the points  
plt.subplot(2,2,2)
plt.plot(values[k_index],values[v_index]) 
plt.xlabel('k') # naming the x axis
plt.ylabel('v') # naming the y axis    
#plt.title('Linear Velocity x k') # giving a title to my graph 

# plotting the points  
plt.subplot(2,2,3)
plt.plot(values[k_index],values[w_index]) 
plt.xlabel('k') # naming the x axis
plt.ylabel('w') # naming the y axis    
#plt.title('Angle Velocity x k') # giving a title to my graph

# plotting the points  
plt.subplot(2,2,4)
plt.plot(values[k_index],values[o_index]) 
plt.xlabel('k') # naming the x axis
plt.ylabel('angle') # naming the y axis    
#plt.title('Angle x k',loc='center') # giving a title to my graph 

# function to show the plot 
plt.show() 
