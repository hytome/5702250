def main():
    subtotal = meals()
    print_results(subtotal)
    
def meals():
    people = int(input("How many people ate? "))
    subtotal = 0.0; 
    for i in range(1, people + 1):
        person_cost = float(input("Person #" + str(i) + ": How much did your dinner cost? "))
        subtotal = subtotal + person_cost 
    return subtotal
    
def print_results(subtotal):
    tax = subtotal * .08
    tip = subtotal * .15
    total = subtotal + tax + tip
    print("Subtotal: $" + str(subtotal))
    print("Tax: $" + str(tax))
    print("Tip: $" + str(tip))
    print("Total: $" + str(total))
    
    
main()