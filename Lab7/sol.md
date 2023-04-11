non-pipelined:  
Longest time = max(Adder, MUX + Adder, Shifter) = 20 + 45 = 65ns   
4 * 65 +  Setup + CLK2Q = 4 * 65 + 10 + 10 = 280 ns  
f = 1 / 280ns = 3.571 MHz

pipelined:  
we want a single unit
10+65+10 = 85ns  
f=1/85ns = 11.764MHz  