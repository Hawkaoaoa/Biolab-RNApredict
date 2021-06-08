#!/usr/bin/env python
# coding: utf-8

# In[16]:


import matplotlib.pyplot as plt

with open("E:/pythonProject1/Test/Gene_iteration.txt",'r') as f:
    result = []
    for line in f.readlines():
        result.append(int(line.strip()))

num = len(result)
itera = list(range(1,num+1))

fig, ax = plt.subplots()
ax.set(xlim=[1,250],title="Gene_iteration", ylabel="Max_fit_score",xlabel="Iteration,N")
ax.plot(itera, result, label="trend")

ax.legend()


# In[ ]:




