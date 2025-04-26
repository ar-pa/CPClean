int phi(int n){
    int tot = n;
    for(int p = 2; p * p <= n; p++)
	if(n % p == 0){
	    tot = tot / p * (p - 1);
	    while(n % p == 0)  n /= p;
	}
    if(n > 1)
	tot = tot / n * (n - 1);
    return tot;
}
for(int i = 1; i < n; i++){
	phi[i] += i;
	for(int j = i * 2; j < n; j += i)
		phi[j] -= phi[i];
}

