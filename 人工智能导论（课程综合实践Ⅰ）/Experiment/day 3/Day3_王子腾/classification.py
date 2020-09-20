import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
# Parameters
learning_rate = 0.01
training_epochs = 1000
display_step = 50
# Training Data
x0=[3.3,4.4,5.5,6.71,6.93,4.168,9.779,6.182,\
   7.59,2.167,7.042,10.791,5.313,7.997,5.654,9.27,3.1]
y0=[1.7,2.76,2.09,3.19,1.694,1.573,3.366,2.596,\
   2.53,1.221,2.827,3.465,1.65,2.904,2.42,2.94,1.3]
l0=[1,1,1,1,0,1,0,1,0,1,1,0,0,1,1,0,1]
# Testing Data
x1=[6.83, 4.668, 8.9, 7.91, 5.7, 8.7, 3.1, 2.1]
y1=[1.84, 2.273, 3.2, 2.831, 2.92, 3.24, 1.35, 1.03]
l1=[0, 1, 1, 0, 1, 1, 1, 1]

# data illustration
x0=np.asarray(x0).reshape(-1,1)
y0=np.asarray(y0).reshape(-1,1)         #将x0，y0转换为列向量
l0=np.asarray(l0).reshape(-1)
x = np.hstack((x0,y0))                  #将x,y统一放入x中，x为（17,2）型

x1 = np.array(x1).reshape(-1,1)
y1 = np.array(y1).reshape(-1,1)
l1 = np.array(l1).reshape(-1)
X = np.hstack((x1,y1))                  #与x0,y0,l0采取同样操作

pos_index=np.where(l0==1)
neg_index=np.where(l0==0)
plt.subplot(1, 2, 1)                    #l0对应1的点用红点表示，对应0的点用蓝点表示
plt.title('train data label')
plt.plot(x0[pos_index], y0[pos_index], 'ro')
plt.plot(x0[neg_index], y0[neg_index], 'bo')
plt.subplot(1,2,2)
plt.title('test data')
plt.plot(x1,y1,'ko')
plt.show()                              #画出训练数据和测试数据的图像

# train process
# 1.Graph Input
x_input=tf.placeholder(tf.float32,(None,2))
l_input=tf.placeholder(tf.int32,(None,))
# 2.Set Model Weight
w=tf.Variable(np.random.rand(2,2),dtype=tf.float32)
b=tf.Variable(np.random.rand(2,),dtype=tf.float32)
# 3.Construct Logistic Model
pred=tf.add(tf.matmul(x_input,w),b)
loss=tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits=pred, labels=l_input))
optim=tf.train.GradientDescentOptimizer(learning_rate).minimize(loss)
# 4.session()
with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    sess.run(tf.local_variables_initializer())
    #start train model
    for epoch in range(training_epochs):
        pred_l,l,_=sess.run([pred,loss,optim],feed_dict={x_input:x ,l_input:l0})        #将整合好的x,l0传入sess.run
        # Display logs per epoch step
        if (epoch + 1) % display_step == 0:
            print("Epoch {} cost: {}".format((epoch + 1),l))
    print("Optimization Finished!")
    final_w=sess.run(w)
    final_b=sess.run(b)

# plot train result
#referring: np.where
plt.subplot(2,1,1)
plt.title('original train data')
pos_index=np.where(l0==1)
neg_index=np.where(l0==0)
plt.plot(x0[pos_index], y0[pos_index], 'ro')
plt.plot(x0[neg_index], y0[neg_index], 'bo')
#plt.show()在最后show出来

plt.subplot(2,1,2)
plt.title('train data result')
pred_l0=np.dot(x,final_w)+final_b
label_l0=np.argmax(pred_l0,axis=1)
pos_index=np.where(label_l0==1)
neg_index=np.where(label_l0==0)
plt.plot(x0[pos_index], y0[pos_index], 'r^')
plt.plot(x0[neg_index], y0[neg_index], 'b^')
plt.show()

# test process
plt.subplot(2,1,1)
plt.title('original test data')
pos_index=np.where(l1==1)
neg_index=np.where(l1==0)
plt.plot(x1[pos_index], y1[pos_index], 'ro')
plt.plot(x1[neg_index], y1[neg_index], 'bo')
#plt.show() 多开一图 无法同时展示

plt.subplot(2,1,2)
plt.title('test result')
pred_l1=np.dot(X,final_w)+final_b
label_l1=np.argmax(pred_l1,axis=1)
pos_index=np.where(label_l1==1)
neg_index=np.where(label_l1==0)
plt.plot(x1[pos_index], y1[pos_index], 'r^')
plt.plot(x1[neg_index], y1[neg_index], 'b^')
plt.show()
# plot test result