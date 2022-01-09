import urllib.request
from time import sleep
from bs4 import BeautifulSoup
import datetime


while True:

    html = urllib.request.urlopen('http://192.168.1.200').read()
    soup = BeautifulSoup(html, 'html.parser')

    humidity = soup.find("div", {"id": "humidity"})
    temperature = soup.find("div", {"id": "temperature"})

    print("Time:{}".format(datetime.datetime.now()))
    print("humidity:{}".format(humidity.contents[0]))
    print("temperature:{}".format(temperature.contents[0]))
    print('...')


    sleep(5)
