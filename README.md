# RedBlackTree - self-balancing binary search tree

RedBlackTree Invariants:
1. Every node is red or Black
2. Root is always Black
3. New inserted node is always red
4. Every path from root to any leaves has the same number of black nodes
5. No path can have two consecutive red nodes
6. Null nodes are always black

<pre>
Rotations:
##
Note: gp - grandparent, p - parent. <br />

4                               4                
 \                             /         ##           
  6                           6           ##          
   \                         /                      
    8                       8                       
left(gp) rotation        right(gp) rotation         
RR case                  <br />LL case                    

   4                                8
    \                              /
     8                            4
    /                              \
   6                                6
right(p)-left(g) rotation      left(p)-right(gp) rotation
RL case                        <br />LR case

Re-balancing:

1) Black Uncle -> Rotate 
## 
After rotation: Parent is BLACK, and two children are RED

2) Red Uncle -> Color flip
##
After color flip: Parent is RED, and two children are BLACK
</pre>