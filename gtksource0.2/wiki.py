
"""
Created on Tue Aug 20 21:29:43 2019
@author: Youssef
"""
import sys
import requests
import io

S = requests.Session()

URL = "https://fr.wikipedia.org/w/api.php"

PARAMS = {
    "action": "opensearch",
    "namespace": "0",
    "search": sys.argv[1],
    "limit": "5",
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


f=io.open('out.txt', 'w', encoding='utf8')
f.write(page['extract'])

f.close()





PARAMS = {
    "action": "opensearch",
    "namespace": "0",
    "search": sys.argv[2],
    "limit": "5",
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


f=io.open('out2.txt', 'w', encoding='utf8')
f.write(page['extract'])

f.close()



PARAMS = {
    "action": "opensearch",
    "namespace": "0",
    "search": sys.argv[3],
    "limit": "5",
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


f=io.open('out3.txt', 'w', encoding='utf8')
f.write(page['extract'])

f.close()

   
