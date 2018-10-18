# hn_queries
Extract the popular (most frequent) queries that have been done during a
specific time range.

# Thought process

Let `n` be the number of lines (queries) in the input file.

## First idea

At first, the problem seems very simple. We just have to parse the file and,
in the potential boundaries of minimum and maximum timestamps, give either
the counts of the total distinct queries either the top N queries.

I assumed we wanted to optimize the search query, so I thought about how to
store this data the most efficiently to make the search in minimum time and 
space for both queries. 

Therefore, I set up an ordered map that keeps the timestamp as the key, 
and as a value an object `LogObject` containing a list of tuples (query, 
nb_query) for each distinct query.

This way, the search is done with the complexity of a search in a regular 
Binary Search Tree (as std::map is implemented like a red/black BST), but
the space complexity is the one of a map of length at most N, plus:
* For "distinct": a set to fill while parsing the required timestamps,
* For "top": a map to fill while parsing the required timestamps, and sort at
the end.

Total complexity of this idea #1:

Command distinct:
* Time: o(n*log(n))
* Space: o(n)

Command top:
* Time: o(n*log(n))
* Space: o(n)

Then, I realized I had it more complex than it really was: the subject was not
asking for such a service, that could do both command from the same data
structure. So I tought maybe we could improve those complexities using the
minimal algorithm for both commands. That led me to idea #2.

## Second idea

The problem is indeed simple. We can compute the result while we parse the
input file.

For the "distinct" command, we can put all the queries we see
in a set, and give the set at the end ; giving us a time complexity of O(n)
and space of O(n) too. 

For the "top", we store the queries and their counter in a map<string, int>,
and at the end we flip the map to make int <int, string> and sort it before
printing the top N queries as asked. This give us a time complexity of
O(n*log(n)) (because of the sorting) and space O(n).

In both case, we can save time by ending the parsing if the encountered
timestamp is greater than our maximum timestamp asked because the input logs
are sorted.

Total complexity of this idea #2:

Command distinct:
* Time: o(n)
* Space: o(n)

Command top:
* Time: o(n*log(n))
* Space: o(n)
