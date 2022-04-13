# 2SAT-Problem
SAT (Boolean satisfiability problem) is the problem of assigning Boolean values to variables to satisfy a given Boolean formula. 
The Boolean formula will usually be given in CNF(Conjuctive Normal form / Product of Maxterms / POS form)
The General satisfiability problem can be solved in exponential time. 

The special case of 2- satifiability problem is however polynomial time solvable.
Conditions: Each clause of the CNF expresssion must contain exactly 2 literals 
eg:  (x v y), (~x v y), (~x v ~y)

Brute Force: for n literals, truth table contains 2^n combinations that need to be checked.  O(2^n)  ( General satifiability problem solving approach)

Optimzed approach: Using the comcept of Graph traversals and SCCs( Strongly Connected components) we can reduce the time complexity from O(2^n) to O(n).
Data structures used: Adjacency List, Stack, vectors.
 
 
