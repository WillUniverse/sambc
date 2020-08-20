# -*- coding: UTF-8 -*-
import matplotlib.pyplot as plt 
import socket
import sys
from drawnow import *
from array import array 
BPM = []
cnt=0
plt.ion()

def makeFig():
  #Plot 1
  plt.ylim([0,1024])#valor min e max de y
  plt.title('BATIMENTO')#titulo
  plt.ylabel('frequencia cardiaca')#etiquetas do eixo y
  plt.plot(BPM, 'ro-', label='sinal de pulso ') #plot de temperature
  plt.legend(loc='upper left')#plot da legenda

#deixar vazio para receber conexões fora da rede local
host = ''

#porta onde o servidor irá escutar
port = 5000

#cria um UDP/IP socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#garante que o socket será destruído (pode ser reusado) após uma interrupção da execução 
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
#associa o socket à uma porta
s.bind((host, port))
   
while True:
  print('waiting to receive message')
  data, address = s.recvfrom(1024)
  
		
	#print ('received: ' + data + '\nfrom: ' + address[0] + '\nlistening on port: ' + str(address[1]))
  data= float(data)
  BPM.append(data)
  drawnow(makeFig)
  plt.pause(.000005)
  cnt=cnt+1
  if(cnt>50):
    cnt=+cnt;
    BPM.pop(0)


