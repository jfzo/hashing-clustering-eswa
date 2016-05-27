import fileinput

'''
linea de ejemplo:  5 Entropy: 0.645, Purity: 0.653
Los diccionarios tienen un valor de k para cada llave, y como valores asociados
tienen una lista con los valores obtenidos para firmas de 500,100,1500,2000 tanto para un esquema como para otro.
'''

etable=dict()
ptable=dict()
name = "" 
for line in fileinput.input():    
    fields=line.strip().replace(",","").split()
    if len(fields) > 1:
        #print fields
        k=int(fields[0])
        ent=float(fields[2])
        pur=float(fields[4])
        if k not in etable:
            etable[k] = []
        etable[k].append( ent )
        if k not in ptable:
            ptable[k] = []
        ptable[k].append( pur )
    else:
        name = fields[0]

#print "Entropy:\n",etable
#print "Purity:\n",ptable

# Primero Entropy
print "\n#### Entropy ",name,"\n"
print "|  k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |"
print "|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|"
for k in sorted(etable.keys()):
    print "|  {0:2d} |  'XX' |  {1:.3f}  |  {2:.3f}  |  {3:.3f}  |  {4:.3f}  |".format(k, etable[k][0], etable[k][1], etable[k][2], etable[k][3]),
    print "  {0:.3f} |  {1:.3f} |  {2:.3f} |  {3:.3f} |".format(etable[k][4], etable[k][5], etable[k][6], etable[k][7])

print ""
# Luego Purity
print "\n#### Purity ",name,"\n"
print "|  k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |"
print "|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|"
for k in sorted(ptable.keys()):
    print "|  {0:2d} |  'XX' |  {1:.3f}  |  {2:.3f}  |  {3:.3f}  |  {4:.3f}  |".format(k, ptable[k][0], ptable[k][1], ptable[k][2], ptable[k][3]),
    print "  {0:.3f} |  {1:.3f} |  {2:.3f} |  {3:.3f} |".format(ptable[k][4], ptable[k][5], ptable[k][6], ptable[k][7])
