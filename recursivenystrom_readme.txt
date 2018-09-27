read the code of Recursive Sampling for the Nystrom Method
Algorithm 3 in the paper
 
lSize: n, n/2, n/2^2, ....

p_i = levs(code)
samp : index (code)
perm: 1:m (code)
SKS (code) has only index, not weight , hence 1/\sqrt(p_i) in Algorithm 3 is weights
\hat(S) (Algorithm 3) == samp (code)
\bar(S) (Algorithm 3) == rIndCurr from lSize (code)
\tilde(S) (Algorithm 3) == rInd (code)

line 6 in Algorithm \hat(S) = \bar(S) \cdot \tilde(S) is actually
perm : randperm(n)
line 106 to 109 in code
rIndCurr = perm(1:lSize(l)) # each X has some duplicate
KS = kernelFunc(X, rIndCurr, rInd) 
SKS = KS(samp, :);

