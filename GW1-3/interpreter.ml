
(* This is an *interpreter* for the typed arithmetic language discussed
 * in class. An interpreter is an implementation of the statics and dynamics.
 * The interpreter is responsible for typechecking and evaluating terms.
 * To run this interpeter, download the file and run from the command line:
 *    ocaml 03.2-interpreter.ml *)

(* First, we need to define types that mirror the grammar for our language.
 * The structure of the types should roughly match the structure of the
 * grammar, but the way we write them is a little different. These are
 * called the "abstract syntax" of the language. For example, in our
 * arithmetic language, the following would be "concrete syntax":
 *   if iszero z then z else s(z)
 * And in OCaml, the corresponding "abstract syntax" would be:
 *   If(Iszero(Z), Z, S(Z))
 * An instance of abstract syntax is called an "abstract syntax tree", or AST. *)
module Type = struct
  type t =
    | Int
    | Bool
    | Num
end

module Term = struct
  type t =
    | Z
    | N
    | S of t
    | True
    | False
    | If of t * t * t
    | Iszero of t
    | Plus of t * t
    | Times of t * t
end

(* The typechecker's job is to determine the type of a term if one exists.
 * We represent this with the OCaml type Type.t option, using the option
 * types discussed in class. Below is an implementation of a typechecker
 * for our arithmetic language. *)
let rec typecheck (t : Term.t) : Type.t option =
  match t with
  | Term.Z -> Some (Type.Int)
  | Term.N -> Some (Type.Num)
  | Term.S t' ->
    let tau = typecheck t' in
    (match tau with
     | Some Type.Int -> Some (Type.Int)
     | Some Type.Num -> Some (Type.Num)
     | _ -> None)
  | Term.True -> Some (Type.Bool)
  | Term.False -> Some (Type.Bool)
  | Term.If (t1, t2, t3) ->
    (match typecheck t1 with
     | Some Type.Bool ->
       (match typecheck t2 with
        | Some tau ->
          (match typecheck t3 with
           | Some tau' ->
             if tau = tau' then Some tau
             else None
           | _ -> None)
        | _ -> None)
     | _ -> None)
  | Term.Plus (t1, t2) ->
    (match typecheck t1 with
     | Some Type.Num ->
       (match typecheck t2 with
        | Some Type.Num -> Some (Type.Num)
        | _ -> None)
     | Some Type.Int ->
       (match typecheck t2 with
        | Some Type.Int -> Some (Type.Int)
        | _ -> None)
     | _ -> None)
  | Term.Times (t1, t2) ->
    (match typecheck t1 with
     | Some Type.Num ->
       (match typecheck t2 with
        | Some Type.Num -> Some (Type.Num)
        | _ -> None)
     | Some Type.Int ->
       (match typecheck t2 with
        | Some Type.Int -> Some (Type.Int)
        | _ -> None)
     | _ -> None)
  | Term.Iszero t' ->
    match typecheck t' with
    | Some Type.Int -> Some Type.Bool
    | Some Type.Num -> Some Type.Bool
    | _ -> None

exception Unreachable

(* Eval is a function that takes a term and reduces it all the way to
 * a value. It assumes that the terms it takes as arguments are well-typed,
 * meaning they won't be things like "S(false)" or "if 1 then ...". *)
let rec eval (t : Term.t) : Term.t =
  match t with
  | Term.Z -> Term.Z
  | Term.N -> Term.N
  | Term.S t' -> Term.S (eval t')
  | Term.True -> Term.True
  | Term.False -> Term.False
  | Term.If (t1, t2, t3) ->
    eval (match eval t1 with
     | Term.True -> t2
     | Term.False -> t3
     | _ -> raise Unreachable)
  | Term.Iszero t' ->
    (match eval t' with
     | Term.Z -> Term.True
     | Term.S _ -> Term.False
     | _ -> raise Unreachable)
  | Term.Plus (t1, t2) ->
    eval (match eval t1 with
     | Term.N ->  (match eval t2 with 
     | Term.N -> Term.N
             | _ -> raise Unreachable)
     | Term.Z ->  (match eval t2 with 
     | Term.Z -> Term.Z
             | _ -> raise Unreachable)
     | _ -> raise Unreachable)
  | Term.Times (t1, t2) ->
    eval (match eval t1 with
     | Term.N ->  (match eval t2 with 
     | Term.N -> Term.N
             | _ -> raise Unreachable)
     | Term.Z ->  (match eval t2 with 
     | Term.Z -> Term.Z
             | _ -> raise Unreachable)
     | _ -> raise Unreachable)

let main () =
  let t1 = Term.Z in
  assert (typecheck t1 = Some Type.Int);
  assert (eval t1 = Term.Z);

  let t2 = Term.Iszero Term.Z in
  assert (typecheck t2 = Some Type.Bool);
  assert (eval t2 = Term.True);

  let t3 = Term.Iszero Term.N in
  assert (typecheck t3 =  Some Type.Bool);
 
  let t4 = Term.Iszero Term.True in
  assert (typecheck t4 =  None);

  let t5 = Term.S Term.N in
  assert (typecheck t5 = Some Type.Num);

  let t6 = Term.Plus (Term.N ,Term.N) in
  assert (typecheck t6 = Some Type.Num);
  assert (eval t6 = Term.N);

  let t7 = Term.Plus (Term.Z ,Term.N) in
  assert (typecheck t7 = None);

  let t8 = Term.Plus (Term.Z ,Term.Z) in
  assert (typecheck t8 = Some Type.Int);
  assert (eval t8 = Term.Z);

  let t9 = Term.Plus (Term.N ,Term.N) in
  assert (typecheck t9 = Some Type.Num);

  let t10 = Term.Plus (Term.Z ,Term.N) in
  assert (typecheck t10 = None);

  let t11 = Term.Plus (Term.Z ,Term.Z) in
  assert (typecheck t11 = Some Type.Int);
  assert (eval t11 = Term.Z)


let () = main ()