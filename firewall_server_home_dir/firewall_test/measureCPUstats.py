import sys
import time
import threading
import subprocess
import signal
import os
import multiprocessing



class CPUstats(threading.Thread):
    def __init__(self, path):
        self.file = open(path+'_cpu.log', 'w')
        self.file2 = open(path+'_mem.log', 'w')

        threading.Thread.__init__(self)
        self.running = True
    def isRunning(self):
        return self.running

    def run(self):
        my_env = os.environ.copy()
        # force mpstat to use this time format and never append 'AM' or 'PM'
        my_env["S_TIME_FORMAT"] = "ISO"

        cpu_count = multiprocessing.cpu_count()

        self.file.write('time;cpu;usr;nice;sys;iowait;irq;soft;steal;guest;gnice;idle\n')
        self.file2.write('time;'+
                        'mem.total;mem.used;mem.free;mem.shared;mem.buffcache;mem.available;'+
                        'swap.total;swap.used;swap.free\n')

        while (self.running):
            cpustats = subprocess.Popen(['mpstat', '1' , '1', '-P', 'ON'], env=my_env, stdout=subprocess.PIPE).communicate()[0].split('\n')
            memstats = subprocess.Popen(['free', '-m'], stdout=subprocess.PIPE).communicate()[0].split('\n')
            t = time.time()
            self.file2.write(str(t)+';')
            self.file2.write(";".join(str(memstats[1]).split(':')[1].strip().split())+';')
            self.file2.write(";".join(str(memstats[2]).split(':')[1].strip().split())+'\n')
            for i in range(4,4 + cpu_count):
                self.file.write(str(t)+';')
                self.file.write(";".join(str(cpustats[i]).split()[1:])+'\n')
            self.file.flush()
            self.file2.flush()



        self.file.close()
        self.file2.close()

    def stop(self):
        self.running = False

def measure(path):
    global thread
    thread = CPUstats(path)
    thread.start()



def stop():
    thread.stop()



if sys.argv[1] == "handle_signal":
    stop()




if __name__ == '__main__':

    if(len(sys.argv)!=3):
        sys.exit("Error: wrong amount of arguments!!\nUsage: python measureCPUstats.py filename_to_wite_to duration")
    name = str(sys.argv[1])
    duration = int(sys.argv[2])
    measure(name)
    time.sleep(duration)
    stop()
