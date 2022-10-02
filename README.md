## HW 2

 - Name: Arin Nene
 - Email: arnene@usc.edu

### Programming Problem Notes

 For each programming problem, let us know:

 - How we should compile your code (`g++` command or `make` target)
  Just "make" or "make all". No target necessary.


 - Design decisions you made or other non-trivial choices for your implementation
 I used a vector for productList. For search, I use a product set as an intermediate to find all pertinent products. I push it to a vector "hits" and return that.


 - Any additional tests you wrote and what files those exist in

 - Known errors/anything to help us grade (though we will run automated tests,
knowing what features may be broken/missing may help us provide some partial credit)
Valgrind should be good. No features should be missing. My AND/OR search will ignore mistyped or non-existent terms  (e.g. AND tommy trjan will return the Tommy book rather than nothing.)
Also clang-format and clang-tidy are irrelevant