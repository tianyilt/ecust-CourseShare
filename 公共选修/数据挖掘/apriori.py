import numpy as np
from apyori import apriori

data = [['K','A','C','B'],
        ['D','A','C','E','B'],
        ['C','A','B','E'],
        ['B','A','D']
       ]
min_supp = 0.2
min_conf = 0.7
min_lift = 0.0
res = apriori(transactions=data, min_support=min_supp, min_confidence=min_conf, min_lift=min_lift)
for rule in res:
    print(str(rule))
print("ok")
