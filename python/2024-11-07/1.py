def name_diamond(name):
    
    for i in range(len(name)):
        print(name[:i+1])
    
    #
    for i in range(1, len(name)):
        print(' ' * i + name[i:])
        
name_diamond("MARTY")