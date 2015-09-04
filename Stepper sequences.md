#Stepper sequences
Two coil stepper motors, coil A and B with either positve current (+) or negative current (-)

Assume that four pins, where coil A is connected to pins 0 & 1 and coil B is connected to pins 2 & 3

Positive current is assumeed as lower index pin positive

##Two-phase, four-beat
Step	| A	 | B |Pins (0..3)
------	|---|---|----------
0		| + | + |	1010
1		| - | + | 0110
2		| - | - | 0101
3		| + | - | 1001
 
##Single-phase, four-beat 

Step	| A	 | B |Pins (0..3)
------	|---|---|-----------
0		| + | Z |	1000
1		| Z | + | 0010
2		| - | Z | 0100
3		| Z | - | 0001


##Eight-shot, half

Step	| A	 | B |Pins (0..3)
------	|---|---|-----------
0		| + | + |	1010
1		| Z | + | 0010
2		| - | + | 0110
3		| - | Z | 0100
4		| - | - |	0101
5		| Z | - | 0001
6		| + | - | 1001
7		| + | Z | 1000
