import matplotlib.pyplot as plt

input = open('Tue_16_Jul_2019_19_49_38-l-5-m-10-x-4000.log', 'r')
input_ = open('Tue_16_Jul_2019_20_19_03-l-5-m-10-x-4000.log', 'r')

rangeUpdateTime = [0.0]
rangeUpdateTime_ = [0.0]

for line in input:
    line = line.split()
    if '#' in line :
        rangeUpdateTime.append(float(line[19]))
for line_ in input_:
    line_ = line_.split()
    if '#' in line_ :
        rangeUpdateTime_.append(float(line_[19]))

plt.figure('frame time')
plt.subplot(211)
plt.plot(rangeUpdateTime, '.r',)
plt.grid(True)
plt.subplot(212)
plt.plot(rangeUpdateTime_,'.b')
plt.grid(True)
plt.show()