# m,n,k-game
A performant, C++ implementation of the [m,n,k-game](http://weijima.com/index.php?option=com_content&view=article&id=11).

---
#### An m,n,k game, where m = 5, n = 9, k = 4:

 
(x,y) | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8
------|---|---|---|---|---|---|---|---|---
0     |   | X |   |   | X | X |   | O | X 
1     | O | X |   | O |   |   |   | X |  
2     |   | X |   |   | O |   |   |   |  
3     | O | O | O |   |   | O |   |   | O 
4     | X |   |   | X |   |   | O | X |  

Above, 'O' has won with 'k'-in-a-row (4-in-a-row) at: (1,3), (2,4), (3,5), (4,6)

---
##### This repository primarily adopts the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
