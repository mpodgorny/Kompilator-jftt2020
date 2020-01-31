#!/bin/bash
clear
make clean
make

 ./kompilator test/0-div-mod.imp outs/t0.mr
 ./kompilator test/00-div-mod.imp outs/t00.mr
 ./kompilator test/1-numbers.imp outs/t1.mr
 ./kompilator test/2-fib.imp outs/t2.mr
 ./kompilator test/3-fib-factorial.imp outs/t3.mr
 ./kompilator test/4-factorial.imp outs/t4.mr
 ./kompilator test/5-tab.imp outs/t5.mr
 ./kompilator test/6-mod-mult.imp outs/t6.mr
 ./kompilator test/7-loopiii.imp outs/t7.mr
 ./kompilator test/8-for.imp outs/t8.mr
 ./kompilator test/9-sort.imp outs/t9.mr
 ./kompilator test/program0.imp outs/p1.mr
 ./kompilator test/program1.imp outs/p2.mr
 ./kompilator test/program2.imp outs/p3.mr

 ./maszyna-wirtualna outs/t0.mr
 ./maszyna-wirtualna outs/t00.mr
 ./maszyna-wirtualna outs/t1.mr
 ./maszyna-wirtualna outs/t2.mr
 ./maszyna-wirtualna outs/t3.mr
 ./maszyna-wirtualna outs/t4.mr
 ./maszyna-wirtualna outs/t5.mr
 ./maszyna-wirtualna outs/t6.mr
 ./maszyna-wirtualna outs/t7.mr
 ./maszyna-wirtualna outs/t8.mr
 ./maszyna-wirtualna outs/t9.mr
 ./maszyna-wirtualna outs/p1.mr
 ./maszyna-wirtualna outs/p2.mr
 ./maszyna-wirtualna outs/p3.mr
