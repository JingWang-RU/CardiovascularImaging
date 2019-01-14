import os
import json
dir = os.listdir('./gt-test-epoch200/')
print("hello")

dict={}
summ_vessel={}
summ_patient ={}
for a in dir:
   tt = a.split('_')
   if tt[0]+'_'+tt[1]+'_'+tt[2] in summ_vessel:
      summ_vessel[tt[0]+'_'+tt[1]+'_'+tt[2]]+=1
   else:
      summ_vessel[tt[0]+'_'+tt[1]+'_'+tt[2]]=1
   if tt[0]+'_'+tt[1] in summ_patient:
      summ_patient[tt[0]+'_'+tt[1]]+=1
   else:
      summ_patient[tt[0]+'_'+tt[1]]=1
 
print(len(summ_vessel.keys()))

print(len(summ_patient.keys()))

with open('sumary_vessel.txt', 'w') as file:
   file.write(json.dumps(summ_vessel))
with open('summary_patient.txt', 'w') as file:
   file.write(json.dumps(summ_patient))

