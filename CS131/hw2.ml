let rec converter rules givenSym = 
    match rules with
        |[]->[]
        |h::t -> if fst h = givenSym then snd h::converter t givenSym
                    else converter t givenSym

let convert_grammar gram1 = 
    (fst gram1, converter (snd gram1))

type ('nonterminal, 'terminal) parse_tree =
  | Node of 'nonterminal * ('nonterminal, 'terminal) parse_tree list
  | Leaf of 'terminal

type ('nonterminal, 'terminal) symbol =
  | N of 'nonterminal
  | T of 'terminal;;

let rec stupidtypeerror trees = 
  match trees with
    |[]->[]
    |h::t-> match h with
      |Node (_,leaves) -> stupidtypeerror leaves @ stupidtypeerror t
      |Leaf lf -> lf::stupidtypeerror t

let parse_tree_leaves tree = stupidtypeerror [tree]


let matcher_connector sym gram accept frag = 
  let rules = (gram sym) in
  let rec use_acceptor rules accept frag = match rules with
  | [] -> None
  | h::t -> let isAccepted = accepted h accept frag in match isAccepted with
            | None -> use_acceptor t accept frag
            | _ -> isAccepted

  and accepted ruless accept frag = match ruless with
    | []-> accept frag
    | hd::tl -> match hd with
      |N x -> let another_rule = gram x in use_acceptor another_rule (accepted tl accept) frag
      |T x -> match frag with
        |[]-> None
        |head::tail-> if head <> x then None
                      else accepted tl accept tail
  in use_acceptor rules accept frag


let make_matcher gram =  matcher_connector (fst gram) (snd gram)

let acceptor_for_parser t f = match f with 
  | [] -> Some t
  | _ -> None 

(*shuold look very similar to matcher - from TA slide *)
let iterate sym gram accept frag = 
  let rules = (gram sym) in
  let rec parsing sym rules accept child frag = match rules with
    |[] -> None
    |h::t-> let isParsed = parsed sym h accept child frag in 
      if isParsed <> None then isParsed
      else parsing sym t accept child frag
  and parsed sym ruless accept child frag = match ruless with
    |[] -> accept (Node(sym,child)) frag
    |hd::tl -> match hd with
      |N x -> let acceptorr new_child = parsed sym tl accept (child@[new_child]) in parsing x (gram x) acceptorr [] frag
      |T x ->  match frag with
        |[]->None
        |head::tail -> if head <> x then None
                      else parsed sym tl accept (child@[Leaf x]) tail
  in parsing sym rules accept [] frag

let make_parser gram = iterate (fst gram) (snd gram) acceptor_for_parser
