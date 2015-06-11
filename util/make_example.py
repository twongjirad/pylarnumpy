from tables import *
import numpy as np

NADCS = 10

class Particle(IsDescription):
    eventid = UInt64Col(pos=0)
    crate   = UInt16Col(pos=1)
    slot    = UInt16Col(pos=2)
    channel = UInt16Col(pos=3)
    wireid  = UInt16Col(pos=4)
    adcs    = UInt16Col( (NADCS,), (0)*NADCS, pos=5 )

h5file = open_file("outtest.h5",mode="w",title="Test file")

#group = h5file.create_group( "/", "RawDigits", "TPC ADC values" )
table = h5file.create_table( "/", "RawDigits", Particle, "TPC data" )
particle = table.row

for i in xrange(0,3):
    particle['eventid'] = i+1
    particle['crate'] = 9
    particle['slot'] = 7
    particle['channel'] = 16
    particle['wireid'] = 10
    particle['adcs'] = np.ones( NADCS )*(i+1)
    particle.append()
