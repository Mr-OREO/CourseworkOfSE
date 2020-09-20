# Modified version of
# DQN implementation by Tejas Kulkarni found at
# https://github.com/mrkulk/deepQN_tensorflow

import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

#使用DQN算法
class DQN:
    def __init__(self, params):
        self.params = params               # 传入常数（from pacman_Agents）
        self.network_name = 'qnet'         # network的名字
        self.sess = tf.Session()           # sess赋类
        self.x = tf.placeholder('float', [None, params['width'],params['height'], 6],name=self.network_name + '_x')
                                           # state
        self.q_t = tf.placeholder('float', [None], name=self.network_name + '_q_t')
                                           # quality target
        self.actions = tf.placeholder("float", [None, 4], name=self.network_name + '_actions')
                                           # action的选择
        self.rewards = tf.placeholder("float", [None], name=self.network_name + '_rewards')
                                           # action对应得到的rewards
        self.terminals = tf.placeholder("float", [None], name=self.network_name + '_terminals')
                                           # 是否终结 1表示终结，0表示未终结
        def build_layers(x):
            ##########################################################################
            # 第一种network：一层CNN，一层MLP，一层输出
            # Layer 1 (Convolutional)
            layer_name = 'conv2' ; size = 3 ; channels = 6 ; filters = 16 ; stride = 1
            self.w2 = tf.Variable(tf.random_normal([size,size,channels,filters], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights')
            self.b2 = tf.Variable(tf.constant(0.1, shape=[filters]),name=self.network_name + '_'+layer_name+'_biases')
            self.c2 = tf.nn.conv2d(x, self.w2, strides=[1, stride, stride, 1], padding='SAME',name=self.network_name + '_'+layer_name+'_convs')
            self.o2 = tf.nn.relu(tf.add(self.c2,self.b2),name=self.network_name + '_'+layer_name+'_activations')
            o2_shape = self.o2.get_shape().as_list()

            # Layer 2 (Fully connected)
            layer_name = 'fc3' ; hiddens = 256 ; dim = o2_shape[1]*o2_shape[2]*o2_shape[3]
            self.o2_flat = tf.reshape(self.o2, [-1,dim],name=self.network_name + '_'+layer_name+'_input_flat')
            self.w3 = tf.Variable(tf.random_normal([dim,hiddens], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights')
            self.b3 = tf.Variable(tf.constant(0.1, shape=[hiddens]),name=self.network_name + '_'+layer_name+'_biases')
            self.ip3 = tf.add(tf.matmul(self.o2_flat,self.w3),self.b3,name=self.network_name + '_'+layer_name+'_ips')
            self.o3 = tf.nn.relu(self.ip3,name=self.network_name + '_'+layer_name+'_activations')

            # Layer 3 output
            layer_name = 'fc4' ; hiddens = 4 ; dim = 256
            self.w4 = tf.Variable(tf.random_normal([dim,hiddens], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights')
            self.b4 = tf.Variable(tf.constant(0.1, shape=[hiddens]),name=self.network_name + '_'+layer_name+'_biases')
            self.y = tf.add(tf.matmul(self.o3,self.w4),self.b4,name=self.network_name + '_'+layer_name+'_outputs')
            return self.y
            ##########################################################################
            # 第二种network：两层CNN，一层MLP，一层输出
            # Layer 1 (Convolutional)
            # layer_name = 'conv1' ; size = 3 ; channels = 6 ; filters = 16 ; stride = 1
            # self.w1 = tf.Variable(tf.random_normal([size,size,channels,filters], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights')
            # self.b1 = tf.Variable(tf.constant(0.1, shape=[filters]),name=self.network_name + '_'+layer_name+'_biases')
            # self.c1 = tf.nn.conv2d(x, self.w1, strides=[1, stride, stride, 1], padding='SAME',name=self.network_name + '_'+layer_name+'_convs')
            # self.o1 = tf.nn.relu(tf.add(self.c1,self.b1),name=self.network_name + '_'+layer_name+'_activations')

            # Layer 2 (Convolutional)
            # layer_name = 'conv2' ; size = 3 ; channels = 6 ; filters = 16 ; stride = 1
            # self.w2 = tf.Variable(tf.random_normal([size,size,channels,filters], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights')
            # self.b2 = tf.Variable(tf.constant(0.1, shape=[filters]),name=self.network_name + '_'+layer_name+'_biases')
            # self.c2 = tf.nn.conv2d(self.o1, self.w2, strides=[1, stride, stride, 1], padding='SAME',name=self.network_name + '_'+layer_name+'_convs')
            # self.o2 = tf.nn.relu(tf.add(self.c2,self.b2),name=self.network_name + '_'+layer_name+'_activations')
            # print("o2_shape.shape:{}", self.o2.get_shape())
            # o2_shape = self.o2.get_shape().as_list()
            # print(o2_shape)

            # Layer 3 (Fully connected)
            # layer_name = 'fc1'
            # hiddens = 256
            # dim = o2_shape[1] * o2_shape[2] * o2_shape[3]
            # self.x_flat = tf.reshape(self.o2, [-1, dim], name=self.network_name + '_' + layer_name + '_input_flat')
            # self.w3 = tf.Variable(tf.random_normal([dim, hiddens], stddev=0.01),
            #                         name=self.network_name + '_' + layer_name + '_weights')
            # self.b3 = tf.Variable(tf.constant(0.1, shape=[hiddens]), name=self.network_name + '_' + layer_name + '_biases')
            # self.ip3 = tf.add(tf.matmul(self.x_flat, self.w3), self.b3, name=self.network_name + '_' + layer_name + '_ips')
            # self.o3 = tf.nn.relu(self.ip3, name=self.network_name + '_' + layer_name + '_activations')

            # Layer 3 (Fully connected)
            # layer_name = 'fc3' ; hiddens = 256 ; dim = o2_shape[1]*o2_shape[2]*o2_shape[3]
            # # print(dim)
            # self.o2_flat = tf.reshape(self.o2, [-1,dim],name=self.network_name + '_'+layer_name+'_input_flat')
            # self.w3 = tf.Variable(tf.random_normal([dim,hiddens], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights')
            # self.b3 = tf.Variable(tf.constant(0.1, shape=[hiddens]),name=self.network_name + '_'+layer_name+'_biases')
            # self.ip3 = tf.add(tf.matmul(self.o2_flat,self.w3),self.b3,name=self.network_name + '_'+layer_name+'_ips')
            # self.o3 = tf.nn.relu(self.ip3,name=self.network_name + '_'+layer_name+'_activations')
            #
            # Layer 4 output
            # layer_name = 'fc4' ; hiddens = 4 ; dim = 256
            # self.w4 = tf.Variable(tf.random_normal([dim,hiddens], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights')
            # self.b4 = tf.Variable(tf.constant(0.1, shape=[hiddens]),name=self.network_name + '_'+layer_name+'_biases')
            # self.y = tf.add(tf.matmul(self.o3,self.w4),self.b4,name=self.network_name + '_'+layer_name+'_outputs')
            # return self.y
            ##########################################################################
            # 第三种network：
            # 这里设置两层MLP，包括一层隐藏层与一层输出层；origin代码为四层：两层卷积、一层MLP、一层输出，在考虑运算速度好进行化简
            # Layer 1 (Fully connected)
            # x_shape = self.x.get_shape().as_list()
            # layer_name = 'fc1'
            # hiddens = 256
            # dim = x_shape[1] * x_shape[2] * x_shape[3]
            # self.x_flat = tf.reshape(x, [-1, dim], name=self.network_name + '_' + layer_name + '_input_flat')
            # self.w3 = tf.Variable(tf.random_normal([dim, hiddens], stddev=0.01),
            #                         name=self.network_name + '_' + layer_name + '_weights')
            # self.b3 = tf.Variable(tf.constant(0.1, shape=[hiddens]), name=self.network_name + '_' + layer_name + '_biases')
            # self.ip3 = tf.add(tf.matmul(self.x_flat, self.w3), self.b3, name=self.network_name + '_' + layer_name + '_ips')
            # self.o3 = tf.nn.relu(self.ip3, name=self.network_name + '_' + layer_name + '_activations')
            # Layer 2 output
            # layer_name = 'fc4';
            # hiddens = 4;
            # dim = 256
            # self.w4 = tf.Variable(tf.random_normal([dim, hiddens], stddev=0.01),
            #                       name=self.network_name + '_' + layer_name + '_weights')
            # self.b4 = tf.Variable(tf.constant(0.1, shape=[hiddens]), name=self.network_name + '_' + layer_name + '_biases')
            # self.y = tf.add(tf.matmul(self.o3, self.w4), self.b4, name=self.network_name + '_' + layer_name + '_outputs')
            # return self.y
            #########################################################################################

        #Q,Cost,Optimizer
        self.discount = tf.constant(self.params['discount'])  #1-terminal：判断是否为terminal step；discount：参数;
        # 计算Q_target(使用贝尔曼公式计算得到的理论值）
        self.yj = tf.add(self.rewards, tf.multiply(1.0-self.terminals, tf.multiply(self.discount, self.q_t)))

        # 神经网络计算得到的预测值
        self.y = build_layers(x=self.x)
        self.Q_pred = tf.reduce_sum(tf.multiply(self.y,self.actions), reduction_indices=1)
        #print(self.Q_pred.shape)
        # 计算loss（cost），用MSE
        self.cost = tf.reduce_sum(tf.pow(tf.subtract(self.yj, self.Q_pred), 2))

        # 为global_step开新变量寄存
        if self.params['load_file'] is not None:
            self.global_step = tf.Variable(int(self.params['load_file'].split('_')[-1]),name='global_step', trainable=False)
        else:
            self.global_step = tf.Variable(0, name='global_step', trainable=False)

        #Adam方法进行优化
        self.optim = tf.train.AdamOptimizer(self.params['lr']).minimize(self.cost, global_step=self.global_step)
        # 不储存sess的变量（max_to_keep=0 一个都不保留）
        self.saver = tf.train.Saver(max_to_keep=0)

        # sess初始化
        self.sess.run(tf.global_variables_initializer())

        if self.params['load_file'] is not None:
            print('Loading checkpoint...')
            self.saver.restore(self.sess,self.params['load_file'])

    # DQN主体
    def train(self,bat_s,bat_a,bat_t,bat_n,bat_r,cnt):
        # 通过next_step（bat_n）传入神经网络，得到q_t（quality target），用于计算cost（在同一神经网络中）
        feed_dict={self.x: bat_n, self.q_t: np.zeros(bat_n.shape[0]), self.actions: bat_a, self.terminals:bat_t, self.rewards: bat_r}
        # 运行Network
        q_t = self.sess.run(self.y,feed_dict=feed_dict)  #32*4 （batch_size,hiddens)

        # 取每行最大
        q_t = np.amax(q_t, axis=1)
        #print(q_t)
        #传入 bat_s:state(observation);q_t:target quality；bat_a:action;
        feed_dict={self.x: bat_s, self.q_t: q_t, self.actions: bat_a, self.terminals:bat_t, self.rewards: bat_r}
        _,cnt,cost = self.sess.run([self.optim, self.global_step,self.cost],feed_dict=feed_dict)
            #返回cnt：次数；cost：损失值
        return cnt, cost

    def save_ckpt(self,filename):
        self.saver.save(self.sess, filename)
