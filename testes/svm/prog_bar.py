

import sys
import time



class ProgBar:
  """Simple console progress bar class. Note that object creation and destruction matter, as they indicate when processing starts and when it stops."""
  def __init__(self, width = 60, onCallback = None):
    self.start = time.time()
    self.fill = 0
    self.width = width
    self.onCallback = onCallback

    sys.stdout.write('Working \n')
    sys.stdout.flush()
    

  def __del__(self):
    self.end = time.time()
    self.__show(self.width)
    sys.stdout.write('\nDone - '+str(self.end-self.start)+' seconds\n\n')
    sys.stdout.flush()

  def callback(self, nDone, nToDo):
    """Hand this into the callback of methods to get a progress bar - it works by users repeatedly calling it to indicate how many units of work they have done (nDone) out of the total number of units required (nToDo)."""
    if self.onCallback:
      self.onCallback()
    n = int(float(self.width)*float(nDone)/float(nToDo))
    n = min((n,self.width))
    if n>self.fill:
      self.__show(n)

  def __show(self,n):
    sys.stdout.write('-'*(n-self.fill))
    sys.stdout.flush()
    self.fill = n
    