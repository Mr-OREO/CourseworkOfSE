# Modified version of
# DQN implementation by Tejas Kulkarni found at
# https://github.com/mrkulk/deepQN_tensorflow

import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt



#使用DQN算法
class DoubleDQN:
    def __init__(self, params):
        self.params = params               # 传入常数（from pacman_Agents）
        self.network_name = 'DDQnet'         # network的名字
        self.sess = tf.Session()           # sess赋类

        self.x = tf.placeholder('float', [None, params['width'], params['height'], 6], name=self.network_name + '_x')
        self.x_ = tf.placeholder('float', [None, params['width'], params['height'], 6], name=self.network_name + '_x_')
        self.q_t = tf.placeholder('float', [None], name=self.network_name + '_q_t')
        # quality target
        self.actions = tf.placeholder("float", [None, 4], name=self.network_name + '_actions')
        # action的选择
        self.rewards = tf.placeholder("float", [None], name=self.network_name + '_rewards')
        # action对应得到的rewards
        self.terminals = tf.placeholder("float", [None], name=self.network_name + '_terminals')
        # 是否终结 1表示终结，0表示未终结

    # def _build_net(self,params):
        ##########################################################################
        # 第一种network：一层CNN，一层MLP，一层输出
        def build_layers(x,names):
            # Layer 1 (Convolutional)
            layer_name = 'conv2' ; size = 3 ; channels = 6 ; filters = 16 ; stride = 1
            self.w2 = tf.Variable(tf.random_normal([size,size,channels,filters], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights',collections=names)
            self.b2 = tf.Variable(tf.constant(0.1, shape=[filters]),name=self.network_name + '_'+layer_name+'_biases',collections=names)
            self.c2 = tf.nn.conv2d(x, self.w2, strides=[1, stride, stride, 1], padding='SAME',name=self.network_name + '_'+layer_name+'_convs')
            self.o2 = tf.nn.relu(tf.add(self.c2,self.b2),name=self.network_name + '_'+layer_name+'_activations')
            o2_shape = self.o2.get_shape().as_list()

            # Layer 2 (Fully connected)
            layer_name = 'fc3' ; hiddens = 256 ; dim = o2_shape[1]*o2_shape[2]*o2_shape[3]
            self.o2_flat = tf.reshape(self.o2, [-1,dim],name=self.network_name + '_'+layer_name+'_input_flat')
            self.w3 = tf.Variable(tf.random_normal([dim,hiddens], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights',collections=names)
            self.b3 = tf.Variable(tf.constant(0.1, shape=[hiddens]),name=self.network_name + '_'+layer_name+'_biases',collections=names)
            self.ip3 = tf.add(tf.matmul(self.o2_flat,self.w3),self.b3,name=self.network_name + '_'+layer_name+'_ips')
            self.o3 = tf.nn.relu(self.ip3,name=self.network_name + '_'+layer_name+'_activations')

            # Layer 3 output
            layer_name = 'fc4' ; hiddens = 4 ; dim = 256
            self.w4 = tf.Variable(tf.random_normal([dim,hiddens], stddev=0.01),name=self.network_name + '_'+layer_name+'_weights',collections=names)
            self.b4 = tf.Variable(tf.constant(0.1, shape=[hiddens]),name=self.network_name + '_'+layer_name+'_biases',collections=names)
            self.y = tf.add(tf.matmul(self.o3,self.w4),self.b4,name=self.network_name + '_'+layer_name+'_outputs')

            return self.y

        ###################   build eval net     ##############################################
        with tf.variable_scope('eval_net'):
            self.y_eval= build_layers(x=self.x,names=['eval_net_params', tf.GraphKeys.GLOBAL_VARIABLES])
            self.y = self.y_eval
            #Q,Cost,Optimizer
            self.discount = tf.constant(self.params['discount'])  #1-terminal：判断是否为terminal step；discount：参数;
            # # 计算Q_target(使用贝尔曼公式计算得到的理论值）
            self.yj = tf.add(self.rewards, tf.multiply(1.0-self.terminals, tf.multiply(self.discount, self.q_t)))
            self.y_eval_action = tf.reduce_sum(tf.multiply(self.y_eval, self.actions),reduction_indices=1)
        with tf.variable_scope('loss'):
        # 计算loss（cost），用MSE
            self.cost = tf.reduce_sum(tf.pow(tf.subtract(self.yj, self.y_eval_action), 2))

        with tf.variable_scope('optim'):
        # 为global_step开新变量寄存
            if self.params['load_file'] is not None:
                self.global_step = tf.Variable(int(self.params['load_file'].split('_')[-1]), name='global_step',
                                                   trainable=False)
            else:
                self.global_step = tf.Variable(0, name='global_step', trainable=False)

                #Adam方法进行优化
            self.optim = tf.train.AdamOptimizer(self.params['lr']).minimize(self.cost, global_step=self.global_step)
        ###################   build target net   #############################################
        with tf.variable_scope('target_net'):
            c_names = ['target_net_params', tf.GraphKeys.GLOBAL_VARIABLES]
            self.y_next= build_layers(self.x_,c_names)
            self.y_next_action =  tf.reduce_sum(tf.multiply(self.y_next, self.actions),reduction_indices=1)

        self.saver = tf.train.Saver(max_to_keep=0)
        # tf.reset_default_graph()
        self.sess.run(tf.global_variables_initializer())  # 再次初始化
        # 储存神经网络变量
        t_params = tf.get_collection('target_net_params')
        e_params = tf.get_collection('eval_net_params')
        self.replace_target_op = [tf.assign(t, e) for t, e in zip(t_params, e_params)]
        if self.params['load_file'] is not None:
            print('Loading checkpoint...')
            self.saver.restore(self.sess,self.params['load_file'])
    # DDQN主体
    def train(self,bat_s,bat_a,bat_t,bat_n,bat_r,cnt):
        if cnt % 100 ==0:
            self.sess.run(self.replace_target_op)

        feed_dict={self.x: bat_n,self.x_: bat_n,self.q_t: np.zeros(bat_n.shape[0]), self.actions: bat_a, self.terminals:bat_t, self.rewards: bat_r}
        # 运行Network
        q_next,q_eval4next= self.sess.run([self.y_next,self.y_eval],feed_dict=feed_dict)     #32*4 （batch_size,hiddens)
        batch_index = np.arange(self.params['batch_size'], dtype=np.int32)
        max_act4next = np.argmax(q_eval4next, axis=1)  # the action that brings the highest value is evaluated by q_eval
        selected_q_next = q_next[batch_index, max_act4next]  # Double DQN, select q_next depending on above actions

        #传入 bat_s:state(observation);q_t:target quality；bat_a:action;
        feed_dict={self.x: bat_s,self.x_: bat_s,self.q_t:selected_q_next , self.actions: bat_a, self.terminals:bat_t, self.rewards: bat_r}
        _,cnt,cost = self.sess.run([self.optim, self.global_step,self.cost],feed_dict=feed_dict)
        return cnt, cost

    def save_ckpt(self,filename):
        self.saver.save(self.sess, filename)
