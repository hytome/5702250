def print_num_range(start, end):
    
    if start == end:
        print(f"[{start}]")
    
    elif start < end:
        print(f"[{', '.join(str(i) for i in range(start, end + 1))}]")
    
    else:
        print(f"[{', '.join(str(i) for i in range(start, end - 1, -1))}]")


print_num_range(2, 7)
print_num_range(19, 11)
print_num_range(5, 5)