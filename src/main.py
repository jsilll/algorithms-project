execution_costs = [[6,5,10,4], [4,10,3,8]]
communication_costs = [[0,5,0,0], [5,0,6,2], [0,6,0,1], [0,2,1,0]]



total_cost = assigned_processes = 0
matching = [-1] * len(execution_costs[0])
while(assigned_processes < len(execution_costs[0])):

    effective_costs = []
    # Setting up effective costs matrix
    for i in range(len(execution_costs)):
        effective_line = []
        for j in range(len(execution_costs[0])):
            effective_line.append(execution_costs[i][j] + sum(communication_costs[j]))
        effective_costs.append(effective_line)

    # Choosing best processor to assign
    min_cost =  min_i =  min_j = 999999
    for i in range(len(effective_costs)):
        for j in range(len(effective_costs[0])):
            if effective_costs[i][j] < min_cost:
                min_cost = effective_costs[i][j]
                min_i = i
                min_j = j

    for i in range(len(effective_costs)):
        for j in range(len(effective_costs[0])):
            if j == min_j:
                effective_costs[i][j] = 999999

    for i in range(len(execution_costs)):
        if i != min_i: 
            for j in range(len(execution_costs[0])):
                execution_costs[i][min_j] += communication_costs[i][min_j]
                communication_costs[i][min_j] = 0                

    assigned_processes += 1
    matching[min_j] = min_i
    total_cost += execution_costs[min_i][min_j]
    print(matching)


print(total_cost)