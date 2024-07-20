# yeah its a do do conversino from minizic cause i need to learn to index with a deciscion variable

n = 5;
rankWomen =
[| 1, 2, 4, 3, 5,
| 3, 5, 1, 2, 4,
| 5, 4, 2, 1, 3,
| 1, 3, 5, 4, 2,
| 4, 2, 3, 5, 1 |];

rankMen =
[| 5, 1, 2, 4, 3,
| 4, 1, 3, 2, 5,
| 5, 3, 2, 4, 1,
| 1, 5, 4, 3, 2,
| 4, 3, 2, 1, 5 |];
int: n;

enum Men = _(1..n);
enum Women = _(1..n);

array[Women, Men] of int: rankWomen;
array[Men, Women] of int: rankMen;

array[Men] of var Women: wife;
array[Women] of var Men: husband;

% assignment
constraint forall (m in Men) (husband[wife[m]]=m);
constraint forall (w in Women) (wife[husband[w]]=w);
% ranking
constraint forall (m in Men, o in Women) (
    rankMen[m,o] < rankMen[m,wife[m]] ->
rankWomen[o,husband[o]] < rankWomen[o,m] );

constraint forall (w in Women, o in Men) (
    rankWomen[w,o] < rankWomen[w,husband[w]] ->
rankMen[o,wife[o]] < rankMen[o,w] );
solve satisfy;

output ["wives= \(wife)\nhusbands= \(husband)\n"];