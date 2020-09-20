import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
#%matplotlib inline
# Parameters
learning_rate = 0.01
training_epochs = 1000
display_step = 50
# Training Data
x0=[3.3,4.4,5.5,6.71,6.93,4.168,9.779,6.182,\
   7.59,2.167,7.042,10.791,5.313,7.997,5.654,9.27,3.1]
y0=[1.7,2.76,2.09,3.19,1.694,1.573,3.366,2.596,\
   2.53,1.221,2.827,3.465,1.65,2.904,2.42,2.94,1.3]
# Testing Data
x1=[6.83, 4.668, 8.9, 7.91, 5.7, 8.7, 3.1, 2.1]
y1=[1.84, 2.273, 3.2, 2.831, 2.92, 3.24, 1.35, 1.03]
# # data illustration
plt.subplot(1,2,1)
plt.title('Original train data')
plt.plot(x0, y0, 'go')
plt.subplot(1,2,2)
plt.title('Testing data')
plt.plot(x1, y1, 'bo')
plt.show()
# train process
# step1 Graph Input
# referring: tf.placeholder

x0=np.array(x0).reshape(-1,1)
y0=np.array(y0).reshape(-1,1)
x_input=tf.placeholder(tf.float32,(None,1))
y_input=tf.placeholder(tf.float32,(None,1))
# step2 Set model weights
# referring: tf.Variable
w=tf.Variable(np.random.rand(1,1),dtype=tf.float32)
b=tf.Variable(np.random.rand(1,),dtype=tf.float32)
# step3 Construct a logistic model
# referring: y=wx+b
pred=tf.add(tf.matmul(x_input,w),b)
# step4 Construct (Mean squared) loss
# referring: tf.reduce_mean tf.reduce_sum
loss=tf.reduce_mean(tf.pow(pred-y_input,2))
# step5 Declare optimizer method
# referring: tf.train.GradientDescentOptimizer tf.train.AdamOptimizer
optim=tf.train.GradientDescentOptimizer(learning_rate).minimize(loss)
# step6 Create session, initial variables, feed data and print result
# referring: tf.Session() Sess.run()\
# tf.global_variables_initializer() tf.local_variables_initializer()
sess=tf.Session()
sess.run(tf.global_variables_initializer())
sess.run(tf.local_variables_initializer())
#start train model
for epoch in range(training_epochs):
    pred_y,l,_=sess.run([pred,loss,optim],feed_dict={x_input:x0,y_input:y0})
# Display logs per epoch step
    if (epoch + 1) % display_step == 0:
        print("Epoch {:4d} cost: {:.9f}".format((epoch + 1),l))
print("Optimization Finished!")
final_w=np.squeeze(sess.run(w))
final_b=np.squeeze(sess.run(b))
print("Training modal w: {:.5f}, b: {:.5f}".format(final_w,final_b))
# display the fitting line
# plot the trained model point(input x and output y0')
pred_y = final_w*x0+final_b
plt.plot(x0, y0, 'ro', label='Original data')
plt.plot(x0, pred_y, 'g-',label='Fitted line')
plt.xlabel('x axis label')
plt.ylabel('y axis label')
plt.title('Trained data and fitted line')
plt.legend(['Oringinal data', 'Fitted line'])
plt.show()
# test process
# same method as train above to get predict y
pred_y1 = final_w*x1+final_b
# display the test result

plt.plot(x1, y1, 'bo', label='Testing data')
plt.plot(x1, pred_y1, 'g-',label='Fitted line')
plt.xlabel('x axis label')
plt.ylabel('y axis label')
plt.title('Tested data and fitted line')
plt.legend(['Oringinal data', 'Fitted line'])
plt.show()