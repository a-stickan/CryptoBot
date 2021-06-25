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
    file = open("sell.txt")
    content = file.readlines()
    ticker = content[0]
    amount = float(content[1])
    file.close()
    os.remove("sell.txt")
except:
    print("Error in the file system.")
    sys.exit(0)


try:
    #sell will never be greater than the amount possessed
    rs.robinhood.orders.order_sell_crypto_by_quantity(ticker,amount*0.15)
    print("Successfully sold " + str(amount * 0.15) + " of " + str(ticker))
except:
    print("Error accessing Robinhood. Please check your internet connection.")
    sys.exit(0)

try:
    rs.robinhood.export.export_completed_crypto_orders(dir_path = 'C:\CryptoBot', file_name='completedorders.csv')
except:
    print("Error storing the transaction file.")
    
