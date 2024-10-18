def allprice_num():
    global price, price_num
    price, price_num = map(int, input("").split())
    

def allprice_cheak():
    sum_price = 0
    for i in range(1,price_num+1):
        cheak_price1,cheak_price2 = map(int, input("").split())
        sum_price += cheak_price1 * cheak_price2
        
        
    if price == sum_price:
            print("Yes")
    else:
            print("No")
            
def main():
    allprice_num()
    allprice_cheak()
    
main()