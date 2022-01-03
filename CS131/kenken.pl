/*
    This section is the illustration of performance difference in kenken vs plain_kenken
    A test case I chose was the size of 4. The reason behind it was size 6 took too long for 
    plain_kenken to finish and size 1 did not show a significant difference in performance.
    Below runtime is a measure of cpu_time in statistics, and the unit is ms. Below test case
    was used for the calcultation.

    statistics(cpu_time,[Start|_]),
    kenken(
            4,
            [
            +(6, [[1|1], [1|2], [2|1]]),
            *(96, [[1|3], [1|4], [2|2], [2|3], [2|4]]),
            -(1, [3|1], [3|2]),
            -(1, [4|1], [4|2]),
            +(8, [[3|3], [4|3], [4|4]]),
            *(2, [[3|4]])
            ],
            T
        ),
    statistics(cpu_time,[Stop|_]),
    Runtime is Stop - Start.

    kenken:
        Runtime = 1 ms

    same test case as kenken.
    plain_kenken:
        Runtime = 1550 ms
    
    As it is illustrated in the results, plain_kenken is significantly slower than kenken on size 4.
    As the size of matrix increases, the difference will get even more drastic.
*/
kenken(N,C,T):-
    row_length(T,N),
    col_length(T,N),
    in_domain(T,N),
    maplist(fd_all_different,T),
    transpose(T,TT),
    maplist(fd_all_different,TT),
    maplist(rule(T),C),
    maplist(fd_labeling,T).

extract(S, [X|Y], Element):-
    nth(X,S,Row),
    nth(Y,Row,Element).

rule(T,+(S, L)):-add(T,S,L).
rule(T,*(P, L)):-multiply(T,P,L).
rule(T,-(D, J, K)):-subtract(T,J,K,D).
rule(T,/(Q, J, K)):-divide(T,J,K,Q).

add(_,0,[]).
add(T,S,[H|TL]):- 
    extract(T,H,Element),
    add(T, Result, TL),
    S #= Element + Result.

multiply(_,1,[]).
multiply(T,P,[H|TL]):- 
    extract(T,H,Element),
    multiply(T, Result, TL),
    P #= Element * Result.

subtract(T,J,K,D):-
    extract(T,K,First_element),
    extract(T,J,Second_element),
    (D #= First_element - Second_element; D #= Second_element - First_element).

divide(T,J,K,Q):-
    extract(T,K,First_element),
    extract(T,J,Second_element),
    (Q #= First_element / Second_element; Q #= Second_element / First_element).

row_length(T,N):- length(T,N).

col_length([],_).
col_length([H|T], N):-
    length(H,N),
    col_length(T,N).

in_domain([],_).
in_domain([H|T], N):-
    fd_domain(H,1,N),
    in_domain(T,N).

%got the idea of implementation of transpose from the TA hint ccode reference github provided in Piaza
%it is originally from SWI-prolog implementation
%credit of tranpose goes to SWI-prolog and TA hint code.
%Source: https://stackoverflow.com/questions/4280986/how-to-transpose-a-matrix-in-prolog

transpose([], []).
transpose([F|Fs], Ts) :-
    transpose(F, [F|Fs], Ts).
transpose([], _, []).
transpose([_|Rs], Ms, [Ts|Tss]) :-
        lists_firsts_rests(Ms, Ts, Ms1),
        transpose(Rs, Ms1, Tss).
lists_firsts_rests([], [], []).
lists_firsts_rests([[F|Os]|Rest], [F|Fs], [Os|Oss]) :-
        lists_firsts_rests(Rest, Fs, Oss).


unique_list(N,List) :-
    length(List, N),
    elements_between(List, 1, N),
    all_unique(List).

all_unique([ ]).
all_unique([H|T]) :-
    member(H, T), !, fail.
all_unique([_|T]) :- all_unique(T).

elements_between(List, Min, Max) :-
    maplist(between(Min, Max), List).


plain_kenken(N,C,T):-
    row_length(T,N),
    col_length(T,N),
    maplist(unique_list(N),T),
    transpose(T,TT),
    maplist(unique_list(N),TT),
    maplist(plain_rule(T),C).

plain_rule(T,+(S, L)):-plain_add(T,S,L).
plain_rule(T,*(P, L)):-plain_multiply(T,P,L).
plain_rule(T,-(D, J, K)):-plain_subtract(T,J,K,D).
plain_rule(T,/(Q, J, K)):-plain_divide(T,J,K,Q).

plain_add(_,0,[]).
plain_add(T,S,[H|TL]):- 
    extract(T,H,Element),
    plain_add(T, Result, TL),
    S is Element + Result.

plain_multiply(_,1,[]).
plain_multiply(T,P,[H|TL]):- 
    extract(T,H,Element),
    plain_multiply(T, Result, TL),
    P is Element * Result.

plain_subtract(T,J,K,D):-
    extract(T,K,First_element),
    extract(T,J,Second_element),
    (D is First_element - Second_element; D is Second_element - First_element).

plain_divide(T,J,K,Q):-
    extract(T,K,First_element),
    extract(T,J,Second_element),
    (Q is First_element / Second_element; Q is Second_element / First_element).

/*
    API for No-op KenKen
    noop_kenken/4 accepts folliwng arguments:
    1. N, a nonnegative integer specifying the number of cells on each side of the KenKen square.
    2. C, a list of numeric cage constraints as described below.
    3. T, a list of list of integers. All the lists have length N. This represents the N×N grid.
    4. O, a list of operators that the solver need to apply onto each cells (for example, [+,-,*,/])
    The caller should expect similar output compared to KenKen solver; the only difference is that
        operators will also be inlcuded in the outputs since the solver needs to figure out the outputs.
    
    For exmaple,

    noop_kenken_testcase(
        4,
        [
            (7,[1|1],[1|2]),
            (1,[1|3],[2|3]),
            (3,[1|4],[2|4]),
            (3,[2|1],[3|1]),
            (2,[2|2],[3|2]),
            (6,[4|1],[4|2], [4|3]),
            (48,[3|3],[3|4],[4|4]),
        ], T, O
    ).

    This out output:
    O = [+,-,*,/]
    T = [
        [3,4,2,1],
        [4,1,3,2],
        [1,2,4,3],
        [2,3,1,4]
    ]

      when the user types ; for more, the solver outputs no.
      If there are no solution, then the solver outputs no.

*/


