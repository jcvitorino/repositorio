from pyroc import *
import pyroc
random_sample  =  pyroc.random_mixture_model()
#print random_sample
roc = ROCData(random_sample)
roc.auc()
roc.plot(title='ROC Curve')
roc.confusion_matrix(0.5)
roc.confusion_matrix(0.5,True)
roc.evaluateMetrics(roc.confusion_matrix(0.5))

x = random_mixture_model()
print x
r1 = ROCData(x)
y = random_mixture_model()
print y
r2 = ROCData(y)
lista = [r1,r2]
plot_multiple_roc(lista,'Multiple ROC Curves',include_baseline=True)
 
