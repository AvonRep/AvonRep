num=[0 ,10];
denom=[1,15,50,10];
T=tf([num],[denom]);

figure(1)
rlocus(T)

figure(2)
bode(T)

figure(3)
margin(T)

%% 

Kp = 35;
Kd = 10;
C = pid(Kp,0,Kd)
R = feedback(C*T,1)

t = 0:0.01:2;

figure(4)
step(R,t)
