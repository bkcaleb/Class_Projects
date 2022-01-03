let subset a b = List.for_all (fun ai -> List.exists(fun bi-> ai=bi) b) a

let equal_sets a b = (subset b a) && (subset a b)

let rec set_union a b = match b with | [] -> a | h::t -> h::(set_union a t)

let rec set_all_union a = match a with
  | [] -> [] 
  | h::t -> set_union h (set_all_union t)

(*number 5*)
(*It is not possible to implement Russell's Paradox in Ocaml. The main problem with implementing Russell's function is that the code will run in infinite recursive loop
    if russell's function takes russell as a parameter. I believe implementation for russell function that takes in empty set or sets of themselves is possible; however,
     the problem occurs when russell takes in russell. Since russell tries to contradict itself over and over the loop does not end. The barbar's paradox is the perfect example too.
     Since the barbar can only shave who doesnt shave, if he shaves hiimself then he cant shave himself since he shaves himself. But if the barbar does not shave himself then he can
     shave himself since he does not shave himself. And the loop goes forever, which depicts our code for Ocaml implementation of Russell's paradox. *)

let rec computed_fixed_point eq f x =
  if eq x (f x) then x
  else computed_fixed_point eq f (f x)

type ('nonterminal, 'terminal) symbol =
  | N of 'nonterminal
  | T of 'terminal


let equals a b = equal_sets (snd a) (snd b)

let rec getN x =
  match x with
    | [] -> []
    | T h::t -> getN t
    | N h::t -> h::(getN t)


let rec get_reach input =
  let rules = (fst) input in
  let symbols = (snd) input in
  match rules with
  | []-> (rules,symbols)
  | h::t -> let temp_symbol = (fst h)::[] in
            let temp_rule = (snd h) in
            if subset temp_symbol symbols then get_reach (t,(set_union symbols (getN temp_rule)))
            else get_reach (t,symbols)

let get_reach_save input = 
  let x = get_reach input in
  ((fst)input, (snd)x)

let filter_reachable g = 
  let startSym = (fst g) in
  let rules = (snd g) in
  let _,reach_sym = computed_fixed_point equals get_reach_save (rules, startSym::[]) in
 (startSym, List.filter(fun a->List.exists(fun b -> b = (fst a))reach_sym )rules)