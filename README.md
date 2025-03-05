# PA 3: Implementing an AVL-Based Map and Performance Comparison

# How to run (enter in terminal): 
## 1) make 
## 2) ./run 

## logarithmic insertion and lookup 
- The AVL tree maintains O(log n) time complexity for insertion and lookup
- because the height of the tree is always O(log n) due to necessary rotations. 
- Also, nodes are arranged in sorted order, allowing binary search for insertion/lookup. 

## AVL Tree Operations and Logarithmic performance 
- The insert function follows a binary search pattern down the tree, finding the correct position
- and inserting. Rebalancing will occur if necessary to maintain logarithmic depth. 
- The erase function operates in a similar way. It removes the node and rebalances after if 
- needed to maintain logarithmic height. The lookup function traverses, at most, log(n) levels 
- in the tree which is efficient for a database as large as the one we're working with in this 
- project. 
- Insert: (O(log m))
- Erase: (O(log n))
- Lookup: (O(log n)) 

## Comparing Results 
- avl_map is consistently anywhere from ~10 to 60 ms faster than std::map. 
- This can be attributed to the fact that avl_map provides faste lookups than std::map due 
- to the way AVL trees have strictier balance and a reduced tree length. std::map 
- has fsater insertion/deletion due to the fact that it doesnt have to perform as many 
- rotations. In terms of trade-offs, std::map is stronger for datasets that require more 
- insertions and deletions while avl_map is stronger for frequent lookups. Both maintain 
- O(log n) complexity. 