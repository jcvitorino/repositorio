

# This script file generates a svm.html file, which contains all the information needed to use the svm system.

import svm
import pydoc

doc = pydoc.HTMLDoc()


# Open the document...
out = open('svm.html','w')
out.write('<html>\n')
out.write('<head>\n')
out.write('<title>pysvm</title>\n')
out.write('</head>\n')
out.write('<body>\n')


# Openning blob...
readme = open('readme.txt','r').read()
readme = readme.replace('\n','<br/>')
out.write(doc.bigsection('Overview','#ffffff','#7799ee',readme))


# lda functions...
funcs = ''
funcs += doc.docroutine(svm.solvePair)
funcs += doc.docroutine(svm.looPair)
funcs += doc.docroutine(svm.looPairSelect)
funcs = funcs.replace('&nbsp;',' ')
out.write(doc.bigsection('Functions','#ffffff','#eeaa77',funcs))


# Classes...
classes = ''
classes += doc.docclass(svm.Kernel)
classes += doc.docclass(svm.Params)
classes += doc.docclass(svm.ParamsRange)
classes += doc.docclass(svm.ParamsSet)
classes += doc.docclass(svm.Dataset)
classes += doc.docclass(svm.Model)
classes += doc.docclass(svm.MultiModel)
classes = classes.replace('&nbsp;',' ')
out.write(doc.bigsection('Classes','#ffffff','#ee77aa',classes))


# Close the document...
out.write('</body>\n')
out.write('</html>\n')
out.close()
