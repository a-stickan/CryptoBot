import robin_stocks as rs
import json
import os
from os import path

if (path.isfile('completedorders.csv')):
    os.remove('completedorders.csv')

try:
    rs.robinhood.authentication.login(by_sms=False) 
except:
    print("Error signing in to your Robinhood account. Make sure your account information is correct.")
    sys.exit(0)

try:
    file = open("buy.txt")
    content = file.readlines()
    ticker = content[0]
    amount = float(content[1])
    buying_power = float(content[2])
    buying_power *= 0.15; #change for different percentage
    file.close();
    f = open("buy.txt","w")
    f.write(str(buying_power))
    f.close()
except:
    print("Error in the file system.")
    sys.exit(0)

try:
    #operates off percentages, theoretically leaving buying_power always > 0
    rs.robinhood.orders.order_buy_crypto_by_price(ticker,buying_power)
    print("Successfully bought $" + str(buying_power) + " of " + str(ticker))
except:
    print("Error accessing Robinhood. Please check your internet connection.")
    sys.exit(0)

try:
    rs.robinhood.export.export_completed_crypto_orders(dir_path = 'C:\CryptoBot', file_name='completedorders.csv')
except:
    print("Error storing the transaction file.")
