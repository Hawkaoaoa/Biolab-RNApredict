#!/usr/bin/env python
# coding: utf-8

# In[9]:


import matplotlib.pyplot as plt
import numpy as np

barWidth = 0.25
result = [0.244, 0.061, 0.031]
r1 = np.arange(len(result))

plt.bar(r1, result, width=barWidth, edgecolor='white',label='DATA' )

plt.xticks([r  for r in range(len(result))], ['Weight','origin_dyna','improve_dyna',])
plt.legend()
plt.xlabel('Groups')
plt.ylabel('Time')
plt.show()


# In[ ]:




