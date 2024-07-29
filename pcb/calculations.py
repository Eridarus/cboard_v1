vout = 2.5
vin = 5
r_p = 19000
vfb = 0.55
ifb = 10e-9
#  vout = vfb(1+r2/r1)
#r1 + r2 <= vfb/(100*i_fb)
#r2 = r1(vout/vfb - 1)
ratio = vout/vfb-1
print("r2 to r1 ratio: "+str(vout/vfb-1))
print("maximum series resistance: " + str(vfb/(100*ifb)))

resistors = [10,	11,	12,	13,	15,	16,
18,	20,	22,	24,	27,	30,
33,	36,	39,	43,	47,	51,
56,	62,	68,	75,	82,	91]
bestpair=(10,11)
current_min = 4000000
for i in range(len(resistors)-1):
    for j in range(i+1,len(resistors)):
        if abs(resistors[j]/resistors[i]- ratio) < abs(current_min-ratio):
                current_min = resistors[j]/resistors[i]
                bestpair=(resistors[i], resistors[j])
print(bestpair)