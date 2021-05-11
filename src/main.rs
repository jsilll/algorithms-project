let costs = [
    [7, 10, 14, 20, 21, 30],
    [8, 9, 15, 10, 18, 20],
    [9, 9, 16, 28, 30, 40],
    [11, 15, 20, 30, 35, 20],
];

let mut optimal = vec![vec![999999999; costs[0].len()]; costs.len()];

for j in 0..costs[0].len() {
    optimal[0][j] = costs[0][j];
}

for i in 1..optimal.len() {
    for j in i..optimal[i].len() {
        let mut min = 999999999;
        //Wrong interval
        for k in 1..j+1 {
            //Index shift because we start with 0
            let c = optimal[i - 1][j - k] + costs[i][k-1];
            min = std::cmp::min(c, min);
        }
        optimal[i][j] = min;
    }
}