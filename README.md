# GenealogicalTree
Trial for a Genealogical Tree

There are limitations on the algorithm. 

1. It will not handle correctly, maybe get into loop, the case where 
there is one of the parents have relation with their child or even a predecessor.

2. If there are more than one ascendants with the same name we are searching eg father and grand-father then it will not show as different path,
but will show them all.

3. The algorithm will handle a person having more than one relations.

The TestData.txt file has sections:

Section [INFO] holds the name of the descendant and his/her ascendant we are looking

Then there are sections for all persons [Person_%d] and their relation [Relation_%d]. The order is of no consequence.
But there must not be gaps in the number of [Person_%d] or [Relation_%d], they start from 0 and increase by 1

eg
[Person_0]  [Person_1] ...... [Person_10] ......
[Relation_0]  [Relation_1] ...... [Person_20] ......

the ID of the Person is used in the relation sections to indicate each partner and children (if the exist)

Format:
[Person_%d]
Name = (a string)
Lastname = (a string)
Location = (a string)
DateOfBirth = (a string)

[Relation_%d]
Partner_0 = (integer which MUST exist in the [Perspn_%d])
Partner_1 = (integer which MUST exist in the [Perspn_%d])

                     OR if there are children from the relation
[Relation_%d]
Partner_0 = (integer which MUST exist in the [Perspn_%d])
Partner_1 = (integer which MUST exist in the [Perspn_%d])
Child_0 = (integer which MUST exist in the [Perspn_%d])
Child_1 = (integer which MUST exist in the [Perspn_%d])
....................
Child_10 = (integer which MUST exist in the [Perspn_%d])

in case of children again there must not be gaps in the sequence starting from 0 increasing by 1.




The order of data in each section ([Person_%d], [Relation_%d]) is of no consequence.