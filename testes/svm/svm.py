from params import Kernel
from params import Params
from params_sets import ParamsRange
from params_sets import ParamsSet
from dataset import Dataset
from model import Model
from loo import looPair
from loo import looPairRange
from loo import looPairBrute
from loo import looPairSelect
from multiclass import MultiModel

import smo



def solvePair(params,dataset,negLabel,posLabel):
  """Solves for a pair of labels - you provide a parameters object, a data set and the labels to assign to -1 and +1 respectivly. It then returns a Model object."""
  s = smo.SMO()
  s.setParams(params)
  s.setData(dataset.getTrainData(negLabel,posLabel))

  s.solve()

  return s.getModel()
