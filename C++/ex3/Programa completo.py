# -*- coding: utf-8 -*-
"""
Created on Fri Jul  2 15:59:50 2021

@author: DISRCT
"""
import pandas as pd
import requests
import time 

def sinal():
    proxies = {'https':"https://disrct:saladigital0305@rb-proxy-de.bosch.com:8080"}
    url_temperatura = 'https://treinamento-ets-default-rtdb.firebaseio.com/Gabriel/temperatura.json'
    url_umidade = 'https://treinamento-ets-default-rtdb.firebaseio.com/Gabriel/umidade.json'
    temperatura = float(requests.get(url_temperatura, proxies = proxies).content)
    umidade = float(requests.get(url_umidade,proxies = proxies).content)
    return temperatura, umidade


import mysql.connector
from sqlalchemy import create_engine
import matplotlib.pyplot as plt

def Inserir (sinal):
    con = mysql.connector.connect(user = "root", password = "saladigitalsql", host = "localhost",
                              port= "3306", database = "bernardelli", use_pure=True)
    cursor= con.cursor()
    insert_query = """INSERT INTO DHT11 (Temperatura, umidade) values ({},{});""".format(sinal[0],sinal[1])
    print(insert_query)
    cursor.execute(insert_query)
    con.commit()


def apresentar(sinal):
    print("Temperatura: {}".format(sinal[0]))
    print("Umidade: {}".format(sinal[1]))
    

def  Pegar():
	con = create_engine('mysql+pymysql://root:saladigitalsql@localhost/bernardelli')    
	df = pd.read_sql('SELECT * FROM DHT11', con) 
	df["timestamp"] = df.apply(string, axis =1)
	return df
    
def string (linha):
	b = str(linha["timestamp"])
	b = b[10:]
	return b
	
  


for i in range(10):
    valores = sinal()
    apresentar(valores)
    Inserir(valores)
    time.sleep(2)


a = Pegar()
a = a.iloc[-10:,:]

plt.plot(a["timestamp"],a["Temperatura"])
plt.xticks(rotation = 90)
plt.ylabel("Temperatura (C°)")
plt.xlabel("Timestamp")
plt.title("Temperatura x Timestamp", size = 15)
plt.show()

plt.plot(a["timestamp"],a["Umidade"], color = "red")
plt.xticks(rotation = 90)
plt.ylabel("Umidade")
plt.xlabel("Timestamp")
plt.title("Umidade x Timestamp", size = 15)
plt.show()
	
    