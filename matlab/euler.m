clear all;
close all;
data = load("data_debug.txt");


figure();
t = data(:,1);
ve = data(:,2);
vs = data(:,3);
plot(t,ve,'r');
hold on;
plot(t,vs,'g');
%plot(t,vs,'r');
legend('Ve(t)','Vs(t)');
%pause(2);
%hold on;
%u0=10;
%v0=10;
%rlambda=sqrt(6.28);
%exact = v0/rlambda * sin(t*rlambda)+u0*cos(t*rlambda);
%plot(t,exact, 'b');
