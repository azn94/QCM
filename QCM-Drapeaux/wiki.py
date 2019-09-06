# -*- coding: utf-8 -*-
import sys
import requests
import io
import time
import os

start = time.time()
S = requests.Session()
URL = "https://fr.wikipedia.org/w/api.php"
L=["wikipedia/out.txt","wikipedia/out2.txt","wikipedia/out3.txt","wikipedia/out4.txt","wikipedia/out5.txt","wikipedia/out6.txt"]
L2=["Chypre","Comores","Dominique","Equateur","Géorgie","Irlande","Macédoine","Maurice","Micronésie"]


for k in range(len(sys.argv)-1):
	if(os.fork()==0):
		
		if sys.argv[k+1] in L2:
			print("ajoute (pays)")
			PARAMS = {
				"action": "opensearch",
				"namespace": "0",
				"search": sys.argv[k+1]+" (pays)",
				"limit": "1",
				"format": "json"
			}
			print(sys.argv[k+1]+" (pays)")
		else:
			PARAMS = {
			"action": "opensearch",
			"namespace": "0",
			"search": sys.argv[k+1],
			"limit": "1",
			"format": "json"
		}
		
		R = S.get(url=URL, params=PARAMS)
		DATA = R.json()
		
		
		sys.tracebacklimit = 0
		response = requests.get(
			 'https://fr.wikipedia.org/w/api.php',
			 params={
				 'action': 'query',
				 'format': 'json',
				 'titles': DATA[1][0],
				 'prop': 'extracts',
				 'exintro': True,
				 'explaintext': True,
			 }
		 ).json()
		page = next(iter(response['query']['pages'].values()))
		f=io.open(L[k], 'w', encoding='utf8')
		f.write(page['extract'])
		
		f.close()
		exit()

os.wait()
end = time.time()
print("l'api wikipedia a pris "+str(end - start)+" secondes")
